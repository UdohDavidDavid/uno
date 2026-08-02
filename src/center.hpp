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

    bool is_over;

    Center();
    void draw();
    void load_texture();
    void choose_random_card();
};
