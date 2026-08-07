#ifndef OPP_HPP
#define OPP_HPP

#include "raylib.h"
#include "cards.hpp"
#include <vector>
#include "center.hpp"

enum ORT {
    TP,
    LH,
    RH,
};

class Opp {
public:
    ORT orientation;

    bool is_turn;

    Texture cards;
    Rectangle texture_rect;
    Rectangle rect;

    int normal_moves;
    int possible_moves;
    int wild_card_moves;
    int four_wild_card_moves;

    int temp_x_pos;

    std::vector<Card> deck;

    Rectangle clone;

    int mov_x;
    int mov_y;

    Card card;
    int card_num;

    int random_x;
    int random_y;

    bool draw_four_wild;
    bool draw_wild;
    bool begin_four_timer;
    bool begin_one_timer;
    bool draw_one;

    bool is_drawing_card;

    bool skip_next;

    Card currently_moving_card;

    bool is_over;

    bool has_win;

    Sound draw_sound;
    Sound play_sound;

    float draw_pos_x;
    float draw_pos_y;

    Opp(ORT orientation);
    void draw() ;
    void update(Center &center);
    void load_texture() ;
    void load_sounds() ;
    void create_card() ;
    void choose_random_card() ;
    void center_rect() ;
    void load_deck() ;
    void play(Center &center);
    void dish_card(Center &center, int i);
    void dish_wild(Center &center, int i) ;
    void dish_four_wild(Center &center, int i);
    void add_card() ;
    void sort_deck();
    int check_possible_colors();
};

#endif
