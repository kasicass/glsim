/*
** 3/06/2001
** http://graphics.stanford.edu/software/wiregl
**
** Copyright 2001
** The Board of Trustees of The Leland Stanford Junior University.
** All rights reserved.
**
** Except for commercial resale, lease, license or other commercial
** transactions, permission is hereby given to use, copy, and/or
** modify this software, provided that the above copyright notice and
** this permission notice appear in all copies of this software.  No
** part of this software or any derivatives thereof may be used in
** graphics systems for resale or for use in a commercial product.
**
** This software is provided "as is" and without warranty of any kind,
** express, implied or otherwise, including without limitation, any
** warranty of merchantability or fitness for a particular purpose.
*/

#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "gltypes.h"
#include "glconfig.h"

#define GLTEXTURE_HASHSIZE 1047
#define GLTEXTURE_NAMEOFFSET 4

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLtextureid *GLtextureidptr;
struct GLtextureid {
	GLuint name;
	GLuint hwid;
	GLtextureidptr next;
};

typedef struct {
	GLubyte *img;
	int bytes;
	GLint width;
	GLint height;
	GLint depth;
	GLint components;
	GLint border;
	GLenum format;
	GLenum type;
	int	bytesperpixel;

	GLbitvalue dirty;
} GLtexturelevel;

typedef struct GLtextureobj GLtextureobj;
typedef struct GLtextureobj * GLtextureobjptr;
struct GLtextureobj {

	GLtexturelevel *level;
	
	GLcolorf	bordercolor;
	GLenum		target;
	GLuint		name;
	GLtextureobj *next;
	GLenum		minfilter, magfilter;
	GLenum		wraps, wrapt;

	GLbitvalue	dirty;
	GLbitvalue  paramsbit;
	GLbitvalue  imagebit;

	/* state used by glcore for rendering */
	GLboolean	valid;
	GLint		lastlevel;
};

typedef struct GLtexture_freeelem GLtexture_freeelem;
struct GLtexture_freeelem {
	GLuint min;
	GLuint max;
	GLtexture_freeelem *next;
	GLtexture_freeelem *prev;
};

typedef struct {
	GLbitvalue dirty;
	GLbitvalue enable;
	GLbitvalue current;
	GLbitvalue objgen;
	GLbitvalue eyegen;
	GLbitvalue envbit;
	GLbitvalue gen;
} GLtexturebits;

typedef struct {
	GLuint allocated;
	GLtextureobj *textures;

	GLtextureobj *firstfree;
	GLtextureobj *currenttexture1d;
	GLtextureobj *currenttexture2d;
	GLtextureobj *currenttexture3d;
	GLuint currenttexture1dname;
	GLuint currenttexture2dname;
	GLuint currenttexture3dname;

	GLenum		envmode;
	GLcolorf	envcolor;
	
	GLboolean	enabled1d;
	GLboolean	enabled2d;
	GLboolean	enabled3d;
	GLtexcoordb	texturegen;

	GLtextureobjptr mapping[GLTEXTURE_HASHSIZE];
	GLtexture_freeelem *freelist;
	GLtextureidptr hwidhash[GLTEXTURE_HASHSIZE];

	GLtextureobj base1d;
	GLtextureobj base2d;
	GLtextureobj base3d;
	
	GLint		maxtexturesize;
	GLint		max3dtexturesize;
	GLint		maxlevel;
	GLint		max3dlevel;

	/* Texture gen mode */
	GLvectorf	objscoeff;
	GLvectorf	objtcoeff;
	GLvectorf	objrcoeff;
	GLvectorf	objqcoeff;
	GLvectorf	eyescoeff;
	GLvectorf	eyetcoeff;
	GLvectorf	eyercoeff;
	GLvectorf	eyeqcoeff;
	GLtexcoorde	gen;
} GLtexturestate;

void __gltexture_initbits (GLtexturebits *t, GLconfig *c);

void __gltexture_init(GLtexturestate *t, GLconfig *c);
void __gltexture_destroy(GLtexturestate *t);
void __gltexture_sethwid(GLenum target, GLuint textureid, GLuint hwid);
GLuint __gltexture_gethwid(GLenum target, GLuint textureid);
void __gltexture_inittexture(GLuint name);
GLtextureobj *__gltexture_allocatetexture(GLuint name);
void __gltexture_deletetexture(GLuint name);
GLtextureobj * __gltexture_gettexture(GLuint textureid);
int __gltexture_getcurrenttexturesize(GLenum target, GLenum level);
const GLvoid * __gltexture_getcurrenttexturedata(GLenum target, GLenum level);

GLEXPORT void GLSTATE_DECL __glstate_GenTextures(GLsizei n, GLuint *textures);
GLEXPORT void GLSTATE_DECL __glstate_DeleteTextures(GLsizei n, GLuint *textures);
GLEXPORT void GLSTATE_DECL __glstate_BindTexture(GLenum target, GLuint texture);
GLEXPORT void GLSTATE_DECL __glstate_TexImage1D (GLenum target, GLint level, GLint components, 
							GLsizei width, GLint border, GLenum format,
							GLenum type, const GLvoid *pixels  );
GLEXPORT void GLSTATE_DECL __glstate_TexImage2D (GLenum target, GLint level, GLint components, 
							GLsizei width, GLsizei height, 
							GLint border, GLenum format,
							GLenum type, const GLvoid *pixels  );
GLEXPORT void GLSTATE_DECL __glstate_TexSubImage1D (GLenum target, GLint level, GLint xoffset, 
					  GLsizei width, GLenum format,
					  GLenum type, const GLvoid *pixels  );
GLEXPORT void GLSTATE_DECL __glstate_TexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, 
					  GLsizei width, GLsizei height,
					  GLenum format, GLenum type, const GLvoid *pixels  );
GLEXPORT void GLSTATE_DECL __glstate_TexImage3D (GLenum target, GLint level, GLint components, 
							GLsizei width, GLsizei height, GLsizei depth,
							GLint border, GLenum format,
							GLenum type, const GLvoid *pixels  );

GLEXPORT void GLSTATE_DECL __glstate_GetTexImage (GLenum target, GLint level, GLenum format,
						 GLenum type, GLvoid * pixels);


GLEXPORT void GLSTATE_DECL __glstate_TexParameteri (GLenum target, GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_TexParameterf (GLenum target, GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_TexParameteriv (GLenum target, GLenum pname, const GLint *param);
GLEXPORT void GLSTATE_DECL __glstate_TexParameterfv (GLenum target, GLenum pname, const GLfloat *param);

GLEXPORT void GLSTATE_DECL __glstate_GetTexParameteriv (GLenum target, GLenum pname, GLint *params);
GLEXPORT void GLSTATE_DECL __glstate_GetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
GLEXPORT void GLSTATE_DECL __glstate_GetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
GLEXPORT void GLSTATE_DECL __glstate_GetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);

GLEXPORT void GLSTATE_DECL __glstate_TexEnvf (GLenum target, GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_TexEnvi (GLenum target, GLenum pname, GLint param);
GLEXPORT void GLSTATE_DECL __glstate_TexEnvfv (GLenum target, GLenum pname, const GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_TexEnviv (GLenum target, GLenum pname, const GLint *param);
GLEXPORT void GLSTATE_DECL __glstate_GetTexEnvfv (GLenum target, GLenum pname, GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_GetTexEnviv (GLenum target, GLenum pname, GLint *param);

GLEXPORT void GLSTATE_DECL __glstate_TexGend (GLenum coord, GLenum pname, GLdouble param);
GLEXPORT void GLSTATE_DECL __glstate_TexGenf (GLenum coord, GLenum pname, GLfloat param);
GLEXPORT void GLSTATE_DECL __glstate_TexGeni (GLenum coord, GLenum pname, GLint param);

GLEXPORT void GLSTATE_DECL __glstate_TexGendv (GLenum coord, GLenum pname, const GLdouble *param);
GLEXPORT void GLSTATE_DECL __glstate_TexGenfv (GLenum coord, GLenum pname, const GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_TexGeniv (GLenum coord, GLenum pname, const GLint *param);

GLEXPORT void GLSTATE_DECL __glstate_GetTexGendv (GLenum coord, GLenum pname, GLdouble *param);
GLEXPORT void GLSTATE_DECL __glstate_GetTexGenfv (GLenum coord, GLenum pname, GLfloat *param);
GLEXPORT void GLSTATE_DECL __glstate_GetTexGeniv (GLenum coord, GLenum pname, GLint *param);

GLEXPORT GLboolean GLSTATE_DECL __glstate_AreTexturesResident(GLsizei /*n*/, GLuint * /*textures*/, GLboolean * /*residences*/);
GLEXPORT void GLSTATE_DECL __glstate_PrioritizeTextures (GLsizei n, GLuint * textures, GLclampf * priorities);

#ifdef __cplusplus
}
#endif

#endif
