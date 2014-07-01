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

#ifndef GLTRANS_H
#define GLTRANS_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue dirty;
	GLbitvalue mode;
	GLbitvalue matrix[4];
	GLbitvalue clipplane;
	GLbitvalue enable;
	GLbitvalue base;
} GLtransbits;

typedef struct {
	GLenum		mode;
	GLint		matrixid;

	GLint		maxmodelviewstackdepth;
	GLint		maxprojectionstackdepth;
	GLint		maxtexturestackdepth;
	GLint		maxcolorstackdepth;
	GLint		maxdepth;

	GLint		modelviewdepth;
	GLint		projectiondepth;
	GLint		texturedepth;
	GLint		colordepth;
	GLint		*depth;

	GLint		maxclipplanes;
	GLvectord	*clipplane;
	GLboolean	*clip;

	GLmatrix	*modelview;
	GLmatrix	*projection;
	GLmatrix	*texture;
	GLmatrix	*color;
	GLmatrix	*m;

	GLmatrix	baseprojection;
	GLboolean	usebase;

	/* Stuff for bucketing */
	/* Context Switch for this???? */
	GLboolean	transformvalid;
	GLmatrix	transform;

} GLtransstate;

void __gltrans_initbits		(GLtransbits *t, GLconfig *c);
void __gltrans_init			(GLtransstate *, GLconfig *);
void __gltrans_destroy		(GLtransstate *);
void __gltrans_UpdateTransform (GLtransstate *t);
void __gltrans_TransformPoint  (GLtransstate *t, GLvectorf *p);
void __gltrans_TransformPointMatrixf(GLmatrix *m, GLvectorf *p);
void __gltrans_TransformPointMatrixd(GLmatrix *m, GLvectord *p);
void __gltrans_InvertTransposeMatrix(GLmatrix *inv, GLmatrix *mat);
void __gltrans_normalizedims (GLrectf *p, GLrecti *r, GLrecti *q);


GLEXPORT void GLSTATE_DECL __glstate_ClipPlane	(const GLenum plane, const GLdouble *equation);
GLEXPORT void GLSTATE_DECL __glstate_GetClipPlane	(const GLenum plane, GLdouble *equation);
GLEXPORT void GLSTATE_DECL __glstate_MatrixMode	(const GLenum e);
GLEXPORT void GLSTATE_DECL __glstate_LoadIdentity(void);
GLEXPORT void GLSTATE_DECL __glstate_PopMatrix	(void);
GLEXPORT void GLSTATE_DECL __glstate_PushMatrix	(void);
GLEXPORT void GLSTATE_DECL __glstate_LoadMatrixf	(const GLfloat *);
GLEXPORT void GLSTATE_DECL __glstate_LoadMatrixd	(const GLdouble *);
GLEXPORT void GLSTATE_DECL __glstate_MultMatrixf	(const GLfloat *);
GLEXPORT void GLSTATE_DECL __glstate_MultMatrixd	(const GLdouble *);
GLEXPORT void GLSTATE_DECL __glstate_Translatef	(const GLfloat, const GLfloat, const GLfloat);
GLEXPORT void GLSTATE_DECL __glstate_Translated	(const GLdouble, const GLdouble, const GLdouble);
GLEXPORT void GLSTATE_DECL __glstate_Rotatef		(const GLfloat, GLfloat, GLfloat, GLfloat);
GLEXPORT void GLSTATE_DECL __glstate_Rotated		(const GLdouble, GLdouble, GLdouble, GLdouble);
GLEXPORT void GLSTATE_DECL __glstate_Scalef		(const GLfloat, const GLfloat, const GLfloat);
GLEXPORT void GLSTATE_DECL __glstate_Scaled		(const GLdouble, const GLdouble, const GLdouble);
GLEXPORT void GLSTATE_DECL __glstate_Frustum		(const GLdouble, const GLdouble,
										const GLdouble, const GLdouble, 
										const GLdouble, const GLdouble);
GLEXPORT void GLSTATE_DECL __glstate_Ortho ( GLdouble, GLdouble,
									GLdouble, GLdouble,
									GLdouble, GLdouble);

#ifdef __cplusplus
}
#endif

#endif
