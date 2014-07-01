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

#ifndef GLPIXEL_H
#define GLPIXEL_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue dirty;
	GLbitvalue pack;
	GLbitvalue unpack;
	GLbitvalue transfer;
	GLbitvalue zoom;
} GLpixelbits;

typedef struct {
	GLint		maxpixelmaptable;

	GLint		unpackrowlength;
	GLint		unpackskiprows;
	GLint		unpackskippixels;
	GLint		unpackalignment;

	GLint		unpackimageheight;
	GLint		unpackskipimages;
	
	GLint		packrowlength;
	GLint		packskiprows;
	GLint		packskippixels;
	GLint		packalignment;
	
	GLint		packimageheight;
	GLint		packskipimages;

	GLint		indexshift;
	GLint		indexoffset;

	GLboolean	unpackswapbytes;
	GLboolean	unpacklsbfirst;
	GLboolean	packswapbytes;
	GLboolean	packlsbfirst;

	GLcolorf	scale;
	GLfloat		depthscale;
	
	GLcolorf	bias;
	GLfloat		depthbias;

	GLfloat		xzoom;
	GLfloat		yzoom;

	GLint		pixelmapmaxsize;

	GLfloat		*pixelmapitoi;
	GLfloat		*pixelmapstos;
	GLfloat		*pixelmapitor;
	GLfloat		*pixelmapitog;
	GLfloat		*pixelmapitob;
	GLfloat		*pixelmapitoa;
	GLfloat		*pixelmaprtor;
	GLfloat		*pixelmapgtog;
	GLfloat		*pixelmapbtob;
	GLfloat		*pixelmapatoa;

	GLint		pixelmapitoisize;
	GLint		pixelmapstossize;
	GLint		pixelmapitorsize;
	GLint		pixelmapitogsize;
	GLint		pixelmapitobsize;
	GLint		pixelmapitoasize;
	GLint		pixelmaprtorsize;
	GLint		pixelmapgtogsize;
	GLint		pixelmapbtobsize;
	GLint		pixelmapatoasize;
} GLpixelstate;

void __glpixel_initbits (GLpixelbits *p, GLconfig *c);
void __glpixel_init (GLpixelstate *, GLconfig *c);
void __glpixel_destroy (GLpixelstate *);
int __glpixel_getdata2Dsize (GLsizei width, GLsizei height,
					   GLenum format, GLenum type);
void __glpixel_getdata2D_p (GLpixelstate *p, GLvoid *dstptr, GLsizei width, 
						GLsizei height, GLenum format, GLenum type,
						const GLvoid *data);
void __glpixel_getdata2D (GLvoid *dstptr, GLsizei width, 
						GLsizei height, GLenum format, GLenum type,
						const GLvoid *data);
int __glpixel_getdata3Dsize (GLsizei width, GLsizei height,
					   GLsizei depth, GLenum format, GLenum type);
void __glpixel_getdata3D_p (GLpixelstate *p, GLvoid *dstptr, GLsizei width, 
						GLsizei height, GLsizei depth, GLenum format, GLenum type,
						const GLvoid *data);
void __glpixel_getdata3D (GLvoid *dstptr, GLsizei width, 
						GLsizei height, GLsizei depth, GLenum format, GLenum type,
						const GLvoid *data);

GLEXPORT void GLSTATE_DECL __glstate_PixelStoref (GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_PixelStorei (GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_PixelTransferf (GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_PixelTransferi (GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_PixelZoom (GLfloat xfactor, GLfloat yfactor);

GLEXPORT void GLSTATE_DECL __glstate_PixelMapfv (GLenum map, GLint mapsize, const GLfloat * values);
GLEXPORT void GLSTATE_DECL __glstate_PixelMapuiv (GLenum map, GLint mapsize, const GLuint * values);
GLEXPORT void GLSTATE_DECL __glstate_PixelMapusv (GLenum map, GLint mapsize, const GLushort * values);
GLEXPORT void GLSTATE_DECL __glstate_GetPixelMapfv (GLenum map, const GLfloat * values);
GLEXPORT void GLSTATE_DECL __glstate_GetPixelMapuiv (GLenum map, const GLuint * values);
GLEXPORT void GLSTATE_DECL __glstate_GetPixelMapusv (GLenum map, const GLushort * values);


#ifdef __cplusplus
}
#endif

#endif
