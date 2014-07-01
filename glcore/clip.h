/*
 *  clip.h
 *
 *  Header file for primitive clipping routines.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#ifndef CLIP_H_INCLUDED
#define CLIP_H_INCLUDED

#include "glcoretypes.h"
#include <glcontext/glcontext.h>

void __glcore_clip_primitives (GL_primitive_list *pl, GLcontext *g);

#endif /* CLIP_H_INCLUDED */
