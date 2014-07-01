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

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "glcontext.h"
#include "glerror.h"

void 
__gllighting_initbits (GLlightingbits *l, GLconfig *c) {
	l->light = (GLlightbits *) malloc (sizeof(GLlightbits) * c->maxlight);
	memset (l->light, 0, sizeof(GLlightbits) * c->maxlight);
  l->numlightbits = c->maxlight;
}

void
__gllighting_destroybits (GLlightingbits *l) {
	free(l->light);
}


void
__gllighting_init (GLlightingstate *l, GLconfig *c) {
	int i;
	GLvectorf zero_vector	= {0.0f, 0.0f, 0.0f, 1.0f};
	GLcolorf zero_color		= {0.0f, 0.0f, 0.0f, 1.0f};
	GLcolorf ambient_color = {0.2f, 0.2f, 0.2f, 1.0f};
	GLcolorf diffuse_color = {0.8f, 0.8f, 0.8f, 1.0f};
	GLvectorf spot_vector	= {0.0f, 0.0f, -1.0f, 0.0f};
	GLcolorf one_color		= {1.0f, 1.0f, 1.0f, 1.0f};

	l->lighting = GL_FALSE;
	l->colormaterial = GL_FALSE;
	l->shademodel = GL_SMOOTH;
	l->colormaterialmode = GL_AMBIENT_AND_DIFFUSE;
	l->colormaterialface = GL_FRONT_AND_BACK;
	l->ambient[0] = ambient_color;
	l->diffuse[0] = diffuse_color;
	l->specular[0] = zero_color;
	l->emission[0] = zero_color;
	l->shininess[0] = 0.0f;
	l->ambient[1] = ambient_color;
	l->diffuse[1] = diffuse_color;
	l->specular[1] = zero_color;
	l->emission[1] = zero_color;
	l->shininess[1] = 0.0f;
	l->lightmodelambient = ambient_color;
	l->lightmodellocalviewer = GL_FALSE;
	l->lightmodeltwoside = GL_FALSE;
	l->maxlights = c->maxlight;
	
	l->light = (GLlight *) malloc (sizeof (GLlight) * l->maxlights);
	memset ((void *) l->light, 0, sizeof (GLlight) * l->maxlights);

	for (i=0; i<l->maxlights; i++) {
		l->light[i].enable = GL_FALSE;
		l->light[i].ambient = zero_color;
		l->light[i].diffuse = zero_color;
		l->light[i].specular = zero_color;
		l->light[i].position = zero_vector;
		l->light[i].position.z = 1.0f;
		l->light[i].position.w = 0.0f;
		l->light[i].objposition = l->light[i].position;
		l->light[i].spotdirection = spot_vector;
		l->light[i].spotexponent = 0.0f;
		l->light[i].spotcutoff = 180.0f;
		l->light[i].constantattenuation= 1.0f;
		l->light[i].linearattenuation= 0.0f;
		l->light[i].quadraticattenuation = 0.0f;
	}
	l->light[0].diffuse = one_color;
	l->light[0].specular = one_color;
}

void 
__gllighting_destroy (GLlightingstate *l) {
	free (l->light);
}

void GLSTATE_DECL
__glstate_ShadeModel (GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"ShadeModel called in begin/end"))
			return;

 
		

	if (mode != GL_SMOOTH &&
		mode != GL_FLAT)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"ShadeModel: Bogus mode %d", mode))
			return;
/*ECHECK*/

	l->shademodel = mode;
	lb->shademodel = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_ColorMaterial (GLenum face, GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"ColorMaterial called in begin/end"))
			return;
	
 
		

	if (face != GL_FRONT &&
		face != GL_BACK &&
		face != GL_FRONT_AND_BACK)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"ColorMaterial: Bogus face &d", face))
			return;

	if (mode != GL_EMISSION &&
		mode != GL_AMBIENT &&
		mode != GL_DIFFUSE &&
		mode != GL_SPECULAR &&
		mode != GL_AMBIENT_AND_DIFFUSE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"ColorMaterial: Bogus mode &d", mode))
			return;
/*ECHECK*/

	/* need to do more here than just setting the state.... */
	l->colormaterialface = face;
	l->colormaterialmode = mode;
	lb->colormaterial = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_LightModelf (GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"LightModelf called in begin/end"))
			return;

 
		
/*ECHECK*/

	switch (pname) {
	case GL_LIGHT_MODEL_LOCAL_VIEWER:
		l->lightmodellocalviewer = (GLboolean) (param==0.0f?GL_FALSE:GL_TRUE);
		break;
	case GL_LIGHT_MODEL_TWO_SIDE:
		l->lightmodeltwoside = (GLboolean) (param==0.0f?GL_FALSE:GL_TRUE);
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"LightModelf: Invalid pname: %d", pname))
			return;
/*ECHECK*/
	}


	lb->lightmodel = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_LightModeli (GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"LightModeli called in begin/end"))
			return;

 
		
/*ECHECK*/

	switch (pname) {
	case GL_LIGHT_MODEL_LOCAL_VIEWER:
		l->lightmodellocalviewer = (GLboolean) (param==0?GL_FALSE:GL_TRUE);
		break;
	case GL_LIGHT_MODEL_TWO_SIDE:
		l->lightmodeltwoside = (GLboolean) (param==0?GL_FALSE:GL_TRUE);
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"LightModeli: Invalid pname: %d", pname))
			return;
/*ECHECK*/
	}

	lb->lightmodel = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_LightModelfv (GLenum pname, const GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"LightModelfv called in begin/end"))
			return;

 
		
/*ECHECK*/

	switch (pname) {
	case GL_LIGHT_MODEL_LOCAL_VIEWER:
		l->lightmodellocalviewer = (GLboolean) (*param==0.0f?GL_FALSE:GL_TRUE);
		break;
	case GL_LIGHT_MODEL_TWO_SIDE:
		l->lightmodeltwoside = (GLboolean) (*param==0.0f?GL_FALSE:GL_TRUE);
		break;
	case GL_LIGHT_MODEL_AMBIENT:
		l->lightmodelambient.r = param[0];
		l->lightmodelambient.g = param[1];
		l->lightmodelambient.b = param[2];
		l->lightmodelambient.a = param[3];
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"LightModelfv: Invalid pname: %d", pname))
			return;
/*ECHECK*/
	}
	lb->lightmodel = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_LightModeliv (GLenum pname, const GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"LightModeliv called in begin/end"))
			return;

 
		
/*ECHECK*/

	switch (pname) {
	case GL_LIGHT_MODEL_LOCAL_VIEWER:
		l->lightmodellocalviewer = (GLboolean) (param==0?GL_FALSE:GL_TRUE);
		break;
	case GL_LIGHT_MODEL_TWO_SIDE:
		l->lightmodeltwoside = (GLboolean) (param==0?GL_FALSE:GL_TRUE);
		break;
	case GL_LIGHT_MODEL_AMBIENT:
		l->lightmodelambient.r = ((GLfloat)param[0])/GL_MAXINT;
		l->lightmodelambient.g = ((GLfloat)param[1])/GL_MAXINT;
		l->lightmodelambient.b = ((GLfloat)param[2])/GL_MAXINT;
		l->lightmodelambient.a = ((GLfloat)param[3])/GL_MAXINT;
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"LightModeliv: Invalid pname: %d", pname))
			return;
/*ECHECK*/
	}
	lb->lightmodel = g->nbitID;
	lb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_Lightf (GLenum light, GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLlight *lt;
	int i;
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);
	GLlightbits *ltb;

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glLightf called in begin/end"))
			return;

 
		

/*ECHECK*/

	i = light - GL_LIGHT0;

/*ECHECK*/
	if (i<0 || i>=l->maxlights)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glLight: invalid light specified: %d", light))
			return;
/*ECHECK*/

	lt = l->light + i;
	ltb = lb->light + i;

	switch (pname) {
	case GL_SPOT_EXPONENT:
/*ECHECK*/
		if (param < 0.0f || param > 180.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot exponent out of range: %f", param))
				return;
/*ECHECK*/
		lt->spotexponent = param;
		ltb->spot = g->nbitID;
		break;
	case GL_SPOT_CUTOFF:
/*ECHECK*/
		if ((param < 0.0f || param > 90.0f) && param != 180.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot cutoff out of range: %f", param))
				return;
/*ECHECK*/
		lt->spotcutoff = param;
		ltb->spot = g->nbitID;
		break;
	case GL_CONSTANT_ATTENUATION:
/*ECHECK*/
		if (param < 0.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: constant attenuation negative: %f", param))
				return;
/*ECHECK*/
		lt->constantattenuation = param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_LINEAR_ATTENUATION:
/*ECHECK*/
		if (param < 0.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: linear attenuation negative: %f", param))
				return;
/*ECHECK*/
		lt->linearattenuation = param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_QUADRATIC_ATTENUATION:
/*ECHECK*/
		if (param < 0.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: quadratic attenuation negative: %f", param))
				return;
/*ECHECK*/
		ltb->attenuation = g->nbitID;
		lt->quadraticattenuation = param;
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glLight: invalid pname: %d", pname))
			return;
		break;
/*ECHECK*/
	}
	ltb->dirty = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_Lighti (GLenum light, GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLlight *lt;
	int i;
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);
	GLlightbits *ltb;

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glLighti called in begin/end"))
			return;

 
		

/*ECHECK*/
	i = light - GL_LIGHT0;
/*ECHECK*/
	if (i<0 || i>=l->maxlights)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glLight: invalid light specified: %d", light))
			return;
/*ECHECK*/

	lt = l->light + i;
	ltb = lb->light + i;

	switch (pname) {
	case GL_SPOT_EXPONENT:
/*ECHECK*/
		if (param < 0 || param > 180)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot exponent out of range: %d", param))
				return;
/*ECHECK*/
		lt->spotexponent = (GLfloat) param;
		ltb->spot = g->nbitID;
		break;
	case GL_SPOT_CUTOFF:
/*ECHECK*/
		if ((param < 0 || param > 90) && param != 180)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot cutoff out of range: %d", param))
				return;
/*ECHECK*/
		lt->spotcutoff = (GLfloat) param;
		ltb->spot = g->nbitID;
		break;
	case GL_CONSTANT_ATTENUATION:
/*ECHECK*/
		if (param < 0)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: constant attenuation negative: %d", param))
				return;
/*ECHECK*/
		lt->constantattenuation = (GLfloat) param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_LINEAR_ATTENUATION:
/*ECHECK*/
		if (param < 0)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: linear attenuation negative: %d", param))
				return;
/*ECHECK*/
		lt->linearattenuation = (GLfloat) param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_QUADRATIC_ATTENUATION:
/*ECHECK*/
		if (param < 0)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: quadratic attenuation negative: %d", param))
				return;
/*ECHECK*/
		lt->quadraticattenuation = (GLfloat) param;
		ltb->attenuation = g->nbitID;
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glLight: invalid pname: %d", param))
			return;
		break;
/*ECHECK*/
	}
	ltb->dirty = g->nbitID;
	lb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_Lightfv (GLenum light, GLenum pname, const GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLtransstate *t = &(g->trans);
	GLlight *lt;
	int i;
	GLfloat x, y, z, w;
	GLmatrix inv;
	GLmatrix *mat;
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);
	GLlightbits *ltb;

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glLightfv called in begin/end"))
			return;

 
		

/*ECHECK*/
	i = light - GL_LIGHT0;
/*ECHECK*/
	if (i<0 || i>=l->maxlights)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glLight: invalid light specified: %d", light))
			return;
/*ECHECK*/

	lt = l->light + i;
	ltb = lb->light + i;

	switch (pname) {
	case GL_AMBIENT:
		lt->ambient.r = param[0];
		lt->ambient.g = param[1];
		lt->ambient.b = param[2];
		lt->ambient.a = param[3];
		ltb->ambient = g->nbitID;
		break;
	case GL_DIFFUSE:
		lt->diffuse.r = param[0];
		lt->diffuse.g = param[1];
		lt->diffuse.b = param[2];
		lt->diffuse.a = param[3];
		ltb->diffuse = g->nbitID;
		break;
	case GL_SPECULAR:
		lt->specular.r = param[0];
		lt->specular.g = param[1];
		lt->specular.b = param[2];
		lt->specular.a = param[3];
		ltb->specular = g->nbitID;
		break;
	case GL_POSITION:
		x = param[0];
		y = param[1];
		z = param[2];
		w = param[3];
		mat = t->modelview+t->modelviewdepth;

		lt->objposition.x = x;
		lt->objposition.y = y;
		lt->objposition.z = z;
		lt->objposition.w = w;

		lt->position.x = mat->m00*x + mat->m10*y + mat->m20*z + mat->m30*w; 
		lt->position.y = mat->m01*x + mat->m11*y + mat->m21*z + mat->m31*w; 
		lt->position.z = mat->m02*x + mat->m12*y + mat->m22*z + mat->m32*w; 
		lt->position.w = mat->m03*x + mat->m13*y + mat->m23*z + mat->m33*w;

		ltb->position = g->nbitID;
		break;
	case GL_SPOT_DIRECTION:
		lt->spotdirection.x = param[0];
		lt->spotdirection.y = param[1];
		lt->spotdirection.z = param[2];
		lt->spotdirection.w = 0.0f;
		mat = t->modelview+t->modelviewdepth;

		if (lt->objposition.w != 0.0f) {
			lt->spotdirection.w = - ( (	lt->objposition.x * lt->spotdirection.x +
						lt->objposition.y * lt->spotdirection.y +
						lt->objposition.z * lt->spotdirection.z ) /
						lt->objposition.w );
		}

		__gltrans_InvertTransposeMatrix (&inv, mat);
		__gltrans_TransformPointMatrixf (&inv, &(lt->spotdirection));

		ltb->spot = g->nbitID;
		break;
	case GL_SPOT_EXPONENT:
/*ECHECK*/
		if (*param < 0.0f || *param > 180.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot exponent out of range: %f", *param))
				return;
/*ECHECK*/
		lt->spotexponent = *param;
		ltb->spot = g->nbitID;
		break;
	case GL_SPOT_CUTOFF:
/*ECHECK*/
		if ((*param < 0.0f || *param > 90.0f) && *param != 180.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot cutoff out of range: %f", *param))
				return;
/*ECHECK*/
		lt->spotcutoff = *param;
		ltb->spot = g->nbitID;
		break;
	case GL_CONSTANT_ATTENUATION:
/*ECHECK*/
		if (*param < 0.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: constant attenuation negative: %f", *param))
				return;
/*ECHECK*/
		lt->constantattenuation = *param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_LINEAR_ATTENUATION:
/*ECHECK*/
		if (*param < 0.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: linear attenuation negative: %f", *param))
				return;
/*ECHECK*/
		lt->linearattenuation = *param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_QUADRATIC_ATTENUATION:
/*ECHECK*/
		if (*param < 0.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: quadratic attenuation negative: %f", *param))
				return;
/*ECHECK*/
		lt->quadraticattenuation = *param;
		ltb->attenuation = g->nbitID;
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glLight: invalid pname: %d", param))
			return;
		break;
/*ECHECK*/
	}
	ltb->dirty = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_Lightiv (GLenum light, GLenum pname, const GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLtransstate *t = &(g->trans);
	GLlight *lt;
	int i;
	GLfloat x, y, z, w;
	GLmatrix *mat;
	GLmatrix inv;
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);
	GLlightbits *ltb;

/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glLightiv called in begin/end"))
			return;

 
		

/*ECHECK*/
	i = light - GL_LIGHT0;
/*ECHECK*/
	if (i<0 || i>=l->maxlights)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glLight: invalid light specified: %d", light))
			return;
/*ECHECK*/

	lt = l->light + i;
	ltb = lb->light + i;

	switch (pname) {
	case GL_AMBIENT:
		lt->ambient.r = ((GLfloat)param[0])/GL_MAXINT;
		lt->ambient.g = ((GLfloat)param[1])/GL_MAXINT;
		lt->ambient.b = ((GLfloat)param[2])/GL_MAXINT;
		lt->ambient.a = ((GLfloat)param[3])/GL_MAXINT;
		ltb->ambient = g->nbitID;
		break;
	case GL_DIFFUSE:
		lt->diffuse.r = ((GLfloat)param[0])/GL_MAXINT;
		lt->diffuse.g = ((GLfloat)param[1])/GL_MAXINT;
		lt->diffuse.b = ((GLfloat)param[2])/GL_MAXINT;
		lt->diffuse.a = ((GLfloat)param[3])/GL_MAXINT;
		ltb->diffuse = g->nbitID;
		break;
	case GL_SPECULAR:
		lt->specular.r = ((GLfloat)param[0])/GL_MAXINT;
		lt->specular.g = ((GLfloat)param[1])/GL_MAXINT;
		lt->specular.b = ((GLfloat)param[2])/GL_MAXINT;
		lt->specular.a = ((GLfloat)param[3])/GL_MAXINT;
		ltb->specular = g->nbitID;
		break;
	case GL_POSITION:
		x = (GLfloat)param[0];
		y = (GLfloat)param[1];
		z = (GLfloat)param[2];
		w = (GLfloat)param[3];
		mat = t->modelview+t->modelviewdepth;

		lt->objposition.x = x;
		lt->objposition.y = y;
		lt->objposition.z = z;
		lt->objposition.w = w;

		lt->position.x = mat->m00*x + mat->m10*y + mat->m20*z + mat->m30*w; 
		lt->position.y = mat->m01*x + mat->m11*y + mat->m21*z + mat->m31*w; 
		lt->position.z = mat->m02*x + mat->m12*y + mat->m22*z + mat->m32*w; 
		lt->position.w = mat->m03*x + mat->m13*y + mat->m23*z + mat->m33*w;

		ltb->position = g->nbitID;
		break;
	case GL_SPOT_DIRECTION:
		lt->spotdirection.x = (GLfloat) param[0];
		lt->spotdirection.y = (GLfloat) param[1];
		lt->spotdirection.z = (GLfloat) param[2];
		lt->spotdirection.w = 0.0f;
		mat = t->modelview+t->modelviewdepth;

		if (lt->objposition.w != 0.0f) {
			lt->spotdirection.w = - ( (	lt->objposition.x * lt->spotdirection.x +
						lt->objposition.y * lt->spotdirection.y +
						lt->objposition.z * lt->spotdirection.z ) /
						lt->objposition.w );
		}

		__gltrans_InvertTransposeMatrix (&inv, mat);
		__gltrans_TransformPointMatrixf (&inv, &(lt->spotdirection));

		ltb->spot = g->nbitID;
		break;
	case GL_SPOT_EXPONENT:
/*ECHECK*/
		if (*param < 0 || *param > 180)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot exponent out of range: %d", *param))
				return;
/*ECHECK*/
		lt->spotexponent= (GLfloat) *param;
		ltb->spot = g->nbitID;
		break;
	case GL_SPOT_CUTOFF:
/*ECHECK*/
		if ((*param < 0 || *param > 90) && *param != 180)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: spot cutoff out of range: %d", *param))
				return;
/*ECHECK*/
		lt->spotcutoff= (GLfloat) *param;
		ltb->spot = g->nbitID;
		break;
	case GL_CONSTANT_ATTENUATION:
/*ECHECK*/
		if (*param < 0)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: constant attenuation negative: %d", *param))
				return;
/*ECHECK*/
		lt->constantattenuation= (GLfloat) *param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_LINEAR_ATTENUATION:
/*ECHECK*/
		if (*param < 0)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: linear attenuation negative: %d", *param))
				return;
/*ECHECK*/
		lt->linearattenuation= (GLfloat) *param;
		ltb->attenuation = g->nbitID;
		break;
	case GL_QUADRATIC_ATTENUATION:
/*ECHECK*/
		if (*param < 0)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
				"glLight: quadratic attenuation negative: %d", *param))
				return;
/*ECHECK*/
		lt->quadraticattenuation= (GLfloat) *param;
		ltb->attenuation = g->nbitID;
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glLight: invalid pname: %d", param))
			return;
		break;
/*ECHECK*/
	}
	ltb->dirty = g->nbitID;
	lb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_Materialf (GLenum face, GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);
	
/*ECHECK*/
  if (pname != GL_SHININESS)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glMaterialf: bad pname: %d", pname))
			return;

	if (param > 180.0f || param < 0.0f)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glMaterialf: param out of range: %f", param))
			return;
/*ECHECK*/

	switch (face) {
	case GL_FRONT:
		l->shininess[0] = param;
		break;
	case GL_FRONT_AND_BACK:
		l->shininess[0] = param;
	case GL_BACK:
		l->shininess[1] = param;
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glMaterialf: bad face: %d", face))
			return;
/*ECHECK*/
	}
	lb->material = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_Materiali (GLenum face, GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);

/*ECHECK*/

	if (pname != GL_SHININESS)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glMaterialf: bad pname: %d", pname))
			return;

	if (param > 180 || param < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glMaterialf: param out of range: %d", param))
			return;
/*ECHECK*/

	switch (face) {
	case GL_FRONT:
		l->shininess[0] = (GLfloat) param;
		break;
	case GL_FRONT_AND_BACK:
		l->shininess[0] = (GLfloat) param;
	case GL_BACK:
		l->shininess[1] = (GLfloat) param;
		break;
/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glMaterialf: bad face: %d", face))
			return;
/*ECHECK*/
	}
	lb->material = g->nbitID;
	lb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_Materialfv (GLenum face, GLenum pname, const GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);
	
	switch (pname) {
	case GL_AMBIENT :
		switch (face) {
		case GL_FRONT:
			l->ambient[0].r = param[0];
			l->ambient[0].g = param[1];
			l->ambient[0].b = param[2];
			l->ambient[0].a = param[3];
			break;
		case GL_FRONT_AND_BACK:
			l->ambient[0].r = param[0];
			l->ambient[0].g = param[1];
			l->ambient[0].b = param[2];
			l->ambient[0].a = param[3];
		case GL_BACK:
			l->ambient[1].r = param[0];
			l->ambient[1].g = param[1];
			l->ambient[1].b = param[2];
			l->ambient[1].a = param[3];
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glMaterialfv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_AMBIENT_AND_DIFFUSE :
		switch (face) {
		case GL_FRONT:
			l->ambient[0].r = param[0];
			l->ambient[0].g = param[1];
			l->ambient[0].b = param[2];
			l->ambient[0].a = param[3];
			break;
		case GL_FRONT_AND_BACK:
			l->ambient[0].r = param[0];
			l->ambient[0].g = param[1];
			l->ambient[0].b = param[2];
			l->ambient[0].a = param[3];
		case GL_BACK:
			l->ambient[1].r = param[0];
			l->ambient[1].g = param[1];
			l->ambient[1].b = param[2];
			l->ambient[1].a = param[3];
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialfv: bad face: %d", face))
				return;
/*ECHECK*/
		}
	case GL_DIFFUSE :
		switch (face) {
		case GL_FRONT:
			l->diffuse[0].r = param[0];
			l->diffuse[0].g = param[1];
			l->diffuse[0].b = param[2];
			l->diffuse[0].a = param[3];
			break;
		case GL_FRONT_AND_BACK:
			l->diffuse[0].r = param[0];
			l->diffuse[0].g = param[1];
			l->diffuse[0].b = param[2];
			l->diffuse[0].a = param[3];
		case GL_BACK:
			l->diffuse[1].r = param[0];
			l->diffuse[1].g = param[1];
			l->diffuse[1].b = param[2];
			l->diffuse[1].a = param[3];
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialfv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_SPECULAR :
		switch (face) {
		case GL_FRONT:
			l->specular[0].r = param[0];
			l->specular[0].g = param[1];
			l->specular[0].b = param[2];
			l->specular[0].a = param[3];
			break;
		case GL_FRONT_AND_BACK:
			l->specular[0].r = param[0];
			l->specular[0].g = param[1];
			l->specular[0].b = param[2];
			l->specular[0].a = param[3];
		case GL_BACK:
			l->specular[1].r = param[0];
			l->specular[1].g = param[1];
			l->specular[1].b = param[2];
			l->specular[1].a = param[3];
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialfv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_EMISSION :
		switch (face) {
		case GL_FRONT:
			l->emission[0].r = param[0];
			l->emission[0].g = param[1];
			l->emission[0].b = param[2];
			l->emission[0].a = param[3];
			break;
		case GL_FRONT_AND_BACK:
			l->emission[0].r = param[0];
			l->emission[0].g = param[1];
			l->emission[0].b = param[2];
			l->emission[0].a = param[3];
		case GL_BACK:
			l->emission[1].r = param[0];
			l->emission[1].g = param[1];
			l->emission[1].b = param[2];
			l->emission[1].a = param[3];
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialfv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_SHININESS:
/*ECHECK*/
		if (*param > 180.0f || *param < 0.0f)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, 
				"glMaterialfv: param out of range: %f", param))
				return;
/*ECHECK*/
		
		switch (face) {
		case GL_FRONT:
			l->shininess[0] = *param;
			break;
		case GL_FRONT_AND_BACK:
			l->shininess[0] = *param;
		case GL_BACK:
			l->shininess[1] = *param;
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialfv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
/*ECHECK*/
	case GL_COLOR_INDEXES :
		UNIMPLEMENTED();
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glMaterialfv: bad pname: %d", pname))
			return;
/*ECHECK*/
	}
	lb->material = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_Materialiv (GLenum face, GLenum pname, const GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLstatebits *sb = GetStateBits();
	GLlightingbits *lb = &(sb->lighting);
	
	switch (pname) {
	case GL_AMBIENT :
		switch (face) {
		case GL_FRONT:
			l->ambient[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
		case GL_FRONT_AND_BACK:
			l->ambient[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
		case GL_BACK:
			l->ambient[1].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->ambient[1].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->ambient[1].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->ambient[1].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialiv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_AMBIENT_AND_DIFFUSE :
		switch (face) {
		case GL_FRONT:
			l->ambient[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
		case GL_FRONT_AND_BACK:
			l->ambient[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->ambient[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
		case GL_BACK:
			l->ambient[1].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->ambient[1].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->ambient[1].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->ambient[1].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialiv: bad face: %d", face))
				return;
/*ECHECK*/
		}
	case GL_DIFFUSE :
		switch (face) {
		case GL_FRONT:
			l->diffuse[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->diffuse[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->diffuse[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->diffuse[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
		case GL_FRONT_AND_BACK:
			l->diffuse[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->diffuse[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->diffuse[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->diffuse[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
		case GL_BACK:
			l->diffuse[1].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->diffuse[1].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->diffuse[1].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->diffuse[1].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialiv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_SPECULAR :
		switch (face) {
		case GL_FRONT:
			l->specular[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->specular[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->specular[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->specular[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
		case GL_FRONT_AND_BACK:
			l->specular[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->specular[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->specular[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->specular[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
		case GL_BACK:
			l->specular[1].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->specular[1].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->specular[1].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->specular[1].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialiv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_EMISSION :
		switch (face) {
		case GL_FRONT:
			l->emission[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->emission[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->emission[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->emission[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
		case GL_FRONT_AND_BACK:
			l->emission[0].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->emission[0].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->emission[0].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->emission[0].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
		case GL_BACK:
			l->emission[1].r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
			l->emission[1].g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
			l->emission[1].b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
			l->emission[1].a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialiv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
	case GL_SHININESS:
/*ECHECK*/
		if (*param > 180 || *param < 0)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, 
				"glMaterialiv: param out of range: %d", param))
				return;
/*ECHECK*/
		
		switch (face) {
		case GL_FRONT:
			l->shininess[0] = (GLfloat) *param;
			break;
		case GL_FRONT_AND_BACK:
			l->shininess[0] = (GLfloat) *param;
		case GL_BACK:
			l->shininess[1] = (GLfloat) *param;
			break;
/*ECHECK*/
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glMaterialiv: bad face: %d", face))
				return;
/*ECHECK*/
		}
		break;
/*ECHECK*/
	case GL_COLOR_INDEXES :
		UNIMPLEMENTED();
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glMaterialiv: bad pname: %d", pname))
			return;
/*ECHECK*/
	}
	lb->material = g->nbitID;
	lb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_GetMaterialfv (GLenum face, GLenum pname, GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetMaterialfv called in begin/end"))
			return;

	switch (pname) {
	case GL_AMBIENT :
			switch (face) {
			case GL_FRONT:
				param[0] = l->ambient[0].r;
				param[1] = l->ambient[0].g;
				param[2] = l->ambient[0].b;
				param[3] = l->ambient[0].a;
				break;
			case GL_BACK:
				param[0] = l->ambient[1].r;
				param[1] = l->ambient[1].g;
				param[2] = l->ambient[1].b;
				param[3] = l->ambient[1].a;
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_DIFFUSE :
			switch (face) {
			case GL_FRONT:
				param[0] = l->diffuse[0].r;
				param[1] = l->diffuse[0].g;
				param[2] = l->diffuse[0].b;
				param[3] = l->diffuse[0].a;
				break;
			case GL_BACK:
				param[0] = l->diffuse[1].r;
				param[1] = l->diffuse[1].g;
				param[2] = l->diffuse[1].b;
				param[3] = l->diffuse[1].a;
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_SPECULAR :
			switch (face) {
			case GL_FRONT:
				param[0] = l->specular[0].r;
				param[1] = l->specular[0].g;
				param[2] = l->specular[0].b;
				param[3] = l->specular[0].a;
				break;
			case GL_BACK:
				param[0] = l->specular[1].r;
				param[1] = l->specular[1].g;
				param[2] = l->specular[1].b;
				param[3] = l->specular[1].a;
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_EMISSION :
			switch (face) {
			case GL_FRONT:
				param[0] = l->emission[0].r;
				param[1] = l->emission[0].g;
				param[2] = l->emission[0].b;
				param[3] = l->emission[0].a;
				break;
			case GL_BACK:
				param[0] = l->emission[1].r;
				param[1] = l->emission[1].g;
				param[2] = l->emission[1].b;
				param[3] = l->emission[1].a;
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_SHININESS:
		switch (face) {
		case GL_FRONT:
			*param = l->shininess[0];
			break;
		case GL_BACK:
			*param = l->shininess[1];
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glGetMaterialfv: bad face: %d", face))
				return;
		}
		break;
	case GL_COLOR_INDEXES :
		UNIMPLEMENTED();
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glGetMaterialfv: bad pname: %d", pname))
			return;
	}
}


void GLSTATE_DECL
__glstate_GetMaterialiv (GLenum face, GLenum pname, GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetMaterialfv called in begin/end"))
			return;

	switch (pname) {
	case GL_AMBIENT :
			switch (face) {
			case GL_FRONT:
				param[0] = (GLint) (l->ambient[0].r * GL_MAXINT);
				param[1] = (GLint) (l->ambient[0].g * GL_MAXINT);
				param[2] = (GLint) (l->ambient[0].b * GL_MAXINT);
				param[3] = (GLint) (l->ambient[0].a * GL_MAXINT);
				break;
			case GL_BACK:
				param[0] = (GLint) (l->ambient[1].r * GL_MAXINT);
				param[1] = (GLint) (l->ambient[1].g * GL_MAXINT);
				param[2] = (GLint) (l->ambient[1].b * GL_MAXINT);
				param[3] = (GLint) (l->ambient[1].a * GL_MAXINT);
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_DIFFUSE :
			switch (face) {
			case GL_FRONT:
				param[0] = (GLint) (l->diffuse[0].r * GL_MAXINT);
				param[1] = (GLint) (l->diffuse[0].g * GL_MAXINT);
				param[2] = (GLint) (l->diffuse[0].b * GL_MAXINT);
				param[3] = (GLint) (l->diffuse[0].a * GL_MAXINT);
				break;
			case GL_BACK:
				param[0] = (GLint) (l->diffuse[1].r * GL_MAXINT);
				param[1] = (GLint) (l->diffuse[1].g * GL_MAXINT);
				param[2] = (GLint) (l->diffuse[1].b * GL_MAXINT);
				param[3] = (GLint) (l->diffuse[1].a * GL_MAXINT);
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_SPECULAR :
			switch (face) {
			case GL_FRONT:
				param[0] = (GLint) (l->specular[0].r * GL_MAXINT);
				param[1] = (GLint) (l->specular[0].g * GL_MAXINT);
				param[2] = (GLint) (l->specular[0].b * GL_MAXINT);
				param[3] = (GLint) (l->specular[0].a * GL_MAXINT);
				break;
			case GL_BACK:
				param[0] = (GLint) (l->specular[1].r * GL_MAXINT);
				param[1] = (GLint) (l->specular[1].g * GL_MAXINT);
				param[2] = (GLint) (l->specular[1].b * GL_MAXINT);
				param[3] = (GLint) (l->specular[1].a * GL_MAXINT);
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_EMISSION :
			switch (face) {
			case GL_FRONT:
				param[0] = (GLint) (l->emission[0].r * GL_MAXINT);
				param[1] = (GLint) (l->emission[0].g * GL_MAXINT);
				param[2] = (GLint) (l->emission[0].b * GL_MAXINT);
				param[3] = (GLint) (l->emission[0].a * GL_MAXINT);
				break;
			case GL_BACK:
				param[0] = (GLint) (l->emission[1].r * GL_MAXINT);
				param[1] = (GLint) (l->emission[1].g * GL_MAXINT);
				param[2] = (GLint) (l->emission[1].b * GL_MAXINT);
				param[3] = (GLint) (l->emission[1].a * GL_MAXINT);
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
					"glGetMaterialfv: bad face: %d", face))
					return;
			}
			break;
	case GL_SHININESS:
		switch (face) {
		case GL_FRONT:
			*param = (GLint) l->shininess[0];
			break;
		case GL_BACK:
			*param = (GLint) l->shininess[1];
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
				"glGetMaterialfv: bad face: %d", face))
				return;
		}
		break;
	case GL_COLOR_INDEXES :
		UNIMPLEMENTED();
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glGetMaterialfv: bad pname: %d", pname))
			return;
	}
}


void GLSTATE_DECL
__glstate_GetLightfv (GLenum light, GLenum pname, GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLlight *lt;
	int i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetLightfv called in begin/end"))
			return;

	i = light - GL_LIGHT0;
	if (i<0 || i>=l->maxlights)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetLight: invalid light specified: %d", light))
			return;

	lt = l->light + i;

	switch (pname) {
	case GL_AMBIENT:
		param[0] = lt->ambient.r;
		param[1] = lt->ambient.g;
		param[2] = lt->ambient.b;
		param[3] = lt->ambient.a;
		break;
	case GL_DIFFUSE:
		param[0] = lt->diffuse.r;
		param[1] = lt->diffuse.g;
		param[2] = lt->diffuse.b;
		param[3] = lt->diffuse.a;
		break;
	case GL_SPECULAR:
		param[0] = lt->specular.r;
		param[1] = lt->specular.g;
		param[2] = lt->specular.b;
		param[3] = lt->specular.a;
		break;
	case GL_POSITION:
		param[0] = lt->position.x;
		param[1] = lt->position.y;
		param[2] = lt->position.z;
		param[3] = lt->position.w;
		break;
	case GL_SPOT_DIRECTION:
		param[0] = lt->spotdirection.x;
		param[1] = lt->spotdirection.y;
		param[2] = lt->spotdirection.z;
#if 0
		/* the w-component of the direction, although possibly (?)
           useful to keep around internally, is not returned as part
           of the get. */
		param[3] = lt->spotdirection.w;
#endif
		break;
	case GL_SPOT_EXPONENT:
		*param = lt->spotexponent;
		break;
	case GL_SPOT_CUTOFF:
		*param = lt->spotcutoff;
		break;
	case GL_CONSTANT_ATTENUATION:
		*param = lt->constantattenuation;
		break;
	case GL_LINEAR_ATTENUATION:
		*param = lt->linearattenuation;
		break;
	case GL_QUADRATIC_ATTENUATION:
		*param = lt->quadraticattenuation;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glGetLight: invalid pname: %d", param))
			return;
		break;
	}
}


void GLSTATE_DECL
__glstate_GetLightiv (GLenum light, GLenum pname, GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLlightingstate *l = &(g->lighting);
	GLlight *lt;
	int i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetLightiv called in begin/end"))
			return;

	i = light - GL_LIGHT0;
	if (i<0 || i>=l->maxlights)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetLight: invalid light specified: %d", light))
			return;

	lt = l->light + i;

	switch (pname) {
	case GL_AMBIENT:
		param[0] = (GLint) (lt->ambient.r * GL_MAXINT);
		param[1] = (GLint) (lt->ambient.g * GL_MAXINT);
		param[2] = (GLint) (lt->ambient.b * GL_MAXINT);
		param[3] = (GLint) (lt->ambient.a * GL_MAXINT);
		break;
	case GL_DIFFUSE:
		param[0] = (GLint) (lt->diffuse.r * GL_MAXINT);
		param[1] = (GLint) (lt->diffuse.g * GL_MAXINT);
		param[2] = (GLint) (lt->diffuse.b * GL_MAXINT);
		param[3] = (GLint) (lt->diffuse.a * GL_MAXINT);
		break;
	case GL_SPECULAR:
		param[0] = (GLint) (lt->specular.r * GL_MAXINT);
		param[1] = (GLint) (lt->specular.g * GL_MAXINT);
		param[2] = (GLint) (lt->specular.b * GL_MAXINT);
		param[3] = (GLint) (lt->specular.a * GL_MAXINT);
		break;
	case GL_POSITION:
		param[0] = (GLint) (lt->position.x);
		param[1] = (GLint) (lt->position.y);
		param[2] = (GLint) (lt->position.z);
		param[3] = (GLint) (lt->position.w);
		break;
	case GL_SPOT_DIRECTION:
		param[0] = (GLint) (lt->spotdirection.x);
		param[1] = (GLint) (lt->spotdirection.y);
		param[2] = (GLint) (lt->spotdirection.z);
#if 0
		/* the w-component of the direction, although possibly (?)
           useful to keep around internally, is not returned as part
           of the get. */
		param[3] = (GLint) (lt->spotdirection.w);
#endif
		break;
	case GL_SPOT_EXPONENT:
		*param = (GLint) (lt->spotexponent);
		break;
	case GL_SPOT_CUTOFF:
		*param = (GLint) (lt->spotcutoff);
		break;
	case GL_CONSTANT_ATTENUATION:
		*param = (GLint) (lt->constantattenuation);
		break;
	case GL_LINEAR_ATTENUATION:
		*param = (GLint) (lt->linearattenuation);
		break;
	case GL_QUADRATIC_ATTENUATION:
		*param = (GLint) (lt->quadraticattenuation);
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glGetLight: invalid pname: %d", param))
			return;
		break;
	}
}




