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

#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "gltypes.h"
#include "glconfig.h"

#include "glbuffer.h"
#include "glclient.h"
#include "glcurrent.h"
#include "glenable.h"
#include "gleval.h"
#include "glfog.h"
#include "glget.h"
#include "glhint.h"
#include "glimaging.h"
#include "gllighting.h"
#include "glline.h"
#include "gllists.h"
#include "glpixel.h"
#include "glpolygon.h"
#include "glselection.h"
#include "glstencil.h"
#include "gltexture.h"
#include "gltrans.h"
#include "glviewport.h"

#include "glmystate.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLCONTEXT_MAXCONTEXTS GLBITS_LENGTH

struct GLrenderstate;
struct GLframebuffer;

typedef struct GLstatebits {
	GLbufferbits	  buffer;
	GLclientbits	  client;
	GLcurrentbits	  current;
	GLfogbits		    fog;
	GLhintbits		  hint;
	GLlightingbits	lighting;
	GLlinebits		  line;
	GLpixelbits		  pixel;
	GLpolygonbits	  polygon;
	GLstencilbits	  stencil;
	GLtexturebits	  texture;
	GLtransbits		  trans;
	GLviewportbits	viewport;
	GLevalbits		  eval;
/* Still need implementing... */
	GLimagingbits	  imaging;
	GLlistsbits		  lists;
	GLselectionbits	selection;
} GLstatebits;

typedef struct GLcontext {
	GLbufferstate	  buffer;
	GLclientstate	  client;
	GLcurrentstate	current;
	GLevalstate		  eval;
	GLfogstate		  fog;
	GLhintstate		  hint;
	GLlightingstate	lighting;
	GLlinestate		  line;
	GLlistsstate	  lists;
	GLpixelstate	  pixel;
	GLpolygonstate	polygon;
	GLstencilstate	stencil;
	GLtexturestate	texture;
	GLtransstate	  trans;
	GLviewportstate viewport;

  GLmystate       mystate;
  
  /* Still need implementing */
	GLimagingstate		imaging;
	GLselectionstate	selection;
	
	GLuint			ID;
	GLbitvalue	bitID;
	GLbitvalue	nbitID;
	GLbitvalue	update;
	GLenum			error;
	char *	vendor;
	char *	renderer;
	char *	version;
	char *	extensions;

	GLconfig		*config;

  struct GLrenderstate *renderstate;
  struct GLframebuffer *framebuffer;

} GLcontext;

#ifdef GLCONTEXT_EXPORTS
extern GLboolean __glinitflag;
extern GLcontext *	__currentcontext;
extern GLstatebits	* __statebits;
extern GLint __bktactive;
extern GLconfig * __config;

#define GetCurrentContext() __currentcontext
#define GetStateBits() __statebits
#endif

GLEXPORT GLcontext * __glCreateVirtualContext(GLconfig *cfg);
GLEXPORT GLcontext *	__glCreateContext(GLconfig *cfg);
GLEXPORT GLcontext * __glCreateContext_id(GLconfig *cfg, GLbitvalue id, int i);
GLEXPORT void		     __glMakeCurrent(GLcontext *g);
GLEXPORT GLcontext * __glGetCurrentContext (void);
GLEXPORT void		     __glDestroyContext(GLcontext *g);

GLEXPORT GLenum	GLSTATE_DECL __glstate_GetError(void);

#define UNUSED(x)  ((void) x)

#ifdef __cplusplus
}
#endif

#endif
