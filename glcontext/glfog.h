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

#ifndef GLFOG_H
#define GLFOG_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue dirty;
	GLbitvalue color;
	GLbitvalue index;
	GLbitvalue density;
	GLbitvalue start;
	GLbitvalue end;
	GLbitvalue mode;
	GLbitvalue enable;
} GLfogbits;

typedef struct {
	GLcolorf	color;
	GLint		index;
	GLfloat		density;
	GLfloat		start;
	GLfloat		end;
	GLint		mode;
	GLboolean   enable;
} GLfogstate;

void __glfog_initbits (GLfogbits *e, GLconfig *c);
void __glfog_init(GLfogstate *f, GLconfig *c);
void __glfog_destroy(GLfogstate *);

GLEXPORT void GLSTATE_DECL __glstate_Fogf(GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_Fogi(GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_Fogiv(GLenum pname, const GLint *param);
GLEXPORT void GLSTATE_DECL __glstate_Fogfv(GLenum pname, const GLfloat *param);

#ifdef __cplusplus
}
#endif

#endif
