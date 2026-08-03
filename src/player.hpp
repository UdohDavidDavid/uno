#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "constants.hpp"
#include "raylib.h"
#include <vector>
#include "cards.hpp"
#include "center.hpp"
#include "opp.hpp"

class Player {
public:
    bool isHidden;
    int card_num;
    Rectangle rect;
    Rectangle draw_rect;
    Vector2 scale;


    int random_x;
    int random_y;

	Texture cards;
    Rectangle texture_rect;
    Vector2 current_sprite;

    Card card;
    std::vector<Card> deck;

    Rectangle collision_rect;

    int normal_moves;
    int possible_moves;
    int wild_card_moves;
    int four_wild_card_moves;

    bool is_turn;

    bool passed;

    int temp_x_pos;

    bool pass_play;

    bool draw_wild;

    int wild_color;

    bool pick_color;

    float color_picker_size;
    Rectangle red;
    Rectangle green;
    Rectangle yellow;
    Rectangle blue;

    Card current_wild_card;

    int color_pick;

    Sound draw_sound;
    Sound play_sound;

    Player();
    void draw();
    void update(Center &center, Opp &opponent);
    void center_rect(); // Center deck to the middle of screen
    void load_texture();
    void load_deck();
    void choose_random_card();
    void create_card();
    void add_card();
    void dish_deck(Center &center, int i, Opp &opponent);
    void dish_wild(Center &center, int i);
    void load_sounds();
};

#endif
