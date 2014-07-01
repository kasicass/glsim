
/* Misc functions */

#include <stdio.h>
#include "gllocal.h"
#include "glcontext/glcontext.h"
#include "glcontext/glerror.h"
#include "glcore/glcore.h"

void FUNCAPI __gllocal_Flush (void) {
  GLcontext *g = __glGetCurrentContext();
  __glcore_Flush(g);
}

void FUNCAPI __gllocal_Finish (void) {
  GLcontext *g = __glGetCurrentContext();
  __glcore_Finish(g);
}

void FUNCAPI __gllocal_Clear (GLbitfield  mask) {
  GLcontext *g = __glGetCurrentContext();
  __glcore_Clear(g, mask);
}

void FUNCAPI __gllocal_ArrayElement (GLint index) {
	GLcontext *g = __glGetCurrentContext();
	GLclientstate *c = &(g->client);
	unsigned char *p;

	if (index < 0)
		UNIMPLEMENTED();

	if (c->e.enabled) {
		__glstate_EdgeFlagv(c->e.p + index*c->e.stride);
	}
	if (c->t.enabled) {
		p = c->t.p + index*c->t.stride;
		switch (c->t.type) {
		case GL_SHORT:
			switch (c->t.size) {
			case 1:
				__glstate_TexCoord1sv((GLshort *)p);
				break;
			case 2:
				__glstate_TexCoord2sv((GLshort *)p);
				break;
			case 3:
				__glstate_TexCoord3sv((GLshort *)p);
				break;
			case 4:
				__glstate_TexCoord4sv((GLshort *)p);
				break;
			}
			break;
		case GL_INT:
			switch (c->t.size) {
			case 1:
				__glstate_TexCoord1iv((GLint *)p);
				break;
			case 2:
				__glstate_TexCoord2iv((GLint *)p);
				break;
			case 3:
				__glstate_TexCoord3iv((GLint *)p);
				break;
			case 4:
				__glstate_TexCoord4iv((GLint *)p);
				break;
			}
			break;
		case GL_FLOAT:
			switch (c->t.size) {
			case 1:
				__glstate_TexCoord1fv((GLfloat *)p);
				break;
			case 2:
				__glstate_TexCoord2fv((GLfloat *)p);
				break;
			case 3:
				__glstate_TexCoord3fv((GLfloat *)p);
				break;
			case 4:
				__glstate_TexCoord4fv((GLfloat *)p);
				break;
			}
			break;
		case GL_DOUBLE:
			switch (c->t.size) {
			case 1:
				__glstate_TexCoord1dv((GLdouble *)p);
				break;
			case 2:
				__glstate_TexCoord2dv((GLdouble *)p);
				break;
			case 3:
				__glstate_TexCoord3dv((GLdouble *)p);
				break;
			case 4:
				__glstate_TexCoord4dv((GLdouble *)p);
				break;
			}
			break;
		}
	}
	if (c->i.enabled) {
		p = c->i.p + index*c->i.stride;
		switch (c->i.type) {
		case GL_SHORT:
			__glstate_Indexsv((GLshort *)p);
			break;
		case GL_INT:
			__glstate_Indexiv((GLint *)p);
			break;
		case GL_FLOAT:
			__glstate_Indexfv((GLfloat *)p);
			break;
		case GL_DOUBLE:
			__glstate_Indexdv((GLdouble *)p);
			break;
		}
	}
	if (c->c.enabled) {
		p = c->c.p + index*c->c.stride;
		switch (c->c.type) {
		case GL_BYTE:
			switch (c->c.size) {
			case 3:
				__glstate_Color3bv((GLbyte *)p);
				break;
			case 4:
				__glstate_Color4bv((GLbyte *)p);
				break;
			}
			break;
		case GL_UNSIGNED_BYTE:
			switch (c->c.size) {
			case 3:
				__glstate_Color3ubv((GLubyte *)p);
				break;
			case 4:
				__glstate_Color4ubv((GLubyte *)p);
				break;
			}
			break;
		case GL_SHORT:
			switch (c->c.size) {
			case 3:
				__glstate_Color3sv((GLshort *)p);
				break;
			case 4:
				__glstate_Color4sv((GLshort *)p);
				break;
			}
			break;
		case GL_UNSIGNED_SHORT:
			switch (c->c.size) {
			case 3:
				__glstate_Color3usv((GLushort *)p);
				break;
			case 4:
				__glstate_Color4usv((GLushort *)p);
				break;
			}
			break;
		case GL_INT:
			switch (c->c.size) {
			case 3:
				__glstate_Color3iv((GLint *)p);
				break;
			case 4:
				__glstate_Color4iv((GLint *)p);
				break;
			}
			break;
		case GL_UNSIGNED_INT:
			switch (c->c.size) {
			case 3:
				__glstate_Color3uiv((GLuint *)p);
				break;
			case 4:
				__glstate_Color4uiv((GLuint *)p);
				break;
			}
			break;
		case GL_FLOAT:
			switch (c->c.size) {
			case 3:
				__glstate_Color3fv((GLfloat *)p);
				break;
			case 4:
				__glstate_Color4fv((GLfloat *)p);
				break;
			}
			break;
		case GL_DOUBLE:
			switch (c->c.size) {
			case 3:
				__glstate_Color3dv((GLdouble *)p);
				break;
			case 4:
				__glstate_Color4dv((GLdouble *)p);
				break;
			}
			break;
		}
	}
	if (c->n.enabled) {
		p = c->n.p + index*c->n.stride;
		switch (c->n.type) {
		case GL_BYTE:
			__glstate_Normal3bv((GLbyte *)p);
			break;
		case GL_SHORT:
			__glstate_Normal3sv((GLshort *)p);
			break;
		case GL_INT:
			__glstate_Normal3iv((GLint *)p);
			break;
		case GL_FLOAT:
			__glstate_Normal3fv((GLfloat *)p);
			break;
		case GL_DOUBLE:
			__glstate_Normal3dv((GLdouble *)p);
			break;
		}
	}
	if (c->v.enabled) {
		p = c->v.p + (index*c->v.stride);

		switch (c->v.type) {
		case GL_SHORT:
			switch (c->v.size) {
			case 2:
				__gllocal_Vertex2sv((GLshort *)p);
				break;
			case 3:
				__gllocal_Vertex3sv((GLshort *)p);
				break;
			case 4:
				__gllocal_Vertex4sv((GLshort *)p);
				break;
			}
			break;
		case GL_INT:
			switch (c->v.size) {
			case 2:
				__gllocal_Vertex2iv((GLint *)p);
				break;
			case 3:
				__gllocal_Vertex3iv((GLint *)p);
				break;
			case 4:
				__gllocal_Vertex4iv((GLint *)p);
				break;
			}
			break;
		case GL_FLOAT:
			switch (c->v.size) {
			case 2:
				__gllocal_Vertex2fv((GLfloat *)p);
				break;
			case 3:
				__gllocal_Vertex3fv((GLfloat *)p);
				break;
			case 4:
				__gllocal_Vertex4fv((GLfloat *)p);
				break;
			}
			break;
		case GL_DOUBLE:
			switch (c->v.size) {
			case 2:
				__gllocal_Vertex2dv((GLdouble *)p);
				break;
			case 3:
				__gllocal_Vertex3dv((GLdouble *)p);
				break;
			case 4:
				__gllocal_Vertex4dv((GLdouble *)p);
				break;
			}
			break;
		}
	}
}

void FUNCAPI
__gllocal_DrawArrays(GLenum mode, GLint first, GLsizei count) {
  int i;

  __glstate_DrawArrays(mode, first, count);
  
	__gllocal_Begin(mode);
	for (i=0; i<count; i++) 
		__gllocal_ArrayElement(first++);
	__gllocal_End();
}

void FUNCAPI
__gllocal_DrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) {
	int i;
	GLubyte *p = (GLubyte *)indices;

  __glstate_DrawElements(mode, count, type, indices);
	
	__gllocal_Begin (mode);
	switch (type) {
	case GL_UNSIGNED_BYTE:
		for (i=0; i<count; i++)
			__gllocal_ArrayElement((GLint) *p++);
		break;
	case GL_UNSIGNED_SHORT:
		for (i=0; i<count; i++) {
			__gllocal_ArrayElement((GLint) * (GLushort *) p);
			p+=sizeof (GLushort);
		}
		break;
	case GL_UNSIGNED_INT:
		for (i=0; i<count; i++) {
			__gllocal_ArrayElement((GLint) * (GLuint *) p);
			p+=sizeof (GLuint);
		}
		break;
	default:
		UNIMPLEMENTED();
	}
	__gllocal_End();
}
