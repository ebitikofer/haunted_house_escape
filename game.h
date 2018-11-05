#ifndef GAME_H
#define GAME_H

void set_objects();

void walls();
void roof();
void floor();
void doors();
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

void gun();
void zombies();
void coffee();

// // ENVIRONMENT
vec3 wall_loc[NUM_OBJECTS] = { vec3(0.0, 0.0, 0.0) };

vec3 bookcase_loc[NUM_BOOKCASE] = { vec3(0.0, 0.0, 0.0) };

vec3 table_loc[NUM_TABLES] = { vec3(0.0, 0.0, 0.0) };

vec3 enemy_loc[NUM_ENEMIES] = { vec3(0.0, 0.0, 0.0) };

vec3 wall_size[NUM_OBJECTS] = { vec3(0.0, 0.0, 0.0) };

vec3 bookcase_size[NUM_BOOKCASE] = { vec3(0.0, 0.0, 0.0) };

vec3 table_size[NUM_TABLES] = { vec3(0.0, 0.0, 0.0) };

vec3 enemy_size[NUM_ENEMIES] = { vec3(0.0, 0.0, 0.0) };

#endif
