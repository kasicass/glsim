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

#ifndef GLCURRENT_H
#define GLCURRENT_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLcurrentbits {
	GLbitvalue	dirty;
	GLbitvalue  enable;
	GLbitvalue	color;
	GLbitvalue	index;
	GLbitvalue	texcoord;
	GLbitvalue	normal;
	GLbitvalue	raster;
	GLbitvalue	edgeflag;
} GLcurrentbits; 

typedef struct GLvertex {
	GLvectorf	  pos;
	GLcolorf	  color;
	GLtexcoordf	texcoord;
	GLvectorf	  normal;
	GLboolean	  edgeflag;
	GLfloat		  index;
} GLvertex;

typedef struct GLcurrentstate {
	GLcolorf		color;
	GLfloat			index;
	GLtexcoordf	texcoord;
	GLvectorf		normal;
	GLboolean		edgeflag;
	
	GLvectorf		rasterpos;

	GLfloat     rasterdistance;
	GLcolorf    rastercolor;
	GLtexcoordf rastertexture;
	GLdouble    rasterindex;
	GLboolean   rastervalid;

	GLboolean   normalize;

	GLboolean   beginend;
	GLenum      mode;

} GLcurrentstate; 

void __glcurrent_initbits (GLcurrentbits *, GLconfig *);

void __glcurrent_init (GLcurrentstate *c, GLconfig *cfg);
void __glcurrent_destroy (GLcurrentstate *c);

GLEXPORT void GLSTATE_DECL __glstate_RasterPos2d(GLdouble x, GLdouble y);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos2f(GLfloat x, GLfloat y);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos2i(GLint x, GLint y);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos2s(GLshort x, GLshort y);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3d(GLdouble x, GLdouble y, GLdouble z);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3f(GLfloat x, GLfloat y, GLfloat z);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3i(GLint x, GLint y, GLint z);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3s(GLshort x, GLshort y, GLshort z);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4i(GLint x, GLint y, GLint z, GLint w);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos2dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos2fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos2iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos2sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos3sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_RasterPos4sv(const GLshort *v);

GLEXPORT void GLSTATE_DECL __glstate_Begin (GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_End (void);

GLEXPORT void GLSTATE_DECL __glstate_Indexub(GLubyte v0);
GLEXPORT void GLSTATE_DECL __glstate_Indexs(GLshort v0);
GLEXPORT void GLSTATE_DECL __glstate_Indexi(GLint v0);
GLEXPORT void GLSTATE_DECL __glstate_Indexf(GLfloat v0);
GLEXPORT void GLSTATE_DECL __glstate_Indexd(GLdouble v0);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1s(GLshort v0);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2s(GLshort v0, GLshort v1);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3s(GLshort v0, GLshort v1, GLshort v2);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4s(GLshort v0, GLshort v1, GLshort v2, GLshort v3);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1i(GLint v0);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2i(GLint v0, GLint v1);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3i(GLint v0, GLint v1, GLint v2);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4i(GLint v0, GLint v1, GLint v2, GLint v3);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1f(GLfloat v0);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2f(GLfloat v0, GLfloat v1);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3f(GLfloat v0, GLfloat v1, GLfloat v2);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1d(GLdouble v0);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2d(GLdouble v0, GLdouble v1);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3d(GLdouble v0, GLdouble v1, GLdouble v2);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4d(GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
GLEXPORT void GLSTATE_DECL __glstate_Normal3b(GLbyte v0, GLbyte v1, GLbyte v2);
GLEXPORT void GLSTATE_DECL __glstate_Normal3s(GLshort v0, GLshort v1, GLshort v2);
GLEXPORT void GLSTATE_DECL __glstate_Normal3i(GLint v0, GLint v1, GLint v2);
GLEXPORT void GLSTATE_DECL __glstate_Normal3f(GLfloat v0, GLfloat v1, GLfloat v2);
GLEXPORT void GLSTATE_DECL __glstate_Normal3d(GLdouble v0, GLdouble v1, GLdouble v2);
GLEXPORT void GLSTATE_DECL __glstate_EdgeFlag(GLboolean v0);
GLEXPORT void GLSTATE_DECL __glstate_Color3b(GLbyte v0, GLbyte v1, GLbyte v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4b(GLbyte v0, GLbyte v1, GLbyte v2, GLbyte v3);
GLEXPORT void GLSTATE_DECL __glstate_Color3ub(GLubyte v0, GLubyte v1, GLubyte v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4ub(GLubyte v0, GLubyte v1, GLubyte v2, GLubyte v3);
GLEXPORT void GLSTATE_DECL __glstate_Color3s(GLshort v0, GLshort v1, GLshort v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4s(GLshort v0, GLshort v1, GLshort v2, GLshort v3);
GLEXPORT void GLSTATE_DECL __glstate_Color3us(GLushort v0, GLushort v1, GLushort v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4us(GLushort v0, GLushort v1, GLushort v2, GLushort v3);
GLEXPORT void GLSTATE_DECL __glstate_Color3i(GLint v0, GLint v1, GLint v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4i(GLint v0, GLint v1, GLint v2, GLint v3);
GLEXPORT void GLSTATE_DECL __glstate_Color3ui(GLuint v0, GLuint v1, GLuint v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4ui(GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GLEXPORT void GLSTATE_DECL __glstate_Color3f(GLfloat v0, GLfloat v1, GLfloat v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
GLEXPORT void GLSTATE_DECL __glstate_Color3d(GLdouble v0, GLdouble v1, GLdouble v2);
GLEXPORT void GLSTATE_DECL __glstate_Color4d(GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
GLEXPORT void GLSTATE_DECL __glstate_Indexubv(const GLubyte *v);
GLEXPORT void GLSTATE_DECL __glstate_Indexsv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_Indexiv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_Indexfv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_Indexdv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord1dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord2dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord3dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_TexCoord4dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_Normal3bv(const GLbyte *v);
GLEXPORT void GLSTATE_DECL __glstate_Normal3sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_Normal3iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_Normal3fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_Normal3dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_EdgeFlagv(const GLboolean *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3bv(const GLbyte *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4bv(const GLbyte *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3ubv(const GLubyte *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4ubv(const GLubyte *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4sv(const GLshort *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3usv(const GLushort *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4usv(const GLushort *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4iv(const GLint *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3uiv(const GLuint *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4uiv(const GLuint *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4fv(const GLfloat *v);
GLEXPORT void GLSTATE_DECL __glstate_Color3dv(const GLdouble *v);
GLEXPORT void GLSTATE_DECL __glstate_Color4dv(const GLdouble *v);

#ifdef __cplusplus
}
#endif

#endif
