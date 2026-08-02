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

    Game();
    ~Game();
    void run();
    void process_keys();
    void draw_dots(Color color);
    void restart();
};

#endif
