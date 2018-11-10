#ifndef INSTANCE_H
#define INSTANCE_H

#include <Angel.h>
#include "models.h"

// Motion rates
#define RATE_PLAYER	  0.5
#define RATE_GUN	    1

// Game object locations
vec3 player = vec3(0.0, 0.0, 6.0);

// Color vec3s
vec3 sky = vec3(0.8, 1.0, 1.0);
vec3 feather = vec3(FEATHER_RE, FEATHER_GR, FEATHER_BL);

float dart_x = 0.0, dart_z = 0.0;
bool fire_gun = false, reload = true, action = false;
float elevation = 0.0, frame = 3.0;
int darts = 10, score = 0;
bool solid_part = true, game_over = false;


GLfloat ghost_height[5] = { 0.0 },
        bookcase_x[2] = { 20.0, 30.0 },
        zombie_height[6] = { 0.0 };

GLfloat wall_height = 5.0,
        door_vert = 2.5,
        ghost_mult = 1.0,
        bookcase_z = -45.0,
        dizziness = 0.0,
        nausea = 0.0,
        zombie_mult[NUM_ZOMBIES] = { 1.0 },
        door_height = 27.5,
        speed_boost = 1.0;

vec3 zombie_loc[NUM_ZOMBIES] = {
  vec3(10.0, zombie_height[0], 25.0),
  vec3(10.0, zombie_height[0], 35.0),
  vec3(15.0, zombie_height[0], 32.5)
};

vec3 agency_loc = vec3(-51.0, 0.0, 10.0),
     ghost_loc = vec3(-17.5, ghost_height[0], -5.0),
     picture_loc = vec3(12.5, 0.0, -1.0);

int picture_rot = 225, flicker = 0, door_open[NUM_DOORS] = { 0 };

bool draw_table = false,
     open_door[NUM_DOORS] = { false },
     werewolf_chase = false,
     ghost_chase = false,
     get_sweeper = false,
     kill_ghost = false,
     sweep_ghost = false,
     fix_picture = false,
     lose_power = false,
     bookcase_open = false,
     //light_fire = false,
     get_key = false,
     agency_chase = false,
     zombie_chase = false,
     get_gun = false,
     kill_zombie[3] = { false },
     //hit_glass = false,
     get_coffee = false,
     shut_door = false;

bool rooms[NUM_ROOMS] = { false };
bool displayed[NUM_ROOMS] = { false };
vec4 bounds[NUM_ROOMS] = {
  vec4(-25.0, -50.0, 40.0, 0.0),
  vec4(-25.0, -50.0, 0.0, -50.0),
  vec4(0.0, -25.0, 0.0, -50.0),
  vec4(25.0, 0.0, 0.0, -25.0),
  vec4(25.0, 0.0, -25.0, -50.0),
  vec4(50.0, 25.0, -25.0, -50.0),
  vec4(50.0, 25.0, 25.0, -25.0),
  vec4(25.0, -25.0, 40.0, 0.0),
  vec4(50.0, 25.0, 40.0, 25.0),
  vec4(50.0, -50.0, 50.0, 40.0)
};

// void open_door(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void werewolf_chase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void ghost_chase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void picture_fix(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void open_bookcase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void door_unlock(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void escape_agency(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void zombie_chase(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void confront_agency(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)
// void door_shut(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d)

void set_room(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d){
  for (int i = 0; i < NUM_ROOMS; i++) {
    if (x - w / 2 < bounds[i].x &&
        x + w / 2 > bounds[i].y &&
        z - d / 2 < bounds[i].z &&
        z + d / 2 > bounds[i].w ) {
      if (!displayed[i]) {
        std::cout << "ROOM" << (i + 1) << std::endl;
        displayed[i] = true;
      }
      rooms[i] = true;
    } else {
      displayed[i] = false;
      rooms[i] = false;
    }
  }
}

// animation function, runs the updating of the variables
void animation(void) {

  static int step;

  set_room(mvx, 0.0, mvz, PLAYER_W, PLAYER_H, PLAYER_D);

  if (rooms[0]) {
    if (doors[0]){
      if (action) {
        open_door[0] = true;
      }
    }
  } else { }

  if (rooms[1]) {
    if (doors[1]){
      if (action) {
        open_door[1] = true;
      }
    }
  } else { }

  if (rooms[2]) {
    ghost_chase = true;
    if (pickup[0]){
      get_sweeper = true;
    }
    if (doors[2]){
      if (action) {
        open_door[2] = true;
      }
    }
  }
  else { ghost_chase = false; }

  if (rooms[3]) {
    if (proximal[2]){
      if (action) {
        fix_picture = true;
      }
    }
    if (doors[3]){
      if (action) {
        open_door[3] = true;
      }
    }
  } else {
    lose_power = false;
  }

  if (rooms[4]) {
    agency_loc = vec3(12.5, 0.0, -51.0);
    if (proximal[3]){
      if (action) {
        bookcase_open = true;
      }
    }
  } else {
    bookcase_open = false;
  }

  if (rooms[5]) {
    if (pickup[1]){
      get_key = true;
    }
    if (doors[4]){
      if (action) {
        open_door[4] = true;
      }
    }
  } else { }

  if (rooms[6]) {
    if (!agency_chase) {
      agency_loc = vec3(45.0, 0.0, 15.0);
    }
    hallucinate = true;
    agency_chase = true;
    dizziness = sickness(mt);
    nausea += 0.001 + dizziness;
    phi = 25 * -sin(nausea *180/M_PI);
    theta = -90 + 25 * cos((nausea *180/M_PI)/2);
    if (doors[5]){
      if (action) {
        open_door[5] = true;
      }
    }
  } else {
    hallucinate = false;
    agency_chase = false;
  }

  if (rooms[7]) {
    zombie_chase = true;
    if (pickup[2]){
      get_gun = true;
    }
    if (doors[6]){
      if (action) {
        open_door[6] = true;
      }
    }
  }
  else { zombie_chase = false; }

  if (rooms[8]) {
    agency_loc = vec3(51.0, 0.0, 30.0);
    if (doors[7]){
      if (action) {
        open_door[7] = true;
      }
    }
  } else { }

  if (rooms[9]) {
    shut_door = true;
    if (pickup[3]){
      get_coffee = true;
    }
  }
  else { shut_door = false; }

  if (frame >= 0.0 && frame <= 360.0) {
    if (step == 0 || step == 2) {

      if (frame == 0.0) frame = 1.0;
      if (frame == 360) step++;
      if (frame < 360) frame = frame + 1.0;
      for (int i = 0; i < 5; i++){
        ghost_height[i] = sin((frame - i)*M_PI/30);
      }

      if (lose_power && flicker < 7) {
        light1 = !light1;
        glUniform1i(Light1,light1);
        flicker++;
      }

      if (lose_power && flicker >= 7 && flicker < 15) {
        flicker++;
        agency_loc = vec3(12.5, 0.0, -12.5);
      }

      if (lose_power && flicker >= 15) {
        light1 = false;
        glUniform1i(Light1,light1);
        light2 = false;
        glUniform1i(Light2,light2);
      }

    } else if (step == 1 || step == 3) {

      if (frame == 0.0) step++;
      if (frame > 0) frame = frame - 1.0;
      for (int i = 0; i < 5; i++){
        ghost_height[i] = -sin((frame - i)*M_PI/30);
      }

      if (lose_power && flicker < 7) {
        light2 = !light2;
        glUniform1i(Light2,light2);
        flicker++;
      }

    }

    if (fire_gun) dart_z -= 0.1; // RATE_GUN;
    else dart_z = 0.0;

  }

  if (step == 4) step = 0;

  if (fire_gun)
    reload = false;
  else {
    reload = true;
    dart_x = 0.0;
  }

  // if (mvz >= DRAW_DISTANCE) { mvz = -DRAW_DISTANCE; regen = true; }
  // if (mvz < -DRAW_DISTANCE) { mvz =  DRAW_DISTANCE; regen = true; }
  // if (mvx >= DRAW_DISTANCE) { mvx = -DRAW_DISTANCE; regen = true; }
  // if (mvx < -DRAW_DISTANCE) { mvx =  DRAW_DISTANCE; regen = true; }

  // static GLint lasttime = glutGet(GLUT_ELAPSED_TIME);
  // GLint time = glutGet(GLUT_ELAPSED_TIME);
  // if (rotatep) move_angle += 20.0 / 1000.0 * (time - lasttime);
  // doorAngle += doorAngleIncr / 1000.0 * (time - lasttime);
  // if (doorAngle > 60.0) doorAngleIncr *= -1.0;
  // if (doorAngle < 0.0) { doorAngle = 0.0; doorAngleIncr *= -1.0; }
  // // Do the animation code here in idle, not in display. Code for moving 2nd cube
  // trans += transinc / 1000.0 * ( time - lasttime );
  // if (trans > 1.5) { trans = 1.5; transinc *= -1; }
  // if (trans < -1.5) { trans = -1.5; transinc *= -1; }
  // lasttime=time;

  if (darts == 0) exit(EXIT_SUCCESS);

  for (int i = 0; i < NUM_DOORS; i++) {
    if (door_open[i] < 90) {
      if (open_door[i]) { door_open[i] += 1; }
    }
  }

  if (ghost_chase) {
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

  if (get_sweeper) {
    if (g_die[0]) kill_ghost = true;
  } else {
    if (g_die[0]) death = true;// exit(EXIT_FAILURE);
  }

  if (kill_ghost) {
    if (ghost_mult >= 0.0) {
      ghost_mult -= 0.01;
    }
  }

  if (picture_rot < 270) {
    if (fix_picture) { picture_rot += 1; }
  } else {
    lose_power = true;
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

  if (get_key) {

  }

  if (agency_chase) {
    if (agency_loc.x != mvx) {
      if (agency_loc.x - mvx < 0) {
        agency_loc.x += 0.1;
      }
      if (agency_loc.x - mvx > 0) {
        agency_loc.x -= 0.1;
      }
    }
    if (agency_loc.z != mvz) {
      if (agency_loc.z - mvz < 0) {
        agency_loc.z += 0.1;
      }
      if (agency_loc.z - mvz > 0) {
        agency_loc.z -= 0.1;
      }
    }
  }

  if (zombie_chase) {
    for (int i = 0; i < 3; i++) {
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

  if (get_gun) {
    for (int i = 0; i < NUM_ZOMBIES; i++) {
      if (z_die[i]) kill_zombie[i] = true;
    }
  } else {
    if (z_die[0] || z_die[1] || z_die[2]) death = true;// exit(EXIT_FAILURE);
  }

  for (int i = 0; i < NUM_ZOMBIES; i++) {
    if (kill_zombie[i]) {
      if (zombie_mult[i] >= 0.0) {
        zombie_mult[i] -= 0.01;
      }
    }
  }

  if (door_height > wall_height) {
    if (shut_door) { door_height -= 0.075; }
  }

  if (get_coffee) {
    speed_boost = 2.0;
  }

  title_bar = "Score: " + std::to_string(theta) + " Darts: " + std::to_string(phi) + " bool: " + std::to_string(pickup[1]); // + " l:" + std::to_string(l) + " r:" + std::to_string(r) + " f:" + std::to_string(f) + " b:" + std::to_string(b);

  for (int i = 0; i < 256; i++) {

    if (key_buffer[i]){
      switch (i) {
        case 033: { } break; // Escape Key
        case 'Q': exit(EXIT_SUCCESS); break; // Quit
        case 'w': { mvz -= speed_boost * sin(theta*M_PI/180)/2; mvx -= speed_boost * cos(theta*M_PI/180)/2; } break;
        case 's': { mvz += speed_boost * sin(theta*M_PI/180)/2; mvx += speed_boost * cos(theta*M_PI/180)/2; } break;
        case 'a': { mvx -= speed_boost * sin(theta*M_PI/180)/2; mvz += speed_boost * cos(theta*M_PI/180)/2; } break;
        case 'd': { mvx += speed_boost * sin(theta*M_PI/180)/2; mvz -= speed_boost * cos(theta*M_PI/180)/2; } break;
        case 'f': { action = true; } break; // Action
        case ' ': { if (reload) { fire_gun = true; darts--; } } break; // Shoot
        case '1': { hallucinate = !hallucinate; } break; // Weapon 1
        case '2': { } break; // Weapon 2
        case '3': { } break; // Weapon 3
        case 'c': perspective = !perspective; break; //fire
        // Utility
        case '-': light1 = !light1; glUniform1i(Light1,light1); break;
        case '=': light2 = !light2; glUniform1i(Light2,light2); break;
        case 'W': { solid_part = !solid_part; } break; //wire
        case 'z': zNear *= 1.1; zFar /= 1.1; break;
        case 'Z': zNear /= 1.1; zFar *= 1.1; break;
        case 'r': radius *= 1.5; break;
        case 'R': radius /= 1.5; break;
        case 'v': fovy -= 5; if (fovy < 0) { fovy = 1; } break;
        case 'V': fovy += 5; /* break; */ if (fovy > 179) { fovy = 179; } break;
        case '~': zNear = 0.1; zFar = 300.0; radius = 3.0; theta = 0.0; phi = 0.0; break; // reset
        case '`': { } break;
        default: { } break; // Default

      }
    } else {
      switch (i) {
        case ' ': fire_gun = false; break; // Stop firing, not the same as bullet landing
        case 'f': { action = false; } break; //wire
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
