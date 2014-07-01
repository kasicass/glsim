/*
 *  clip.c
 *
 *  Primitive clipping routines.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#include <assert.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "clip.h"
#include "util.h"
#include "vec.h"

#include <glcontext/glcontext.h>

#define IN  0
#define OUT 1

#define ENCODE(v0,v1,v2) ((v0<<2)|(v1<<1)|(v2<<0))
#define ENCODE2(v1,v2) ENCODE(0,v1,v2)
#define ENCODE1(v1) ENCODE(0,0,v1)

static GL_procvert *
intersect(GL_primitive_list *pl, GLcontext *g, GL_procvert *v0,
	  GL_procvert *v1, GL_procvert *vc, GL_float plane[4])
{
    GL_clipvert *cv = __glcore_create_clipvert();
    GL_procvert *v = &cv->procvert;

    /* Hack! If d0 is always outside, complementary criterion cannot be met */
    /* Should use a spatial sort of d0 and d1 */
    GL_float d0 = vdot(v0->position, plane); /* outside */
    GL_float d1 = vdot(v1->position, plane); /* inside */
    GL_float t = d0 / (d0 - d1);

    assert(d0 < 0.0f);
    assert(d1 >= 0.0f);

    __glcore_add_clipvert(pl, cv);

    vinterp(v->position, v0->position, v1->position, t);

    /* Hack? There has got to be a better way to maintain color vertex. */
    /* Hack? Given primitive facing, could copy only front or back. */
    if (g->lighting.shademodel == GL_SMOOTH) {
	vinterp(v->frontcolor, v0->frontcolor, v1->frontcolor, t);
	vinterp(v->backcolor, v0->backcolor, v1->backcolor, t);
    }
    else {
	vcopy(v->frontcolor, vc->frontcolor);
	vcopy(v->backcolor, vc->backcolor);
    }

    vinterp(v->texcoord, v0->texcoord, v1->texcoord, t);

    return v;
}

static void
clip_point (GL_primitive_list *pl, GLcontext *g, GL_float plane[4],
	    GL_primitive *p, int bits)
{
    switch (bits) {
    case ENCODE1(OUT):
	__glcore_destroy_primitive(p);
	break;
    case ENCODE1(IN):
	__glcore_add_primitive(pl, p);
	break;
    }
}

static void
clip_line (GL_primitive_list *pl, GLcontext *g, GL_float plane[4],
	   GL_primitive *p, int bits)
{
    GL_procvert *v0 = p->verts[0];
    GL_procvert *v1 = p->verts[1];
    GL_procvert *v2;

    switch (bits) {
    case ENCODE2(OUT, OUT):
	__glcore_destroy_primitive(p);
	break;
    case ENCODE2(OUT, IN):
	v2 = intersect(pl, g, v0, v1, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 2, v2, v0, NULL);
	break;
    case ENCODE2(IN, OUT):
	v2 = intersect(pl, g, v1, v0, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 2, v0, v2, NULL);
	break;
    case ENCODE2(IN, IN):
	__glcore_add_primitive(pl, p);
	break;
    }
}

static void
clip_triangle (GL_primitive_list *pl, GLcontext *g, GL_float plane[4],
	       GL_primitive *p, int bits)
{
    GL_procvert *v0 = p->verts[0];
    GL_procvert *v1 = p->verts[1];
    GL_procvert *v2 = p->verts[2];
    GL_procvert *v3;
    GL_procvert *v4;

    switch (bits) {
    case ENCODE(OUT, OUT, OUT):
	__glcore_destroy_primitive(p);
	break;
    case ENCODE(OUT, OUT, IN):
	v3 = intersect(pl, g, v1, v2, v0, plane);
	v4 = intersect(pl, g, v0, v2, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 3, v3, v2, v4);
	break;
    case ENCODE(OUT, IN, OUT):
	v3 = intersect(pl, g, v0, v1, v0, plane);
	v4 = intersect(pl, g, v2, v1, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 3, v3, v1, v4);
	break;
    case ENCODE(OUT, IN, IN):
	v3 = intersect(pl, g, v0, v1, v0, plane);
	v4 = intersect(pl, g, v0, v2, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 3, v3, v1, v2);
	__glcore_add_new_primitive(pl, 3, v3, v2, v4);
	break;
    case ENCODE(IN, OUT, OUT):
	v3 = intersect(pl, g, v1, v0, v0, plane);
	v4 = intersect(pl, g, v2, v0, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 3, v0, v3, v4);
	break;
    case ENCODE(IN, OUT, IN):
	v3 = intersect(pl, g, v1, v0, v0, plane);
	v4 = intersect(pl, g, v1, v2, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 3, v0, v3, v4);
	__glcore_add_new_primitive(pl, 3, v0, v4, v2);
	break;
    case ENCODE(IN, IN, OUT):
	v3 = intersect(pl, g, v2, v1, v0, plane);
	v4 = intersect(pl, g, v2, v0, v0, plane);
	__glcore_set_and_add_primitive(pl, p, 3, v0, v1, v3);
	__glcore_add_new_primitive(pl, 3, v0, v3, v4);
	break;
    case ENCODE(IN, IN, IN):
	__glcore_add_primitive(pl, p);
	break;
    }
}

static void
clip_primitives (GL_primitive_list *pl, GLcontext *g, GL_float plane[4])
{
    GLrenderstate *r = g->renderstate;
    GL_primitive *p = pl->head, *next;

    pl->head = NULL;
    pl->tail = NULL;

    for ( ; p; p = next) {
	int bits = 0;
	int cull = 1;
	int clip = 0;
	int i;

	next = p->next;

	for (i = 0; i < p->nverts; i++) {
	    int c = (vdot(p->verts[i]->position, plane) < 0.0f);
	    cull &= c;
	    clip |= c;
	    bits = (bits << 1) | c;
	}

	if (cull)
	    __glcore_destroy_primitive(p);
	else if (!clip)
	    __glcore_add_primitive(pl, p);
	else {
	    switch (p->nverts) {
	    case 1: clip_point(pl, g, plane, p, bits); break;
	    case 2: clip_line(pl, g, plane, p, bits); break;
	    case 3: clip_triangle(pl, g, plane, p, bits); break;
	    }
	}
    }
}

void
__glcore_clip_primitives (GL_primitive_list *pl, GLcontext *g)
{
    int i;

    pl->clipverts = NULL;

    for (i = 0; i < 6; i++) {
	static GL_float frustum[6][4] = {
	    { 1, 0, 0, 1 }, { -1, 0, 0, 1 },
	    { 0, 1, 0, 1 }, { 0, -1, 0, 1 },
	    { 0, 0, 1, 1 }, { 0, 0, -1, 1 }
	};
	clip_primitives(pl, g, frustum[i]);
    }

    for (i = 0; i < g->trans.maxclipplanes; i++) {
	if (g->trans.clip[i]) {
	    GL_float plane[4];
	    vinit_vec(plane, g->trans.clipplane[i]);
	    clip_primitives(pl, g, plane);
	}
    }
}
