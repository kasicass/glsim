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

#include "gltypes.h"
#include "glconfig.h"
#include "glcontext.h"

#define GLCONFIG_VENDOR "GLConfig 1.0 by Ian Buck"
#define GLCONFIG_RENDERER "GLConfig"
#define GLCONFIG_VERSION "1.1"
#define GLCONFIG_EXTENSIONS ""


GLconfig *
__glconfig_CreateDefaultConfig (void){
	GLconfig *c = (GLconfig *) malloc (sizeof (GLconfig));
	memset((void *) c, 0, sizeof (GLconfig));
	
	c->vendor = _strdup (GLCONFIG_VENDOR);
	c->renderer = _strdup (GLCONFIG_RENDERER);
	c->version = _strdup (GLCONFIG_VERSION);
	c->extensions = _strdup (GLCONFIG_EXTENSIONS);

	c->maxlight = 8;
	c->max3dtexturesize = 16;
	c->maxnamestackdepth = 64;
	c->maxlistnesting = 64;
	c->maxevalorder = 8;
	c->maxattribstackdepth = 16;
	c->maxclientattribstackdepth = 16;
	c->auxbuffers = 0;
	c->rgbamode = GL_TRUE;
	c->indexmode = GL_FALSE;
	c->doublebuffer = GL_TRUE;
	c->stereo = GL_FALSE;
	c->subpixelbits = 4;
	c->redbits = 8;
	c->greenbits = 8;
	c->bluebits = 8;
	c->alphabits = 8;
	c->depthbits = 24;
	c->stencilbits = 32;
	c->accumredbits = 32;
	c->accumgreenbits = 32;
	c->accumbluebits = 32;
	c->accumalphabits = 32;
	c->aliasedpointsizerange_min = 1.0f;
	c->aliasedpointsizerange_max = 1.0f;
	c->aliasedpointsizegranularity = 1.0f;
	c->smoothpointsizerange_min = 1.0f;
	c->smoothpointsizerange_max = 1.0f;
	c->smoothpointgranularity = 1.0f;
	c->aliasedlinewidth_min = 1.0f;
	c->aliasedlinewidth_max = 1.0f;
	c->aliasedlinegranularity = 1.0f;
	c->smoothlinewidth_min = 1.0f;
	c->smoothlinewidth_max = 1.0f;
	c->smoothlinegranularity = 1.0f;
	c->maxconvolution_width = 3;
	c->maxconvolution_height = 3;
	c->maxelementsindices = GL_MAXINT;
	c->maxelementsvertices = GL_MAXINT;
	c->maxpixelmaptable = 32;
	c->maxmodelviewstackdepth = 64;
	c->maxprojectionstackdepth = 8;
	c->maxtexturestackdepth = 8;
	c->maxcolorstackdepth = 8;
	c->maxclipplanes = 6;

	/* HACK for uber screens */
	c->maxviewportdims_width = 2048000;
	c->maxviewportdims_height = 2048000;

	c->maxtexturesize = 2048;

	c->id = 0;
	c->mode = GLCONFIG_STATE;

	c->viewport.x1 = -1;
	c->viewport.y1 = -1;
	c->viewport.x2 = -2;
	c->viewport.y2 = -2;
	c->getwindowsize = NULL;
	c->viewport_valid = GL_FALSE;


	c->gui_error = (getenv("WIREGL_GUI_ERROR")!=NULL);
	c->state_error_gui = (getenv("WIREGL_STATE_ERROR_GUI")!=NULL);
	
	return c;
}

GLconfig *
__glconfig_CopyConfig (GLconfig *a) {
	GLconfig *c;
	GLconfigmsg *msg;

	msg = __glconfig_CreateMessage (a);
	c = __glconfig_CreateMessageConfig (msg);
	__glconfig_FreeMessage(msg);

	return c;
}

void
__glconfig_FreeConfig (GLconfig * c) {
#if 0
	/* XXX: Should free here but causes
	** problems with custom user 
	** malloced strings 
	*/
	if (c->vendor)
		free (c->vendor);
	if (c->renderer)
		free (c->renderer);
	if (c->version)
		free (c->version);
	if (c->extensions)
		free (c->extensions);
#endif
	free (c);
}

GLconfigmsg * 
__glconfig_CreateMessage (GLconfig *c) {
	GLconfigmsg *msg;
	int size;
	char *p;
	size =  sizeof (GLconfigmsg) +
			sizeof (GLconfig) + 
			strlen(c->vendor) + 1 +
			strlen(c->renderer) + 1 +
			strlen(c->version) + 1 +
			strlen(c->extensions) + 1;

	msg = (GLconfigmsg *) malloc (size);
	msg->size = size;

	memcpy ((void *)msg->data, (const void *) c, sizeof (GLconfig));
	p = msg->data + sizeof (GLconfig);
	strcpy (p, c->vendor);
	p+=strlen(c->vendor) + 1;
	strcpy (p, c->renderer);
	p+=strlen(c->renderer) + 1;
	strcpy (p, c->version);
	p+=strlen(c->version) + 1;
	strcpy (p, c->extensions);
	return msg;
}

GLconfig * 
__glconfig_CreateMessageConfig(GLconfigmsg *m) {
	
	GLconfig *c;
	char *vendor;
	char *renderer;
	char *version;
	char *extensions;
	vendor = m->data + sizeof (GLconfig);
	renderer = vendor + strlen(vendor) + 1;
	version = renderer + strlen (renderer) + 1;
	extensions = version + strlen (version) + 1;

	c = __glconfig_CreateDefaultConfig ();
#if 0
	/* MWE: these aren't heap allocated -- or at least they aren't
       necessarily */
	free (c->vendor);
	free (c->renderer);
	free (c->version);
	free (c->extensions);
#endif

	memcpy ((void *) c, (const void *) m->data, sizeof (GLconfig));

#if 0
	c->flush = __glconfig_flushnop;
	c->immediateapi = NULL;
	c->packapi = NULL;
	c->stateapi = NULL;
#endif

	c->vendor = (char *) malloc (strlen (vendor) + 1);
	c->renderer = (char *) malloc (strlen (renderer) + 1);
	c->version = (char *) malloc (strlen (version) + 1);
	c->extensions = (char *) malloc (strlen (extensions) + 1);

	strcpy (c->vendor, vendor);
	strcpy (c->renderer, renderer);
	strcpy (c->version, version);
	strcpy (c->extensions, extensions);

	return c;
}

void 
__glconfig_FreeMessage(GLconfigmsg *m) {
	free (m);
}
