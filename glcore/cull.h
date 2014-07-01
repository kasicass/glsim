/*
 *  cull.h
 *
 *  Header file for primitive culling routines.  Culls backfaces.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#ifndef CULL_H_DEFINED
#define CULL_H_DEFINED

#include "glcoretypes.h"
#include <glcontext/glcontext.h>

void __glcore_cull_primitives (GL_primitive_list *pl, GLcontext *g);

#endif /* CULL_H_DEFINED */
