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

#ifndef GLLIGHTING_H
#define GLLIGHTING_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue dirty;
	GLbitvalue enable;
	GLbitvalue ambient;
	GLbitvalue diffuse;
	GLbitvalue specular;
	GLbitvalue position;
	GLbitvalue attenuation;
	GLbitvalue spot;
} GLlightbits;

typedef struct {
	GLbitvalue dirty;
	GLbitvalue shademodel;
	GLbitvalue colormaterial;
	GLbitvalue lightmodel;
	GLbitvalue material;
	GLbitvalue enable;
	GLlightbits *light;
  GLint numlightbits;
} GLlightingbits;

typedef struct {
	GLboolean	enable;
	GLcolorf	ambient;
	GLcolorf	diffuse;
	GLcolorf	specular;
	GLvectorf	position;
	GLvectorf	objposition;
	GLfloat		constantattenuation;
	GLfloat		linearattenuation;
	GLfloat		quadraticattenuation;
	GLvectorf	spotdirection;
	GLfloat 	spotexponent;
	GLfloat		spotcutoff;
} GLlight;

typedef struct {
	GLboolean	lighting;
	GLboolean	colormaterial;
	GLenum		shademodel;
	GLenum		colormaterialmode;
	GLenum		colormaterialface;
	GLcolorf	ambient[2];
	GLcolorf	diffuse[2];
	GLcolorf	specular[2];
	GLcolorf	emission[2];
	GLfloat		shininess[2];
	GLcolorf	lightmodelambient;
	GLboolean	lightmodellocalviewer;
	GLboolean	lightmodeltwoside;
	GLlight		*light;
	GLint		maxlights;
} GLlightingstate;

void __gllighting_initbits (GLlightingbits *l, GLconfig *c);
void __gllighting_destroybits (GLlightingbits *l);

void __gllighting_init (GLlightingstate *l, GLconfig *c);
void __gllighting_destroy (GLlightingstate *);

GLEXPORT void GLSTATE_DECL __glstate_ShadeModel (GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_ColorMaterial (GLenum face, GLenum mode);

GLEXPORT void GLSTATE_DECL __glstate_LightModelf (GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_LightModeli (GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_LightModelfv (GLenum pname, const GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_LightModeliv (GLenum pname, const GLint *param);

GLEXPORT void GLSTATE_DECL __glstate_Lightf (GLenum light, GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_Lighti (GLenum light, GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_Lightfv (GLenum light, GLenum pname, const GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_Lightiv (GLenum light, GLenum pname, const GLint *param);

GLEXPORT void GLSTATE_DECL __glstate_Materialf (GLenum face, GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_Materiali (GLenum face, GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_Materialfv (GLenum face, GLenum pname, const GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_Materialiv (GLenum face, GLenum pname, const GLint *param);

GLEXPORT void GLSTATE_DECL __glstate_GetMaterialfv (GLenum face, GLenum pname, GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_GetMaterialiv (GLenum face, GLenum pname, GLint *param);
GLEXPORT void GLSTATE_DECL __glstate_GetLightfv (GLenum light, GLenum pname, GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_GetLightiv (GLenum light, GLenum pname, GLint *param);

#ifdef __cplusplus
}
#endif

#endif
