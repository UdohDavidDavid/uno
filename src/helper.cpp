#include "helper.hpp"
#include "constants.hpp"
#include "raylib.h"
#include <cmath>
#include <iostream>
#include <random>
#include "player.hpp"

void translate(Vector2 &init_pos, Vector2 &dest, int steps) {
    Vector2 dist = {dest.x - init_pos.x, dest.y - init_pos.y};
    Vector2 step = {dist.x / steps, dist.y / steps};
    init_pos.x += step.x;
    init_pos.y += step.y;
}


void translateL(Vector2 &a, Vector2 &b, float t) {
    a.x = a.x + t * (b.x - a.x);
    a.y = a.y + t * (b.y - a.y);
}

void translateEx(Vector2 &a, Vector2 &b, float t) {
    static float s_t = std::pow(t, 3);
    s_t = std::pow(t, 3);
    a.x = a.x + s_t * (b.x - a.x);
    a.y = a.y + s_t * (b.y - a.y);
}

void translateSq(Vector2 &a, Vector2 &b, float t) {
    static float s_t = t * 2;
    a.x = a.x + s_t * (b.x - a.x);
    a.y = a.y + s_t * (b.y - a.y);
    s_t *= 2;
}

float f(float t) {
    return t * t;
}

int random_int(int start, int end) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(start, end);
    return dist6(rng);
}

int choose_wild() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);
    return dist6(rng);
}

int choose_col() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 12);
    return dist6(rng);
}

int choose_row() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5);
    return dist6(rng);
}

void draw_four(Player &player) {
    for (int i = 0; i < 4; i++) {
        player.add_card();
    }
}

void draw_four(Opp &opponent) {
    for (int i = 0; i < 4; i++) {
        opponent.add_card();
    }
}

bool start_timer(float sec) {
    static float timer = 0.0f;
    static float last_time = 0.0f;
    if (timer - last_time > sec) {
        timer = 0.0f;
        last_time = timer;
        return true;
    }
    else {
        timer += 1 * GetFrameTime();
        return false;
    }
}

int get_wild_color() {
    float size = 67.0f;
    int ret = 0;
    Rectangle red = {(Constants::WINDOW_WIDTH / 2.0f) - size, (Constants::WINDOW_HEIGHT / 2.0f) - (size / 2.0f), size, size};
    Rectangle green = {(Constants::WINDOW_WIDTH / 2.0f) - size, (Constants::WINDOW_HEIGHT / 2.0f) - size, size, size};
    Rectangle yellow = {(Constants::WINDOW_WIDTH / 2.0f) - size, (Constants::WINDOW_HEIGHT / 2.0f) - size, size, size};
    Rectangle blue = {(Constants::WINDOW_WIDTH / 2.0f) - size, (Constants::WINDOW_HEIGHT / 2.0f) - size, size, size};
    return ret;
}
