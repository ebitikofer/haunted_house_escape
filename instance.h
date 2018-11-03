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
bool free_look = true, fire = false, reload = true, regen = false;

// Game editing bools
bool solid_part = true;

// Gameplay mechanisms
float elevation = 0.0, frame = 3.0;
int darts = 10, dart_type = 0, score = 0;
bool game_over = false;

// animation function, runs the updating of the variables
void animation(void) {

  static int step;

  if (frame >= 0.0 && frame <= 314.0) {
    if (step == 0 || step == 2) {

      if (frame == 0.0) frame = 1.0;
      if (frame == 314) step++;
      if (frame < 314) frame = frame + 1.0;
      animal_x = 7.0 * sin(frame/100);

    } else if (step == 1 || step == 3) {

      if (frame == 0.0) step++;
      if (frame > 0) frame = frame - 1.0;
      animal_x = 7.0 * -sin(frame/100);

    }

    if (fire) dart_z -= 0.1; // RATE_GUN;
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

    if (fire) reload = false;
    else {
      reload = true;
      dart_x = 0.0;
    }

  } else {

    // x_len = player.x - animal[player_look].x - animal_x * mult;
    // y_len = player.z - animal[player_look].z;
    // hturn = (atan(x_len/(y_len + 0.01)) * 180 / M_PI);
    if (fire){
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

  title_bar = "Score: " + std::to_string(collide[0]) + "                    Darts: " + std::to_string(mvz);

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
        case ' ': { if (reload) { fire = true; darts--; } } break; //fire
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
        case ' ': fire = false; break; // Stop firing, not the same as bullet landing
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
