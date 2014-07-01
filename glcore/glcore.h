/*
 *  glcore.h
 *
 *  Header file for core rendering interface.
 *
 */

#ifndef GLCORE_H_INCLUDED
#define GLCORE_H_INCLUDED

#include <glcontext/glcontext.h>

struct GLrenderstate;
struct GLframebuffer;

typedef struct GLrenderstate GLrenderstate;
typedef struct GLframebuffer GLframebuffer;

typedef void (*GLDrawFunc)(unsigned int *, int, int, int, int, int);
typedef void (*GLSyncFunc)(void);

GLrenderstate *__glcore_CreateContext (void);
void __glcore_DestroyContext (GLrenderstate *);

GLframebuffer *__glcore_CreateFrameBuffer (int, int, int, GLDrawFunc, GLSyncFunc);
void __glcore_ResizeFrameBuffer (GLframebuffer *, int, int);
void __glcore_DestroyFrameBuffer (GLframebuffer *);

void __glcore_Begin (GLcontext *g, GLenum mode);
void __glcore_End (GLcontext *g);
void __glcore_Vertex4f (GLcontext *g, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void __glcore_Flush (GLcontext *g);
void __glcore_Finish (GLcontext *g);

void __glcore_Clear (GLcontext *g, GLbitfield mask);
void __glcore_SwapBuffers (GLcontext *g);

#endif /* GLCORE_H_INCLUDED */
