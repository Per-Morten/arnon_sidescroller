#include "glCallbacks.h"
#include "debug/arnlog.h"

void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    switch (severity)
    {
    case gl::DEBUG_SEVERITY_NOTIFICATION:
        // Don't bother logging this
        break;
    case gl::DEBUG_SEVERITY_LOW:
        logWarn("OpenGL Low Priority Error #{}: {}", id, message);
        break;
    case gl::DEBUG_SEVERITY_MEDIUM:
        logWarn("OpenGL Medium Priority Error #{}: {}", id, message);
        break;
    case gl::DEBUG_SEVERITY_HIGH:
    default:
        // Treat default as error
        logErr("OpenGL Error #{}: {}", id, message);
        break;
    }
}
