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
__glenable_set (GLcontext *g, GLstatebits *sb, GLbitvalue nbitID,
				GLenum cap, GLboolean val) {
	int i;

	i = cap - GL_CLIP_PLANE0;
	if (i >= 0 && i < g->trans.maxclipplanes) {
		g->trans.clip[i] = val;
		sb->trans.enable = nbitID;
		sb->trans.dirty = nbitID;
		return;
	}
	i = cap - GL_LIGHT0;
	if (i >= 0 && i < g->lighting.maxlights) {
		g->lighting.light[i].enable = val;
		sb->lighting.light[i].dirty = nbitID;
		sb->lighting.light[i].enable = nbitID;
		sb->lighting.dirty = nbitID;
		return;
	}
	
	switch (cap) {
	case GL_AUTO_NORMAL:
		g->eval.autonormal = val;
		sb->eval.enable = nbitID;
		sb->eval.dirty = nbitID;
		break;
	case GL_ALPHA_TEST:
		g->buffer.alphatest = val;
		sb->buffer.enable = nbitID;
		sb->buffer.dirty = nbitID;
		break;
	case GL_BLEND:
		g->buffer.blend = val;
		sb->buffer.enable = nbitID;
		sb->buffer.dirty = nbitID;
		break;
	case GL_COLOR_MATERIAL :
		g->lighting.colormaterial = val;
		sb->lighting.enable = nbitID;
		sb->lighting.dirty = nbitID;
		break;
	case GL_CULL_FACE :
		g->polygon.cullface = val;
		sb->polygon.enable = nbitID;
		sb->polygon.dirty = nbitID;
		break;
	case GL_DEPTH_TEST :
		g->buffer.depthtest = val;
		sb->buffer.enable = nbitID;
		sb->buffer.dirty = nbitID;
		break;
	case GL_DITHER :
		g->buffer.dither = val;
		sb->buffer.enable = nbitID;
		sb->buffer.dirty = nbitID;
		break;
	case GL_FOG :
		g->fog.enable = val;
		sb->fog.enable = nbitID;
		sb->fog.dirty = nbitID;
		break;
	case GL_LIGHTING :
		g->lighting.lighting = val;
		sb->lighting.enable = nbitID;
		sb->lighting.dirty = nbitID;
		break;
	case GL_LINE_SMOOTH :
		g->line.linesmooth = val;
		sb->line.enable = nbitID;
		sb->line.dirty = nbitID;
		break;
	case GL_LINE_STIPPLE :
		g->line.linestipple = val;
		sb->line.enable = nbitID;
		sb->line.dirty = nbitID;
		break;
	case GL_LOGIC_OP :
		g->buffer.logicop = val;
		sb->buffer.enable = nbitID;
		sb->buffer.dirty = nbitID;
		break;
	case GL_NORMALIZE :
		g->current.normalize = val;
		sb->current.enable = nbitID;
		sb->current.dirty = nbitID;
		break;
	case GL_POINT_SMOOTH :
		g->line.pointsmooth = val;
		sb->line.enable = nbitID;
		sb->line.dirty = nbitID;
		break;
	case GL_POLYGON_OFFSET_FILL:
		g->polygon.polygonoffset = val;
		sb->polygon.enable = nbitID;
		sb->polygon.dirty = nbitID;
		break;
	case GL_POLYGON_SMOOTH :
		g->polygon.polygonsmooth = val;
		sb->polygon.enable = nbitID;
		sb->polygon.dirty = nbitID;
		break;
	case GL_POLYGON_STIPPLE :
		g->polygon.polygonstipple = val;
		sb->polygon.enable = nbitID;
		sb->polygon.dirty = nbitID;
		break;
	case GL_SCISSOR_TEST :
		g->viewport.scissortest = val;
		sb->viewport.enable = nbitID;
		sb->viewport.dirty = nbitID;
		break;
	case GL_STENCIL_TEST :
		g->stencil.stenciltest= val;
		sb->stencil.enable = nbitID;
		sb->stencil.dirty = nbitID;
		break;
	case GL_TEXTURE_1D :
		g->texture.enabled1d = val;
		sb->texture.enable = nbitID;
		sb->texture.dirty = nbitID;
		break;
	case GL_TEXTURE_2D :
		g->texture.enabled2d = val;
		sb->texture.enable = nbitID;
		sb->texture.dirty = nbitID;
		break;
	case GL_TEXTURE_3D :
		g->texture.enabled3d = val;
		sb->texture.enable = nbitID;
		sb->texture.dirty = nbitID;
		break;
	case GL_TEXTURE_GEN_Q :
		g->texture.texturegen.q = val;
		sb->texture.enable = nbitID;
		sb->texture.dirty = nbitID;
		break;
	case GL_TEXTURE_GEN_R :
		g->texture.texturegen.p = val;
		sb->texture.enable = nbitID;
		sb->texture.dirty = nbitID;
		break;
	case GL_TEXTURE_GEN_S :
		g->texture.texturegen.s = val;
		sb->texture.enable = nbitID;
		sb->texture.dirty = nbitID;
		break;
	case GL_TEXTURE_GEN_T :
		g->texture.texturegen.t = val;
		sb->texture.enable = nbitID;
		sb->texture.dirty = nbitID;
		break;

	case GL_MAP1_COLOR_4 :
	case GL_MAP1_INDEX :
	case GL_MAP1_NORMAL :
	case GL_MAP1_TEXTURE_COORD_1 :
	case GL_MAP1_TEXTURE_COORD_2 :
	case GL_MAP1_TEXTURE_COORD_3 :
	case GL_MAP1_TEXTURE_COORD_4 :
	case GL_MAP1_VERTEX_3 :
	case GL_MAP1_VERTEX_4 :
		g->eval.enable1d[cap - GL_MAP1_COLOR_4] = val;
		sb->eval.enable1d[cap - GL_MAP1_COLOR_4] = nbitID;
		sb->eval.dirty = nbitID;
		break;

	case GL_MAP2_COLOR_4 :
	case GL_MAP2_INDEX :
	case GL_MAP2_NORMAL :
	case GL_MAP2_TEXTURE_COORD_1 :
	case GL_MAP2_TEXTURE_COORD_2 :
	case GL_MAP2_TEXTURE_COORD_3 :
	case GL_MAP2_TEXTURE_COORD_4 :
	case GL_MAP2_VERTEX_3 :
	case GL_MAP2_VERTEX_4 :
		g->eval.enable2d[cap - GL_MAP2_COLOR_4] = val;
		sb->eval.enable2d[cap - GL_MAP2_COLOR_4] = nbitID;
		sb->eval.dirty = nbitID;
		break;

	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glEnable/glDisable called with bogus cap: %d", cap))
			return;
	}
}


void GLSTATE_DECL
__glstate_Enable (GLenum cap) {
	GLcontext *g = GetCurrentContext();
	GLstatebits *sb = GetStateBits();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glEnable called in begin/end"))
			return;

 
		

	__glenable_set(g, sb, g->nbitID, cap, GL_TRUE);

}


void GLSTATE_DECL
__glstate_Disable (GLenum cap) {
	GLcontext *g = GetCurrentContext();
	GLstatebits *sb = GetStateBits();

	if (g->current.beginend)
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION, "glDisable called in begin/end"))
			return;

 
		

	__glenable_set(g, sb, g->nbitID, cap, GL_FALSE);

}
