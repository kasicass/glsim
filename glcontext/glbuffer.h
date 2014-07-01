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

#ifndef GLBUFFER_H
#define GLBUFFER_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue	dirty;
	GLbitvalue  enable;
	GLbitvalue	alphafunc;
	GLbitvalue	depthfunc;
	GLbitvalue	blendfunc;
	GLbitvalue	blendcolor;
	GLbitvalue	blendequation;
	GLbitvalue	logicop;
	GLbitvalue	drawbuffer;
	GLbitvalue	readbuffer;
	GLbitvalue	indexmask;
	GLbitvalue	colorwritemask;
	GLbitvalue	clearcolor;
	GLbitvalue	clearindex;
	GLbitvalue	cleardepth;
	GLbitvalue	clearaccum;
	GLbitvalue  depthmask;
} GLbufferbits;

typedef struct {

	GLboolean	depthtest;
	GLboolean	blend;
	GLboolean	alphatest;
	GLboolean	logicop;
	GLboolean	dither;
	GLboolean   depthmask;

	GLenum		alphatestfunc;
	GLfloat		alphatestref;
	GLenum		depthfunc;
	GLenum		blendsrc;
	GLenum		blenddst;
	GLcolorf	blendcolor;	
	GLenum		blendequation;
	GLenum		logicopmode;
	GLenum		drawbuffer;
	GLenum		readbuffer;
	GLint		indexwritemask;
	GLcolorb	colorwritemask;
	GLcolorf	colorclearvalue;
	GLfloat 	indexclearvalue;
	GLdefault	depthclearvalue;
	GLcolorf	accumclearvalue;

	/* static config state */
	GLint	auxbuffers;
	GLboolean	rgbamode;
	GLboolean	indexmode;
	GLboolean	doublebuffer;
	GLboolean	stereo;
	GLint	subpixelbits;			
	GLint	redbits;
	GLint	greenbits;
	GLint	bluebits;
	GLint	alphabits;
	GLint	depthbits;
	GLint	stencilbits;
	GLint	accumredbits;
	GLint	accumgreenbits;
	GLint	accumbluebits;
	GLint	accumalphabits;
} GLbufferstate;


void __glbuffer_initbits(GLbufferbits *b, GLconfig *c);
void __glbuffer_init(GLbufferstate *b, GLconfig *c);
void __glbuffer_destroy(GLbufferstate *);

GLEXPORT void GLSTATE_DECL __glstate_AlphaFunc (GLenum func, GLclampf ref);
GLEXPORT void GLSTATE_DECL __glstate_DepthFunc (GLenum func);
GLEXPORT void GLSTATE_DECL __glstate_BlendFunc (GLenum sfactor, GLenum dfactor);
GLEXPORT void GLSTATE_DECL __glstate_LogicOp (GLenum opcode);
GLEXPORT void GLSTATE_DECL __glstate_DrawBuffer (GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_ReadBuffer (GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_IndexMask (GLuint mask);
GLEXPORT void GLSTATE_DECL __glstate_ColorMask (GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GLEXPORT void GLSTATE_DECL __glstate_ClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GLEXPORT void GLSTATE_DECL __glstate_ClearIndex (GLfloat c);
GLEXPORT void GLSTATE_DECL __glstate_ClearDepth (GLclampd depth);
GLEXPORT void GLSTATE_DECL __glstate_ClearAccum(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GLEXPORT void GLSTATE_DECL __glstate_DepthMask(GLboolean b);

#ifdef __cplusplus
}
#endif

#endif
