/*
 *  cull.c
 *
 *  Primitive culling routines.  Culls backfaces.  Polygons only.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#include <assert.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "cull.h"
#include "util.h"
#include "vec.h"

#include <glcontext/glcontext.h>

void
__glcore_cull_primitives (GL_primitive_list *pl, GLcontext *g)
{
    if (g->polygon.cullface) {
	int cullfront = ((g->polygon.cullfacemode == GL_FRONT) ||
			 (g->polygon.cullfacemode == GL_FRONT_AND_BACK));
	int cullback = ((g->polygon.cullfacemode == GL_BACK) ||
			(g->polygon.cullfacemode == GL_FRONT_AND_BACK));
	int frontcw = (g->polygon.frontface == GL_CW);

	GLrenderstate *r = g->renderstate;
	GL_primitive *p = pl->head, *next;

	pl->head = NULL;
	pl->tail = NULL;

	for ( ; p; p = next) {
	    next = p->next;
	    if (p->nverts != 3) {
		__glcore_add_primitive(pl, p);
	    }
	    else {
		GL_procvert *v0 = p->verts[0];
		GL_procvert *v1 = p->verts[1];
		GL_procvert *v2 = p->verts[2];
		GL_float x0, y0, z0, w0;
		GL_float x1, y1, z1, w1;
		GL_float x2, y2, z2, w2;
		int ccw;
		int front;

		vunpack(v0->position, x0, y0, z0, w0);
		vunpack(v1->position, x1, y1, z1, w1);
		vunpack(v2->position, x2, y2, z2, w2);

                ccw = (w0 * (x1 * y2 - x2 * y1) +
                       w1 * (x2 * y0 - x0 * y2) +
                       w2 * (x0 * y1 - x1 * y0) >= 0.0f);

		p->front = front = (ccw ^ frontcw);

		if ((front && cullfront) || (!front && cullback))
		    __glcore_destroy_primitive(p);
		else
		    __glcore_add_primitive(pl, p);
	    }
	}
    }
}
