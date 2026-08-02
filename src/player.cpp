#include "player.hpp"
#include "cards.hpp"
#include "constants.hpp"
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "helper.hpp"
#include "rlgl.h"
#include <iostream>
#include <iterator>
#include <numbers>
#include "opp.hpp"

Player::Player() : card_num(Constants::initial_num_cards) {
    is_turn = true;


    draw_wild = false;

    color_pick = 0;
    pick_color = false;

    pass_play = false;

    current_sprite.x = 0;
    current_sprite.y = 0;

    scale.x = 1;
    scale.y = 1;

    color_picker_size = 20;

    red = {(Constants::WINDOW_WIDTH / 2.0f) - (color_picker_size), (Constants::WINDOW_HEIGHT / 2.0f) - (color_picker_size / 2.0f) + 100, color_picker_size, color_picker_size};
    green = {(Constants::WINDOW_WIDTH / 2.0f), (Constants::WINDOW_HEIGHT / 2.0f) - (color_picker_size / 2.0f) + 100, color_picker_size, color_picker_size};
    yellow = {(Constants::WINDOW_WIDTH / 2.0f) - (color_picker_size), (Constants::WINDOW_HEIGHT / 2.0f) + (color_picker_size / 2.0f) + 100, color_picker_size, color_picker_size};
    blue = {(Constants::WINDOW_WIDTH / 2.0f), (Constants::WINDOW_HEIGHT / 2.0f) + (color_picker_size / 2.0f) + 100, color_picker_size, color_picker_size};

    SearchAndSetResourceDir("resources");

    rect = {(float)Constants::WINDOW_WIDTH / 2,
                    ((float)Constants::WINDOW_HEIGHT - Constants::sprite_height) - Constants::border_offset,
                    (Constants::sprite_width * 0.73f) * Constants::initial_num_cards,
                    Constants::sprite_height
    };
    rect.x -= rect.width / 2;

    texture_rect = {
        Constants::sprite_offset_x + (Constants::sprite_width * current_sprite.x),
        Constants::sprite_offset_y + (Constants::sprite_height * current_sprite.y),
        Constants::sprite_width, Constants::sprite_height
    };
    
    draw_rect = {
        rect.x, rect.y,
        Constants::sprite_width * scale.x,
        Constants::sprite_height * scale.y,
    };

}

void Player::draw() {
    DrawRectangleRec(rect, {0, 0, 0, 0});
    for (int i = 0; i < deck.size(); ++i) {
        texture_rect.x = Constants::sprite_offset_x + (Constants::sprite_width * deck[i].pos.x);
        texture_rect.y = (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * deck[i].pos.y),
        deck[i].rect.x = Lerp(deck[i].rect.x, rect.x + ((Constants::sprite_width / 1.5) * i), 0.2);
        deck[i].rect.y = Lerp(deck[i].rect.y, rect.y - ((Constants::sprite_height / 6) * deck[i].y_offset), 0.2);
        DrawTexturePro(cards, texture_rect, deck[i].rect, {0, 0}, 0, WHITE);
    }
}

void Player::load_deck() {
    for (int i = 0; i < Constants::initial_num_cards; ++i) {
        create_card();
        deck.push_back(card);
    }
    rect = {(float)Constants::WINDOW_WIDTH / 2,
                    ((float)Constants::WINDOW_HEIGHT - Constants::sprite_height) - Constants::border_offset,
                    (Constants::sprite_width * 0.73f) * Constants::initial_num_cards,
                    Constants::sprite_height
    };
    rect.x -= rect.width / 2;
}


void Player::create_card() {
    choose_random_card();
    card.pos.x = random_x;
    card.pos.y = random_y;
    card.y_offset = 0;
    card.isHovering = false;
    card.rect = {
        ((float)Constants::WINDOW_WIDTH / 2) - (Constants::sprite_width * 2), ((float)Constants::WINDOW_HEIGHT / 2 + (Constants::sprite_width / 2)),
        Constants::sprite_width,
        Constants::sprite_height,
    };
}

void Player::choose_random_card() {
    random_x = choose_col();
    random_y = choose_row();
    if (random_y == 5) {
        int trial = random_int(0, 1);
        if (trial) {
            random_x = 5;
        }
        else {
            random_x = 0;
        }
    }
}

void Player::add_card() {
    rect.width += Constants::sprite_width / 1.5;
    center_rect();
    create_card();
    deck.push_back(card);
    card_num++;
}

void Player::dish_deck(Center &center, int i, Opp &opponent) {
    center.random_x = deck[i].pos.x;
    center.random_y = deck[i].pos.y;
    rect.width -= Constants::sprite_width / 1.5;
    center_rect();
    card_num--;
    deck.erase(deck.begin() + i);
}

void Player::dish_wild(Center &center, int i) {
    current_wild_card = deck[i];
    center.random_y = deck[i].pos.y;
    center.random_x = deck[i].pos.x + color_pick;
    rect.width -= Constants::sprite_width / 1.5;
    center_rect();
    card_num--;
    deck.erase(deck.begin() + i);
}


void Player::update(Center &center, Opp &opponent) {
    possible_moves = 0;
    normal_moves = 0;
    wild_card_moves = 0;
    temp_x_pos = center.random_x;
    color_pick = 0;

    if (is_turn) {
        if (center.random_y == 5) {
            if (center.random_x < 5) {
            }
            else {
                temp_x_pos -= 5;
            }
        }

        if (center.random_y < 5) {
            for (int i = 0; i < deck.size(); ++i) {
                if (deck[i].pos.y == 5 && deck[i].pos.x == 0) {
                    normal_moves++;
                }
                if (deck[i].pos.y == 5 && deck[i].pos.y == 5) {
                    // wild_card_moves++;
                    normal_moves++;
                }
                if (deck[i].pos.x == center.random_x && deck[i].pos.y != 5) {
                    normal_moves++;
                }
                if (deck[i].pos.y == center.random_y && deck[i].pos.y != 5) {
                    normal_moves++;
                }
            };
        }
        else {
            for (int i = 0; i < deck.size(); ++i) {
                if (deck[i].pos.y == 5 && deck[i].pos.x == 0) {
                    normal_moves++;
                }
                if (deck[i].pos.y == 5 && deck[i].pos.y == 5) {
                    // wild_card_moves++;
                    normal_moves++;
                }
                if (deck[i].pos.y == temp_x_pos && deck[i].pos.y != 5) {
                    normal_moves++;
                }
            };
        }
        if (normal_moves == 0) {
            possible_moves = wild_card_moves;
        }
        else {
            possible_moves = normal_moves;
        }

        if (pass_play) {
            if (pick_color == false) {
                static float timer = 0.0f;
                static float last_time = 0.0f;
                if (timer - last_time > 2.0f) {
                    opponent.play(center);
                    pass_play = false;
                    timer = 0.0f;
                    last_time = timer;
                }
                else {
                    timer += 1 * GetFrameTime();
                }
            }
        }
    }

    // 1 to last - 1 cards
    if (pass_play == false) {
        if (normal_moves > 0) {
            for (int i = 0; i < Clamp(deck.size() - 1, 0, 1000); ++i) {
                collision_rect = {deck[i].rect.x, deck[i].rect.y, (deck[i].rect.width) / 1.5f, deck[i].rect.height};
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {collision_rect})) {
                    if (center.random_x == deck[i].pos.x || center.random_y == deck[i].pos.y && center.random_y < 5) {
                        if (deck[i].pos.x == 10) {
                            opponent.spawn();
                            opponent.spawn();
                            dish_deck(center, i, opponent);
                            pass_play = false;
                        }
                        else if (deck[i].pos.x == 11) {
                            dish_deck(center, i, opponent);
                            pass_play = false;
                        }
                        else if (deck[i].pos.x == 12) {
                            dish_deck(center, i, opponent);
                            pass_play = false;
                        }
                        else {
                            dish_deck(center, i, opponent);
                            pass_play = true;
                        }
                    }
                    else if (center.random_y == 5) {
                        if (deck[i].pos.y == temp_x_pos) {
                            if (deck[i].pos.x == 10) {
                                opponent.spawn();
                                opponent.spawn();
                                dish_deck(center, i, opponent);
                                pass_play = false;
                            }
                            else if (deck[i].pos.x == 11) {
                                dish_deck(center, i, opponent);
                                pass_play = false;
                            }
                            else if (deck[i].pos.x == 12) {
                                dish_deck(center, i, opponent);
                                pass_play = false;
                            }
                            else {
                                dish_deck(center, i, opponent);
                                pass_play = true;
                            }
                        }
                        else if (deck[i].pos.y == 5 && deck[i].pos.x < 5) {
                            dish_wild(center, i);
                            pick_color = true;
                            pass_play = true;
                            return;
                        }
                        else if (deck[i].pos.y == 5 && deck[i].pos.x == 5) {
                            dish_wild(center, i);
                            pass_play = false;
                            draw_wild = true;
                            pick_color = true;
                        }
                    }
                    else if (deck[i].pos.y == 5 && deck[i].pos.x < 5) {
                        dish_wild(center, i);
                        pick_color = true;
                        pass_play = true;
                        return;
                    }
                    else if (deck[i].pos.y == 5 && deck[i].pos.x == 5) {
                        dish_wild(center, i);
                        pass_play = false;
                        draw_wild = true;
                        pick_color = true;
                    }
                }
            }
        }
        else if (wild_card_moves > 0) {
            for (int i = 0; i < Clamp(deck.size() - 1, 0, 1000); ++i) {
                collision_rect = {deck[i].rect.x, deck[i].rect.y, (deck[i].rect.width) / 1.5f, deck[i].rect.height};
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {collision_rect})) {
                    if (deck[i].pos.y == 5 && deck[i].pos.x == 5) {
                        dish_wild(center, i);
                        if (center.random_y == 5 && center.random_x < 5) {
                            pick_color = true;
                            pass_play = true;
                        }
                        else {
                            pass_play = false;
                            draw_wild = true;
                            pick_color = true;
                        }
                    }
                }
            }
        }

        // last card
        if (normal_moves > 0) {
            collision_rect = {deck[deck.size() - 1].rect.x, deck[deck.size() - 1].rect.y, deck[deck.size() - 1].rect.width, deck[deck.size() - 1].rect.height};
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {collision_rect})) {
                if (center.random_x == deck[deck.size() - 1].pos.x || center.random_y == deck[deck.size() - 1].pos.y && center.random_y < 5) {
                    if (deck[deck.size() - 1].pos.x == 10) {
                        opponent.spawn();
                        opponent.spawn();
                        dish_deck(center, deck.size() - 1, opponent);
                        pass_play = false;
                    }
                    else if (deck[deck.size() - 1].pos.x == 11) {
                        dish_deck(center, deck.size() - 1, opponent);
                        pass_play = false;
                    }
                    else if (deck[deck.size() - 1].pos.x == 12) {
                        dish_deck(center, deck.size() - 1, opponent);
                        pass_play = false;
                    }
                    else {
                        dish_deck(center, deck.size() - 1, opponent);
                        pass_play = true;
                    }
                }
                else if (center.random_y == 5) {
                    if (deck[deck.size() -1].pos.y == temp_x_pos) {
                        if (deck[deck.size() - 1].pos.x == 10) {
                            opponent.spawn();
                            opponent.spawn();
                            dish_deck(center, deck.size() - 1, opponent);
                            pass_play = false;
                        }
                        else if (deck[deck.size() - 1].pos.x == 11) {
                            dish_deck(center, deck.size() - 1, opponent);
                            pass_play = false;
                        }
                        else if (deck[deck.size() - 1].pos.x == 12) {
                            dish_deck(center, deck.size() - 1, opponent);
                            pass_play = false;
                        }
                        else {
                            dish_deck(center, deck.size() - 1, opponent);
                            pass_play = true;
                        }
                    }
                    else if (deck[deck.size() - 1].pos.y == 5 && deck[deck.size() - 1].pos.x < 5) {
                        dish_wild(center, deck.size() - 1);
                        pick_color = true;
                        pass_play = true;
                        return;
                    }
                    else if (deck[deck.size() - 1].pos.y == 5 && deck[deck.size() - 1].pos.x == 5) {
                        dish_wild(center, deck.size() - 1);
                        pass_play = false;
                        draw_wild = true;
                        pick_color = true;
                    }
                }
                else if (deck[deck.size() - 1].pos.y == 5 && deck[deck.size() - 1].pos.x < 5) {
                    dish_wild(center, deck.size() - 1);
                    pick_color = true;
                    pass_play = true;
                    return;
                }
                else if (deck[deck.size() - 1].pos.y == 5 && deck[deck.size() - 1].pos.x == 5) {
                    dish_wild(center, deck.size() - 1);
                    pass_play = false;
                    draw_wild = true;
                    pick_color = true;
                }
            }
        }
        else if (wild_card_moves > 0) {
            collision_rect = {deck[deck.size() - 1].rect.x, deck[deck.size() - 1].rect.y, deck[deck.size() - 1].rect.width, deck[deck.size() - 1].rect.height};
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {collision_rect})) {
                if (deck[deck.size() - 1].pos.y == 5 && deck[deck.size() - 1].pos.x == 5) {
                    dish_wild(center, deck.size() - 1);
                    if (center.random_y == 5 && center.random_x < 5) {
                        pass_play = true;
                        pick_color = true;
                    }
                    else {
                        pass_play = false;
                        draw_wild = true;
                        pick_color = true;
                    }
                }
            }
        }
    }


    if (pass_play == false) {
        for (int i = 0; i < deck.size(); ++i) {
            collision_rect = {deck[i].rect.x, deck[i].rect.y, (deck[i].rect.width) / 1.5f, deck[i].rect.height};
            if (CheckCollisionPointRec(GetMousePosition(), {collision_rect})) {
                deck[i].isHovering = true;
                deck[i].y_offset = Lerp(deck[i].y_offset, 1.0f, 0.3f);
            }
            else {
                deck[i].isHovering = false;
                deck[i].y_offset = Lerp(deck[i].y_offset, 0.0f, 0.3f);
            }
        }

        int last = deck.size() - 1;
        if (deck.size() > 0) {
            collision_rect = {deck[last].rect.x, deck[last].rect.y, (deck[last].rect.width), deck[last].rect.height};
            if (CheckCollisionPointRec(GetMousePosition(), {collision_rect})) {
                deck[last].isHovering = true;
                deck[last].y_offset = Lerp(deck[last].y_offset, 1.0f, 0.3f);
            }
            else {
                deck[last].isHovering = false;
                deck[last].y_offset = Lerp(deck[last].y_offset, 0.0f, 0.3f);
            }
        }
    }
    if (deck.size() == 0) {
        center.is_over = true;
    }
}

void Player::load_texture() {
    cards = LoadTexture("cards.png");
}

void Player::center_rect() {
    rect.x = (float)Constants::WINDOW_WIDTH / 2;
    rect.x -= rect.width / 2;
}
