/*
 *  assemble.c
 *
 *  Primitive assembly routines.  Assembles vertices into primitives.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#include <assert.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "assemble.h"
#include "util.h"

#include <glcontext/glcontext.h>

void
__glcore_assemble_primitives (GL_primitive_list *p, GLcontext *g)
{
    GLrenderstate *r = g->renderstate;
    GL_procvert *v = r->procverts;
    int i;

    p->head = NULL;
    p->tail = NULL;

    switch (g->current.mode) {
    case GL_POINTS:
	for (i = 0; i < r->nverts; i++)
	    __glcore_add_new_primitive(p, 1, &v[i], NULL, NULL);
	break;
    case GL_LINES:
	for (i = 1; i < r->nverts; i += 2)
	    __glcore_add_new_primitive(p, 2, &v[i], &v[i-1], NULL);
	break;
    case GL_LINE_LOOP:
	i = (r->assembleflags & ASSEMBLE_CONTINUE) ? 2 : 1;
	for ( ; i < r->nverts; i++)
	    __glcore_add_new_primitive(p, 2, &v[i], &v[i-1], NULL);
	if (r->assembleflags & ASSEMBLE_END)
	    __glcore_add_new_primitive(p, 2, &v[0], &v[i-1], NULL);
	break;
    case GL_LINE_STRIP:
	for (i = 1; i < r->nverts; i++)
	    __glcore_add_new_primitive(p, 2, &v[i], &v[i-1], NULL);
	break;
    case GL_TRIANGLES:
	for (i = 2; i < r->nverts; i += 3)
	    __glcore_add_new_primitive(p, 3, &v[i], &v[i-2], &v[i-1]);
	break;
    case GL_TRIANGLE_STRIP:
	for (i = 2; i < r->nverts; i++) {
	    if (i % 2 == 0)
		__glcore_add_new_primitive(p, 3, &v[i], &v[i-2], &v[i-1]);
	    else
		__glcore_add_new_primitive(p, 3, &v[i], &v[i-1], &v[i-2]);
	}
	break;
    case GL_TRIANGLE_FAN:
	for (i = 2; i < r->nverts; i += 1)
	    __glcore_add_new_primitive(p, 3, &v[i], &v[0], &v[i-1]);
	break;
    case GL_QUADS:
	for (i = 3; i < r->nverts; i += 4) {
	    __glcore_add_new_primitive(p, 3, &v[i], &v[i-3], &v[i-2]);
	    __glcore_add_new_primitive(p, 3, &v[i], &v[i-2], &v[i-1]);
	}
	break;
    case GL_QUAD_STRIP:
	for (i = 3; i < r->nverts; i += 2) {
	    __glcore_add_new_primitive(p, 3, &v[i], &v[i-3], &v[i-2]);
	    __glcore_add_new_primitive(p, 3, &v[i], &v[i-1], &v[i-3]);
	}
	break;
    case GL_POLYGON:
	for (i = 2; i < r->nverts; i++)
	    __glcore_add_new_primitive(p, 3, &v[0], &v[i-1], &v[i]);
	break;
    }      
}
