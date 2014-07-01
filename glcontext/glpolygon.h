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

#ifndef GLPOLYGON_H
#define GLPOLYGON_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue enable;
	GLbitvalue offset;
	GLbitvalue mode;
	GLbitvalue stipple;
	GLbitvalue dirty;
} GLpolygonbits;

typedef struct {
	GLboolean	polygonsmooth;
	GLboolean   polygonoffset;
	GLboolean	polygonstipple;
	GLboolean   cullface;
	GLfloat		offsetfactor;
	GLfloat		offsetunits;
	GLenum		cullfacemode;
	GLenum		frontface;
	GLenum		frontmode;
	GLenum		backmode;
	GLint		stipple[32];
} GLpolygonstate;

void __glpolygone_initbits (GLpolygonbits *p, GLconfig *c);
void __glpolygon_init(GLpolygonstate *p, GLconfig *c);
void __glpolygon_destroy(GLpolygonstate *);

GLEXPORT void GLSTATE_DECL __glstate_PolygonOffset (GLfloat factor, GLfloat units);
GLEXPORT void GLSTATE_DECL __glstate_CullFace(GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_FrontFace (GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_PolygonMode (GLenum face, GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_PolygonStipple (const GLubyte *);
GLEXPORT void GLSTATE_DECL __glstate_GetPolygonStipple (GLubyte *);

#ifdef __cplusplus
}
#endif

#endif
