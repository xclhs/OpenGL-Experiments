#ifndef _ANGLE_H_
#define _ANGLE_H_
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__

namespace Angel{
    GLuint InitShader(const char* vertexShaderFile,
                      const char* fragmentShaderFile);


      const GLfloat DivideByZeroTolerance = GLfloat(1.0e-07);

      const GLfloat DegreesToRadians = M_PI/180.0;

}

#include "vec.h"
#include "mat.h"
using namespace Angel;
#endif // _ANGLE_H_
