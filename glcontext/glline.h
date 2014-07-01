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

#ifndef GLLINE_H
#define GLLINE_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue enable;
	GLbitvalue size;
	GLbitvalue width;
	GLbitvalue stipple;
	GLbitvalue dirty;
} GLlinebits;

typedef struct {
	GLboolean	linesmooth;
	GLboolean	linestipple;
	GLboolean	pointsmooth;

	GLfloat		pointsize;
	GLfloat		width;
	GLushort	pattern;
	GLint		repeat;
	GLfloat	aliasedpointsizerange_min;
	GLfloat aliasedpointsizerange_max;
	GLfloat	aliasedpointsizegranularity;
	GLfloat smoothpointsizerange_min;
	GLfloat smoothpointsizerange_max;
	GLfloat smoothpointgranularity;
	GLfloat aliasedlinewidth_min;
	GLfloat aliasedlinewidth_max;
	GLfloat aliasedlinegranularity;
	GLfloat smoothlinewidth_min;
	GLfloat smoothlinewidth_max;
	GLfloat smoothlinegranularity;
} GLlinestate;

void __glline_initbits (GLlinebits *l, GLconfig *c);
void __glline_init (GLlinestate *l, GLconfig *c);
void __glline_destroy (GLlinestate *);

GLEXPORT void GLSTATE_DECL __glstate_PointSize(GLfloat size);
GLEXPORT void GLSTATE_DECL __glstate_LineWidth(GLfloat width);
GLEXPORT void GLSTATE_DECL __glstate_LineStipple(GLuint factor, GLushort pattern);

#ifdef __cplusplus
}
#endif

#endif
