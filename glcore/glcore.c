/*
 *  glcore.c
 *
 *  Core rendering interface.  Includes code to buffer vertices and initiate
 *  rendering.  Includes code to manage a framebuffer and display the
 *  framebuffer on the screen.
 *
 *  Kekoa Proudfoot
 *  10/31/01
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "vec.h"
#include "util.h"
#include "render.h"
#include "gl/gllocal.h"
#include "glcontext/glcontext.h"

/* Core interface */

#define VERTEX_BUFFER_SIZE 1024 /* must be at least 4 */

GLrenderstate *
__glcore_CreateContext (void)
{
    GLrenderstate *r = (GLrenderstate *) malloc (sizeof (GLrenderstate));

    r->nverts = 0;
    r->maxverts = VERTEX_BUFFER_SIZE;
    r->verts = (GL_vertex *)malloc(r->maxverts * sizeof(GL_vertex));
    r->procverts = (GL_procvert *)malloc(r->maxverts * sizeof(GL_procvert));

    r->numtris = 0;
    r->numfrags = 0;

#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_CreateContext\n");
#endif

    return r;
}

GLframebuffer *
__glcore_CreateFrameBuffer (int width, int height, int isdouble,
			    GLDrawFunc drawfunc, GLSyncFunc syncfunc)
{
    GLframebuffer *fb;

#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_CreateFrameBuffer\n");
#endif

    fb = (GLframebuffer *)malloc(sizeof(GLframebuffer));

    fb->width = -1;
    fb->height = -1;
    fb->isdouble = isdouble;
    fb->color[0] = NULL;
    fb->color[1] = NULL;
    fb->depth = NULL;
    fb->drawfunc = drawfunc;
    fb->syncfunc = syncfunc;

    __glcore_ResizeFrameBuffer(fb, width, height);

    return fb;
}

void
__glcore_ResizeFrameBuffer (GLframebuffer *fb, int width, int height)
{
    /* For simplicity: do not try to copy old contents into new buffers */

    if (width == fb->width && height == fb->height)
	return;

    if (fb->color[0])
	free(fb->color[0]);
    if (fb->color[1])
	free(fb->color[1]);
    if (fb->depth)
	free(fb->depth);

    fb->color[0] = malloc(width * height * sizeof(fb->color[0][0]));
    fb->color[1] = malloc(width * height * sizeof(fb->color[1][0]));
    fb->depth = malloc(width * height * sizeof(fb->depth[0]));

    fb->width = width;
    fb->height = height;
}

void
__glcore_Begin (GLcontext *g, GLenum mode)
{
    GLrenderstate *r = g->renderstate;

    __glcore_update_current_texture_info(g);

    r->nverts = 0;

    switch (mode) {
    case GL_POINTS:
    case GL_LINE_STRIP:
    case GL_LINE_LOOP:
    case GL_TRIANGLE_FAN:
    case GL_POLYGON:
	r->lastvert = r->maxverts;
	break;
    case GL_LINES:
    case GL_TRIANGLE_STRIP:
    case GL_QUAD_STRIP:
	r->lastvert = (r->maxverts / 2) * 2;
	break;
    case GL_TRIANGLES:
	r->lastvert = (r->maxverts / 3) * 3;
	break;
    case GL_QUADS:
	r->lastvert = (r->maxverts / 4) * 4;
	break;
    }

    r->assembleflags = ASSEMBLE_START;

#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_Begin\n");
#endif
}

void
__glcore_End (GLcontext *g)
{
    GLrenderstate *r = g->renderstate;

    r->assembleflags |= ASSEMBLE_END;

    __glcore_render_verts(g);

#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_End\n");
#endif
}

void
__glcore_Vertex4f (GLcontext *g, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLrenderstate *r = g->renderstate;
    GL_vertex *v;

    if (r->nverts == r->lastvert)
	__glcore_break_verts(g);

    /* Store vertex */
    v = &r->verts[r->nverts++];
    vinit(v->position, x, y, z, w);
    vinit_col(v->color, g->current.color);
    vinit_tex(v->texcoord, g->current.texcoord);
    if (g->lighting.lighting) {
	vinit_vec(v->normal, g->current.normal);
	vinit_col(v->frontmaterial.ambient, g->lighting.ambient[0]);
	vinit_col(v->frontmaterial.diffuse, g->lighting.diffuse[0]);
	vinit_col(v->frontmaterial.specular, g->lighting.specular[0]);
	vinit_col(v->frontmaterial.emission, g->lighting.emission[0]);
	v->frontmaterial.shininess = g->lighting.shininess[0];
	if (g->lighting.lightmodeltwoside) {
	    vinit_col(v->backmaterial.ambient, g->lighting.ambient[1]);
	    vinit_col(v->backmaterial.diffuse, g->lighting.diffuse[1]);
	    vinit_col(v->backmaterial.specular, g->lighting.specular[1]);
	    vinit_col(v->backmaterial.emission, g->lighting.emission[1]);
	    v->backmaterial.shininess = g->lighting.shininess[1];
	}
    }


#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_Vertex4f\n");
#endif
}

static void
finish (GLcontext *g)
{
    if (__glcore_draw_buffer_front_left(g)) {
	GLframebuffer *fb = g->framebuffer;
	unsigned int *front = fb->color[0];
	int w = fb->width;
	int h = fb->height;
	fb->drawfunc(front, 0, 0, w, h, w);
    }

    /* sync up with the X server */
    g->framebuffer->syncfunc();    
}

void
__glcore_Flush (GLcontext *g)
{
#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_Flush\n");
#endif
    /* flush equals finish for us */
    finish(g);
}

void
__glcore_Finish (GLcontext *g)
{
#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_Finish\n");
#endif
    finish(g);
}

static void
clear_scissor_rect_ui (GLcontext *g, unsigned int *ptr, unsigned int value)
{
	int x, xmin, xmax;
	int y, ymin, ymax;
	int w = g->framebuffer->width;
    
	__glcore_get_scissor_rect(g, &xmin, &xmax, &ymin, &ymax);

	if (xmin >= xmax || ymin >= ymax)
		return;

	for (y = ymin; y < ymax; y++) {
		unsigned int *p = &ptr[y * w + xmin];
		for (x = xmin; x < xmax; x++)
			*p++ = value;
	}
}

static void
clear_scissor_rect_f (GLcontext *g, GL_float *ptr, GL_float value)
{
	int x, xmin, xmax;
	int y, ymin, ymax;
	int w = g->framebuffer->width;    

	__glcore_get_scissor_rect(g, &xmin, &xmax, &ymin, &ymax);

	if (xmin >= xmax || ymin >= ymax)
		return;

	for (y = ymin; y < ymax; y++) {
		GL_float *p = &ptr[y * w + xmin];
		for (x = xmin; x < xmax; x++)
			*p++ = value;
	}
}

void
__glcore_Clear (GLcontext *g, GLbitfield mask)
{
	GLframebuffer *fb = g->framebuffer;

	if (mask & GL_COLOR_BUFFER_BIT) {
		GL_float clear_color[4];
		unsigned int packed_clear_color;

		vinit_col(clear_color, g->buffer.colorclearvalue);
		packed_clear_color = cpack(clear_color);

		if (__glcore_draw_buffer_front_left(g))
			clear_scissor_rect_ui(g, fb->color[0], packed_clear_color);
		if (__glcore_draw_buffer_back_left(g) && fb->isdouble)
			clear_scissor_rect_ui(g, fb->color[1], packed_clear_color);
	}

	if (mask & GL_DEPTH_BUFFER_BIT)
		clear_scissor_rect_f(g, fb->depth, g->buffer.depthclearvalue);

#ifdef DEBUG_GLCORE_CALLS
	fprintf(stderr, "__glcore_Clear\n");
#endif
}

void
__glcore_SwapBuffers (GLcontext *g)
{
    GLframebuffer *fb = g->framebuffer;
    int w = fb->width;
    int h = fb->height;

    if (fb->isdouble) {
	unsigned int *back = fb->color[1];
	fb->drawfunc(back, 0, 0, w, h, w);
	fb->color[1] = fb->color[0];
	fb->color[0] = back;
    }
    else {
	unsigned int *front = fb->color[1];
	fb->drawfunc(front, 0, 0, w, h, w);
    }

#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_SwapBuffers\n");
#endif

#if 0
#define PRINT_STATS
#endif

#ifdef PRINT_STATS
    {
	GLrenderstate *r = g->renderstate;
	static int frame = 0;

	fprintf(stderr, "frame %d\n", frame++);
	fprintf(stderr, "buffer size %d %d\n", w, h);
	fprintf(stderr, "number of triangles %d\n", r->numtris);
	fprintf(stderr, "number of fragments %d\n", r->numfrags);
	r->numtris = 0;
	r->numfrags = 0;
    }
#endif
}


void
__glcore_DestroyFrameBuffer (GLframebuffer *fb)
{
#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_CreateFrameBuffer\n");
#endif
    if (fb->color[0]) free(fb->color[0]);
    if (fb->color[1]) free(fb->color[1]);
    if (fb->depth) free(fb->depth);
    free(fb);
}

void
__glcore_DestroyContext (GLrenderstate *r)
{
#ifdef DEBUG_GLCORE_CALLS
    fprintf(stderr, "__glcore_DestroyContext\n");
#endif
    free(r->verts);
    free(r);
}
