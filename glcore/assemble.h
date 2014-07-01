/*
 *  assemble.h
 *
 *  Header file for primitive assembly code.
 *
 *  Kekoa Proudfoot
 *  11/4/01
 */

#ifndef ASSEMBLE_H_INCLUDED
#define ASSEMBLE_H_INCLUDED

#include "glcoretypes.h"
#include <glcontext/glcontext.h>

void __glcore_assemble_primitives (GL_primitive_list *p, GLcontext *g);

#endif /* ASSEMBLE_H_INCLUDED */
