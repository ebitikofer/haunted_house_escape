//////////////////////////////////////////////////////////////////////////////
//
//  --- InitShader.cpp ---
//
//   from Angel 6th Edition
// 
//   Allows shaders to be read from a file and initialized.
//
//   Modified by Prof. David M. Chelberg for style and clarity
//   last-modified: Mon Sep 17 10:52:51 2012
//
//////////////////////////////////////////////////////////////////////////////
// Conde from 

#include "Angel.h"

namespace Angel {

  // Create a NULL-terminated string by reading the provided file
  static char* readShaderSource(const char* shaderFile)
  {
    FILE* fp = fopen(shaderFile, "r");

    if (fp == NULL) { 
      return NULL; 
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);

    return buf;
  }


  // To allow for more shaders in the future.
  static const int NUM_SHADERS=2;

  // Create a GLSL program object from vertex and fragment shader files
  GLuint InitShader(const char* vShaderFile, const char* fShaderFile)
  {
    struct Shader {
      const char*  filename;
      GLenum       type;
      GLchar*      source;
    }  shaders[NUM_SHADERS] = {{vShaderFile, GL_VERTEX_SHADER, NULL},
		               {fShaderFile, GL_FRAGMENT_SHADER, NULL}
                              };

    GLuint program = glCreateProgram();
    
    // For each shader do this stuff
    for (int i = 0; i < NUM_SHADERS; ++i) {
      Shader& s = shaders[i];
      s.source = readShaderSource(s.filename);
      if (shaders[i].source == NULL) {
	std::cerr << "Failed to read " << s.filename << std::endl;
	exit(EXIT_FAILURE);
      }

      GLuint shader = glCreateShader(s.type);
      glShaderSource(shader, 1, (const GLchar**) &s.source, NULL);
      glCompileShader(shader);

      GLint  compiled;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
      if (!compiled) {
	std::cerr << s.filename << " failed to compile:" << std::endl;
	GLint  logSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
	char* logMsg = new char[logSize];
	glGetShaderInfoLog(shader, logSize, NULL, logMsg);
	std::cerr << logMsg << std::endl;
	delete [] logMsg;

	exit(EXIT_FAILURE);
      }

      delete [] s.source;

      glAttachShader(program, shader);
    }

    // link  and error check
    glLinkProgram(program);

    GLint  linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
      std::cerr << "Shader program failed to link" << std::endl;
      GLint  logSize;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
      char* logMsg = new char[logSize];
      glGetProgramInfoLog(program, logSize, NULL, logMsg);
      std::cerr << logMsg << std::endl;
      delete [] logMsg;

      exit(EXIT_FAILURE);
    }

    // use program object
    glUseProgram(program);
    return program;
  }

}  // Close namespace Angel block
