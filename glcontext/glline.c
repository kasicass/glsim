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
__glline_initbits (GLlinebits *l, GLconfig *cfg) {
	/* do nothing */
	UNUSED(l);
	UNUSED(cfg);
}

void
__glline_init (GLlinestate *l, GLconfig *c) {
	l->linesmooth = GL_FALSE;
	l->linestipple = GL_FALSE;
	l->pointsmooth = GL_FALSE;
	l->pointsize = 1.0f;
	l->width = 1.0f;
	l->pattern = 0xFFFF;
	l->repeat = 1;
	l->aliasedpointsizerange_min = c->aliasedpointsizerange_min;
	l->aliasedpointsizerange_max = c->aliasedpointsizerange_max;
	l->aliasedpointsizegranularity = c->aliasedpointsizegranularity;
	l->smoothpointsizerange_min = c->smoothpointsizerange_min;
	l->smoothpointsizerange_max = c->smoothpointsizerange_max;
	l->smoothpointgranularity = c->smoothpointgranularity;
	l->aliasedlinewidth_min = c->aliasedlinewidth_min;
	l->aliasedlinewidth_max = c->aliasedlinewidth_max;
	l->aliasedlinegranularity = c->aliasedlinegranularity;
	l->smoothlinewidth_min = c->smoothlinewidth_min;
	l->smoothlinewidth_max = c->smoothlinewidth_max;
	l->smoothlinegranularity = c->smoothlinegranularity;
}

void
__glline_destroy (GLlinestate *l) {
	/* do nothing */
	UNUSED(l);
}

void GLSTATE_DECL
__glstate_PointSize(GLfloat size) {
	GLcontext *g = GetCurrentContext();
	GLlinestate *l = &(g->line);
	GLstatebits *sb = GetStateBits();
	GLlinebits *lb = &(sb->line);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glPointSize called in begin/end"))
			return;

 
		

	if (size <= 0.0f) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glPointSize called with size <= 0.0: %f", size))
			return;
	/*ECHECK*/
		
	l->pointsize = size;
	lb->size = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_LineWidth(GLfloat width) {
	GLcontext *g = GetCurrentContext();
	GLlinestate *l = &(g->line);
	GLstatebits *sb = GetStateBits();
	GLlinebits *lb = &(sb->line);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glLineWidth called in begin/end"))
			return;

 
		

	if (width <= 0.0f) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glLineWidth called with size <= 0.0: %f", width))
			return;
	/*ECHECK*/

	l->width = width;
	lb->width = g->nbitID;
	lb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_LineStipple(GLuint factor, GLushort pattern) {
	GLcontext *g = GetCurrentContext();
	GLlinestate *l = &(g->line);
	GLstatebits *sb = GetStateBits();
	GLlinebits *lb = &(sb->line);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glLineStipple called in begin/end"))
			return;

 
		

	if (factor < 1) factor = 1;
	if (factor > 256) factor = 256;
	/*ECHECK*/

	l->pattern = pattern;
	l->repeat = factor;
	lb->stipple = g->nbitID;
	lb->dirty = g->nbitID;
}

