#include "game.hpp"
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "constants.hpp"
#include "player.hpp"
#include "rlgl.h"
#include "center.hpp"
#include "opp.hpp"
#include "helper.hpp"
#include <cmath>
#include <iostream>

Game::Game() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Hello Raylib");
    InitAudioDevice();

    SearchAndSetResourceDir("resources");
    cards = LoadTexture("cards.png");
    // background = LoadTexture("uno_cards_background.webp");

    player1.load_texture();
    player1.load_deck();
    player1.load_sounds();

    opponent.load_texture();
    opponent.load_deck();
    opponent.load_sounds();

    center.load_texture();

    picker_pos = {((float)Constants::WINDOW_WIDTH / 2) - (Constants::sprite_width / 2.0f), ((float)Constants::WINDOW_HEIGHT / 2)};
    scale = {1, 1};
    picker_rect = {picker_pos.x, picker_pos.y, Constants::sprite_width * scale.x, Constants::sprite_height * scale.y};

    picker_texture_rect = {
        Constants::sprite_offset_x + (Constants::sprite_width * 0),
        (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * 0),
        Constants::sprite_width, Constants::sprite_height};

    collision_rect = {picker_rect.x - (picker_rect.width / 2), picker_rect.y - (picker_rect.height / 2), picker_rect.width, picker_rect.height};

    w_sound = LoadMusicStream("country.mp3");
    w_sound.looping = true;
    PlayMusicStream(w_sound);
    SetMusicVolume(w_sound, 0.4f);
}

Game::~Game() {
    CloseAudioDevice();
    CloseWindow();
}

void Game::run() {
	while (!WindowShouldClose()) {
        UpdateMusicStream(w_sound);
        // PlayMusicStream(w_sound);
		BeginDrawing();
            process_keys();

            ClearBackground({10, 10, 10, 255});

            draw_dots({67, 67, 67, 255});

            // DrawTexturePro(background, {0, 0, 900, 766}, {0, 0, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}, {0, 0}, 0, WHITE);

            center.draw();

            player1.draw();
            if (!center.is_over) player1.update(center, opponent);

            opponent.draw();
            if (!center.is_over) opponent.update(center);

            if (center.is_over && IsKeyPressed(KEY_G)) {
                restart();
            }

            if (opponent.is_drawing_card) {
                opponent.clone = {opponent.currently_moving_card.rect.x, opponent.currently_moving_card.rect.y, Constants::sprite_width, Constants::sprite_height};
                    opponent.mov_x = Lerp(opponent.mov_x, center.rect.x, 0.2f);
                    opponent.mov_y = Lerp(opponent.mov_y, center.rect.y, 0.2f);
                    if (std::abs(center.rect.x - opponent.mov_x) < Constants::sprite_width / 2.0f && std::abs(center.rect.y - opponent.mov_y) < Constants::sprite_height / 2.0f) {
                        if (opponent.currently_moving_card.pos.y == 5) {
                            center.random_x = opponent.currently_moving_card.pos.x + opponent.check_possible_colors();
                            center.random_y = opponent.currently_moving_card.pos.y;
                        }
                        else {
                            center.random_x = opponent.currently_moving_card.pos.x;
                            center.random_y = opponent.currently_moving_card.pos.y;
                        }
                        opponent.is_drawing_card = false;
                    }
                    opponent.clone.x = opponent.mov_x;
                    opponent.clone.y = opponent.mov_y;
                    opponent.texture_rect.x = Constants::sprite_offset_x + (Constants::sprite_width * opponent.currently_moving_card.pos.x);
                    opponent.texture_rect.y = (Constants::sprite_offset_y - Constants::sprite_height) + (Constants::sprite_height * opponent.currently_moving_card.pos.y);
                    DrawTexturePro(cards, opponent.texture_rect, opponent.clone, {0, 0}, 0, WHITE);
            }


            if (opponent.draw_one) {
                player1.add_card();
                player1.add_card();
                opponent.draw_one = false;
            }
            if (opponent.draw_four_wild) {
                draw_four(player1);
                opponent.draw_four_wild = false;
            }
            if (player1.draw_wild) {
                if (player1.pick_color == false) {
                    draw_four(opponent);
                    player1.draw_wild = false;
                }
            }
            if (opponent.play_again) {
                static float timer = 0.0f;
                static float last_time = 0.0f;
                if (timer - last_time > 1.0f) {
                    opponent.play(center);
                    timer = 0.0f;
                    last_time = timer;
                }
                else {
                    timer += 1 * GetFrameTime();
                }
            }


            collision_rect = {picker_rect.x - (picker_rect.width / 2), picker_rect.y - (picker_rect.height / 2), picker_rect.width, picker_rect.height};
            if (CheckCollisionPointRec(GetMousePosition(), {picker_rect.x - (picker_rect.width / 2), picker_rect.y - (picker_rect.height / 2), picker_rect.width, picker_rect.height})) {
                scale.x = Lerp(scale.x, 1.2f, 0.1f);
                scale.y = Lerp(scale.y, 1.2f, 0.1f);
            }
            else {
                scale.x = Lerp(scale.x, 1.0f, 0.1);
                scale.y = Lerp(scale.y, 1.0f, 0.1);
            }

            picker_rect = {picker_pos.x, picker_pos.y, Constants::sprite_width * scale.x, Constants::sprite_height * scale.y};
            DrawTexturePro(cards, picker_texture_rect, picker_rect, {picker_rect.width / 2, picker_rect.height / 2}, 0, WHITE);

            if (player1.pick_color) {
                DrawRectangleRec(player1.red, RED);
                DrawRectangleLinesEx(player1.red, 2.0f, WHITE);
                DrawRectangleRec(player1.green, GREEN);
                DrawRectangleLinesEx(player1.green, 2.0f, WHITE);
                DrawRectangleRec(player1.yellow, YELLOW);
                DrawRectangleLinesEx(player1.yellow, 2.0f, WHITE);
                DrawRectangleRec(player1.blue, BLUE);
                DrawRectangleLinesEx(player1.blue, 2.0f, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(GetMousePosition(), player1.red)) {
                        player1.color_pick = 1;
                        player1.pick_color = false;
                    }
                    else if (CheckCollisionPointRec(GetMousePosition(), player1.green)) {
                        player1.color_pick = 2;
                        player1.pick_color = false;
                    }
                    else if (CheckCollisionPointRec(GetMousePosition(), player1.yellow)) {
                        player1.color_pick = 3;
                        player1.pick_color = false;
                    }
                    else if (CheckCollisionPointRec(GetMousePosition(), player1.blue)) {
                        player1.color_pick = 4;
                        player1.pick_color = false;
                    }
                    center.random_x = player1.current_wild_card.pos.x + player1.color_pick;
                }
            }

            // if (opponent.has_win) {
            //     DrawText("Player 2 win", int posX, int posY, int fontSize, Color color)
            // }
		
		EndDrawing();
	}
}

void Game::restart() {
    player1.deck.clear();
    player1.load_deck();
    opponent.deck.clear();
    opponent.load_deck();
    center.random_x = choose_col();
    center.random_y = choose_row();
    center.is_over = false;
}

void Game::draw_dots(Color color) {
    static int offset = 10;
    for (int i = 1; i < Constants::WINDOW_WIDTH / offset; ++i) {
        for (int j = 1; j < Constants::WINDOW_HEIGHT / offset; ++j) {
            DrawPixel(i * offset, j * offset, color);
        }
    }
}

void Game::process_keys() {
    if(IsKeyPressed(KEY_SPACE)) {
        player1.add_card();
    }
    if(IsKeyPressed(KEY_BACKSPACE)) {
        if (player1.card_num > 1) {
            player1.rect.width -= Constants::sprite_width / 1.5f;
            player1.center_rect();
            player1.card_num--;
            player1.deck.pop_back();
        }
    }
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        dest_pos = GetMousePosition();
        collision_rect = {picker_rect.x - (picker_rect.width / 2), picker_rect.y - (picker_rect.height / 2), picker_rect.width, picker_rect.height};
        if (CheckCollisionPointRec(GetMousePosition(), collision_rect)) {
            player1.add_card();
            player1.pass_play = true;
        }
    }
    if (IsKeyPressed(KEY_ENTER)) {
        opponent.play(center);
    }
    if (IsKeyPressed(KEY_V)) {
        opponent.spawn();
    }
}
