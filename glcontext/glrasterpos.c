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
__glrasterpos_UpdateRasterPos(GLcontext *g,
							  GLfloat x, GLfloat y, GLfloat z, GLfloat w) {

	GLcurrentstate *c = &(g->current);
	GLtransstate *t = &(g->trans);
	GLviewportstate *v = &(g->viewport);
	GLvectorf p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.w = w;

	__gltrans_TransformPoint(t, &p);	

	if (p.x > p.w ||
		p.y > p.w ||
		p.z > p.w ||
		p.x < -p.w ||
		p.y < -p.w ||
		p.z < -p.w) {
		c->rastervalid = GL_FALSE;
		return;
	} 

	p.x /= p.w;
	p.y /= p.w;
	p.z /= p.w;
	p.w = 1.0f;

	__glviewport_ApplyViewport(v, &p);

	c->rastervalid = GL_TRUE;
	c->rasterpos = p;

	/*
	**  Need handle these for glGet...
	**  c->rasterdistance;
	**  c->rastercolor;
	**  c->rasterindex;
	**  c->rastertexture;
	*/
}

void GLSTATE_DECL __glstate_RasterPos2d(GLdouble x, GLdouble y) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos2f(GLfloat x, GLfloat y) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,x, y, 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos2i(GLint x, GLint y) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos2s(GLshort x, GLshort y) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, (GLfloat) z, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,x, y, z, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3i(GLint x, GLint y, GLint z) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

  __glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, (GLfloat) z, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3s(GLshort x, GLshort y, GLshort z) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, (GLfloat) z, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, (GLfloat) z, (GLfloat) w);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

	__glrasterpos_UpdateRasterPos(g,x, y, z, w);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4i(GLint x, GLint y, GLint z, GLint w) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, (GLfloat) z, (GLfloat) w);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) x, (GLfloat) y, (GLfloat) z, (GLfloat) w);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos2dv(const GLdouble *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos2fv(const GLfloat *v) {
  GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,v[0], v[1], 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos2iv(const GLint *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos2sv(const GLshort *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], 0.0f, 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3dv(const GLdouble *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3fv(const GLfloat *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,v[0], v[1], v[2], 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3iv(const GLint *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos3sv(const GLshort *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], 1.0f);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4dv(const GLdouble *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], (GLfloat) v[3]);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4fv(const GLfloat *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,v[0], v[1], v[2], v[3]);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4iv(const GLint *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], (GLfloat) v[3]);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}

void GLSTATE_DECL __glstate_RasterPos4sv(const GLshort *v) {
	GLcontext *g = GetCurrentContext();
  GLstatebits *sb = GetStateBits();
  GLcurrentbits *cb = &(sb->current);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "RasterPos called in Begin/End"))
			return;

 
    

	__glrasterpos_UpdateRasterPos(g,(GLfloat) v[0], (GLfloat) v[1], (GLfloat) v[2], (GLfloat) v[3]);

	cb->dirty = g->nbitID;
	cb->raster = g->nbitID;
}
