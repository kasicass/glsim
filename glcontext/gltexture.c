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
#include <assert.h>
#include "glcontext.h"
#include "glerror.h"


#define GET_TOBJ(tobj,id) 	for (tobj = t->mapping[id%GLTEXTURE_HASHSIZE]; tobj && tobj->name != id; tobj = tobj->next){}
#define GET_HWID(hwid,id) 	for (hwid = t->hwidhash[id%GLTEXTURE_HASHSIZE]; hwid && hwid->name != id; hwid = hwid->next){}

void __gltexture_inittexture_tobj (GLtexturestate *t, GLtextureobj *tobj, GLuint name);
GLtextureobj *__gltexture_allocatetexture_t (GLtexturestate *t, GLuint name);
void __gltexture_deletetexture_t (GLtexturestate *t, GLuint name);

GLtextureobj *tex_broadcast = NULL;

void 
__gltexture_initbits (GLtexturebits *b, GLconfig *cfg) {
	/* do nothing */
	UNUSED(b);
	UNUSED(cfg);
}
\

void
__gltexture_init(GLtexturestate *t, GLconfig *c) {
	int i;
	unsigned int a;
	GLvectorf zero_vector = {0.0f, 0.0f, 0.0f, 0.0f};
	GLcolorf zero_color = {0.0f, 0.0f, 0.0f, 0.0f};
	GLvectorf x_vector = {1.0f, 0.0f, 0.0f, 0.0f};
	GLvectorf y_vector = {0.0f, 1.0f, 0.0f, 0.0f};

	zero_vector.x = 0.0f;
	zero_vector.y = 0.0f;
	zero_vector.z = 0.0f;
	zero_vector.w = 0.0f;

	x_vector.x = 1.0f;
	x_vector.y = 0.0f;
	x_vector.z = 0.0f;
	x_vector.w = 0.0f;

	y_vector.x = 0.0f;
	y_vector.y = 1.0f;
	y_vector.z = 0.0f;
	y_vector.w = 0.0f;

	t->maxtexturesize = c->maxtexturesize;
	t->max3dtexturesize = c->max3dtexturesize;
	for (i=0, a=t->maxtexturesize; a; i++, a=a>>1);
	t->maxlevel = i;
	for (i=0, a=t->max3dtexturesize; a; i++, a=a>>1);
	t->max3dlevel = i;

	t->allocated = 1;

	t->textures = (GLtextureobj *) malloc (sizeof (GLtextureobj));
	__gltexture_inittexture_tobj(t, t->textures, 0);
	t->firstfree = t->textures;
	t->firstfree->next = NULL;

	/* Initalize the hash table to empty */
	for (i=0; i<GLTEXTURE_HASHSIZE; i++)
		t->mapping[i] = NULL;

	for (i=0; i<GLTEXTURE_HASHSIZE; i++)
		t->hwidhash[i] = NULL;

	t->freelist = (GLtexture_freeelem *) malloc (sizeof(GLtexture_freeelem));
	t->freelist->min = 1;
	t->freelist->max = GL_MAXUINT;
	t->freelist->next = NULL;
	t->freelist->prev = NULL;

	t->currenttexture1d = &(t->base1d);
	t->currenttexture2d = &(t->base2d);
	t->currenttexture3d = &(t->base3d);
	
	t->currenttexture1dname = 0;
	t->currenttexture2dname = 0;
	t->currenttexture3dname = 0;

	t->enabled1d = GL_FALSE;
	t->enabled2d = GL_FALSE;
	t->enabled3d = GL_FALSE;
	t->texturegen.s = GL_FALSE;
	t->texturegen.t = GL_FALSE;
	t->texturegen.p = GL_FALSE;
	t->texturegen.q = GL_FALSE;

	t->envmode = GL_MODULATE;
	t->envcolor = zero_color;

	__gltexture_inittexture_tobj(t, &(t->base1d), 0);
	__gltexture_inittexture_tobj(t, &(t->base2d), 0);
	__gltexture_inittexture_tobj(t, &(t->base3d), 0);

	t->gen.s = GL_EYE_LINEAR;
	t->gen.t = GL_EYE_LINEAR;
	t->gen.p = GL_EYE_LINEAR;
	t->gen.q = GL_EYE_LINEAR;
	
	t->objscoeff = x_vector;
	t->objtcoeff = y_vector;
	t->objrcoeff = zero_vector;
	t->objqcoeff = zero_vector;

	t->eyescoeff = x_vector;
	t->eyetcoeff = y_vector;
	t->eyercoeff = zero_vector;
	t->eyeqcoeff = zero_vector;
}

void
__gltexture_inittexture_tobj (GLtexturestate *t, GLtextureobj *tobj, GLuint name){
	int i;
	GLtexturelevel *tl;

	tobj->bordercolor.r = 0.0f;
	tobj->bordercolor.g = 0.0f;
	tobj->bordercolor.b = 0.0f;
	tobj->bordercolor.a = 0.0f;
	tobj->minfilter = GL_NEAREST_MIPMAP_LINEAR;
	tobj->magfilter = GL_LINEAR;
	tobj->wraps = GL_REPEAT;
	tobj->wrapt = GL_REPEAT;
	tobj->target = GL_NONE;
	tobj->name = name;

	tobj->level = (GLtexturelevel *) malloc (sizeof(GLtexturelevel) * t->maxlevel);
	for (i=0; i<t->maxlevel; i++) {
		tl = &(tobj->level[i]);
		tl->bytes = 0;
		tl->img = NULL;
		tl->width = 0;
		tl->height = 0;
		tl->depth = 0;
		tl->border = 0;
		tl->components = 1;
		tl->bytesperpixel = 0;
		tl->format = GL_RGBA;
		tl->type = GL_UNSIGNED_BYTE;
		tl->dirty = 0;  // By default this level is ignored.
	}

	/* UGh. Should be nbitID */
	tobj->dirty = GLBITS_ONES;
	tobj->paramsbit = GLBITS_ONES;
	tobj->imagebit = GLBITS_ONES;
}

void 
__gltexture_inittexture (GLuint name) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj;

	GET_TOBJ(tobj, name);
	if (!tobj) return;

	__gltexture_inittexture_tobj(t, tobj, name);
}

GLtextureobj *
__gltexture_gettexture(GLuint name) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj;

	GET_TOBJ(tobj, name);
	
	return tobj;
}

GLtextureobj *
__gltexture_allocatetexture (GLuint name) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	return __gltexture_allocatetexture_t(t, name);
}


void checkfreelist(GLtexturestate *t) {
	GLtextureobj *tobj;
	GLtexture_freeelem *f;
	GLuint i;

	for (i=1; i < t->freelist->min; i++) {
		GET_TOBJ(tobj, i);
		assert(tobj);
	}		

	for (f = t->freelist; f; f = f->next) {
		if (f->max == GL_MAXUINT) return;
		for (i = f->max+1; i < (f->next?f->next->min:GL_MAXUINT); i++) {
			GET_TOBJ(tobj, i)
			if (t->mapping[i%GLTEXTURE_HASHSIZE]) assert(tobj);
		}
	}
}
		

GLtextureobj *
__gltexture_allocatetexture_t (GLtexturestate *t, GLuint name) {
	GLuint i;
	GLtextureobj *tobj;
	GLtexture_freeelem *k;
	GLtexture_freeelem *newelem;

	if (!name) return NULL;

	/* First we use the firstfree*/
	if (t->firstfree) {
		GLtextureobj *j;
		tobj = t->firstfree;

		i = name % GLTEXTURE_HASHSIZE;
		/* Check to see that it isn't already there */
		if (t->mapping[i]) {
			for (j = t->mapping[i]; j && j->name != name; j=j->next);
			if (j) return j; /* Return object that was already allocated. */
		}
		/* Remove tobj from the free list */
		t->firstfree = tobj->next;

		/* Insert it in the hash table */
		tobj->next = t->mapping[i];
		t->mapping[i] = tobj;

		/* Initalize all of its members */
		__gltexture_inittexture_tobj(t, tobj, name);

		/* Include name into the free list */
		/* First find which region it fits in */
		for (k=t->freelist; k && !(k->min <= name && name <= k->max) && !(k->min > name); k=k->next);

		if (!k) 
			UNIMPLEMENTED();

		if (k->min > name)
			UNIMPLEMENTED();

		/* (name, name) */
		if (k->max == name && k->min == name) {
			/*Remove from freelist*/
			if (k==t->freelist) {
				t->freelist = t->freelist->next;
				t->freelist->prev = NULL;
			} else {
				k->prev->next = k->next;
				k->next->prev = k->prev;
			}
			free (k);
			return tobj;
		}
		
		/* (name, ~) */
		if (k->min == name) {
			k->min++;
			return tobj;
		}

		/* (~, name) */
		if (k->max == name) {
			k->max--;
			return tobj;
		}

		/* (<name, >name) change to        */
		/* (<name, name-1) (name+1, >name) */
		newelem = (GLtexture_freeelem *) malloc (sizeof(GLtexture_freeelem));
		newelem->min = name+1;
		newelem->max = k->max;
		k->max = name-1;

		newelem->next = k->next;
		newelem->prev = k;
		if (k->next)
			k->next->prev = newelem;
		k->next = newelem;
		return tobj;
	}

	/* No firstfree available, lets allocate some more and try again. */
	tobj = t->textures;
	t->textures = (GLtextureobj *) realloc(tobj, t->allocated*2*sizeof (GLtextureobj));

	if (tobj != t->textures) {
		/* Fix all the pointers */
		for (i=0; i<t->allocated; i++) 
			if (t->textures[i].next)
				t->textures[i].next = t->textures + (t->textures[i].next - tobj);
		for (i=0; i<GLTEXTURE_HASHSIZE; i++)
			if (t->mapping[i])
				t->mapping[i] = t->textures + (t->mapping[i] - tobj);
	
		if (t->currenttexture1d != &(t->base1d)) 
			t->currenttexture1d = t->textures + (t->currenttexture1d - tobj);
		if (t->currenttexture2d != &(t->base2d)) 
			t->currenttexture2d = t->textures + (t->currenttexture2d - tobj);
		if (t->currenttexture3d != &(t->base3d)) 
			t->currenttexture3d = t->textures + (t->currenttexture3d - tobj);
	}

	/* Update the free list */
	t->firstfree = t->textures+t->allocated;
	for (i=t->allocated; i < t->allocated*2; i++) {
		__gltexture_inittexture_tobj(t, t->textures+i, 0);		
		t->textures[i].next = t->textures+i+1;
	}

	t->textures[t->allocated*2-1].next = NULL;
	t->allocated*=2;

	/* Call function again. Gotta love that tail recursion! */
	return __gltexture_allocatetexture_t (t, name);
}

void 
__gltexture_deletetexture(GLuint name) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	__gltexture_deletetexture_t(t, name);
}

void 
__gltexture_deletetexture_t(GLtexturestate *t, GLuint name) {
	GLtextureobj *i;
	GLtextureobj **iprev;
	GLtexture_freeelem *j;
	GLtexture_freeelem *jnext;
	int k;

	if (!name) return;

	/* Find it in the hash */
	for (iprev = &(t->mapping[name % GLTEXTURE_HASHSIZE]), i=t->mapping[name % GLTEXTURE_HASHSIZE]; 
			 i && i->name != name; 
			 iprev = &((*iprev)->next), i = i->next);
	
	if (!i) return; /* Freeing a freed obj */

	/* Clear the image ptr */
	for (k=0; k<t->maxlevel; k++) {
		GLtexturelevel *tl = i->level+k;
		if (tl->img) {
			free (tl->img);
			tl->img = NULL;
			tl->bytes = 0;
		}
	}
	free (i->level);
	i->level = NULL;
		
	/* Remove from hash table */
	*iprev = i->next;
	
	/* Add to firstfree */
	i->next = t->firstfree;
	t->firstfree = i;

	/*********************************/
	/* Add the name to the freelist  */
	/* Find the bracketing sequences */

	for (j=t->freelist;
		j && j->next && j->next->min < name;
		j = j->next);

	/* j will always be valid */
	if (!j) 
		UNIMPLEMENTED();

	/* Case:  j:(~,name-1) */
	if (j->max+1 == name) {
		j->max++;
		if (j->next && j->max+1 >= j->next->min) {
			/* Collapse */
			j->next->min = j->min;
			j->next->prev = j->prev;
			if (j->prev)
				j->prev->next = j->next;
			if (j==t->freelist) 
				t->freelist = j->next;
			free(j);
		}
		return;
	}

	/* Case: j->next: (name+1, ~)*/
	if (j->next && j->next->min-1 == name) {
		j->next->min--;
		if (j->max+1 >= j->next->min) {
			/* Collapse */
			j->next->min = j->min;
			j->next->prev = j->prev;
			if (j->prev)
				j->prev->next = j->next;
			if (j==t->freelist) 
				t->freelist = j->next;
			free(j);
		}
		return;
	}

	/* Case: j: (name+1, ~) j->next: null */
	if (!j->next && j->min-1 == name) {
		j->min--;
		return;
	}

	jnext = (GLtexture_freeelem *) malloc (sizeof (GLtexture_freeelem));
	jnext->min = name;
	jnext->max = name;

	/* Case: j: (~,name-(2+))  j->next: (name+(2+), ~) or null */
	if (name > j->max) {
		jnext->prev = j;
		jnext->next = j->next;
		if (j->next)
			j->next->prev = jnext;
		j->next = jnext;
		return;
	}

	/* Case: j: (name+(2+), ~) */
	/* Can only happen if j = t->freelist! */
	if (j == t->freelist && j->min > name) {
		jnext->next = j;
		jnext->prev = j->prev;
		j->prev = jnext;
		t->freelist = jnext;
		return;
	}
	
	UNIMPLEMENTED();
}


void
__gltexture_destroy(GLtexturestate *t) {
	unsigned int i;
	int j;
	GLtexture_freeelem *f;

	for (i=0; i<t->allocated; i++) {
		GLtexturelevel *tl = t->textures[i].level;
		for (j=0; j<t->maxlevel; j++)
			if (tl && tl[j].img)
				free(tl[j].img);
		free(t->textures[i].level);
	}

	f = t->freelist;
	while (f) {
		GLtexture_freeelem *fnext = f->next;
		free (f);
		f = fnext;
	}

}


int
__gltexture_getcurrenttexturesize(GLenum target, GLenum level) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	switch (target) {
	case GL_TEXTURE_1D:
		return t->currenttexture1d->level[level].bytes;
	case GL_TEXTURE_2D:
		return t->currenttexture2d->level[level].bytes;
	case GL_TEXTURE_3D:
		return t->currenttexture3d->level[level].bytes;
	}
	return 0;
}

const GLvoid *
__gltexture_getcurrenttexturedata(GLenum target, GLenum level) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	switch (target) {
	case GL_TEXTURE_1D:
		return t->currenttexture1d->level[level].img;
	case GL_TEXTURE_2D:
		return t->currenttexture2d->level[level].img;
	case GL_TEXTURE_3D:
		return t->currenttexture3d->level[level].img;
	}
	return NULL;
}


void GLSTATE_DECL
__glstate_GenTextures(GLsizei n, GLuint *textures) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLsizei i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glGenTextures called in Begin/End"))
			return;

 
		

	if (n < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative n passed to glGenTextures: %d", n))
			return;

	i=0;
	/* Get a valid name */
	for (i=0; i<n; i++) {
		if (!t->freelist)
			UNIMPLEMENTED();
		/* Grab the next free name*/
		textures[i] = t->freelist->min;
		assert( textures[i] );
		__gltexture_allocatetexture_t (t, textures[i]);
	}
}

void GLSTATE_DECL
__glstate_DeleteTextures(GLsizei n, GLuint *textures) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	int i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glDeleteTextures called in Begin/End"))
			return;

 
		

	if (n < 0)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative n passed to glDeleteTextures: %d", n))
			return;

	for (i=0; i<n; i++) {
		GLuint name = textures[i];
		if (name) {
			__gltexture_deletetexture_t(t, name);
			/* if the currenttexture is deleted, 
			** reset back to the base texture.
			*/
			if (name == t->currenttexture1dname) {
				t->currenttexture1d = &(t->base1d);
				t->currenttexture1dname = 0;
			}
			if (name == t->currenttexture2dname) {
				t->currenttexture2d = &(t->base2d);
				t->currenttexture2dname = 0;
			}
			if (name == t->currenttexture3dname) {
				t->currenttexture3d = &(t->base3d);
				t->currenttexture3dname = 0;
			}
		}
	}

	tb->dirty = g->nbitID;
	tb->current = g->nbitID;
}

void GLSTATE_DECL
__glstate_BindTexture(GLenum target, GLuint texture) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glBindTexture called in Begin/End"))
			return;

 
		

	/* Special Case name = 0 */
	if (!texture) {
		switch (target) {
			case GL_TEXTURE_1D:
				t->currenttexture1d = &(t->base1d);
				t->currenttexture1dname = 0;
				break;
			case GL_TEXTURE_2D:
				t->currenttexture2d = &(t->base2d);
				t->currenttexture2dname = 0;
				break;
			case GL_TEXTURE_3D:
				t->currenttexture3d = &(t->base3d);
				t->currenttexture3dname = 0;
				break;
			default:
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid target passed to glBindTexture: %d", target))
					return;
		}

		tb->dirty = g->nbitID;
		tb->current = g->nbitID;
		return;
	}

	/* texture != 0 */
	/* Get the texture */
	GET_TOBJ(tobj, texture);
	if (!tobj)
		tobj = __gltexture_allocatetexture_t(t, texture);
	
	/* Check the targets */
	if (tobj->target == GL_NONE)
		/* Target isn't set so set it now.*/
		tobj->target = target;
	else
		if (tobj->target != target)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "Attempt to bind a texture of diffent dimenions"))
				return;

	/* Set the current texture */
	switch (target) {
	case GL_TEXTURE_1D:
		t->currenttexture1d = tobj;
		t->currenttexture1dname = texture;
		break;
	case GL_TEXTURE_2D:
		t->currenttexture2d = tobj;
		t->currenttexture2dname = texture;
		break;
	case GL_TEXTURE_3D:
		t->currenttexture3d = tobj;
		t->currenttexture3dname = texture;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "Invalid target passed to glBindTexture: %d", target))
			return;
	}
	
	tb->dirty = g->nbitID;
	tb->current = g->nbitID;
}



void GLSTATE_DECL
__glstate_TexImage1D (GLenum target, GLint level, GLint components, 
					  GLsizei width, GLint border, GLenum format,
					  GLenum type, const GLvoid *pixels  ) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLpixelstate *p = &(g->pixel);
	GLtextureobj *tobj;
	GLtexturelevel *tl;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	int i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glTexImage1D called in Begin/End"))
			return;

 
		

	if (target != GL_TEXTURE_1D)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glTexImage1D target != GL_TEXTURE_1D: %d", target))
			return;

	if (level < 0 || level > t->maxlevel) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage1D level oob: %d", level))
			return;

	/* Not needed in 1.1
	if (componnents < 1 || components > 4)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage1D components oob: %d", components))
			return;
	*/

	if (border != 0 && border != 1)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage1D border oob: %d", border))
			return;

	/* check the bits in width */
	i=1;
    if (width > 0)
		for (i=width-2*border; i>0 && !(i&0x1); i = i >> 1);
	if (width < 0 || i!=1) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage1D width is not valid: %d", width))
			return;
	
	if (width > t->maxtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glTexImage1D width oob: %d", width))
			return;

	/*
	** Only set these fields if 
	** defining the base texture.
	*/
	tobj = t->currenttexture1d;
	tl = tobj->level+level;
	tl->bytes = __glpixel_getdata2Dsize(width, 1, format, type);
	
	if (tl->img) 
		free (tl->img);
	tl->img = (GLubyte *) malloc (tl->bytes);

	if (pixels) {
		__glpixel_getdata2D_p(p, (GLvoid *) tl->img,
		width, 1, format, type, pixels);
	}

	tl->width = width;
	tl->height = 1;
	tl->depth = 1;
	tl->format = format;
	tl->border = border;
	tl->components = components;
	tl->type = type;
	tl->bytesperpixel = tl->bytes / width;

	tobj->target = target;

	tl->dirty = g->nbitID;
	tobj->dirty = g->nbitID;
	tobj->imagebit = g->nbitID;
	tb->dirty = g->nbitID;

}

void GLSTATE_DECL
__glstate_TexImage2D (GLenum target, GLint level, GLint components, 
					  GLsizei width, GLsizei height, GLint border,
					  GLenum format, GLenum type, const GLvoid *pixels  ) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLpixelstate *p = &(g->pixel);
	GLtextureobj *tobj;
	GLtexturelevel *tl;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	int i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glTexImage2D called in Begin/End"))
			return;

	if (target != GL_TEXTURE_2D)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glTexImage2D target != GL_TEXTURE_2D: %d", target))
			return;

	if (level < 0 || level > t->maxlevel) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage2D level oob: %d", level))
			return;

	if (border != 0 && border != 1)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage2D border oob: %d", border))
			return;

	/* normal texture case */
	/* check the bits in width */
	i = 1;
	if (width > 0)
		for (i=width-2*border; i>0 && !(i&0x1); i = i >> 1);
	if (width < 0 || i!=1) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage2D width is not valid: %d", width))
			return;
	/* check the bits in height */
	i=1;
	if (height > 0)
		for (i=height-2*border; i>0 && !(i&0x1); i = i >> 1);
	if (height < 0 || i!=1) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage2D height is not valid: %d", height))
			return;

	if (width > t->maxtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glTexImage2D width oob: %d", width))
			return;

	if (height > t->maxtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glTexImage2D height oob: %d", height))
			return;
	
	/*
	** Only set these fields if 
	** defining the base texture.
	*/
	tobj = t->currenttexture2d;
	tl = tobj->level+level;

  tl->bytes= __glpixel_getdata2Dsize(width, height, format, type);

	if (tl->img)
		free (tl->img);
	tl->img= (GLubyte *) malloc (tl->bytes);

  if (pixels) {
		__glpixel_getdata2D_p(p, (GLvoid *) (tl->img),
		width, height, format, type, pixels);
	}

	tl->width = width;
	tl->height = height;
	tl->depth = 1;
	tl->format = format;
	tl->components = components;
	tl->border = border;
	tl->type = type;
  tl->bytesperpixel = tl->bytes/ (width*height);

	tobj->target = target;

	tl->dirty = g->nbitID;
	tobj->dirty = g->nbitID;
	tobj->imagebit = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_TexSubImage1D (GLenum target, GLint level, GLint xoffset, 
					  GLsizei width, GLenum format,
					  GLenum type, const GLvoid *pixels  ) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLpixelstate *p = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	GLtextureobj *tobj = t->currenttexture1d;
	GLtexturelevel *tl = tobj->level + level;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glSubTexImage1D called in Begin/End"))
			return;

 
		

	if (target != GL_TEXTURE_1D)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glSubTexImage1D target != GL_TEXTURE_1D: %d", target))
			return;

	if (level < 0 || level > t->maxlevel) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glSubTexImage1D level oob: %d", level))
			return;

	if (width > t->maxtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glSubTexImage1D width oob: %d", width))
			return;

	/* Not needed in 1.1
	if (componnents < 1 || components > 4)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage1D components oob: %d", components))
			return;
	*/

	/* XXX We need to handle conversion! */	
	if (format != tl->format) {
		UNIMPLEMENTED();
		exit (1);
	}
	if (type != tl->type) {
		UNIMPLEMENTED();
		exit (1);
	}
	if (width + xoffset > tl->width) {
		UNIMPLEMENTED();
		exit (1);
	}

	__glpixel_getdata2D_p(p, tl->img +
		xoffset*tl->bytesperpixel,
		width, 1, format, type, pixels);
	
	tl->dirty = g->nbitID;
	tobj->dirty = g->nbitID;
	tobj->imagebit = g->nbitID;
	tb->dirty = g->nbitID;

}

void GLSTATE_DECL
__glstate_TexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, 
					  GLsizei width, GLsizei height,
					  GLenum format, GLenum type, const GLvoid *pixels  ) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLpixelstate *p = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	GLtextureobj *tobj = t->currenttexture2d;
	GLtexturelevel *tl = tobj->level + level;

	GLubyte *subimg = NULL;
	GLubyte *img = NULL;
	GLubyte *src;

	int i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glTexSubImage2D called in Begin/End"))
			return;

 
		

	if (target != GL_TEXTURE_2D)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glTexSubImage2D target != GL_TEXTURE_2D: %d", target))
			return;

	if (level < 0 || level > t->maxlevel) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexSubImage2D level oob: %d", level))
			return;

	if (width < 0 || width > t->maxtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glSubTexImage2D width oob: %d", width))
			return;

	if (height < 0 || height > t->maxtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glSubTexImage2D height oob: %d", height))
			return;

	
	/* XXX We need to handle conversion! */	
	if (format != tl->format) {
		UNIMPLEMENTED();
		exit (1);
	}
	if (type != tl->type) {
		UNIMPLEMENTED();
		exit (1);
	}
	if (width + xoffset > tl->width) {
		UNIMPLEMENTED();
		exit (1);
	}
	if (height + yoffset > tl->height) {
		UNIMPLEMENTED();
		exit (1);
	}

	subimg = (GLubyte *) malloc (__glpixel_getdata2Dsize(width, height, format, type));
		
	__glpixel_getdata2D_p(p, subimg,		
		width, height, format, type, pixels);

	img =   tl->img +
			xoffset*tl->bytesperpixel +
			yoffset*tl->width*tl->bytesperpixel;
	src = subimg;

	/* Copy the data into the texture */
	for (i=0; i<height; i++) {
		memcpy (img, src, tl->bytesperpixel * width);
		img += tl->width * tl->bytesperpixel;
		src += width * tl->bytesperpixel;
	}

	free (subimg);

	tobj->dirty = g->nbitID;
	tobj->imagebit = g->nbitID;
	tl->dirty = g->nbitID;
	tb->dirty = g->nbitID;

}

void GLSTATE_DECL
__glstate_TexImage3D (GLenum target, GLint level, GLint components, 
					  GLsizei width, GLsizei height, GLsizei depth,
					  GLint border, GLenum format, GLenum type, const GLvoid *pixels  ) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLpixelstate *p = &(g->pixel);
	GLtextureobj *tobj;
	GLtexturelevel *tl;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	int i;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glTexImage3D called in Begin/End"))
			return;

 
		

	if (target != GL_TEXTURE_3D)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glTexImage3D target != GL_TEXTURE_3D: %d", target))
			return;

	if (level < 0 || level > t->max3dlevel) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage3D level oob: %d", level))
			return;

	if (border != 0 && border != 1)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage3D border oob: %d", border))
			return;

	/* check the bits in width */
	i=1;
    if (width > 0)
		for (i=width-2*border; i>0 && !(i&0x1); i = i >> 1);
	if (width < 0 || i!=1) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage3D width is not valid: %d", width))
			return;

	/* check the bits in height */
	i=1;
    if (height > 0)
		for (i=height-2*border; i>0 && !(i&0x1); i = i >> 1);
	if (height < 0 || i!=1) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage3D height is not valid: %d", height))
			return;

	/* check the bits in height */
	i=1;
    if (depth > 0)
		for (i=depth-2*border; i>0 && !(i&0x1); i = i >> 1);
	if (depth < 0 || i!=1) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "glTexImage3D depth is not valid: %d", depth))
			return;

	if (width > t->max3dtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glTexImage3D width oob: %d", width))
			return;

	if (height > t->max3dtexturesize)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glTexImage3D height oob: %d", height))
			return;

	/*
	** Only set these fields if 
	** defining the base texture.
	*/
	tobj = t->currenttexture1d;
	tl = tobj->level+level;

	tobj->target = target;

	tl->components = components;
	tl->border = border;
	tl->width = width;
	tl->height = height;
	tl->depth = depth;
	tl->format = format;
	tl->type = type;
	tl->bytes = __glpixel_getdata3Dsize(width, height, depth, format, type);
	tl->img = (GLubyte *) malloc (tl->bytes);

	__glpixel_getdata3D_p(p, (GLvoid *) tl->img,
		width, height, depth, format, type, pixels);

	tl->dirty = g->nbitID;
	tobj->imagebit = g->nbitID;
	tobj->dirty = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_TexParameterfv (GLenum target, GLenum pname, const GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;
	GLenum e = (GLenum) *param;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"TexParameterfv called in Begin/End"))
			return;

 
		

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamterfv: target is invalid: %d", target))
			return;
	}

	switch (pname) {
	case GL_TEXTURE_MIN_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR &&
			e != GL_NEAREST_MIPMAP_NEAREST &&
			e != GL_LINEAR_MIPMAP_NEAREST &&
			e != GL_NEAREST_MIPMAP_LINEAR &&
			e != GL_LINEAR_MIPMAP_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamterfv: GL_TEXTURE_MIN_FILTER invalid param: %d", e))
				return;
		tobj->minfilter = e;
		break;
	case GL_TEXTURE_MAG_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamterfv: GL_TEXTURE_MAG_FILTER invalid param: %d", e))
				return;
		tobj->magfilter = e;
		break;
	case GL_TEXTURE_WRAP_S:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameterfv: GL_TEXTURE_WRAP_S invalid param: %d", e))
				return;
		tobj->wraps = e;
		break;
	case GL_TEXTURE_WRAP_T:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameterfv: GL_TEXTURE_WRAP_T invalid param: %d", e))
				return;
		tobj->wrapt = e;
		break;
	case GL_TEXTURE_BORDER_COLOR:
		tobj->bordercolor.r = param[0];
		tobj->bordercolor.g = param[1];
		tobj->bordercolor.b = param[2];
		tobj->bordercolor.a = param[3];
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamterfv: Invalid pname: %d", pname))
			return;
	}

	tobj->dirty = g->nbitID;
	tobj->paramsbit = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_TexParameteriv (GLenum target, GLenum pname, const GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;
	GLenum e = (GLenum) *param;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"TexParameteriv called in Begin/End"))
			return;

 
		

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamteriv: target is invalid: %d", target))
			return;
	}

	switch (pname) {
	case GL_TEXTURE_MIN_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR &&
			e != GL_NEAREST_MIPMAP_NEAREST &&
			e != GL_LINEAR_MIPMAP_NEAREST &&
			e != GL_NEAREST_MIPMAP_LINEAR &&
			e != GL_LINEAR_MIPMAP_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamteriv: GL_TEXTURE_MIN_FILTER invalid param: %d", e))
				return;
		tobj->minfilter = e;
		break;
	case GL_TEXTURE_MAG_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamteriv: GL_TEXTURE_MAG_FILTER invalid param: %d", e))
				return;
		tobj->magfilter = e;
		break;
	case GL_TEXTURE_WRAP_S:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameteriv: GL_TEXTURE_WRAP_S invalid param: %d", e))
				return;
		tobj->wraps = e;
		break;
	case GL_TEXTURE_WRAP_T:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameteriv: GL_TEXTURE_WRAP_T invalid param: %d", e))
				return;
		tobj->wrapt = e;
		break;
	case GL_TEXTURE_BORDER_COLOR:
		tobj->bordercolor.r = ((GLfloat) param[0])/GL_MAXINT;
		tobj->bordercolor.g = ((GLfloat) param[1])/GL_MAXINT;
		tobj->bordercolor.b = ((GLfloat) param[2])/GL_MAXINT;
		tobj->bordercolor.a = ((GLfloat) param[3])/GL_MAXINT;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamteriv: Invalid pname: %d", pname))
			return;
	}

	tobj->dirty = g->nbitID;
	tobj->paramsbit = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_TexParameterf (GLenum target, GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;
	GLenum e = (GLenum) param;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);


	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"TexParameterf called in Begin/End"))
			return;

 
		

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamterf: target is invalid: %d", target))
			return;
	}

	switch (pname) {
	case GL_TEXTURE_MIN_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR &&
			e != GL_NEAREST_MIPMAP_NEAREST &&
			e != GL_LINEAR_MIPMAP_NEAREST &&
			e != GL_NEAREST_MIPMAP_LINEAR &&
			e != GL_LINEAR_MIPMAP_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamterf: GL_TEXTURE_MIN_FILTER invalid param: %d", e))
				return;
		tobj->minfilter = e;
		break;
	case GL_TEXTURE_MAG_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamterf: GL_TEXTURE_MAG_FILTER invalid param: %d", e))
				return;
		tobj->magfilter = e;
		break;
	case GL_TEXTURE_WRAP_S:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameterf: GL_TEXTURE_WRAP_S invalid param: %d", e))
				return;
		tobj->wraps = e;
		break;
	case GL_TEXTURE_WRAP_T:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameterf: GL_TEXTURE_WRAP_T invalid param: %d", e))
				return;
		tobj->wrapt = e;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamterf: Invalid pname: %d", pname))
			return;
	}

	tobj->dirty = g->nbitID;
	tobj->paramsbit = g->nbitID;
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_TexParameteri (GLenum target, GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;
	GLenum e = (GLenum) param;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"TexParameteri called in Begin/End"))
			return;

 
		

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamteri: target is invalid: %d", target))
			return;
	}

	switch (pname) {
	case GL_TEXTURE_MIN_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR &&
			e != GL_NEAREST_MIPMAP_NEAREST &&
			e != GL_LINEAR_MIPMAP_NEAREST &&
			e != GL_NEAREST_MIPMAP_LINEAR &&
			e != GL_LINEAR_MIPMAP_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamteri: GL_TEXTURE_MIN_FILTER invalid param: %d", e))
				return;
		tobj->minfilter = e;
		break;
	case GL_TEXTURE_MAG_FILTER:
		if (e != GL_NEAREST &&
			e != GL_LINEAR)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParamteri: GL_TEXTURE_MAG_FILTER invalid param: %d", e))
				return;
		tobj->magfilter = e;
		break;
	case GL_TEXTURE_WRAP_S:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameteri: GL_TEXTURE_WRAP_S invalid param: %d", e))
				return;
		tobj->wraps = e;
		break;
	case GL_TEXTURE_WRAP_T:
		if (e != GL_CLAMP &&
			e != GL_REPEAT)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"TexParameteri: GL_TEXTURE_WRAP_T invalid param: %d", e))
				return;
		tobj->wrapt = e;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"TexParamteri: Invalid pname: %d", pname))
			return;
	}

	tobj->dirty = g->nbitID;
	tobj->paramsbit = g->nbitID;
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_TexEnvf (GLenum target, GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	GLenum e = (GLenum) param;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexEnvf called in begin/end"))
			return;

 
		

	if (target != GL_TEXTURE_ENV)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvf: target != GL_TEXTURE_ENV: %d", target))
			return;
		
	if (pname != GL_TEXTURE_ENV_MODE) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvf: pname != GL_TEXTURE_ENV_MODE: %d", pname))
			return;

	if (e != GL_MODULATE &&
		e != GL_DECAL &&
		e != GL_BLEND &&
		e != GL_REPLACE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvf: invalid param: %f", param))
			return;
		
	t->envmode = e;
	tb->envbit = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_TexEnvi (GLenum target, GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	GLenum e = (GLenum) param;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexEnvi called in begin/end"))
			return;

 
		

	if (target != GL_TEXTURE_ENV)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvi: target != GL_TEXTURE_ENV: %d", target))
			return;
		
	if (pname != GL_TEXTURE_ENV_MODE) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvi: pname != GL_TEXTURE_ENV_MODE: %d", pname))
			return;

	if (e != GL_MODULATE &&
		e != GL_DECAL &&
		e != GL_BLEND &&
		e != GL_REPLACE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvi: invalid param: %d", param))
			return;
		
	t->envmode = e;
	tb->envbit = g->nbitID;
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_TexEnvfv (GLenum target, GLenum pname, const GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	GLenum e;
	GLcolorf c;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexEnvfv called in begin/end"))
			return;

 
		

	if (target != GL_TEXTURE_ENV)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvfv: target != GL_TEXTURE_ENV: %d", target))
			return;
		
	switch (pname) {
	case GL_TEXTURE_ENV_MODE:
		e = (GLenum) *param;
		if (e != GL_MODULATE &&
			e != GL_DECAL &&
			e != GL_BLEND &&
			e != GL_REPLACE)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexEnvfv: invalid param: %f", *param))
				return;
			t->envmode = e;
		break;
	case GL_TEXTURE_ENV_COLOR:
		c.r = param[0];
		c.g = param[1];
		c.b = param[2];
		c.a = param[3];
		if (c.r > 1.0f) c.r = 1.0f;
		if (c.g > 1.0f) c.g = 1.0f;
		if (c.b > 1.0f) c.b = 1.0f;
		if (c.a > 1.0f) c.a = 1.0f;
		if (c.r < 0.0f) c.r = 0.0f;
		if (c.g < 0.0f) c.g = 0.0f;
		if (c.b < 0.0f) c.b = 0.0f;
		if (c.a < 0.0f) c.a = 0.0f;
		t->envcolor = c;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvfv: invalid pname: %d", pname))
			return;
	}

	tb->envbit = g->nbitID;
	tb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_TexEnviv (GLenum target, GLenum pname, const GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);
	GLenum e;
	GLcolorf c;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexEnviv called in begin/end"))
			return;

 
		

	if (target != GL_TEXTURE_ENV)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnviv: target != GL_TEXTURE_ENV: %d", target))
			return;
		
	switch (pname) {
	case GL_TEXTURE_ENV_MODE:
		e = (GLenum) *param;
		if (e != GL_MODULATE &&
			e != GL_DECAL &&
			e != GL_BLEND &&
			e != GL_REPLACE)
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexEnviv: invalid param: %f", *param))
				return;
		t->envmode = e;
		break;
	case GL_TEXTURE_ENV_COLOR:
		c.r = ((GLfloat) param[0]) / GL_MAXINT;
		c.g = ((GLfloat) param[1]) / GL_MAXINT;
		c.b = ((GLfloat) param[2]) / GL_MAXINT;
		c.a = ((GLfloat) param[3]) / GL_MAXINT;
		if (c.r < 0.0f) c.r = 0.0f;
		if (c.g < 0.0f) c.g = 0.0f;
		if (c.b < 0.0f) c.b = 0.0f;
		if (c.a < 0.0f) c.a = 0.0f;
		t->envcolor = c;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexEnvfv: invalid pname: %d", pname))
			return;
	}

	tb->envbit = g->nbitID;
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_GetTexEnvfv (GLenum target, GLenum pname, GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__,GL_INVALID_OPERATION,
			"glGetTexEnvfv called in begin/end"))
			return;

	if (target != GL_TEXTURE_ENV)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexEnvfv: target != GL_TEXTURE_ENV: %d", target))
			return;
		
	switch (pname) {
	case GL_TEXTURE_ENV_MODE:
		*param = (GLfloat) t->envmode;
	break;
	case GL_TEXTURE_ENV_COLOR:
		param[0] = t->envcolor.r;
		param[1] = t->envcolor.g;
		param[2] = t->envcolor.b;
		param[3] = t->envcolor.a;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexEnvfv: invalid pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_GetTexEnviv (GLenum target, GLenum pname, GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__,GL_INVALID_OPERATION,
			"glGetTexEnviv called in begin/end"))
			return;

	if (target != GL_TEXTURE_ENV)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexEnviv: target != GL_TEXTURE_ENV: %d", target))
			return;
		
	switch (pname) {
	case GL_TEXTURE_ENV_MODE:
		*param = (GLint) t->envmode;
		break;
	case GL_TEXTURE_ENV_COLOR:
		param[0] = (GLint) (t->envcolor.r * GL_MAXINT);
		param[0] = (GLint) (t->envcolor.g * GL_MAXINT);
		param[0] = (GLint) (t->envcolor.b * GL_MAXINT);
		param[0] = (GLint) (t->envcolor.a * GL_MAXINT);
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexEnviv: invalid pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_TexGend (GLenum coord, GLenum pname, GLdouble param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLenum e = (GLenum) param;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexGen called in begin/end"))
			return;

 
		

	if (pname != GL_TEXTURE_GEN_MODE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus pname: %d", pname))
			return;
	
	if (e != GL_OBJECT_LINEAR &&
		e != GL_EYE_LINEAR &&
		e != GL_SPHERE_MAP)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bad param: %lf", param))
			return;

	switch (coord) {
	case GL_S:
		t->gen.s = e;
		break;
	case GL_T:
		t->gen.t = e;
		break;
	case GL_R:
		if (e == GL_SPHERE_MAP) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen: Cannot set GL_R for GL_SPHERE_MAP."))
				return;
		t->gen.p = e;
		break;
	case GL_Q:
		if (e == GL_SPHERE_MAP) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen: Cannot set GL_Q for GL_SPHERE_MAP."))
				return;
		t->gen.q = e;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus coord: %d", coord))
			return;
	}

	tb->gen = g->nbitID;	
	tb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_TexGenf (GLenum coord, GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLenum e = (GLenum) param;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexGen called in begin/end"))
			return;

 
		

	if (pname != GL_TEXTURE_GEN_MODE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus pname: %d", pname))
			return;
	
	if (e != GL_OBJECT_LINEAR &&
		e != GL_EYE_LINEAR &&
		e != GL_SPHERE_MAP)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bad param: %f", param))
			return;

	switch (coord) {
	case GL_S:
		t->gen.s = e;
		break;
	case GL_T:
		t->gen.t = e;
		break;
	case GL_R:
		if (e == GL_SPHERE_MAP) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen: Cannot set GL_R for GL_SPHERE_MAP."))
				return;
		t->gen.p = e;
		break;
	case GL_Q:
		if (e == GL_SPHERE_MAP) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen: Cannot set GL_Q for GL_SPHERE_MAP."))
				return;
		t->gen.q = e;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus coord: %d", coord))
			return;
	}

	tb->dirty = g->nbitID;
	tb->gen = g->nbitID;
}


void GLSTATE_DECL
__glstate_TexGeni (GLenum coord, GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLenum e = (GLenum) param;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexGen called in begin/end"))
			return;

 
		

	if (pname != GL_TEXTURE_GEN_MODE)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus pname: %d", pname))
			return;
	
	if (e != GL_OBJECT_LINEAR &&
		e != GL_EYE_LINEAR &&
		e != GL_SPHERE_MAP)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bad param: %d", param))
			return;

	switch (coord) {
	case GL_S:
		t->gen.s = e;
		break;
	case GL_T:
		t->gen.t = e;
		break;
	case GL_R:
		if (e == GL_SPHERE_MAP) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen: Cannot set GL_R for GL_SPHERE_MAP."))
				return;
		t->gen.p = e;
		break;
	case GL_Q:
		if (e == GL_SPHERE_MAP) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen: Cannot set GL_Q for GL_SPHERE_MAP."))
				return;
		t->gen.q = e;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus coord: %d", coord))
			return;
	}

	tb->dirty = g->nbitID;
	tb->gen = g->nbitID;
}


void GLSTATE_DECL
__glstate_TexGendv (GLenum coord, GLenum pname, const GLdouble *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtransstate *trans = &(g->trans);
	GLvectorf v;
	GLenum e;
	GLmatrix inv;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexGen called in begin/end"))
			return;

 
		

	switch (coord) {
	case GL_S:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR &&
				e != GL_SPHERE_MAP)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.s = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objscoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyescoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_T:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR &&
				e != GL_SPHERE_MAP)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.t = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objtcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyetcoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_R:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.p = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objrcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyercoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_Q:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.q = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objqcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyeqcoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus coord: %d", coord))
			return;
	}
}

void GLSTATE_DECL
__glstate_TexGenfv (GLenum coord, GLenum pname, const GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtransstate *trans = &(g->trans);
	GLvectorf v;
	GLenum e;
	GLmatrix inv;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexGen called in begin/end"))
			return;

 
		

	switch (coord) {
	case GL_S:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR &&
				e != GL_SPHERE_MAP)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.s = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			t->objscoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyescoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_T:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR &&
				e != GL_SPHERE_MAP)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.t = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			t->objtcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyetcoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_R:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.p = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			t->objrcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyercoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_Q:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.q = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			t->objqcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = param[0];
			v.y = param[1];
			v.z = param[2];
			v.w = param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyeqcoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus coord: %d", coord))
			return;
	}
}

void GLSTATE_DECL
__glstate_TexGeniv (GLenum coord, GLenum pname, const GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtransstate *trans = &(g->trans);
	GLvectorf v;
	GLenum e;
	GLmatrix inv;
	GLstatebits *sb = GetStateBits();
	GLtexturebits *tb = &(sb->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glTexGen called in begin/end"))
			return;

 
		

	switch (coord) {
	case GL_S:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR &&
				e != GL_SPHERE_MAP)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.s = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objscoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyescoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_T:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR &&
				e != GL_SPHERE_MAP)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.t = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objtcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyetcoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_R:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.p = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objrcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyercoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	case GL_Q:
		switch (pname) {
		case GL_TEXTURE_GEN_MODE:
			e = (GLenum) *param;
			if (e != GL_OBJECT_LINEAR &&
				e != GL_EYE_LINEAR)
				if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
					"glTexGen called with bad param: %lf", *param))
					return;
			t->gen.q = e;
			tb->gen = g->nbitID;
			tb->dirty = g->nbitID;
		break;
		case GL_OBJECT_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			t->objqcoeff = v;
			tb->objgen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		case GL_EYE_PLANE:
			v.x = (GLfloat) param[0];
			v.y = (GLfloat) param[1];
			v.z = (GLfloat) param[2];
			v.w = (GLfloat) param[3];
			__gltrans_InvertTransposeMatrix(&inv, trans->modelview+trans->modelviewdepth);
			__gltrans_TransformPointMatrixf(&inv, &v);
			t->eyeqcoeff = v;
			tb->eyegen = g->nbitID;
			tb->dirty = g->nbitID;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glTexGen called with bogus pname: %d", pname))
				return;
		}
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glTexGen called with bogus coord: %d", coord))
			return;
	}
}


void GLSTATE_DECL
__glstate_GetTexGendv (GLenum coord, GLenum pname, GLdouble *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetTexGen called in begin/end"))
			return;

	switch (pname) {
	case GL_TEXTURE_GEN_MODE:
		switch (coord) {
		case GL_S:
			*param = (GLdouble) t->gen.s;
			break;
		case GL_T:
			*param = (GLdouble) t->gen.t;
			break;
		case GL_R:
			*param = (GLdouble) t->gen.p;
			break;
		case GL_Q:
			*param = (GLdouble) t->gen.q;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	case GL_OBJECT_PLANE:
		switch (coord) {
		case GL_S:
			param[0] = (GLdouble) t->objscoeff.x;
			param[1] = (GLdouble) t->objscoeff.y;
			param[2] = (GLdouble) t->objscoeff.z;
			param[3] = (GLdouble) t->objscoeff.w;
			break;
		case GL_T:
			param[0] = (GLdouble) t->objtcoeff.x;
			param[1] = (GLdouble) t->objtcoeff.y;
			param[2] = (GLdouble) t->objtcoeff.z;
			param[3] = (GLdouble) t->objtcoeff.w;
			break;
		case GL_R:
			param[0] = (GLdouble) t->objrcoeff.x;
			param[1] = (GLdouble) t->objrcoeff.y;
			param[2] = (GLdouble) t->objrcoeff.z;
			param[3] = (GLdouble) t->objrcoeff.w;
			break;
		case GL_Q:
			param[0] = (GLdouble) t->objqcoeff.x;
			param[1] = (GLdouble) t->objqcoeff.y;
			param[2] = (GLdouble) t->objqcoeff.z;
			param[3] = (GLdouble) t->objqcoeff.w;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	case GL_EYE_PLANE:
		switch (coord) {
		case GL_S:
			param[0] = (GLdouble) t->eyescoeff.x;
			param[1] = (GLdouble) t->eyescoeff.y;
			param[2] = (GLdouble) t->eyescoeff.z;
			param[3] = (GLdouble) t->eyescoeff.w;
			break;
		case GL_T:
			param[0] = (GLdouble) t->eyetcoeff.x;
			param[1] = (GLdouble) t->eyetcoeff.y;
			param[2] = (GLdouble) t->eyetcoeff.z;
			param[3] = (GLdouble) t->eyetcoeff.w;
			break;
		case GL_R:
			param[0] = (GLdouble) t->eyercoeff.x;
			param[1] = (GLdouble) t->eyercoeff.y;
			param[2] = (GLdouble) t->eyercoeff.z;
			param[3] = (GLdouble) t->eyercoeff.w;
			break;
		case GL_Q:
			param[0] = (GLdouble) t->eyeqcoeff.x;
			param[1] = (GLdouble) t->eyeqcoeff.y;
			param[2] = (GLdouble) t->eyeqcoeff.z;
			param[3] = (GLdouble) t->eyeqcoeff.w;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexGen called with bogus pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_GetTexGenfv (GLenum coord, GLenum pname, GLfloat *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetTexGen called in begin/end"))
			return;

	switch (pname) {
	case GL_TEXTURE_GEN_MODE:
		switch (coord) {
		case GL_S:
			*param = (GLfloat) t->gen.s;
			break;
		case GL_T:
			*param = (GLfloat) t->gen.t;
			break;
		case GL_R:
			*param = (GLfloat) t->gen.p;
			break;
		case GL_Q:
			*param = (GLfloat) t->gen.q;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	case GL_OBJECT_PLANE:
		switch (coord) {
		case GL_S:
			param[0] = t->objscoeff.x;
			param[1] = t->objscoeff.y;
			param[2] = t->objscoeff.z;
			param[3] = t->objscoeff.w;
			break;
		case GL_T:
			param[0] =  t->objtcoeff.x;
			param[1] =  t->objtcoeff.y;
			param[2] =  t->objtcoeff.z;
			param[3] =  t->objtcoeff.w;
			break;
		case GL_R:
			param[0] =  t->objrcoeff.x;
			param[1] =  t->objrcoeff.y;
			param[2] =  t->objrcoeff.z;
			param[3] =  t->objrcoeff.w;
			break;
		case GL_Q:
			param[0] =  t->objqcoeff.x;
			param[1] =  t->objqcoeff.y;
			param[2] =  t->objqcoeff.z;
			param[3] =  t->objqcoeff.w;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	case GL_EYE_PLANE:
		switch (coord) {
		case GL_S:
			param[0] =  t->eyescoeff.x;
			param[1] =  t->eyescoeff.y;
			param[2] =  t->eyescoeff.z;
			param[3] =  t->eyescoeff.w;
			break;
		case GL_T:
			param[0] =  t->eyetcoeff.x;
			param[1] =  t->eyetcoeff.y;
			param[2] =  t->eyetcoeff.z;
			param[3] =  t->eyetcoeff.w;
			break;
		case GL_R:
			param[0] =  t->eyercoeff.x;
			param[1] =  t->eyercoeff.y;
			param[2] =  t->eyercoeff.z;
			param[3] =  t->eyercoeff.w;
			break;
		case GL_Q:
			param[0] =  t->eyeqcoeff.x;
			param[1] =  t->eyeqcoeff.y;
			param[2] =  t->eyeqcoeff.z;
			param[3] =  t->eyeqcoeff.w;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexGen called with bogus pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_GetTexGeniv (GLenum coord, GLenum pname, GLint *param) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetTexGen called in begin/end"))
			return;

	switch (pname) {
	case GL_TEXTURE_GEN_MODE:
		switch (coord) {
		case GL_S:
			*param = (GLint) t->gen.s;
			break;
		case GL_T:
			*param = (GLint) t->gen.t;
			break;
		case GL_R:
			*param = (GLint) t->gen.p;
			break;
		case GL_Q:
			*param = (GLint) t->gen.q;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	case GL_OBJECT_PLANE:
		switch (coord) {
		case GL_S:
			param[0] = (GLint) t->objscoeff.x;
			param[1] = (GLint) t->objscoeff.y;
			param[2] = (GLint) t->objscoeff.z;
			param[3] = (GLint) t->objscoeff.w;
			break;
		case GL_T:
			param[0] = (GLint) t->objtcoeff.x;
			param[1] = (GLint) t->objtcoeff.y;
			param[2] = (GLint) t->objtcoeff.z;
			param[3] = (GLint) t->objtcoeff.w;
			break;
		case GL_R:
			param[0] = (GLint) t->objrcoeff.x;
			param[1] = (GLint) t->objrcoeff.y;
			param[2] = (GLint) t->objrcoeff.z;
			param[3] = (GLint) t->objrcoeff.w;
			break;
		case GL_Q:
			param[0] = (GLint) t->objqcoeff.x;
			param[1] = (GLint) t->objqcoeff.y;
			param[2] = (GLint) t->objqcoeff.z;
			param[3] = (GLint) t->objqcoeff.w;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	case GL_EYE_PLANE:
		switch (coord) {
		case GL_S:
			param[0] = (GLint) t->eyescoeff.x;
			param[1] = (GLint) t->eyescoeff.y;
			param[2] = (GLint) t->eyescoeff.z;
			param[3] = (GLint) t->eyescoeff.w;
			break;
		case GL_T:
			param[0] = (GLint) t->eyetcoeff.x;
			param[1] = (GLint) t->eyetcoeff.y;
			param[2] = (GLint) t->eyetcoeff.z;
			param[3] = (GLint) t->eyetcoeff.w;
			break;
		case GL_R:
			param[0] = (GLint) t->eyercoeff.x;
			param[1] = (GLint) t->eyercoeff.y;
			param[2] = (GLint) t->eyercoeff.z;
			param[3] = (GLint) t->eyercoeff.w;
			break;
		case GL_Q:
			param[0] = (GLint) t->eyeqcoeff.x;
			param[1] = (GLint) t->eyeqcoeff.y;
			param[2] = (GLint) t->eyeqcoeff.z;
			param[3] = (GLint) t->eyeqcoeff.w;
			break;
		default:
			if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
				"glGetTexGen called with bogus coord: %d", coord))
				return;
		}
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexGen called with bogus pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_GetTexImage (GLenum target, GLint level, GLenum format,
						 GLenum type, GLvoid * pixels){
	UNUSED(target);
	UNUSED(level);
	UNUSED(format);
	UNUSED(type);
	UNUSED(pixels);
	UNIMPLEMENTED();
}


void GLSTATE_DECL
__glstate_GetTexLevelParameterfv (GLenum target, GLint level, 
								  GLenum pname, GLfloat *params) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetTexLevelParameter called in begin/end"))
			return;

	if (level < 0 && level > t->maxlevel)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glGetTexLevelParameter: level oob: %d", level))
			return;

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default: 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"GetTexLevelParameter: invalid target: %d", target))
			return;
	}
	
	switch (pname) {
	case GL_TEXTURE_WIDTH:
		*params = (GLfloat) tobj->level[level].width;
		break;
	case GL_TEXTURE_HEIGHT:
		*params = (GLfloat) tobj->level[level].height;
		break;
	case GL_TEXTURE_COMPONENTS:
		*params = (GLfloat) tobj->level[level].components;
		break;
	case GL_TEXTURE_BORDER:
		*params = (GLfloat) tobj->level[level].border;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"GetTexLevelParameter: invalid pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_GetTexLevelParameteriv (GLenum target, GLint level, 
								  GLenum pname, GLint *params) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetTexLevelParameter called in begin/end"))
			return;

	if (level < 0 && level > t->maxlevel)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE,
			"glGetTexLevelParameter: level oob: %d", level))
			return;

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default: 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"GetTexLevelParameter: invalid target: %d", target))
			return;
	}
	
	switch (pname) {
	case GL_TEXTURE_WIDTH:
		*params = (GLint) tobj->level[level].width;
		break;
	case GL_TEXTURE_HEIGHT:
		*params = (GLint) tobj->level[level].height;
		break;
	case GL_TEXTURE_COMPONENTS:
		*params = (GLint) tobj->level[level].components;
		break;
	case GL_TEXTURE_BORDER:
		*params = (GLint) tobj->level[level].border;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"GetTexLevelParameter: invalid pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_GetTexParameterfv (GLenum target, GLenum pname, GLfloat *params) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetTexParameter called in begin/end"))
			return;

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default: 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexParameter: invalid target: %d", target))
			return;
	}

	switch (pname) {
	case GL_TEXTURE_MAG_FILTER:
		*params = (GLfloat) tobj->magfilter;
		break;
	case GL_TEXTURE_MIN_FILTER:
		*params = (GLfloat) tobj->minfilter;
		break;
	case GL_TEXTURE_WRAP_S:
		*params = (GLfloat) tobj->wraps;
		break;
	case GL_TEXTURE_WRAP_T:
		*params = (GLfloat) tobj->wrapt;
		break;
	case GL_TEXTURE_BORDER_COLOR:
		params[0] = tobj->bordercolor.r;
		params[1] = tobj->bordercolor.g;
		params[2] = tobj->bordercolor.b;
		params[3] = tobj->bordercolor.a;
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glGetTExParameter: invalid pname: %d", pname))
			return;
	}
}

void GLSTATE_DECL
__glstate_GetTexParameteriv (GLenum target, GLenum pname, GLint *params) {
	GLcontext *g = GetCurrentContext();
	GLtexturestate *t = &(g->texture);
	GLtextureobj *tobj = NULL;

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"glGetTexParameter called in begin/end"))
			return;

	switch (target) {
	case GL_TEXTURE_1D:
		tobj = t->currenttexture1d;
		break;
	case GL_TEXTURE_2D:
		tobj = t->currenttexture2d;
		break;
	case GL_TEXTURE_3D:
		tobj = t->currenttexture3d;
		break;
	default: 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"glGetTexParameter: invalid target: %d", target))
			return;
	}

	switch (pname) {
	case GL_TEXTURE_MAG_FILTER:
		*params = (GLint) tobj->magfilter;
		break;
	case GL_TEXTURE_MIN_FILTER:
		*params = (GLint) tobj->minfilter;
		break;
	case GL_TEXTURE_WRAP_S:
		*params = (GLint) tobj->wraps;
		break;
	case GL_TEXTURE_WRAP_T:
		*params = (GLint) tobj->wrapt;
		break;
	case GL_TEXTURE_BORDER_COLOR:
		params[0] = (GLint) (tobj->bordercolor.r * GL_MAXINT);
		params[1] = (GLint) (tobj->bordercolor.g * GL_MAXINT);
		params[2] = (GLint) (tobj->bordercolor.b * GL_MAXINT);
		params[3] = (GLint) (tobj->bordercolor.a * GL_MAXINT);
		break;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, 
			"glGetTExParameter: invalid pname: %d", pname))
			return;
	}
}


// TODO:
void GLSTATE_DECL
__glstate_PrioritizeTextures (GLsizei n, GLuint * textures, GLclampf * priorities) {
	UNUSED(n);
	UNUSED(textures);
	UNUSED(priorities);
	return;
}
 

GLboolean GLSTATE_DECL
__glstate_AreTexturesResident(GLsizei n, GLuint * textures, GLboolean * residences) {
	UNUSED(n);
	UNUSED(textures);
	UNUSED(residences);
	return GL_TRUE;
}


