#ifndef HELPER_HPP
#define HELPER_HPP

#include "raylib.h"
#include "player.hpp"
#include "opp.hpp"

void translate(Vector2 &init_pos, Vector2 &dest, int steps);
void translateL(Vector2 &a, Vector2 &b, float t);
void translateEx(Vector2 &a, Vector2 &b, float t);
void translateSq(Vector2 &a, Vector2 &b, float t);
float f(float t);
int random_int(int start, int end);
int choose_wild();
int choose_col();
int choose_row();

void draw_four(Player &player);
void draw_four(Opp &opponent);
bool start_timer(float sec);
int get_wild_color();

#endif
