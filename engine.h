#ifndef ENGINE_H
#define ENGINE_H

#include <Angel.h>
#include <chrono>
#include <random>

// Screen dimensions
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
// Drawing
#define DRAW_DISTANCE 20.0
// Trig
#ifndef M_PI
#define M_PI 3.141592654
#endif

// Motion rates
#define RATE_CAMERA_H	4
#define RATE_CAMERA_V	2

const int NumVertices = 36; // (6 faces)(2 triangles/face)(3 vertices/triangle)
const int NumNodes = 11;
const int NumAngles = 11;

// glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Position

// glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Direction
// glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

// glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Right Axis
// glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

// glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); // Up Axis

// glm::mat4 view; // Look At
// view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
//   		   glm::vec3(0.0f, 0.0f, 0.0f),
//   		   glm::vec3(0.0f, 1.0f, 0.0f));

// float radius = 10.0f;
// float camX = sin(glfwGetTime()) * radius;
// float camZ = cos(glfwGetTime()) * radius;
// glm::mat4 view;
// view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

// glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

point4 points[NumVertices];
color4 colors[NumVertices];

GLUquadricObj *qobj; // For drawing cylinders

GLuint camera_view;  // camera-view matrix uniform shader variable location
GLuint model_view;  // model-view matrix uniform shader variable location
GLuint projection; // projection matrix uniform shader variable location

mat4 p;
mat4 mv;
mat4 cv;
mat4 pv;

// Globals to control moving around a scene.
GLfloat mvx = 0.0;
GLfloat mvz = 0.0;

// Projection transformation parameters
GLfloat fovy = 45.0;  // Field-of-view in Y direction angle (in degrees)
GLfloat zNear = 0.5, zFar = 50.0; //GLfloat zNear = 0.1, zFar = 300.0;

GLfloat aspect; // Viewport aspect ratio

// Title bar modifiers
std::string title_bar;

int Index = 0; // Global to keep track of what vertex we are setting.

bool key_buffer[256] = { false };
bool spec_buffer[256] = { false };

bool display_bool = false;

// Random
uint64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::seed_seq ss{ uint32_t( seed & 0xffffffff ), uint32_t( seed >> 32 ) };
std::mt19937 mt(ss);
std::uniform_real_distribution<double> dist_x(-7.0, 7.0);
std::uniform_real_distribution<double> dist_z(-10.0, -6.0);

color4 vertex_colors[8] = {

    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(1.0, 0.0, 1.0, 1.0),  // magenta
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(0.0, 1.0, 1.0, 1.0)   // cyan

};

point4 vertices[8] = {

    point4(-0.5, -0.5,  0.5, 1.0),
    point4(-0.5,  0.5,  0.5, 1.0),
    point4( 0.5,  0.5,  0.5, 1.0),
    point4( 0.5, -0.5,  0.5, 1.0),
    point4(-0.5, -0.5, -0.5, 1.0),
    point4(-0.5,  0.5, -0.5, 1.0),
    point4( 0.5,  0.5, -0.5, 1.0),
    point4( 0.5, -0.5, -0.5, 1.0)

};

// MyQuad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d) {

  colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
  colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
  colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
  colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
  colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
  colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;

}

// generate 12 triangles: 36 vertices and 36 colors
void cube() {

  quad(1, 0, 3, 2);
  quad(2, 3, 7, 6);
  quad(3, 0, 4, 7);
  quad(6, 5, 1, 2);
  quad(4, 5, 6, 7);
  quad(5, 4, 0, 1);

}

//
void object(mat4 matrix, GLuint uniform, GLfloat x, GLfloat y, GLfloat z,GLfloat w, GLfloat h, GLfloat d, int pitch, int yaw, int roll, int sl, int st, int type) {

    mat4 instance = (
      Translate( x, y, z )
      * RotateX(pitch) * RotateY(yaw) * RotateZ(roll)
    );
    switch (type) {
      case 0:
        glUniformMatrix4fv( uniform, 1, GL_TRUE, matrix * instance * Scale( w, h, d ) );
        glDrawArrays( GL_TRIANGLES, 0, NumVertices );
        break;
      case 1:
        glUniformMatrix4fv( uniform, 1, GL_TRUE, matrix * instance );
        gluCylinder(qobj, w, d, h, sl, st); break;
    };

}

// keyboard function, keyboard callback for key down functionality
void keyboard(unsigned char key, int x, int y) { key_buffer[key] = true; }

// keyboardUp function, keyboard callback for key up functionality
void keyboardUp(unsigned char key, int x, int y) { key_buffer[key] = false; }

// special function, special callback for special key down functionality
void special(int key, int x, int y) { spec_buffer[key] = true; }

// specialUp function, special callback for special key up functionality
void specialUp(int key, int x, int y) { spec_buffer[key] = false; }

// myReshape function, reshapes the window when resized
void reshape(int width, int height) {

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // gluPerspective(100.0, (GLfloat) w / (GLfloat) h, 1.0, 30.0);
  gluPerspective(65.0, (GLfloat) width / (GLfloat) height, 1.0, 5.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // glTranslatef(0.0, 1.2, -5.5);  /* viewing transform  */

  aspect = GLfloat(width)/height;

}

// init function, initializes the drawables and GL_DEPTH_TEST
void init(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  glutCreateWindow( "SEDATIVE FELLA" );
  glutReshapeFunc(reshape);

  glewExperimental = GL_TRUE;
  glewInit();

  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialUp);

  // int j = 0, k = 0;

  qobj = gluNewQuadric();

  cube();

  // Drawables(solid_part);

  // for (k = 0; k < NUM_OF_ANIMALS; k++) {
  //   for (j = NUM_EACH_ANIMAL * k; j < NUM_EACH_ANIMAL * (k + 1); j++) {
  //     animal[j].x = ((GLfloat) dist_x(mt) + 0.1);
  //     animal[j].z = ((GLfloat) dist_z(mt) + 0.1);
  //     animal_det[j].x = (GLfloat) k;
  //     animal_health[j] = vec3(1.0, 1.0, 1.0);
  //   }
  // }

  // Create a vertex array object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create and initialize a buffer object
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("shaders/vshader.glsl", "shaders/fshader.glsl");
  glUseProgram(program);

  // // set up vertex arrays
  GLuint vPosition = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  GLuint vColor = glGetAttribLocation(program, "vColor");
  glEnableVertexAttribArray(vColor);
  glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

  model_view = glGetUniformLocation(program, "model_view");
  camera_view = glGetUniformLocation(program, "camera_view");
  projection = glGetUniformLocation(program, "projection");

  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0, 1.0, 1.0, 1.0);

}

#endif
