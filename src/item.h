#ifndef _item_h_
#define _item_h_

#define EMPTY 0
#define GRASS 1
#define SAND 2
#define STONE 3
#define BRICK 4
#define WOOD 5
#define CEMENT 6
#define DIRT 7
#define PLANK 8
#define SNOW 9
#define GLASS 10
#define COBBLE 11
#define LIGHT_STONE 12
#define DARK_STONE 13
#define CHEST 14
#define LEAVES 15
#define CLOUD 16
#define TALL_GRASS 17
#define BLOCK_INVALID 31

extern const int items[];
extern const int item_count;
extern const int blocks[256][6];
extern const int plants[256];

int is_plant(int w);
int is_obstacle(int w);
int is_transparent(int w);
int is_destructable(int w);

#endif
