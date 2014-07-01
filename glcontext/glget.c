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
#include <math.h>

#include "glcontext.h"
#include "glerror.h"

#if 0

static GLint
__glcontext_double_to_int( GLdouble d )
{
    /* i = (GLint) d, with clamping and rounding */
    if ( d >= 2147483647.5 )
        return 0x7fffffff;
    if ( d < -2147483648.5 )
        return 0x80000000;
    return (GLint) floor( d + 0.5 );
}

static GLint
__glcontext_float_to_int( GLfloat f )
{
    /* i = (GLint) f, with clamping and rounding */
    if ( f >= 2147483647.5f )
        return 0x7fffffff;
    if ( f < -2147483648.5f )
        return 0x80000000;
    return (GLint) floor( f + 0.5f );
}

#endif

static GLint
__glcontext_clampd_to_int( GLdouble d )
{
    /* -1.0 -> MIN_INT, 1.0 -> MAX_INT */
    if ( d > 1.0 )
        return 0x7fffffff;
    if ( d < -1.0 )
        return 0x80000000;
    return (GLint) floor( d * 2147483647.5 );
}

static GLint
__glcontext_clampf_to_int( GLfloat f )
{
    /* -1.0f -> MIN_INT, 1.0f -> MAX_INT */
    if ( f > 1.0f )
        return 0x7fffffff;
    if ( f < -1.0f )
        return 0x80000000;
    return (GLint) floor( f * 2147483647.5f );
}

const GLubyte * GLSTATE_DECL
__glstate_GetString (GLenum pname) {
	GLcontext *g = GetCurrentContext( );

	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"GetString called in Begin/End"))
			return NULL;

	switch (pname) {
	case GL_VENDOR:
		return (const GLubyte *) g->vendor;
	case GL_VERSION:
		return (const GLubyte *) g->version;
	case GL_RENDERER:
		return (const GLubyte *) g->renderer;
	case GL_EXTENSIONS:
		return (const GLubyte *) g->extensions;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"GetString with bogus string enum: %d", pname))
			return NULL;
	}
	return NULL;
}




void GLSTATE_DECL
__glstate_GetBooleanv( GLenum pname, GLboolean *params )
{
    GLcontext   *g = GetCurrentContext( );

    if (g->current.beginend)
        if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
                      "glGet called in Begin/End"))
            return;
  
    switch ( pname ) {

      case GL_ACCUM_CLEAR_VALUE:
        params[0] = (GLboolean) ( g->buffer.accumclearvalue.r != 0.0f );
        params[1] = (GLboolean) ( g->buffer.accumclearvalue.g != 0.0f );
        params[2] = (GLboolean) ( g->buffer.accumclearvalue.b != 0.0f );
        params[3] = (GLboolean) ( g->buffer.accumclearvalue.a != 0.0f );
        break;

      case GL_ALPHA_TEST:
        params[0] = (GLboolean) ( g->buffer.alphatest != 0 );
        break;

      case GL_ALPHA_TEST_FUNC:
        params[0] = (GLboolean) ( g->buffer.alphatestfunc != 0 );
        break;

      case GL_ALPHA_TEST_REF:
        params[0] = (GLboolean) ( g->buffer.alphatestref != 0 );
        break;

      case GL_AUX_BUFFERS:
        params[0] = (GLboolean) ( g->buffer.auxbuffers != 0 );
        break;

      case GL_BLEND:
        params[0] = (GLboolean) ( g->buffer.blend != 0 );
        break;

      case GL_BLEND_COLOR:
        params[0] = (GLboolean) ( g->buffer.blendcolor.r != 0.0f );
        params[1] = (GLboolean) ( g->buffer.blendcolor.g != 0.0f );
        params[2] = (GLboolean) ( g->buffer.blendcolor.b != 0.0f );
        params[3] = (GLboolean) ( g->buffer.blendcolor.a != 0.0f );
        break;

      case GL_BLEND_DST:
        params[0] = (GLboolean) ( g->buffer.blenddst != 0 );
        break;

      case GL_BLEND_EQUATION:
        params[0] = (GLboolean) ( g->buffer.blendequation != 0 );
        break;

      case GL_BLEND_SRC:
        params[0] = (GLboolean) ( g->buffer.blendsrc != 0 );
        break;

      case GL_CLIP_PLANE0:
        params[0] = (GLboolean) ( g->trans.clip[0] != 0 );
        break;

      case GL_CLIP_PLANE1:
        params[0] = (GLboolean) ( g->trans.clip[1] != 0 );
        break;

      case GL_CLIP_PLANE2:
        params[0] = (GLboolean) ( g->trans.clip[2] != 0 );
        break;

      case GL_CLIP_PLANE3:
        params[0] = (GLboolean) ( g->trans.clip[3] != 0 );
        break;

      case GL_CLIP_PLANE4:
        params[0] = (GLboolean) ( g->trans.clip[4] != 0 );
        break;

      case GL_CLIP_PLANE5:
        params[0] = (GLboolean) ( g->trans.clip[5] != 0 );
        break;

      case GL_COLOR_CLEAR_VALUE:
        params[0] = (GLboolean) ( g->buffer.colorclearvalue.r != 0.0f );
        params[1] = (GLboolean) ( g->buffer.colorclearvalue.g != 0.0f );
        params[2] = (GLboolean) ( g->buffer.colorclearvalue.b != 0.0f );
        params[3] = (GLboolean) ( g->buffer.colorclearvalue.a != 0.0f );
        break;

      case GL_COLOR_MATERIAL:
        params[0] = (GLboolean) ( GL_FALSE != 0 );
        break;

      case GL_COLOR_MATERIAL_FACE:
        params[0] = (GLboolean) ( g->lighting.colormaterialface != 0 );
        break;

      case GL_COLOR_MATERIAL_PARAMETER:
        params[0] = (GLboolean) ( g->lighting.colormaterialmode != 0 );
        break;

      case GL_COLOR_MATRIX:
        params[0] = (GLboolean) ( g->trans.color[g->trans.colordepth].m00 != (GLdefault) 0.0 );
        params[1] = (GLboolean) ( g->trans.color[g->trans.colordepth].m01 != (GLdefault) 0.0 );
        params[2] = (GLboolean) ( g->trans.color[g->trans.colordepth].m02 != (GLdefault) 0.0 );
        params[3] = (GLboolean) ( g->trans.color[g->trans.colordepth].m03 != (GLdefault) 0.0 );
        params[4] = (GLboolean) ( g->trans.color[g->trans.colordepth].m10 != (GLdefault) 0.0 );
        params[5] = (GLboolean) ( g->trans.color[g->trans.colordepth].m11 != (GLdefault) 0.0 );
        params[6] = (GLboolean) ( g->trans.color[g->trans.colordepth].m12 != (GLdefault) 0.0 );
        params[7] = (GLboolean) ( g->trans.color[g->trans.colordepth].m13 != (GLdefault) 0.0 );
        params[8] = (GLboolean) ( g->trans.color[g->trans.colordepth].m20 != (GLdefault) 0.0 );
        params[9] = (GLboolean) ( g->trans.color[g->trans.colordepth].m21 != (GLdefault) 0.0 );
        params[10] = (GLboolean) ( g->trans.color[g->trans.colordepth].m22 != (GLdefault) 0.0 );
        params[11] = (GLboolean) ( g->trans.color[g->trans.colordepth].m23 != (GLdefault) 0.0 );
        params[12] = (GLboolean) ( g->trans.color[g->trans.colordepth].m30 != (GLdefault) 0.0 );
        params[13] = (GLboolean) ( g->trans.color[g->trans.colordepth].m31 != (GLdefault) 0.0 );
        params[14] = (GLboolean) ( g->trans.color[g->trans.colordepth].m32 != (GLdefault) 0.0 );
        params[15] = (GLboolean) ( g->trans.color[g->trans.colordepth].m33 != (GLdefault) 0.0 );
        break;

      case GL_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.colordepth+1 != 0 );
        break;

      case GL_CULL_FACE:
        params[0] = (GLboolean) ( g->polygon.cullface != 0 );
        break;

      case GL_CULL_FACE_MODE:
        params[0] = (GLboolean) ( g->polygon.cullfacemode != 0 );
        break;

      case GL_CURRENT_COLOR:
        params[0] = (GLboolean) ( g->current.color.r != 0.0f );
        params[1] = (GLboolean) ( g->current.color.g != 0.0f );
        params[2] = (GLboolean) ( g->current.color.b != 0.0f );
        params[3] = (GLboolean) ( g->current.color.a != 0.0f );
        break;

      case GL_CURRENT_INDEX:
        params[0] = (GLboolean) ( g->current.index != 0.0f );
        break;

      case GL_CURRENT_NORMAL:
        params[0] = (GLboolean) ( g->current.normal.x != 0.0f );
        params[1] = (GLboolean) ( g->current.normal.y != 0.0f );
        params[2] = (GLboolean) ( g->current.normal.z != 0.0f );
        break;

      case GL_CURRENT_RASTER_COLOR:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_DISTANCE:
        params[0] = (GLboolean) ( g->current.rasterdistance != 0.0f );
        break;

      case GL_CURRENT_RASTER_INDEX:
        params[0] = (GLboolean) ( g->current.rasterindex != 0.0 );
        break;

      case GL_CURRENT_RASTER_POSITION:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_POSITION_VALID:
        params[0] = (GLboolean) ( g->current.rastervalid != 0 );
        break;

      case GL_CURRENT_RASTER_TEXTURE_COORDS:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_TEXTURE_COORDS:
        params[0] = (GLboolean) ( g->current.texcoord.s != 0.0f );
        params[1] = (GLboolean) ( g->current.texcoord.t != 0.0f );
        params[2] = (GLboolean) ( g->current.texcoord.p != 0.0f );
        params[3] = (GLboolean) ( g->current.texcoord.q != 0.0f );
        break;

      case GL_DEPTH_CLEAR_VALUE:
        params[0] = (GLboolean) ( g->buffer.depthclearvalue != 0.0 );
        break;

      case GL_DEPTH_FUNC:
        params[0] = (GLboolean) ( g->buffer.depthfunc != 0 );
        break;

      case GL_DEPTH_RANGE:
        params[0] = (GLboolean) ( g->viewport.n != 0.0 );
        params[1] = (GLboolean) ( g->viewport.f != 0.0 );
        break;

      case GL_DEPTH_TEST:
        params[0] = (GLboolean) ( g->buffer.depthtest != 0 );
        break;

      case GL_DEPTH_WRITEMASK:
        params[0] = (GLboolean) ( g->buffer.depthmask != 0 );
        break;

      case GL_DRAW_BUFFER:
        params[0] = (GLboolean) ( g->buffer.drawbuffer != 0 );
        break;

      case GL_EDGE_FLAG:
        params[0] = (GLboolean) ( g->current.edgeflag != 0 );
        break;

      case GL_FOG:
        params[0] = (GLboolean) ( g->fog.enable != 0 );
        break;

      case GL_FOG_COLOR:
        params[0] = (GLboolean) ( g->fog.color.r != 0.0f );
        params[1] = (GLboolean) ( g->fog.color.g != 0.0f );
        params[2] = (GLboolean) ( g->fog.color.b != 0.0f );
        params[3] = (GLboolean) ( g->fog.color.a != 0.0f );
        break;

      case GL_FOG_DENSITY:
        params[0] = (GLboolean) ( g->fog.density != 0.0f );
        break;

      case GL_FOG_END:
        params[0] = (GLboolean) ( g->fog.end != 0.0f );
        break;

      case GL_FOG_MODE:
        params[0] = (GLboolean) ( g->fog.mode != 0 );
        break;

      case GL_FOG_START:
        params[0] = (GLboolean) ( g->fog.start != 0.0f );
        break;

      case GL_FRONT_FACE:
        params[0] = (GLboolean) ( g->polygon.frontface != 0 );
        break;

      case GL_INDEX_CLEAR_VALUE:
        params[0] = (GLboolean) ( g->buffer.indexclearvalue != 0.0f );
        break;

      case GL_LIGHT0:
        params[0] = (GLboolean) ( g->lighting.light[0].enable != 0 );
        break;

      case GL_LIGHT1:
        params[0] = (GLboolean) ( g->lighting.light[1].enable != 0 );
        break;

      case GL_LIGHT2:
        params[0] = (GLboolean) ( g->lighting.light[2].enable != 0 );
        break;

      case GL_LIGHT3:
        params[0] = (GLboolean) ( g->lighting.light[3].enable != 0 );
        break;

      case GL_LIGHT4:
        params[0] = (GLboolean) ( g->lighting.light[4].enable != 0 );
        break;

      case GL_LIGHT5:
        params[0] = (GLboolean) ( g->lighting.light[5].enable != 0 );
        break;

      case GL_LIGHT6:
        params[0] = (GLboolean) ( g->lighting.light[6].enable != 0 );
        break;

      case GL_LIGHT7:
        params[0] = (GLboolean) ( g->lighting.light[7].enable != 0 );
        break;

      case GL_LIGHTING:
        params[0] = (GLboolean) ( g->lighting.lighting != 0 );
        break;

      case GL_LIGHT_MODEL_AMBIENT:
        params[0] = (GLboolean) ( g->lighting.lightmodelambient.r != 0.0f );
        params[1] = (GLboolean) ( g->lighting.lightmodelambient.g != 0.0f );
        params[2] = (GLboolean) ( g->lighting.lightmodelambient.b != 0.0f );
        params[3] = (GLboolean) ( g->lighting.lightmodelambient.a != 0.0f );
        break;

      case GL_LIGHT_MODEL_LOCAL_VIEWER:
        params[0] = (GLboolean) ( g->lighting.lightmodellocalviewer != 0 );
        break;

      case GL_LIGHT_MODEL_TWO_SIDE:
        params[0] = (GLboolean) ( g->lighting.lightmodeltwoside != 0 );
        break;

      case GL_LINE_SMOOTH:
        params[0] = (GLboolean) ( g->line.linesmooth != 0 );
        break;

      case GL_LINE_STIPPLE:
        params[0] = (GLboolean) ( g->line.linestipple != 0 );
        break;

      case GL_LINE_STIPPLE_PATTERN:
        params[0] = (GLboolean) ( g->line.pattern != 0 );
        break;

      case GL_LINE_STIPPLE_REPEAT:
        params[0] = (GLboolean) ( g->line.repeat != 0 );
        break;

      case GL_LINE_WIDTH:
        params[0] = (GLboolean) ( g->line.width != 0.0f );
        break;

      case GL_LINE_WIDTH_GRANULARITY:
        params[0] = (GLboolean) ( g->line.aliasedlinegranularity != 0.0f );
        break;

      case GL_LINE_WIDTH_RANGE:
        params[0] = (GLboolean) ( g->line.aliasedlinewidth_min != 0.0f );
        params[1] = (GLboolean) ( g->line.aliasedlinewidth_max != 0.0f );
        break;

      case GL_MATRIX_MODE:
        params[0] = (GLboolean) ( g->trans.mode != 0 );
        break;

      case GL_MAX_ATTRIB_STACK_DEPTH:
        params[0] = (GLboolean) ( 0 != 0 );
        break;

      case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
        params[0] = (GLboolean) ( 0 != 0 );
        break;

      case GL_MAX_CLIP_PLANES:
        params[0] = (GLboolean) ( g->trans.maxclipplanes != 0 );
        break;

      case GL_MAX_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.maxcolorstackdepth != 0 );
        break;

      case GL_MAX_EVAL_ORDER:
        params[0] = (GLboolean) ( g->eval.maxevalorder != 0 );
        break;

      case GL_MAX_LIGHTS:
        params[0] = (GLboolean) ( g->lighting.maxlights != 0 );
        break;

      case GL_MAX_MODELVIEW_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.maxmodelviewstackdepth != 0 );
        break;

      case GL_MAX_NAME_STACK_DEPTH:
        params[0] = (GLboolean) ( 0 != 0 );
        break;

      case GL_MAX_PIXEL_MAP_TABLE:
        params[0] = (GLboolean) ( 0 != 0 );
        break;

      case GL_MAX_PROJECTION_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.maxprojectionstackdepth != 0 );
        break;

      case GL_MAX_TEXTURE_SIZE:
        params[0] = (GLboolean) ( g->texture.maxtexturesize != 0 );
        break;

      case GL_MAX_TEXTURE_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.maxtexturestackdepth != 0 );
        break;

      case GL_MAX_VIEWPORT_DIMS:
        params[0] = (GLboolean) ( g->viewport.maxviewportdims_width != 0 );
        params[1] = (GLboolean) ( g->viewport.maxviewportdims_height != 0 );
        break;

      case GL_MODELVIEW_MATRIX:
        params[0] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m00 != (GLdefault) 0.0 );
        params[1] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m01 != (GLdefault) 0.0 );
        params[2] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m02 != (GLdefault) 0.0 );
        params[3] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m03 != (GLdefault) 0.0 );
        params[4] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m10 != (GLdefault) 0.0 );
        params[5] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m11 != (GLdefault) 0.0 );
        params[6] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m12 != (GLdefault) 0.0 );
        params[7] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m13 != (GLdefault) 0.0 );
        params[8] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m20 != (GLdefault) 0.0 );
        params[9] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m21 != (GLdefault) 0.0 );
        params[10] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m22 != (GLdefault) 0.0 );
        params[11] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m23 != (GLdefault) 0.0 );
        params[12] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m30 != (GLdefault) 0.0 );
        params[13] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m31 != (GLdefault) 0.0 );
        params[14] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m32 != (GLdefault) 0.0 );
        params[15] = (GLboolean) ( g->trans.modelview[g->trans.modelviewdepth].m33 != (GLdefault) 0.0 );
        break;

      case GL_MODELVIEW_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.modelviewdepth+1 != 0 );
        break;

      case GL_NORMALIZE:
        params[0] = (GLboolean) ( g->current.normalize != 0 );
        break;

      case GL_PACK_ALIGNMENT:
        params[0] = (GLboolean) ( g->pixel.packalignment != 0 );
        break;

      case GL_PACK_IMAGE_HEIGHT:
        params[0] = (GLboolean) ( g->pixel.packimageheight != 0 );
        break;

      case GL_PACK_LSB_FIRST:
        params[0] = (GLboolean) ( g->pixel.packlsbfirst != 0 );
        break;

      case GL_PACK_ROW_LENGTH:
        params[0] = (GLboolean) ( g->pixel.packrowlength != 0 );
        break;

      case GL_PACK_SKIP_IMAGES:
        params[0] = (GLboolean) ( g->pixel.packskipimages != 0 );
        break;

      case GL_PACK_SKIP_PIXELS:
        params[0] = (GLboolean) ( g->pixel.packskippixels != 0 );
        break;

      case GL_PACK_SKIP_ROWS:
        params[0] = (GLboolean) ( g->pixel.packskiprows != 0 );
        break;

      case GL_PACK_SWAP_BYTES:
        params[0] = (GLboolean) ( g->pixel.packswapbytes != 0 );
        break;

      case GL_POINT_SIZE:
        params[0] = (GLboolean) ( g->line.pointsize != 0.0f );
        break;

      case GL_POINT_SIZE_GRANULARITY:
        params[0] = (GLboolean) ( g->line.aliasedpointsizegranularity != 0.0f );
        break;

      case GL_POINT_SIZE_RANGE:
        params[0] = (GLboolean) ( g->line.aliasedpointsizerange_min != 0.0f );
        params[1] = (GLboolean) ( g->line.aliasedpointsizerange_max != 0.0f );
        break;

      case GL_POINT_SMOOTH:
        params[0] = (GLboolean) ( g->line.pointsmooth != 0 );
        break;

      case GL_POLYGON_MODE:
        params[0] = (GLboolean) ( g->polygon.frontmode != 0 );
        params[1] = (GLboolean) ( g->polygon.backmode != 0 );
        break;

      case GL_POLYGON_SMOOTH:
        params[0] = (GLboolean) ( g->polygon.polygonsmooth != 0 );
        break;

      case GL_POLYGON_STIPPLE:
        params[0] = (GLboolean) ( g->polygon.polygonstipple != 0 );
        break;

      case GL_PROJECTION_MATRIX:
        params[0] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m00 != (GLdefault) 0.0 );
        params[1] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m01 != (GLdefault) 0.0 );
        params[2] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m02 != (GLdefault) 0.0 );
        params[3] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m03 != (GLdefault) 0.0 );
        params[4] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m10 != (GLdefault) 0.0 );
        params[5] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m11 != (GLdefault) 0.0 );
        params[6] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m12 != (GLdefault) 0.0 );
        params[7] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m13 != (GLdefault) 0.0 );
        params[8] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m20 != (GLdefault) 0.0 );
        params[9] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m21 != (GLdefault) 0.0 );
        params[10] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m22 != (GLdefault) 0.0 );
        params[11] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m23 != (GLdefault) 0.0 );
        params[12] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m30 != (GLdefault) 0.0 );
        params[13] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m31 != (GLdefault) 0.0 );
        params[14] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m32 != (GLdefault) 0.0 );
        params[15] = (GLboolean) ( g->trans.projection[g->trans.projectiondepth].m33 != (GLdefault) 0.0 );
        break;

      case GL_PROJECTION_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.projectiondepth+1 != 0 );
        break;

      case GL_READ_BUFFER:
        params[0] = (GLboolean) ( g->buffer.readbuffer != 0 );
        break;

      case GL_RGBA_MODE:
        params[0] = (GLboolean) ( GL_TRUE != 0 );
        break;

      case GL_SHADE_MODEL:
        params[0] = (GLboolean) ( g->lighting.shademodel != 0 );
        break;

      case GL_STENCIL_BITS:
        params[0] = (GLboolean) ( g->buffer.stencilbits != 0 );
        break;

      case GL_STENCIL_CLEAR_VALUE:
        params[0] = (GLboolean) ( g->stencil.clearvalue != 0 );
        break;

      case GL_TEXTURE_1D:
        params[0] = (GLboolean) ( g->texture.enabled1d != 0 );
        break;

      case GL_TEXTURE_2D:
        params[0] = (GLboolean) ( g->texture.enabled2d != 0 );
        break;

      case GL_TEXTURE_3D:
        params[0] = (GLboolean) ( g->texture.enabled3d != 0 );
        break;

      case GL_TEXTURE_BINDING_1D:
        params[0] = (GLboolean) ( g->texture.currenttexture1dname != 0 );
        break;

      case GL_TEXTURE_BINDING_2D:
        params[0] = (GLboolean) ( g->texture.currenttexture2dname != 0 );
        break;

      case GL_TEXTURE_BINDING_3D:
        params[0] = (GLboolean) ( g->texture.currenttexture3dname != 0 );
        break;

      case GL_TEXTURE_GEN_Q:
        params[0] = (GLboolean) ( g->texture.texturegen.q != 0 );
        break;

      case GL_TEXTURE_GEN_R:
        params[0] = (GLboolean) ( g->texture.texturegen.p != 0 );
        break;

      case GL_TEXTURE_GEN_S:
        params[0] = (GLboolean) ( g->texture.texturegen.s != 0 );
        break;

      case GL_TEXTURE_GEN_T:
        params[0] = (GLboolean) ( g->texture.texturegen.t != 0 );
        break;

      case GL_TEXTURE_MATRIX:
        params[0] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m00 != (GLdefault) 0.0 );
        params[1] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m01 != (GLdefault) 0.0 );
        params[2] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m02 != (GLdefault) 0.0 );
        params[3] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m03 != (GLdefault) 0.0 );
        params[4] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m10 != (GLdefault) 0.0 );
        params[5] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m11 != (GLdefault) 0.0 );
        params[6] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m12 != (GLdefault) 0.0 );
        params[7] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m13 != (GLdefault) 0.0 );
        params[8] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m20 != (GLdefault) 0.0 );
        params[9] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m21 != (GLdefault) 0.0 );
        params[10] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m22 != (GLdefault) 0.0 );
        params[11] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m23 != (GLdefault) 0.0 );
        params[12] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m30 != (GLdefault) 0.0 );
        params[13] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m31 != (GLdefault) 0.0 );
        params[14] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m32 != (GLdefault) 0.0 );
        params[15] = (GLboolean) ( g->trans.texture[g->trans.texturedepth].m33 != (GLdefault) 0.0 );
        break;

      case GL_TEXTURE_STACK_DEPTH:
        params[0] = (GLboolean) ( g->trans.texturedepth+1 != 0 );
        break;

      case GL_UNPACK_ALIGNMENT:
        params[0] = (GLboolean) ( g->pixel.unpackalignment != 0 );
        break;

      case GL_UNPACK_IMAGE_HEIGHT:
        params[0] = (GLboolean) ( g->pixel.unpackimageheight != 0 );
        break;

      case GL_UNPACK_LSB_FIRST:
        params[0] = (GLboolean) ( g->pixel.unpacklsbfirst != 0 );
        break;

      case GL_UNPACK_ROW_LENGTH:
        params[0] = (GLboolean) ( g->pixel.unpackrowlength != 0 );
        break;

      case GL_UNPACK_SKIP_IMAGES:
        params[0] = (GLboolean) ( g->pixel.unpackskipimages != 0 );
        break;

      case GL_UNPACK_SKIP_PIXELS:
        params[0] = (GLboolean) ( g->pixel.unpackskippixels != 0 );
        break;

      case GL_UNPACK_SKIP_ROWS:
        params[0] = (GLboolean) ( g->pixel.unpackskiprows != 0 );
        break;

      case GL_UNPACK_SWAP_BYTES:
        params[0] = (GLboolean) ( g->pixel.unpackswapbytes != 0 );
        break;

      case GL_VIEWPORT:
        params[0] = (GLboolean) ( g->viewport.v_x != 0 );
        params[1] = (GLboolean) ( g->viewport.v_y != 0 );
        params[2] = (GLboolean) ( g->viewport.v_w != 0 );
        params[3] = (GLboolean) ( g->viewport.v_h != 0 );
        break;

      case GL_ZOOM_X:
        params[0] = (GLboolean) ( g->pixel.xzoom != 0.0f );
        break;

      case GL_ZOOM_Y:
        params[0] = (GLboolean) ( g->pixel.yzoom != 0.0f );
        break;

      default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glGet: Unknown enum: 0x%x", pname))
				return;
    }
}

void GLSTATE_DECL
__glstate_GetDoublev( GLenum pname, GLdouble *params )
{
    GLcontext   *g = GetCurrentContext( );

    if (g->current.beginend)
        if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
                      "glGet called in Begin/End"))
            return;
  
    switch ( pname ) {

      case GL_ACCUM_CLEAR_VALUE:
        params[0] = (GLdouble) g->buffer.accumclearvalue.r;
        params[1] = (GLdouble) g->buffer.accumclearvalue.g;
        params[2] = (GLdouble) g->buffer.accumclearvalue.b;
        params[3] = (GLdouble) g->buffer.accumclearvalue.a;
        break;

      case GL_ALPHA_TEST:
        params[0] = (GLdouble) g->buffer.alphatest;
        break;

      case GL_ALPHA_TEST_FUNC:
        params[0] = (GLdouble) g->buffer.alphatestfunc;
        break;

      case GL_ALPHA_TEST_REF:
        params[0] = (GLdouble) g->buffer.alphatestref;
        break;

      case GL_AUX_BUFFERS:
        params[0] = (GLdouble) g->buffer.auxbuffers;
        break;

      case GL_BLEND:
        params[0] = (GLdouble) g->buffer.blend;
        break;

      case GL_BLEND_COLOR:
        params[0] = (GLdouble) g->buffer.blendcolor.r;
        params[1] = (GLdouble) g->buffer.blendcolor.g;
        params[2] = (GLdouble) g->buffer.blendcolor.b;
        params[3] = (GLdouble) g->buffer.blendcolor.a;
        break;

      case GL_BLEND_DST:
        params[0] = (GLdouble) g->buffer.blenddst;
        break;

      case GL_BLEND_EQUATION:
        params[0] = (GLdouble) g->buffer.blendequation;
        break;

      case GL_BLEND_SRC:
        params[0] = (GLdouble) g->buffer.blendsrc;
        break;

      case GL_CLIP_PLANE0:
        params[0] = (GLdouble) g->trans.clip[0];
        break;

      case GL_CLIP_PLANE1:
        params[0] = (GLdouble) g->trans.clip[1];
        break;

      case GL_CLIP_PLANE2:
        params[0] = (GLdouble) g->trans.clip[2];
        break;

      case GL_CLIP_PLANE3:
        params[0] = (GLdouble) g->trans.clip[3];
        break;

      case GL_CLIP_PLANE4:
        params[0] = (GLdouble) g->trans.clip[4];
        break;

      case GL_CLIP_PLANE5:
        params[0] = (GLdouble) g->trans.clip[5];
        break;

      case GL_COLOR_CLEAR_VALUE:
        params[0] = (GLdouble) g->buffer.colorclearvalue.r;
        params[1] = (GLdouble) g->buffer.colorclearvalue.g;
        params[2] = (GLdouble) g->buffer.colorclearvalue.b;
        params[3] = (GLdouble) g->buffer.colorclearvalue.a;
        break;

      case GL_COLOR_MATERIAL:
        params[0] = (GLdouble) GL_FALSE;
        break;

      case GL_COLOR_MATERIAL_FACE:
        params[0] = (GLdouble) g->lighting.colormaterialface;
        break;

      case GL_COLOR_MATERIAL_PARAMETER:
        params[0] = (GLdouble) g->lighting.colormaterialmode;
        break;

      case GL_COLOR_MATRIX:
        params[0] = (GLdouble) g->trans.color[g->trans.colordepth].m00;
        params[1] = (GLdouble) g->trans.color[g->trans.colordepth].m01;
        params[2] = (GLdouble) g->trans.color[g->trans.colordepth].m02;
        params[3] = (GLdouble) g->trans.color[g->trans.colordepth].m03;
        params[4] = (GLdouble) g->trans.color[g->trans.colordepth].m10;
        params[5] = (GLdouble) g->trans.color[g->trans.colordepth].m11;
        params[6] = (GLdouble) g->trans.color[g->trans.colordepth].m12;
        params[7] = (GLdouble) g->trans.color[g->trans.colordepth].m13;
        params[8] = (GLdouble) g->trans.color[g->trans.colordepth].m20;
        params[9] = (GLdouble) g->trans.color[g->trans.colordepth].m21;
        params[10] = (GLdouble) g->trans.color[g->trans.colordepth].m22;
        params[11] = (GLdouble) g->trans.color[g->trans.colordepth].m23;
        params[12] = (GLdouble) g->trans.color[g->trans.colordepth].m30;
        params[13] = (GLdouble) g->trans.color[g->trans.colordepth].m31;
        params[14] = (GLdouble) g->trans.color[g->trans.colordepth].m32;
        params[15] = (GLdouble) g->trans.color[g->trans.colordepth].m33;
        break;

      case GL_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.colordepth+1;
        break;

      case GL_CULL_FACE:
        params[0] = (GLdouble) g->polygon.cullface;
        break;

      case GL_CULL_FACE_MODE:
        params[0] = (GLdouble) g->polygon.cullfacemode;
        break;

      case GL_CURRENT_COLOR:
        params[0] = (GLdouble) g->current.color.r;
        params[1] = (GLdouble) g->current.color.g;
        params[2] = (GLdouble) g->current.color.b;
        params[3] = (GLdouble) g->current.color.a;
        break;

      case GL_CURRENT_INDEX:
        params[0] = (GLdouble) g->current.index;
        break;

      case GL_CURRENT_NORMAL:
        params[0] = (GLdouble) g->current.normal.x;
        params[1] = (GLdouble) g->current.normal.y;
        params[2] = (GLdouble) g->current.normal.z;
        break;

      case GL_CURRENT_RASTER_COLOR:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_DISTANCE:
        params[0] = (GLdouble) g->current.rasterdistance;
        break;

      case GL_CURRENT_RASTER_INDEX:
        params[0] = g->current.rasterindex;
        break;

      case GL_CURRENT_RASTER_POSITION:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_POSITION_VALID:
        params[0] = (GLdouble) g->current.rastervalid;
        break;

      case GL_CURRENT_RASTER_TEXTURE_COORDS:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_TEXTURE_COORDS:
        params[0] = (GLdouble) g->current.texcoord.s;
        params[1] = (GLdouble) g->current.texcoord.t;
        params[2] = (GLdouble) g->current.texcoord.p;
        params[3] = (GLdouble) g->current.texcoord.q;
        break;

      case GL_DEPTH_CLEAR_VALUE:
        params[0] = g->buffer.depthclearvalue;
        break;

      case GL_DEPTH_FUNC:
        params[0] = (GLdouble) g->buffer.depthfunc;
        break;

      case GL_DEPTH_RANGE:
        params[0] = g->viewport.n;
        params[1] = g->viewport.f;
        break;

      case GL_DEPTH_TEST:
        params[0] = (GLdouble) g->buffer.depthtest;
        break;

      case GL_DEPTH_WRITEMASK:
        params[0] = (GLdouble) g->buffer.depthmask;
        break;

      case GL_DRAW_BUFFER:
        params[0] = (GLdouble) g->buffer.drawbuffer;
        break;

      case GL_EDGE_FLAG:
        params[0] = (GLdouble) g->current.edgeflag;
        break;

      case GL_FOG:
        params[0] = (GLdouble) g->fog.enable;
        break;

      case GL_FOG_COLOR:
        params[0] = (GLdouble) g->fog.color.r;
        params[1] = (GLdouble) g->fog.color.g;
        params[2] = (GLdouble) g->fog.color.b;
        params[3] = (GLdouble) g->fog.color.a;
        break;

      case GL_FOG_DENSITY:
        params[0] = (GLdouble) g->fog.density;
        break;

      case GL_FOG_END:
        params[0] = (GLdouble) g->fog.end;
        break;

      case GL_FOG_MODE:
        params[0] = (GLdouble) g->fog.mode;
        break;

      case GL_FOG_START:
        params[0] = (GLdouble) g->fog.start;
        break;

      case GL_FRONT_FACE:
        params[0] = (GLdouble) g->polygon.frontface;
        break;

      case GL_INDEX_CLEAR_VALUE:
        params[0] = (GLdouble) g->buffer.indexclearvalue;
        break;

      case GL_LIGHT0:
        params[0] = (GLdouble) g->lighting.light[0].enable;
        break;

      case GL_LIGHT1:
        params[0] = (GLdouble) g->lighting.light[1].enable;
        break;

      case GL_LIGHT2:
        params[0] = (GLdouble) g->lighting.light[2].enable;
        break;

      case GL_LIGHT3:
        params[0] = (GLdouble) g->lighting.light[3].enable;
        break;

      case GL_LIGHT4:
        params[0] = (GLdouble) g->lighting.light[4].enable;
        break;

      case GL_LIGHT5:
        params[0] = (GLdouble) g->lighting.light[5].enable;
        break;

      case GL_LIGHT6:
        params[0] = (GLdouble) g->lighting.light[6].enable;
        break;

      case GL_LIGHT7:
        params[0] = (GLdouble) g->lighting.light[7].enable;
        break;

      case GL_LIGHTING:
        params[0] = (GLdouble) g->lighting.lighting;
        break;

      case GL_LIGHT_MODEL_AMBIENT:
        params[0] = (GLdouble) g->lighting.lightmodelambient.r;
        params[1] = (GLdouble) g->lighting.lightmodelambient.g;
        params[2] = (GLdouble) g->lighting.lightmodelambient.b;
        params[3] = (GLdouble) g->lighting.lightmodelambient.a;
        break;

      case GL_LIGHT_MODEL_LOCAL_VIEWER:
        params[0] = (GLdouble) g->lighting.lightmodellocalviewer;
        break;

      case GL_LIGHT_MODEL_TWO_SIDE:
        params[0] = (GLdouble) g->lighting.lightmodeltwoside;
        break;

      case GL_LINE_SMOOTH:
        params[0] = (GLdouble) g->line.linesmooth;
        break;

      case GL_LINE_STIPPLE:
        params[0] = (GLdouble) g->line.linestipple;
        break;

      case GL_LINE_STIPPLE_PATTERN:
        params[0] = (GLdouble) g->line.pattern;
        break;

      case GL_LINE_STIPPLE_REPEAT:
        params[0] = (GLdouble) g->line.repeat;
        break;

      case GL_LINE_WIDTH:
        params[0] = (GLdouble) g->line.width;
        break;

      case GL_LINE_WIDTH_GRANULARITY:
        params[0] = (GLdouble) g->line.aliasedlinegranularity;
        break;

      case GL_LINE_WIDTH_RANGE:
        params[0] = (GLdouble) g->line.aliasedlinewidth_min;
        params[1] = (GLdouble) g->line.aliasedlinewidth_max;
        break;

      case GL_MATRIX_MODE:
        params[0] = (GLdouble) g->trans.mode;
        break;

      case GL_MAX_ATTRIB_STACK_DEPTH:
        params[0] = (GLdouble) 0;
        break;

      case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
        params[0] = (GLdouble) 0;
        break;

      case GL_MAX_CLIP_PLANES:
        params[0] = (GLdouble) g->trans.maxclipplanes;
        break;

      case GL_MAX_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.maxcolorstackdepth;
        break;

      case GL_MAX_EVAL_ORDER:
        params[0] = (GLdouble) g->eval.maxevalorder;
        break;

      case GL_MAX_LIGHTS:
        params[0] = (GLdouble) g->lighting.maxlights;
        break;

      case GL_MAX_MODELVIEW_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.maxmodelviewstackdepth;
        break;

      case GL_MAX_NAME_STACK_DEPTH:
        params[0] = (GLdouble) 0;
        break;

      case GL_MAX_PIXEL_MAP_TABLE:
        params[0] = (GLdouble) 0;
        break;

      case GL_MAX_PROJECTION_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.maxprojectionstackdepth;
        break;

      case GL_MAX_TEXTURE_SIZE:
        params[0] = (GLdouble) g->texture.maxtexturesize;
        break;

      case GL_MAX_TEXTURE_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.maxtexturestackdepth;
        break;

      case GL_MAX_VIEWPORT_DIMS:
        params[0] = (GLdouble) g->viewport.maxviewportdims_width;
        params[1] = (GLdouble) g->viewport.maxviewportdims_height;
        break;

      case GL_MODELVIEW_MATRIX:
        params[0] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m00;
        params[1] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m01;
        params[2] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m02;
        params[3] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m03;
        params[4] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m10;
        params[5] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m11;
        params[6] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m12;
        params[7] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m13;
        params[8] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m20;
        params[9] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m21;
        params[10] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m22;
        params[11] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m23;
        params[12] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m30;
        params[13] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m31;
        params[14] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m32;
        params[15] = (GLdouble) g->trans.modelview[g->trans.modelviewdepth].m33;
        break;

      case GL_MODELVIEW_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.modelviewdepth+1;
        break;

      case GL_NORMALIZE:
        params[0] = (GLdouble) g->current.normalize;
        break;

      case GL_PACK_ALIGNMENT:
        params[0] = (GLdouble) g->pixel.packalignment;
        break;

      case GL_PACK_IMAGE_HEIGHT:
        params[0] = (GLdouble) g->pixel.packimageheight;
        break;

      case GL_PACK_LSB_FIRST:
        params[0] = (GLdouble) g->pixel.packlsbfirst;
        break;

      case GL_PACK_ROW_LENGTH:
        params[0] = (GLdouble) g->pixel.packrowlength;
        break;

      case GL_PACK_SKIP_IMAGES:
        params[0] = (GLdouble) g->pixel.packskipimages;
        break;

      case GL_PACK_SKIP_PIXELS:
        params[0] = (GLdouble) g->pixel.packskippixels;
        break;

      case GL_PACK_SKIP_ROWS:
        params[0] = (GLdouble) g->pixel.packskiprows;
        break;

      case GL_PACK_SWAP_BYTES:
        params[0] = (GLdouble) g->pixel.packswapbytes;
        break;

      case GL_POINT_SIZE:
        params[0] = (GLdouble) g->line.pointsize;
        break;

      case GL_POINT_SIZE_GRANULARITY:
        params[0] = (GLdouble) g->line.aliasedpointsizegranularity;
        break;

      case GL_POINT_SIZE_RANGE:
        params[0] = (GLdouble) g->line.aliasedpointsizerange_min;
        params[1] = (GLdouble) g->line.aliasedpointsizerange_max;
        break;

      case GL_POINT_SMOOTH:
        params[0] = (GLdouble) g->line.pointsmooth;
        break;

      case GL_POLYGON_MODE:
        params[0] = (GLdouble) g->polygon.frontmode;
        params[1] = (GLdouble) g->polygon.backmode;
        break;

      case GL_POLYGON_SMOOTH:
        params[0] = (GLdouble) g->polygon.polygonsmooth;
        break;

      case GL_POLYGON_STIPPLE:
        params[0] = (GLdouble) g->polygon.polygonstipple;
        break;

      case GL_PROJECTION_MATRIX:
        params[0] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m00;
        params[1] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m01;
        params[2] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m02;
        params[3] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m03;
        params[4] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m10;
        params[5] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m11;
        params[6] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m12;
        params[7] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m13;
        params[8] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m20;
        params[9] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m21;
        params[10] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m22;
        params[11] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m23;
        params[12] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m30;
        params[13] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m31;
        params[14] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m32;
        params[15] = (GLdouble) g->trans.projection[g->trans.projectiondepth].m33;
        break;

      case GL_PROJECTION_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.projectiondepth+1;
        break;

      case GL_READ_BUFFER:
        params[0] = (GLdouble) g->buffer.readbuffer;
        break;

      case GL_RGBA_MODE:
        params[0] = (GLdouble) GL_TRUE;
        break;

      case GL_SHADE_MODEL:
        params[0] = (GLdouble) g->lighting.shademodel;
        break;

      case GL_STENCIL_BITS:
        params[0] = (GLdouble) g->buffer.stencilbits;
        break;

      case GL_STENCIL_CLEAR_VALUE:
        params[0] = (GLdouble) g->stencil.clearvalue;
        break;

      case GL_TEXTURE_1D:
        params[0] = (GLdouble) g->texture.enabled1d;
        break;

      case GL_TEXTURE_2D:
        params[0] = (GLdouble) g->texture.enabled2d;
        break;

      case GL_TEXTURE_3D:
        params[0] = (GLdouble) g->texture.enabled3d;
        break;

      case GL_TEXTURE_BINDING_1D:
        params[0] = (GLdouble) g->texture.currenttexture1dname;
        break;

      case GL_TEXTURE_BINDING_2D:
        params[0] = (GLdouble) g->texture.currenttexture2dname;
        break;

      case GL_TEXTURE_BINDING_3D:
        params[0] = (GLdouble) g->texture.currenttexture3dname;
        break;

      case GL_TEXTURE_GEN_Q:
        params[0] = (GLdouble) g->texture.texturegen.q;
        break;

      case GL_TEXTURE_GEN_R:
        params[0] = (GLdouble) g->texture.texturegen.p;
        break;

      case GL_TEXTURE_GEN_S:
        params[0] = (GLdouble) g->texture.texturegen.s;
        break;

      case GL_TEXTURE_GEN_T:
        params[0] = (GLdouble) g->texture.texturegen.t;
        break;

      case GL_TEXTURE_MATRIX:
        params[0] = (GLdouble) g->trans.texture[g->trans.texturedepth].m00;
        params[1] = (GLdouble) g->trans.texture[g->trans.texturedepth].m01;
        params[2] = (GLdouble) g->trans.texture[g->trans.texturedepth].m02;
        params[3] = (GLdouble) g->trans.texture[g->trans.texturedepth].m03;
        params[4] = (GLdouble) g->trans.texture[g->trans.texturedepth].m10;
        params[5] = (GLdouble) g->trans.texture[g->trans.texturedepth].m11;
        params[6] = (GLdouble) g->trans.texture[g->trans.texturedepth].m12;
        params[7] = (GLdouble) g->trans.texture[g->trans.texturedepth].m13;
        params[8] = (GLdouble) g->trans.texture[g->trans.texturedepth].m20;
        params[9] = (GLdouble) g->trans.texture[g->trans.texturedepth].m21;
        params[10] = (GLdouble) g->trans.texture[g->trans.texturedepth].m22;
        params[11] = (GLdouble) g->trans.texture[g->trans.texturedepth].m23;
        params[12] = (GLdouble) g->trans.texture[g->trans.texturedepth].m30;
        params[13] = (GLdouble) g->trans.texture[g->trans.texturedepth].m31;
        params[14] = (GLdouble) g->trans.texture[g->trans.texturedepth].m32;
        params[15] = (GLdouble) g->trans.texture[g->trans.texturedepth].m33;
        break;

      case GL_TEXTURE_STACK_DEPTH:
        params[0] = (GLdouble) g->trans.texturedepth+1;
        break;

      case GL_UNPACK_ALIGNMENT:
        params[0] = (GLdouble) g->pixel.unpackalignment;
        break;

      case GL_UNPACK_IMAGE_HEIGHT:
        params[0] = (GLdouble) g->pixel.unpackimageheight;
        break;

      case GL_UNPACK_LSB_FIRST:
        params[0] = (GLdouble) g->pixel.unpacklsbfirst;
        break;

      case GL_UNPACK_ROW_LENGTH:
        params[0] = (GLdouble) g->pixel.unpackrowlength;
        break;

      case GL_UNPACK_SKIP_IMAGES:
        params[0] = (GLdouble) g->pixel.unpackskipimages;
        break;

      case GL_UNPACK_SKIP_PIXELS:
        params[0] = (GLdouble) g->pixel.unpackskippixels;
        break;

      case GL_UNPACK_SKIP_ROWS:
        params[0] = (GLdouble) g->pixel.unpackskiprows;
        break;

      case GL_UNPACK_SWAP_BYTES:
        params[0] = (GLdouble) g->pixel.unpackswapbytes;
        break;

      case GL_VIEWPORT:
        params[0] = (GLdouble) g->viewport.v_x;
        params[1] = (GLdouble) g->viewport.v_y;
        params[2] = (GLdouble) g->viewport.v_w;
        params[3] = (GLdouble) g->viewport.v_h;
        break;

      case GL_ZOOM_X:
        params[0] = (GLdouble) g->pixel.xzoom;
        break;

      case GL_ZOOM_Y:
        params[0] = (GLdouble) g->pixel.yzoom;
        break;

      default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glGet: Unknown enum: 0x%x", pname))
				return;
    }
}

void GLSTATE_DECL
__glstate_GetFloatv( GLenum pname, GLfloat *params )
{
    GLcontext   *g = GetCurrentContext( );

    if (g->current.beginend)
        if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
                      "glGet called in Begin/End"))
            return;
  
    switch ( pname ) {

      case GL_ACCUM_CLEAR_VALUE:
        params[0] = g->buffer.accumclearvalue.r;
        params[1] = g->buffer.accumclearvalue.g;
        params[2] = g->buffer.accumclearvalue.b;
        params[3] = g->buffer.accumclearvalue.a;
        break;

      case GL_ALPHA_TEST:
        params[0] = (GLfloat) g->buffer.alphatest;
        break;

      case GL_ALPHA_TEST_FUNC:
        params[0] = (GLfloat) g->buffer.alphatestfunc;
        break;

      case GL_ALPHA_TEST_REF:
        params[0] = (GLfloat) g->buffer.alphatestref;
        break;

      case GL_AUX_BUFFERS:
        params[0] = (GLfloat) g->buffer.auxbuffers;
        break;

      case GL_BLEND:
        params[0] = (GLfloat) g->buffer.blend;
        break;

      case GL_BLEND_COLOR:
        params[0] = g->buffer.blendcolor.r;
        params[1] = g->buffer.blendcolor.g;
        params[2] = g->buffer.blendcolor.b;
        params[3] = g->buffer.blendcolor.a;
        break;

      case GL_BLEND_DST:
        params[0] = (GLfloat) g->buffer.blenddst;
        break;

      case GL_BLEND_EQUATION:
        params[0] = (GLfloat) g->buffer.blendequation;
        break;

      case GL_BLEND_SRC:
        params[0] = (GLfloat) g->buffer.blendsrc;
        break;

      case GL_CLIP_PLANE0:
        params[0] = (GLfloat) g->trans.clip[0];
        break;

      case GL_CLIP_PLANE1:
        params[0] = (GLfloat) g->trans.clip[1];
        break;

      case GL_CLIP_PLANE2:
        params[0] = (GLfloat) g->trans.clip[2];
        break;

      case GL_CLIP_PLANE3:
        params[0] = (GLfloat) g->trans.clip[3];
        break;

      case GL_CLIP_PLANE4:
        params[0] = (GLfloat) g->trans.clip[4];
        break;

      case GL_CLIP_PLANE5:
        params[0] = (GLfloat) g->trans.clip[5];
        break;

      case GL_COLOR_CLEAR_VALUE:
        params[0] = g->buffer.colorclearvalue.r;
        params[1] = g->buffer.colorclearvalue.g;
        params[2] = g->buffer.colorclearvalue.b;
        params[3] = g->buffer.colorclearvalue.a;
        break;

      case GL_COLOR_MATERIAL:
        params[0] = (GLfloat) GL_FALSE;
        break;

      case GL_COLOR_MATERIAL_FACE:
        params[0] = (GLfloat) g->lighting.colormaterialface;
        break;

      case GL_COLOR_MATERIAL_PARAMETER:
        params[0] = (GLfloat) g->lighting.colormaterialmode;
        break;

      case GL_COLOR_MATRIX:
        params[0] = (GLfloat) g->trans.color[g->trans.colordepth].m00;
        params[1] = (GLfloat) g->trans.color[g->trans.colordepth].m01;
        params[2] = (GLfloat) g->trans.color[g->trans.colordepth].m02;
        params[3] = (GLfloat) g->trans.color[g->trans.colordepth].m03;
        params[4] = (GLfloat) g->trans.color[g->trans.colordepth].m10;
        params[5] = (GLfloat) g->trans.color[g->trans.colordepth].m11;
        params[6] = (GLfloat) g->trans.color[g->trans.colordepth].m12;
        params[7] = (GLfloat) g->trans.color[g->trans.colordepth].m13;
        params[8] = (GLfloat) g->trans.color[g->trans.colordepth].m20;
        params[9] = (GLfloat) g->trans.color[g->trans.colordepth].m21;
        params[10] = (GLfloat) g->trans.color[g->trans.colordepth].m22;
        params[11] = (GLfloat) g->trans.color[g->trans.colordepth].m23;
        params[12] = (GLfloat) g->trans.color[g->trans.colordepth].m30;
        params[13] = (GLfloat) g->trans.color[g->trans.colordepth].m31;
        params[14] = (GLfloat) g->trans.color[g->trans.colordepth].m32;
        params[15] = (GLfloat) g->trans.color[g->trans.colordepth].m33;
        break;

      case GL_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.colordepth+1;
        break;

      case GL_CULL_FACE:
        params[0] = (GLfloat) g->polygon.cullface;
        break;

      case GL_CULL_FACE_MODE:
        params[0] = (GLfloat) g->polygon.cullfacemode;
        break;

      case GL_CURRENT_COLOR:
        params[0] = g->current.color.r;
        params[1] = g->current.color.g;
        params[2] = g->current.color.b;
        params[3] = g->current.color.a;
        break;

      case GL_CURRENT_INDEX:
        params[0] = g->current.index;
        break;

      case GL_CURRENT_NORMAL:
        params[0] = g->current.normal.x;
        params[1] = g->current.normal.y;
        params[2] = g->current.normal.z;
        break;

      case GL_CURRENT_RASTER_COLOR:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_DISTANCE:
        params[0] = g->current.rasterdistance;
        break;

      case GL_CURRENT_RASTER_INDEX:
        params[0] = (GLfloat) g->current.rasterindex;
        break;

      case GL_CURRENT_RASTER_POSITION:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_POSITION_VALID:
        params[0] = (GLfloat) g->current.rastervalid;
        break;

      case GL_CURRENT_RASTER_TEXTURE_COORDS:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_TEXTURE_COORDS:
        params[0] = g->current.texcoord.s;
        params[1] = g->current.texcoord.t;
        params[2] = g->current.texcoord.p;
        params[3] = g->current.texcoord.q;
        break;

      case GL_DEPTH_CLEAR_VALUE:
        params[0] = (GLfloat) g->buffer.depthclearvalue;
        break;

      case GL_DEPTH_FUNC:
        params[0] = (GLfloat) g->buffer.depthfunc;
        break;

      case GL_DEPTH_RANGE:
        params[0] = (GLfloat) g->viewport.n;
        params[1] = (GLfloat) g->viewport.f;
        break;

      case GL_DEPTH_TEST:
        params[0] = (GLfloat) g->buffer.depthtest;
        break;

      case GL_DEPTH_WRITEMASK:
        params[0] = (GLfloat) g->buffer.depthmask;
        break;

      case GL_DRAW_BUFFER:
        params[0] = (GLfloat) g->buffer.drawbuffer;
        break;

      case GL_EDGE_FLAG:
        params[0] = (GLfloat) g->current.edgeflag;
        break;

      case GL_FOG:
        params[0] = (GLfloat) g->fog.enable;
        break;

      case GL_FOG_COLOR:
        params[0] = g->fog.color.r;
        params[1] = g->fog.color.g;
        params[2] = g->fog.color.b;
        params[3] = g->fog.color.a;
        break;

      case GL_FOG_DENSITY:
        params[0] = g->fog.density;
        break;

      case GL_FOG_END:
        params[0] = g->fog.end;
        break;

      case GL_FOG_MODE:
        params[0] = (GLfloat) g->fog.mode;
        break;

      case GL_FOG_START:
        params[0] = g->fog.start;
        break;

      case GL_FRONT_FACE:
        params[0] = (GLfloat) g->polygon.frontface;
        break;

      case GL_INDEX_CLEAR_VALUE:
        params[0] = g->buffer.indexclearvalue;
        break;

      case GL_LIGHT0:
        params[0] = (GLfloat) g->lighting.light[0].enable;
        break;

      case GL_LIGHT1:
        params[0] = (GLfloat) g->lighting.light[1].enable;
        break;

      case GL_LIGHT2:
        params[0] = (GLfloat) g->lighting.light[2].enable;
        break;

      case GL_LIGHT3:
        params[0] = (GLfloat) g->lighting.light[3].enable;
        break;

      case GL_LIGHT4:
        params[0] = (GLfloat) g->lighting.light[4].enable;
        break;

      case GL_LIGHT5:
        params[0] = (GLfloat) g->lighting.light[5].enable;
        break;

      case GL_LIGHT6:
        params[0] = (GLfloat) g->lighting.light[6].enable;
        break;

      case GL_LIGHT7:
        params[0] = (GLfloat) g->lighting.light[7].enable;
        break;

      case GL_LIGHTING:
        params[0] = (GLfloat) g->lighting.lighting;
        break;

      case GL_LIGHT_MODEL_AMBIENT:
        params[0] = g->lighting.lightmodelambient.r;
        params[1] = g->lighting.lightmodelambient.g;
        params[2] = g->lighting.lightmodelambient.b;
        params[3] = g->lighting.lightmodelambient.a;
        break;

      case GL_LIGHT_MODEL_LOCAL_VIEWER:
        params[0] = (GLfloat) g->lighting.lightmodellocalviewer;
        break;

      case GL_LIGHT_MODEL_TWO_SIDE:
        params[0] = (GLfloat) g->lighting.lightmodeltwoside;
        break;

      case GL_LINE_SMOOTH:
        params[0] = (GLfloat) g->line.linesmooth;
        break;

      case GL_LINE_STIPPLE:
        params[0] = (GLfloat) g->line.linestipple;
        break;

      case GL_LINE_STIPPLE_PATTERN:
        params[0] = (GLfloat) g->line.pattern;
        break;

      case GL_LINE_STIPPLE_REPEAT:
        params[0] = (GLfloat) g->line.repeat;
        break;

      case GL_LINE_WIDTH:
        params[0] = g->line.width;
        break;

      case GL_LINE_WIDTH_GRANULARITY:
        params[0] = g->line.aliasedlinegranularity;
        break;

      case GL_LINE_WIDTH_RANGE:
        params[0] = g->line.aliasedlinewidth_min;
        params[1] = g->line.aliasedlinewidth_max;
        break;

      case GL_MATRIX_MODE:
        params[0] = (GLfloat) g->trans.mode;
        break;

      case GL_MAX_ATTRIB_STACK_DEPTH:
        params[0] = (GLfloat) 0;
        break;

      case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
        params[0] = (GLfloat) 0;
        break;

      case GL_MAX_CLIP_PLANES:
        params[0] = (GLfloat) g->trans.maxclipplanes;
        break;

      case GL_MAX_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.maxcolorstackdepth;
        break;

      case GL_MAX_EVAL_ORDER:
        params[0] = (GLfloat) g->eval.maxevalorder;
        break;

      case GL_MAX_LIGHTS:
        params[0] = (GLfloat) g->lighting.maxlights;
        break;

      case GL_MAX_MODELVIEW_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.maxmodelviewstackdepth;
        break;

      case GL_MAX_NAME_STACK_DEPTH:
        params[0] = (GLfloat) 0;
        break;

      case GL_MAX_PIXEL_MAP_TABLE:
        params[0] = (GLfloat) 0;
        break;

      case GL_MAX_PROJECTION_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.maxprojectionstackdepth;
        break;

      case GL_MAX_TEXTURE_SIZE:
        params[0] = (GLfloat) g->texture.maxtexturesize;
        break;

      case GL_MAX_TEXTURE_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.maxtexturestackdepth;
        break;

      case GL_MAX_VIEWPORT_DIMS:
        params[0] = (GLfloat) g->viewport.maxviewportdims_width;
        params[1] = (GLfloat) g->viewport.maxviewportdims_height;
        break;

      case GL_MODELVIEW_MATRIX:
        params[0] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m00;
        params[1] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m01;
        params[2] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m02;
        params[3] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m03;
        params[4] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m10;
        params[5] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m11;
        params[6] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m12;
        params[7] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m13;
        params[8] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m20;
        params[9] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m21;
        params[10] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m22;
        params[11] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m23;
        params[12] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m30;
        params[13] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m31;
        params[14] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m32;
        params[15] = (GLfloat) g->trans.modelview[g->trans.modelviewdepth].m33;
        break;

      case GL_MODELVIEW_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.modelviewdepth+1;
        break;

      case GL_NORMALIZE:
        params[0] = (GLfloat) g->current.normalize;
        break;

      case GL_PACK_ALIGNMENT:
        params[0] = (GLfloat) g->pixel.packalignment;
        break;

      case GL_PACK_IMAGE_HEIGHT:
        params[0] = (GLfloat) g->pixel.packimageheight;
        break;

      case GL_PACK_LSB_FIRST:
        params[0] = (GLfloat) g->pixel.packlsbfirst;
        break;

      case GL_PACK_ROW_LENGTH:
        params[0] = (GLfloat) g->pixel.packrowlength;
        break;

      case GL_PACK_SKIP_IMAGES:
        params[0] = (GLfloat) g->pixel.packskipimages;
        break;

      case GL_PACK_SKIP_PIXELS:
        params[0] = (GLfloat) g->pixel.packskippixels;
        break;

      case GL_PACK_SKIP_ROWS:
        params[0] = (GLfloat) g->pixel.packskiprows;
        break;

      case GL_PACK_SWAP_BYTES:
        params[0] = (GLfloat) g->pixel.packswapbytes;
        break;

      case GL_POINT_SIZE:
        params[0] = g->line.pointsize;
        break;

      case GL_POINT_SIZE_GRANULARITY:
        params[0] = g->line.aliasedpointsizegranularity;
        break;

      case GL_POINT_SIZE_RANGE:
        params[0] = g->line.aliasedpointsizerange_min;
        params[1] = g->line.aliasedpointsizerange_max;
        break;

      case GL_POINT_SMOOTH:
        params[0] = (GLfloat) g->line.pointsmooth;
        break;

      case GL_POLYGON_MODE:
        params[0] = (GLfloat) g->polygon.frontmode;
        params[1] = (GLfloat) g->polygon.backmode;
        break;

      case GL_POLYGON_SMOOTH:
        params[0] = (GLfloat) g->polygon.polygonsmooth;
        break;

      case GL_POLYGON_STIPPLE:
        params[0] = (GLfloat) g->polygon.polygonstipple;
        break;

      case GL_PROJECTION_MATRIX:
        params[0] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m00;
        params[1] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m01;
        params[2] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m02;
        params[3] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m03;
        params[4] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m10;
        params[5] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m11;
        params[6] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m12;
        params[7] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m13;
        params[8] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m20;
        params[9] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m21;
        params[10] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m22;
        params[11] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m23;
        params[12] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m30;
        params[13] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m31;
        params[14] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m32;
        params[15] = (GLfloat) g->trans.projection[g->trans.projectiondepth].m33;
        break;

      case GL_PROJECTION_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.projectiondepth+1;
        break;

      case GL_READ_BUFFER:
        params[0] = (GLfloat) g->buffer.readbuffer;
        break;

      case GL_RGBA_MODE:
        params[0] = (GLfloat) GL_TRUE;
        break;

      case GL_SHADE_MODEL:
        params[0] = (GLfloat) g->lighting.shademodel;
        break;

      case GL_STENCIL_BITS:
        params[0] = (GLfloat) g->buffer.stencilbits;
        break;

      case GL_STENCIL_CLEAR_VALUE:
        params[0] = (GLfloat) g->stencil.clearvalue;
        break;

      case GL_TEXTURE_1D:
        params[0] = (GLfloat) g->texture.enabled1d;
        break;

      case GL_TEXTURE_2D:
        params[0] = (GLfloat) g->texture.enabled2d;
        break;

      case GL_TEXTURE_3D:
        params[0] = (GLfloat) g->texture.enabled3d;
        break;

      case GL_TEXTURE_BINDING_1D:
        params[0] = (GLfloat) g->texture.currenttexture1dname;
        break;

      case GL_TEXTURE_BINDING_2D:
        params[0] = (GLfloat) g->texture.currenttexture2dname;
        break;

      case GL_TEXTURE_BINDING_3D:
        params[0] = (GLfloat) g->texture.currenttexture3dname;
        break;

      case GL_TEXTURE_GEN_Q:
        params[0] = (GLfloat) g->texture.texturegen.q;
        break;

      case GL_TEXTURE_GEN_R:
        params[0] = (GLfloat) g->texture.texturegen.p;
        break;

      case GL_TEXTURE_GEN_S:
        params[0] = (GLfloat) g->texture.texturegen.s;
        break;

      case GL_TEXTURE_GEN_T:
        params[0] = (GLfloat) g->texture.texturegen.t;
        break;

      case GL_TEXTURE_MATRIX:
        params[0] = (GLfloat) g->trans.texture[g->trans.texturedepth].m00;
        params[1] = (GLfloat) g->trans.texture[g->trans.texturedepth].m01;
        params[2] = (GLfloat) g->trans.texture[g->trans.texturedepth].m02;
        params[3] = (GLfloat) g->trans.texture[g->trans.texturedepth].m03;
        params[4] = (GLfloat) g->trans.texture[g->trans.texturedepth].m10;
        params[5] = (GLfloat) g->trans.texture[g->trans.texturedepth].m11;
        params[6] = (GLfloat) g->trans.texture[g->trans.texturedepth].m12;
        params[7] = (GLfloat) g->trans.texture[g->trans.texturedepth].m13;
        params[8] = (GLfloat) g->trans.texture[g->trans.texturedepth].m20;
        params[9] = (GLfloat) g->trans.texture[g->trans.texturedepth].m21;
        params[10] = (GLfloat) g->trans.texture[g->trans.texturedepth].m22;
        params[11] = (GLfloat) g->trans.texture[g->trans.texturedepth].m23;
        params[12] = (GLfloat) g->trans.texture[g->trans.texturedepth].m30;
        params[13] = (GLfloat) g->trans.texture[g->trans.texturedepth].m31;
        params[14] = (GLfloat) g->trans.texture[g->trans.texturedepth].m32;
        params[15] = (GLfloat) g->trans.texture[g->trans.texturedepth].m33;
        break;

      case GL_TEXTURE_STACK_DEPTH:
        params[0] = (GLfloat) g->trans.texturedepth+1;
        break;

      case GL_UNPACK_ALIGNMENT:
        params[0] = (GLfloat) g->pixel.unpackalignment;
        break;

      case GL_UNPACK_IMAGE_HEIGHT:
        params[0] = (GLfloat) g->pixel.unpackimageheight;
        break;

      case GL_UNPACK_LSB_FIRST:
        params[0] = (GLfloat) g->pixel.unpacklsbfirst;
        break;

      case GL_UNPACK_ROW_LENGTH:
        params[0] = (GLfloat) g->pixel.unpackrowlength;
        break;

      case GL_UNPACK_SKIP_IMAGES:
        params[0] = (GLfloat) g->pixel.unpackskipimages;
        break;

      case GL_UNPACK_SKIP_PIXELS:
        params[0] = (GLfloat) g->pixel.unpackskippixels;
        break;

      case GL_UNPACK_SKIP_ROWS:
        params[0] = (GLfloat) g->pixel.unpackskiprows;
        break;

      case GL_UNPACK_SWAP_BYTES:
        params[0] = (GLfloat) g->pixel.unpackswapbytes;
        break;

      case GL_VIEWPORT:
        params[0] = (GLfloat) g->viewport.v_x;
        params[1] = (GLfloat) g->viewport.v_y;
        params[2] = (GLfloat) g->viewport.v_w;
        params[3] = (GLfloat) g->viewport.v_h;
        break;

      case GL_ZOOM_X:
        params[0] = g->pixel.xzoom;
        break;

      case GL_ZOOM_Y:
        params[0] = g->pixel.yzoom;
        break;

      default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glGet: Unknown enum: 0x%x", pname))
				return;
    }
}

void GLSTATE_DECL
__glstate_GetIntegerv( GLenum pname, GLint *params )
{
    GLcontext   *g = GetCurrentContext( );

    if (g->current.beginend)
        if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
                      "glGet called in Begin/End"))
            return;
  
    switch ( pname ) {

      case GL_ACCUM_CLEAR_VALUE:
        params[0] = (GLint) g->buffer.accumclearvalue.r;
        params[1] = (GLint) g->buffer.accumclearvalue.g;
        params[2] = (GLint) g->buffer.accumclearvalue.b;
        params[3] = (GLint) g->buffer.accumclearvalue.a;
        break;

      case GL_ALPHA_TEST:
        params[0] = (GLint) g->buffer.alphatest;
        break;

      case GL_ALPHA_TEST_FUNC:
        params[0] = (GLint) g->buffer.alphatestfunc;
        break;

      case GL_ALPHA_TEST_REF:
        params[0] = (GLint) g->buffer.alphatestref;
        break;

      case GL_AUX_BUFFERS:
        params[0] = (GLint) g->buffer.auxbuffers;
        break;

      case GL_BLEND:
        params[0] = (GLint) g->buffer.blend;
        break;

      case GL_BLEND_COLOR:
        params[0] = __glcontext_clampf_to_int(g->buffer.blendcolor.r);
        params[1] = __glcontext_clampf_to_int(g->buffer.blendcolor.g);
        params[2] = __glcontext_clampf_to_int(g->buffer.blendcolor.b);
        params[3] = __glcontext_clampf_to_int(g->buffer.blendcolor.a);
        break;

      case GL_BLEND_DST:
        params[0] = (GLint) g->buffer.blenddst;
        break;

      case GL_BLEND_EQUATION:
        params[0] = (GLint) g->buffer.blendequation;
        break;

      case GL_BLEND_SRC:
        params[0] = (GLint) g->buffer.blendsrc;
        break;

      case GL_CLIP_PLANE0:
        params[0] = (GLint) g->trans.clip[0];
        break;

      case GL_CLIP_PLANE1:
        params[0] = (GLint) g->trans.clip[1];
        break;

      case GL_CLIP_PLANE2:
        params[0] = (GLint) g->trans.clip[2];
        break;

      case GL_CLIP_PLANE3:
        params[0] = (GLint) g->trans.clip[3];
        break;

      case GL_CLIP_PLANE4:
        params[0] = (GLint) g->trans.clip[4];
        break;

      case GL_CLIP_PLANE5:
        params[0] = (GLint) g->trans.clip[5];
        break;

      case GL_COLOR_CLEAR_VALUE:
        params[0] = __glcontext_clampf_to_int(g->buffer.colorclearvalue.r);
        params[1] = __glcontext_clampf_to_int(g->buffer.colorclearvalue.g);
        params[2] = __glcontext_clampf_to_int(g->buffer.colorclearvalue.b);
        params[3] = __glcontext_clampf_to_int(g->buffer.colorclearvalue.a);
        break;

      case GL_COLOR_MATERIAL:
        params[0] = (GLint) GL_FALSE;
        break;

      case GL_COLOR_MATERIAL_FACE:
        params[0] = (GLint) g->lighting.colormaterialface;
        break;

      case GL_COLOR_MATERIAL_PARAMETER:
        params[0] = (GLint) g->lighting.colormaterialmode;
        break;

      case GL_COLOR_MATRIX:
        params[0] = (GLint) g->trans.color[g->trans.colordepth].m00;
        params[1] = (GLint) g->trans.color[g->trans.colordepth].m01;
        params[2] = (GLint) g->trans.color[g->trans.colordepth].m02;
        params[3] = (GLint) g->trans.color[g->trans.colordepth].m03;
        params[4] = (GLint) g->trans.color[g->trans.colordepth].m10;
        params[5] = (GLint) g->trans.color[g->trans.colordepth].m11;
        params[6] = (GLint) g->trans.color[g->trans.colordepth].m12;
        params[7] = (GLint) g->trans.color[g->trans.colordepth].m13;
        params[8] = (GLint) g->trans.color[g->trans.colordepth].m20;
        params[9] = (GLint) g->trans.color[g->trans.colordepth].m21;
        params[10] = (GLint) g->trans.color[g->trans.colordepth].m22;
        params[11] = (GLint) g->trans.color[g->trans.colordepth].m23;
        params[12] = (GLint) g->trans.color[g->trans.colordepth].m30;
        params[13] = (GLint) g->trans.color[g->trans.colordepth].m31;
        params[14] = (GLint) g->trans.color[g->trans.colordepth].m32;
        params[15] = (GLint) g->trans.color[g->trans.colordepth].m33;
        break;

      case GL_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLint) g->trans.colordepth+1;
        break;

      case GL_CULL_FACE:
        params[0] = (GLint) g->polygon.cullface;
        break;

      case GL_CULL_FACE_MODE:
        params[0] = (GLint) g->polygon.cullfacemode;
        break;

      case GL_CURRENT_COLOR:
        params[0] = __glcontext_clampf_to_int(g->current.color.r);
        params[1] = __glcontext_clampf_to_int(g->current.color.g);
        params[2] = __glcontext_clampf_to_int(g->current.color.b);
        params[3] = __glcontext_clampf_to_int(g->current.color.a);
        break;

      case GL_CURRENT_INDEX:
        params[0] = (GLint) g->current.index;
        break;

      case GL_CURRENT_NORMAL:
        params[0] = __glcontext_clampf_to_int(g->current.normal.x);
        params[1] = __glcontext_clampf_to_int(g->current.normal.y);
        params[2] = __glcontext_clampf_to_int(g->current.normal.z);
        break;

      case GL_CURRENT_RASTER_COLOR:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_DISTANCE:
        params[0] = (GLint) g->current.rasterdistance;
        break;

      case GL_CURRENT_RASTER_INDEX:
        params[0] = (GLint) g->current.rasterindex;
        break;

      case GL_CURRENT_RASTER_POSITION:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_RASTER_POSITION_VALID:
        params[0] = (GLint) g->current.rastervalid;
        break;

      case GL_CURRENT_RASTER_TEXTURE_COORDS:
			UNIMPLEMENTED();
        break;

      case GL_CURRENT_TEXTURE_COORDS:
        params[0] = (GLint) g->current.texcoord.s;
        params[1] = (GLint) g->current.texcoord.t;
        params[2] = (GLint) g->current.texcoord.p;
        params[3] = (GLint) g->current.texcoord.q;
        break;

      case GL_DEPTH_CLEAR_VALUE:
        params[0] = __glcontext_clampd_to_int(g->buffer.depthclearvalue);
        break;

      case GL_DEPTH_FUNC:
        params[0] = (GLint) g->buffer.depthfunc;
        break;

      case GL_DEPTH_RANGE:
        params[0] = __glcontext_clampd_to_int(g->viewport.n);
        params[1] = __glcontext_clampd_to_int(g->viewport.f);
        break;

      case GL_DEPTH_TEST:
        params[0] = (GLint) g->buffer.depthtest;
        break;

      case GL_DEPTH_WRITEMASK:
        params[0] = (GLint) g->buffer.depthmask;
        break;

      case GL_DRAW_BUFFER:
        params[0] = (GLint) g->buffer.drawbuffer;
        break;

      case GL_EDGE_FLAG:
        params[0] = (GLint) g->current.edgeflag;
        break;

      case GL_FOG:
        params[0] = (GLint) g->fog.enable;
        break;

      case GL_FOG_COLOR:
        params[0] = (GLint) g->fog.color.r;
        params[1] = (GLint) g->fog.color.g;
        params[2] = (GLint) g->fog.color.b;
        params[3] = (GLint) g->fog.color.a;
        break;

      case GL_FOG_DENSITY:
        params[0] = (GLint) g->fog.density;
        break;

      case GL_FOG_END:
        params[0] = (GLint) g->fog.end;
        break;

      case GL_FOG_MODE:
        params[0] = (GLint) g->fog.mode;
        break;

      case GL_FOG_START:
        params[0] = (GLint) g->fog.start;
        break;

      case GL_FRONT_FACE:
        params[0] = (GLint) g->polygon.frontface;
        break;

      case GL_INDEX_CLEAR_VALUE:
        params[0] = __glcontext_clampf_to_int(g->buffer.indexclearvalue);
        break;

      case GL_LIGHT0:
        params[0] = (GLint) g->lighting.light[0].enable;
        break;

      case GL_LIGHT1:
        params[0] = (GLint) g->lighting.light[1].enable;
        break;

      case GL_LIGHT2:
        params[0] = (GLint) g->lighting.light[2].enable;
        break;

      case GL_LIGHT3:
        params[0] = (GLint) g->lighting.light[3].enable;
        break;

      case GL_LIGHT4:
        params[0] = (GLint) g->lighting.light[4].enable;
        break;

      case GL_LIGHT5:
        params[0] = (GLint) g->lighting.light[5].enable;
        break;

      case GL_LIGHT6:
        params[0] = (GLint) g->lighting.light[6].enable;
        break;

      case GL_LIGHT7:
        params[0] = (GLint) g->lighting.light[7].enable;
        break;

      case GL_LIGHTING:
        params[0] = (GLint) g->lighting.lighting;
        break;

      case GL_LIGHT_MODEL_AMBIENT:
        params[0] = __glcontext_clampf_to_int(g->lighting.lightmodelambient.r);
        params[1] = __glcontext_clampf_to_int(g->lighting.lightmodelambient.g);
        params[2] = __glcontext_clampf_to_int(g->lighting.lightmodelambient.b);
        params[3] = __glcontext_clampf_to_int(g->lighting.lightmodelambient.a);
        break;

      case GL_LIGHT_MODEL_LOCAL_VIEWER:
        params[0] = (GLint) g->lighting.lightmodellocalviewer;
        break;

      case GL_LIGHT_MODEL_TWO_SIDE:
        params[0] = (GLint) g->lighting.lightmodeltwoside;
        break;

      case GL_LINE_SMOOTH:
        params[0] = (GLint) g->line.linesmooth;
        break;

      case GL_LINE_STIPPLE:
        params[0] = (GLint) g->line.linestipple;
        break;

      case GL_LINE_STIPPLE_PATTERN:
        params[0] = (GLint) g->line.pattern;
        break;

      case GL_LINE_STIPPLE_REPEAT:
        params[0] = (GLint) g->line.repeat;
        break;

      case GL_LINE_WIDTH:
        params[0] = (GLint) g->line.width;
        break;

      case GL_LINE_WIDTH_GRANULARITY:
        params[0] = (GLint) g->line.aliasedlinegranularity;
        break;

      case GL_LINE_WIDTH_RANGE:
        params[0] = (GLint) g->line.aliasedlinewidth_min;
        params[1] = (GLint) g->line.aliasedlinewidth_max;
        break;

      case GL_MATRIX_MODE:
        params[0] = (GLint) g->trans.mode;
        break;

      case GL_MAX_ATTRIB_STACK_DEPTH:
        params[0] = (GLint) 0;
        break;

      case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
        params[0] = (GLint) 0;
        break;

      case GL_MAX_CLIP_PLANES:
        params[0] = (GLint) g->trans.maxclipplanes;
        break;

      case GL_MAX_COLOR_MATRIX_STACK_DEPTH:
        params[0] = (GLint) g->trans.maxcolorstackdepth;
        break;

      case GL_MAX_EVAL_ORDER:
        params[0] = (GLint) g->eval.maxevalorder;
        break;

      case GL_MAX_LIGHTS:
        params[0] = (GLint) g->lighting.maxlights;
        break;

      case GL_MAX_MODELVIEW_STACK_DEPTH:
        params[0] = (GLint) g->trans.maxmodelviewstackdepth;
        break;

      case GL_MAX_NAME_STACK_DEPTH:
        params[0] = (GLint) 0;
        break;

      case GL_MAX_PIXEL_MAP_TABLE:
        params[0] = (GLint) 0;
        break;

      case GL_MAX_PROJECTION_STACK_DEPTH:
        params[0] = (GLint) g->trans.maxprojectionstackdepth;
        break;

      case GL_MAX_TEXTURE_SIZE:
        params[0] = (GLint) g->texture.maxtexturesize;
        break;

      case GL_MAX_TEXTURE_STACK_DEPTH:
        params[0] = (GLint) g->trans.maxtexturestackdepth;
        break;

      case GL_MAX_VIEWPORT_DIMS:
        params[0] = (GLint) g->viewport.maxviewportdims_width;
        params[1] = (GLint) g->viewport.maxviewportdims_height;
        break;

      case GL_MODELVIEW_MATRIX:
        params[0] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m00;
        params[1] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m01;
        params[2] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m02;
        params[3] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m03;
        params[4] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m10;
        params[5] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m11;
        params[6] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m12;
        params[7] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m13;
        params[8] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m20;
        params[9] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m21;
        params[10] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m22;
        params[11] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m23;
        params[12] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m30;
        params[13] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m31;
        params[14] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m32;
        params[15] = (GLint) g->trans.modelview[g->trans.modelviewdepth].m33;
        break;

      case GL_MODELVIEW_STACK_DEPTH:
        params[0] = (GLint) g->trans.modelviewdepth+1;
        break;

      case GL_NORMALIZE:
        params[0] = (GLint) g->current.normalize;
        break;

      case GL_PACK_ALIGNMENT:
        params[0] = (GLint) g->pixel.packalignment;
        break;

      case GL_PACK_IMAGE_HEIGHT:
        params[0] = (GLint) g->pixel.packimageheight;
        break;

      case GL_PACK_LSB_FIRST:
        params[0] = (GLint) g->pixel.packlsbfirst;
        break;

      case GL_PACK_ROW_LENGTH:
        params[0] = (GLint) g->pixel.packrowlength;
        break;

      case GL_PACK_SKIP_IMAGES:
        params[0] = (GLint) g->pixel.packskipimages;
        break;

      case GL_PACK_SKIP_PIXELS:
        params[0] = (GLint) g->pixel.packskippixels;
        break;

      case GL_PACK_SKIP_ROWS:
        params[0] = (GLint) g->pixel.packskiprows;
        break;

      case GL_PACK_SWAP_BYTES:
        params[0] = (GLint) g->pixel.packswapbytes;
        break;

      case GL_POINT_SIZE:
        params[0] = (GLint) g->line.pointsize;
        break;

      case GL_POINT_SIZE_GRANULARITY:
        params[0] = (GLint) g->line.aliasedpointsizegranularity;
        break;

      case GL_POINT_SIZE_RANGE:
        params[0] = (GLint) g->line.aliasedpointsizerange_min;
        params[1] = (GLint) g->line.aliasedpointsizerange_max;
        break;

      case GL_POINT_SMOOTH:
        params[0] = (GLint) g->line.pointsmooth;
        break;

      case GL_POLYGON_MODE:
        params[0] = (GLint) g->polygon.frontmode;
        params[1] = (GLint) g->polygon.backmode;
        break;

      case GL_POLYGON_SMOOTH:
        params[0] = (GLint) g->polygon.polygonsmooth;
        break;

      case GL_POLYGON_STIPPLE:
        params[0] = (GLint) g->polygon.polygonstipple;
        break;

      case GL_PROJECTION_MATRIX:
        params[0] = (GLint) g->trans.projection[g->trans.projectiondepth].m00;
        params[1] = (GLint) g->trans.projection[g->trans.projectiondepth].m01;
        params[2] = (GLint) g->trans.projection[g->trans.projectiondepth].m02;
        params[3] = (GLint) g->trans.projection[g->trans.projectiondepth].m03;
        params[4] = (GLint) g->trans.projection[g->trans.projectiondepth].m10;
        params[5] = (GLint) g->trans.projection[g->trans.projectiondepth].m11;
        params[6] = (GLint) g->trans.projection[g->trans.projectiondepth].m12;
        params[7] = (GLint) g->trans.projection[g->trans.projectiondepth].m13;
        params[8] = (GLint) g->trans.projection[g->trans.projectiondepth].m20;
        params[9] = (GLint) g->trans.projection[g->trans.projectiondepth].m21;
        params[10] = (GLint) g->trans.projection[g->trans.projectiondepth].m22;
        params[11] = (GLint) g->trans.projection[g->trans.projectiondepth].m23;
        params[12] = (GLint) g->trans.projection[g->trans.projectiondepth].m30;
        params[13] = (GLint) g->trans.projection[g->trans.projectiondepth].m31;
        params[14] = (GLint) g->trans.projection[g->trans.projectiondepth].m32;
        params[15] = (GLint) g->trans.projection[g->trans.projectiondepth].m33;
        break;

      case GL_PROJECTION_STACK_DEPTH:
        params[0] = (GLint) g->trans.projectiondepth+1;
        break;

      case GL_READ_BUFFER:
        params[0] = (GLint) g->buffer.readbuffer;
        break;

      case GL_RGBA_MODE:
        params[0] = (GLint) GL_TRUE;
        break;

      case GL_SHADE_MODEL:
        params[0] = (GLint) g->lighting.shademodel;
        break;

      case GL_STENCIL_BITS:
        params[0] = (GLint) g->buffer.stencilbits;
        break;

      case GL_STENCIL_CLEAR_VALUE:
        params[0] = (GLint) g->stencil.clearvalue;
        break;

      case GL_TEXTURE_1D:
        params[0] = (GLint) g->texture.enabled1d;
        break;

      case GL_TEXTURE_2D:
        params[0] = (GLint) g->texture.enabled2d;
        break;

      case GL_TEXTURE_3D:
        params[0] = (GLint) g->texture.enabled3d;
        break;

      case GL_TEXTURE_BINDING_1D:
        params[0] = (GLint) g->texture.currenttexture1dname;
        break;

      case GL_TEXTURE_BINDING_2D:
        params[0] = (GLint) g->texture.currenttexture2dname;
        break;

      case GL_TEXTURE_BINDING_3D:
        params[0] = (GLint) g->texture.currenttexture3dname;
        break;

      case GL_TEXTURE_GEN_Q:
        params[0] = (GLint) g->texture.texturegen.q;
        break;

      case GL_TEXTURE_GEN_R:
        params[0] = (GLint) g->texture.texturegen.p;
        break;

      case GL_TEXTURE_GEN_S:
        params[0] = (GLint) g->texture.texturegen.s;
        break;

      case GL_TEXTURE_GEN_T:
        params[0] = (GLint) g->texture.texturegen.t;
        break;

      case GL_TEXTURE_MATRIX:
        params[0] = (GLint) g->trans.texture[g->trans.texturedepth].m00;
        params[1] = (GLint) g->trans.texture[g->trans.texturedepth].m01;
        params[2] = (GLint) g->trans.texture[g->trans.texturedepth].m02;
        params[3] = (GLint) g->trans.texture[g->trans.texturedepth].m03;
        params[4] = (GLint) g->trans.texture[g->trans.texturedepth].m10;
        params[5] = (GLint) g->trans.texture[g->trans.texturedepth].m11;
        params[6] = (GLint) g->trans.texture[g->trans.texturedepth].m12;
        params[7] = (GLint) g->trans.texture[g->trans.texturedepth].m13;
        params[8] = (GLint) g->trans.texture[g->trans.texturedepth].m20;
        params[9] = (GLint) g->trans.texture[g->trans.texturedepth].m21;
        params[10] = (GLint) g->trans.texture[g->trans.texturedepth].m22;
        params[11] = (GLint) g->trans.texture[g->trans.texturedepth].m23;
        params[12] = (GLint) g->trans.texture[g->trans.texturedepth].m30;
        params[13] = (GLint) g->trans.texture[g->trans.texturedepth].m31;
        params[14] = (GLint) g->trans.texture[g->trans.texturedepth].m32;
        params[15] = (GLint) g->trans.texture[g->trans.texturedepth].m33;
        break;

      case GL_TEXTURE_STACK_DEPTH:
        params[0] = (GLint) g->trans.texturedepth+1;
        break;

      case GL_UNPACK_ALIGNMENT:
        params[0] = (GLint) g->pixel.unpackalignment;
        break;

      case GL_UNPACK_IMAGE_HEIGHT:
        params[0] = (GLint) g->pixel.unpackimageheight;
        break;

      case GL_UNPACK_LSB_FIRST:
        params[0] = (GLint) g->pixel.unpacklsbfirst;
        break;

      case GL_UNPACK_ROW_LENGTH:
        params[0] = (GLint) g->pixel.unpackrowlength;
        break;

      case GL_UNPACK_SKIP_IMAGES:
        params[0] = (GLint) g->pixel.unpackskipimages;
        break;

      case GL_UNPACK_SKIP_PIXELS:
        params[0] = (GLint) g->pixel.unpackskippixels;
        break;

      case GL_UNPACK_SKIP_ROWS:
        params[0] = (GLint) g->pixel.unpackskiprows;
        break;

      case GL_UNPACK_SWAP_BYTES:
        params[0] = (GLint) g->pixel.unpackswapbytes;
        break;

      case GL_VIEWPORT:
        params[0] = (GLint) g->viewport.v_x;
        params[1] = (GLint) g->viewport.v_y;
        params[2] = (GLint) g->viewport.v_w;
        params[3] = (GLint) g->viewport.v_h;
        break;

      case GL_ZOOM_X:
        params[0] = (GLint) g->pixel.xzoom;
        break;

      case GL_ZOOM_Y:
        params[0] = (GLint) g->pixel.yzoom;
        break;

      default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, "glGet: Unknown enum: 0x%x", pname))
				return;
    }
}

/* this file auto-generated by glget.pl */
