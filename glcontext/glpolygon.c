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

#include <memory.h>
#include "glcontext.h"
#include "glerror.h"

void 
__glpolygon_initbits (GLpolygonbits *p, GLconfig *cfg) {
	/* do nothing */
	UNUSED(p);
	UNUSED(cfg);
}

void
__glpolygon_init(GLpolygonstate *p, GLconfig *cfg) {
	int i;
	UNUSED(cfg);
	p->polygonsmooth = GL_FALSE;
	p->polygonoffset = GL_FALSE;
	p->polygonstipple = GL_FALSE;
	p->cullface = GL_FALSE;

	p->offsetfactor = 0;
	p->offsetunits = 0;
	p->cullfacemode = GL_BACK;
	p->frontface = GL_CCW;
	p->frontmode = GL_FILL;
	p->backmode = GL_FILL;
	for (i=0; i<32; i++)
		p->stipple[i] = 0xFFFFFFFF;
}

void
__glpolygon_destroy(GLpolygonstate *p) {
	/* do nothing */
	UNUSED(p);
}

void GLSTATE_DECL
__glstate_CullFace(GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLpolygonstate *p = &(g->polygon);
	GLstatebits *sb = GetStateBits();
	GLpolygonbits *pb = &(sb->polygon);

	/*ECHECK*/
	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glCullFace called in begin/end"))
			return;

 
		

	if (mode != GL_FRONT &&
		mode != GL_BACK)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glCullFace called with bogus mode: %d", mode))
			return;
	/*ECHECK*/

	p->cullfacemode = mode;
	pb->mode = g->nbitID;
	pb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_FrontFace (GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLpolygonstate *p = &(g->polygon);
	GLstatebits *sb = GetStateBits();
	GLpolygonbits *pb = &(sb->polygon);

	/*ECHECK*/
	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glFrontFace called in begin/end"))
			return;

 
		

	if (mode != GL_CW &&
		mode != GL_CCW)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glFrontFace called with bogus mode: %d", mode))
			return;
	/*ECHECK*/

	p->frontface = mode;
	pb->mode = g->nbitID;
	pb->dirty = g->nbitID;
}

void  GLSTATE_DECL
__glstate_PolygonMode (GLenum face, GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLpolygonstate *p = &(g->polygon);
	GLstatebits *sb = GetStateBits();
	GLpolygonbits *pb = &(sb->polygon);

	/*ECHECK*/
	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glPolygonMode called in begin/end"))
			return;

 
		

	if (mode != GL_POINT &&
		mode != GL_LINE &&
		mode != GL_FILL)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glPolygonMode called with bogus mode: %d", mode))
			return;
	/*ECHECK*/

	switch (face) {
	case GL_FRONT:
		p->frontmode = mode;
		break;
	case GL_FRONT_AND_BACK:
		p->frontmode = mode;
	case GL_BACK:
		p->backmode = mode;
		break;
	/*ECHECK*/
	default:
	if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
		"glPolygonMode called with bogus face: %d", face))
		return;
	/*ECHECK*/
	}
	pb->mode = g->nbitID;
	pb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_PolygonOffset (GLfloat factor, GLfloat units) {
	GLcontext *g = GetCurrentContext();
	GLpolygonstate *p = &(g->polygon);
	GLstatebits *sb = GetStateBits();
	GLpolygonbits *pb = &(sb->polygon);

	/*ECHECK*/
	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glPolygonMode called in begin/end"))
			return;

 
		
	/*ECHECK*/

	p->offsetfactor = factor;
	p->offsetunits = units;

	pb->offset = g->nbitID;
	pb->dirty = g->nbitID;
}


/* We need an unpack function for this guy */
void GLSTATE_DECL
__glstate_PolygonStipple (const GLubyte *p) {
	GLcontext *g = GetCurrentContext();
	GLpolygonstate *poly = &(g->polygon);
	GLpixelstate *pix = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLpolygonbits *pb = &(sb->polygon);

	/*ECHECK*/
	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glPolygonMode called in begin/end"))
			return;
	
	if (!p)
		if (__glerror(__LINE__, __FILE__, GL_NO_ERROR,
			"Void pointer passed to PolygonStipple"))
			return;
	/*ECHECK*/

	__glpixel_getdata2D_p (pix, (GLvoid *) poly->stipple, 
							32, 32, GL_COLOR_INDEX, GL_BITMAP, 
							(const GLvoid *) p);

	pb->dirty = g->nbitID;
	pb->stipple = g->nbitID;
}

void GLSTATE_DECL
__glstate_GetPolygonStipple (GLubyte *b) {
	UNUSED(b);
	UNIMPLEMENTED();
}

