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

// Which entity will the mouse control (see list above), initally the
// Head2 angle.
// GLint angle = Head2;

// Viewing transformation parameters
GLfloat radius = 3.0;
GLfloat theta = 0.0;
GLfloat phi = 0.0;
GLfloat pitch = 3.0;
GLfloat yaw = 0.0;
GLfloat roll = 0.0;


const GLfloat dr = 0.1; // 5.0 * DegreesToRadians;

bool moving = false;
GLfloat axial = 0.0;
GLfloat strafe = 0.0;

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
int x_len = 0, y_len = 0;

// Proc gen and animal selection helpers
int player_look = 1;
bool free_look = true, fire = false, reload = true, regen = false;

// Game editing bools
bool solid_part = true;

// Movement
int hturn = 0, vturn = 0;
bool forward = false, backward = false, left = false, right = false;

// Gameplay mechanisms
float elevation = 0.0, z_distance = 0.0, x_distance = 0.0, frame = 3.0;
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

    if (fire)
      dart_z -= 0.1; // RATE_GUN;
    else
      dart_z = 0.0;

  }

  if (step == 4)
    step = 0;

  if (dart_z < animal[player_look].z) {
    //dart_z = 0.0;
    if (dart_type == animal_det[player_look].x) {
      animal_health[player_look] = vec3(0.5, 0.5, 0.5);
      score++;
    } else if (dart_type > animal_det[player_look].x) {
      animal_health[player_look] = vec3(0.0, 0.0, 0.0);
      score--;
    } else if (dart_type < animal_det[player_look].x) {
      animal_health[player_look] = vec3(2.0, 2.0, 2.0);
      score--;
    }
  }

  float mult = 1.0;

  switch (player_look / NUM_EACH_ANIMAL) {
    case 0: mult = 2.0; break;
    case 1: mult = 1.5; break;
    case 2: mult = 0.75; break;
  }

  if (free_look) {

    if (fire) reload = false;
    else {
      reload = true;
      dart_x = 0.0;
    }

  } else {

    x_len = player.x - animal[player_look].x - animal_x * mult;
    y_len = player.z - animal[player_look].z;
    hturn = (atan(x_len/(y_len + 0.01)) * 180 / M_PI);
    if (fire){
      reload = false;
      dart_x = animal[player_look].x + animal_x;
    } else {
      reload = true;
      dart_x = 0.0;
    }

  }

  if (z_distance >= DRAW_DISTANCE) { z_distance = -DRAW_DISTANCE; regen = true; }
  if (z_distance < -DRAW_DISTANCE) { z_distance =  DRAW_DISTANCE; regen = true; }
  if (x_distance >= DRAW_DISTANCE) { x_distance = -DRAW_DISTANCE; regen = true; }
  if (x_distance < -DRAW_DISTANCE) { x_distance =  DRAW_DISTANCE; regen = true; }

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

  // if (forward) distance -= 0.1678;
  // if (backward) distance += 0.1678;

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
        case 'w': { z_distance -= RATE_PLAYER; mvz -= RATE_PLAYER; forward = true; i++; } break; //wire
        case 's': { z_distance += RATE_PLAYER; mvz += RATE_PLAYER; backward = true; i++; } break; //wire
        case 'a': { x_distance -= RATE_PLAYER; mvx -= RATE_PLAYER; left = true; i++; } break; //wire
        case 'd': { x_distance += RATE_PLAYER; mvx += RATE_PLAYER; right = true; i++; } break; //wire
        // Shoot
        case ' ': { if (reload) { fire = true; darts--; } i++; } break; //fire
        // Dart Selection
        case '1': { feather = vec3(0.33, 1.0, 0.5); dart_type = 0; i++; } break; //small dart
        case '2': { feather = vec3(1.0, 0.5, 0.25); dart_type = 1; i++; } break; //med dart
        case '3': { feather = vec3(0.35, 0.0, 0.5); dart_type = 2; i++; } break; //large dart
        // Camera Lock
        case '`': { free_look = !free_look; i++; } break; //fire
        // Game start
        case 'x': { glutIdleFunc(animation); i++; } break;
        // Utility
        case 'W': { solid_part = !solid_part; i++; } break; //wire
        // Default
        default: { forward = false; backward = false; i++; } break; //wire

        case 'z': zNear  *= 1.1; zFar /= 1.1; break;
        case 'Z': zNear /= 1.1; zFar *= 1.1; break;
        case 'r': radius *= 1.5; break;
        case 'R': radius /= 1.5; break;
        case 'o': theta += dr; break;
        case 'O': theta -= dr; break;
        case 'p': phi += dr; break;
        case 'P': phi -= dr; break;
        case 'v':
          fovy-=5;
          if (fovy < 0) {
            // Min angle of view 1 degree
            fovy = 1;
          }
          break;
        case 'V': fovy+=5; break;
          if (fovy > 179) {
            // Max angle of view 179 degrees
            fovy = 179;
          }
          break;

        case '~':  // reset values to their defaults
          rotatep=!rotatep;
          //    zNear = 0.1;
          //    zFar = 300.0;
          zNear = 0.5;
          zFar = 3.0;

          radius = 3.0;
          theta  = 0.0;
          phi    = 0.0;
          break;
      }
    } else {
      switch (i) {
        // Unshoot
        case ' ': { fire = false; } break; //fire
      }
    }

    if (spec_buffer[i]) {
      switch (i) {
        // View Position
        case GLUT_KEY_RIGHT: theta += dr; { if(free_look) hturn = (hturn - RATE_CAMERA_H) % 360; else if (player_look > 0) player_look--; i++; } break;
        case GLUT_KEY_LEFT:  theta -= dr; { if(free_look) hturn = (hturn + RATE_CAMERA_H) % 360; else if (player_look < (NUM_OF_ANIMALS * NUM_EACH_ANIMAL) - 1) player_look++; i++; } break;
        case GLUT_KEY_DOWN:  phi += dr;   { if (free_look) { vturn = (vturn - RATE_CAMERA_V) % 360; i++; } } break;
        case GLUT_KEY_UP:    phi -= dr;   { if (free_look) { vturn = (vturn + RATE_CAMERA_V) % 360; i++; } } break;
      }
    }

  }

  if (darts == 0) exit(EXIT_SUCCESS);

  // Perspective view of a color cube using LookAt() and Perspective()
  // Separated the transform for the camera (camera_view) from the object (model_view).

  // Added code to account for glutElapsedTime
  static GLint lasttime = glutGet(GLUT_ELAPSED_TIME);
  GLint time = glutGet(GLUT_ELAPSED_TIME);

  // Code to animate cube goes here.
  if (rotatep) {
    move_angle += 20.0 / 1000.0 * (time - lasttime);
  }

  doorAngle += doorAngleIncr / 1000.0 * (time - lasttime);;
  if (doorAngle > 60.0) {
    doorAngleIncr *= -1.0;
  }
  if (doorAngle < 0.0){
    doorAngle = 0.0;
    doorAngleIncr *= -1.0;
  }

  // Do the animation code here in idle, not in display.
  //  Code for moving 2nd cube
  trans += transinc / 1000.0 * ( time - lasttime );
  if (trans > 1.5) {
    trans = 1.5;
    transinc *= -1;
  }
  if (trans < -1.5) {
    trans = -1.5;
    transinc *= -1;
  }
  lasttime=time;

  title_bar = "Score: " + std::to_string(score) + "                    Darts: " + std::to_string(darts);

  glutPostRedisplay();

}

// menu_select function, functions for menu click
void menu_select(int mode) {

  switch (mode) {
    case 1: glutIdleFunc(animation); break;
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
