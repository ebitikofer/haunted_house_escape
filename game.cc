//***************
// Eric Bitikofer
// 10/14/18
// 3D game made in OpenGL
//

#include <Angel.h>
#include "engine.h"
#include "instance.h"
#include "game.h"

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
  glEnable( GL_DEPTH_TEST );

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

  // ENVIRONMENT
  // object(mv, model_view,   0.0,  7.5,  50.0, LAT_WALL_W * NUM_TILES, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  -7.5,  7.5,  40.0, LAT_WALL_W * NUM_TILES - 15.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  45.0,  7.5,  40.0, LAT_WALL_W * NUM_TILES - 90.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  25.0,  7.5,  20.0, LAT_WALL_W * NUM_TILES - 50.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  -5.0,  7.5,   0.0, LAT_WALL_W * NUM_TILES - 40.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view, -45.0,  7.5,   0.0, LAT_WALL_W * NUM_TILES - 90.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  45.0,  7.5, -25.0, LAT_WALL_W * NUM_TILES - 90.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  25.0,  7.5, -25.0, LAT_WALL_W * NUM_TILES - 80.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,   5.0,  7.5, -25.0, LAT_WALL_W * NUM_TILES - 90.0, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,   0.0,  7.5, -50.0, LAT_WALL_W * NUM_TILES, LAT_WALL_H, LAT_WALL_D, LAT_WALL_R, LAT_WALL_G, LAT_WALL_B, 0, 0, 0, 0, 0, 0);
  //
  // object(mv, model_view, -50.0,  7.5,  -5.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 10.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view, -25.0,  7.5,   0.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 20.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view, -25.0,  7.5, -47.5, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 95.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  25.0,  7.5,  37.5, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 95.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  25.0,  7.5,  20.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 90.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  25.0,  7.5,   0.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 90.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  25.0,  7.5, -25.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 60.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,   0.0,  7.5, -32.5, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 65.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,   0.0,  7.5,  -5.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 90.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
  // object(mv, model_view,  50.0,  7.5,   0.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);

  // object(mv, model_view, -5.0, 0.0, -5.0, TREE_W, TREE_H, TREE_D, TREE_R, TREE_G, TREE_B, -10, 45, 10, 0, 0, 0); // translate down half of the object
  // object(mv, model_view, -5.0, 0.0, -5.0, ROCK_W, ROCK_H, ROCK_D, ROCK_R, ROCK_G, ROCK_B, 45, 45, 45, 0, 0, 0); // translate down half of the object
  // object(mv, model_view, -5.0, 0.0, -5.0, ANIMAL_W, ANIMAL_H, ANIMAL_D, FLOOR_R, FLOOR_G, FLOOR_B, 0, 0, 0, 0, 0, 0); // translate down half of the object

  set_objects(); // Set objects for render

  // Move fourth sphere to where light2 is positioned, and make it an
  // emissive object.
  // glUniform4fv(Material_Emiss, 1, light2_diffuse);
  // glUniformMatrix4fv(model_view, 1, GL_TRUE, mv*Translate(-37.5, 0.0, 20.0));
  // glUniform1f( enable, 1.0 );
  // glDrawArrays(GL_TRIANGLES, NumVertices, NumVertices2);
  // glUniform4fv(Material_Emiss, 1, emissive_off);

  // Environment
  floor();
  walls();
  roof();
  doors();
  moon();
  bookcase();
  tables();

  // Props
  doorknob();
  vaccuum();
  picture();

  light();
  book();
  fire();
  key();
  gun();
  coffee();

  // Enemies
  werewolf();
  ghost();
  agency();
  zombies();

  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, wall_loc, wall_size, collide, NUM_OBJECTS);
  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, bookcase_loc, bookcase_size, collide, NUM_BOOKCASE);
  // collision(&enemy_loc[0].x, 0.0, &enemy_loc[0].z, GHOST_W, GHOST_H, GHOST_D, wall_loc, wall_size, collide, NUM_OBJECTS);
  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, table_loc, table_size, collide, NUM_TABLES);
  collision(&mvx, 0.0, &mvz, PLAYER_W, PLAYER_H, PLAYER_D, enemy_loc, enemy_size, die, NUM_ENEMIES);

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
      // if (i % 5 == 0) {
      //   if (j % 10 == 0) {
      //     object(mv, model_view, -50.0 + (i / 6 * 10.0), 0.0, -50.0 + ( j / 10 * 20.0), TREE_W, TREE_H, TREE_D, TREE_R, TREE_G, TREE_B, -10, 45, 10, 0, 0, 0); // translate down half of the object
      //     object(mv, model_view, -45.0 + (i / 6 * 10.0), 0.0, -45.0 + ( j / 10 * 20.0), ROCK_W, ROCK_H, ROCK_D, ROCK_R, ROCK_G, ROCK_B, 45, 45, 45, 0, 0, 0); // translate down half of the object
      //     object(mv, model_view, -30.0 + (i / 6 * 10.0), 0.0, -30.0 + ( j / 10 * 20.0), ANIMAL_W, ANIMAL_H, ANIMAL_D, FLOOR_R, FLOOR_G, FLOOR_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
      //   }
      // }
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
  object(mv, model_view, -50.0,  door_height,  45.0, LON_WALL_W, LON_WALL_H, LON_WALL_D * NUM_TILES - 90.0, LON_WALL_R, LON_WALL_G, LON_WALL_B, 0, 0, 0, 0, 0, 0);
}

void roof() {
  object(mv, model_view, -50.0 + FLOOR_SIZE / 2, 12.5, -50.0 + FLOOR_SIZE / 2, ROOF_W, ROOF_H, ROOF_D, ROOF_R, ROOF_G, ROOF_B, 0, 0, 0, 0, 0, 0);
}

void doors() {
  object(mv, model_view, door_loc[0].x, door_vert, door_loc[0].z, DOOR_W, DOOR_H, DOOR_D, DOOR_R, DOOR_G, DOOR_B, 0, door_rot[0], 0, 0, 0, 0);
  object(mv, model_view, door_loc[1].x, door_vert, door_loc[1].z, DOOR_W, DOOR_H, DOOR_D, DOOR_R, DOOR_G, DOOR_B, 0, door_rot[1], 0, 0, 0, 0);
}

void doorknob() {
  object(mv, model_view, door_loc[0].x + 1.5, door_vert - 2.0, door_loc[0].z + 0.5, BULB_W, BULB_H, BULB_D, DOORKNOB_R, DOORKNOB_G, DOORKNOB_B, 0, door_rot[0], 0, 0, 0, 0);
  object(mv, model_view, door_loc[0].x + 1.5, door_vert - 2.0, door_loc[0].z + 0.25, SHAFT_W, SHAFT_H, SHAFT_D, DOORKNOB_R, DOORKNOB_G, DOORKNOB_B, 0, door_rot[0], 0, 0, 0, 0);
  object(mv, model_view, door_loc[1].x + 1.5, door_vert - 2.0, door_loc[1].z + 0.5, BULB_W, BULB_H, BULB_D, DOORKNOB_R, DOORKNOB_G, DOORKNOB_B, 0, door_rot[1], 0, 0, 0, 0);
  object(mv, model_view, door_loc[1].x + 1.5, door_vert - 2.0, door_loc[1].z + 0.25, SHAFT_W, SHAFT_H, SHAFT_D, DOORKNOB_R, DOORKNOB_G, DOORKNOB_B, 0, door_rot[1], 0, 0, 0, 0);
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
    object(mv, model_view, enemy_loc[i].x + 0.0, zombie_height[0] + 0.5, enemy_loc[i].z + 0.0, ZOMBIE_W*.75, ZOMBIE_H*.75, ZOMBIE_D*.75, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x + 0.0, zombie_height[1] + 0.0, enemy_loc[i].z + 0.0, ZOMBIE_W*1, ZOMBIE_H*1, ZOMBIE_D*1, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x + 1.0, zombie_height[2] + 0.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x - 1.0, zombie_height[3] + 0.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x + 0.5, zombie_height[4] - 1.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x - 0.5, zombie_height[5] - 1.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  }
}

void vaccuum() {
  object(pv, model_view, -5.0 + 0.0*0.2, table_loc[1].y - 3.0*0.2, -45.0 + 0.0*0.2, BODYL_W*0.2, BODYL_H*0.2, BODYL_D*0.2, VACCUUM_R, VACCUUM_G, VACCUUM_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 0.0*0.2, table_loc[1].y + 0.5*0.2, -45.0 - 0.5*0.2, BODYS_W*0.2, BODYS_H*0.2, BODYS_D*0.2, VACCUUM_R, VACCUUM_G, VACCUUM_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 2.5*0.2, table_loc[1].y + 0.5*0.2, -45.0 + 1.0*0.2, HOSEL_W*0.203, HOSEL_H*0.2, HOSEL_D*0.203, HOSE_R, HOSE_G, HOSE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 0.0*0.2, table_loc[1].y + 2.5*0.2, -45.0 + 1.0*0.2, HOSEM_W*0.201, HOSEM_H*0.2, HOSEM_D*0.201, HOSE_R, HOSE_G, HOSE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 1.25*0.2, table_loc[1].y + 3.5*0.2, -45.0 + 1.0*0.2, HOSES_W*0.202, HOSES_H*0.2, HOSES_D*0.202, HOSE_R, HOSE_G, HOSE_B, 0, 0, 90, 0, 0, 0);
  object(pv, model_view, -5.0 + 2.5*0.2, table_loc[1].y - 2.5*0.2, -45.0 + 1.5*0.2, NOZZLE_W*0.2, NOZZLE_H*0.2, NOZZLE_D*0.2, HOSE_R, HOSE_G, HOSE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 - 1.0*0.2, table_loc[1].y - 1.5*0.2, -45.0 - 2.0*0.2, STRAP_W*0.2, STRAP_H*0.2, STRAP_D*0.2, STRAP_R, STRAP_G, STRAP_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 1.0*0.2, table_loc[1].y - 1.5*0.2, -45.0 - 2.0*0.2, STRAP_W*0.2, STRAP_H*0.2, STRAP_D*0.2, STRAP_R, STRAP_G, STRAP_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 - 2.5*0.2, table_loc[1].y - 3.5*0.2, -45.0 - 0.5*0.2, WHEEL_W*0.2, WHEEL_H*0.2, WHEEL_D*0.2, WHEEL_R, WHEEL_G, WHEEL_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 2.5*0.2, table_loc[1].y - 3.5*0.2, -45.0 - 0.5*0.2, WHEEL_W*0.2, WHEEL_H*0.2, WHEEL_D*0.2, WHEEL_R, WHEEL_G, WHEEL_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, -5.0 + 0.0*0.2, table_loc[1].y + 0.5*0.2, -45.0 + 1.0*0.2, LIGHT_W*0.2, LIGHT_H*0.2, LIGHT_D*0.2, LIGHT_R, LIGHT_G, LIGHT_B, 0, 0, 0, 0, 0, 0);
}

void ghost() {
  object(mv, model_view, enemy_loc[0].x, ghost_height[0] + 0.5, enemy_loc[0].z, GHOST_W, GHOST_H, GHOST_D, GHOST_R, GHOST_G, GHOST_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, enemy_loc[0].x, ghost_height[1] + 0.0, enemy_loc[0].z, GHOST_W*1.25, GHOST_H*1.25, GHOST_D*1.25, GHOST_R, GHOST_G, GHOST_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  object(mv, model_view, enemy_loc[0].x + 0.5 * cos(105 * M_PI/180), ghost_height[2] - 1.0, enemy_loc[0].z + 0.5 * sin(105 * M_PI/180), GHOST_W/2, GHOST_H/2, GHOST_D/2, GHOST_R, GHOST_G, GHOST_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
  object(mv, model_view, enemy_loc[0].x + 0.5 * cos(225 * M_PI/180), ghost_height[3] - 1.0, enemy_loc[0].z + 0.5 * sin(225 * M_PI/180), GHOST_W/2, GHOST_H/2, GHOST_D/2, GHOST_R, GHOST_G, GHOST_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
  object(mv, model_view, enemy_loc[0].x + 0.5 * cos(345 * M_PI/180), ghost_height[4] - 1.0, enemy_loc[0].z + 0.5 * sin(345 * M_PI/180), GHOST_W/2, GHOST_H/2, GHOST_D/2, GHOST_R, GHOST_G, GHOST_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
}

void picture() {
  object(pv, model_view, 12.5 + 0.0*0.2, table_loc[1].y + 13.0*0.2, -1.0 + 0.0*0.2, FRAME_W*0.2, FRAME_H*0.2, FRAME_D*0.2, PICTURE_R, PICTURE_G, PICTURE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, 12.5 - 2.0*0.2, table_loc[1].y + 25.0*0.2, -1.0 + 0.0*0.2, STRING_W*0.2, STRING_H*0.2, STRING_D*0.2, PICTURE_R, PICTURE_G, PICTURE_B, 0, 0, -45, 0, 0, 0);
  object(pv, model_view, 12.5 + 2.0*0.2, table_loc[1].y + 25.0*0.2, -1.0 + 0.0*0.2, STRING_W*0.2, STRING_H*0.2, STRING_D*0.2, PICTURE_R, PICTURE_G, PICTURE_B, 0, 0, 45, 0, 0, 0);
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
  for (int i = 1; i < 4; i++) {
    object(mv, model_view, enemy_loc[i].x + 0.0, zombie_height[0] + 0.5, enemy_loc[i].z + 0.0, ZOMBIE_W*.75, ZOMBIE_H*.75, ZOMBIE_D*.75, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 45, 0, 45, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x + 0.0, zombie_height[1] + 0.0, enemy_loc[i].z + 0.0, ZOMBIE_W*1, ZOMBIE_H*1, ZOMBIE_D*1, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x + 1.0, zombie_height[2] + 0.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x - 1.0, zombie_height[3] + 0.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x + 0.5, zombie_height[4] - 1.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
    object(mv, model_view, enemy_loc[i].x - 0.5, zombie_height[5] - 1.0, enemy_loc[i].z + 0.0, ZOMBIE_W/2, ZOMBIE_H, ZOMBIE_D/2, ZOMBIE_R, ZOMBIE_G, ZOMBIE_B, 0, 0, 0, 0, 0, 0); // translate down half of the object
  }
}

void coffee() {
  object(pv, model_view, table_loc[0].x + 0.0*0.2, table_loc[0].y - 0.8*0.2, table_loc[0].z + 0.0*0.2, COFFEE_W*0.2, COFFEE_H*0.2, COFFEE_D*0.2, COFFEE_R, COFFEE_G, COFFEE_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, table_loc[0].x + 0.0*0.2, table_loc[0].y - 1.0*0.2, table_loc[0].z + 0.0*0.2, CUP_W*0.2, CUP_H*0.2, CUP_D*0.2, DISH_R, DISH_G, DISH_B, 0, 0, 0, 0, 0, 0);
  object(pv, model_view, table_loc[0].x + 0.0*0.2, table_loc[0].y - 1.5*0.2, table_loc[0].z + 0.0*0.2, SAUCER_W*0.2, SAUCER_H*0.2, SAUCER_D*0.2, DISH_R, DISH_G, DISH_B, 0, 45, 0, 0, 0, 0);
  object(pv, model_view, table_loc[0].x + 0.0*0.2, table_loc[0].y - 1.5*0.2, table_loc[0].z + 0.0*0.2, SAUCER_W*0.2, SAUCER_H*0.2, SAUCER_D*0.2, DISH_R, DISH_G, DISH_B, 0, 0, 0, 0, 0, 0);
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
  wall_loc[14] = vec3(25.0, wall_height, 37.5);
  wall_loc[15] = vec3(25.0, wall_height, 20.0);
  wall_loc[16] = vec3(25.0, wall_height, 0.0);
  wall_loc[17] = vec3(25.0, wall_height, -25.0);
  wall_loc[18] = vec3(0.0, wall_height, -32.5);
  wall_loc[19] = vec3(0.0, wall_height, -5.0);
  wall_loc[20] = vec3(-50.0, door_height, 45.0);

  table_loc[0] = vec3(45.0, 0.0, 45.0);
  table_loc[1] = vec3(30.0, 0.0, -30.0);
  table_loc[2] = vec3(-20.0, 0.0, 10.0);
  table_loc[3] = vec3(20.0, 0.0, -30.0);

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

  enemy_loc[0] = vec3(ghost_loc.x, ghost_height[0], ghost_loc.z);
  enemy_loc[1] = vec3(zombie_loc[0].x, zombie_height[0], zombie_loc[0].z);
  enemy_loc[2] = vec3(zombie_loc[1].x, zombie_height[0], zombie_loc[1].z);
  enemy_loc[3] = vec3(zombie_loc[2].x, zombie_height[0], zombie_loc[2].z);
  // enemy_loc[1] = vec3(agency_loc[0].x, agency_height[0], agency_loc[0].z);

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
  wall_size[14] = vec3(LON_WALL_W, LON_WALL_H, 5.0);
  wall_size[15] = vec3(LON_WALL_W, LON_WALL_H, 10.0);
  wall_size[16] = vec3(LON_WALL_W, LON_WALL_H, 10.0);
  wall_size[17] = vec3(LON_WALL_W, LON_WALL_H, 40.0);
  wall_size[18] = vec3(LON_WALL_W, LON_WALL_H, 35.0);
  wall_size[19] = vec3(LON_WALL_W, LON_WALL_H, 10.0);
  wall_size[20] = vec3(LON_WALL_W, LON_WALL_H, 10.0);

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

  enemy_size[0] = vec3(GHOST_W, GHOST_H, GHOST_D);
  enemy_size[1] = vec3(ZOMBIE_W, ZOMBIE_H, ZOMBIE_D);
  enemy_size[2] = vec3(ZOMBIE_W, ZOMBIE_H, ZOMBIE_D);
  enemy_size[3] = vec3(ZOMBIE_W, ZOMBIE_H, ZOMBIE_D);

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
