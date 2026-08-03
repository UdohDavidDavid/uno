#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "player.hpp"
#include "center.hpp"
#include "opp.hpp"

class Game {
public:
	Texture cards;
    Player player1;
    Opp opponent;
    Center center;
    Vector2 scale;
    bool isMoving = false;
    Vector2 dest_pos;
    Rectangle collision_rect;

    Card card_pressed;

    Rectangle picker_rect;
    Rectangle picker_texture_rect;
    Vector2 picker_pos;

    Rectangle deck_rect;
    Rectangle deck_texture_rect;
    Vector2 deck_pos;

    Music w_sound;

    Texture background;

    float t;

    Color colors[5];

    Texture hand;

    Rectangle hand_rect;
    float hand_scale_x;
    float hand_scale_y;

    float last_card_timer;
    float last_card_time;
    bool say_uno;

    Shader vignette;

    Game();
    ~Game();
    void run();
    void process_keys();
    void draw_dots(Color color);
    void restart();
};

#endif
