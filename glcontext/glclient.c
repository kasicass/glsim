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

#define GLCLIENT_NUMPOINTERS 6
#define GLCLIENT_INDEX_ALLOC 1024
#define GLCLIENT_DATA_ALLOC 1024
#define GLCLIENT_CACHE_ALLOC 1024
#define GLCLIENT_LIST_ALLOC 1024
#define GLCLIENT_BIT_ALLOC 1024

void (*__glhw_UpdateClientPointer) (int array, int index_size, int *index, int data_size, unsigned char * data);
void __glhw_UpdateClientPointer_nop (int array, int index_size, int * index, int data_size, unsigned char * data) { 
	UNUSED(array);
	UNUSED(index_size);
	UNUSED(index);
	UNUSED(data_size);
	UNUSED(data);
}

void 
__glclient_initbits (GLclientbits *c, GLconfig * cfg) {
	UNUSED(cfg);
	c->v = (GLbitvalue *) malloc (GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	c->n = (GLbitvalue *) malloc (GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	c->c = (GLbitvalue *) malloc (GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	c->i = (GLbitvalue *) malloc (GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	c->t = (GLbitvalue *) malloc (GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	c->e = (GLbitvalue *) malloc (GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	memset(c->v, 0, GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	memset(c->n, 0, GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	memset(c->c, 0, GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	memset(c->i, 0, GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	memset(c->t, 0, GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	memset(c->e, 0, GLCLIENT_BIT_ALLOC*sizeof(GLbitvalue));
	c->valloc = GLCLIENT_BIT_ALLOC;
	c->nalloc = GLCLIENT_BIT_ALLOC;
	c->calloc = GLCLIENT_BIT_ALLOC;
	c->ialloc = GLCLIENT_BIT_ALLOC;
	c->talloc = GLCLIENT_BIT_ALLOC;
	c->ealloc = GLCLIENT_BIT_ALLOC;
}

void
__glclient_init(GLclientstate *c, GLconfig *cfg) {
	GLclientpointer *lookup[6];
	GLclientpointer *cp;
	int i;

	lookup[0] = &(c->v);
	lookup[1] = &(c->c);
	lookup[2] = &(c->e);
	lookup[3] = &(c->i);
	lookup[4] = &(c->n);
	lookup[5] = &(c->t);
	
	c->maxelementsindices = cfg->maxelementsindices;
	c->maxelementsvertices = cfg->maxelementsvertices;

	c->list_alloc = GLCLIENT_LIST_ALLOC;
	c->list_size = 0;
	c->list = (int *) malloc (c->list_alloc * sizeof (int));

	for (i=0; i<GLCLIENT_NUMPOINTERS; i++) {
		cp = lookup[i];
		cp->p = NULL;
		cp->size = 0;
		cp->type = GL_NONE;
		cp->stride = 0;
		cp->enabled = 0;

	}
}

void 
__glclient_destroy(GLclientstate *c) {
	free (c->list);
}

void
__glclient_finish(GLclientstate *c, GLclientbits *cb, GLbitvalue bitID) {
	UNUSED(cb);
	UNUSED(bitID);
	c->list_size = 0;
}

void 
__glclient_setclientstate(GLclientstate *c, GLclientbits *cb, GLbitvalue nbitID, 
						  GLenum array, GLboolean state) {
	switch (array) {
	case GL_VERTEX_ARRAY:
		c->v.enabled = state;
	break;
	case GL_COLOR_ARRAY:
		c->c.enabled = state;
	break;
	case GL_NORMAL_ARRAY:
		c->n.enabled = state;
	break;
	case GL_INDEX_ARRAY:
		c->i.enabled = state;
	break;
	case GL_TEXTURE_COORD_ARRAY:
		c->t.enabled = state;
	break;
	case GL_EDGE_FLAG_ARRAY:
		c->e.enabled = state;
	break;	
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid Enum passed to Enable/Disable Client State"))
			return;
	}
	cb->dirty = nbitID;
	cb->enableclientstate = nbitID;
}



void GLSTATE_DECL
__glstate_EnableClientState (GLenum array) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	__glclient_setclientstate(c, cb, g->nbitID, array, GL_TRUE);
}

void GLSTATE_DECL
__glstate_DisableClientState (GLenum array) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	__glclient_setclientstate(c, cb, g->nbitID, array, GL_FALSE);
}

void 
__glclient_setcppointer (GLclientpointer *cp, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
	cp->p = (unsigned char *) pointer;
	cp->size = size;
	cp->type = type;
	// Calculate the bytes per index for address calculation
	cp->bytesperindex = size;
	switch (type) {
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
		break;
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
		cp->bytesperindex *= sizeof(GLshort);
		break;
	case GL_INT:
	case GL_UNSIGNED_INT:
		cp->bytesperindex *= sizeof(GLint);
		break;
	case GL_FLOAT:
		cp->bytesperindex *= sizeof(GLfloat);
		break;
	case GL_DOUBLE:
		cp->bytesperindex *= sizeof(GLdouble);
		break;
	}

	/* 
	**  Note: If stide==0 then we set the 
	**  stride equal address offset
	**  therefore stride can never equal
	**  zero.
	*/
	cp->stride = stride;
	if (!stride) cp->stride = cp->bytesperindex;
}

void GLSTATE_DECL
__glstate_VertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *p) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	if (size != 2 &&
		size != 3 &&
		size != 4)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glVertexPointer: invalid size: %d", size))
			return;
	if (type != GL_SHORT &&
		type != GL_INT &&
		type != GL_FLOAT &&
		type != GL_DOUBLE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glVertexPointer: invalid type: %d", type))
			return;
	if (stride < 0) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glVertexPointer: stride was negative: %d", stride))
			return;
	
	__glclient_setcppointer(&(c->v), size, type, stride, p);
	cb->dirty = g->nbitID;
	cb->clientpointer = g->nbitID;
}

void GLSTATE_DECL
__glstate_ColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *p) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	if (size != 3 &&
		size != 4)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glColorPointer: invalid size: %d", size))
			return;
	if (type != GL_BYTE &&
		type != GL_UNSIGNED_BYTE &&
		type != GL_SHORT &&
		type != GL_UNSIGNED_SHORT &&
		type != GL_INT &&
		type != GL_UNSIGNED_INT &&
		type != GL_FLOAT &&
		type != GL_DOUBLE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glColorPointer: invalid type: %d", type))
			return;
	if (stride < 0) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glColorPointer: stride was negative: %d", stride))
			return;

	__glclient_setcppointer(&(c->c), size, type, stride, p);
	cb->dirty = g->nbitID;
	cb->clientpointer = g->nbitID;
}

void GLSTATE_DECL
__glstate_IndexPointer(GLenum type, GLsizei stride, const GLvoid *p) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	if (type != GL_SHORT &&
		type != GL_INT &&
		type != GL_FLOAT &&
		type != GL_DOUBLE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glIndexPointer: invalid type: %d", type))
			return;
	if (stride < 0) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glIndexPointer: stride was negative: %d", stride))
			return;

	__glclient_setcppointer(&(c->i), 1, type, stride, p);
	cb->dirty = g->nbitID;
	cb->clientpointer = g->nbitID;
}

void GLSTATE_DECL
__glstate_NormalPointer(GLenum type, GLsizei stride, const GLvoid *p) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	if (type != GL_BYTE &&
		type != GL_SHORT &&
		type != GL_INT &&
		type != GL_FLOAT &&
		type != GL_DOUBLE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glNormalPointer: invalid type: %d", type))
			return;
	if (stride < 0) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glNormalPointer: stride was negative: %d", stride))
			return;

	__glclient_setcppointer(&(c->n), 3, type, stride, p);
	cb->dirty = g->nbitID;
	cb->clientpointer = g->nbitID;
}

void GLSTATE_DECL
__glstate_TexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *p) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	if (size != 1 &&
		size != 2 &&
		size != 3 &&
		size != 4)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexCoordPointer: invalid size: %d", size))
			return;
	if (type != GL_SHORT &&
		type != GL_INT &&
		type != GL_FLOAT &&
		type != GL_DOUBLE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glTexCoordPointer: invalid type: %d", type))
			return;
	if (stride < 0) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexCoordPointer: stride was negative: %d", stride))
			return;

	__glclient_setcppointer(&(c->t), size, type, stride, p);
	cb->dirty = g->nbitID;
	cb->clientpointer = g->nbitID;
}

void GLSTATE_DECL
__glstate_EdgeFlagPointer(GLsizei stride, const GLvoid *p) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);

 
		

	if (stride < 0) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexCoordPointer: stride was negative: %d", stride))
			return;

	__glclient_setcppointer(&(c->e), 1, GL_UNSIGNED_BYTE, stride, p);
	cb->dirty = g->nbitID;
	cb->clientpointer = g->nbitID;
}


/* 
** Currently I treat Interleaved Arrays as if the 
** user uses them as separate arrays.
** Certainly not the most efficient method but it 
** lets me use the same glDrawArrays method.
*/
void GLSTATE_DECL 
__glstate_InterleavedArrays(GLenum format, GLsizei stride, const GLvoid *p) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	GLstatebits *sb = GetStateBits();
	GLclientbits *cb = &(sb->client);
	GLclientpointer *cp;
	unsigned char *base = (unsigned char *) p;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glInterleavedArrays called in begin/end"))
			return;

 
		

	if (stride < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glInterleavedArrays: stride < 0: %d", stride))
			return;

	switch (format) {
	case GL_T4F_C4F_N3F_V4F:
	case GL_T2F_C4F_N3F_V3F:
	case GL_C4F_N3F_V3F:
	case GL_T4F_V4F:
	case GL_T2F_C3F_V3F:
	case GL_T2F_N3F_V3F:
	case GL_C3F_V3F:
	case GL_N3F_V3F:
	case GL_T2F_C4UB_V3F:
	case GL_T2F_V3F:
	case GL_C4UB_V3F:
	case GL_V3F:
	case GL_C4UB_V2F:
	case GL_V2F:
		break;
	default:
		if(__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glInterleavedArrays: Unrecognized format: %d", format))
			return;
	}

	cb->dirty = g->nbitID;
	cb->clientpointer = g->nbitID;

/* p, size, type, stride, enabled, bytesperindex */
/*
**  VertexPointer 
*/
	
	cp = &(c->v);
	cp->type = GL_FLOAT;
	cp->enabled = GL_TRUE;

	switch (format) {
	case GL_T4F_C4F_N3F_V4F:
		cp->p = base+4*sizeof(GLfloat)+4*sizeof(GLfloat)+3*sizeof(GLfloat);
		cp->size = 4;
		break;
	case GL_T2F_C4F_N3F_V3F:
		cp->p = base+2*sizeof(GLfloat)+4*sizeof(GLfloat)+3*sizeof(GLfloat);
		cp->size = 3;
		break;
	case GL_C4F_N3F_V3F:
		cp->p = base+4*sizeof(GLfloat)+3*sizeof(GLfloat);
		cp->size = 3;
		break;
	case GL_T4F_V4F:
		cp->p = base+4*sizeof(GLfloat);
		cp->size = 4;
		break;
	case GL_T2F_C3F_V3F:
		cp->p = base+2*sizeof(GLfloat)+3*sizeof(GLfloat);
		cp->size = 3;
		break;
	case GL_T2F_N3F_V3F:
		cp->p = base+2*sizeof(GLfloat)+3*sizeof(GLfloat);
		cp->size = 3;
		break;
	case GL_C3F_V3F:
		cp->p = base+3*sizeof(GLfloat);
		cp->size = 3;
		break;
	case GL_N3F_V3F:
		cp->p = base+3*sizeof(GLfloat);
		cp->size = 3;
		break;
	case GL_T2F_C4UB_V3F:
		cp->p = base+2*sizeof(GLfloat)+4*sizeof(GLubyte);
		cp->size = 3;
		break;
	case GL_T2F_V3F:
		cp->p = base+2*sizeof(GLfloat);
		cp->size = 2;
		break;
	case GL_C4UB_V3F:
		cp->p = base+4*sizeof(GLubyte);
		cp->size = 3;
		break;
	case GL_V3F:
		cp->p = base;
		cp->size = 3;
		break;
	case GL_C4UB_V2F:
		cp->p = base+4*sizeof(GLubyte);
		cp->size = 2;
		break;
	case GL_V2F:
		cp->p = base;
		cp->size = 2;
		break;
	default:
		if(__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glInterleavedArrays: Unrecognized format: %d", format))
			return;
	}

	cp->bytesperindex = cp->size * sizeof (GLfloat);

	if (stride)
		cp->stride = stride + (cp->p - base);
	else
		cp->stride = cp->bytesperindex + (cp->p - base);

/*
**  NormalPointer
*/

	cp = &(c->n);
	cp->enabled = GL_TRUE;
	switch (format) {
	case GL_T4F_C4F_N3F_V4F:
		cp->p = base+4*sizeof(GLfloat)+4*sizeof(GLfloat);
		cp->stride = 4*sizeof(GLfloat)+4*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 3*sizeof(GLfloat)+4*sizeof(GLfloat);
		break;
	case GL_T2F_C4F_N3F_V3F:
		cp->p = base+2*sizeof(GLfloat)+4*sizeof(GLfloat);
		cp->stride = 2*sizeof(GLfloat)+4*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_C4F_N3F_V3F:
		cp->p = base+4*sizeof(GLfloat);
		cp->stride = 4*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_T2F_N3F_V3F:
		cp->p = base+2*sizeof(GLfloat);
		cp->stride = 2*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_N3F_V3F:
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride += 3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_T4F_V4F:
	case GL_T2F_C3F_V3F:
	case GL_C3F_V3F:
	case GL_T2F_C4UB_V3F:
	case GL_T2F_V3F:
	case GL_C4UB_V3F:
	case GL_V3F:
	case GL_C4UB_V2F:
	case GL_V2F:
		cp->enabled = GL_FALSE;
	default:
		if(__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glInterleavedArrays: Unrecognized format: %d", format))
			return;
	}

	if (cp->enabled) {
		cp->type = GL_FLOAT;
		cp->size = 3;
		cp->bytesperindex = cp->size * sizeof (GLfloat);
	}
	
/*
**  ColorPointer
*/

	cp = &(c->c);
	cp->enabled = GL_TRUE;
	switch (format) {
	case GL_T4F_C4F_N3F_V4F:
		cp->size = 4;
		cp->type = GL_FLOAT;
		cp->bytesperindex = cp->size * sizeof(GLfloat);
		cp->p = base+4*sizeof(GLfloat);
		cp->stride = 4*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 4*sizeof(GLfloat)+3*sizeof(GLfloat)+4*sizeof(GLfloat);
		break;
	case GL_T2F_C4F_N3F_V3F:
		cp->size = 4;
		cp->type = GL_FLOAT;
		cp->bytesperindex = cp->size * sizeof(GLfloat);
		cp->p = base+2*sizeof(GLfloat);
		cp->stride = 2*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 4*sizeof(GLfloat)+3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_C4F_N3F_V3F:
		cp->size = 4;
		cp->type = GL_FLOAT;
		cp->bytesperindex = cp->size * sizeof(GLfloat);
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride += 4*sizeof(GLfloat)+3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_T2F_C3F_V3F:
		cp->size = 3;
		cp->type = GL_FLOAT;
		cp->bytesperindex = cp->size * sizeof(GLfloat);
		cp->p = base+2*sizeof(GLfloat);
		cp->stride = 2*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_C3F_V3F:
		cp->size = 3;
		cp->type = GL_FLOAT;
		cp->bytesperindex = cp->size * sizeof(GLfloat);
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride += 3*sizeof(GLfloat) + 3*sizeof(GLfloat);
		break;
	case GL_T2F_C4UB_V3F:
		cp->size = 4;
		cp->type = GL_UNSIGNED_BYTE;
		cp->bytesperindex = cp->size * sizeof(GLubyte);
		cp->p = base+2*sizeof(GLfloat);
		cp->stride = 2*sizeof(GLfloat)+stride;
		if (!stride) cp->stride += 4*sizeof(GLubyte)+2*sizeof(GLfloat);
		break;
	case GL_C4UB_V3F:
		cp->size = 4;
		cp->type = GL_UNSIGNED_BYTE;
		cp->bytesperindex = cp->size * sizeof(GLubyte);
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride += 4*sizeof(GLubyte)+3*sizeof(GLfloat);
		break;
	case GL_C4UB_V2F:
		cp->size = 4;
		cp->type = GL_UNSIGNED_BYTE;
		cp->bytesperindex = cp->size * sizeof(GLubyte);
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride += 4*sizeof(GLubyte)+2*sizeof(GLfloat);
		break;
	case GL_T2F_N3F_V3F:
	case GL_N3F_V3F:
	case GL_T4F_V4F:
	case GL_T2F_V3F:
	case GL_V3F:
	case GL_V2F:
		cp->enabled = GL_FALSE;
	default:
		if(__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glInterleavedArrays: Unrecognized format: %d", format))
			return;
	}

/*
**  TexturePointer
*/

	cp = &(c->t);
	cp->enabled = GL_TRUE;
	switch (format) {
	case GL_T4F_C4F_N3F_V4F:
		cp->size = 4;
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride = 4*sizeof(GLfloat)+4*sizeof(GLfloat)+3*sizeof(GLfloat)+4*sizeof(GLfloat);
		break;
	case GL_T2F_C4F_N3F_V3F:
		cp->size = 2;
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride = 2*sizeof(GLfloat)+4*sizeof(GLfloat)+3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_T2F_C3F_V3F:
	case GL_T2F_N3F_V3F:
		cp->size = 2;
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride = 2*sizeof(GLfloat)+3*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_T2F_C4UB_V3F:
		cp->size = 2;
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride = 2*sizeof(GLfloat)+4*sizeof(GLubyte)+3*sizeof(GLfloat);
		break;
	case GL_T4F_V4F:
		cp->size = 4;
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride = 4*sizeof(GLfloat)+4*sizeof(GLfloat);
		break;
	case GL_T2F_V3F:
		cp->size = 2;
		cp->p = base;
		cp->stride = stride;
		if (!stride) cp->stride = 2*sizeof(GLfloat)+3*sizeof(GLfloat);
		break;
	case GL_C4UB_V3F:
	case GL_C4UB_V2F:
	case GL_C3F_V3F:
	case GL_C4F_N3F_V3F:
	case GL_N3F_V3F:
	case GL_V3F:
	case GL_V2F:
		cp->enabled = GL_FALSE;
	default:
		if(__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glInterleavedArrays: Unrecognized format: %d", format))
			return;
	}

	if (cp->enabled) {
		cp->type = GL_FLOAT;
		cp->bytesperindex = cp->size * sizeof (GLfloat);
	}	
}


void GLSTATE_DECL
__glstate_GetPointerv(GLenum pname, GLvoid * * params) {
	GLcontext *g = GetCurrentContext();
	GLclientstate *c = &(g->client);
	
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"GetPointerv called in begin/end"))
			return;

	switch (pname) {
	case GL_VERTEX_ARRAY:
		*params = (GLvoid *) c->v.p;
	break;
	case GL_COLOR_ARRAY:
		*params = (GLvoid *) c->c.p;
	break;
	case GL_NORMAL_ARRAY:
		*params = (GLvoid *) c->n.p;
	break;
	case GL_INDEX_ARRAY:
		*params = (GLvoid *) c->i.p;
	break;
	case GL_TEXTURE_COORD_ARRAY:
		*params = (GLvoid *) c->t.p;
	break;
	case GL_EDGE_FLAG_ARRAY:
		*params = (GLvoid *) c->e.p;
	break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetPointerv: invalid pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_DrawArrays(GLenum mode, GLint first, GLsizei count) {
	GLcontext *g = GetCurrentContext();
	
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"DrawArrays called in begin/end"))
			return;

	if (count < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"DrawArrays passed negative count: %d", count))
			return;

	if (mode > GL_POLYGON)
		if (__glerror (__LINE__, __FILE__, GL_INVALID_ENUM,
			"DrawArrays called with invalid mode: %d", mode))
			return;

  UNUSED(first);
}

void GLSTATE_DECL
__glstate_DrawElements( GLenum mode,  GLsizei count,  GLenum type,  const GLvoid *indices) {
	GLcontext *g = GetCurrentContext();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"DrawElements called in begin/end"))
			return;

	if (count < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"DrawArrays passed negative count: %d", count))
			return;

	if (mode > GL_POLYGON)
		if (__glerror (__LINE__, __FILE__, GL_INVALID_ENUM,
			"DrawArrays called with invalid mode: %d", mode))
			return;

	if (type != GL_UNSIGNED_BYTE &&
		type != GL_UNSIGNED_SHORT &&
		type != GL_UNSIGNED_INT)
		if (__glerror (__LINE__, __FILE__, GL_INVALID_ENUM,
			"DrawArrays called with invalid type: %d", type))
			return;
	
  UNUSED (indices);

}

void GLSTATE_DECL
__glstate_ArrayElement (GLint index) {

  UNUSED(index);
}
