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

#include <math.h>
#include <assert.h>
#ifdef WINDOWS
#pragma warning( disable : 4514 )  
#endif

static const GLmatrix identity_matrix = { 
	(GLdefault) 1.0, (GLdefault) 0.0, (GLdefault) 0.0, (GLdefault) 0.0,
	(GLdefault) 0.0, (GLdefault) 1.0, (GLdefault) 0.0, (GLdefault) 0.0,
	(GLdefault) 0.0, (GLdefault) 0.0, (GLdefault) 1.0, (GLdefault) 0.0,
	(GLdefault) 0.0, (GLdefault) 0.0, (GLdefault) 0.0, (GLdefault) 1.0
};

#define TRANSLATECODE { \
	const GLdefault x = (GLdefault) x_arg;	\
	const GLdefault y = (GLdefault) y_arg;	\
	const GLdefault z = (GLdefault) z_arg;	\
	m->m30 = m->m00*x + m->m10*y + m->m20*z + m->m30;	\
	m->m31 = m->m01*x + m->m11*y + m->m21*z + m->m31;	\
	m->m32 = m->m02*x + m->m12*y + m->m22*z + m->m32;	\
	m->m33 = m->m03*x + m->m13*y + m->m23*z + m->m33;	\
}
#ifndef M_PI
#define M_PI             3.14159265358979323846
#endif


#ifdef GL_DEFAULTTYPE_FLOAT

#define LOADMATRIX(a) \
{ \
GLfloat f[16]; \
f[0] = (a)->m00; f[1] = (a)->m01; f[2] = (a)->m02; f[3] = (a)->m03; \
f[4] = (a)->m10; f[5] = (a)->m11; f[6] = (a)->m12; f[7] = (a)->m13; \
f[8] = (a)->m20; f[9] = (a)->m21; f[10] = (a)->m22; f[11] = (a)->m23; \
f[12] = (a)->m30; f[13] = (a)->m31; f[14] = (a)->m32; f[15] = (a)->m33; \
__glhw_LoadMatrixf((const GLfloat *) f); \
}

#endif

#ifdef GL_DEFAULTTYPE_DOUBLE

#define LOADMATRIX(a) \
{ \
GLdouble f[16]; \
f[0] = (a)->m00; f[1] = (a)->m01; f[2] = (a)->m02; f[3] = (a)->m03; \
f[4] = (a)->m10; f[5] = (a)->m11; f[6] = (a)->m12; f[7] = (a)->m13; \
f[8] = (a)->m20; f[9] = (a)->m21; f[10] = (a)->m22; f[11] = (a)->m23; \
f[12] = (a)->m30; f[13] = (a)->m31; f[14] = (a)->m32; f[15] = (a)->m33; \
__glhw_LoadMatrixd((const GLdouble *) f); \
}
#endif

/*INCLUDE*/

void 
__gltrans_initbits (GLtransbits *t, GLconfig *cfg) {
	UNUSED(cfg);
	t->dirty = GLBITS_ONES;
	t->matrix[1] = GLBITS_ONES;
}

void
__gltrans_init(GLtransstate *t, GLconfig *c) {
	int i;
	
	t->mode = GL_MODELVIEW;
	t->matrixid = 0;

	t->maxmodelviewstackdepth = c->maxmodelviewstackdepth;
	t->maxprojectionstackdepth = c->maxprojectionstackdepth;
	t->maxtexturestackdepth = c->maxtexturestackdepth;
	t->maxcolorstackdepth = c->maxcolorstackdepth;
	t->maxdepth = t->maxmodelviewstackdepth;

	if (t->maxmodelviewstackdepth)
		t->modelview = (GLmatrix *) malloc (sizeof (GLmatrix) * t->maxmodelviewstackdepth);
	if (t->maxprojectionstackdepth)
		t->projection = (GLmatrix *) malloc (sizeof (GLmatrix) * t->maxprojectionstackdepth);
	if (t->maxtexturestackdepth)
		t->texture = (GLmatrix *) malloc (sizeof (GLmatrix) * t->maxtexturestackdepth);
	if (t->maxcolorstackdepth)
		t->color = (GLmatrix *) malloc (sizeof (GLmatrix) * t->maxcolorstackdepth);

	t->modelview[0] = identity_matrix;
	t->projection[0] = identity_matrix;
	t->texture[0] = identity_matrix;
	t->color[0] = identity_matrix;
	t->m = t->modelview;

	t->modelviewdepth = 0;
	t->projectiondepth = 0;
	t->texturedepth = 0;
	t->colordepth = 0;
	t->depth = &t->modelviewdepth;

	t->maxclipplanes = c->maxclipplanes;

	t->clipplane = NULL;
	t->clip = NULL;
	if (t->maxclipplanes) {
		t->clipplane = (GLvectord *) malloc (sizeof (GLvectord) * t->maxclipplanes);
		t->clip = (GLboolean *) malloc (sizeof (GLboolean) * t->maxclipplanes);
		for (i=0; i<t->maxclipplanes; i++) {
			t->clipplane[i].x = 0.0f;
			t->clipplane[i].y = 0.0f;
			t->clipplane[i].z = 0.0f;
			t->clipplane[i].w = 0.0f;
			t->clip[i] = GL_FALSE;
		}
	}

	t->transformvalid = 0;
}

void
__gltrans_destroy(GLtransstate *t) {
	if (t->modelview)
		free (t->modelview);
	if (t->projection)
		free (t->projection);
	if (t->texture)
		free (t->texture);
	if (t->color)
		free (t->color);

	if (t->clipplane)
		free(t->clipplane);
	if (t->clip)
		free(t->clip);
}

void
__gltrans_UpdateTransform (GLtransstate *t) {
	GLmatrix *m1 = &t->projection[t->projectiondepth];
	GLmatrix *m2 = &t->modelview[t->modelviewdepth];
	GLmatrix *m = &(t->transform);
	const GLdefault lm00 = m1->m00;  
	const GLdefault lm01 = m1->m01;  
	const GLdefault lm02 = m1->m02;	
	const GLdefault lm03 = m1->m03;	
	const GLdefault lm10 = m1->m10;	
	const GLdefault lm11 = m1->m11;	
	const GLdefault lm12 = m1->m12;	
	const GLdefault lm13 = m1->m13;	
	const GLdefault lm20 = m1->m20;	
	const GLdefault lm21 = m1->m21;	
	const GLdefault lm22 = m1->m22;	
	const GLdefault lm23 = m1->m23;	
	const GLdefault lm30 = m1->m30;	
	const GLdefault lm31 = m1->m31;	
	const GLdefault lm32 = m1->m32;		
	const GLdefault lm33 = m1->m33;		
	const GLdefault rm00 = m2->m00;  
	const GLdefault rm01 = m2->m01;  
	const GLdefault rm02 = m2->m02;	
	const GLdefault rm03 = m2->m03;	
	const GLdefault rm10 = m2->m10;	
	const GLdefault rm11 = m2->m11;	
	const GLdefault rm12 = m2->m12;	
	const GLdefault rm13 = m2->m13;	
	const GLdefault rm20 = m2->m20;	
	const GLdefault rm21 = m2->m21;	
	const GLdefault rm22 = m2->m22;	
	const GLdefault rm23 = m2->m23;	
	const GLdefault rm30 = m2->m30;	
	const GLdefault rm31 = m2->m31;	
	const GLdefault rm32 = m2->m32;		
	const GLdefault rm33 = m2->m33;	
	m->m00 = lm00*rm00 + lm10*rm01 + lm20*rm02 + lm30*rm03;	
	m->m01 = lm01*rm00 + lm11*rm01 + lm21*rm02 + lm31*rm03;	
	m->m02 = lm02*rm00 + lm12*rm01 + lm22*rm02 + lm32*rm03;	
	m->m03 = lm03*rm00 + lm13*rm01 + lm23*rm02 + lm33*rm03;	
	m->m10 = lm00*rm10 + lm10*rm11 + lm20*rm12 + lm30*rm13;	
	m->m11 = lm01*rm10 + lm11*rm11 + lm21*rm12 + lm31*rm13;	
	m->m12 = lm02*rm10 + lm12*rm11 + lm22*rm12 + lm32*rm13;	
	m->m13 = lm03*rm10 + lm13*rm11 + lm23*rm12 + lm33*rm13;	
	m->m20 = lm00*rm20 + lm10*rm21 + lm20*rm22 + lm30*rm23;	
	m->m21 = lm01*rm20 + lm11*rm21 + lm21*rm22 + lm31*rm23;	
	m->m22 = lm02*rm20 + lm12*rm21 + lm22*rm22 + lm32*rm23;	
	m->m23 = lm03*rm20 + lm13*rm21 + lm23*rm22 + lm33*rm23;	
	m->m30 = lm00*rm30 + lm10*rm31 + lm20*rm32 + lm30*rm33;	
	m->m31 = lm01*rm30 + lm11*rm31 + lm21*rm32 + lm31*rm33;	
	m->m32 = lm02*rm30 + lm12*rm31 + lm22*rm32 + lm32*rm33;	
	m->m33 = lm03*rm30 + lm13*rm31 + lm23*rm32 + lm33*rm33;
	t->transformvalid = 1;
}

void
__gltrans_TransformPoint(GLtransstate *t, GLvectorf *p) {
	GLmatrix *m;
	GLfloat x = p->x;
	GLfloat y = p->y;
	GLfloat z = p->z;
	GLfloat w = p->w;

	if (!t->transformvalid)
		__gltrans_UpdateTransform(t);

	m = &(t->transform);
	
	p->x = m->m00*x + m->m10*y + m->m20*z + m->m30*w;
	p->y = m->m01*x + m->m11*y + m->m21*z + m->m31*w;
	p->z = m->m02*x + m->m12*y + m->m22*z + m->m32*w;
	p->w = m->m03*x + m->m13*y + m->m23*z + m->m33*w;
}

void
__gltrans_TransformPointMatrixf(GLmatrix *m, GLvectorf *p) {
	GLfloat x = p->x;
	GLfloat y = p->y;
	GLfloat z = p->z;
	GLfloat w = p->w;
	
	p->x = m->m00*x + m->m10*y + m->m20*z + m->m30*w;
	p->y = m->m01*x + m->m11*y + m->m21*z + m->m31*w;
	p->z = m->m02*x + m->m12*y + m->m22*z + m->m32*w;
	p->w = m->m03*x + m->m13*y + m->m23*z + m->m33*w;
}

void
__gltrans_TransformPointMatrixd(GLmatrix *m, GLvectord *p) {
	GLdouble x = p->x;
	GLdouble y = p->y;
	GLdouble z = p->z;
	GLdouble w = p->w;
	
	p->x = (GLdouble) (m->m00*x + m->m10*y + m->m20*z + m->m30*w);
	p->y = (GLdouble) (m->m01*x + m->m11*y + m->m21*z + m->m31*w);
	p->z = (GLdouble) (m->m02*x + m->m12*y + m->m22*z + m->m32*w);
	p->w = (GLdouble) (m->m03*x + m->m13*y + m->m23*z + m->m33*w);
}


void
__gltrans_InvertTransposeMatrix(GLmatrix *inv, GLmatrix *mat) {
    /* Taken from Pomegranite code, trans.c.
	** Note: We have our data structures reversed
	*/
	GLdefault m00 = mat->m00;
    GLdefault m01 = mat->m10;
    GLdefault m02 = mat->m20;
    GLdefault m03 = mat->m30;

    GLdefault m10 = mat->m01;
    GLdefault m11 = mat->m11;
    GLdefault m12 = mat->m21;
    GLdefault m13 = mat->m31;

    GLdefault m20 = mat->m02;
    GLdefault m21 = mat->m12;
    GLdefault m22 = mat->m22;
    GLdefault m23 = mat->m32;

    GLdefault m30 = mat->m03;
    GLdefault m31 = mat->m13;
    GLdefault m32 = mat->m23;
    GLdefault m33 = mat->m33;

#define det3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3) \
(a1 * (b2 * c3 - b3 * c2) + \
 b1 * (c2 * a3 - a2 * c3) + \
 c1 * (a2 * b3 - a3 * b2))

    GLdefault cof00 = det3x3( m11, m12, m13,
                             m21, m22, m23,
                             m31, m32, m33 );

    GLdefault cof01 = -det3x3( m12, m13, m10,
                              m22, m23, m20,
                              m32, m33, m30 );

    GLdefault cof02 = det3x3( m13, m10, m11,
                             m23, m20, m21,
                             m33, m30, m31 );

    GLdefault cof03 = -det3x3( m10, m11, m12,
                              m20, m21, m22,
                              m30, m31, m32 );


    GLdefault inv_det = ((GLdefault) 1.0) / ( m00 * cof00 + m01 * cof01 +
                               m02 * cof02 + m03 * cof03 );


    GLdefault cof10 = -det3x3( m21, m22, m23,
                              m31, m32, m33,
                              m01, m02, m03 );

    GLdefault cof11 = det3x3( m22, m23, m20,
                             m32, m33, m30,
                             m02, m03, m00 );

    GLdefault cof12 = -det3x3( m23, m20, m21,
                              m33, m30, m31,
                              m03, m00, m01 );

    GLdefault cof13 = det3x3( m20, m21, m22,
                             m30, m31, m32,
                             m00, m01, m02 );



    GLdefault cof20 = det3x3( m31, m32, m33,
                             m01, m02, m03,
                             m11, m12, m13 );

    GLdefault cof21 = -det3x3( m32, m33, m30,
                              m02, m03, m00,
                              m12, m13, m10 );

    GLdefault cof22 = det3x3( m33, m30, m31,
                             m03, m00, m01,
                             m13, m10, m11 );

    GLdefault cof23 = -det3x3( m30, m31, m32,
                              m00, m01, m02,
                              m10, m11, m12 );


    GLdefault cof30 = -det3x3( m01, m02, m03,
                              m11, m12, m13,
                              m21, m22, m23 );

    GLdefault cof31 = det3x3( m02, m03, m00,
                             m12, m13, m10,
                             m22, m23, m20 );

    GLdefault cof32 = -det3x3( m03, m00, m01,
                              m13, m10, m11,
                              m23, m20, m21 );

    GLdefault cof33 = det3x3( m00, m01, m02,
                             m10, m11, m12,
                             m20, m21, m22 );

#undef det3x3

/* Perform transpose in asignment */

    inv->m00 = cof00 * inv_det;
    inv->m10 = cof01 * inv_det;
    inv->m20 = cof02 * inv_det;
    inv->m30 = cof03 * inv_det;

    inv->m01 = cof10 * inv_det;
    inv->m11 = cof11 * inv_det;
    inv->m21 = cof12 * inv_det;
    inv->m31 = cof13 * inv_det;

    inv->m02 = cof20 * inv_det;
    inv->m12 = cof21 * inv_det;
    inv->m22 = cof22 * inv_det;
    inv->m32 = cof23 * inv_det;

    inv->m03 = cof30 * inv_det;
    inv->m13 = cof31 * inv_det;
    inv->m23 = cof32 * inv_det;
    inv->m33 = cof33 * inv_det;
}


float _vmult(float *m, float x, float y, float z) {
	return m[0]*x + 
		   m[4]*y +
		   m[8]*z +
		   m[12];
}

void GLSTATE_DECL
__glstate_ClipPlane (const GLenum plane, const GLdouble *equation) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &g->trans;
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLvectord e;
	int i;
	GLmatrix inv;

	e.x = equation[0];
	e.y = equation[1];
	e.z = equation[2];
	e.w = equation[3];

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"ClipPlane called in begin/end"))
			return;

 
		
	/*ECHECK*/

	i = plane - GL_CLIP_PLANE0;
	/*ECHECK*/
	if (i >= t->maxclipplanes)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"ClipPlane called with bad enumerant: %d", plane))
			return;
	/*ECHECK*/

	__gltrans_InvertTransposeMatrix (&inv, t->modelview+t->modelviewdepth);
	__gltrans_TransformPointMatrixd (&inv, &e);
	t->clipplane[i] = e;
	tb->clipplane = g->nbitID;
	tb->dirty = g->nbitID;
}

void  GLSTATE_DECL
__glstate_GetClipPlane (const GLenum plane, GLdouble *equation) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &g->trans;
	int i;
	
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetClipPlane called in begin/end"))
			return;

	i = plane - GL_CLIP_PLANE0;
	if (i >= t->maxclipplanes)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"GetClipPlane called with bad enumerant: %d", plane))
			return;

	equation[0] = t->clipplane[i].x;
	equation[1] = t->clipplane[i].x;
	equation[2] = t->clipplane[i].x;
	equation[3] = t->clipplane[i].x;
}

void GLSTATE_DECL
__glstate_MatrixMode(const GLenum e) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &g->trans;
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"MatrixMode called in begin/end"))
			return;

 
		
	/*ECHECK*/

	switch (e) {
	case GL_MODELVIEW:
		t->m = t->modelview+t->modelviewdepth;
		t->depth = &t->modelviewdepth;
		t->maxdepth = t->maxmodelviewstackdepth;
		t->mode = GL_MODELVIEW;
		t->matrixid = 0;
	break;
	case GL_PROJECTION:
		t->m = t->projection+t->projectiondepth;
		t->depth = &t->projectiondepth;
		t->maxdepth = t->maxprojectionstackdepth;
		t->mode = GL_PROJECTION;
		t->matrixid = 1;
	break;
	case GL_TEXTURE:
		t->m = t->texture+t->texturedepth;
		t->depth = &t->texturedepth;
		t->maxdepth = t->maxtexturestackdepth;
		t->mode = GL_TEXTURE;
		t->matrixid = 2;
	break;
	case GL_COLOR:
		t->m = t->color+t->colordepth;
		t->depth = &t->colordepth;
		t->maxdepth = t->maxcolorstackdepth;
		t->mode = GL_COLOR;
		t->matrixid = 3;
	break;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"Invalid matrix mode: %d", e))
			return;
	/*ECHECK*/
	}
	tb->mode = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_LoadIdentity() {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"LoadIdentity called in begin/end"))
			return;

 
		
	/*ECHECK*/

	*(t->m) = identity_matrix;
	t->transformvalid = 0;

	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_PopMatrix() {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &g->trans;
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"PopMatrix called in begin/end"))
			return;

 
		

	if (*(t->depth) == 0)
		if (__glerror(__LINE__, __FILE__, GL_STACK_UNDERFLOW,
			"PopMatrix of empty stack."))
			return;
	/*ECHECK*/

	if ( *t->depth < 0 && *t->depth >= t->maxdepth ) {
	  __glerror( __LINE__, __FILE__, GL_STACK_UNDERFLOW, "PopMatrix!" );
	  abort( );
	}
	
	t->m--;
	(*t->depth)--;

	t->transformvalid = 0;

	tb->matrix[t->matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_PushMatrix() {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &g->trans;
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"PushMatrix called in begin/end"))
			return;

 
		

	if (*(t->depth)+1 == t->maxdepth)
		if (__glerror(__LINE__, __FILE__, GL_STACK_OVERFLOW,
			"PushMatrix pass the end of allocated stack"))
			return;
	/*ECHECK*/

	if ( *t->depth < 0 && *t->depth >= t->maxdepth ) {
	  __glerror( __LINE__, __FILE__, GL_STACK_OVERFLOW, "PushMatrix!" );
	  abort( );
	}
	
	/* Perform the copy */
	t->m[1] = t->m[0];

	/* Move the stack pointer */
	t->m++;
	(*t->depth)++;

	tb->matrix[t->matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_LoadMatrixf(const GLfloat *m1) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m;

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"LoadMatrixf called in begin/end"))
			return;

 
		
	/*ECHECK*/

	m = t->m;
	m->m00 = (GLdefault) m1[0];	
	m->m01 = (GLdefault) m1[1];		
	m->m02 = (GLdefault) m1[2];	
	m->m03 = (GLdefault) m1[3];	
	m->m10 = (GLdefault) m1[4];	
	m->m11 = (GLdefault) m1[5];		
	m->m12 = (GLdefault) m1[6];	
	m->m13 = (GLdefault) m1[7];	
	m->m20 = (GLdefault) m1[8];		
	m->m21 = (GLdefault) m1[9];	
	m->m22 = (GLdefault) m1[10];	
	m->m23 = (GLdefault) m1[11];	
	m->m30 = (GLdefault) m1[12];	
	m->m31 = (GLdefault) m1[13];	
	m->m32 = (GLdefault) m1[14];	
	m->m33 = (GLdefault) m1[15];	

	t->transformvalid = 0;
	tb->matrix[g->trans.matrixid] = g->nbitID;

	tb->dirty = g->nbitID;

}

void GLSTATE_DECL
__glstate_LoadMatrixd(const GLdouble *m1) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m;

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"LoadMatrixd called in begin/end"))
			return;

 
		
	/*ECHECK*/

	m = t->m;
	m->m00 = (GLdefault) m1[0];	
	m->m01 = (GLdefault) m1[1];		
	m->m02 = (GLdefault) m1[2];	
	m->m03 = (GLdefault) m1[3];	
	m->m10 = (GLdefault) m1[4];	
	m->m11 = (GLdefault) m1[5];		
	m->m12 = (GLdefault) m1[6];	
	m->m13 = (GLdefault) m1[7];	
	m->m20 = (GLdefault) m1[8];		
	m->m21 = (GLdefault) m1[9];	
	m->m22 = (GLdefault) m1[10];	
	m->m23 = (GLdefault) m1[11];	
	m->m30 = (GLdefault) m1[12];	
	m->m31 = (GLdefault) m1[13];	
	m->m32 = (GLdefault) m1[14];	
	m->m33 = (GLdefault) m1[15];	

	t->transformvalid = 0;
	
	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;

}

/* This code is based on the pomegranite stuff.
** The theory is that by preloading everything,
** the compiler could do optimizations that 
** were not doable in the array version
** I'm not too sure with a PII with 4 registers
** that this really helps.
*/	
void GLSTATE_DECL
__glstate_MultMatrixf(const GLfloat *m1) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m = t->m;
	const GLdefault lm00 = m->m00;  
	const GLdefault lm01 = m->m01;  
	const GLdefault lm02 = m->m02;	
	const GLdefault lm03 = m->m03;	
	const GLdefault lm10 = m->m10;	
	const GLdefault lm11 = m->m11;	
	const GLdefault lm12 = m->m12;	
	const GLdefault lm13 = m->m13;	
	const GLdefault lm20 = m->m20;	
	const GLdefault lm21 = m->m21;	
	const GLdefault lm22 = m->m22;	
	const GLdefault lm23 = m->m23;	
	const GLdefault lm30 = m->m30;	
	const GLdefault lm31 = m->m31;	
	const GLdefault lm32 = m->m32;		
	const GLdefault lm33 = m->m33;		
	const GLdefault rm00 = (GLdefault) m1[0];	
	const GLdefault rm01 = (GLdefault) m1[1];	
	const GLdefault rm02 = (GLdefault) m1[2];	
	const GLdefault rm03 = (GLdefault) m1[3];	
	const GLdefault rm10 = (GLdefault) m1[4];	
	const GLdefault rm11 = (GLdefault) m1[5];		
	const GLdefault rm12 = (GLdefault) m1[6];	
	const GLdefault rm13 = (GLdefault) m1[7];	
	const GLdefault rm20 = (GLdefault) m1[8];	
	const GLdefault rm21 = (GLdefault) m1[9];	
	const GLdefault rm22 = (GLdefault) m1[10];	
	const GLdefault rm23 = (GLdefault) m1[11];	
	const GLdefault rm30 = (GLdefault) m1[12];	
	const GLdefault rm31 = (GLdefault) m1[13];	
	const GLdefault rm32 = (GLdefault) m1[14];	
	const GLdefault rm33 = (GLdefault) m1[15];	

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"MultMatrixf called in begin/end"))
			return;

 
		
	/*ECHECK*/

	m->m00 = lm00*rm00 + lm10*rm01 + lm20*rm02 + lm30*rm03;	
	m->m01 = lm01*rm00 + lm11*rm01 + lm21*rm02 + lm31*rm03;	
	m->m02 = lm02*rm00 + lm12*rm01 + lm22*rm02 + lm32*rm03;	
	m->m03 = lm03*rm00 + lm13*rm01 + lm23*rm02 + lm33*rm03;	
	m->m10 = lm00*rm10 + lm10*rm11 + lm20*rm12 + lm30*rm13;	
	m->m11 = lm01*rm10 + lm11*rm11 + lm21*rm12 + lm31*rm13;	
	m->m12 = lm02*rm10 + lm12*rm11 + lm22*rm12 + lm32*rm13;	
	m->m13 = lm03*rm10 + lm13*rm11 + lm23*rm12 + lm33*rm13;	
	m->m20 = lm00*rm20 + lm10*rm21 + lm20*rm22 + lm30*rm23;	
	m->m21 = lm01*rm20 + lm11*rm21 + lm21*rm22 + lm31*rm23;	
	m->m22 = lm02*rm20 + lm12*rm21 + lm22*rm22 + lm32*rm23;	
	m->m23 = lm03*rm20 + lm13*rm21 + lm23*rm22 + lm33*rm23;	
	m->m30 = lm00*rm30 + lm10*rm31 + lm20*rm32 + lm30*rm33;	
	m->m31 = lm01*rm30 + lm11*rm31 + lm21*rm32 + lm31*rm33;	
	m->m32 = lm02*rm30 + lm12*rm31 + lm22*rm32 + lm32*rm33;	
	m->m33 = lm03*rm30 + lm13*rm31 + lm23*rm32 + lm33*rm33;

	assert (*(unsigned int *)(&(m->m00)) != 0xffc00000);

	t->transformvalid = 0;

	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_MultMatrixd(const GLdouble *m1) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m = t->m;
	const GLdefault lm00 = m->m00;  
	const GLdefault lm01 = m->m01;  
	const GLdefault lm02 = m->m02;	
	const GLdefault lm03 = m->m03;	
	const GLdefault lm10 = m->m10;	
	const GLdefault lm11 = m->m11;	
	const GLdefault lm12 = m->m12;	
	const GLdefault lm13 = m->m13;	
	const GLdefault lm20 = m->m20;	
	const GLdefault lm21 = m->m21;	
	const GLdefault lm22 = m->m22;	
	const GLdefault lm23 = m->m23;	
	const GLdefault lm30 = m->m30;	
	const GLdefault lm31 = m->m31;	
	const GLdefault lm32 = m->m32;		
	const GLdefault lm33 = m->m33;		
	const GLdefault rm00 = (GLdefault) m1[0];	
	const GLdefault rm01 = (GLdefault) m1[1];	
	const GLdefault rm02 = (GLdefault) m1[2];	
	const GLdefault rm03 = (GLdefault) m1[3];	
	const GLdefault rm10 = (GLdefault) m1[4];	
	const GLdefault rm11 = (GLdefault) m1[5];		
	const GLdefault rm12 = (GLdefault) m1[6];	
	const GLdefault rm13 = (GLdefault) m1[7];	
	const GLdefault rm20 = (GLdefault) m1[8];	
	const GLdefault rm21 = (GLdefault) m1[9];	
	const GLdefault rm22 = (GLdefault) m1[10];	
	const GLdefault rm23 = (GLdefault) m1[11];	
	const GLdefault rm30 = (GLdefault) m1[12];	
	const GLdefault rm31 = (GLdefault) m1[13];	
	const GLdefault rm32 = (GLdefault) m1[14];	
	const GLdefault rm33 = (GLdefault) m1[15];	

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"MultMatrixd called in begin/end"))
			return;

 
		
	/*ECHECK*/

	m->m00 = lm00*rm00 + lm10*rm01 + lm20*rm02 + lm30*rm03;	
	m->m01 = lm01*rm00 + lm11*rm01 + lm21*rm02 + lm31*rm03;	
	m->m02 = lm02*rm00 + lm12*rm01 + lm22*rm02 + lm32*rm03;	
	m->m03 = lm03*rm00 + lm13*rm01 + lm23*rm02 + lm33*rm03;	
	m->m10 = lm00*rm10 + lm10*rm11 + lm20*rm12 + lm30*rm13;	
	m->m11 = lm01*rm10 + lm11*rm11 + lm21*rm12 + lm31*rm13;	
	m->m12 = lm02*rm10 + lm12*rm11 + lm22*rm12 + lm32*rm13;	
	m->m13 = lm03*rm10 + lm13*rm11 + lm23*rm12 + lm33*rm13;	
	m->m20 = lm00*rm20 + lm10*rm21 + lm20*rm22 + lm30*rm23;	
	m->m21 = lm01*rm20 + lm11*rm21 + lm21*rm22 + lm31*rm23;	
	m->m22 = lm02*rm20 + lm12*rm21 + lm22*rm22 + lm32*rm23;	
	m->m23 = lm03*rm20 + lm13*rm21 + lm23*rm22 + lm33*rm23;	
	m->m30 = lm00*rm30 + lm10*rm31 + lm20*rm32 + lm30*rm33;	
	m->m31 = lm01*rm30 + lm11*rm31 + lm21*rm32 + lm31*rm33;	
	m->m32 = lm02*rm30 + lm12*rm31 + lm22*rm32 + lm32*rm33;	
	m->m33 = lm03*rm30 + lm13*rm31 + lm23*rm32 + lm33*rm33;

	assert (*(unsigned int *)(&(m->m00)) != 0xffc00000);
	
	t->transformvalid = 0;

	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}



void GLSTATE_DECL
__glstate_Translatef(const GLfloat x_arg, const GLfloat y_arg, const GLfloat z_arg) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m = t->m;

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Translatef called in begin/end"))
			return;

 
		
	/*ECHECK*/

	TRANSLATECODE

	t->transformvalid = 0;

	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_Translated(const GLdouble x_arg, const GLdouble y_arg, const GLdouble z_arg) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m = t->m;

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Translated called in begin/end"))
			return;

 
		
	/*ECHECK*/

	TRANSLATECODE

	t->transformvalid = 0;

	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}	


/* TODO: use lookup tables for cosine and sine functions */
/* TODO: we need a fast sqrt function SIMD?*/
/* TODO: don't call multmatrix. Do your own multiply. */


void GLSTATE_DECL
__glstate_Rotatef(const GLfloat ang, GLfloat x, GLfloat y, GLfloat z) {
	const GLfloat c = (GLfloat) cos(ang*M_PI/180.0f);			
	const GLfloat one_minus_c = 1.0f - c;	
	const GLfloat s = (GLfloat) sin(ang*M_PI/180.0f);			
	const GLfloat v_len = (GLfloat) sqrt (x*x + y*y + z*z);	
	GLfloat rot[16];				
	GLfloat x_one_minus_c;	
	GLfloat y_one_minus_c;	
	GLfloat z_one_minus_c;	

	if (v_len == 0.0f)
		return;

	/* Normalize the vector */	
	if (v_len != 1.0f) {		
		x /= v_len;				
		y /= v_len;					
		z /= v_len;				
	}							
	/* compute some common values */	
	x_one_minus_c = x * one_minus_c;	
	y_one_minus_c = y * one_minus_c;	
	z_one_minus_c = z * one_minus_c;	
	/* Generate the terms of the rotation matrix	
	** from pg 325 OGL 1.1 Blue Book.				
	*/												
	rot[0] = x*x_one_minus_c + c;					
	rot[1] = x*y_one_minus_c + z*s;				
	rot[2] = x*z_one_minus_c - y*s;				
	rot[3] = 0.0f;						
	rot[4] = y*x_one_minus_c - z*s;				
	rot[5] = y*y_one_minus_c + c;					
	rot[6] = y*z_one_minus_c + x*s;				
	rot[7] = 0.0f;						
	rot[8] = z*x_one_minus_c + y*s;				
	rot[9] = z*y_one_minus_c - x*s;				
	rot[10] = z*z_one_minus_c + c;						
	rot[11] = 0.0f;						
	rot[12] = 0.0f;						
	rot[13] = 0.0f;						
	rot[14] = 0.0f;						
	rot[15] = 1.0f;						
	__glstate_MultMatrixf((const GLfloat *) rot);
}

void GLSTATE_DECL
__glstate_Rotated(const GLdouble ang, GLdouble x, GLdouble y, GLdouble z) {
	const GLdouble c = (GLdouble) cos(ang*M_PI/180.0);			
	const GLdouble one_minus_c = 1.0 - c;	
	const GLdouble s = (GLdouble) sin(ang*M_PI/180.0f);			
	const GLdouble v_len = (GLdouble) sqrt (x*x + y*y + z*z);	
	GLdouble rot[16];				
	GLdouble x_one_minus_c;	
	GLdouble y_one_minus_c;	
	GLdouble z_one_minus_c;	

	/* Normalize the vector */	
	if (v_len != 1.0f) {		
		x /= v_len;				
		y /= v_len;					
		z /= v_len;				
	}							
	/* compute some common values */	
	x_one_minus_c = x * one_minus_c;	
	y_one_minus_c = y * one_minus_c;	
	z_one_minus_c = z * one_minus_c;	
	/* Generate the terms of the rotation matrix	
	** from pg 325 OGL 1.1 Blue Book.				
	*/												
	rot[0] = x*x_one_minus_c + c;					
	rot[1] = x*y_one_minus_c + z*s;				
	rot[2] = x*z_one_minus_c - y*s;				
	rot[3] = 0.0;						
	rot[4] = y*x_one_minus_c - z*s;				
	rot[5] = y*y_one_minus_c + c;					
	rot[6] = y*z_one_minus_c + x*s;				
	rot[7] = 0.0;						
	rot[8] = z*x_one_minus_c + y*s;				
	rot[9] = z*y_one_minus_c - x*s;				
	rot[10] = z*z_one_minus_c + c;						
	rot[11] = 0.0;						
	rot[12] = 0.0;						
	rot[13] = 0.0;						
	rot[14] = 0.0;						
	rot[15] = 1.0;						
	__glstate_MultMatrixd((const GLdouble *) rot);
}	

void GLSTATE_DECL
__glstate_Scalef (const GLfloat x_arg, const GLfloat y_arg, const GLfloat z_arg) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m = t->m;
	const GLdefault x = (GLdefault) x_arg;	
	const GLdefault y = (GLdefault) y_arg;	
	const GLdefault z = (GLdefault) z_arg;	

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Scalef called in begin/end"))
			return;

 
		
	/*ECHECK*/

	m->m00 *= x;	
	m->m01 *= x;	
	m->m02 *= x;		
	m->m03 *= x;	
	m->m10 *= y;	
	m->m11 *= y;	
	m->m12 *= y;	
	m->m13 *= y;	
	m->m20 *= z;	
	m->m21 *= z;	
	m->m22 *= z;	
	m->m23 *= z;	

	t->transformvalid = 0;
	
	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_Scaled (const GLdouble x_arg, const GLdouble y_arg, const GLdouble z_arg) {
	GLcontext *g = GetCurrentContext();
	GLtransstate *t = &(g->trans);
	GLstatebits *sb = GetStateBits();
	GLtransbits *tb = &(sb->trans);
	GLmatrix *m = t->m;
	const GLdefault x = (GLdefault) x_arg;	
	const GLdefault y = (GLdefault) y_arg;	
	const GLdefault z = (GLdefault) z_arg;	

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"Scaled called in begin/end"))
			return;

 
		
	/*ECHECK*/

	m->m00 *= x;	
	m->m01 *= x;	
	m->m02 *= x;		
	m->m03 *= x;	
	m->m10 *= y;	
	m->m11 *= y;	
	m->m12 *= y;	
	m->m13 *= y;	
	m->m20 *= z;	
	m->m21 *= z;	
	m->m22 *= z;	
	m->m23 *= z;

	t->transformvalid = 0;
	
	tb->matrix[g->trans.matrixid] = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_Frustum (	const GLdouble left, const GLdouble right,
					const GLdouble bottom, const GLdouble top, 
					const GLdouble zNear, const GLdouble zFar) {
	GLdouble m[16];

	/* Build the frustum matrix
	** from pg 163 OGL 1.1 Blue Book
	*/
	m[0] = (2.0*zNear)/(right-left);
	m[1] = 0.0;
	m[2] = 0.0;
	m[3] = 0.0;
	
	m[4] = 0.0;
	m[5] = (2.0*zNear)/(top-bottom);
	m[6] = 0.0;
	m[7] = 0.0;
	
	m[8] = (right+left)/(right-left);
	m[9] = (top+bottom)/(top-bottom);
	m[10] = (-zNear-zFar)/(zFar-zNear);
	m[11] = -1.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = (2.0*zFar*zNear)/(zNear-zFar);
	m[15] = 0.0;

	__glstate_MultMatrixd((const GLdouble *) m);
}

void GLSTATE_DECL
__glstate_Ortho ( GLdouble left, GLdouble right,
				  GLdouble bottom, GLdouble top,
				  GLdouble znear, GLdouble zfar) {

	GLdouble m[16];	

	m[0] = 2.0 / (right - left);
	m[1] = 0.0;
	m[2] = 0.0;
	m[3] = 0.0;

	m[4] = 0.0;
	m[5] = 2.0 / (top - bottom);
	m[6] = 0.0;
	m[7] = 0.0;

	m[8] = 0.0;
	m[9] = 0.0;
	m[10] = -2.0 / (zfar - znear);
	m[11] = 0.0;

	m[12] = -(right + left) / (right - left);
	m[13] = -(top + bottom) / (top - bottom);
	m[14] = -(zfar + znear) / (zfar - znear);
	m[15] = 1.0;

	__glstate_MultMatrixd((const GLdouble *) m);
}



