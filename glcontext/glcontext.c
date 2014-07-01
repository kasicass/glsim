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
#include <string.h>
#include <assert.h>

#include "glcontext.h"
#include "glerror.h"

GLcontext *   __currentcontext = NULL;
GLbitvalue    __bitID = GLBITS_ONES;
GLstatebits	* __statebits;

GLcontext *
__glCreateVirtualContext(GLconfig *cfg) {
	return __glCreateContext_id(cfg, 0, -1);
}

GLcontext *
__glCreateContext(GLconfig *cfg) {
	int i;
	GLbitvalue a;
	GLcontext *g;
  
  /* Get a bitID */
	for (i=0, a=1; i < GLBITS_LENGTH && !(__bitID & a); i++, a = a<<1);

	if (i == GLBITS_LENGTH) 
		if (__glerror(__LINE__, __FILE__, GL_NO_ERROR, 
			"No more context bitIDs available")) {
			return NULL;
		}

	g = __glCreateContext_id(cfg, a, i);
	
	return g;
}

GLcontext *  
__glCreateContext_id(GLconfig *cfg, GLbitvalue id, int i) {
	GLcontext *g;
	

  /* Allocate the statebits */
  if (!__statebits) {
    __statebits = (GLstatebits *) malloc (sizeof (GLstatebits));
	  memset ((void *) __statebits, 0, sizeof (GLstatebits));

    /* Call all the initbits functions */
    __gltrans_initbits    (&(__statebits->trans), cfg);
    __gllighting_initbits	(&(__statebits->lighting), cfg);
    __glclient_initbits		(&(__statebits->client), cfg);
  } else {
    /* fixup the light bits */
    if (__statebits->lighting.numlightbits < cfg->maxlight) {
      GLlightingbits *l = &(__statebits->lighting);
      l->light = (GLlightbits *) realloc (l->light, sizeof(GLlightbits) * cfg->maxlight);
	    memset (l->light+l->numlightbits, 0, sizeof(GLlightbits) * (cfg->maxlight-l->numlightbits));
      l->numlightbits = cfg->maxlight;
    }
  }

	cfg->id = i;

	/* Allocate a new context */
	g = (GLcontext *) malloc (sizeof (GLcontext));
	memset( (void *) g, 0, sizeof (GLcontext));

	/* Set the bitID */
	g->bitID = id;
	g->nbitID = ~id;
	__bitID &= ~id;
	g->ID = i;
	g->update = GLBITS_ONES;

	/* Init the components */
	__glbuffer_init(&(g->buffer), cfg);
	__glclient_init(&(g->client), cfg);
	__glcurrent_init(&(g->current), cfg);
	__gleval_init(&(g->eval), cfg);
	__glfog_init(&(g->fog), cfg);
	__glhint_init(&(g->hint), cfg);
	__glimaging_init(&(g->imaging), cfg);
	__gllighting_init(&(g->lighting), cfg);
	__glline_init(&(g->line), cfg);
	__gllists_init(&(g->lists), cfg);
	__glpixel_init(&(g->pixel), cfg);
	__glpolygon_init(&(g->polygon), cfg);
	__glstencil_init(&(g->stencil), cfg);
	__gltexture_init(&(g->texture), cfg);
	__gltrans_init(&(g->trans), cfg);
	__glviewport_init(&(g->viewport), cfg);
	
  __glmystate_init(&(g->mystate), cfg);

	if (cfg->vendor) {
		g->vendor = (char *) malloc (strlen(cfg->vendor) + 1);
		strcpy (g->vendor, cfg->vendor);
	}
	if (cfg->renderer) {
		g->renderer = (char *) malloc (strlen(cfg->renderer) + 1);
		strcpy (g->renderer, cfg->renderer);
	}
	if (cfg->version) {
		g->version = (char *) malloc (strlen(cfg->version) + 1);
		strcpy (g->version, cfg->version);
	}
	if (cfg->extensions) {
		g->extensions = (char *) malloc (strlen(cfg->extensions) + 1);
		strcpy (g->extensions, cfg->extensions);
	}

	g->error = GL_NO_ERROR;
  g->config = __glconfig_CopyConfig(cfg);

	/* Set initial dirties 
	** Note: We should move these into the init functions...
	*/
	__statebits->trans.base = GLBITS_ONES;
	__statebits->trans.dirty = GLBITS_ONES;

	return g;
}

void
__glMakeCurrent(GLcontext *g) {
	__currentcontext = g;
}

GLcontext *
__glGetCurrentContext (void) {
	return __currentcontext;
}

void
__glDestroyContext(GLcontext *g) {
	__glbuffer_destroy(&(g->buffer));
	__glclient_destroy(&(g->client));
	__glcurrent_destroy(&(g->current));
	__gleval_destroy(&(g->eval));
	__glfog_destroy(&(g->fog));
	__glhint_destroy(&(g->hint));
	__glimaging_destroy(&(g->imaging));
	__gllighting_destroy(&(g->lighting));
	__glline_destroy(&(g->line));
	__gllists_destroy(&(g->lists));
	__glpixel_destroy(&(g->pixel));
	__glpolygon_destroy(&(g->polygon));
	__glstencil_destroy(&(g->stencil));
	__gltexture_destroy(&(g->texture));
	__gltrans_destroy(&(g->trans));
	__glviewport_destroy(&(g->viewport));

#if 0
  if (g->vendor) free(g->vendor);
	if (g->renderer) free(g->renderer);
	if (g->version) free(g->version);
	if (g->extensions) free(g->extensions);
#endif

	__bitID |= g->bitID;
	
	free(g);
}
