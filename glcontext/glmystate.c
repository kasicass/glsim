
#include "glcontext.h"
#include "glerror.h"

void 
__glmystate_init(GLmystate *m, GLconfig *c) {

  UNUSED(c);

  m->a = 0;
  m->b = 0;

}
