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

#include <stdlib.h>
#include <stdio.h>
#include "glcontext.h"
#include "glcurrent.h"
#include "glerror.h"


void 
__glcurrent_initbits (GLcurrentbits *c, GLconfig *cfg) {
	/* do nothing */
	UNUSED(c);
	UNUSED(cfg);
}

void
__glcurrent_init (GLcurrentstate *c, GLconfig *cfg) {
	
	GLvectorf	zero_vector     = {0.0f, 0.0f, 0.0f, 1.0f};
	GLcolorf	one_color	      = {1.0f, 1.0f, 1.0f, 1.0f};
	GLtexcoordf zero_texcoord = {0.0f, 0.0f, 0.0f, 1.0f};

	UNUSED(cfg);

	c->color	= one_color;
	c->index	= 1.0f;
	c->texcoord = zero_texcoord;
	c->normal	= zero_vector;
	c->normal.z = 1.0f;

  c->rasterpos = zero_vector;

	c->rasterdistance = 0.0f;
	c->rastercolor    = one_color;
	c->rastertexture  = zero_texcoord;
	c->rastervalid    = GL_TRUE;
	c->rasterindex    = 1.0f;

	c->edgeflag = GL_TRUE;
	c->normalize = GL_FALSE;

	c->beginend = GL_FALSE;
	c->mode = 0x10; /* Undefined Mode */
}

void
__glcurrent_destroy (GLcurrentstate *c) {
/*
** Do Nothing
*/
	UNUSED(c);
}


void GLSTATE_DECL
__glstate_Begin (GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLcurrentstate *c = &g->current;

	if (mode > GL_POLYGON)
		if (__glerror (__LINE__, __FILE__, GL_INVALID_ENUM,
			"Begin called with invalid mode: %d", mode))
			return;

	if (c->beginend)
		if (__glerror (__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Begin called inside begin/end"))
			return;

	c->beginend = GL_TRUE;
	c->mode = mode;
}

void GLSTATE_DECL
__glstate_End (void) {
	GLcontext *g = GetCurrentContext();
	GLcurrentstate *c = &g->current;

	if (!c->beginend)
		if (__glerror (__LINE__, __FILE__, GL_INVALID_OPERATION,
			"End called without preceeding Begin"))
			return;

	c->beginend = GL_FALSE;
}
