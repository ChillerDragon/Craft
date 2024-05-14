#include "item.h"
#include "util.h"

const int items[] = {
    // items the user can build
    GRASS, SAND,        STONE,        BRICK, WOOD,   DIRT,      PLANK,
    GLASS, STONE_BRICK, SMOOTH_STONE, CHEST, LEAVES, TALL_GRASS};

const int item_count = sizeof(items) / sizeof(int);

const int blocks[256][6] = {
    // w => (left, right, top, bottom, front, back) tiles
    {0, 0, 0, 0, 0, 0},       // 0 - empty
    {2, 2, 18, 3, 2, 2},      // 1 - grass
    {12, 12, 12, 12, 12, 12}, // 2 - sand
    {1, 1, 1, 1, 1, 1},       // 3 - stone
    {3, 3, 3, 3, 3, 3},       // 4 - brick
    {36, 36, 52, 20, 36, 36}, // 5 - wood
    {31, 31, 31, 31, 31, 31}, // 6
    {3, 3, 3, 3, 3, 3},       // 7 - dirt
    {5, 5, 5, 5, 5, 5},       // 8 - plank
    {24, 24, 40, 8, 24, 24},  // 9 - snow
    {9, 9, 9, 9, 9, 9},       // 10 - glass
    {10, 10, 10, 10, 10, 10}, // 11 - stone brick
    {11, 11, 11, 11, 11, 11}, // 12 - smooth stone
    {31, 31, 31, 31, 31, 31}, // 13
    {13, 13, 13, 13, 13, 13}, // 14 - chest
    {14, 14, 14, 14, 14, 14}, // 15 - leaves
    {15, 15, 15, 15, 15, 15}, // 16 - cloud
    {0, 0, 0, 0, 0, 0},       // 17 * tall grass is handled in plants
    {0, 0, 0, 0, 0, 0},       // 18
    {0, 0, 0, 0, 0, 0},       // 19
    {0, 0, 0, 0, 0, 0},       // 20
    {0, 0, 0, 0, 0, 0},       // 21
    {0, 0, 0, 0, 0, 0},       // 22
    {0, 0, 0, 0, 0, 0},       // 23
    {0, 0, 0, 0, 0, 0},       // 24
    {0, 0, 0, 0, 0, 0},       // 25
    {0, 0, 0, 0, 0, 0},       // 26
    {0, 0, 0, 0, 0, 0},       // 27
    {0, 0, 0, 0, 0, 0},       // 28
    {0, 0, 0, 0, 0, 0},       // 29
    {0, 0, 0, 0, 0, 0},       // 30
    {0, 0, 0, 0, 0, 0},       // 31
    {0, 0, 0, 0, 0, 0},       // 32
    {0, 0, 0, 0, 0, 0},       // 33
    {0, 0, 0, 0, 0, 0},       // 34
    {0, 0, 0, 0, 0, 0},       // 35
    {0, 0, 0, 0, 0, 0},       // 36
    {0, 0, 0, 0, 0, 0},       // 37
    {0, 0, 0, 0, 0, 0},       // 38
    {0, 0, 0, 0, 0, 0},       // 39
    {0, 0, 0, 0, 0, 0},       // 40
    {0, 0, 0, 0, 0, 0},       // 41
    {0, 0, 0, 0, 0, 0},       // 42
    {0, 0, 0, 0, 0, 0},       // 43
    {0, 0, 0, 0, 0, 0},       // 44
    {0, 0, 0, 0, 0, 0},       // 45
    {0, 0, 0, 0, 0, 0},       // 46
    {0, 0, 0, 0, 0, 0},       // 47
    {0, 0, 0, 0, 0, 0},       // 48
    {0, 0, 0, 0, 0, 0},       // 49
    {0, 0, 0, 0, 0, 0},       // 50
    {0, 0, 0, 0, 0, 0},       // 51
    {0, 0, 0, 0, 0, 0},       // 52
    {0, 0, 0, 0, 0, 0},       // 53
    {0, 0, 0, 0, 0, 0},       // 54
    {0, 0, 0, 0, 0, 0},       // 55
    {0, 0, 0, 0, 0, 0},       // 56
    {0, 0, 0, 0, 0, 0},       // 57
    {0, 0, 0, 0, 0, 0},       // 58
    {0, 0, 0, 0, 0, 0},       // 59
    {0, 0, 0, 0, 0, 0},       // 60
    {0, 0, 0, 0, 0, 0},       // 61
    {0, 0, 0, 0, 0, 0},       // 62
    {0, 0, 0, 0, 0, 0},       // 63
};

const int plants[256] = {
    // w => tile
    0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0 - 16
    48,                                                 // 17 - tall grass
};

int is_plant(int w) {
  switch (w) {
  case TALL_GRASS:
    return 1;
  default:
    return 0;
  }
}

int is_obstacle(int w) {
  w = ABS(w);
  if (is_plant(w)) {
    return 0;
  }
  switch (w) {
  case EMPTY:
  case CLOUD:
    return 0;
  default:
    return 1;
  }
}

int is_transparent(int w) {
  if (w == EMPTY) {
    return 1;
  }
  w = ABS(w);
  if (is_plant(w)) {
    return 1;
  }
  switch (w) {
  case EMPTY:
  case GLASS:
  case LEAVES:
    return 1;
  default:
    return 0;
  }
}

int is_destructable(int w) {
  switch (w) {
  case EMPTY:
  case CLOUD:
    return 0;
  default:
    return 1;
  }
}
