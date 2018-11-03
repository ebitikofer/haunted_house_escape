#ifndef MODELS_H
#define MODELS_H

#include <Angel.h>

#define FLOOR_SIZE 100
#define NUM_TILES  50
#define TILE_SIZE  FLOOR_SIZE / NUM_TILES

#define SKY_R 0.05
#define SKY_G 0.0
#define SKY_B 0.1

#define COLOR_SKY     1
//   vec3(0.8, 1.0, 1.0),

#define TREE_W 1.0
#define TREE_H 5.0
#define TREE_D 1.0
#define TREE_R 0.5
#define TREE_G 0.3
#define TREE_B 0.1

#define ROCK_W 2.0
#define ROCK_H 2.0
#define ROCK_D 2.0
#define ROCK_R 0.5
#define ROCK_G 0.4
#define ROCK_B 0.3

#define ANIMAL_W 1.0
#define ANIMAL_H 1.0
#define ANIMAL_D 1.0
#define ANIMAL_R 1.0
#define ANIMAL_G 1.0
#define ANIMAL_B 1.0
// vec3 animal_col[NUM_OF_ANIMALS] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };

#define BARREL_W 0.75
#define BARREL_H 1.0
#define BARREL_D 3.0
#define BARREL_R 0.6
#define BARREL_G 0.6
#define BARREL_B 0.6

#define COLOR_BARREL  5
//   vec3(0.9, 0.6, 0.5),

#define SIGHT_W 0.25
#define SIGHT_H 0.25
#define SIGHT_D 2.0
#define SIGHT_R 0.5
#define SIGHT_G 0.5
#define SIGHT_B 0.5

#define HANDLE_W 0.6
#define HANDLE_H 2.0
#define HANDLE_D 0.5
#define HANDLE_R 0.4
#define HANDLE_G 0.4
#define HANDLE_B 0.4

#define FLOOR_W TILE_SIZE
#define FLOOR_H 0.1
#define FLOOR_D TILE_SIZE
#define FLOOR_R 0.9
#define FLOOR_G 0.6
#define FLOOR_B 0.5

#define COLOR_FLOORS  4
//   vec3(0.6, 0.6, 0.6),

#define LON_WALL_W 0.5
#define LON_WALL_H 10.0
#define LON_WALL_D TILE_SIZE
#define LON_WALL_R 0.9
#define LON_WALL_G 0.6
#define LON_WALL_B 0.5

#define LAT_WALL_W TILE_SIZE
#define LAT_WALL_H 10.0
#define LAT_WALL_D 0.5
#define LAT_WALL_R 0.9
#define LAT_WALL_G 0.6
#define LAT_WALL_B 0.5

#define TIP_B 0.01
#define TIP_T 0.01
#define TIP_H 0.5
#define TIP_SL 16
#define TIP_ST 10
#define TIP_RE 0.5
#define TIP_GR 0.5
#define TIP_BL 0.5

#define BODY_B 0.1
#define BODY_T 0.1
#define BODY_H 0.6
#define BODY_SL 16
#define BODY_ST 10
#define BODY_RE 0.1
#define BODY_GR 0.1
#define BODY_BL 0.1

#define FEATHER_B 0.0
#define FEATHER_T 0.4
#define FEATHER_H 0.3
#define FEATHER_SL 16
#define FEATHER_ST 10
#define FEATHER_RE 0.0
#define FEATHER_GR 0.0
#define FEATHER_BL 0.0

#endif
