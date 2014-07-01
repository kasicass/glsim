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

#include <float.h>
#include "glcontext.h"
#include "glerror.h"

static const GLvectorf maxvector = {FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX};
static const GLvectorf minvector = {-FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX};

void 
__glhint_initbits (GLhintbits *h, GLconfig *cfg) {
	/* do nothing */
	UNUSED(h);
	UNUSED(cfg);
}

void
__glhint_init (GLhintstate *h, GLconfig *cfg) {

	UNUSED(cfg);

	h->perspectivecorrection = GL_DONT_CARE;
	h->fog = GL_DONT_CARE;
	h->linesmooth = GL_DONT_CARE;
	h->pointsmooth = GL_DONT_CARE;
	h->polygonsmooth = GL_DONT_CARE;
}

void
__glhint_destroy (GLhintstate *h) {
	/* do nothing */
	UNUSED(h);
}


void GLSTATE_DECL
__glstate_Hint (GLenum target, GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLhintstate *h = &(g->hint);
	GLstatebits *sb = GetStateBits();
	GLhintbits *hb = &(sb->hint);
	const GLbitvalue nbitID = g->nbitID;

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glHint called in begin/end"))
			return;

  /*ECHECK*/
		
	switch (target) {
	case GL_FOG_HINT:
		h->fog = mode;
		hb->dirty = nbitID;
		break;
	case GL_LINE_SMOOTH_HINT:
		h->linesmooth = mode;
		hb->dirty = nbitID;
		break;
	case GL_PERSPECTIVE_CORRECTION_HINT:
		h->perspectivecorrection = mode;
		hb->dirty = nbitID;
		break;
	case GL_POINT_SMOOTH_HINT:
		h->pointsmooth = mode;
		hb->dirty = nbitID;
		break;
	case GL_POLYGON_SMOOTH_HINT:
		h->polygonsmooth = mode;
		hb->dirty = nbitID;
		break;
	default:
		return;
	}
}

