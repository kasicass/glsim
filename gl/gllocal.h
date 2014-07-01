
#ifndef GLLOCAL_H
#define GLLOCAL_H

#include "glcontext/glcontext.h"
#include "glcontext/glconfig.h"

#ifdef WIN32
#define FUNCAPI __stdcall
#else
#define FUNCAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

void __gllocal_doinit (void);
void __gllocal_InitFuncPtrs(void);
void __gllocal_SwapBuffers(void);
void __gllocal_MakeCurrent(struct GLframebuffer *, GLcontext *);

GLcontext *__gllocal_CreateContext(GLconfig *);
GLcontext *__gllocal_GetCurrentContext(void);

void FUNCAPI __gllocal_Rects(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
void FUNCAPI __gllocal_Recti(GLint x1, GLint y1, GLint x2, GLint y2);
void FUNCAPI __gllocal_Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
void FUNCAPI __gllocal_Rectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
void FUNCAPI __gllocal_Rectsv(const GLshort *v1, const GLshort *v2);
void FUNCAPI __gllocal_Rectiv(const GLint *v1, const GLint *v2);
void FUNCAPI __gllocal_Rectfv(const GLfloat *v1, const GLfloat *v2);
void FUNCAPI __gllocal_Rectdv(const GLdouble *v1, const GLdouble *v2);

void FUNCAPI __gllocal_Begin(GLenum mode);
void FUNCAPI __gllocal_End(void);

void FUNCAPI __gllocal_Finish(void);
void FUNCAPI __gllocal_Flush(void);

void FUNCAPI __gllocal_ArrayElement(GLint index);
void FUNCAPI __gllocal_DrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
void FUNCAPI __gllocal_DrawArrays  ( GLenum mode, GLint first, GLsizei count);

void FUNCAPI __gllocal_Clear(GLbitfield mask);

void FUNCAPI __gllocal_Vertex2d(GLdouble v1, GLdouble v2);
void FUNCAPI __gllocal_Vertex3d(GLdouble v1, GLdouble v2, GLdouble v3);
void FUNCAPI __gllocal_Vertex4d(GLdouble v1, GLdouble v2, GLdouble v3, GLdouble v4);
void FUNCAPI __gllocal_Vertex2i(GLint v1, GLint v2);
void FUNCAPI __gllocal_Vertex3i(GLint v1, GLint v2, GLint v3);
void FUNCAPI __gllocal_Vertex4i(GLint v1, GLint v2, GLint v3, GLint v4);
void FUNCAPI __gllocal_Vertex2s(GLshort v1, GLshort v2);
void FUNCAPI __gllocal_Vertex3s(GLshort v1, GLshort v2, GLshort v3);
void FUNCAPI __gllocal_Vertex4s(GLshort v1, GLshort v2, GLshort v3, GLshort v4);
void FUNCAPI __gllocal_Vertex2f(GLfloat v1, GLfloat v2);
void FUNCAPI __gllocal_Vertex3f(GLfloat v1, GLfloat v2, GLfloat v3);
void FUNCAPI __gllocal_Vertex4f(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);

void FUNCAPI __gllocal_Vertex2dv(const GLdouble *v);
void FUNCAPI __gllocal_Vertex3dv(const GLdouble *v);
void FUNCAPI __gllocal_Vertex4dv(const GLdouble *v);
void FUNCAPI __gllocal_Vertex2iv(const GLint *v);
void FUNCAPI __gllocal_Vertex3iv(const GLint *v);
void FUNCAPI __gllocal_Vertex4iv(const GLint *v);
void FUNCAPI __gllocal_Vertex2sv(const GLshort *v);
void FUNCAPI __gllocal_Vertex3sv(const GLshort *v);
void FUNCAPI __gllocal_Vertex4sv(const GLshort *v);
void FUNCAPI __gllocal_Vertex2fv(const GLfloat *v);
void FUNCAPI __gllocal_Vertex3fv(const GLfloat *v);
void FUNCAPI __gllocal_Vertex4fv(const GLfloat *v);




/* Unimplemented */
void FUNCAPI __gllocal_CopyPixels(void);
void FUNCAPI __gllocal_CopyTexImage1D(void);
void FUNCAPI __gllocal_CopyTexImage2D(void);
void FUNCAPI __gllocal_CopyTexSubImage1D(void);
void FUNCAPI __gllocal_CopyTexSubImage2D(void);
void FUNCAPI __gllocal_EvalCoord1d(void);
void FUNCAPI __gllocal_EvalCoord1dv(void);
void FUNCAPI __gllocal_EvalCoord1f(void);
void FUNCAPI __gllocal_EvalCoord1fv(void);
void FUNCAPI __gllocal_EvalCoord2d(void);
void FUNCAPI __gllocal_EvalCoord2dv(void);
void FUNCAPI __gllocal_EvalCoord2f(void);
void FUNCAPI __gllocal_EvalCoord2fv(void);
void FUNCAPI __gllocal_EvalMesh1(void);
void FUNCAPI __gllocal_EvalMesh2(void);
void FUNCAPI __gllocal_EvalPoint1(void);
void FUNCAPI __gllocal_EvalPoint2(void);
void FUNCAPI __gllocal_FeedbackBuffer(void);
void FUNCAPI __gllocal_SelectBuffer(void);
void FUNCAPI __gllocal_IsTexture(void);
void FUNCAPI __gllocal_InitNames(void);
void FUNCAPI __gllocal_LoadName(void);
void FUNCAPI __gllocal_PassThrough(void);
void FUNCAPI __gllocal_PopAttrib(void);
void FUNCAPI __gllocal_PopClientAttrib(void);
void FUNCAPI __gllocal_PopName(void);
void FUNCAPI __gllocal_PushAttrib(void);
void FUNCAPI __gllocal_PushClientAttrib(void);
void FUNCAPI __gllocal_PushName(void);
void FUNCAPI __gllocal_ReadPixels(void);
void FUNCAPI __gllocal_DrawPixels(void);
void FUNCAPI __gllocal_RenderMode(void);
void FUNCAPI __gllocal_CallLists(void);
void FUNCAPI __gllocal_CallList(void);
void FUNCAPI __gllocal_Bitmap(void);
void FUNCAPI __gllocal_Accum(void);


#ifdef __cplusplus
}
#endif



#endif

