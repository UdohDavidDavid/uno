#include "opp.hpp"
#include "constants.hpp"
#include "helper.hpp"
#include "player.hpp"
#include "raylib.h"
#include "raymath.h"
#include "center.hpp"
#include <iostream>
#include <utility>

Opp::Opp(){
    is_turn = true;
    card_num = Constants::initial_num_cards;
    possible_moves = 0;
    wild_card_moves = 0;
    temp_x_pos = 0;
    draw_wild = false;
    draw_four_wild = false;
    is_drawing_card = false;
    begin_four_timer = false;
    begin_one_timer = false;
    play_again = false;
    draw_one = false;
    has_win = false;

    rect = {Constants::WINDOW_WIDTH / 2.0f,
        Constants::border_offset,
        (Constants::sprite_width * 0.73f) * Constants::initial_num_cards,
        Constants::sprite_height,
    };
    rect.x -= rect.width / 2;

    texture_rect = {
        Constants::sprite_offset_x + (Constants::sprite_width * 0),
        (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * 0),
        Constants::sprite_width, Constants::sprite_height
    };
}

void Opp::load_texture() {
    cards = LoadTexture("cards.png");
}

void Opp::create_card() {
    choose_random_card();
    card.pos.x = random_x;
    card.pos.y = random_y;
    card.y_offset = 0;
    card.isHovering = false;
    card.rect = {
        ((float)Constants::WINDOW_WIDTH / 2) - (Constants::sprite_width * 2), ((float)Constants::WINDOW_HEIGHT / 2 - (Constants::sprite_width)),
        Constants::sprite_width,
        Constants::sprite_height,
    };
}

void Opp::choose_random_card() {
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

void Opp::center_rect() {
    rect.x = (float)Constants::WINDOW_WIDTH / 2;
    rect.x -= rect.width / 2;
}

void Opp::load_deck() {
    for (int i = 0; i < Constants::initial_num_cards; ++i) {
        create_card();
        deck.push_back(card);
    }
    rect = {Constants::WINDOW_WIDTH / 2.0f,
        Constants::border_offset,
        (Constants::sprite_width * 0.73f) * Constants::initial_num_cards,
        Constants::sprite_height,
    };
    rect.x -= rect.width / 2;
}


void Opp::dish_wild(Center &center, int i) {
    currently_moving_card = deck[i];
    mov_x = currently_moving_card.rect.x;
    mov_y = currently_moving_card.rect.y;
    is_drawing_card = true;
    rect.width -= Constants::sprite_width * 0.73;
    center_rect();
    deck.erase(deck.begin() + i);
}

void Opp::dish_four_wild(Center &center, int i) {
    currently_moving_card = deck[i];
    mov_x = currently_moving_card.rect.x;
    mov_y = currently_moving_card.rect.y;
    is_drawing_card = true;
    rect.width -= Constants::sprite_width * 0.73;
    center_rect();
    deck.erase(deck.begin() + i);
}

void Opp::dish_card(Center &center, int i) {
    currently_moving_card = deck[i];
    mov_x = currently_moving_card.rect.x;
    mov_y = currently_moving_card.rect.y;
    is_drawing_card = true;
    rect.width -= Constants::sprite_width * 0.73;
    center_rect();
    deck.erase(deck.begin() + i);
}

void Opp::spawn() {
    if (!is_over) {
        create_card();
        deck.push_back(card);
        rect.width += Constants::sprite_width * 0.73;
        center_rect();
        play_again = false;
    }
}

int Opp::check_possible_colors() {
    int color = 1;
    for (int i = 0; i < deck.size(); ++i) {
        if (deck[i].pos.y < 5) {
            color = deck[i].pos.y;
            break;
        }
    }
    return color;
}

void Opp::sort_deck() {
    int n = deck.size();
    n = Clamp(n - 1, 0, 19999);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; j++) {
            if (deck[j].pos.x < deck[j + 1].pos.x) {
                std::swap(deck[j], deck[j + 1]);
            }
        }
    }
}

void Opp::play(Center &center) {
    if (possible_moves > 0) {
        if (normal_moves > 0) {
            if (center.random_y < 5) {
                for (int i = 0; i < deck.size(); ++i) {
                    if (deck[i].pos.y == center.random_y && deck[i].pos.y != 5) {
                        if (deck[i].pos.x == 10) {
                            dish_card(center, i);
                            play_again = true;
                            begin_one_timer = true;
                            return;
                        }
                        else if (deck[i].pos.x == 11) {
                            dish_card(center, i);
                            play_again = true;
                            return;
                        }
                        else if (deck[i].pos.x == 12) {
                            dish_card(center, i);
                            play_again = true;
                            return;
                        }
                        else {
                            dish_card(center, i);
                            play_again = false;
                            return;
                        }
                    }
                    if (deck[i].pos.x == center.random_x && deck[i].pos.y != 5) {
                        if (deck[i].pos.x < 9) {
                            dish_card(center, i);
                            play_again = false;
                            return;
                        }
                        else {
                            dish_card(center, i);
                            play_again = true;
                            return;
                        }
                        return;
                    }
                }
            }
            else {
                for (int i = 0; i < deck.size(); ++i) {
                    if (deck[i].pos.y == temp_x_pos && deck[i].pos.y != 5) {
                        if (deck[i].pos.x == 10) {
                            dish_card(center, i);
                            play_again = true;
                            begin_one_timer = true;
                            return;
                        }
                        else if (deck[i].pos.x == 11) {
                            dish_card(center, i);
                            play_again = true;
                            return;
                        }
                        else if (deck[i].pos.x == 12) {
                            dish_card(center, i);
                            play_again = true;
                            return;
                        }
                        else {
                            dish_card(center, i);
                            play_again = false;
                            return;
                        }
                        return;
                    }
                }
            }
        }
        else if (wild_card_moves > 0) {
            for (int i = 0; i < deck.size(); ++i) {
                if (deck[i].pos.y == 5) {
                    if (deck[i].pos.x == 5) {
                        dish_four_wild(center, i);
                        begin_four_timer = true;
                        play_again = true;
                        return;
                    }
                    else {
                        dish_wild(center, i);
                        play_again = false;
                        return;
                    }
                }
            }
        }
    }
    else {
        spawn();
    }
}

void Opp::update(Center &center) {
    possible_moves = 0;
    normal_moves = 0;
    wild_card_moves = 0;
    temp_x_pos = center.random_x;
    is_over = center.is_over;

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
                if (deck[i].pos.y == 5) {
                    wild_card_moves++;
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
                if (deck[i].pos.y == 5) {
                    wild_card_moves++;
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
    }
    if (begin_four_timer) {
        if (start_timer(0.4f)) {
            draw_four_wild = true;
            begin_four_timer = false;
        }
    }
    if (begin_one_timer) {
        if (start_timer(0.4f)) {
            draw_one = true;
            begin_one_timer = false;
        }
    }
    if (deck.size() == 0) {
        has_win = true;
        center.is_over = true;
    }
    sort_deck();
}

void Opp::draw() {
    DrawRectangleRec(rect, {0, 0, 0, 0});
    for (int i = 0; i < deck.size(); ++i) {
        texture_rect.x = Constants::sprite_offset_x + (Constants::sprite_width * 0);
        texture_rect.y = (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * 0),
        // texture_rect.x = Constants::sprite_offset_x + (Constants::sprite_width * deck[i].pos.x);
        // texture_rect.y = (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * deck[i].pos.y);
        deck[i].rect.x = Lerp(deck[i].rect.x, rect.x + ((Constants::sprite_width / 1.5) * i), 0.2);
        deck[i].rect.y = Lerp(deck[i].rect.y, rect.y - ((Constants::sprite_height / 6) * deck[i].y_offset), 0.2);
        DrawTexturePro(cards, texture_rect, deck[i].rect, {0, 0}, 0, WHITE);
    }
}
