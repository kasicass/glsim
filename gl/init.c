
#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "glcontext/glcontext.h"
#include "glcontext/glconfig.h"
#include "gllocal.h"
#include "glcore/glcore.h"


GLcontext *__gllocal_CreateContext(GLconfig *cfg) {
  GLcontext *g;

  fprintf (stderr, "*********************************\n");
  fprintf (stderr, "Using GLSim OpenGL Implementation\n");
  fprintf (stderr, "*********************************\n");

  __gllocal_InitFuncPtrs();

  g = __glCreateContext(cfg);
  g->renderstate = __glcore_CreateContext();

  return g;
}

GLcontext *__gllocal_GetCurrentContext(void) {
  return __glGetCurrentContext();
}

void __gllocal_SwapBuffers(void) {
  GLcontext *g = __glGetCurrentContext();
  __glcore_SwapBuffers(g);
}

void __gllocal_MakeCurrent(GLframebuffer *fb, GLcontext *g) {
  __glMakeCurrent(g);
  g->framebuffer = fb;
}



