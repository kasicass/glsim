/*
 *  rasterize.h
 *
 *  Header file for routines to scan convert primitives.
 *
 *  Kekoa Proudfoot
 *  11/5/01
 */

#ifndef RASTERIZE_H_DEFINED
#define RASTERIZE_H_DEFINED

#include "glcoretypes.h"
#include <glcontext/glcontext.h>

void __glcore_rasterize_primitives (GL_primitive_list *pl, GLcontext *g);

#endif /* RASTERIZE_H_DEFINED */



