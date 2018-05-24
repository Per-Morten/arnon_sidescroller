/// ArnonSidescroller - by Carl Findahl - 2018

/* 
 * \brief Contains OpenGL Callbacks. To be honest, that 
 * means the Debug callback used to get OpenGL error
 * messages automatically.
 */

#ifndef GLCALLBACKS_H
#define GLCALLBACKS_H

#include "GL/glCore45.h"

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

#endif // GLCALLBACKS_H
