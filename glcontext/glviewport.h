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

#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue dirty;
	GLbitvalue v_dims;
	GLbitvalue s_dims;
	GLbitvalue enable;
	GLbitvalue depth;
} GLviewportbits;

typedef struct {

	GLconfig_GetWindowSize_func getwindowsize;

	/* Viewport state */
	GLint     v_x;
	GLint     v_y;
	GLint     v_w;
	GLint     v_h;
	GLclampd  n;
	GLclampd  f;
	GLboolean v_valid;

	/* Scissor state */
	GLboolean	scissortest;
	GLint		  s_x;
	GLint		  s_y;
	GLsizei		s_w;
	GLsizei		s_h;
	GLboolean s_valid;

	GLint maxviewportdims_width;
	GLint maxviewportdims_height;

} GLviewportstate;

void __glviewport_initbits (GLviewportbits *v, GLconfig *c);
void __glviewport_init(GLviewportstate *, GLconfig *c);
void __glviewport_destroy(GLviewportstate *);
void __glviewport_ApplyViewport(GLviewportstate *v, GLvectorf *p);

GLEXPORT void GLSTATE_DECL __glstate_Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
GLEXPORT void GLSTATE_DECL __glstate_DepthRange(GLclampd znear, GLclampd zfar);
GLEXPORT void GLSTATE_DECL __glstate_Scissor (GLint x, GLint y, GLsizei width, GLsizei height);

#ifdef __cplusplus
}
#endif

#endif
