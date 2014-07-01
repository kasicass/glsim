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

#ifndef GLCONST_H
#define GLCONST_H

#include "glbase.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GLCONFIG_TRACK 0x100
#define GLCONFIG_STATE 0x101

#define GLCONFIG_MAX_PROJECTORS 32
#define GLCONFIG_MAX_EXTENTS    256

typedef int (*GLconfig_GetWindowSize_func) ( int *width_return, int *height_return );

struct GLcontext;

typedef struct {
	GLint	maxclipplanes;			/*tranformation*/
	GLint	maxmodelviewstackdepth;
	GLint	maxprojectionstackdepth;
	GLint	maxtexturestackdepth;
	GLint	maxcolorstackdepth;
	GLint	maxlight;				/*lighting*/
	GLint   max3dtexturesize;		/*texture*/
	GLint	maxtexturesize;
	GLint	maxpixelmaptable;		/*pixel*/
	GLint	maxnamestackdepth;		/*selection*/
	GLint	maxlistnesting;			/*list*/
	GLint	maxevalorder;			/*eval*/
	GLint	maxviewportdims_width;	/*viewport*/
	GLint	maxviewportdims_height;
	GLint	maxattribstackdepth;	/*attribs*/
	GLint	maxclientattribstackdepth;
	GLint	auxbuffers;				/*buffer*/
	GLboolean	rgbamode;
	GLboolean	indexmode;
	GLboolean	doublebuffer;
	GLboolean	stereo;
	GLint	subpixelbits;			
	GLint	redbits;
	GLint	greenbits;
	GLint	bluebits;
	GLint	alphabits;
	GLint	depthbits;
	GLint	stencilbits;
	GLint	accumredbits;
	GLint	accumgreenbits;
	GLint	accumbluebits;
	GLint	accumalphabits;
	GLfloat	aliasedpointsizerange_min;	/*line*/
	GLfloat aliasedpointsizerange_max;
	GLfloat	aliasedpointsizegranularity;
	GLfloat smoothpointsizerange_min;
	GLfloat smoothpointsizerange_max;
	GLfloat smoothpointgranularity;
	GLfloat aliasedlinewidth_min;
	GLfloat aliasedlinewidth_max;
	GLfloat aliasedlinegranularity;
	GLfloat smoothlinewidth_min;
	GLfloat smoothlinewidth_max;
	GLfloat smoothlinegranularity;
	GLint	maxconvolution_width;		/*imaging*/
	GLint	maxconvolution_height;
	GLint	maxelementsindices;			/*client*/
	GLint	maxelementsvertices;

	GLenum	mode;
	GLint	id;

	GLrecti viewport;
	GLconfig_GetWindowSize_func getwindowsize;
	GLboolean viewport_valid;

	GLapi *packapi;
	GLjumptable *immediateapi;

	char *	vendor;
	char *	renderer;
	char *	version;
	char *	extensions;

	int gui_error;
	int state_error_gui;

} GLconfig;

typedef struct {
	int size;
	char data[1];
} GLconfigmsg;

GLEXPORT GLconfig *__glconfig_CreateDefaultConfig(void);
GLEXPORT GLconfig *__glconfig_CopyConfig(GLconfig *c);
GLEXPORT void __glconfig_FreeConfig(GLconfig *c);
GLEXPORT GLconfigmsg * __glconfig_CreateMessage (GLconfig *c);
GLEXPORT GLconfig * __glconfig_CreateMessageConfig(GLconfigmsg *m);
GLEXPORT void __glconfig_FreeMessage(GLconfigmsg *m);

#ifdef __cplusplus
}
#endif

#endif
