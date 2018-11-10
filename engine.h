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

#define NUM_OBJECTS	38
#define NUM_DOORS	8
#define NUM_BOOKCASE	10
#define NUM_ENEMIES	4
#define NUM_GHOSTS	1
#define NUM_ZOMBIES	3
#define NUM_WEREWOLVES	4
#define NUM_AGENCIES	3
#define NUM_TABLES	4
#define NUM_INTERACTABLES	4
#define NUM_PICKUPS	4
#define NUM_ROOMS 10

enum cardinal{ north, south, east, west };

const int NumVertices = 36; // (6 faces)(2 triangles/face)(3 vertices/triangle)
const int NumNodes = 11;
const int NumAngles = 11;

const int NumTimesToSubdivide = 5;
const int NumTriangles        = 4096;  // (4 faces)^(NumTimesToSubdivide + 1)
const int NumVertices2        = 3 * NumTriangles;


typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

point4 points[NumVertices];
color4 colors[NumVertices];

point4 points2[NumVertices2];
vec4   normals[NumVertices2];

GLUquadricObj *qobj;  // For drawing cylinders

GLuint camera_view;   // camera-view matrix uniform shader variable location
GLuint model_view;    // model-view matrix uniform shader variable location
GLuint projection;    // projection matrix uniform shader variable location
GLuint color_change;  // projection matrix uniform shader variable location
GLuint enable;  // projection matrix uniform shader variable location
GLuint ambient_product;
GLuint diffuse_product;
GLuint specular_product;
GLuint ambient_product2;
GLuint diffuse_product2;
GLuint specular_product2;

mat4 p, mv, cv, pv;   // shader variables
vec4 cc;

// Globals to control moving around a scene.
GLfloat mvx = -37.5; // Start in furthest room
GLfloat mvz = 30.0;
// GLfloat mvx = -50.0; // Start at door
// GLfloat mvz = 45.0;

// Projection transformation parameters
GLfloat fovy = 65.0;  // Field-of-view in Y direction angle (in degrees)
GLfloat zNear = 0.5;  // Near clipping plane
GLfloat zFar = 250.0; // Far clipping plane
GLfloat aspect;       // Viewport aspect ratio

const GLfloat dr = 5.0; // 5.0 * DegreesToRadians;

// Viewing transformation parameters
GLfloat radius = 1.0;
GLfloat theta = 90.0;
GLfloat phi = 0.0;
GLfloat psi = 0.0;
GLfloat pitch = 3.0;
GLfloat yaw = 0.0;
GLfloat roll = 0.0;

bool moving = false;

bool perspective = false;

bool collide[NUM_OBJECTS] = { false };

bool proximal[NUM_INTERACTABLES] = { false };

bool pickup[NUM_PICKUPS] = { false };

bool doors[NUM_DOORS] = { false };

bool g_die[NUM_GHOSTS] = { false };

bool z_die[NUM_ZOMBIES] = { false };

GLfloat l = 0.0;
GLfloat r = 0.0;
GLfloat f = 0.0;
GLfloat b = 0.0;

float red = 0.0, green = 0.5, blue = 1.0, color_a_pink = 0.0;

// Title bar modifiers
std::string title_bar;

int Index = 0;        // Global to keep track of what vertex we are setting.

bool key_buffer[256] = { false };
bool spec_buffer[256] = { false };

bool display_bool = false;

bool death = false, hallucinate = false;

// Random
uint64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::seed_seq ss{ uint32_t( seed & 0xffffffff ), uint32_t( seed >> 32 ) };
std::mt19937 mt(ss);
std::uniform_real_distribution<double> dist_x(-7.0, 7.0);
std::uniform_real_distribution<double> dist_z(-10.0, -6.0);
std::uniform_real_distribution<double> sickness(0.0, 0.005);
std::uniform_real_distribution<double> morpher1(0.0, 0.5);
std::uniform_real_distribution<double> morpher2(0.0, 0.5);
std::uniform_real_distribution<double> morpher3(
);
// Position of light1
point4 light_position(-65.0,  30.0, -55.0, 1.0);
// If you want a non-positional light use 0.0 for fourth value
//point4 light_position(0.0, 0.0, 1.0, 0.0);

// Initialize first light lighting parameters
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(0.5, 0.5, 0.5, 1.0);
color4 light_specular(0.6, 0.6, 0.6, 1.0);

// Position of light2 (it will change, so needs to be global).
point4 light2_position(12.5, 12.5, -12.5, 0.0);
GLuint Light2_Pos; // uniform location

// Initialize second light lighting parameters
color4 light2_ambient(1.0, 1.0, 1.0, 1.0);
color4 light2_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light2_specular(1.0, 1.0, 1.0, 1.0);

// Material Properties for spheres
color4 material_ambient(1.0, 1.0, 1.0, 1.0);
color4 material_diffuse(1.0, 1.0, 1.0, 1.0);
color4 material_specular(1.0, 1.0, 1.0, 1.0);
float  material_shininess = 50.0;

// Next variables used to move light2.
GLfloat light_theta = 0.0;  // the angle of light2
GLfloat light_incr= 0.001;// the amount to move light2 in radians/millisecond
bool rotate = false;        // are we animating light2?

GLuint Light1;     // uniform location to turn light on or off
GLuint Light2;     // uniform location to turn light on or off

bool light1 = true;  // Is light1 on?
bool light2 = true;  // Is light2 on?

color4 emissive(1.0, 1.0, 1.0, 1.0);
color4 emissive_off(0.0, 0.0, 0.0, 1.0);

GLuint Material_Emiss; // uniform location of emissive property of surface

color4 ap = light_ambient * material_ambient;
color4 dp = light_diffuse * material_diffuse;
color4 sp = light_specular * material_specular;

color4 ap2 = light2_ambient * material_ambient;
color4 dp2 = light2_diffuse * material_diffuse;
color4 sp2 = light2_specular * material_specular;

// color4 vertex_colors[8] = {
//
//   color4(0.0, 0.0, 0.0, 1.0),  // black
//   color4(1.0, 0.0, 0.0, 1.0),  // red
//   color4(1.0, 1.0, 0.0, 1.0),  // yellow
//   color4(0.0, 1.0, 0.0, 1.0),  // green
//   color4(0.0, 0.0, 1.0, 1.0),  // blue
//   color4(1.0, 0.0, 1.0, 1.0),  // magenta
//   color4(1.0, 1.0, 1.0, 1.0),  // white
//   color4(0.0, 1.0, 1.0, 1.0)   // cyan
//
// };

color4 vertex_colors[8] = {

  color4(0.9, 0.9, 0.9, 1.0),  // black
  color4(1.0, 1.0, 1.0, 1.0),  // white
  color4(0.9, 0.9, 0.9, 1.0),  // black
  color4(1.0, 1.0, 1.0, 1.0),  // white
  color4(0.9, 0.9, 0.9, 1.0),  // black
  color4(1.0, 1.0, 1.0, 1.0),  // white
  color4(0.9, 0.9, 0.9, 1.0),  // black
  color4(1.0, 1.0, 1.0, 1.0),  // white

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

  Index = 0;

  quad(1, 0, 3, 2);
  quad(2, 3, 7, 6);
  quad(3, 0, 4, 7);
  quad(6, 5, 1, 2);
  quad(4, 5, 6, 7);
  quad(5, 4, 0, 1);

}

void triangle(const point4& a, const point4& b, const point4& c)
{
  normals[Index] = a;  normals[Index].w=0.0;  points2[Index] = a;  Index++;
  normals[Index] = b;  normals[Index].w=0.0;  points2[Index] = b;  Index++;
  normals[Index] = c;  normals[Index].w=0.0;  points2[Index] = c;  Index++;
}


point4 unit(const point4& p)
{
  float len = p.x*p.x + p.y*p.y + p.z*p.z;

  point4 t;
  if (len > DivideByZeroTolerance) {
    t = p / sqrt(len);
    t.w = 1.0;
  }

  return t;
}

void divide_triangle(const point4& a, const point4& b,
		     const point4& c, int count)
{
  if (count > 0) {
    point4 v1 = unit(a + b);
    point4 v2 = unit(a + c);
    point4 v3 = unit(b + c);
    divide_triangle( a, v1, v2, count - 1);
    divide_triangle( c, v2, v3, count - 1);
    divide_triangle( b, v3, v1, count - 1);
    divide_triangle(v1, v3, v2, count - 1);
  }
  else {
    triangle(a, b, c);
  }
}


void tetrahedron(int count)
{

  Index = 0;

  point4 v[4] = {
    vec4(0.0, 0.0, 1.0, 1.0),
    vec4(0.0, 0.942809, -0.333333, 1.0),
    vec4(-0.816497, -0.471405, -0.333333, 1.0),
    vec4(0.816497, -0.471405, -0.333333, 1.0)
  };

  divide_triangle(v[0], v[1], v[2], count);
  divide_triangle(v[3], v[2], v[1], count);
  divide_triangle(v[0], v[3], v[1], count);
  divide_triangle(v[0], v[2], v[3], count);
}

//
void object(mat4 matrix, GLuint uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d, GLfloat r, GLfloat g, GLfloat b, int pitch, int yaw, int roll, int sl, int st, int type) {

  if (death) {
    ap = light_ambient * vec4(r, g, b, 1.0);
    dp = light_diffuse * vec4(r, g, b, 1.0);
    sp = light_specular * vec4(r, g, b, 1.0);
    ap2 = light2_ambient * vec4(1.0, 0.0, 0.0, 1.0);
    dp2 = light2_diffuse * vec4(1.0, 0.0, 0.0, 1.0);
    sp2 = light2_specular * vec4(1.0, 0.0, 0.0, 1.0);
  } else if (hallucinate) {
    color_a_pink += 0.001;
    red = sin(color_a_pink*M_PI/180/2);
    green = sin(90 + 1.5 * color_a_pink*M_PI/180/2);
    blue = sin(180 + 2.0 * color_a_pink*M_PI/180/2);
    ap = light_ambient * vec4(red * 0.6, green * 0.6, blue * 0.6, 1.0);
    dp = light_diffuse * vec4(red * 0.5, green * 0.5, blue * 0.5, 1.0);
    sp = light_specular * vec4(red * 0.4, green * 0.4, blue * 0.4, 1.0);
    ap = light2_ambient * vec4(-red * 0.4, -green * 0.5, -blue * 0.6, 1.0);
    dp = light2_diffuse * vec4(-blue * 0.5, -red * 0.6, -green * 0.4, 1.0);
    sp = light2_specular * vec4(-green * 0.6, -blue * 0.4, -red * 0.5, 1.0);
  } else {
    ap = light_ambient * vec4(r, g, b, 1.0);
    dp = light_diffuse * vec4(r, g, b, 1.0);
    sp = light_specular * vec4(r, g, b, 1.0);
    ap2 = light2_ambient * vec4(r, g, b, 1.0);
    dp2 = light2_diffuse * vec4(r, g, b, 1.0);
    sp2 = light2_specular * vec4(r, g, b, 1.0);
  }


    glUniform4fv(ambient_product, 1, ap);
    glUniform4fv(diffuse_product, 1, dp);
    glUniform4fv(specular_product, 1, sp);

    glUniform4fv(ambient_product2, 1, ap2);
    glUniform4fv(diffuse_product2, 1, dp2);
    glUniform4fv(specular_product2, 1, sp2);

    mat4 instance = (
      Translate( x, y, z )
      * RotateX(pitch) * RotateY(yaw) * RotateZ(roll)
    );

    switch (type) {
      case 0:
        glUniformMatrix4fv( uniform, 1, GL_TRUE, matrix * instance * Scale( w, h, d ) );
        glUniform1f( enable, 0.0 );
        glDrawArrays( GL_TRIANGLES, 0, NumVertices ); break;
      // case 1:
      //   glUniformMatrix4fv( uniform, 1, GL_TRUE, matrix * instance );
      //   glUniform1f( enable, 2.0 );
      //   gluCylinder(qobj, w, d, h, sl, st); break;
      case 2:
        glUniform4fv(Material_Emiss, 1, emissive);
          glUniformMatrix4fv( uniform, 1, GL_TRUE, matrix * instance * Scale( w, h, d ) );
          glUniform1f( enable, 1.0 );
          glDrawArrays( GL_TRIANGLES, NumVertices, NumVertices2 );
        glUniform4fv(Material_Emiss, 1, emissive_off); break;

    };

}

void collision(GLfloat *x, GLfloat y, GLfloat *z, GLfloat w, GLfloat h, GLfloat d, vec3 loc[], vec3 size[], bool result[], int num) {
  for (int i = 0; i < num; i++) {
    if (*x - w / 2 < loc[i].x + size[i].x / 2 &&
        *x + w / 2 > loc[i].x - size[i].x / 2 &&
        *z - d / 2 < loc[i].z + size[i].z / 2 &&
        *z + d / 2 > loc[i].z - size[i].z / 2 ) {
      result[i] = true;
      l = (loc[i].x + size[i].x / 2) - (*x - w / 2);
      r = (*x + w / 2) - (loc[i].x - size[i].x / 2);
      f = (loc[i].z + size[i].z / 2) - (*z - d / 2);
      b = (*z + d / 2) - (loc[i].z - size[i].z / 2);
      if (l < f && l < b && l < r) { *x += l; }
      else if (r < f && r < b && r < l) { *x -= r; }
      else if (f < b && f < l && f < r) { *z += f; }
      else if (b < f && b < l && b < r) { *z -= b; }
    } else {
      result[i] = false;
    }
  }
}

void proximity(GLfloat *x, GLfloat y, GLfloat *z, GLfloat w, GLfloat h, GLfloat d, vec3 loc[], vec3 size[], bool result[], int num) {
  for (int i = 0; i < num; i++) {
    if (*x - w / 2 < loc[i].x + size[i].x + 2.0 / 2 &&
        *x + w / 2 > loc[i].x - size[i].x - 2.0 / 2 &&
        *z - d / 2 < loc[i].z + size[i].z + 2.0 / 2 &&
        *z + d / 2 > loc[i].z - size[i].z - 2.0 / 2 ) {
      result[i] = true;
    } else {
      result[i] = false;
    }
  }
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
  gluPerspective(fovy, (GLfloat) width / (GLfloat) height, zNear, zFar);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // glTranslatef(0.0, 1.2, -5.5);  /* viewing transform  */

  aspect = GLfloat(width)/height;

}


// //----------------------------------------------------------------------------
// extern "C" void reshape(int width, int height)
// {
//   glViewport(0, 0, width, height);
//
//   aspect = GLfloat(width)/height;
//
//   mat4 projection = Perspective(fovy, aspect, 0.1, 100.0);
//   glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
// }
//


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

  tetrahedron(NumTimesToSubdivide);

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(points2) + sizeof(colors) + sizeof(normals), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(points2), points2);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(points2), sizeof(colors), colors);
  // glBufferSubData(GL_ARRAY_BUFFER, sizeof(colors), sizeof(normals), normals);

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("shaders/vshader.glsl", "shaders/fshader.glsl");
  glUseProgram(program);

  // // set up vertex arrays
  GLuint vPosition = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  GLuint vColor = glGetAttribLocation(program, "vColor");
  glEnableVertexAttribArray(vColor);
  glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points2)));

  GLuint vNormal = glGetAttribLocation(program, "vNormal");
  glEnableVertexAttribArray(vNormal);
  glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(normals)));

  model_view = glGetUniformLocation(program, "model_view");
  camera_view = glGetUniformLocation(program, "camera_view");
  projection = glGetUniformLocation(program, "projection");
  color_change = glGetUniformLocation(program, "color_change");
  enable = glGetUniformLocation(program, "enable");

  ambient_product = glGetUniformLocation(program, "AmbientProduct");
  diffuse_product = glGetUniformLocation(program, "DiffuseProduct");
  specular_product = glGetUniformLocation(program, "SpecularProduct");
  ambient_product2 = glGetUniformLocation(program, "AmbientProduct2");
  diffuse_product2 = glGetUniformLocation(program, "DiffuseProduct2");
  specular_product2 = glGetUniformLocation(program, "SpecularProduct2");

  glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);

  Light2_Pos = glGetUniformLocation(program, "LightPosition2");
  glUniform4fv(Light2_Pos, 1, light2_position);

  glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

  // If surface glows, it should have an emissive term in the material property.
  Material_Emiss = glGetUniformLocation(program, "emissive");
  glUniform4fv(Material_Emiss, 1, emissive_off);

  Light1 = glGetUniformLocation(program, "light1");
  glUniform1i(Light1,light1);

  Light2 = glGetUniformLocation(program, "light2");
  glUniform1i(Light2,light2);

  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0, 1.0, 1.0, 1.0);

}

#endif
