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

#ifndef GLEVAL_H
#define GLEVAL_H

#include "gltypes.h"
#include "glconfig.h"

#define GLEVAL_TOT 9

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue eval1d[GLEVAL_TOT];
	GLbitvalue eval2d[GLEVAL_TOT];
	GLbitvalue enable;
	GLbitvalue enable1d[GLEVAL_TOT];
	GLbitvalue enable2d[GLEVAL_TOT];
	GLbitvalue grid1d;
	GLbitvalue grid2d;
	GLbitvalue dirty;
} GLevalbits;

typedef struct {
	GLdouble	u1, u2;
	GLint		order;
	GLdouble	*coeff;
} GLeval1d;

typedef struct {
	GLdouble	u1, u2;
	GLdouble	v1, v2;
	GLint		uorder;
	GLint		vorder;
	GLdouble	*coeff;
} GLeval2d;

typedef struct {
	GLboolean	enable1d[GLEVAL_TOT];
	GLboolean	enable2d[GLEVAL_TOT];
	GLboolean	autonormal;

	GLint	maxevalorder;

	GLeval1d	eval1d[GLEVAL_TOT];
	GLeval2d	eval2d[GLEVAL_TOT];

	GLint		un1d;
	GLdouble	u11d, u21d;

	GLint		un2d;
	GLint		vn2d;
	GLdouble	u12d, u22d;
	GLdouble	v12d, v22d;
} GLevalstate;

extern const int gleval_sizes[];

void __gleval_initbits (GLevalbits *, GLconfig *);
void __gleval_init (GLevalstate *e, GLconfig *c);
void __gleval_destroy (GLevalstate *);

GLEXPORT void GLSTATE_DECL __glstate_Map1d (GLenum target, GLdouble u1, GLdouble u2, 
				 GLint stride, GLint order, const GLdouble *points);
GLEXPORT void GLSTATE_DECL __glstate_Map1f (GLenum target, GLfloat u1, GLfloat u2, 
					  GLint stride, GLint order, const GLfloat *points);
GLEXPORT void GLSTATE_DECL __glstate_Map2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder,
					 GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
GLEXPORT void GLSTATE_DECL __glstate_Map2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder,
					 GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
GLEXPORT void GLSTATE_DECL __glstate_MapGrid1d (GLint un, GLdouble u1, GLdouble u2);
GLEXPORT void GLSTATE_DECL __glstate_MapGrid1f (GLint un, GLfloat u1, GLfloat u2);
GLEXPORT void GLSTATE_DECL __glstate_MapGrid2d (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
GLEXPORT void GLSTATE_DECL __glstate_MapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);

GLEXPORT void GLSTATE_DECL __glstate_GetMapdv (GLenum target, GLenum query, GLdouble * v);
GLEXPORT void GLSTATE_DECL __glstate_GetMapfv (GLenum target, GLenum query, GLfloat * v);
GLEXPORT void GLSTATE_DECL __glstate_GetMapiv (GLenum target, GLenum query, GLint * v);

#ifdef __cplusplus
}
#endif

#endif

