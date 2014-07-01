/*
** 3/06/2001
** http://graphics.stanford.edu/software/wiregl
**
** Copyright 2001
** The Board of Trustees of The Leland Stanford Junior University.
** All rights reserved.
**
** Except for commercial resale, lease, license or other commercial
** transactions, permission is hereby given to use, copy, and/or
** modify this software, provided that the above copyright notice and
** this permission notice appear in all copies of this software.  No
** part of this software or any derivatives thereof may be used in
** graphics systems for resale or for use in a commercial product.
**
** This software is provided "as is" and without warranty of any kind,
** express, implied or otherwise, including without limitation, any
** warranty of merchantability or fitness for a particular purpose.
*/

#include "glcontext.h"
#include "glerror.h"

// glRect bucket
void GLSTATE_DECL
__glstate_Rectd (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(x1);
  UNUSED(y1);
  UNUSED(x2);
  UNUSED(y2);

}

void GLSTATE_DECL
__glstate_Rectdv (const GLdouble *v1, const GLdouble *v2) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(v1);
  UNUSED(v2);
}

void GLSTATE_DECL
__glstate_Rectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(x1);
  UNUSED(y1);
  UNUSED(x2);
  UNUSED(y2);
}

void GLSTATE_DECL
__glstate_Rectfv (const GLfloat *v1, const GLfloat *v2) {
	GLcontext *g = GetCurrentContext();

 	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(v1);
  UNUSED(v2);
}

void GLSTATE_DECL
__glstate_Recti (GLint x1, GLint y1, GLint x2, GLint y2) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(x1);
  UNUSED(y1);
  UNUSED(x2);
  UNUSED(y2);
}

void GLSTATE_DECL
__glstate_Rectiv (const GLint *v1, const GLint *v2) {
	GLcontext *g = GetCurrentContext();

  if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(v1);
  UNUSED(v2);
}

void GLSTATE_DECL
__glstate_Rects (GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(x1);
  UNUSED(y1);
  UNUSED(x2);
  UNUSED(y2);
}


void GLSTATE_DECL
__glstate_Rectsv (const GLshort *v1, const GLshort *v2) {
	GLcontext *g = GetCurrentContext();
	
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Rect called in Begin/End"))
			return;

  UNUSED(v1);
  UNUSED(v2);
}
