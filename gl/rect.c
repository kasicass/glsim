

/* glRect functions */

#include "gllocal.h"

#define RECT_FUNC(prefix, type) \
void FUNCAPI __gllocal_Rect##prefix (type x1, type y1, type x2, type y2) {\
  __gllocal_Begin(GL_POLYGON);         \
  __gllocal_Vertex2##prefix (x1, y1);  \
  __gllocal_Vertex2##prefix (x2, y1);  \
  __gllocal_Vertex2##prefix (x2, y2);  \
  __gllocal_Vertex2##prefix (x1, y2);  \
  __gllocal_End();                     \
}  \
void FUNCAPI __gllocal_Rect##prefix##v (const type *v1, const type *v2) { \
  __gllocal_Begin(GL_POLYGON);         \
  __gllocal_Vertex2##prefix (v1[0], v1[1]);  \
  __gllocal_Vertex2##prefix (v2[0], v1[1]);  \
  __gllocal_Vertex2##prefix (v2[0], v2[1]);  \
  __gllocal_Vertex2##prefix (v1[0], v2[1]);  \
  __gllocal_End();                     \
}  \

RECT_FUNC(s,GLshort)
RECT_FUNC(i,GLint)
RECT_FUNC(f,GLfloat)
RECT_FUNC(d,GLdouble)
