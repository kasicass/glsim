/*
 *  render.c
 *
 *  Core rendering routines.  Rendering starts here.  This code renders
 *  buffered vertices, calling the necessary functions to transform and
 *  light the vertices and assemble them into primitives, which are then
 *  clipped, culled, and rasterized.
 *
 *  Kekoa Proudfoot
 *  11/3/01
 */

#include <assert.h>

#include "render.h"
#include "glcore.h"
#include "glcoretypes.h"
#include "transform.h"
#include "assemble.h"
#include "clip.h"
#include "cull.h"
#include "project.h"
#include "rasterize.h"
#include "util.h"
#include <glcontext/glcontext.h>

void
__glcore_render_verts (GLcontext *g)
{
    GL_primitive_list p;
    __glcore_transform_vertices(g);
    __glcore_assemble_primitives(&p, g);
    __glcore_clip_primitives(&p, g);
    __glcore_cull_primitives(&p, g);
    __glcore_project_vertices(&p, g);
    __glcore_rasterize_primitives(&p, g);
    __glcore_destroy_primitive_list_items(&p);
}

void
__glcore_break_verts (GLcontext *g)
{
    GLrenderstate *r = g->renderstate;

    switch (g->current.mode) {
    case GL_POINTS:
    case GL_LINE_STRIP:
    case GL_LINE_LOOP:
    case GL_TRIANGLE_FAN:
    case GL_POLYGON:
	break;
    case GL_LINES:
    case GL_TRIANGLE_STRIP:
    case GL_QUAD_STRIP:
	assert(r->nverts % 2 == 0);
	break;
    case GL_TRIANGLES:
	assert(r->nverts % 3 == 0);
	break;
    case GL_QUADS:
	assert(r->nverts % 4 == 0);
	break;
    }

    __glcore_render_verts(g);

    switch (g->current.mode) {
    case GL_POINTS:
    case GL_LINES:
    case GL_TRIANGLES:
    case GL_QUADS:
	r->nverts = 0;
	break;
    case GL_LINE_STRIP:
	r->verts[0] = r->verts[r->nverts - 1];
	r->nverts = 1;
	break;
    case GL_TRIANGLE_STRIP:
    case GL_QUAD_STRIP:
	r->verts[0] = r->verts[r->nverts - 2];
	r->verts[1] = r->verts[r->nverts - 1];
	r->nverts = 2;
	break;
    case GL_LINE_LOOP:
    case GL_TRIANGLE_FAN:
    case GL_POLYGON:
	r->verts[1] = r->verts[r->nverts - 1];
	r->nverts = 2;
	break;
    }

    r->assembleflags |= ASSEMBLE_CONTINUE;
}
