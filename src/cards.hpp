#ifndef CARDS_HPP
#define CARDS_HPP

#include "raylib.h"
#include <string>
#include <vector>

struct Card {
    Vector2 pos;
    Rectangle rect;
    bool isHovering;
    float y_offset;
};

// struct Card {
//     Color color;
//     std::string name;
//     bool isHovering;
//     Vector2 pos;
//     Rectangle draw_rect;
//     Rectangle collision_rect;
//     Vector2 scale;
// };
//
// inline std::vector<Card> card_definition {
//     // --- RED (Row 0) ---
//     {RED, "0", false, {0, 0}},
//     {RED, "1", false, {1, 0}},
//     {RED, "2", false, {2, 0}},
//     {RED, "3", false, {3, 0}},
//     {RED, "4", false, {4, 0}},
//     {RED, "5", false, {5, 0}},
//     {RED, "6", false, {6, 0}},
//     {RED, "7", false, {7, 0}},
//     {RED, "8", false, {8, 0}},
//     {RED, "9", false, {9, 0}},
//     {RED, "Draw Two", false, {10, 0}},
//     {RED, "Reverse", false, {11, 0}},
//     {RED, "Skip", false, {12, 0}},
//
//     // --- GREEN (Row 1) ---
//     {GREEN, "0", false, {0, 1}},
//     {GREEN, "1", false, {1, 1}},
//     {GREEN, "2", false, {2, 1}},
//     {GREEN, "3", false, {3, 1}},
//     {GREEN, "4", false, {4, 1}},
//     {GREEN, "5", false, {5, 1}},
//     {GREEN, "6", false, {6, 1}},
//     {GREEN, "7", false, {7, 1}},
//     {GREEN, "8", false, {8, 1}},
//     {GREEN, "9", false, {9, 1}},
//     {GREEN, "Draw Two", false, {10, 1}},
//     {GREEN, "Reverse", false, {11, 1}},
//     {GREEN, "Skip", false, {12, 1}},
//
//     // --- YELLOW (Row 2) ---
//     {YELLOW, "0", false, {0, 2}},
//     {YELLOW, "1", false, {1, 2}},
//     {YELLOW, "2", false, {2, 2}},
//     {YELLOW, "3", false, {3, 2}},
//     {YELLOW, "4", false, {4, 2}},
//     {YELLOW, "5", false, {5, 2}},
//     {YELLOW, "6", false, {6, 2}},
//     {YELLOW, "7", false, {7, 2}},
//     {YELLOW, "8", false, {8, 2}},
//     {YELLOW, "9", false, {9, 2}},
//     {YELLOW, "Draw Two", false, {10, 2}},
//     {YELLOW, "Reverse", false, {11, 2}},
//     {YELLOW, "Skip", false, {12, 2}},
//
//     // --- BLUE (Row 3) ---
//     {BLUE, "0", false, {0, 3}},
//     {BLUE, "1", false, {1, 3}},
//     {BLUE, "2", false, {2, 3}},
//     {BLUE, "3", false, {3, 3}},
//     {BLUE, "4", false, {4, 3}},
//     {BLUE, "5", false, {5, 3}},
//     {BLUE, "6", false, {6, 3}},
//     {BLUE, "7", false, {7, 3}},
//     {BLUE, "8", false, {8, 3}},
//     {BLUE, "9", false, {9, 3}},
//     {BLUE, "Draw Two", false, {10, 3}},
//     {BLUE, "Reverse", false, {11, 3}},
//     {BLUE, "Skip", false, {12, 3}},
//
//     // --- SPECIAL / WILD CARDS (Row 4) ---
//     {BLACK, "Wild", false, {0, 4}},
//     {RED, "Wild", false, {1, 4}},
//     {GREEN, "Wild", false, {2, 4}},
//     {YELLOW, "Wild", false, {3, 4}},
//     {BLUE, "Wild", false, {4, 4}},
//     {RED, "Draw Four", false, {5, 4}},
//     {GREEN, "Draw Four", false, {6, 4}},
//     {YELLOW, "Draw Four", false, {7, 4}},
//     {BLUE, "Draw Four", false, {8, 4}},
//     {BLACK, "Draw Four", false, {9, 4}}
// };
//
#endif
