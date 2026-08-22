#include "center.hpp"
#include "constants.hpp"
#include "helper.hpp"
#include "raylib.h"
#include "raymath.h"

Center::Center()
    : tex_pos(0, 0), is_over(false), is_opponent_playing(false), draw_wild(0),
      index(0), increment_speed(1), direction(1), opp_num(1) {

  choose_random_card();
  tex_rect = {
      Constants::sprite_offset_x + (Constants::sprite_width * random_x),
      Constants::sprite_offset_y + (Constants::sprite_height * random_y),
      Constants::sprite_width,
      Constants::sprite_height,
  };
  // rect = {
  //     (Constants::WINDOW_WIDTH / 2.0f) - (Constants::sprite_width / 2.0f),
  //     (Constants::WINDOW_HEIGHT / 2.0f) - (Constants::sprite_height / 2.0f),
  //     Constants::sprite_width,
  //     Constants::sprite_height,
  // };
  rect = {
      (Constants::WINDOW_WIDTH / 2.0f),
      (Constants::WINDOW_HEIGHT / 2.0f) - Constants::sprite_height / 2,
      Constants::sprite_width,
      Constants::sprite_height,
  };
  // rect = {
  //     0,
  //     0,
  //     Constants::sprite_width,
  //     Constants::sprite_height,
  // };
}

void Center::draw() {
  tex_rect = {
      Constants::sprite_offset_x + (Constants::sprite_width * random_x),
      (Constants::sprite_offset_y - Constants::sprite_height) +
          (Constants::sprite_height * random_y),
      Constants::sprite_width,
      Constants::sprite_height,
  };
  DrawTexturePro(card, tex_rect, rect, {0, 0}, 0, WHITE);
}

void Center::load_texture() { card = LoadTexture("cards.png"); }

void Center::choose_random_card() {
  random_x = choose_col();
  random_y = choose_row();
  if (random_y == 5) {
    int trial = random_int(0, 1);
    if (trial) {
      draw_wild = 5;
      random_x = random_int(6, 9);
    } else {
      draw_wild = 0;
      random_x = random_int(1, 4);
    }
  }
}
