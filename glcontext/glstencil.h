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

#ifndef GLSTENCIL_H
#define GLSTENCIL_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue dirty;
	GLbitvalue enable;
	GLbitvalue func;
	GLbitvalue op;
	GLbitvalue clearvalue;
	GLbitvalue writemask;
} GLstencilbits;

typedef struct {
	GLboolean	stenciltest;
	GLenum		func;
	GLint		mask;
	GLint		ref;
	GLenum		fail;
	GLenum		passdepthfail;
	GLenum		passdepthpass;
	GLint		clearvalue;
	GLint		writemask;
} GLstencilstate;

void __glstencil_initbits (GLstencilbits *s, GLconfig *c);

void __glstencil_init(GLstencilstate *s, GLconfig *c);
void __glstencil_destroy(GLstencilstate *);

GLEXPORT void GLSTATE_DECL __glstate_StencilFunc(GLenum func, GLint ref, GLuint mask);
GLEXPORT void GLSTATE_DECL __glstate_StencilOp (GLenum fail, GLenum zfail, GLenum zpass);
GLEXPORT void GLSTATE_DECL __glstate_ClearStencil (GLint c);
GLEXPORT void GLSTATE_DECL __glstate_StencilMask (GLuint mask);

#ifdef __cplusplus
}
#endif

#endif
