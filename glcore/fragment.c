/*
 *  fragment.c
 *
 *  Fragment processing routines.  Performs texturing, implements the
 *  texture environment, performs the depth and alpha tests, implements the
 *  depth and color buffer writes.
 *
 *  Kekoa Proudfoot
 *  11/8/01
 */

#include <assert.h>
#include <math.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "fragment.h"
#include "util.h"
#include "vec.h"

#include <glcontext/glcontext.h>

#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif

int index;

static void
unpack_image_sample (GL_float color[4], GLint components, GLenum format,
		     GLenum type, GLvoid *pixel)
{
    int dst[4];
    int i, n;

    vinit(color, 0.0f, 0.0f, 0.0f, 1.0f);

    /* get format parameters */
    switch (format) {
    case GL_RED: n = 1; vinit(dst, 0, 0, 0, 0); break;
    case GL_GREEN: n = 1; vinit(dst, 1, 0, 0, 0); break;
    case GL_BLUE: n = 1; vinit(dst, 2, 0, 0, 0); break;
    case GL_ALPHA: n = 1; vinit(dst, 3, 0, 0, 0); break;
    case GL_RGB: n = 3; vinit(dst, 0, 1, 2, 0); break;
    case GL_RGBA: n = 4; vinit(dst, 0, 1, 2, 3); break;
    case GL_BGR: n = 3; vinit(dst, 2, 1, 0, 0); break;
    case GL_BGRA: n = 4; vinit(dst, 2, 1, 0, 3); break;
    case GL_ABGR_EXT: n = 4; vinit(dst, 3, 2, 1, 0); break;
    case GL_LUMINANCE: n = 1; vinit(dst, 0, 0, 0, 0); break;
    case GL_LUMINANCE_ALPHA: n = 2; vinit(dst, 0, 3, 0, 0); break;
    default: n = 0; vinit(dst, 0, 0, 0, 0); break;
    }

    /* get pixel data */
    for (i = 0; i < n; i++) {
	switch (type) {
	case GL_UNSIGNED_BYTE:
	    color[dst[i]] = ((GLubyte *)pixel)[i] / 255.0f;
	    break;
	case GL_FLOAT:
	    color[dst[i]] = ((GLfloat *)pixel)[i];
	    break;
	default:
	    /* unsupported, use default */
	    break;
	}
    }

    /* convert to internal format if necessary */
    switch (components) {
    case GL_ALPHA:
	color[0] = color[1] = color[2] = 1.0f;
	break;
    case GL_LUMINANCE: case 1:
    case GL_LUMINANCE_ALPHA: case 2:	
	color[1] = color[2] = color[0];
	break;
    case GL_INTENSITY:
	color[1] = color[2] = color[3] = color[0];
	break;
    case GL_RGB:
    case GL_RGBA:
	/* no action necessary */
	break;
    }
}

static void
sample_texture_level (GL_float color[4], GLtextureobj *tex, int level,
		      GLfloat coord[3], int linear)
{
    GLtexturelevel *tl = &tex->level[level];
    int b = tl->border;
    int sizes[3] = { tl->width, tl->height, tl->depth };
    int dims[3] = { sizes[0] - 2 * b, sizes[1] - 2 * b, sizes[2] - 2 * b };
    int repeat[3] = { (tex->wraps == GL_REPEAT),
		      (tex->wrapt == GL_REPEAT),
		      1 /* tex->wrapr does not exist, use default */ };
    int dimsize;
    int n;

    int offsets[2][3];
    int out[2][3];
    GL_float frac[3];
    int i, j, k;

    GL_float samples[8][4];

    /* get number of components */
    switch (tex->target) {
    case GL_TEXTURE_1D: n = 1; break;
    case GL_TEXTURE_2D: n = 2; break;
    case GL_TEXTURE_3D: n = 3; break;
    }

    /* generate texel offsets and interpolation fractions */
    for (i = 0, dimsize = tl->bytesperpixel; i < n; i++) {
	GL_float wcoord;
	int index0 = 0;
	int index1 = 0;

	/* wrap coordinate */
	if (repeat[i])
	    wcoord = (coord[i] - floor(coord[i]));
	else
	    wcoord = clamp(coord[i], 0.0f, 1.0f);

	/* scale by texture dimension */
	wcoord *= dims[i];

	/* nearest or linear? */
	if (!linear) {
	    /* nearest, compute one index */
	    index0 = floor(wcoord);
	    index0 = min(index0, dims[i] - 1);
	}
	else {
	    /* linear, compute two indices and a fraction */
	    GL_float wfloor = floor(wcoord - 0.5f);
	    int mask = (repeat[i]) ? dims[i] - 1 : -1;
	    index0 = ((int)wfloor) & mask;
	    index1 = (index0 + 1) & mask;
	    frac[i] = (wcoord - 0.5f) - wfloor;

	    /* check for sampling outside texture image */
	    out[1][i] = (index1 < -b || index1 >= dims[i] + b);

	    /* compute address offset */
	    offsets[1][i] = dimsize * (index1 + b);
	}

	/* check for sampling outside texture image */
	out[0][i] = (index0 < -b || index0 >= dims[i] + b);

	/* compute address offset */
	offsets[0][i] = dimsize * (index0 + b);

	/* update address offset */
	dimsize *= sizes[i];
    }

    /* clear relevant remaining offsets and flags */
    for ( ; i < 3; i++)
	offsets[0][i] = out[0][i] = 0;

    /* if nearest, force single sample */
    if (!linear)
	n = 0;

    /* get texture samples */
    for (i = 0; i < (1<<n); i++) {
	int i0 = (i >> 0) & 1;
	int i1 = (i >> 1) & 1;
	int i2 = (i >> 2) & 1;

	if (out[i0][0] | out[i1][1] | out[i2][2]) {
	    /* sample the border color */
	    GLfloat bordercolor[4];
	    vinit_col(bordercolor, tex->bordercolor);
	    unpack_image_sample(samples[i], tl->components, GL_RGBA,
				GL_FLOAT, bordercolor);
	}
	else {
	    /* sample the actual texture image */
	    int offset = offsets[i0][0] + offsets[i1][1] + offsets[i2][2];

#if 0
	    int betteroffset, bpp;
	    switch (tl->components) {
	    case GL_ALPHA: GL_LUMINANCE: GL_INTENSITY: case 1: bpp = 1; break;
	    case GL_LUMINANCE_ALPHA: case 2: bpp = 2; break;
	    case GL_RGB: case 3: bpp = 3; break;
	    case GL_RGBA: case 4: default: bpp = 4; break;
	    }
	    /*
	     *  NOTE: The texture image is stored in a weird internal format.
	     *  If you are using this for the graphics hardware class,
	     *  uncomment this code and use it to compute a better offset
	     *  into the texture.  Note the element size of bpp.
             */
	    betteroffset = (offset * bpp) / tl->bytesperpixel;
#endif
	    unpack_image_sample(samples[i], tl->components, tl->format,
				tl->type, &tl->img[offset]);
	}
    }

    /* filter texture samples */
    for (i = n - 1; i >= 0; i--)
	for (j = 0, k = (1<<i); j < k; j++)
	    vinterp(samples[j], samples[j], samples[k+j], frac[i]);

    /* copy result to color */
    vcopy(color, samples[0]);
}

static void
sample_texture (GL_float color[4], GLtextureobj *tex, GLfloat coord[3],
		GL_float dx[3], GL_float dy[3])
{
    int mip, linear, miplinear;
    GL_float lod;

    int baselevel = 0; /* tex->baselevel does not exist, use default */
    int lastlevel = tex->lastlevel;
    int level;

    /* get min filter parameters */
    switch (tex->minfilter) {
    case GL_NEAREST: mip = 0; linear = 0; miplinear = 0; break;
    case GL_LINEAR: mip = 0; linear = 1; miplinear = 0; break;
    case GL_NEAREST_MIPMAP_NEAREST: mip = 1; linear = 0; miplinear = 0; break;
    case GL_NEAREST_MIPMAP_LINEAR: mip = 1; linear = 0; miplinear = 1; break;
    case GL_LINEAR_MIPMAP_NEAREST: mip = 1; linear = 1; miplinear = 0; break;
    case GL_LINEAR_MIPMAP_LINEAR: mip = 1; linear = 1; miplinear = 1; break;
    }

    /* determine lod */
    if (mip) {
	int b = tex->level[baselevel].border;
	int w = tex->level[baselevel].width - 2 * b;
	int h = tex->level[baselevel].height - 2 * b;
	int d = tex->level[baselevel].depth - 2 * b;
	GL_float dims[3];
	GL_float xlen, ylen, scale;

	/* get dimension scale factors */
	switch (tex->target) {
	case GL_TEXTURE_1D: vinit3(dims, w, 0.0f, 0.0f); break;
	case GL_TEXTURE_2D: vinit3(dims, w, h, 0.0f); break;
	case GL_TEXTURE_3D: vinit3(dims, w, h, d); break;
	}

	/* compute level of detail */
	vmul3(dx, dx, dims);
	vmul3(dy, dy, dims);
	xlen = vlen3(dx);
	ylen = vlen3(dy);
	scale = max(xlen, ylen);
	lod = log(scale) / M_LN2;

	/* check for magnify */
	mip = (lod > ((!linear && tex->magfilter == GL_LINEAR) ? 0.5f : 0.0f));

	if (!mip)
	    linear = (tex->magfilter == GL_LINEAR);
    }

    /* determine lower level */
    if (!mip)
	level = baselevel;
    else if (!miplinear)
	level = baselevel + ceil(lod + 0.5f) - 1.0f;
    else
	level = baselevel + floor(lod);
    level = clamp(level, baselevel, lastlevel);

    /* sample the lower level */
    sample_texture_level(color, tex, level, coord, linear);

    /* sample the upper level if necessary */
    if (mip && miplinear && level < lastlevel) {
	GL_float frac = lod - floor(lod);
	GL_float upper[4];
	sample_texture_level(upper, tex, level + 1, coord, linear);
	vinterp(color, color, upper, frac);
    }
}

static void
get_blend_factor (GLenum factor, GL_float val[4], GL_float s[4], GL_float d[4])
{
    GL_float tmp;

    switch (factor) {
    case GL_ZERO:
	vinit(val, 0.0f, 0.0f, 0.0f, 0.0f);
	break;
    case GL_ONE:
	vinit(val, 1.0f, 1.0f, 1.0f, 1.0f);
	break;
    case GL_SRC_COLOR:
	vcopy(val, s);
	break;
    case GL_ONE_MINUS_SRC_COLOR:
	vinit(val, 1.0f, 1.0f, 1.0f, 1.0f);
	vsub(val, val, s);
	break;
    case GL_DST_COLOR:
	vcopy(val, d);
	break;
    case GL_ONE_MINUS_DST_COLOR:
	vinit(val, 1.0f, 1.0f, 1.0f, 1.0f);
	vsub(val, val, d);
	break;
    case GL_SRC_ALPHA:
	tmp = s[3];
	vinit(val, tmp, tmp, tmp, tmp);
	break;
    case GL_ONE_MINUS_SRC_ALPHA:
	tmp = 1.0f - s[3];
	vinit(val, tmp, tmp, tmp, tmp);
	break;
    case GL_DST_ALPHA:
	tmp = d[3];
	vinit(val, tmp, tmp, tmp, tmp);
	break;
    case GL_ONE_MINUS_DST_ALPHA:
	tmp = 1.0f - d[3];
	vinit(val, tmp, tmp, tmp, tmp);
	break;
    case GL_SRC_ALPHA_SATURATE:
	tmp = min(s[3], 1.0f - d[3]);
	vinit(val, tmp, tmp, tmp, 1.0f);
	break;
    default:
	assert(0);
    }
}

static void
update_buffer (GLcontext *g, unsigned int *buffer, int offset, GL_float *color)
{
    GL_float prevcolor[4];

    /* get previous color */
    cunpack(prevcolor, buffer[offset]);
    
    /* blending */
    if (g->buffer.blend) {
	GL_float src[4];
	GL_float dst[4];
	get_blend_factor(g->buffer.blendsrc, src, color, prevcolor);
	get_blend_factor(g->buffer.blenddst, dst, color, prevcolor);
	vmul(src, src, color);
	vmul(dst, dst, prevcolor);
	vadd(color, src, dst);
	vclamp(color, color, 0.0f, 1.0f);
    }

    /* no dithering yet */
    
    /* write masks */
    color[0] = (g->buffer.colorwritemask.r == 0) ? prevcolor[0] : color[0];
    color[1] = (g->buffer.colorwritemask.g == 0) ? prevcolor[1] : color[1];
    color[2] = (g->buffer.colorwritemask.b == 0) ? prevcolor[2] : color[2];
    color[3] = (g->buffer.colorwritemask.a == 0) ? prevcolor[3] : color[3];

    /* buffer update */
    buffer[offset] = cpack(color);
}

void
__glcore_process_fragments (GLcontext *g, int n, GL_fragment *f)
{
    GLrenderstate *r = g->renderstate;
    GLtextureobj *tex = r->texobj;

    unsigned int *frontcolorbuf = g->framebuffer->color[0];
    unsigned int *backcolorbuf = g->framebuffer->color[1];
    GL_float *depthbuf = g->framebuffer->depth;
    int w = g->framebuffer->width;
    int h = g->framebuffer->height;
    int i;

    assert(!r->texobj || r->texobj->valid);

    if (!__glcore_draw_buffer_front_left(g)) frontcolorbuf = NULL;
    if (!__glcore_draw_buffer_back_left(g)) backcolorbuf = NULL;

    for (i = 0; i < n; i++) {
	int x = f[i].x;
	int y = f[i].y;
	GL_float depth = f[i].depth;
	GL_float color[4];

	int offset = y * w + x;

	int apass = 1;
	int zpass = 1;

index = i;

	assert(x >= 0 && x < w);
	assert(y >= 0 && y < h);

	vclamp(color, f[i].color, 0.0f, 1.0f);

	/* texturing */
	if (tex) {
	    GL_float texcolor[4];
	    GL_float envcolor[4];
	    GL_float tmpcolor[4];
	    int baselevel = 0; /* tex->baselevel does not exist, use default */
	    int format = tex->level[baselevel].components;

	    /* texture lookup */
	    sample_texture(texcolor, tex, f[i].texcoord, f[i].texcoorddx,
			   f[i].texcoorddy);

	    /* texture environment */
	    switch (g->texture.envmode) {
	    case GL_REPLACE:
		switch (format) {
		case GL_ALPHA:
		    color[3] = texcolor[3];
		    break;
		case GL_LUMINANCE: case 1:
		case GL_RGB: case 3:
		    vcopy3(color, texcolor);
		    break;
		case GL_LUMINANCE_ALPHA: case 2:
		case GL_INTENSITY:
		case GL_RGBA: case 4:
		    vcopy(color, texcolor);
		    break;
		}
		break;
	    case GL_MODULATE:
		vmul(color, color, texcolor);
		break;
	    case GL_DECAL:
		switch (format) {
		case GL_RGB: case 3:
		    vcopy3(color, texcolor);
		    break;
		case GL_RGBA: case 4:
		    vscale3(color, color, 1.0f - texcolor[3]);
		    vscale3(texcolor, texcolor, texcolor[3]);
		    vadd3(color, color, texcolor);
		    break;
		}
		break;
	    case GL_BLEND:
		switch (format) {
		case GL_ALPHA:
		    color[3] *= texcolor[3];
		    break;
		case GL_LUMINANCE: case 1:
		case GL_LUMINANCE_ALPHA: case 2:
		case GL_INTENSITY:
		case GL_RGB: case 3:
		case GL_RGBA: case 4:
		    vinit_col(envcolor, g->texture.envcolor);
		    vinit(tmpcolor, 1.0f, 1.0f, 1.0f, 1.0f);
		    vsub3(tmpcolor, tmpcolor, texcolor);
		    vmul3(color, color, tmpcolor);
		    vmul3(envcolor, envcolor, texcolor);
		    vadd3(color, color, envcolor);
		    break;
		}
		break;
	    }
	}

	/* fog unimplemented */

	/* alpha test */
	if (g->buffer.alphatest) {
	    /* perform test using quantized colors */
	    int alpha = cftob(color[3]);
	    int ref = cftob(g->buffer.alphatestref);
	    switch (g->buffer.alphatestfunc) {
	    case GL_NEVER: apass = 0; break;
	    case GL_LESS: apass = (alpha < ref); break;
	    case GL_EQUAL: apass = (alpha == ref); break;
	    case GL_LEQUAL: apass = (alpha <= ref); break;
	    case GL_GREATER: apass = (alpha > ref); break;
	    case GL_NOTEQUAL: apass = (alpha != ref); break;
	    case GL_GEQUAL: apass = (alpha >= ref); break;
	    case GL_ALWAYS: apass = 1; break;
	    default: assert(0);
	    }
	}

	/* depth test */
	if (g->buffer.depthtest) {
	    switch (g->buffer.depthfunc) {
	    case GL_NEVER: zpass = 0; break;
	    case GL_LESS: zpass = (depth < depthbuf[offset]); break;
	    case GL_EQUAL: zpass = (depth == depthbuf[offset]); break;
	    case GL_LEQUAL: zpass = (depth <= depthbuf[offset]); break;
	    case GL_GREATER: zpass = (depth > depthbuf[offset]); break;
	    case GL_NOTEQUAL: zpass = (depth != depthbuf[offset]); break;
	    case GL_GEQUAL: zpass = (depth >= depthbuf[offset]); break;
	    case GL_ALWAYS: zpass = 1; break;
	    default: assert(0);
	    }
	}

	/* passed tests? */
	if (apass && zpass) {
	    if (frontcolorbuf)
		update_buffer(g, frontcolorbuf, offset, color);
	    if (backcolorbuf)
		update_buffer(g, backcolorbuf, offset, color);
	    if (g->buffer.depthmask)
		depthbuf[offset] = depth;
	}
    }
}

