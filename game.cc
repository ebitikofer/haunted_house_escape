//***************
// Eric Bitikofer
// 10/14/18
// 3D game made in OpenGL
//

#include <Angel.h>
#include "engine.h"
#include "instance.h"
#include "game.h"

cardinal door_dir[NUM_DOORS];

// display function, update everything for display
void display(void) {

  // int i = 0, j = 0;

  if (!solid_part) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
              else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  // if (perspective) radius = 6.0;
              // else radius = 3.0;

  glutSetWindowTitle(title_bar.c_str());

  point4  eye(mvx + radius * cos(theta * M_PI/180) * cos(phi * M_PI/180),
              radius * sin(phi * M_PI/180),
              mvz + radius * sin(theta * M_PI/180) * cos(phi * M_PI/180),
              1.0);
  // point4  gun(mvx + radius * cos(theta * M_PI/180) * cos(phi * M_PI/180),
  //             radius * sin(phi * M_PI/180),
  //             mvz + radius * sin(theta * M_PI/180) * cos(phi * M_PI/180),
  //             1.0);
  point4  at(mvx, 0.0, mvz, 1.0);
  vec4    up(0.0, 1.0, 0.0, 0.0);

  glClearColor(SKY_R, SKY_G, SKY_B, 0.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  cv = LookAt(eye, at, up);
  // pv = LookAt(gun, at, up) * RotateY(180);
  // mv = RotateZ(move_angle);
  p = Perspective(fovy, aspect, zNear, zFar);

  glUniformMatrix4fv(camera_view, 1, GL_TRUE, cv);
  // glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
  glUniformMatrix4fv(projection, 1, GL_TRUE, p);

  // PLAYER
  // object(pv, model_view, 2.0, 0.0, -5.0, BARREL_W, BARREL_H, BARREL_D, BARREL_R, BARREL_G, BARREL_B, 0, 0, 0, 0, 0, 0);
  // object(pv, model_view, 1.6, -0.5, -5.75, SIGHT_W, SIGHT_H, SIGHT_D, SIGHT_R, SIGHT_G, SIGHT_B, 0, 0, 0, 0, 0, 0);
  // object(pv, model_view, 2.1, -1.1, -4.0, HANDLE_W, HANDLE_H, HANDLE_D, HANDLE_R, HANDLE_G, HANDLE_B, 0, 0, 0, 0, 0, 0);

  // // DART
  // object(mv, model_view, 2.0, 0.0, -2.8, TIP_B, TIP_H, TIP_T, 0, 0, 0, TIP_SL, TIP_ST, 1);
  // object(mv, model_view, 2.0, 0.0, -2.4, BODY_B, BODY_H, BODY_T, 0, 0, 0, BODY_SL, BODY_ST, 1);
  // object(mv, model_view, 2.0, 0.0, -2.3, FEATHER_B, FEATHER_H, FEATHER_T, 0, 0, 0, FEATHER_SL, FEATHER_ST, 1);

  set_objects(); // Set objects for render

  // Environment
  floor();
  walls();
  roof();
  doors();
  moon();
  bookcase();
  tables();

  // Pickups
  if (!get_sweeper) vaccuum();
  if (!get_key) key();
  if (!get_gun) gun();
  if (!get_coffee) coffee();

  // Props
  doorknob();
  picture();
  light();
  book();
  fire();

  // Enemies
  // werewolf();
  ghost();
  agency();
  zombies();

  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, wall_loc, wall_size, collide, NUM_OBJECTS);
  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, bookcase_loc, bookcase_size, collide, NUM_BOOKCASE);
  // collision(&enemy_loc[0].x, 0.0, &enemy_loc[0].z, GHOST_W, GHOST_H, GHOST_D, wall_loc, wall_size, collide, NUM_OBJECTS);
  // collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, table_loc, table_size, collide, NUM_TABLES);
  // collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, door_loc, door_size, collide, NUM_DOORS);
  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, ghosts_loc, ghosts_size, g_die, NUM_GHOSTS);
  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, zombies_loc, zombies_size, z_die, NUM_ZOMBIES);
  proximity(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, inter_loc, inter_size, proximal, NUM_INTERACTABLES);
  proximity(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, pickup_loc, pickup_size, pickup, NUM_PICKUPS);

  glFlush();
  glutSwapBuffers();

}

int main(int argc, char **argv) {

  // INIT
  init(argc, argv);

  glutDisplayFunc(display);
  glutIdleFunc(animation); // Game start
  glutMenu();

  // RUN
  glutMainLoop();

  return(EXIT_SUCCESS);

}


void floor() {
  for (int i = 0; i < NUM_TILES; i++) {
    for (int j = 0; j < NUM_TILES; j++) {
      object(mv, model_view, -50.0 + (i * TILE_SIZE) + TILE_SIZE / 2, -2.5, -50.0 + (j * TILE_SIZE)  + TILE_SIZE / 2, FLOOR_W, FLOOR_H, FLOOR_D, FLOOR_R, FLOOR_G, FLOOR_B, 0, 0, 0, 0, 0, 0);
    }
  }
}

void walls() {
  for (int i = 0; i < 4; i++) {
    object(mv, model_view, wall_loc[i].x, wall_loc[i].y+6.5, wall_loc[i].z, wall_size[i].x, wall_size[i].y/8, wall_size[i].z, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
    object(mv, model_view, wall_loc[i].x, wall_loc[i].y-6.5, wall_loc[i].z, wall_size[i].x, wall_size[i].y/8, wall_size[i].z, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  }
  for (int i = 4; i < NUM_OBJECTS; i++) {
    object(mv, model_view, wall_loc[i].x, wall_loc[i].y, wall_loc[i].z, wall_size[i].x, wall_size[i].y, wall_size[i].z, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  }
  for (int i = 4; i < NUM_OBJECTS; i++) {
    object(mv, model_view, wall_loc[i].x, wall_loc[i].y, wall_loc[i].z, wall_size[i].x, wall_size[i].y, wall_size[i].z, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  }
  object(mv, model_view, -50.0,  door_height,  45.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 90.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
}

void roof() {
  object(mv, model_view, -50.0 + FLOOR_SIZE / 2, 12.5, -50.0 + FLOOR_SIZE / 2, ROOF_W, ROOF_H, ROOF_D, ROOF_R, ROOF_G, ROOF_B, 0, 0, 0, 0, 0, 0);
}

void doors() {
  for (int i = 0; i < NUM_DOORS; i++) {
    if (door_rot[i] == 0) {
        object(mv, model_view, door_loc[i].x - 2.5 + 2.5 * cos(door_open * M_PI/180), door_vert, door_loc[i].z + 2.5 * sin(-door_open * M_PI/180), DOOR_W, DOOR_H, DOOR_D, DOOR_R, DOOR_G, DOOR_B, 0, door_rot[i] + door_open, 0, 0, 0, 0);
    }
    if (door_rot[i] == 180) {
        object(mv, model_view, door_loc[i].x + 2.5 - 2.5 * cos(door_open * M_PI/180), door_vert, door_loc[i].z - 2.5 * sin(-door_open * M_PI/180), DOOR_W, DOOR_H, DOOR_D, DOOR_R, DOOR_G, DOOR_B, 0, door_rot[i] + door_open, 0, 0, 0, 0);
    }
    if (door_rot[i] == -90) {
        object(mv, model_view, door_loc[i].x + 2.5 * sin(door_open * M_PI/180), door_vert, door_loc[i].z - 2.5  + 2.5 * cos(-door_open * M_PI/180), DOOR_W, DOOR_H, DOOR_D, DOOR_R, DOOR_G, DOOR_B, 0, door_rot[i] + door_open, 0, 0, 0, 0);
    }
    if (door_rot[i] == 90) {
        object(mv, model_view, door_loc[i].x - 2.5 * sin(door_open * M_PI/180), door_vert, door_loc[i].z + 2.5 - 2.5 * cos(-door_open * M_PI/180), DOOR_W, DOOR_H, DOOR_D, DOOR_R, DOOR_G, DOOR_B, 0, door_rot[i] + door_open, 0, 0, 0, 0);
    }
    object(mv, model_view, door_loc[i].x, 10.0, door_loc[i].z, DOOR_W, 5.0, DOOR_D, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, door_rot[i], 0, 0, 0, 0);
  }
}

void doorknob() {
  for (int i = 0; i < NUM_DOORS; i++) {
    object(mv, model_view, door_loc[i].x + 1.5, door_vert - 2.0, door_loc[i].z + 0.5, BULB_W, BULB_H, BULB_D, DOORKNOB_R, DOORKNOB_G, DOORKNOB_B, 0, door_rot[i], 0, 0, 0, 0);
    object(mv, model_view, door_loc[i].x + 1.5, door_vert - 2.0, door_loc[i].z + 0.25, SHAFT_W, SHAFT_H, SHAFT_D, DOORKNOB_R, DOORKNOB_G, DOORKNOB_B, 0, door_rot[i], 0, 0, 0, 0);
  }
}

void tables() {
  for (int i = 0; i < NUM_TABLES; i++) {
    object(mv, model_view, table_loc[i].x - 0.0, table_loc[i].y - 0.5, table_loc[i].z - 0.0, TOP_W, TOP_H, TOP_D, TABLE_R, TABLE_G, TABLE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, table_loc[i].x - 1.0, table_loc[i].y - 1.5, table_loc[i].z + 2.0, LEG_W, LEG_H, LEG_D, TABLE_R, TABLE_G, TABLE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, table_loc[i].x + 1.0, table_loc[i].y - 1.5, table_loc[i].z - 2.0, LEG_W, LEG_H, LEG_D, TABLE_R, TABLE_G, TABLE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, table_loc[i].x - 1.0, table_loc[i].y - 1.5, table_loc[i].z - 2.0, LEG_W, LEG_H, LEG_D, TABLE_R, TABLE_G, TABLE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, table_loc[i].x + 1.0, table_loc[i].y - 1.5, table_loc[i].z + 2.0, LEG_W, LEG_H, LEG_D, TABLE_R, TABLE_G, TABLE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  }
}

void moon() {
  object(mv, model_view, -75.0,  40.0, -65.0, MOON_W, MOON_H, MOON_D, MOON_R, MOON_G, MOON_B, 0, 0, 0, 6, 6, 2);
}

void werewolf() {
  for (int i = 1; i < 4; i++) {
    object(mv, model_view, werewolves_loc[i].x + 0.0, zombie_height[0] + 0.5, werewolves_loc[i].z + 0.0, ZOMBIE_W*.75, ZOMBIE_H*.75, ZOMBIE_D*.75, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
    object(mv, model_view, werewolves_loc[i].x + 0.0, zombie_height[1] + 0.0, werewolves_loc[i].z + 0.0, ZOMBIE_W*1, ZOMBIE_H*1, ZOMBIE_D*1, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, werewolves_loc[i].x + 1.0, zombie_height[2] + 0.0, werewolves_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, werewolves_loc[i].x - 1.0, zombie_height[3] + 0.0, werewolves_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, werewolves_loc[i].x + 0.5, zombie_height[4] - 1.0, werewolves_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, werewolves_loc[i].x - 0.5, zombie_height[5] - 1.0, werewolves_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  }
}

void vaccuum() {
  object(pv, model_view, -5.0 + 0.0*0.2, 0.0 - 3.0*0.2, -45.0 + 0.0*0.2, BODYL_W*0.2, BODYL_H*0.2, BODYL_D*0.2, VACCUUM_R, VACCUUM_G, VACCUUM_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 0.0*0.2, 0.0 + 0.5*0.2, -45.0 - 0.5*0.2, BODYS_W*0.2, BODYS_H*0.2, BODYS_D*0.2, VACCUUM_R, VACCUUM_G, VACCUUM_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 2.5*0.2, 0.0 + 0.5*0.2, -45.0 + 1.0*0.2, HOSEL_W*0.203, HOSEL_H*0.2, HOSEL_D*0.203, HOSE_R, HOSE_G, HOSE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 0.0*0.2, 0.0 + 2.5*0.2, -45.0 + 1.0*0.2, HOSEM_W*0.201, HOSEM_H*0.2, HOSEM_D*0.201, HOSE_R, HOSE_G, HOSE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 1.25*0.2, 0.0 + 3.5*0.2, -45.0 + 1.0*0.2, HOSES_W*0.202, HOSES_H*0.2, HOSES_D*0.202, HOSE_R, HOSE_G, HOSE_B, 0, 0, 90, 0, 0, 0);
  object(pv, model_view, -5.0 + 2.5*0.2, 0.0 - 2.5*0.2, -45.0 + 1.5*0.2, NOZZLE_W*0.2, NOZZLE_H*0.2, NOZZLE_D*0.2, HOSE_R, HOSE_G, HOSE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 - 1.0*0.2, 0.0 - 1.5*0.2, -45.0 - 2.0*0.2, STRAP_W*0.2, STRAP_H*0.2, STRAP_D*0.2, STRAP_R, STRAP_G, STRAP_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 1.0*0.2, 0.0 - 1.5*0.2, -45.0 - 2.0*0.2, STRAP_W*0.2, STRAP_H*0.2, STRAP_D*0.2, STRAP_R, STRAP_G, STRAP_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 - 2.5*0.2, 0.0 - 3.5*0.2, -45.0 - 0.5*0.2, WHEEL_W*0.2, WHEEL_H*0.2, WHEEL_D*0.2, WHEEL_R, WHEEL_G, WHEEL_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 2.5*0.2, 0.0 - 3.5*0.2, -45.0 - 0.5*0.2, WHEEL_W*0.2, WHEEL_H*0.2, WHEEL_D*0.2, WHEEL_R, WHEEL_G, WHEEL_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 0.0*0.2, 0.0 + 0.5*0.2, -45.0 + 1.0*0.2, LIGHT_W*0.2, LIGHT_H*0.2, LIGHT_D*0.2, LIGHT_R, LIGHT_G, LIGHT_B, 0, 0, 0, 0, 0, 0);
}

void ghost() {
  object(mv, model_view, ghosts_loc[0].x, ghost_height[0] + 0.5, ghosts_loc[0].z, ghosts_size[0].x, ghosts_size[0].y, ghosts_size[0].z, GHOST_R, GHOST_G, GHOST_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, ghosts_loc[0].x, ghost_height[1] + 0.0, ghosts_loc[0].z, ghosts_size[0].x*1.25, ghosts_size[0].y*1.25, ghosts_size[0].z*1.25, GHOST_R, GHOST_G, GHOST_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, ghosts_loc[0].x + 0.5 * cos(105 * M_PI/180), ghost_height[2] - 1.0, ghosts_loc[0].z + 0.5 * sin(105 * M_PI/180), ghosts_size[0].x/2, ghosts_size[0].y/2, ghosts_size[0].z/2, GHOST_R, GHOST_G, GHOST_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
  object(mv, model_view, ghosts_loc[0].x + 0.5 * cos(225 * M_PI/180), ghost_height[3] - 1.0, ghosts_loc[0].z + 0.5 * sin(225 * M_PI/180), ghosts_size[0].x/2, ghosts_size[0].y/2, ghosts_size[0].z/2, GHOST_R, GHOST_G, GHOST_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
  object(mv, model_view, ghosts_loc[0].x + 0.5 * cos(345 * M_PI/180), ghost_height[4] - 1.0, ghosts_loc[0].z + 0.5 * sin(345 * M_PI/180), ghosts_size[0].x/2, ghosts_size[0].y/2, ghosts_size[0].z/2, GHOST_R, GHOST_G, GHOST_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
}

void picture() {
  object(pv, model_view, picture_loc.x + 0.0*0.2 + 13.0*0.2 * cos(-picture_rot * M_PI/180), picture_loc.y + 30.0*0.2 + 13.0*0.2 * sin(picture_rot * M_PI/180), picture_loc.z + 0.0*0.2, FRAME_W*0.2, FRAME_H*0.2, FRAME_D*0.2, PICTURE_R, PICTURE_G, PICTURE_B, 0, 0, 90 + picture_rot, 0, 0, 0);
  object(pv, model_view, picture_loc.x + 0.0*0.2 + 0.5*0.2 * cos(-picture_rot * M_PI/180), picture_loc.y + 30.0*0.2 + 0.5*0.2 * sin(picture_rot * M_PI/180), picture_loc.z + 0.0*0.2, STRING_W*0.2, STRING_H*0.2, STRING_D*0.2, PICTURE_R, PICTURE_G, PICTURE_B, 0, 0, 45 + picture_rot, 0, 0, 0);
  object(pv, model_view, picture_loc.x + 0.0*0.2 + 0.5*0.2 * cos(-picture_rot * M_PI/180), picture_loc.y + 30.0*0.2 + 0.5*0.2 * sin(picture_rot * M_PI/180), picture_loc.z + 0.0*0.2, STRING_W*0.2, STRING_H*0.2, STRING_D*0.2, PICTURE_R, PICTURE_G, PICTURE_B, 0, 0, 135 + picture_rot, 0, 0, 0);
}

void light() { ;
  // object(mv, model_view, -50.0,  door_height,  45.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 90.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
}

void bookcase() {
  for (int i = 0; i < NUM_BOOKCASE; i++) {
    object(mv, model_view, bookcase_loc[i].x, bookcase_loc[i].y, bookcase_loc[i].z, bookcase_size[i].x, bookcase_size[i].y, bookcase_size[i].z, BOOKCASE_R, BOOKCASE_G, BOOKCASE_B, 0, 0, 0, 0, 0, 0);
  }
}

void book() {
  object(mv, model_view, bookcase_loc[0].x + 1.5, bookcase_loc[0].y, bookcase_loc[0].z, bookcase_size[0].x/2, bookcase_size[0].y/5, 0.5, 1.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
}

void key() {
  object(pv, model_view, table_loc[1].x + 0.0*0.2, table_loc[1].y - 1.5*0.2, table_loc[1].z + 1.5*0.2, KEYL_W*0.2, KEYL_H*0.2, KEYL_D*0.2, KEY_R, KEY_G, KEY_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, table_loc[1].x + 0.0*0.2, table_loc[1].y - 1.5*0.2, table_loc[1].z - 0.5*0.2, KEYL_W*0.2, KEYL_H*0.2, KEYL_D*0.2, KEY_R, KEY_G, KEY_B, 0, 90, 0, 0, 0, 0);
  object(pv, model_view, table_loc[1].x + 0.0*0.2, table_loc[1].y - 1.5*0.2, table_loc[1].z - 2.5*0.2, KEYL_W*0.2, KEYL_H*0.2, KEYL_D*0.2, KEY_R, KEY_G, KEY_B, 0, 90, 0, 0, 0, 0);
  object(pv, model_view, table_loc[1].x + 1.5*0.2, table_loc[1].y - 1.5*0.2, table_loc[1].z - 1.5*0.2, KEYS_W*0.2, KEYS_H*0.2, KEYS_D*0.2, KEY_R, KEY_G, KEY_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, table_loc[1].x - 1.5*0.2, table_loc[1].y - 1.5*0.2, table_loc[1].z - 1.5*0.2, KEYS_W*0.2, KEYS_H*0.2, KEYS_D*0.2, KEY_R, KEY_G, KEY_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, table_loc[1].x - 1.0*0.2, table_loc[1].y - 1.5*0.2, table_loc[1].z + 2.0*0.2, KEYS_W*0.2, KEYS_H*0.2, KEYS_D*0.2, KEY_R, KEY_G, KEY_B, 0, 90, 0, 0, 0, 0);
}

void fire() { ;
  // object(mv, model_view, -50.0,  door_height,  45.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 90.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
}

void agency() {
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y + 1.15, agency_loc.z + 0.0, HAIR_W, HAIR_H, HAIR_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y + 0.75, agency_loc.z + 0.0, FACE_W, FACE_H, FACE_D, SKIN_R, SKIN_G, SKIN_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.3, agency_loc.y + 0.75, agency_loc.z - 0.175, LENS_W, LENS_H, LENS_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.3, agency_loc.y + 0.75, agency_loc.z + 0.175, LENS_W, LENS_H, LENS_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.4, agency_loc.y + 0.875, agency_loc.z + 0.0, BRIDGE_W, BRIDGE_H, BRIDGE_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y - 0.25, agency_loc.z + 0.0, SHIRT_W, SHIRT_H, SHIRT_D, SHIRT_R, SHIRT_G, SHIRT_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y - 0.25, agency_loc.z - 0.375, SUIT_W, SUIT_H, SUIT_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y - 0.25, agency_loc.z + 0.375, SUIT_W, SUIT_H, SUIT_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.25, agency_loc.y - 0.125, agency_loc.z + 0.0, TIE_W, TIE_H, TIE_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y - 0.375, agency_loc.z - 0.5, APPENDAGE_W, APPENDAGE_H, APPENDAGE_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y - 0.375, agency_loc.z + 0.5, APPENDAGE_W, APPENDAGE_H, APPENDAGE_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y - 1.5, agency_loc.z - 0.25, APPENDAGE_W, APPENDAGE_H, APPENDAGE_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, agency_loc.x + 0.0, agency_loc.y - 1.5, agency_loc.z + 0.25, APPENDAGE_W, APPENDAGE_H, APPENDAGE_D, AGENCY_R, AGENCY_G, AGENCY_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
 }

void gun() {
  object(pv, model_view, table_loc[2].x + 0.0*0.2, table_loc[2].y + 0.0*0.2, table_loc[2].z + -1.0*0.2, BARREL_W*0.2, BARREL_H*0.2, BARREL_D*0.2, BARREL_R, BARREL_G, BARREL_B, 0, 0, 90, 0, 0, 0);
  object(pv, model_view, table_loc[2].x - 0.4*0.2, table_loc[2].y + -0.5*0.2, table_loc[2].z + -1.75*0.2, SIGHT_W*0.2, SIGHT_H*0.2, SIGHT_D*0.2, SIGHT_R, SIGHT_G, SIGHT_B, 0, 0, 90, 0, 0, 0);
  object(pv, model_view, table_loc[2].x + 0.1*0.2, table_loc[2].y + -1.1*0.2, table_loc[2].z + 0.0*0.2, HANDLE_W*0.2, HANDLE_H*0.2, HANDLE_D*0.2, HANDLE_R, HANDLE_G, HANDLE_B, 0, 0, 90, 0, 0, 0);
}

void zombies() {
  for (int i = 0; i < NUM_ZOMBIES; i++) {
    object(mv, model_view, zombies_loc[i].x + 0.0, zombie_height[0] + 0.5, zombies_loc[i].z + 0.0, zombies_size[i].x*.75, zombies_size[i].y*.75, zombies_size[i].z*.75, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
    object(mv, model_view, zombies_loc[i].x + 0.0, zombie_height[1] + 0.0, zombies_loc[i].z + 0.0, zombies_size[i].x*1, zombies_size[i].y*1, zombies_size[i].z*1, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, zombies_loc[i].x + 1.0, zombie_height[2] + 0.0, zombies_loc[i].z + 0.0, zombies_size[i].x/2, zombies_size[i].y, zombies_size[i].z/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, zombies_loc[i].x - 1.0, zombie_height[3] + 0.0, zombies_loc[i].z + 0.0, zombies_size[i].x/2, zombies_size[i].y, zombies_size[i].z/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, zombies_loc[i].x + 0.5, zombie_height[4] - 1.0, zombies_loc[i].z + 0.0, zombies_size[i].x/2, zombies_size[i].y, zombies_size[i].z/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, zombies_loc[i].x - 0.5, zombie_height[5] - 1.0, zombies_loc[i].z + 0.0, zombies_size[i].x/2, zombies_size[i].y, zombies_size[i].z/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  }
}

void coffee() {
  object(pv, model_view, table_loc[3].x + 0.0*0.2, table_loc[3].y - 0.8*0.2, table_loc[3].z + 0.0*0.2, COFFEE_W*0.2, COFFEE_H*0.2, COFFEE_D*0.2, COFFEE_R, COFFEE_G, COFFEE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, table_loc[3].x + 0.0*0.2, table_loc[3].y - 1.0*0.2, table_loc[3].z + 0.0*0.2, CUP_W*0.2, CUP_H*0.2, CUP_D*0.2, DISH_R, DISH_G, DISH_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, table_loc[3].x + 0.0*0.2, table_loc[3].y - 1.5*0.2, table_loc[3].z + 0.0*0.2, SAUCER_W*0.2, SAUCER_H*0.2, SAUCER_D*0.2, DISH_R, DISH_G, DISH_B, 0, 45, 0, 0, 0, 0);
  object(pv, model_view, table_loc[3].x + 0.0*0.2, table_loc[3].y - 1.5*0.2, table_loc[3].z + 0.0*0.2, SAUCER_W*0.2, SAUCER_H*0.2, SAUCER_D*0.2, DISH_R, DISH_G, DISH_B, 0, 0, 0, 0, 0, 0);
}

void set_objects() {

  // ENVIRONMENT
  wall_loc[0] = vec3(0.0, wall_height, 50.0);
  wall_loc[1] = vec3(0.0, wall_height, -50.0);
  wall_loc[2] = vec3(-50.0, wall_height, -5.0);
  wall_loc[3] = vec3(50.0, wall_height, 0.0);
  wall_loc[4] = vec3(-7.5, wall_height, 40.0);
  wall_loc[5] = vec3(45.0, wall_height, 40.0);
  wall_loc[6] = vec3(25.0, wall_height, 20.0);
  wall_loc[7] = vec3(-5.0, wall_height, 0.0);
  wall_loc[8] = vec3(-45.0, wall_height, 0.0);
  wall_loc[9] = vec3(45.0, wall_height, -25.0);
  wall_loc[10] = vec3(25.0, wall_height, -25.0);
  wall_loc[11] = vec3(5.0, wall_height, -25.0);
  wall_loc[12] = vec3(-25.0, wall_height, 0.0);
  wall_loc[13] = vec3(-25.0, wall_height, -47.5);
  wall_loc[14] = vec3(25.0, wall_height, 36.25);
  wall_loc[15] = vec3(25.0, wall_height, 20.0);
  wall_loc[16] = vec3(25.0, wall_height, 0.0);
  wall_loc[17] = vec3(25.0, wall_height, -25.0);
  wall_loc[18] = vec3(0.0, wall_height, -32.5);
  wall_loc[19] = vec3(0.0, wall_height, -5.0);
  wall_loc[20] = vec3(-50.0, door_height, 45.0);

  wall_loc[21] = vec3(-50.0, wall_height, 35.0);
  wall_loc[22] = vec3(-50.0, wall_height, 0.0);
  wall_loc[23] = vec3(-50.0, wall_height, -25.0);
  wall_loc[24] = vec3(-50.0, wall_height, -45.0);

  wall_loc[25] = vec3(-45.0, wall_height, -50.0);
  wall_loc[26] = vec3(-25.0, wall_height, -50.0);
  wall_loc[27] = vec3(0.0, wall_height, -50.0);
  wall_loc[28] = vec3(32.5, wall_height, -50.0);

  wall_loc[29] = vec3(50.0, wall_height, -35.0);
  wall_loc[30] = vec3(50.0, wall_height, -5.0);
  wall_loc[31] = vec3(50.0, wall_height, 17.5);
  wall_loc[32] = vec3(50.0, wall_height, 42.5);

  wall_loc[33] = vec3(40.0, wall_height, 50.0);
  wall_loc[34] = vec3(15.0, wall_height, 50.0);
  wall_loc[35] = vec3(-5.0, wall_height, 50.0);
  wall_loc[36] = vec3(-25.0, wall_height, 50.0);
  wall_loc[37] = vec3(-45.0, wall_height, 50.0);

  door_loc[0] = vec3(-37.5, 0.0, 0.0);
  door_loc[1] = vec3(-25.0, 0.0, -42.5);
  door_loc[2] = vec3(0.0, 0.0, -12.5);
  door_loc[3] = vec3(12.5, 0.0, -25.0);
  door_loc[4] = vec3(37.5, 0.0, -25.0);
  door_loc[5] = vec3(25.0, 0.0, 10.0);
  door_loc[6] = vec3(25.0, 0.0, 30.0);
  door_loc[7] = vec3(37.5, 0.0, 40.0);

  door_rot[0] = 0;
  door_rot[1] = -90;
  door_rot[2] = -90;
  door_rot[3] = 0;
  door_rot[4] = 180;
  door_rot[5] = 90;
  door_rot[6] = -90;
  door_rot[7] = 180;

  door_dir[0] = north;
  door_dir[1] = east;
  door_dir[2] = east;
  door_dir[3] = north;
  door_dir[4] = south;
  door_dir[5] = west;
  door_dir[6] = east;
  door_dir[7] = south;

  table_loc[0] = vec3(20.0, 0.0, -30.0);
  table_loc[1] = vec3(30.0, 0.0, -30.0);
  table_loc[2] = vec3(-20.0, 0.0, 10.0);
  table_loc[3] = vec3(45.0, 0.0, 45.0);

  bookcase_loc[0] = vec3(2.5, wall_height, -37.5);
  bookcase_loc[1] = vec3(47.5, wall_height, -37.5);
  bookcase_loc[2] = vec3(22.5, wall_height, bookcase_z);
  bookcase_loc[3] = vec3(27.5, wall_height, bookcase_z);
  bookcase_loc[4] = vec3(5.0, wall_height, -27.5);
  bookcase_loc[5] = vec3(45.0, wall_height, -27.5);
  bookcase_loc[6] = vec3(5.0, wall_height, -47.5);
  bookcase_loc[7] = vec3(bookcase_x[0], wall_height, -47.5);
  bookcase_loc[8] = vec3(bookcase_x[1], wall_height, -47.5);
  bookcase_loc[9] = vec3(45.0, wall_height, -47.5);

  ghosts_loc[0] = vec3(ghost_loc.x*ghost_mult, ghost_height[0]*ghost_mult, ghost_loc.z*ghost_mult);

  zombies_loc[0] = vec3(zombie_loc[0].x*zombie_mult[0], zombie_height[0]*zombie_mult[0], zombie_loc[0].z*zombie_mult[0]);
  zombies_loc[1] = vec3(zombie_loc[1].x*zombie_mult[1], zombie_height[0]*zombie_mult[1], zombie_loc[1].z*zombie_mult[1]);
  zombies_loc[2] = vec3(zombie_loc[2].x*zombie_mult[2], zombie_height[0]*zombie_mult[2], zombie_loc[2].z*zombie_mult[2]);
  // agencies_loc[1] = vec3(agency_loc[0].x, agency_height[0], agency_loc[0].z);

  inter_loc[0] = vec3(-37.5, 0.0, 0.0);
  inter_loc[1] = vec3(-25.0, 0.0, -42.5);
  inter_loc[2] = vec3(12.5, table_loc[1].y, -1.0); // Picture
  inter_loc[3] = vec3(bookcase_loc[0].x + 1.5, bookcase_loc[0].y, bookcase_loc[0].z);

  pickup_loc[0] = vec3(-5.0, table_loc[1].y, -45.0); // Vaccuum
  pickup_loc[1] = vec3(table_loc[1].x, table_loc[1].y, table_loc[1].z);
  pickup_loc[2] = vec3(table_loc[2].x, table_loc[2].y, table_loc[2].z);
  pickup_loc[3] = vec3(table_loc[3].x, table_loc[3].y, table_loc[3].z);

  wall_size[0] = vec3(100, LAT_WALL_H, LAT_WALL_D);
  wall_size[1] = vec3(100, LAT_WALL_H, LAT_WALL_D);
  wall_size[2] = vec3(LON_WALL_W, LON_WALL_H, 90.0);
  wall_size[3] = vec3(LON_WALL_W, LON_WALL_H, 100.0);
  wall_size[4] = vec3(85.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[5] = vec3(10.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[6] = vec3(50.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[7] = vec3(60.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[8] = vec3(10.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[9] = vec3(10.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[10] = vec3(20.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[11] = vec3(10.0, LAT_WALL_H, LAT_WALL_D);
  wall_size[12] = vec3(LON_WALL_W, LON_WALL_H, 80.0);
  wall_size[13] = vec3(LON_WALL_W, LON_WALL_H, 5.0);
  wall_size[14] = vec3(LON_WALL_W, LON_WALL_H, 7.5);
  wall_size[15] = vec3(LON_WALL_W, LON_WALL_H, 15.0);
  wall_size[16] = vec3(LON_WALL_W, LON_WALL_H, 15.0);
  wall_size[17] = vec3(LON_WALL_W, LON_WALL_H, 40.0);
  wall_size[18] = vec3(LON_WALL_W, LON_WALL_H, 35.0);
  wall_size[19] = vec3(LON_WALL_W, LON_WALL_H, 10.0);
  wall_size[20] = vec3(LON_WALL_W, LON_WALL_H, 10.0);

  wall_size[21] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 10.0);
  wall_size[22] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 20.0);
  wall_size[23] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 10.0);
  wall_size[24] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 10.0);

  wall_size[25] = vec3(10.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);
  wall_size[27] = vec3(20.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);
  wall_size[26] = vec3(10.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);
  wall_size[28] = vec3(35.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);

  wall_size[29] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 30.0);
  wall_size[30] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 10.0);
  wall_size[31] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 15.0);
  wall_size[32] = vec3(LON_WALL_W, LON_WALL_H*6/8+0.2, 15.0);

  wall_size[33] = vec3(20.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);
  wall_size[34] = vec3(10.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);
  wall_size[36] = vec3(10.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);
  wall_size[35] = vec3(10.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);
  wall_size[37] = vec3(10.0, LAT_WALL_H*6/8+0.2, LAT_WALL_D);

  door_size[0] = vec3(DOOR_W, DOOR_H, DOOR_B);
  door_size[1] = vec3(DOOR_W, DOOR_H, DOOR_B);
  door_size[2] = vec3(DOOR_W, DOOR_H, DOOR_B);
  door_size[3] = vec3(DOOR_W, DOOR_H, DOOR_B);
  door_size[4] = vec3(DOOR_W, DOOR_H, DOOR_B);
  door_size[5] = vec3(DOOR_W, DOOR_H, DOOR_B);
  door_size[6] = vec3(DOOR_W, DOOR_H, DOOR_B);
  door_size[7] = vec3(DOOR_W, DOOR_H, DOOR_B);

  bookcase_size[0] = vec3(BOOKCASELZ_W, BOOKCASELZ_H, BOOKCASELZ_D);
  bookcase_size[1] = vec3(BOOKCASELZ_W, BOOKCASELZ_H, BOOKCASELZ_D);
  bookcase_size[2] = vec3(BOOKCASESZ_W, BOOKCASESZ_H, BOOKCASESZ_D);
  bookcase_size[3] = vec3(BOOKCASESZ_W, BOOKCASESZ_H, BOOKCASESZ_D);
  bookcase_size[4] = vec3(BOOKCASESX_W, BOOKCASESX_H, BOOKCASESX_D);
  bookcase_size[5] = vec3(BOOKCASESX_W, BOOKCASESX_H, BOOKCASESX_D);
  bookcase_size[6] = vec3(BOOKCASESX_W, BOOKCASESX_H, BOOKCASESX_D);
  bookcase_size[7] = vec3(BOOKCASESX_W, BOOKCASESX_H, BOOKCASESX_D);
  bookcase_size[8] = vec3(BOOKCASESX_W, BOOKCASESX_H, BOOKCASESX_D);
  bookcase_size[9] = vec3(BOOKCASESX_W, BOOKCASESX_H, BOOKCASESX_D);

  table_size[0] = vec3(TOP_W, LEG_H, TOP_D);
  table_size[1] = vec3(TOP_W, LEG_H, TOP_D);
  table_size[2] = vec3(TOP_W, LEG_H, TOP_D);
  table_size[3] = vec3(TOP_W, LEG_H, TOP_D);

  ghosts_size[0] = vec3(GHOST_W*ghost_mult, GHOST_H*ghost_mult, GHOST_D*ghost_mult);

  zombies_size[0] = vec3(ZOMBIE_W*zombie_mult[0], ZOMBIE_H*zombie_mult[0], ZOMBIE_D*zombie_mult[0]);
  zombies_size[1] = vec3(ZOMBIE_W*zombie_mult[1], ZOMBIE_H*zombie_mult[1], ZOMBIE_D*zombie_mult[1]);
  zombies_size[2] = vec3(ZOMBIE_W*zombie_mult[2], ZOMBIE_H*zombie_mult[2], ZOMBIE_D*zombie_mult[2]);

  inter_size[0] = vec3(2.0, 2.0, 2.0);
  inter_size[1] = vec3(2.0, 2.0, 2.0);
  inter_size[2] = vec3(2.0, 2.0, 2.0);
  inter_size[3] = vec3(2.0, 2.0, 2.0);

  pickup_size[4] = vec3(1.0, 1.0, 1.0);
  pickup_size[5] = vec3(2.5, 1.0, 2.5);
  pickup_size[6] = vec3(2.5, 1.0, 2.5);
  pickup_size[7] = vec3(2.5, 1.0, 2.5);

}

// //----------------------------------------------------------------------------
// int main(int argc, char **argv)
// {
//
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//   glutInitWindowSize(512, 512);
//   glutCreateWindow("Sphere");
//
//   glewInit();
//
//   init();
//
//   glutDisplayFunc(display);
//   glutReshapeFunc(reshape);
//   glutKeyboardFunc(keyboard);
//   glutIdleFunc(idle);
//   glutMainLoop();
//   return(EXIT_SUCCESS);
// }
