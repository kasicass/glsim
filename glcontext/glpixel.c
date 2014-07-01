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

void 
__glpixel_initbits (GLpixelbits *p, GLconfig *cfg) {
	/* do nothing */
	UNUSED(p);
	UNUSED(cfg);
}

void
__glpixel_init (GLpixelstate *p, GLconfig *c) {

	GLcolorf zero_color = {0.0f, 0.0f, 0.0f, 0.0f};
	GLcolorf one_color = {1.0f, 1.0f, 1.0f, 1.0f};

	p->maxpixelmaptable = c->maxpixelmaptable;
	
	p->unpackrowlength = 0;
	p->unpackskiprows = 0;
	p->unpackskippixels = 0;
	p->unpackskipimages = 0;
	p->unpackalignment = 4;
	p->unpackimageheight = 0;
	
	p->packrowlength = 0;
	p->packskiprows = 0;
	p->packskippixels = 0;
	p->packskipimages = 0;
	p->packalignment = 4;
	p->packimageheight = 0;

	p->unpackswapbytes = GL_FALSE;
	p->unpacklsbfirst = GL_FALSE;
	p->packswapbytes = GL_FALSE;
	p->packlsbfirst = GL_FALSE;

	p->indexshift = 0;
	p->indexoffset = 0;

	p->scale = one_color;
	p->depthscale = 1.0f;
	
	p->bias = zero_color;
	p->depthbias = 0.0f;

	p->xzoom = 1.0f;
	p->yzoom = 1.0f;

	/*
	p->pixelmapitoi[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapstos[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapitor[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapitog[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapitob[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapitoa[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmaprtor[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapgtog[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapbtob[GLPIXEL_MAXPIXELMAPTABLE];
	p->pixelmapatoa[GLPIXEL_MAXPIXELMAPTABLE];
	*/

	p->pixelmapitoisize = 1;
	p->pixelmapstossize = 1;
	p->pixelmapitorsize = 1;
	p->pixelmapitogsize = 1;
	p->pixelmapitobsize = 1;
	p->pixelmapitoasize = 1;
	p->pixelmaprtorsize = 1;
	p->pixelmapgtogsize = 1;
	p->pixelmapbtobsize = 1;
	p->pixelmapatoasize = 1;
}

void
__glpixel_destroy(GLpixelstate *p) {
	/* 
	** Do Nothing...
	*/
	UNUSED(p);
}

int
__glpixel_getdata2Dsize (GLsizei width, GLsizei height, GLenum format, 
					   GLenum type) {
	int pixelbytes = width*height;

	switch (format) {
	case GL_COLOR_INDEX :
	case GL_STENCIL_INDEX :
	case GL_DEPTH_COMPONENT :
	case GL_RED :
	case GL_GREEN :
	case GL_BLUE :
	case GL_ALPHA :
	case GL_LUMINANCE :
		break;
	case GL_LUMINANCE_ALPHA :
		pixelbytes *= 2;
		break;
	case GL_RGB :
	case GL_BGR_EXT:
		pixelbytes *= 3;
		break;
	case GL_RGBA :
	case GL_BGRA_EXT :
		pixelbytes *= 4;
		break;
	default:
		UNIMPLEMENTED();
	}

	switch (type) {
	case GL_UNSIGNED_BYTE:
	case GL_BYTE:
		break;
	case GL_BITMAP:
		pixelbytes = width*height/8;
		if((width*height)%8)
			pixelbytes ++;
		break;
	case GL_UNSIGNED_SHORT:
	case GL_SHORT:
		pixelbytes *= 2;
		break;
	case GL_UNSIGNED_INT:
	case GL_INT:
	case GL_FLOAT:
		pixelbytes *= 4;
		break;
	default: 
		UNIMPLEMENTED();
	}
	
	return pixelbytes;
}

int
__glpixel_getdata3Dsize (GLsizei width, GLsizei height, 
						 GLsizei depth, GLenum format, GLenum type) {
	int pixelbytes = width*height*depth;

	switch (format) {
	case GL_COLOR_INDEX :
	case GL_STENCIL_INDEX :
	case GL_DEPTH_COMPONENT :
	case GL_RED :
	case GL_GREEN :
	case GL_BLUE :
	case GL_ALPHA :
	case GL_LUMINANCE :
		break;
	case GL_LUMINANCE_ALPHA :
		pixelbytes *= 2;
		break;
	case GL_RGB :
	case GL_BGR_EXT:
		pixelbytes *= 3;
		break;
	case GL_RGBA :
	case GL_BGRA_EXT :
		pixelbytes *= 4;
		break;
	default:
		UNIMPLEMENTED();
	}

	switch (type) {
	case GL_UNSIGNED_BYTE:
	case GL_BYTE:
		break;
	case GL_BITMAP:
		pixelbytes = width*height/8;
		if((width*height)%8)
			pixelbytes ++;
		break;
	case GL_UNSIGNED_SHORT:
	case GL_SHORT:
		pixelbytes *= 2;
		break;
	case GL_UNSIGNED_INT:
	case GL_INT:
	case GL_FLOAT:
		pixelbytes *= 4;
		break;
	default: 
		UNIMPLEMENTED();
	}
	
	return pixelbytes;
}

void
__glpixel_getdata2D (GLvoid *dstptr, GLsizei width, GLsizei height, 
				   GLenum format, GLenum type, const GLvoid *data) {
	GLcontext *g = GetCurrentContext();
	__glpixel_getdata2D_p(&(g->pixel), dstptr, width, height, format,
		type, data);
}

void
__glpixel_getdata2D_p (GLpixelstate *p, GLvoid *dstptr, GLsizei width, GLsizei height, 
				   GLenum format, GLenum type, const GLvoid *data) {
	const char *src = (const char *) data;
	char *dst = (char *) dstptr;
	int pixelbytes = 1;
	int rowwidth = width;
	int rowbytes;
	int subrowbytes;
	int i;
	int isbitmap = 0;

	switch (format) {
	case GL_COLOR_INDEX :
	case GL_STENCIL_INDEX :
	case GL_DEPTH_COMPONENT :
	case GL_RED :
	case GL_GREEN :
	case GL_BLUE :
	case GL_ALPHA :
	case GL_LUMINANCE :
		break;
	case GL_LUMINANCE_ALPHA :
		pixelbytes *= 2;
		break;
	case GL_RGB :
	case GL_BGR_EXT:
		pixelbytes *= 3;
		break;
	case GL_RGBA :
	case GL_BGRA_EXT :
		pixelbytes *= 4;
		break;
	default:
		UNIMPLEMENTED();
	}

	switch (type) {
	case GL_UNSIGNED_BYTE:
	case GL_BYTE:
		break;
	case GL_BITMAP:
		isbitmap = 1;
		break;
	case GL_UNSIGNED_SHORT:
	case GL_SHORT:
		pixelbytes *= 2;
		break;
	case GL_UNSIGNED_INT:
	case GL_INT:
	case GL_FLOAT:
		pixelbytes *= 4;
		break;
	default: 
		UNIMPLEMENTED();
	}
	
	/* width and height */
	if (p->unpackrowlength > 0)
		rowwidth = p->unpackrowlength;

	rowbytes = rowwidth*pixelbytes;
	subrowbytes = width*pixelbytes;

	/* handle the unpack alignment */
	i = ((int)src)%p->unpackalignment;
	if (i) 
		src += p->unpackalignment - i;

	/* handle skip rows */
	src += p->unpackskiprows*rowbytes;

	/* handle skip pixels */
	src += p->unpackskippixels*pixelbytes;

	if (p->unpacklsbfirst)
		UNIMPLEMENTED();
	if (p->unpackswapbytes)
		UNIMPLEMENTED();

	if (isbitmap) {
		src = ((const char *)data) + ((int)(((const char *)data) - src))/8;
		for (i=0; i<height; i++) {
			memcpy ((void *) dst, (const void *) src, subrowbytes);
			dst+=subrowbytes/8;
			src+=rowbytes/8;
		} 
	} else
		for (i=0; i<height; i++) {
			memcpy ((void *) dst, (const void *) src, subrowbytes);
			dst+=subrowbytes;
			src+=rowbytes;
		}
}


void
__glpixel_getdata3D (GLvoid *dstptr, GLsizei width, GLsizei height, 
				   GLsizei depth, GLenum format, GLenum type, const GLvoid *data) {
	GLcontext *g = GetCurrentContext();
	__glpixel_getdata3D_p(&(g->pixel), dstptr, width, height, depth, format, type, data);

}
	
	
void
__glpixel_getdata3D_p (GLpixelstate *p, GLvoid *dstptr, GLsizei width, GLsizei height, 
				   GLsizei depth, GLenum format, GLenum type, const GLvoid *data) {
	char *src = (char *) data;
	char *dst = (char *) dstptr;
	int pixelbytes = 1;
	int rowwidth = width;
	int imageheight = height;
	int rowbytes;
	int subrowbytes;
	int i,j;

	switch (format) {
	case GL_COLOR_INDEX :
	case GL_STENCIL_INDEX :
	case GL_DEPTH_COMPONENT :
	case GL_RED :
	case GL_GREEN :
	case GL_BLUE :
	case GL_ALPHA :
	case GL_LUMINANCE :
		break;
	case GL_LUMINANCE_ALPHA :
		pixelbytes *= 2;
		break;
	case GL_RGB :
	case GL_BGR_EXT:
		pixelbytes *= 3;
		break;
	case GL_RGBA :
	case GL_BGRA_EXT :
		pixelbytes *= 4;
		break;
	default:
		UNIMPLEMENTED();
	}

	switch (type) {
	case GL_UNSIGNED_BYTE:
	case GL_BYTE:
		break;
	case GL_BITMAP:
		UNIMPLEMENTED();
		break;
	case GL_UNSIGNED_SHORT:
	case GL_SHORT:
		pixelbytes *= 2;
	case GL_UNSIGNED_INT:
	case GL_INT:
	case GL_FLOAT:
		pixelbytes *= 4;
	default: 
		UNIMPLEMENTED();
	}
	
	/* width and height */
	if (p->unpackrowlength > 0)
		rowwidth = p->unpackrowlength;
	if (p->unpackimageheight > 0)
		imageheight = p->unpackimageheight;

	rowbytes = rowwidth*pixelbytes;
	subrowbytes = width*pixelbytes;

	/* handle the unpack alignment */
	i = ((int)src)%p->unpackalignment;
	if (i) 
		src += p->unpackalignment - i;

	/* handle skip images */
	src += p->unpackskipimages*imageheight*rowbytes;

	/* handle skip rows */
	src += p->unpackskiprows*rowbytes;

	/* handle skip pixels */
	src += p->unpackskippixels*pixelbytes;

	if (p->unpacklsbfirst)
		UNIMPLEMENTED();
	if (p->unpackswapbytes)
		UNIMPLEMENTED();

	for (j=0; j<depth; j++) {
		for (i=0; i<height; i++) {
			memcpy ((void *) dst, (const void *) src, subrowbytes);
			dst+=subrowbytes;
			src+=rowbytes;
		}
	}
}


void GLSTATE_DECL
__glstate_PixelStoref (GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLpixelstate *p = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLpixelbits *pb = &(sb->pixel);
	
	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"PixelStoref called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch(pname) {
	case GL_PACK_SWAP_BYTES:
		p->packswapbytes = (GLboolean) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_LSB_FIRST:
		p->packlsbfirst = (GLboolean) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_ROW_LENGTH:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Length: %f", param))
				return;
	/*ECHECK*/
		p->packrowlength = (GLint) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_SKIP_PIXELS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Skip Pixels: %f", param))
				return;
	/*ECHECK*/
		p->packskippixels = (GLint) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_SKIP_ROWS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Skip: %f", param))
				return;
	/*ECHECK*/
		p->packskiprows = (GLint) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_ALIGNMENT:
	/*ECHECK*/
		if (((GLint) param) != 1 && 
			((GLint) param) != 2 &&
			((GLint) param) != 4 &&
			((GLint) param) != 8) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid Alignment: %f", param))
				return;
	/*ECHECK*/
		p->packalignment = (GLint) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;

	case GL_UNPACK_SWAP_BYTES:
		p->unpackswapbytes = GL_TRUE;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_LSB_FIRST:
		p->unpacklsbfirst = GL_TRUE;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_ROW_LENGTH:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Length: %f", param))
				return;
	/*ECHECK*/
		p->unpackrowlength = (GLint) param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_SKIP_PIXELS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Skip Pixels: %f", param))
				return;
	/*ECHECK*/
		p->unpackskippixels = (GLint) param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_SKIP_ROWS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Skip: %f", param))
				return;
	/*ECHECK*/
		p->unpackskiprows = (GLint) param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_ALIGNMENT:
	/*ECHECK*/
		if (((GLint) param) != 1 && 
			((GLint) param) != 2 &&
			((GLint) param) != 4 &&
			((GLint) param) != 8) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid Alignment: %f", param))
				return;
	/*ECHECK*/
		p->unpackalignment = (GLint) param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Unknow glPixelStore enum: %d", pname))
			return;
	/*ECHECK*/
	}
}

void GLSTATE_DECL
__glstate_PixelStorei (GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLpixelstate *p = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLpixelbits *pb = &(sb->pixel);
	
	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"PixelStorei called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch(pname) {
	case GL_PACK_SWAP_BYTES:
		p->packswapbytes = (GLboolean) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_LSB_FIRST:
		p->packlsbfirst = (GLboolean) param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_ROW_LENGTH:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Length: %f", param))
				return;
	/*ECHECK*/
		p->packrowlength = param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_SKIP_PIXELS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Skip Pixels: %f", param))
				return;
	/*ECHECK*/
		p->packskippixels = param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_SKIP_ROWS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Skip: %f", param))
				return;
	/*ECHECK*/
		p->packskiprows = param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_PACK_ALIGNMENT:
	/*ECHECK*/
		if (((GLint) param) != 1 && 
			((GLint) param) != 2 &&
			((GLint) param) != 4 &&
			((GLint) param) != 8) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid Alignment: %f", param))
				return;
	/*ECHECK*/
		p->packalignment = param;
		pb->pack = g->nbitID;
		pb->dirty = g->nbitID;
		break;

	case GL_UNPACK_SWAP_BYTES:
		p->unpackswapbytes = (GLboolean) param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_LSB_FIRST:
		p->unpacklsbfirst = (GLboolean) param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_ROW_LENGTH:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Length: %f", param))
				return;
	/*ECHECK*/
		p->unpackrowlength = param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_SKIP_PIXELS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Skip Pixels: %f", param))
				return;
	/*ECHECK*/
		p->unpackskippixels = param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_SKIP_ROWS:
	/*ECHECK*/
		if (param < 0.0f) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Negative Row Skip: %f", param))
				return;
	/*ECHECK*/
		p->unpackskiprows = param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	case GL_UNPACK_ALIGNMENT:
	/*ECHECK*/
		if (((GLint) param) != 1 && 
			((GLint) param) != 2 &&
			((GLint) param) != 4 &&
			((GLint) param) != 8) 
			if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Invalid Alignment: %f", param))
				return;
	/*ECHECK*/
		p->unpackalignment = param;
		pb->unpack = g->nbitID;
		pb->dirty = g->nbitID;
		break;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Unknown glPixelStore Pname: %d", pname))
			return;
	/*ECHECK*/
	}
}

void GLSTATE_DECL
__glstate_PixelTransferf (GLenum pname, GLfloat param) {
	GLcontext *g = GetCurrentContext();
	GLpixelstate *p = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLpixelbits *pb = &(sb->pixel);
	
	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"PixelTransferf called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch (pname) {
	case GL_MAP_COLOR:
	case GL_MAP_STENCIL:
		UNIMPLEMENTED();
		break;
	case GL_INDEX_SHIFT:
		p->indexshift = (GLint) (param * GL_MAXINT);
		break;
	case GL_INDEX_OFFSET:
		p->indexoffset = (GLint) (param * GL_MAXINT);
		break;
	case GL_RED_SCALE:
		p->scale.r = param;
		break;
	case GL_GREEN_SCALE:
		p->scale.g = param;
		break;
	case GL_BLUE_SCALE:
		p->scale.b = param;
		break;
	case GL_ALPHA_SCALE:
		p->scale.a = param;
		break;
	case GL_DEPTH_SCALE:
		p->depthscale = param;
		break;
	case GL_RED_BIAS:
		p->bias.r = param;
		break;
	case GL_GREEN_BIAS:
		p->bias.g = param;
		break;
	case GL_BLUE_BIAS:
		p->bias.b = param;
		break;
	case GL_ALPHA_BIAS:
		p->bias.a = param;
		break;
	case GL_DEPTH_BIAS:
		p->depthbias = param;
		break;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Unknown glPixelTransfer Pname: %d", pname))
			return;
	/*ECHECK*/
	}
	pb->transfer = g->nbitID;
	pb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_PixelTransferi (GLenum pname, GLint param) {
	GLcontext *g = GetCurrentContext();
	GLpixelstate *p = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLpixelbits *pb = &(sb->pixel);
	
	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"PixelTransferi called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	switch (pname) {
	case GL_MAP_COLOR:
	case GL_MAP_STENCIL:
		UNIMPLEMENTED();
		break;
	case GL_INDEX_SHIFT:
		p->indexshift = param;
		break;
	case GL_INDEX_OFFSET:
		p->indexoffset = param;
		break;
	case GL_RED_SCALE:
		p->scale.r = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_GREEN_SCALE:
		p->scale.g = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_BLUE_SCALE:
		p->scale.b = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_ALPHA_SCALE:
		p->scale.a = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_DEPTH_SCALE:
		p->depthscale = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_RED_BIAS:
		p->bias.r = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_GREEN_BIAS:
		p->bias.g = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_BLUE_BIAS:
		p->bias.b = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_ALPHA_BIAS:
		p->bias.a = ((GLfloat) param) / GL_MAXINT;
		break;
	case GL_DEPTH_BIAS:
		p->depthbias = ((GLfloat) param) / GL_MAXINT;
		break;
	/*ECHECK*/
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_VALUE, "Unknown glPixelTransfer Pname: %d", pname))
			return;
	/*ECHECK*/
	}
	pb->transfer = g->nbitID;
	pb->dirty = g->nbitID;
}


void GLSTATE_DECL
__glstate_PixelZoom (GLfloat xfactor, GLfloat yfactor) {
	GLcontext *g = GetCurrentContext();
	GLpixelstate *p = &(g->pixel);
	GLstatebits *sb = GetStateBits();
	GLpixelbits *pb = &(sb->pixel);

	/*ECHECK*/
	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"PixelZoom called in Begin/End"))
			return;

 
		
	/*ECHECK*/

	p->xzoom = xfactor;
	p->yzoom = yfactor;
	pb->zoom = g->nbitID;
	pb->dirty = g->nbitID;
}

void GLSTATE_DECL
__glstate_PixelMapfv (GLenum map, GLint mapsize, const GLfloat * values) {
	UNUSED(map);
	UNUSED(mapsize);
	UNUSED(values);
	UNIMPLEMENTED();
}
 
void GLSTATE_DECL
__glstate_PixelMapuiv (GLenum map, GLint mapsize, const GLuint * values) {
	UNUSED(map);
	UNUSED(mapsize);
	UNUSED(values);
	UNIMPLEMENTED();
}
 
void GLSTATE_DECL
__glstate_PixelMapusv (GLenum map, GLint mapsize, const GLushort * values) {
	UNUSED(map);
	UNUSED(mapsize);
	UNUSED(values);
	UNIMPLEMENTED();
}
 
void GLSTATE_DECL
__glstate_GetPixelMapfv (GLenum map, const GLfloat * values) {
	UNUSED(map);
	UNUSED(values);
	UNIMPLEMENTED();
}
 
void GLSTATE_DECL
__glstate_GetPixelMapuiv (GLenum map, const GLuint * values) {
	UNUSED(map);
	UNUSED(values);
	UNIMPLEMENTED();
}
 
void GLSTATE_DECL
__glstate_GetPixelMapusv (GLenum map, const GLushort * values) {
	UNUSED(map);
	UNUSED(values);
	UNIMPLEMENTED();
}
