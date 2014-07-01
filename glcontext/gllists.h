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

#ifndef GLLISTS_H
#define GLLISTS_H

#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLlists_freeelem_s GLlists_freeelem;
struct GLlists_freeelem_s {
	GLuint min;
	GLuint max;
	GLlists_freeelem *next;
	GLlists_freeelem *prev;
};

typedef struct {
	GLbitvalue dirty;
} GLlistsbits;

typedef struct {
	GLint	maxlistnesting;
	GLboolean newend;
	GLlists_freeelem *freelist;
	GLuint base;
} GLlistsstate;

void __gllists_initbits (GLlistsbits *, GLconfig *);
void __gllists_init(GLlistsstate *l, GLconfig *c);
void __gllists_destroy(GLlistsstate *l);

GLEXPORT GLuint GLSTATE_DECL __glstate_GenLists(GLsizei range);
GLEXPORT void GLSTATE_DECL __glstate_NewList	(GLuint list, GLenum mode);
GLEXPORT void GLSTATE_DECL __glstate_EndList (void);
GLEXPORT void GLSTATE_DECL __glstate_DeleteLists (GLuint list, GLsizei range);
GLEXPORT GLboolean GLSTATE_DECL __glstate_IsList(GLuint list);
GLEXPORT void GLSTATE_DECL __glstate_ListBase (GLuint base);

#ifdef __cplusplus
}
#endif

#endif
