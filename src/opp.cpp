#include "opp.hpp"
#include "constants.hpp"
#include "helper.hpp"
#include "player.hpp"
#include "raylib.h"
#include "raymath.h"
#include "center.hpp"
#include <iostream>
#include <utility>

Opp::Opp(ORT ort) {
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
    skip_next = false;
    draw_one = false;
    has_win = false;
    this->orientation = ort;

    if (this->orientation == TP) {
        rect = {Constants::WINDOW_WIDTH / 2.0f,
            Constants::border_offset,
            (Constants::sprite_width * 0.73f) * Constants::initial_num_cards,
            Constants::sprite_height,
        };
        rect.x -= rect.width / 2;
    }
    else if (this->orientation == LH) {
        rect = {Constants::border_offset,
            Constants::WINDOW_HEIGHT / 2.0f,
            Constants::sprite_width,
            (Constants::sprite_height * 0.43f) * Constants::initial_num_cards,
        };
        rect.y -= rect.height / 2;
    }
    else if (this->orientation == RH) {
        rect = {(Constants::WINDOW_WIDTH - Constants::sprite_width) - Constants::border_offset,
            Constants::WINDOW_HEIGHT / 2.0f,
            Constants::sprite_width,
            (Constants::sprite_height * 0.43f) * Constants::initial_num_cards,
        };
        rect.y -= rect.height / 2;
    }

    texture_rect = {
        Constants::sprite_offset_x + (Constants::sprite_width * 0),
        (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * 0),
        Constants::sprite_width, Constants::sprite_height
    };
}

void Opp::load_texture() {
    cards = LoadTexture("cards.png");
}

void Opp::load_sounds() {
    draw_sound = LoadSound("cardsounds/cockatrice/draw.wav");
    play_sound = LoadSound("cardsounds/cockatrice/playcard.wav");
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
    if (this->orientation == TP) {
        rect.x = (float)Constants::WINDOW_WIDTH / 2;
        rect.x -= rect.width / 2;
    }
    else if (this->orientation == LH) {
        rect.y = Constants::WINDOW_HEIGHT / 2.0f;
        rect.y -= rect.height / 2.0f;
    }
    else if (this->orientation == RH) {
        rect.y = Constants::WINDOW_HEIGHT / 2.0f;
        rect.y -= rect.height / 2.0f;
    }
}

void Opp::load_deck() {
    for (int i = 0; i < Constants::initial_num_cards; ++i) {
        create_card();
        deck.push_back(card);
    }
    // rect = {Constants::WINDOW_WIDTH / 2.0f,
    //     Constants::border_offset,
    //     (Constants::sprite_width * 0.73f) * Constants::initial_num_cards,
    //     Constants::sprite_height,
    // };
    // rect.x -= rect.width / 2;
    center_rect();
}


void Opp::dish_wild(Center &center, int i) {
    PlaySound(play_sound);
    currently_moving_card = deck[i];
    mov_x = currently_moving_card.rect.x;
    mov_y = currently_moving_card.rect.y;
    is_drawing_card = true;
    if (orientation == TP) {
        rect.width -= Constants::sprite_width * 0.73;
    }
    else if (orientation == LH) {
        rect.height -= Constants::sprite_height * 0.43;
    }
    else if (orientation == RH) {
        rect.height -= Constants::sprite_height * 0.43;
    }
    center_rect();
    deck.erase(deck.begin() + i);
}

void Opp::dish_four_wild(Center &center, int i) {
    PlaySound(play_sound);
    currently_moving_card = deck[i];
    mov_x = currently_moving_card.rect.x;
    mov_y = currently_moving_card.rect.y;
    is_drawing_card = true;
    if (orientation == TP) {
        rect.width -= Constants::sprite_width * 0.73;
    }
    else if (orientation == LH) {
        rect.height -= Constants::sprite_height * 0.43;
    }
    else if (orientation == RH) {
        rect.height -= Constants::sprite_height * 0.43;
    }
    center_rect();
    deck.erase(deck.begin() + i);
}

void Opp::dish_card(Center &center, int i) {
    PlaySound(play_sound);
    currently_moving_card = deck[i];
    mov_x = currently_moving_card.rect.x;
    mov_y = currently_moving_card.rect.y;
    is_drawing_card = true;
    if (orientation == TP) {
        rect.width -= Constants::sprite_width * 0.73;
    }
    else if (orientation == LH) {
        rect.height -= Constants::sprite_height * 0.43;
    }
    else if (orientation == RH) {
        rect.height -= Constants::sprite_height * 0.43;
    }
    center_rect();
    deck.erase(deck.begin() + i);
}

void Opp::add_card() {
    if (!is_over) {
        PlaySound(draw_sound);
        create_card();
        deck.push_back(card);
        if (orientation == TP) {
            rect.width += Constants::sprite_width * 0.73;
        }
        if (orientation == LH) {
            rect.height += Constants::sprite_height * 0.43;
        }
        if (orientation == RH) {
            rect.height += Constants::sprite_height * 0.43;
        }
        center_rect();
        skip_next = false;
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
        // if (normal_moves > 0) {
            if (center.random_y < 5) {
                for (int i = 0; i < deck.size(); ++i) {
                    if (deck[i].pos.y == center.random_y || deck[i].pos.x == center.random_x && deck[i].pos.y != 5) {
                        if (deck[i].pos.x == 10) {
                            dish_card(center, i);
                            // skip_next = true;
                            // begin_one_timer = true;
                            // center.special_effect_draw = true;
                            return;
                        }
                        else if (deck[i].pos.x == 11) {
                            dish_card(center, i);
                            center.direction *= -1;
                            // skip_next = true;
                            return;
                        }
                        else if (deck[i].pos.x == 12) {
                            dish_card(center, i);
                            // skip_next = true;
                            // center.special_effect_skip = true;
                            return;
                        }
                        else {
                            dish_card(center, i);
                            // skip_next = false;
                            return;
                        }
                    }
                    else if (deck[i].pos.y == 5 && deck[i].pos.x == 0 && wild_card_moves > 0) {
                        dish_wild(center, i);
                        // skip_next = false;
                        return;
                    }
                    else if (deck[i].pos.y == 5 && deck[i].pos.x == 5 && normal_moves == 0) {
                        dish_four_wild(center, i);
                        // begin_four_timer = true;
                        // skip_next = true;
                        return;
                    }
                }
            }
            else {
                for (int i = 0; i < deck.size(); ++i) {
                    if (deck[i].pos.y == temp_x_pos && deck[i].pos.y != 5) {
                        if (deck[i].pos.x == 10) {
                            dish_card(center, i);
                            // skip_next = true;
                            // begin_one_timer = true;
                            // center.special_effect_draw = true;
                            return;
                        }
                        else if (deck[i].pos.x == 11) {
                            dish_card(center, i);
                            center.direction *= -1;
                            // skip_next = true;
                            return;
                        }
                        else if (deck[i].pos.x == 12) {
                            dish_card(center, i);
                            // skip_next = true;
                            // center.special_effect_skip = true;
                            return;
                        }
                        else {
                            dish_card(center, i);
                            // skip_next = false;
                            return;
                        }
                        return;
                    }
                    else if (deck[i].pos.y == 5 && deck[i].pos.x == 0 && wild_card_moves > 0) {
                        dish_wild(center, i);
                        // skip_next = false;
                        return;
                    }
                    else if (deck[i].pos.y == 5 && deck[i].pos.x == 5 && normal_moves == 0) {
                        dish_four_wild(center, i);
                        // begin_four_timer = true;
                        // skip_next = true;
                        return;
                    }
                }
            }
    }
    else {
        add_card();
    }
}

void Opp::update(Center &center) {
    possible_moves = 0;
    normal_moves = 0;
    four_wild_card_moves = 0;
    wild_card_moves = 0;
    temp_x_pos = center.random_x;
    is_over = center.is_over;
    center.is_opponent_playing = skip_next;

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
                    wild_card_moves++;
                }
                if (deck[i].pos.y == 5 && deck[i].pos.y == 5) {
                    four_wild_card_moves++;
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
                    wild_card_moves++;
                }
                if (deck[i].pos.y == 5 && deck[i].pos.y == 5) {
                    four_wild_card_moves++;
                }
                if (deck[i].pos.y == temp_x_pos && deck[i].pos.y != 5) {
                    normal_moves++;
                }
            };
        }
        if (normal_moves == 0) {
            possible_moves = wild_card_moves + four_wild_card_moves;
        }
        else {
            possible_moves = normal_moves;
        }
    }

    if (center.special_effect_draw == true) {
        // if (start_timer(2.0f)) {
            add_card();
            add_card();
            center.special_effect_draw = false;
            center.index += 1 * center.direction;
        // }
    }
    if (center.special_effect_draw_four == true) {
        // if (start_timer(2.0f)) {
            add_card();
            add_card();
            add_card();
            add_card();
            center.special_effect_draw_four = false;
            center.index += 1 * center.direction;
        // }
    }
    else if (center.special_effect_skip == true) {
        // if (start_timer(2.0f)) {
        //     center.index += 1 * center.direction;
        //     center.special_effect_skip = false;
        // }
        center.special_effect_skip = false;
        center.index += 1 * center.direction;
    }
    else if (possible_moves > 0) {
        if (start_timer(2.0f)) {
            play(center);
            // if (!is_drawing_card) {
                // center.index++;
            // }
        }
    }
    else {
        if (start_timer(2.0f)) {
            add_card();
            center.index += 1 * center.direction;
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

    if (draw_one) {
        // Players[(center.index++) % Players.size()].add_card();
        // Players[(center.index++) % Players.size()].add_card();
        draw_one = false;
    }

    if (draw_four_wild) {
        // draw_four(Players[center.index]);
        // draw_four(Players[(center.index++) % Players.size()]);
        draw_four_wild = false;
    }

    if (deck.size() == 0) {
        has_win = true;
        center.is_over = true;
    }

    // if (skip_next) {
    //     static float timer = 0.0f;
    //     static float last_time = 0.0f;
    //     if (timer - last_time > 1.0f) {
    //         center.index += 2;
    //         timer = 0.0f;
    //         last_time = timer;
    //     }
    //     else {
    //         timer += 1 * GetFrameTime();
    //     }
    // }
    // else {
    //     static float timer = 0.0f;
    //     static float last_time = 0.0f;
    //     if (timer - last_time > 1.0f) {
    //         center.index++;
    //         timer = 0.0f;
    //         last_time = timer;
    //     }
    //     else {
    //         timer += 1 * GetFrameTime();
    //     }
    // }

    if (is_drawing_card) {
        clone = {currently_moving_card.rect.x, currently_moving_card.rect.y, Constants::sprite_width, Constants::sprite_height};
            mov_x = Lerp(mov_x, center.rect.x, 0.2f);
            mov_y = Lerp(mov_y, center.rect.y, 0.2f);
            if (std::abs(center.rect.x - mov_x) < Constants::sprite_width / 2.0f && std::abs(center.rect.y - mov_y) < Constants::sprite_height / 2.0f) {
                if (currently_moving_card.pos.y == 5) {
                    center.random_x = currently_moving_card.pos.x + check_possible_colors();
                    center.random_y = currently_moving_card.pos.y;
                    if (currently_moving_card.pos.x == 5) {
                        center.special_effect_draw_four = true;
                    }
                }
                else {
                    center.random_x = currently_moving_card.pos.x;
                    center.random_y = currently_moving_card.pos.y;
                    if (currently_moving_card.pos.x == 10) {
                        center.special_effect_draw = true;
                    }
                    if (currently_moving_card.pos.x == 12) {
                        center.special_effect_skip = true;
                    }
                }
                center.index += 1 * center.direction;
                is_drawing_card = false;
            }
            clone.x = mov_x;
            clone.y = mov_y;
            texture_rect.x = Constants::sprite_offset_x + (Constants::sprite_width * currently_moving_card.pos.x);
            texture_rect.y = (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * currently_moving_card.pos.y);
            DrawTexturePro(cards, texture_rect, clone, {0, 0}, 0, WHITE);
    }

    // if (possible_moves) {
    //     if (start_timer(2.0f)) {
    //         play(center);
    //     }
    // }
    // else {
    //     add_card();
    // }
    sort_deck();
}

void Opp::draw() {
    DrawRectangleRec(rect, {0, 0, 0, 0});
    for (int i = 0; i < deck.size(); ++i) {
        texture_rect.x = Constants::sprite_offset_x + (Constants::sprite_width * 0);
        texture_rect.y = (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * 0);
        // texture_rect.x = Constants::sprite_offset_x + (Constants::sprite_width * deck[i].pos.x);
        // texture_rect.y = (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * deck[i].pos.y);
        if (this->orientation == TP) {
            deck[i].rect.x = Lerp(deck[i].rect.x, rect.x + ((Constants::sprite_width / 1.5) * i), 0.2);
            deck[i].rect.y = Lerp(deck[i].rect.y, rect.y, 0.2);
        }
        else if (this->orientation == LH) {
            deck[i].rect.x = Lerp(deck[i].rect.x, rect.x , 0.2);
            deck[i].rect.y = Lerp(deck[i].rect.y, rect.y + ((Constants::sprite_height * 0.3) * i), 0.2);
        }
        else if (this->orientation == RH) {
            deck[i].rect.x = Lerp(deck[i].rect.x, rect.x , 0.2);
            deck[i].rect.y = Lerp(deck[i].rect.y, rect.y + ((Constants::sprite_height * 0.3) * i), 0.2);
        }
        DrawTexturePro(cards, texture_rect, deck[i].rect, {0, 0}, 0, WHITE);
    }
}
