
/* glVertex functions */

#include <stdio.h>
#include "gllocal.h"
#include "glcontext/glcontext.h"
#include "glcore/glcore.h"

void FUNCAPI __gllocal_Begin (GLenum mode) {
  GLcontext *g = __glGetCurrentContext();
  __glstate_Begin(mode);
  __glcore_Begin(g, mode);
}

void FUNCAPI __gllocal_End (void) {
  GLcontext *g = __glGetCurrentContext();
  __glstate_End();
  __glcore_End(g);
}

void __issuevertex(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  GLcontext *g = __glGetCurrentContext();
  __glcore_Vertex4f(g, x, y, z, w);
}

#define VERTEX_FUNC(prefix, type) \
void FUNCAPI __gllocal_Vertex2##prefix (type x, type y) {\
 __issuevertex((GLfloat) x, (GLfloat) y, 0.0f, 1.0f); \
}  \
void FUNCAPI __gllocal_Vertex3##prefix (type x, type y, type z) {\
 __issuevertex((GLfloat) x, (GLfloat) y, (GLfloat) z, 1.0f); \
}  \
void FUNCAPI __gllocal_Vertex4##prefix (type x, type y, type z, type w) {\
 __issuevertex((GLfloat) x, (GLfloat) y, (GLfloat) z, (GLfloat) w); \
}  \
void FUNCAPI __gllocal_Vertex2##prefix##v (const type *v) {\
 __issuevertex((GLfloat) v[0], (GLfloat) v[1], 0.0f, 1.0f); \
}  \
void FUNCAPI __gllocal_Vertex3##prefix##v (const type *v) {\
 __issuevertex((GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], 1.0f); \
}  \
void FUNCAPI __gllocal_Vertex4##prefix##v (const type *v) {\
 __issuevertex((GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], (GLfloat) v[3]); \
}
  
VERTEX_FUNC(s,GLshort)
VERTEX_FUNC(i,GLint)
VERTEX_FUNC(f,GLfloat)
VERTEX_FUNC(d,GLdouble)
