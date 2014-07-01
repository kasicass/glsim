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
#include "glcontext.h"
#include "glerror.h"

void
__gllists_initbits (GLlistsbits *l, GLconfig *cfg) {
	/* unimplemented */
	UNUSED(l);
	UNUSED(cfg);
}

void
__gllists_switch (GLlistsbits *l, GLbitvalue b,
				   GLlistsstate *c, GLlistsstate *t) {
	/* unimplemented */
	UNUSED(l);
	UNUSED(b); 
	UNUSED(c);
	UNUSED(t);
}

void
__gllists_sync (GLlistsbits *l, GLbitvalue b,
				   GLlistsstate *c, GLlistsstate *t) {
	/* unimplemented */
	UNUSED(l);
	UNUSED(b);
	UNUSED(c);
	UNUSED(t);
}

void
__gllists_init(GLlistsstate *l, GLconfig *c) {
	l->maxlistnesting = c->maxlistnesting;
	l->newend = GL_FALSE;
	l->freelist = (GLlists_freeelem *) malloc (sizeof(GLlists_freeelem));
	l->freelist->min = 1;
	l->freelist->max = GL_MAXUINT;
	l->freelist->next = NULL;
	l->freelist->prev = NULL;
}

void 
__gllists_destroy(GLlistsstate *l) {
	GLlists_freeelem *f = l->freelist;
	while (f){
		GLlists_freeelem *tmp = f->next;
		free(f);
		f = tmp;
	}
}

void 
__gllists_bindname(GLlistsstate *l, GLuint name) {
	GLlists_freeelem *i;
	GLlists_freeelem *newelem;
	
	/* First find which region it fits in */
	for (i=l->freelist; i && !(i->min <= name && name <= i->max); i=i->next);

	if (!i) return;

	/* (name, name) */
	if (i->max == name && i->min == name) {
		/*Remove from freelist*/
		if (i==l->freelist) {
			l->freelist = l->freelist->next;
			l->freelist->prev = NULL;
		} else {
			i->prev->next = i->next;
			i->next->prev = i->prev;
		}
		free (i);
		return;
	}
		
	/* (name, ~) */
	if (i->min == name) {
		i->min++;
		return;
	}

	/* (~, name) */
	if (i->max == name) {
		i->max--;
		return;
	}

	/* (<name, >name) change to        */
	/* (<name, name-1) (name+1, >name) */
	newelem = (GLlists_freeelem *) malloc (sizeof(GLlists_freeelem));
	newelem->min = name+1;
	newelem->max = i->max;
	i->max = name-1;

	newelem->next = i->next;
	newelem->prev = i;
	if (i->next)
		i->next->prev = newelem;
	i->next = newelem;
}


void
__gllists_unbindname(GLlistsstate *l, GLuint name) {
	GLlists_freeelem *i;
	GLlists_freeelem *newelem;

	/*********************************/
	/* Add the name to the freelist  */
	/* Find the bracketing sequences */

	for (i=l->freelist;
		i && i->next && i->next->min < name;
		i = i->next);

	/* j will always be valid */
	if (!i) return;
	if (!i->next && i->max == name)  return;

	/* Case:  j:(~,name-1) */
	if (i->max+1 == name) {
		i->max++;
		if (i->next && i->max+1 >= i->next->min) {
			/* Collapse */
			i->next->min = i->min;
			i->next->prev = i->prev;
			if (i->prev)
				i->prev->next = i->next;
			if (i==l->freelist) 
				l->freelist = i->next;
			free(i);
		}
		return;
	}

	/* Case: j->next: (name+1, ~)*/
	if (i->next && i->next->min-1 == name) {
		i->next->min--;
		if (i->max+1 >= i->next->min) {
			/* Collapse */
			i->next->min = i->min;
			i->next->prev = i->prev;
			if (i->prev)
				i->prev->next = i->next;
			if (i==l->freelist) 
				l->freelist = i->next;
			free(i);
		}
		return;
	}

	/* Case: j: (name+1, ~) j->next: null */
	if (!i->next && i->min-1 == name) {
		i->min--;
		return;
	}

	newelem = (GLlists_freeelem *) malloc (sizeof (GLlists_freeelem));
	newelem->min = name;
	newelem->max = name;

	/* Case: j: (~,name-(2+))  j->next: (name+(2+), ~) or null */
	if (name > i->max) {
		newelem->prev = i;
		newelem->next = i->next;
		if (i->next)
			i->next->prev = newelem;
		i->next = newelem;
		return;
	}

	/* Case: j: (name+(2+), ~) */
	/* Can only happen if j = t->freelist! */
	if (i == l->freelist && i->min > name) {
		newelem->next = i;
		newelem->prev = i->prev;
		i->prev = newelem;
		l->freelist = newelem;
		return;
	}
	
	UNIMPLEMENTED();
}


GLuint GLSTATE_DECL
__glstate_GenLists(GLsizei range) {
	GLcontext *g = GetCurrentContext();
	GLlistsstate *l = &(g->lists);
	GLlists_freeelem *f;
	GLuint ret;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glGenLists called in Begin/End"))
			return 0;

	if (range < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative range passed to glGenLists: %d", range))
			return 0;


	f = l->freelist;
	while (f) {
		GLuint temp = f->max - f->min;
		if (temp >= (GLuint) (range - 1)) {
			ret = f->min;
			f->min += range-1;
			/*
			** To handle the list management, we call
			** __glstate_bindname on the last one
			** so that everything gets cleaned up
			*/
			__gllists_bindname(l, f->min);
			return ret;
		}
		f = f->next;
	}

	UNIMPLEMENTED();
	return 0;
}
	
void GLSTATE_DECL
__glstate_NewList (GLuint list, GLenum mode) {
	GLcontext *g = GetCurrentContext();
	GLlistsstate *l = &(g->lists);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glNewList called in Begin/End"))
			return;

	if (l->newend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glNewList called inside display list"))
			return;

	__gllists_bindname (l, list);	

	l->newend = GL_TRUE;

  UNIMPLEMENTED();
  
  UNUSED(mode);

}

void GLSTATE_DECL
__glstate_EndList (void) {
	GLcontext *g = GetCurrentContext();
	GLlistsstate *l = &(g->lists);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glEndList called in Begin/End"))
			return;

	if (!l->newend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glEndList called without preceeding glNewList"))
			return;
		
  l->newend = GL_FALSE;

  UNIMPLEMENTED();
}


void GLSTATE_DECL
__glstate_DeleteLists (GLuint list, GLsizei range) {
	int i;
	GLcontext *g = GetCurrentContext();
	GLlistsstate *l = &(g->lists);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glDeleteLists called in Begin/End"))
			return;

	if (range < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative range passed to glDeleteLists: %d", range))
			return;

	for (i=0; i<range; i++)
		__gllists_unbindname(l, list+i);
}

GLboolean GLSTATE_DECL
__glstate_IsList(GLuint list) {
	GLcontext *g = GetCurrentContext();
	GLlistsstate *l = &(g->lists);
	GLlists_freeelem *i;


	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"GenLists called in Begin/End"))
			return GL_FALSE;
	
	/* First find which region it fits in */
	for (i=l->freelist; i && !(i->min <= list && list <= i->max); i=i->next);

	if (i) return GL_TRUE;
	return GL_FALSE;
}
	
void GLSTATE_DECL
__glstate_ListBase (GLuint base) {
	GLcontext *g = GetCurrentContext();
	GLlistsstate *l = &(g->lists);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"ListBase called in Begin/End"))
			return;

	l->base = base;
}
