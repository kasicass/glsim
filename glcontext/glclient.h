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

#ifndef GLCLIENT_H
#define GLCLIENT_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLbitvalue	dirty;
	GLbitvalue	enableclientstate;
	GLbitvalue	clientpointer;
	GLbitvalue  element;
	GLbitvalue  *v;
	GLbitvalue  *n;
	GLbitvalue  *c;
	GLbitvalue  *i;
	GLbitvalue  *t;
	GLbitvalue  *e;
	int valloc;
	int nalloc;
	int calloc;
	int ialloc;
	int talloc;
	int ealloc;
} GLclientbits;

typedef struct {
	unsigned char *p;
	GLint size;
	GLint type;
	GLint stride;
	GLboolean enabled;

	int bytesperindex;

} GLclientpointer;

typedef struct {
	GLclientpointer v;
	GLclientpointer n;
	GLclientpointer c;
	GLclientpointer i;
	GLclientpointer t;
	GLclientpointer e;

	int *list;
	int list_alloc;
	int list_size;

	GLint	maxelementsindices;
	GLint	maxelementsvertices;
} GLclientstate;

void __glclient_initbits(GLclientbits *c, GLconfig *cfg);

void __glclient_finish(GLclientstate *c, GLclientbits *cb, GLbitvalue bitID);

void __glclient_init (GLclientstate *c, GLconfig *cfg);
void __glclient_destroy (GLclientstate *c);
void __glclient_setclientstate(GLclientstate *c, GLclientbits *cb, GLbitvalue nbitID, 
						  GLenum array, GLboolean state);
void __glclient_setcppointer (GLclientpointer *cp, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

GLEXPORT void GLSTATE_DECL __glstate_EnableClientState (GLenum array);
GLEXPORT void GLSTATE_DECL __glstate_DisableClientState (GLenum array);
GLEXPORT void GLSTATE_DECL __glstate_VertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *p);
GLEXPORT void GLSTATE_DECL __glstate_ColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *p);
GLEXPORT void GLSTATE_DECL __glstate_IndexPointer(GLenum type, GLsizei stride, const GLvoid *p);
GLEXPORT void GLSTATE_DECL __glstate_NormalPointer(GLenum type, GLsizei stride, const GLvoid *p);
GLEXPORT void GLSTATE_DECL __glstate_TexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *p);
GLEXPORT void GLSTATE_DECL __glstate_EdgeFlagPointer(GLsizei stride, const GLvoid *p);
GLEXPORT void GLSTATE_DECL __glstate_InterleavedArrays(GLenum format, GLsizei stride, const GLvoid *p);
GLEXPORT void GLSTATE_DECL __glstate_DrawArrays(GLenum mode, GLint first, GLsizei count);
GLEXPORT void GLSTATE_DECL __glstate_GetPointerv(GLenum pname, GLvoid * * params);
GLEXPORT void GLSTATE_DECL __glstate_DrawArrays(GLenum mode, GLint first, GLsizei count);
GLEXPORT void GLSTATE_DECL __glstate_DrawElements( GLenum mode,  GLsizei count,  GLenum type,  const GLvoid *indices);

#ifdef __cplusplus
}
#endif

#endif


