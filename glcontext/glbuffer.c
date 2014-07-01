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
__glbuffer_initbits (GLbufferbits *b, GLconfig *c) {
	/* do nothing */
	UNUSED(b);
	UNUSED(c);
}

void
__glbuffer_init(GLbufferstate *b, GLconfig *c) {

	GLcolorf zero_colorf = {0.0f, 0.0f, 0.0f, 0.0f};

	b->depthtest = GL_FALSE;
	b->blend = GL_FALSE;
	b->alphatest = GL_FALSE;
	b->logicop = GL_FALSE;
	b->dither = GL_FALSE;
	b->depthmask = GL_TRUE;

	b->alphatestfunc = GL_ALWAYS;
	b->alphatestref = 0;
	b->depthfunc = GL_LESS;
	b->blendsrc = GL_ONE;
	b->blenddst = GL_ZERO;
	b->blendcolor = zero_colorf;
	b->blendequation = GL_FUNC_ADD;
	b->logicopmode = GL_COPY;
	if (c->doublebuffer) {
		b->drawbuffer = GL_BACK;
		b->readbuffer = GL_BACK;
	} else {
		b->drawbuffer = GL_FRONT;
		b->readbuffer = GL_FRONT;
	}
	b->indexwritemask = 0xffffffff;
	b->colorwritemask.r = GL_TRUE;
	b->colorwritemask.g = GL_TRUE;
	b->colorwritemask.b = GL_TRUE;
	b->colorwritemask.a = GL_TRUE;
	b->colorclearvalue = zero_colorf;
	b->indexclearvalue = 0;
	b->depthclearvalue = (GLdefault) 1.0;
	b->accumclearvalue = zero_colorf;

	b->auxbuffers = c->auxbuffers;
	b->rgbamode = c->rgbamode;
	b->indexmode = c->indexmode;
	b->doublebuffer = c->doublebuffer;
	b->stereo = c->stereo;
	b->subpixelbits = c->subpixelbits;			
	b->redbits = c->redbits;
	b->greenbits = c->greenbits;
	b->bluebits = c->bluebits;
	b->alphabits = c->alphabits;
	b->depthbits = c->depthbits;
	b->stencilbits = c->stencilbits;
	b->accumredbits = c->accumredbits;
	b->accumgreenbits = c->accumgreenbits;
	b->accumbluebits = c->accumbluebits;
	b->accumalphabits = c->accumalphabits;
}

void
__glbuffer_destroy(GLbufferstate *b) {
	/* do nothing */
	UNUSED(b);
}

void GLSTATE_DECL
__glstate_AlphaFunc (GLenum func, GLclampf ref) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sb = GetStateBits();
	GLbufferbits *bufferbits = &(sb->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glAlphaFunc called in begin/end"))
			return;
	
	switch (func) {
	case GL_NEVER:
	case GL_LESS:
	case GL_EQUAL:
	case GL_LEQUAL:
	case GL_GREATER:
	case GL_GEQUAL:
	case GL_NOTEQUAL:
	case GL_ALWAYS:
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glAlphaFunc:  Invalid func: %d", func))
			return;
	}

	if (ref < 0.0f) ref = 0.0f;
	if (ref > 1.0f) ref = 1.0f;

/*ECHECK*/

	b->alphatestfunc = func;
	b->alphatestref = ref;
	bufferbits->dirty = g->nbitID;
	bufferbits->alphafunc = g->nbitID;
}

void GLSTATE_DECL
__glstate_DepthFunc (GLenum func) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sb = GetStateBits();
	GLbufferbits *bufferbits = &(sb->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glDepthFunc called in begin/end"))
			return;
	
	switch (func) {
	case GL_NEVER:
	case GL_LESS:
	case GL_EQUAL:
	case GL_LEQUAL:
	case GL_GREATER:
	case GL_NOTEQUAL:
	case GL_GEQUAL:
	case GL_ALWAYS:
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glDepthFunc:  Invalid func: %d", func))
			return;
	}

/*ECHECK*/

	b->depthfunc = func;
	bufferbits->dirty = g->nbitID;
	bufferbits->depthfunc = g->nbitID;
}

void GLSTATE_DECL
__glstate_BlendFunc (GLenum sfactor, GLenum dfactor) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sb = GetStateBits();
	GLbufferbits *bufferbits = &(sb->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glBlendFunc called in begin/end"))
			return;

	switch (sfactor) {
	case GL_ZERO:
	case GL_ONE:
	case GL_DST_COLOR:
	case GL_ONE_MINUS_DST_COLOR:
	case GL_SRC_ALPHA:
	case GL_ONE_MINUS_SRC_ALPHA:
	case GL_DST_ALPHA:
	case GL_ONE_MINUS_DST_ALPHA:
	case GL_SRC_ALPHA_SATURATE:
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid sfactor passed to glBlendFunc: %d", sfactor))
			return;
	}

	switch (dfactor) {
	case GL_ZERO:
	case GL_ONE:
	case GL_SRC_COLOR:
	case GL_ONE_MINUS_SRC_COLOR:
	case GL_SRC_ALPHA:
	case GL_ONE_MINUS_SRC_ALPHA:
	case GL_DST_ALPHA:
	case GL_ONE_MINUS_DST_ALPHA:
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid dfactor passed to glBlendFunc: %d", dfactor))
			return;
	}

/*ECHECK*/

	b->blendsrc = sfactor;
	b->blenddst = dfactor;
	bufferbits->dirty = g->nbitID;
	bufferbits->blendfunc = g->nbitID;
}

void GLSTATE_DECL
__glstate_LogicOp (GLenum opcode) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sb = GetStateBits();
	GLbufferbits *bufferbits = &(sb->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glLogicOp called in begin/end"))
			return;

	switch (opcode) {
	case GL_CLEAR:
	case GL_SET:
	case GL_COPY:
	case GL_COPY_INVERTED:
	case GL_NOOP:
	case GL_INVERT:
	case GL_AND:
	case GL_NAND:
	case GL_OR:
	case GL_NOR:
	case GL_XOR:
	case GL_EQUIV:
	case GL_AND_REVERSE:
	case GL_AND_INVERTED:
	case GL_OR_REVERSE:
	case GL_OR_INVERTED:
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glLogicOp called with bogus opcode: %d", opcode))
			return;
	}
/*ECHECK*/

	b->logicopmode = opcode;
	bufferbits->dirty = g->nbitID;
	bufferbits->logicop = g->nbitID;
}


void GLSTATE_DECL
__glstate_DrawBuffer (GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sb = GetStateBits();
	GLbufferbits *bufferbits = &(sb->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glDrawBuffer called in begin/end"))
			return;

	switch (mode) {
	case GL_NONE:
	case GL_FRONT_LEFT:
	case GL_FRONT_RIGHT:
	case GL_BACK_LEFT:
	case GL_BACK_RIGHT:
	case GL_FRONT:
	case GL_BACK:
	case GL_LEFT:
	case GL_RIGHT:
	case GL_FRONT_AND_BACK:
		break;
	default:
		if ((int) (mode - GL_AUX0) >= b->auxbuffers)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glDrawBuffer called with bogus mode: %d", mode))
				return;
	}
/*ECHECK*/

	b->drawbuffer = mode;
	bufferbits->dirty = g->nbitID;
	bufferbits->drawbuffer = g->nbitID;
}


void GLSTATE_DECL
__glstate_ReadBuffer (GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sb = GetStateBits();
	GLbufferbits *bufferbits = &(sb->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glReadBuffer called in begin/end"))
			return;

	switch (mode) {
	case GL_NONE:
	case GL_FRONT_LEFT:
	case GL_FRONT_RIGHT:
	case GL_BACK_LEFT:
	case GL_BACK_RIGHT:
	case GL_FRONT:
	case GL_BACK:
	case GL_LEFT:
	case GL_RIGHT:
	case GL_FRONT_AND_BACK:
		break;
	default:
		if ((int) (mode - GL_AUX0) >= b->auxbuffers)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glReadBuffer called with bogus mode: %d", mode))
				return;
	}

/*ECHECK*/

	b->readbuffer = mode;
	bufferbits->dirty = g->nbitID;
	bufferbits->readbuffer = g->nbitID;
}

void GLSTATE_DECL
__glstate_IndexMask (GLuint mask) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sp = GetStateBits();
	GLbufferbits *bufferbits = &(sp->buffer);


/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glReadBuffer called in begin/end"))
			return;

/*ECHECK*/

	b->indexwritemask = mask;
	bufferbits->dirty = g->nbitID;
	bufferbits->indexmask = g->nbitID;
}

void GLSTATE_DECL
__glstate_ColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sp = GetStateBits();
	GLbufferbits *bufferbits = &(sp->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glReadBuffer called in begin/end"))
			return;

/*ECHECK*/

	b->colorwritemask.r = red;
	b->colorwritemask.g = green;
	b->colorwritemask.b = blue;
	b->colorwritemask.a = alpha;
	bufferbits->dirty = g->nbitID;
	bufferbits->colorwritemask = g->nbitID;
}

void GLSTATE_DECL
__glstate_ClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sp = GetStateBits();
	GLbufferbits *bufferbits = &(sp->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glClearColor called in begin/end"))
			return;

	if (red < 0.0f) red = 0.0f;
	if (red > 1.0f) red = 1.0f;
	if (green < 0.0f) green = 0.0f;
	if (green > 1.0f) green = 1.0f;
	if (blue < 0.0f) blue = 0.0f;
	if (blue > 1.0f) blue = 1.0f;
	if (alpha < 0.0f) alpha = 0.0f;
	if (alpha > 1.0f) alpha = 1.0f;
/*ECHECK*/


	b->colorclearvalue.r = red;
	b->colorclearvalue.g = green;
	b->colorclearvalue.b = blue;
	b->colorclearvalue.a = alpha;
	bufferbits->dirty = g->nbitID;
	bufferbits->clearcolor = g->nbitID;
}

void GLSTATE_DECL
__glstate_ClearIndex (GLfloat c) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sp = GetStateBits();
	GLbufferbits *bufferbits = &(sp->buffer);


/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glClearIndex called in begin/end"))
			return;

 
		

/*ECHECK*/
	
	b->indexclearvalue = c;
	bufferbits->dirty = g->nbitID;
	bufferbits->clearindex = g->nbitID;
}

void GLSTATE_DECL
__glstate_ClearDepth (GLclampd depth) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sp = GetStateBits();
	GLbufferbits *bufferbits = &(sp->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glClearDepth called in begin/end"))
			return;

 
		

	if (depth < 0.0) depth = 0.0;
	if (depth > 1.0) depth = 1.0;

/*ECHECK*/
	b->depthclearvalue = (GLdefault) depth;
	bufferbits->dirty = g->nbitID;
	bufferbits->cleardepth = g->nbitID;
}

void GLSTATE_DECL
__glstate_ClearAccum (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *b = &(g->buffer);
	GLstatebits *sp = GetStateBits();
	GLbufferbits *bufferbits = &(sp->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glClearAccum called in begin/end"))
			return;
	
 
		
		
	if (red < -1.0f) red = 0.0f;
	if (red > 1.0f) red = 1.0f;
	if (green < -1.0f) green = 0.0f;
	if (green > 1.0f) green = 1.0f;
	if (blue < -1.0f) blue = 0.0f;
	if (blue > 1.0f) blue = 1.0f;
	if (alpha < -1.0f) alpha = 0.0f;
	if (alpha > 1.0f) alpha = 1.0f;
/*ECHECK*/

	b->accumclearvalue.r = red;
	b->accumclearvalue.g = green;
	b->accumclearvalue.b = blue;
	b->accumclearvalue.a = alpha;
	bufferbits->dirty = g->nbitID;
	bufferbits->clearaccum = g->nbitID;
}

void GLSTATE_DECL
__glstate_DepthMask (GLboolean b) {
	GLcontext *g = GetCurrentContext();
	GLbufferstate *bs = &(g->buffer);
	GLstatebits *sp = GetStateBits();
	GLbufferbits *bb = &(sp->buffer);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "DepthMask called in begin/end"))
			return;

 
		
/*ECHECK*/

	bs->depthmask = b;
	bb->dirty = g->nbitID;
	bb->depthmask = g->nbitID;
}

