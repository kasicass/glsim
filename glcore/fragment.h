/*
 *  fragment.h
 *
 *  Header file for fragment processing routines.
 *
 *  Kekoa Proudfoot
 *  11/8/01
 */

#ifndef FRAGMENT_H_DEFINED
#define FRAGMENT_H_DEFINED

#include "glcoretypes.h"
#include <glcontext/glcontext.h>

void __glcore_process_fragments (GLcontext *g, int n, GL_fragment *f);

#endif /* FRAGMENT_H_DEFINED */
