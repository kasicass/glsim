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

#include "glcontext.h"
#include "glerror.h"

void 
__glfog_initbits (GLfogbits *f, GLconfig *cfg) {
	/* do nothing */
	UNUSED(f);
	UNUSED(cfg);
}

void
__glfog_init(GLfogstate *f, GLconfig *cfg) {

	UNUSED(cfg);

	f->color.r = 0.0f;
	f->color.g = 0.0f;
	f->color.b = 0.0f;
	f->color.a = 0.0f;

	f->density = 1.0f;
	f->end = 1.0f;
	f->start = 0.0f;
	f->mode = GL_EXP;
	f->index = 0;
	f->enable = GL_FALSE;
}

void
__glfog_destroy(GLfogstate *f) {
/*
** Do nothing
*/
	UNUSED(f);
}

void GLSTATE_DECL
__glstate_Fogf(GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLfogstate *f = &(g->fog);
	GLstatebits *sb = GetStateBits();
	GLfogbits *fb = &(sb->fog);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glFogf called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch (pname) {
	case GL_FOG_MODE:
		{
			GLenum e = (GLenum) param;
	/*ECHECK*/
			if (e != GL_LINEAR && e != GL_EXP && e != GL_EXP2)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid param for glFog: %d", e))
					return;
	/*ECHECK*/
			f->mode = e;
			fb->dirty = g->nbitID;
			fb->mode = g->nbitID;
		}
		break;
	case GL_FOG_DENSITY:
		f->density = param;
	/*ECHECK*/
		if (f->density < 0.0f)
			f->density = 0.0f;
	/*ECHECK*/
		fb->dirty = g->nbitID;
		fb->density = g->nbitID;
		break;
	case GL_FOG_START:
		f->start = param;
		fb->dirty = g->nbitID;
		fb->start = g->nbitID;
		break;
	case GL_FOG_END:
		f->end = param;
		fb->dirty = g->nbitID;
		fb->end = g->nbitID;
		break;
	case GL_FOG_INDEX:
		f->index = (GLint) param;
		fb->dirty = g->nbitID;
		fb->index = g->nbitID;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid glFog Param: %d", param))
			return;
	/*ECHECK*/
	}
}


void GLSTATE_DECL
__glstate_Fogi(GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLfogstate *f = &(g->fog);
	GLstatebits *sb = GetStateBits();
	GLfogbits *fb = &(sb->fog);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glFogi called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch (pname) {
	case GL_FOG_MODE:
		{
			GLenum e = (GLenum) param;
	/*ECHECK*/
			if (e != GL_LINEAR && e != GL_EXP && e != GL_EXP2)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid param for glFog: %d", e))
					return;
	/*ECHECK*/
			f->mode = e;
			fb->dirty = g->nbitID;
			fb->mode = g->nbitID;
		}
		break;
	case GL_FOG_DENSITY:
		f->density = ((GLfloat) param) / ((GLfloat) GL_MAXINT);
	/*ECHECK*/
		if (f->density < 0.0f)
			f->density = 0.0f;
	/*ECHECK*/
		fb->dirty = g->nbitID;
		fb->density = g->nbitID;
		break;
	case GL_FOG_START:
		f->start = ((GLfloat) param) / ((GLfloat) GL_MAXINT);
		fb->dirty = g->nbitID;
		fb->start = g->nbitID;
		break;
	case GL_FOG_END:
		f->end = ((GLfloat) param) / ((GLfloat) GL_MAXINT);
		fb->dirty = g->nbitID;
		fb->end = g->nbitID;
		break;
	case GL_FOG_INDEX:
		f->index = param;
		fb->dirty = g->nbitID;
		fb->index = g->nbitID;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid glFog Param: %d", param))
			return;
	/*ECHECK*/
	}
}


void GLSTATE_DECL
__glstate_Fogiv(GLenum pname, const GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLfogstate *f = &(g->fog);
	GLstatebits *sb = GetStateBits();
	GLfogbits *fb = &(sb->fog);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glFogiv called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch (pname) {
	case GL_FOG_MODE:
		{
			GLenum e = (GLenum) *param;
	/*ECHECK*/
			if (e != GL_LINEAR && e != GL_EXP && e != GL_EXP2)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid param for glFog: %d", e))
					return;
	/*ECHECK*/
			f->mode = e;
			fb->dirty = g->nbitID;
			fb->mode = g->nbitID;
		}
		break;
	case GL_FOG_DENSITY:
		f->density = ((GLfloat) *param) / ((GLfloat) GL_MAXINT);
	/*ECHECK*/
		if (f->density < 0.0f)
			f->density = 0.0f;
	/*ECHECK*/
		fb->dirty = g->nbitID;
		fb->density = g->nbitID;
		break;
	case GL_FOG_START:
		f->start = ((GLfloat) *param) / ((GLfloat) GL_MAXINT);
		fb->dirty = g->nbitID;
		fb->start = g->nbitID;
		break;
	case GL_FOG_END:
		f->end = ((GLfloat) *param) / ((GLfloat) GL_MAXINT);
		fb->dirty = g->nbitID;
		fb->end = g->nbitID;
		break;
	case GL_FOG_INDEX:
		f->index = *param;
		fb->dirty = g->nbitID;
		fb->index = g->nbitID;
		break;
	case GL_FOG_COLOR:
		f->color.r = ((GLfloat) param[0]) / ((GLfloat) GL_MAXINT);
		f->color.g = ((GLfloat) param[1]) / ((GLfloat) GL_MAXINT);
		f->color.b = ((GLfloat) param[2]) / ((GLfloat) GL_MAXINT);
		f->color.a = ((GLfloat) param[3]) / ((GLfloat) GL_MAXINT);
		fb->dirty = g->nbitID;
		fb->color = g->nbitID;
		break;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid glFog Param: %d", param))
			return;
	/*ECHECK*/
	}
}


void GLSTATE_DECL
__glstate_Fogfv(GLenum pname, const GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLfogstate *f = &(g->fog);
	GLstatebits *sb = GetStateBits();
	GLfogbits *fb = &(sb->fog);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glFogfv called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch (pname) {
	case GL_FOG_MODE:
		{
			GLenum e = (GLenum) *param;
	/*ECHECK*/
			if (e != GL_LINEAR && e != GL_EXP && e != GL_EXP2)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid param for glFog: %d", e))
					return;
	/*ECHECK*/
			f->mode = e;
			fb->dirty = g->nbitID;
			fb->mode = g->nbitID;
		}
		break;
	case GL_FOG_DENSITY:
		f->density = *param;
	/*ECHECK*/
		if (f->density < 0.0f)
			f->density = 0.0f;
	/*ECHECK*/
		fb->dirty = g->nbitID;
		fb->density = g->nbitID;
		break;
	case GL_FOG_START:
		f->start = *param;
		fb->dirty = g->nbitID;
		fb->start = g->nbitID;
		break;
	case GL_FOG_END:
		f->end = *param;
		fb->dirty = g->nbitID;
		fb->end = g->nbitID;
		break;
	case GL_FOG_INDEX:
		f->index = (GLint) *param;
		fb->dirty = g->nbitID;
		fb->index = g->nbitID;
		break;
	case GL_FOG_COLOR:
		f->color.r = param[0];
		f->color.g = param[1];
		f->color.b = param[2];
		f->color.a = param[3];
		fb->dirty = g->nbitID;
		fb->color = g->nbitID;
		break;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid glFog Param: %d", param))
			return;
	/*ECHECK*/
	}
}



