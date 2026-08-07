#pragma once

#include "raylib.h"

class Center {
public:
    Texture card;
    Vector2 tex_pos;
    Rectangle tex_rect;
    Rectangle rect;
    int random_x;
    int random_y;
    int draw_wild;

    bool is_opponent_playing;

    bool is_over;

    int index;
    int increment_speed;
    int direction;
    int opp_num;

    bool special_effect_draw;
    bool special_effect_skip;
    bool special_effect_draw_four;

    Center();
    void draw();
    void load_texture();
    void choose_random_card();
};
