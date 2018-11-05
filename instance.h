#ifndef INSTANCE_H
#define INSTANCE_H

#include <Angel.h>
#include "models.h"

// Motion rates
#define RATE_PLAYER	  0.5
#define RATE_GUN	    1
//
#define NUM_OF_ANIMALS	3
#define NUM_EACH_ANIMAL	1

// Display list
#define DRAW_PLAYER 1
#define DRAW_DART		2
#define DRAW_FLOORS	3
#define DRAW_TREES	4
#define DRAW_ROCKS	5
#define DRAW_ANIMAL 6

// Which entity will the mouse control (see list above), initally the Head2 angle.
// GLint angle = Head2;

// Rotation of first cube
bool rotatep;                  // whether to rotate or not
GLfloat move_angle = 0.0;           // Angle of cube rotation.

// Implementing a door that opens by swinging
GLfloat doorAngle = 0.0;       // Angle of cube's door's rotation.
GLfloat doorAngleIncr = 30.0;   // Amount to increment Angle of cube's door's rotation.

GLfloat trans = 0.0;   // trans of 2nd cube.
GLfloat transinc = 1.0;// trans increment of 2nd cube.

// Game object locations
vec3 player = vec3(0.0, 0.0, 6.0);
vec3 animal[NUM_OF_ANIMALS * NUM_EACH_ANIMAL] = {vec3(0.0, 0.0, 0.0)};
vec3 animal_health[NUM_OF_ANIMALS * NUM_EACH_ANIMAL] = {vec3(1.0, 1.0, 1.0)};
vec2 animal_det[NUM_OF_ANIMALS * NUM_EACH_ANIMAL] = {vec2(0.0, 1.0)};

// Color vec3s
vec3 sky = vec3(0.8, 1.0, 1.0);
vec3 feather = vec3(FEATHER_RE, FEATHER_GR, FEATHER_BL);

// Position and rotation modifiers and helpers
float dart_x = 0.0, dart_z = 0.0, animal_x = 0.0;

// Proc gen and animal selection helpers
int player_look = 1;
bool free_look = true, fire_gun = false, reload = true, regen = false;

// Game editing bools
bool solid_part = true;

// Gameplay mechanisms
float elevation = 0.0, frame = 3.0;
int darts = 10, dart_type = 0, score = 0;
bool game_over = false;

GLfloat door_height = 27.5;
bool shut_door = false;

GLfloat wall_height = 5.0;

vec3 door_loc[2] = {
  vec3(-37.5, 0.0, 0.0),
  vec3(-25.0, 0.0, -42.5)
};
GLfloat door_vert = 2.5;
GLfloat door_rot[2] = { 0, -90 };

GLfloat ghost_height[5] = { 0.0 };
vec3 ghost_loc = {
  vec3(-17.5, ghost_height[0], -5.0)
};
bool chase_ghost = false;

GLfloat zombie_height[6] = { 0.0 };
vec3 zombie_loc[3] = {
  vec3(10.0, zombie_height[0], 25.0),
  vec3(10.0, zombie_height[0], 35.0),
  vec3(15.0, zombie_height[0], 32.5)
};
bool chase_zombie[3] = { false };

bool draw_table = false;

GLfloat bookcase_z = { -45.0 };
GLfloat bookcase_x[2] = { 20.0, 30.0 };
bool bookcase_open = false;

bool displayed[10] = { false };

void open_door(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
    if (x - w / 2 < -25.0 &&
        x + w / 2 > -50.0 &&
        z - d / 2 < 40.0 &&
        z + d / 2 > 0.0 ) {
      if (!displayed[0]) {
        std::cout << "ROOM 1" << std::endl;
        displayed[0] = true;
      }
      // chase_ghost = true;
//       door_rot[0] = 0;
//       door_rot[1] = 90;
//       door_loc[0] = vec3(0.0, 0.0, 0.0);
//       door_loc[1] = vec3(0.0, 0.0, 0.0);
//     } else {
//       chase_ghost = false;
    }
  }

void werewolf_chase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
    if (x - w / 2 < -25.0 &&
        x + w / 2 > -50.0 &&
        z - d / 2 < 0.0 &&
        z + d / 2 > -50.0 ) {
      if (!displayed[1]) {
        std::cout << "ROOM 2" << std::endl;
        displayed[1] = true;
      }
//       chase_ghost = true;
//       door_rot[0] = 0;
//       door_rot[1] = 90;
//       door_loc[0] = vec3(0.0, 0.0, 0.0);
//       door_loc[1] = vec3(0.0, 0.0, 0.0);
//     } else {
//       chase_ghost = false;
    }
  }

void ghost_chase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
  if (x - w / 2 < 0.0 &&
      x + w / 2 > -25.0 &&
      z - d / 2 < 0.0 &&
      z + d / 2 > -50.0 ) {
    if (!displayed[2]) {
      std::cout << "ROOM 3" << std::endl;
      displayed[2] = true;
    }
    chase_ghost = true;
    // door_rot[0] = 0;
    // door_rot[1] = 90;
    // door_loc[0] = vec3(0.0, 0.0, 0.0);
    // door_loc[1] = vec3(0.0, 0.0, 0.0);
  } else {
    chase_ghost = false;
  }
}

void picture_fix(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
  if (x - w / 2 < 25.0 &&
      x + w / 2 > 0.0 &&
      z - d / 2 < 0.0 &&
      z + d / 2 > -25.0 ) {
    if (!displayed[3]) {
      std::cout << "ROOM 4" << std::endl;
      displayed[3] = true;
    }
      // chase_ghost = true;
//       door_rot[0] = 0;
//       door_rot[1] = 90;
//       door_loc[0] = vec3(0.0, 0.0, 0.0);
//       door_loc[1] = vec3(0.0, 0.0, 0.0);
//     } else {
      // chase_ghost = false;
    }
  }

void open_bookcase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
  if (x - w / 2 < 25.0 &&
      x + w / 2 > 0.0 &&
      z - d / 2 < -25.0 &&
      z + d / 2 > -50.0 ) {
    if (!displayed[4]) {
      std::cout << "ROOM 5" << std::endl;
      displayed[4] = true;
    }
    bookcase_open = true;
//     door_rot[0] = 0;
//     door_rot[1] = 90;
//     door_loc[0] = vec3(0.0, 0.0, 0.0);
//     door_loc[1] = vec3(0.0, 0.0, 0.0);
  } else {
    bookcase_open = false;
  }
}

void door_unlock(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
  if (x - w / 2 < 50.0 &&
      x + w / 2 > 25.0 &&
      z - d / 2 < -25.0 &&
      z + d / 2 > -50.0 ) {
    if (!displayed[5]) {
      std::cout << "ROOM 6" << std::endl;
      displayed[5] = true;
    }
//       chase_ghost = true;
//       door_rot[0] = 0;
//       door_rot[1] = 90;
//       door_loc[0] = vec3(0.0, 0.0, 0.0);
//       door_loc[1] = vec3(0.0, 0.0, 0.0);
//     } else {
//       chase_ghost = false;
    }
  }

void escape_agency(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
  if (x - w / 2 < 50.0 &&
      x + w / 2 > 25.0 &&
      z - d / 2 < 25.0 &&
      z + d / 2 > -25.0 ) {
    if (!displayed[6]) {
      std::cout << "ROOM 7" << std::endl;
      displayed[6] = true;
    }
//       chase_ghost = true;
//       door_rot[0] = 0;
//       door_rot[1] = 90;
//       door_loc[0] = vec3(0.0, 0.0, 0.0);
//       door_loc[1] = vec3(0.0, 0.0, 0.0);
//     } else {
//       chase_ghost = false;
    }
  }

void zombie_chase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d, bool *chase) {
  if (x - w / 2 < 25.0 &&
      x + w / 2 > -25.0 &&
      z - d / 2 < 40.0 &&
      z + d / 2 > 0.0 ) {
    if (!displayed[7]) {
      std::cout << "ROOM 8" << std::endl;
      displayed[7] = true;
    }
    *chase = true;
//     door_rot[0] = 0;
//     door_rot[1] = 90;
//     door_loc[0] = vec3(0.0, 0.0, 0.0);
//     door_loc[1] = vec3(0.0, 0.0, 0.0);
  } else {
    *chase = false;
  }
}

void confront_agency(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
  if (x - w / 2 < 50.0 &&
      x + w / 2 > 25.0 &&
      z - d / 2 < 40.0 &&
      z + d / 2 > 25.0 ) {
    if (!displayed[8]) {
      std::cout << "ROOM 9" << std::endl;
      displayed[8] = true;
    }
//       chase_ghost = true;
//       door_rot[0] = 0;
//       door_rot[1] = 90;
//       door_loc[0] = vec3(0.0, 0.0, 0.0);
//       door_loc[1] = vec3(0.0, 0.0, 0.0);
//     } else {
//       chase_ghost = false;
    }
  }

void door_shut(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
  if (x - w / 2 < 50.0 &&
      x + w / 2 > -50.0 &&
      z - d / 2 < 50.0 &&
      z + d / 2 > 40.0 ) {
    if (!displayed[9]) {
      std::cout << "ROOM 10" << std::endl;
      displayed[9] = true;
    }
    shut_door = true;
//     door_rot[0] = 0;
//     door_rot[1] = 90;
//     door_loc[0] = vec3(0.0, 0.0, 0.0);
//     door_loc[1] = vec3(0.0, 0.0, 0.0);
  } else {
    shut_door = false;
  }
}

// animation function, runs the updating of the variables
void animation(void) {

  static int step;

  if (frame >= 0.0 && frame <= 360.0) {
    if (step == 0 || step == 2) {

      if (frame == 0.0) frame = 1.0;
      if (frame == 360) step++;
      if (frame < 360) frame = frame + 1.0;
      for (int i = 0; i < 5; i++){
        ghost_height[i] = sin((frame - i)*M_PI/30);
      }

    } else if (step == 1 || step == 3) {

      if (frame == 0.0) step++;
      if (frame > 0) frame = frame - 1.0;
      for (int i = 0; i < 5; i++){
        ghost_height[i] = -sin((frame - i)*M_PI/30);
      }

    }

    if (fire_gun) dart_z -= 0.1; // RATE_GUN;
    else dart_z = 0.0;

  }

  if (step == 4) step = 0;

  if (dart_z < animal[player_look].z) {
    //dart_z = 0.0;
    if (dart_type == animal_det[player_look].x) {
      animal_health[player_look] = vec3(0.5, 0.5, 0.5); score++;
    } else if (dart_type > animal_det[player_look].x) {
      animal_health[player_look] = vec3(0.0, 0.0, 0.0); score--;
    } else if (dart_type < animal_det[player_look].x) {
      animal_health[player_look] = vec3(2.0, 2.0, 2.0); score--;
    }
  }

  if (free_look) {

    if (fire_gun) reload = false;
    else {
      reload = true;
      dart_x = 0.0;
    }

  } else {

    // x_len = player.x - animal[player_look].x - animal_x * mult;
    // y_len = player.z - animal[player_look].z;
    // hturn = (atan(x_len/(y_len + 0.01)) * 180 / M_PI);
    if (fire_gun){
      reload = false;
      dart_x = animal[player_look].x + animal_x;
    } else {
      reload = true;
      dart_x = 0.0;
    }

  }

  // if (mvz >= DRAW_DISTANCE) { mvz = -DRAW_DISTANCE; regen = true; }
  // if (mvz < -DRAW_DISTANCE) { mvz =  DRAW_DISTANCE; regen = true; }
  // if (mvx >= DRAW_DISTANCE) { mvx = -DRAW_DISTANCE; regen = true; }
  // if (mvx < -DRAW_DISTANCE) { mvx =  DRAW_DISTANCE; regen = true; }

  if (regen) {
    for (int k = 0; k < NUM_OF_ANIMALS; k++) {
      for (int j = NUM_EACH_ANIMAL * k; j < NUM_EACH_ANIMAL * (k + 1); j++) {
        animal[j].x = ((GLfloat) dist_x(mt) + 0.1);
        animal[j].z = ((GLfloat) dist_z(mt) + 0.1);
        animal_det[j].x = (GLfloat) k;
        animal_health[j] = vec3(1.0, 1.0, 1.0);
      }
    }
    regen = false;
  }

  if (darts == 0) exit(EXIT_SUCCESS);

  // static GLint lasttime = glutGet(GLUT_ELAPSED_TIME);
  // GLint time = glutGet(GLUT_ELAPSED_TIME);

  // if (rotatep) move_angle += 20.0 / 1000.0 * (time - lasttime);
  //
  // doorAngle += doorAngleIncr / 1000.0 * (time - lasttime);;
  // if (doorAngle > 60.0) doorAngleIncr *= -1.0;
  // if (doorAngle < 0.0) {
  //   doorAngle = 0.0;
  //   doorAngleIncr *= -1.0;
  // }
  //
  // // Do the animation code here in idle, not in display. Code for moving 2nd cube
  // trans += transinc / 1000.0 * ( time - lasttime );
  // if (trans > 1.5) { trans = 1.5; transinc *= -1; }
  // if (trans < -1.5) { trans = -1.5; transinc *= -1; }
  // lasttime=time;

  open_door(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  werewolf_chase(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  ghost_chase(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  picture_fix(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  open_bookcase(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  door_unlock(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  escape_agency(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  for (int i = 0; i < 3; i++) {
    zombie_chase(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D, &chase_zombie[i]);
  }
  confront_agency(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);
  door_shut(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);



  if (door_height > wall_height) {
    if (shut_door) { door_height -= 0.075; }
  }

  if (bookcase_z < -37.5) {
    if (bookcase_open) { bookcase_z += 0.075; }
  }

  if (bookcase_x[0] > 15.0) {
    if (bookcase_open) { bookcase_x[0] -= 0.075; }
  }

  if (bookcase_x[1] < 35.0) {
    if (bookcase_open) { bookcase_x[1] += 0.075; }
  }

  if (chase_ghost) {
    if (ghost_loc.x != mvx) {
      if (ghost_loc.x - mvx < 0) {
        ghost_loc.x += 0.1;
      }
      if (ghost_loc.x - mvx > 0) {
        ghost_loc.x -= 0.1;
      }
    }
    if (ghost_loc.z != mvz) {
      if (ghost_loc.z - mvz < 0) {
        ghost_loc.z += 0.1;
      }
      if (ghost_loc.z - mvz > 0) {
        ghost_loc.z -= 0.1;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    if (chase_zombie[i]) {
      if (zombie_loc[i].x != mvx) {
        if (zombie_loc[i].x - mvx < 0) {
          zombie_loc[i].x += 0.1;
        }
        if (zombie_loc[i].x - mvx > 0) {
          zombie_loc[i].x -= 0.1;
        }
      }
      if (zombie_loc[i].z != mvz) {
        if (zombie_loc[i].z - mvz < 0) {
          zombie_loc[i].z += 0.1;
        }
        if (zombie_loc[i].z - mvz > 0) {
          zombie_loc[i].z -= 0.1;
        }
      }
    }
  }

  for (int i = 0; i < NUM_ENEMIES; i++) {
    if (die[i]) death = true;// exit(EXIT_FAILURE);
  }

  title_bar = "Score: " + std::to_string(mvx) + "                    Darts: " + std::to_string(mvz); // + " l:" + std::to_string(l) + " r:" + std::to_string(r) + " f:" + std::to_string(f) + " b:" + std::to_string(b);

  for (int i = 0; i < 256; i++) {

    if (key_buffer[i]){
      switch (i) {
        // Escape Key
        case 033:

          break;
        case 'q': case 'Q':
          exit(EXIT_SUCCESS);
          break;
        // Walking
        case 'w': { mvz -= /*RATE_PLAYER +*/ sin(theta*M_PI/180)/2; mvx -= /*RATE_PLAYER +*/ cos(theta*M_PI/180)/2; } break; //wire
        case 's': { mvz += /*RATE_PLAYER +*/ sin(theta*M_PI/180)/2; mvx += /*RATE_PLAYER +*/ cos(theta*M_PI/180)/2; } break; //wire
        case 'a': { mvx -= /*RATE_PLAYER +*/ sin(theta*M_PI/180)/2; mvz += /*RATE_PLAYER +*/ cos(theta*M_PI/180)/2; } break; //wire
        case 'd': { mvx += /*RATE_PLAYER +*/ sin(theta*M_PI/180)/2; mvz -= /*RATE_PLAYER +*/ cos(theta*M_PI/180)/2; } break; //wire
        // Shoot
        case ' ': { if (reload) { fire_gun = true; darts--; } } break; //fire
        // Dart Selection
        case '1': { feather = vec3(0.33, 1.0, 0.5); dart_type = 0; } break; //small dart
        case '2': { feather = vec3(1.0, 0.5, 0.25); dart_type = 1; } break; //med dart
        case '3': { feather = vec3(0.35, 0.0, 0.5); dart_type = 2; } break; //large dart
        // Camera Lock
        case '`': free_look = !free_look; break; //fire
        // Camera Change
        case 'c': perspective = !perspective; break; //fire
        // Utility
        case 'W': { solid_part = !solid_part; } break; //wire
        case 'z': zNear *= 1.1; zFar /= 1.1; break;
        case 'Z': zNear /= 1.1; zFar *= 1.1; break;
        case 'r': radius *= 1.5; break;
        case 'R': radius /= 1.5; break;
        case 'v': fovy -= 5; if (fovy < 0) { fovy = 1; } break;
        case 'V': fovy += 5; /* break; */ if (fovy > 179) { fovy = 179; } break;
        case '~':  // reset
          rotatep =! rotatep;
          zNear = 0.1; zFar = 300.0;
          radius = 3.0;
          theta = 0.0; phi = 0.0;
          break;
        default: { } break; // Default

      }
    } else {
      switch (i) {
        case ' ': fire_gun = false; break; // Stop firing, not the same as bullet landing
      }
    }

    if (spec_buffer[i]) {
      switch (i) {
        case GLUT_KEY_RIGHT: theta += dr; break; // Look angle right
        case GLUT_KEY_LEFT:  theta -= dr; break; // Look angle left
        case GLUT_KEY_DOWN:  phi += dr;   break; // Look angle down
        case GLUT_KEY_UP:    phi -= dr;   break; // Look angle up
      }
    }

  }

  glutPostRedisplay();

}

// menu_select function, functions for menu click
void menu_select(int mode) {

  switch (mode) {
    case 1: ; break;
    case 2: glutIdleFunc(NULL); break;
    case 3: /* solid_part = !solid_part; */ glutPostRedisplay(); break;
    case 4: exit(EXIT_SUCCESS);
  }

}

// null_select function, function for menu items that dont do anything
void null_select(int mode) { }

// glutMenu function, menu generating function
void glutMenu(void) {

  int glut_menu[3];

  glut_menu[1] = glutCreateMenu(null_select);
  glutAddMenuEntry("start : tilde", 0);
  glutAddMenuEntry("right : right arrow", 0);
  glutAddMenuEntry("left  : left arrow", 0);
  glutAddMenuEntry("down  : up arrow", 0);
  glutAddMenuEntry("up    : down arrow", 0);

  glut_menu[2] = glutCreateMenu(null_select);
  glutAddMenuEntry("start  : x", 0);
  glutAddMenuEntry("fire   : space", 0);
  glutAddMenuEntry("weak   : 1", 0);
  glutAddMenuEntry("medium : 2", 0);
  glutAddMenuEntry("strong : 3", 0);

  glut_menu[0] = glutCreateMenu(NULL);
  glutAddSubMenu("freelook", glut_menu[1]);
  glutAddSubMenu("operate the gun", glut_menu[2]);

  glutCreateMenu(menu_select);
  glutAddMenuEntry("Start", 1);
  glutAddMenuEntry("Stop", 2);
  // glutAddMenuEntry("Toggle Wireframe", 3);
  glutAddSubMenu("How to...", glut_menu[0]);
  glutAddMenuEntry("Quit", 4);
  // glutAttachMenu(GLUT_LEFT_BUTTON);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

}

#endif
