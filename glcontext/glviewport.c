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

void 
__glviewport_initbits (GLviewportbits *v, GLconfig *cfg) {
	UNUSED(v);
	UNUSED(cfg);
	/* do nothing */
}

void
__glviewport_init(GLviewportstate *v, GLconfig *c) {
	v->scissortest = GL_FALSE;
	
	v->maxviewportdims_width = c->maxviewportdims_width;
	v->maxviewportdims_height = c->maxviewportdims_height;

	v->v_valid = c->viewport_valid;
	v->v_x = c->viewport.x1;
	v->v_y = c->viewport.y1;
	v->v_w = c->viewport.x2 - c->viewport.x1;
	v->v_h = c->viewport.y2 - c->viewport.y1;

	v->s_valid = c->viewport_valid;
	v->s_x = c->viewport.x1;
	v->s_y = c->viewport.y1;
	v->s_w = c->viewport.x2 - c->viewport.x1;
	v->s_h = c->viewport.y2 - c->viewport.y1;

	v->getwindowsize = c->getwindowsize;

	v->f = 1.0;
	v->n = 0.0;
}

void
__glviewport_destroy(GLviewportstate *v) {
/*
** Do nothing...
*/
	UNUSED(v);
}

void
__glviewport_ApplyViewport(GLviewportstate *v, GLvectorf *p) {
	p->x = (p->x+1.0f)*(v->v_w / 2.0f) + v->v_x;
	p->y = (p->y+1.0f)*(v->v_h / 2.0f) + v->v_y;
}


GLEXPORT void GLSTATE_DECL
__glstate_Viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
	GLcontext *g = GetCurrentContext();
	GLviewportstate *v = &(g->viewport);
	GLstatebits *sb = GetStateBits();
	GLviewportbits *vb = &(sb->viewport);
	
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glViewport called in Begin/End"))
			return;
	
	if (width < 0 || height < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative viewport width or height: %dx%d", width, height))
			return;

	if (x > v->maxviewportdims_width)	x = v->maxviewportdims_width;
	if (x < -v->maxviewportdims_width)	x = -v->maxviewportdims_width;
	if (y > v->maxviewportdims_height)	y = v->maxviewportdims_height;
	if (y < -v->maxviewportdims_height)	y = -v->maxviewportdims_height;
	if (width > v->maxviewportdims_width)	width = v->maxviewportdims_width;
	if (height > v->maxviewportdims_height)	height = v->maxviewportdims_height;

	v->v_x = x;
	v->v_y = y;
	v->v_w = width;
	v->v_h = height;

	v->v_valid = GL_TRUE;
	
	vb->v_dims = g->nbitID;
	vb->dirty = g->nbitID;
}

GLEXPORT void GLSTATE_DECL
__glstate_DepthRange(GLclampd znear, GLclampd zfar) {
	GLcontext *g = GetCurrentContext();
	GLviewportstate *v = &(g->viewport);
	GLstatebits *sb = GetStateBits();
	GLviewportbits *vb = &(sb->viewport);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glDepthRange called in Begin/End"))
			return;

	v->n = znear;
	v->f = zfar;
	if (v->n < 0.0) v->n = 0.0;
	if (v->n > 1.0) v->n = 1.0;
	if (v->f < 0.0) v->f = 0.0;
	if (v->f > 1.0) v->f = 1.0;

	vb->depth = g->nbitID;
	vb->dirty = g->nbitID;
}

GLEXPORT void GLSTATE_DECL
__glstate_Scissor (GLint x, GLint y, 
					 GLsizei width, GLsizei height) {
	GLcontext *g = GetCurrentContext();
	GLviewportstate *v = &(g->viewport);
	GLstatebits *stateb = GetStateBits();
	GLviewportbits *vb = &(stateb->viewport);

	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glScissor called in begin/end"))
			return;

	if (width < 0 || height < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glScissor called with negative width/height: %d,%d",
			width, height))
			return;

	v->s_x = x;
	v->s_y = y;
	v->s_w = width;
	v->s_h = height;

	v->s_valid = GL_TRUE;

	vb->s_dims = g->nbitID;
	vb->dirty = g->nbitID;
}

