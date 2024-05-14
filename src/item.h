#ifndef _item_h_
#define _item_h_

#define EMPTY 0
#define GRASS 1
#define SAND 2
#define STONE 3
#define BRICK 4
#define WOOD 5
#define DIRT 7
#define PLANK 8
#define SNOW 9
#define GLASS 10
#define STONE_BRICK 11
#define SMOOTH_STONE 12
#define CHEST 14
#define LEAVES 15
#define CLOUD 16
#define TALL_GRASS 17

extern const int items[];
extern const int item_count;
extern const int blocks[256][6];
extern const int plants[256];

int is_plant(int w);
int is_obstacle(int w);
int is_transparent(int w);
int is_destructable(int w);

#endif
