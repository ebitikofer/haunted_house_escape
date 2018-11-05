#ifndef MODELS_H
#define MODELS_H

#include <Angel.h>

#define FLOOR_SIZE 100
#define NUM_TILES  50
#define TILE_SIZE  FLOOR_SIZE / NUM_TILES
#define WALL_HEIGHT 15

#define SKY_R 0.05
#define SKY_G 0.0
#define SKY_B 0.1

#define COLOR_SKY 1
//   vec3(0.8, 1.0, 1.0),

#define PLAYER_W 1.0
#define PLAYER_H 10.0
#define PLAYER_D 1.0

#define FLOOR_W TILE_SIZE
#define FLOOR_H 0.1
#define FLOOR_D TILE_SIZE
#define FLOOR_R 0.2
#define FLOOR_G 0.1
#define FLOOR_B 0.0

#define COLOR_FLOORS  4
//   vec3(0.6, 0.6, 0.6),

#define LON_WALL_W 0.5
#define LON_WALL_H WALL_HEIGHT
#define LON_WALL_D TILE_SIZE
#define LON_WALL_R 0.7
#define LON_WALL_G 0.6
#define LON_WALL_B 0.5

#define LAT_WALL_W TILE_SIZE
#define LAT_WALL_H WALL_HEIGHT
#define LAT_WALL_D 0.5
#define LAT_WALL_R 0.7
#define LAT_WALL_G 0.6
#define LAT_WALL_B 0.5

#define ROOF_W FLOOR_SIZE
#define ROOF_H 0.1
#define ROOF_D FLOOR_SIZE
#define ROOF_R 0.2
#define ROOF_G 0.1
#define ROOF_B 0.1

#define DOOR_W 5.0
#define DOOR_H 10.0
#define DOOR_D 0.5
#define DOOR_R 0.25
#define DOOR_G 0.15
#define DOOR_B 0.05

#define BULB_W 0.5
#define BULB_H 0.5
#define BULB_D 0.25
#define SHAFT_W 0.25
#define SHAFT_H 0.25
#define SHAFT_D 0.25
#define DOORKNOB_R 0.9
#define DOORKNOB_G 0.7
#define DOORKNOB_B 0.0

#define TOP_W 2.5
#define TOP_H 0.1
#define TOP_D 5.0
#define LEG_W 0.1
#define LEG_H 2.0
#define LEG_D 0.1
#define TABLE_R 0.5
#define TABLE_G 0.3
#define TABLE_B 0.1

#define BODYL_W 4.0
#define BODYL_H 4.0
#define BODYL_D 4.0
#define BODYS_W 3.5
#define BODYS_H 3.5
#define BODYS_D 3.5
#define HOSEL_W 1.0
#define HOSEL_H 6.0
#define HOSEL_D 1.0
#define HOSEM_W 1.0
#define HOSEM_H 2.0
#define HOSEM_D 1.0
#define HOSES_W 1.0
#define HOSES_H 2.0
#define HOSES_D 1.0
#define NOZZLE_W 3.0
#define NOZZLE_H 0.5
#define NOZZLE_D 1.5
#define HOSE_R 0.8
#define HOSE_G 0.8
#define HOSE_B 0.8
#define STRAP_W 1.0
#define STRAP_H 7.0
#define STRAP_D 1.0
#define STRAP_R 0.7
#define STRAP_G 0.5
#define STRAP_B 0.1
#define WHEEL_W 1.0
#define WHEEL_H 2.0
#define WHEEL_D 2.0
#define WHEEL_R 0.8
#define WHEEL_G 0.8
#define WHEEL_B 0.8
#define LIGHT_W 1.0
#define LIGHT_H 1.0
#define LIGHT_D 1.0
#define LIGHT_R 0.4
#define LIGHT_G 0.8
#define LIGHT_B 0.1
#define VACCUUM_R 0.8
#define VACCUUM_G 0.1
#define VACCUUM_B 0.1

#define GHOST_W 2.0
#define GHOST_H 2.0
#define GHOST_D 2.0
#define GHOST_R 0.9
#define GHOST_G 0.9
#define GHOST_B 1.0

#define FRAME_W 28.0
#define FRAME_H 20.0
#define FRAME_D 0.5
#define STRING_W 0.5
#define STRING_H 8.0
#define STRING_D 0.5
#define STRING_R 0.9
#define STRING_G 0.9
#define STRING_B 0.7
#define PICTURE_R 0.9
#define PICTURE_G 0.7
#define PICTURE_B 0.0

#define BOOKCASELZ_W 5.0
#define BOOKCASELZ_H 15.0
#define BOOKCASELZ_D 25.0
#define BOOKCASELX_W 25.0
#define BOOKCASELX_H 15.0
#define BOOKCASELX_D 5.0
#define BOOKCASESZ_W 5.0
#define BOOKCASESZ_H 15.0
#define BOOKCASESZ_D 10.0
#define BOOKCASESX_W 10.0
#define BOOKCASESX_H 15.0
#define BOOKCASESX_D 5.0
#define BOOKCASE_R 0.25
#define BOOKCASE_G 0.15
#define BOOKCASE_B 0.05

#define KEYL_W 1.0
#define KEYL_H 1.0
#define KEYL_D 3.0
#define KEYS_W 1.0
#define KEYS_H 1.0
#define KEYS_D 2.0
#define KEY_R 0.9
#define KEY_G 0.7
#define KEY_B 0.0

#define ZOMBIE_W 2.0
#define ZOMBIE_H 2.0
#define ZOMBIE_D 2.0
#define ZOMBIE_R 0.1
#define ZOMBIE_G 0.3
#define ZOMBIE_B 0.1

#define COFFEE_W 1.0
#define COFFEE_H 1.0
#define COFFEE_D 1.0
#define CUP_W 1.25
#define CUP_H 1.25
#define CUP_D 1.25
#define SAUCER_W 2.0
#define SAUCER_H 0.1
#define SAUCER_D 2.0
#define COFFEE_R 0.1
#define COFFEE_G 0.1
#define COFFEE_B 0.0
#define DISH_R 0.9
#define DISH_G 0.9
#define DISH_B 1.0

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

// #define TIP_B 0.01
// #define TIP_T 0.01
// #define TIP_H 0.5
// #define TIP_SL 16
// #define TIP_ST 10
// #define TIP_RE 0.5
// #define TIP_GR 0.5
// #define TIP_BL 0.5
//
// #define BODY_B 0.1
// #define BODY_T 0.1
// #define BODY_H 0.6
// #define BODY_SL 16
// #define BODY_ST 10
// #define BODY_RE 0.1
// #define BODY_GR 0.1
// #define BODY_BL 0.1

#define FEATHER_B 0.0
#define FEATHER_T 0.4
#define FEATHER_H 0.3
#define FEATHER_SL 16
#define FEATHER_ST 10
#define FEATHER_RE 0.0
#define FEATHER_GR 0.0
#define FEATHER_BL 0.0

#endif
