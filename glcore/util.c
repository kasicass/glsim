/*
 *  util.c
 *
 *  Miscellaneous utility routines.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "util.h"
#include "vec.h"

/* Primitives, clip vertices, and primitive lists */

static GL_primitive *
init_primitive (GL_primitive *p, int nverts, GL_procvert *v0, GL_procvert *v1,
		GL_procvert *v2)
{
    p->next = NULL;
    p->nverts = nverts;
    p->verts[0] = v0;
    p->verts[1] = v1;
    p->verts[2] = v2;
    return p;
}

static GL_primitive *
create_primitive (int nverts, GL_procvert *v0, GL_procvert *v1,
		  GL_procvert *v2)
{
    GL_primitive *p = (GL_primitive *)malloc(sizeof(GL_primitive));
    init_primitive(p, nverts, v0, v1, v2);
    return p;
}

void
__glcore_add_primitive (GL_primitive_list *l, GL_primitive *p)
{
    if (l->tail)
	l->tail->next = p;
    else
	l->head = p;
    l->tail = p;
    p->next = NULL;
}

void
__glcore_add_new_primitive (GL_primitive_list *l, int nverts, GL_procvert *v0,
			    GL_procvert *v1, GL_procvert *v2)
{
    __glcore_add_primitive(l, create_primitive(nverts, v0, v1, v2));
}

void
__glcore_set_and_add_primitive (GL_primitive_list *l, GL_primitive *p,
				int nverts, GL_procvert *v0, GL_procvert *v1,
				GL_procvert *v2)
{
    __glcore_add_primitive(l, init_primitive(p, nverts, v0, v1, v2));
}

void
__glcore_destroy_primitive (GL_primitive *p)
{
    free(p);
}

GL_clipvert *
__glcore_create_clipvert (void)
{
    return (GL_clipvert *)malloc(sizeof(GL_clipvert));
}

void
__glcore_destroy_clipvert (GL_clipvert *v)
{
    free(v);
}


void
__glcore_add_clipvert (GL_primitive_list *l, GL_clipvert *v)
{
    v->next = l->clipverts;
    l->clipverts = v;
}

void
__glcore_destroy_primitive_list_items (GL_primitive_list *l)
{
    GL_primitive *p, *nextp;
    GL_clipvert *v, *nextv;

    for (p = l->head; p; p = nextp) {
	nextp = p->next;
	__glcore_destroy_primitive(p);
    }
    for (v = l->clipverts; v; v = nextv) {
	nextv = v->next;
	__glcore_destroy_clipvert(v);
    }
}

void
__glcore_dump_primitives (GL_primitive_list *pl)
{
    GL_primitive *p;
    char *names[] = { "", "Point", "Line", "Triangle" };
    for (p = pl->head; p; p = p->next) {
	int i;
	fprintf(stderr, "%s\n", names[p->nverts]);
	for (i = 0; i < p->nverts; i++) {
	    fprintf(stderr, "%6.3f %6.3f %6.3f %6.3f\n",
		    p->verts[i]->position[0],
		    p->verts[i]->position[1],
		    p->verts[i]->position[2],
		    p->verts[i]->position[3]);
	}
    }
}

/* State querying */

void
__glcore_get_scissor_rect (GLcontext *g, int *x0, int *x1, int *y0, int *y1)
{
    int xmin = 0;
    int xmax = g->framebuffer->width;
    int ymin = 0;
    int ymax = g->framebuffer->height;

    if (g->viewport.scissortest) {
	xmin = max(xmin, g->viewport.s_x);
	xmax = min(xmax, g->viewport.s_x + g->viewport.s_w);
	ymin = max(ymin, g->viewport.s_y);
	ymax = min(ymax, g->viewport.s_y + g->viewport.s_h);
    }

    *x0 = xmin;
    *x1 = xmax;
    *y0 = ymin;
    *y1 = ymax;
}

#define do_front_left(x) (((x) == GL_FRONT) || \
                          ((x) == GL_FRONT_LEFT) || \
		          ((x) == GL_FRONT_AND_BACK))
#define do_back_left(x) (((x) == GL_BACK) || \
                         ((x) == GL_BACK_LEFT) || \
		         ((x) == GL_FRONT_AND_BACK))

int
__glcore_draw_buffer_front_left (GLcontext *g)
{
    return do_front_left(g->buffer.drawbuffer);
}

int
__glcore_draw_buffer_back_left (GLcontext *g)
{
    return do_back_left(g->buffer.drawbuffer);
}

static int
translate_format (int format)
{
    switch (format) {
    case 1: return GL_LUMINANCE;
    case 2: return GL_LUMINANCE_ALPHA;
    case 3: return GL_RGB;
    case 4: return GL_RGBA;
    }
    return format;
}

static int
check_texture_object (GLtextureobj *obj)
{
    int baselevel;
    int maxlevel;
    int border;
    int basew, baseh, based;

    assert(obj);

    baselevel = 0; /* obj->baselevel does not exist, use default */
    maxlevel = 1000; /* obj->maxlevel does not exist, use default */

    if (maxlevel < baselevel)
	return 0;

    assert(obj->level);

    border = obj->level[baselevel].border;

    basew = obj->level[baselevel].width - 2 * border;
    baseh = obj->level[baselevel].height - 2 * border;
    based = obj->level[baselevel].depth - 2 * border;

    assert(ispow2(basew));
    assert(ispow2(baseh));
    assert(ispow2(based));

    if (basew == 0 || baseh == 0 || based == 0)
	return 0;

    assert(obj->level[baselevel].img);

    if ((obj->minfilter == GL_NEAREST_MIPMAP_NEAREST ||
	 obj->minfilter == GL_NEAREST_MIPMAP_LINEAR ||
	 obj->minfilter == GL_LINEAR_MIPMAP_NEAREST ||
	 obj->minfilter == GL_LINEAR_MIPMAP_LINEAR)) {

	int format = translate_format(obj->level[baselevel].components);
	int maxlog = log2int(max(basew,(max(baseh,based))));
	int level;

	maxlevel = min(baselevel + maxlog, maxlevel);

	for (level = baselevel + 1; level <= maxlevel; level++) {
	    if (basew > 1) basew >>= 1;
	    if (baseh > 1) baseh >>= 1;
	    if (based > 1) based >>= 1;
	    if (translate_format(obj->level[level].components) != format)
		return 0;
	    if (obj->level[level].border != border)
		return 0;
	    if (obj->level[level].width - 2 * border != basew)
		return 0;
	    if (obj->level[level].height - 2 * border != baseh)
		return 0;
	    if (obj->level[level].depth - 2 * border != based)
		return 0;
	    assert(obj->level[level].img);
	}

	obj->lastlevel = maxlevel;
    }
    else {
	obj->lastlevel = baselevel;
    }

    return 1;
}

static void
update_texture_info (GLtextureobj *obj)
{
    obj->valid = check_texture_object(obj);
    obj->dirty = 0;
}

void
__glcore_update_current_texture_info (GLcontext *g)
{
    GLtextureobj *texobj;

    if (g->texture.enabled3d)
	texobj = g->texture.currenttexture3d;
    else if (g->texture.enabled2d)
	texobj = g->texture.currenttexture2d;
    else if (g->texture.enabled1d)
	texobj = g->texture.currenttexture1d;
    else
	texobj = NULL;
    if (texobj && texobj->dirty)
	update_texture_info(texobj);
    g->renderstate->texobj = (texobj && texobj->valid) ? texobj : NULL;
}
