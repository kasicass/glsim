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
#include <assert.h>
#include "glcontext.h"
#include "glerror.h"

void GLSTATE_DECL
__glstate_Accum (GLenum op, GLfloat value) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"Accum called in begin/end"))
			return;

	if (op != GL_ACCUM &&
		op != GL_LOAD &&
		op != GL_ADD &&
		op != GL_MULT &&
		op != GL_RETURN) {
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"Accum called with bogus enum: %d", op))
			return;
	}

  UNUSED(value);
}


void GLSTATE_DECL
__glstate_CallLists (GLsizei n, GLenum type, const GLvoid *lists) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"CallLists called in begin/end"))
			return;

  UNUSED(n);
  UNUSED(type);
  UNUSED(lists);
}

void GLSTATE_DECL
__glstate_CallList (GLuint list){ 
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"CallList called in begin/end"))
			return;

  UNUSED(list);
}

void GLSTATE_DECL
__glstate_Clear (GLbitfield mask) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"Clear called in begin/end"))
			return;

	if (mask & 
		~GL_COLOR_BUFFER_BIT & 
		~GL_DEPTH_BUFFER_BIT &
		~GL_ACCUM_BUFFER_BIT &
		~GL_STENCIL_BUFFER_BIT)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, 
			"Clear called with bogus mask: %d", mask))
			return;

}

void GLSTATE_DECL 
__glstate_DrawPixels (GLsizei width, GLsizei height, 
		GLenum format, GLenum type, const GLvoid *pixels)
{
	GLcontext *g = GetCurrentContext();
	GLcurrentstate *c = &(g->current);	

	if (c->beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"DrawPixels called in begin/end"))
			return;

	if (width < 0 || height < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"DrawPixels called with neg dims: %dx%d", width, height))
			return;

  UNUSED(format);
  UNUSED(type);
  UNUSED(pixels);
}

void GLSTATE_DECL
__glstate_Bitmap (	GLsizei width, GLsizei height,
					GLfloat xorig, GLfloat yorig,
					GLfloat xmove, GLfloat ymove,
					const GLubyte * bitmap) {
	GLcontext *g = GetCurrentContext();
	GLcurrentstate *c = &(g->current);
	GLstatebits *s = GetStateBits();
	GLcurrentbits *cb = &(s->current);
	
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"Bitmap called in begin/end"))
			return;

	if (width < 0 || height < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"Bitmap called with neg dims: %dx%d", width, height))
			return;

	if (!c->rastervalid)
		return;

  UNUSED(yorig);
  UNUSED(xorig);
  UNUSED(bitmap);

	c->rasterpos.x += xmove;
	c->rasterpos.y += ymove;
	cb->raster = g->nbitID;
	cb->dirty = g->nbitID;
}




