#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "raylib.h"

namespace Constants {
    inline const char *WINDOW_NAME = "Uno";
    inline constexpr int WINDOW_WIDTH = 600;
    inline constexpr int WINDOW_HEIGHT = 600;

    inline constexpr float sprite_width = 41.0f;
    inline constexpr float sprite_height = 61.0f;

    inline constexpr float sprite_offset_x = 10.0f;
    inline constexpr float sprite_offset_y = 71.0f;

    inline constexpr float border_offset = 20.0f;

    inline constexpr int initial_num_cards = 5;

    inline constexpr Color dark_slate_gray = {30, 34, 42, 255};
    inline constexpr Color charcoal = {44, 48, 46, 255};
    inline constexpr Color dark_felt_green = {26, 67, 37, 255};
    inline constexpr Color deep_felt_green = {15, 56, 30, 255};
    inline constexpr Color worm_wood_brown = {59, 35, 20, 255};
    inline constexpr Color deep_midnight_navy_1 = {11, 25, 44, 255};
    inline constexpr Color deep_midnight_navy_2 = {18, 27, 41, 255};
    inline constexpr Color dark_neutral_purple_1 = {35, 24, 52, 255};
    inline constexpr Color dark_neutral_purple_2 = {28, 19, 43, 255};
}

#endif
