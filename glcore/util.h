/*
 *  util.h
 *
 *  Miscellaneous utility routines.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

#include "glcoretypes.h"
#include <glcontext/glcontext.h>

/* Primitives, clip vertices, and primitive lists */

void __glcore_add_primitive (GL_primitive_list *l, GL_primitive *p);
void __glcore_add_new_primitive (GL_primitive_list *l, int nverts, GL_procvert *v0, GL_procvert *v1, GL_procvert *v2);
void __glcore_set_and_add_primitive (GL_primitive_list *l, GL_primitive *p, int nverts, GL_procvert *v0, GL_procvert *v1, GL_procvert *v2);
void __glcore_destroy_primitive (GL_primitive *p);

GL_clipvert *__glcore_create_clipvert (void);
void __glcore_add_clipvert (GL_primitive_list *l, GL_clipvert *v);
void __glcore_destroy_clipvert (GL_clipvert *v);

void __glcore_destroy_primitive_list_items (GL_primitive_list *l);
void __glcore_dump_primitives (GL_primitive_list *l);

/* State querying */

void __glcore_get_scissor_rect (GLcontext *g, int *x0, int *x1, int *y0, int *y1);

int __glcore_draw_buffer_front_left (GLcontext *g);
int __glcore_draw_buffer_back_left (GLcontext *g);

void __glcore_update_current_texture_info (GLcontext *g);

#endif /* UTIL_H_DEFINED */

