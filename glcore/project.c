/*
 *  project.c
 *
 *  Routines to project vertices and perform the viewport transformation.
 *
 *  Kekoa Proudfoot
 *  11/5/01
 */

#include <assert.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "project.h"
#include "util.h"
#include "vec.h"

#include <glcontext/glcontext.h>

void
__glcore_project_vertices (GL_primitive_list *pl, GLcontext *g)
{
    GLrenderstate *r = g->renderstate;
    GL_clipvert *cv;
    int i;

    GL_float l = g->viewport.v_x;
    GL_float b = g->viewport.v_y;
    GL_float w = g->viewport.v_w;
    GL_float h = g->viewport.v_h;
    GL_float n = g->viewport.n;
    GL_float f = g->viewport.f;

    GL_float scale[3];
    GL_float shift[3];

    vinit3(scale, 0.5f * w, 0.5f * h, 0.5f * (f - n));
    vinit3(shift, l + scale[0], b + scale[1], 0.5f * (n + f));

    for (i = 0; i < r->nverts; i++) {
	GL_procvert *v = &r->procverts[i];
	GL_float invw = 1.0f / v->position[3];
	GL_float proj[3];
	vinit3(proj, v->position[0], v->position[1], v->position[2]);
	vscale3(proj, proj, invw);
	vmul3(proj, proj, scale);
	vadd3(v->windowpos, proj, shift);
	v->windowpos[3] = invw;
    }

    for (cv = pl->clipverts; cv; cv = cv->next) {
	GL_procvert *v = &cv->procvert;
	GL_float invw = 1.0f / v->position[3];
	GL_float proj[3];
	vinit3(proj, v->position[0], v->position[1], v->position[2]);
	vscale3(proj, proj, invw);
	vmul3(proj, proj, scale);
	vadd3(v->windowpos, proj, shift);
	v->windowpos[3] = invw;
    }
}
