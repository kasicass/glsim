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
#include "glconfig.h"

void 
__glstencil_initbits (GLstencilbits *s, GLconfig *cfg) {
	/* do nothing */
	UNUSED(s);
	UNUSED(cfg);
}

void
__glstencil_init(GLstencilstate *s, GLconfig *cfg) {
	(void) cfg;
	s->stenciltest = GL_FALSE;
	s->func = GL_ALWAYS;
	s->mask = 0xFFFFFFFF;
	s->ref = 0;
	s->fail = GL_KEEP;
	s->passdepthfail = GL_KEEP;
	s->passdepthpass = GL_KEEP;
	s->clearvalue = 0;
	s->writemask = 0xFFFFFFFF;
}

void
__glstencil_destroy(GLstencilstate *s) {
	/* do nothing */
	(void) s;
}

void GLSTATE_DECL
__glstate_StencilFunc(GLenum func, GLint ref, GLuint mask) {
	GLcontext *g = GetCurrentContext();
	GLstencilstate *s = &(g->stencil);
	GLstatebits *stateb = GetStateBits();
	GLstencilbits *sb = &(stateb->stencil);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"glStencilFunc called in begin/end"))
			return;

 
		

	if (func != GL_NEVER &&
		func != GL_LESS &&
		func != GL_LEQUAL &&
		func != GL_GREATER &&
		func != GL_GEQUAL &&
		func != GL_EQUAL &&
		func != GL_NOTEQUAL &&
		func != GL_ALWAYS)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glStencilFunc called with bogu func: %d", func))
			return;
	/*ECHECK*/

	s->func = func;
	s->ref = ref;
	s->mask = mask;

	sb->func = g->nbitID;
	sb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_StencilOp (GLenum fail, GLenum zfail, GLenum zpass) {
	GLcontext *g = GetCurrentContext();
	GLstencilstate *s = &(g->stencil);
	GLstatebits *stateb = GetStateBits();
	GLstencilbits *sb = &(stateb->stencil);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"glStencilOp called in begin/end"))
			return;

 
		

	if (fail != GL_KEEP &&
		fail != GL_ZERO &&
		fail != GL_REPLACE &&
		fail != GL_INCR &&
		fail != GL_DECR &&
		fail != GL_INVERT) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glStencilOp called with bogus fail: %d", fail))
			return;

	if (zfail != GL_KEEP &&
		zfail != GL_ZERO &&
		zfail != GL_REPLACE &&
		zfail != GL_INCR &&
		zfail != GL_DECR &&
		zfail != GL_INVERT) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glStencilOp called with bogus zfail: %d", zfail))
			return;

	if (zpass != GL_KEEP &&
		zpass != GL_ZERO &&
		zpass != GL_REPLACE &&
		zpass != GL_INCR &&
		zpass != GL_DECR &&
		zpass != GL_INVERT) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glStencilOp called with bogus zpass: %d", zpass))
			return;
	/*ECHECK*/

	s->fail = fail;
	s->passdepthfail = zfail;
	s->passdepthpass = zpass;

	sb->op = g->nbitID;
	sb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_ClearStencil (GLint c) {
	GLcontext *g = GetCurrentContext();
	GLstencilstate *s = &(g->stencil);
	GLstatebits *stateb = GetStateBits();
	GLstencilbits *sb = &(stateb->stencil);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"glClearStencil called in begin/end"))
			return;

 
		
	/*ECHECK*/

	s->clearvalue = c;
	
	sb->clearvalue = g->nbitID;
	sb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_StencilMask (GLuint mask) {
	GLcontext *g = GetCurrentContext();
	GLstencilstate *s = &(g->stencil);
	GLstatebits *stateb = GetStateBits();
	GLstencilbits *sb = &(stateb->stencil);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, 
			"glStencilMask called in begin/end"))
			return;

 
		
	/*ECHECK*/

	s->mask = mask;

	sb->writemask = g->nbitID;
	sb->dirty = g->nbitID;
}
