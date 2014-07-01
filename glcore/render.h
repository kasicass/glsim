/*
 *  render.h
 *
 *  Header file for top-level rendering code.
 *
 *  Kekoa Proudfoot
 *  11/3/01
 */

#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <glcontext/glcontext.h>

void __glcore_render_verts (GLcontext *g); /* render vert buffer, finish */
void __glcore_break_verts (GLcontext *g); /* render vert buffer, continue */

#endif /* RENDER_H_INCLUDED */
