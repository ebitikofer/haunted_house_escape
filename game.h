#ifndef GAME_H
#define GAME_H

void set_objects();

void walls();
void roof();
void floor();
void character();
void hud();
void door();
void doorknob();
void tables();

void moon();
void werewolf();

void vaccuum();
void ghost();
void picture();
void light();
void bookcase();
void book();
void key();

void fire();
void agency();

void gun_pickup();
void gun();
void zombies();
void coffee();

// // ENVIRONMENT
vec3 wall_loc[NUM_OBJECTS] = { vec3(0.0, 0.0, 0.0) };

vec3 door_loc[NUM_DOORS] = { vec3(0.0, 0.0, 0.0) };

int door_rot[NUM_DOORS] = { 0 };

vec3 bookcase_loc[NUM_BOOKCASE] = { vec3(0.0, 0.0, 0.0) };

vec3 table_loc[NUM_TABLES] = { vec3(0.0, 0.0, 0.0) };

vec3 ghosts_loc[NUM_GHOSTS] = { vec3(0.0, 0.0, 0.0) };

vec3 zombies_loc[NUM_ZOMBIES] = { vec3(0.0, 0.0, 0.0) };

vec3 werewolves_loc[NUM_WEREWOLVES] = { vec3(0.0, 0.0, 0.0) };

vec3 agencies_loc[NUM_AGENCIES] = { vec3(0.0, 0.0, 0.0) };

vec3 inter_loc[NUM_INTERACTABLES] = { vec3(0.0, 0.0, 0.0) };

vec3 pickup_loc[NUM_PICKUPS] = { vec3(0.0, 0.0, 0.0) };

vec3 wall_size[NUM_OBJECTS] = { vec3(0.0, 0.0, 0.0) };

vec3 door_size[NUM_DOORS] = { vec3(0.0, 0.0, 0.0) };

vec3 bookcase_size[NUM_BOOKCASE] = { vec3(0.0, 0.0, 0.0) };

vec3 table_size[NUM_TABLES] = { vec3(0.0, 0.0, 0.0) };

vec3 ghosts_size[NUM_GHOSTS] = { vec3(0.0, 0.0, 0.0) };

vec3 zombies_size[NUM_ZOMBIES] = { vec3(0.0, 0.0, 0.0) };

vec3 werewolves_size[NUM_WEREWOLVES] = { vec3(0.0, 0.0, 0.0) };

vec3 agencies_size[NUM_AGENCIES] = { vec3(0.0, 0.0, 0.0) };

vec3 inter_size[NUM_INTERACTABLES] = { vec3(0.0, 0.0, 0.0) };

vec3 pickup_size[NUM_PICKUPS] = { vec3(0.0, 0.0, 0.0) };

#endif
