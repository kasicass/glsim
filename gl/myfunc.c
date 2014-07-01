

/* Myfunc implementation */

#include "gllocal.h"
#include "glcontext/glcontext.h"

void FUNCAPI glMyFunc (GLint a, GLint b) {

  GLcontext *g = __glGetCurrentContext();

  g->mystate.a = a;
  g->mystate.b = b;

}

