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

#ifndef GLTYPES_H
#define GLTYPES_H

#include "glbase.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define GLSTATE_DECL __stdcall
#else 
#define GLSTATE_DECL
#endif

#ifdef WIN32
#ifdef GLCONTEXT_EXPORTS
#define GLEXPORT __declspec( dllexport )
#else
#define GLEXPORT __declspec( dllimport )
#endif
#else
#define GLEXPORT
#endif

/* 
**  GLdefault
**  This is the default internal 
**  size for internal formats
*/
typedef GLfloat GLdefault;
#define GL_DEFAULTTYPE_FLOAT
#define GL_DEFAULTTYPE GL_FLOAT

#define GL_MAXBYTE		(GLbyte)	0x7F
#define GL_MAXUBYTE		(GLubyte)	0xFF
#define GL_MAXSHORT		(GLshort)	0x7FFF
#define GL_MAXUSHORT	(GLushort)	0xFFFF
#define GL_MAXINT		(GLint)		0x7FFFFFFF
#define GL_MAXUINT		(GLuint)	0xFFFFFFFF
#define GL_MAXFLOAT		1.0f
#define GL_MAXDOUBLE	1.0

#define GLBITS_LENGTH 32
#define GLBITS_ONES 0xFFFFFFFF
typedef unsigned long GLbitvalue;

typedef struct {
	char *name;
	void (GLSTATE_DECL *func)();
} GLapi;

typedef struct {
	char *name;
	void (GLSTATE_DECL **func)();
} GLjumptable;

typedef struct {
	GLfloat x1, x2, y1, y2;
} GLrectf;

typedef struct {
	GLint x1, x2, y1, y2;
} GLrecti;

/*
** GLmatrix
*/
typedef struct {
	GLdefault m00, m01, m02, m03;
	GLdefault m10, m11, m12, m13;
	GLdefault m20, m21, m22, m23;
	GLdefault m30, m31, m32, m33;
} GLmatrix;

typedef struct {
	GLfloat m00, m01, m02, m03;
	GLfloat m10, m11, m12, m13;
	GLfloat m20, m21, m22, m23;
	GLfloat m30, m31, m32, m33;
} GLmatrixf;

typedef struct {
	GLdouble m00, m01, m02, m03;
	GLdouble m10, m11, m12, m13;
	GLdouble m20, m21, m22, m23;
	GLdouble m30, m31, m32, m33;
} GLmatrixd;

/*
** GLvector
*/
#define VECTORGUTS(type) \
	type x;\
	type y;\
	type z;\
	type w;

#define COLORGUTS(type) \
	type r;\
	type g;\
	type b;\
	type a;

#define TEXCOORDGUTS(type) \
	type s;\
	type t;\
	type p;\
	type q;

/* GLvector */
typedef struct {
VECTORGUTS(GLdefault)
} GLvector;

typedef struct {
VECTORGUTS(GLenum)
} GLvectore;

typedef struct {
VECTORGUTS(GLubyte)
} GLvectorub;

typedef struct {
VECTORGUTS(GLbyte)
} GLvectorb;

typedef struct {
VECTORGUTS(GLushort)
} GLvectorus;

typedef struct {
VECTORGUTS(GLshort)
} GLvectors;

typedef struct {
VECTORGUTS(GLint)
} GLvectori;

typedef struct {
VECTORGUTS(GLuint)
} GLvectorui;

typedef struct {
VECTORGUTS(GLfloat)
} GLvectorf;

typedef struct {
VECTORGUTS(GLdouble)
} GLvectord;

/* GLcolor */
typedef struct {
COLORGUTS(GLdefault)
} GLcolor;

typedef struct {
COLORGUTS(GLenum)
} GLcolore;

typedef struct {
COLORGUTS(GLubyte)
} GLcolorub;

typedef struct {
COLORGUTS(GLbyte)
} GLcolorb;

typedef struct {
COLORGUTS(GLushort)
} GLcolorus;

typedef struct {
COLORGUTS(GLshort)
} GLcolors;

typedef struct {
COLORGUTS(GLint)
} GLcolori;

typedef struct {
COLORGUTS(GLuint)
} GLcolorui;

typedef struct {
COLORGUTS(GLfloat)
} GLcolorf;

typedef struct {
COLORGUTS(GLdouble)
} GLcolord;

/* GLtexcoord */
typedef struct {
TEXCOORDGUTS(GLdefault)
} GLtexcoord;

typedef struct {
TEXCOORDGUTS(GLenum)
} GLtexcoorde;

typedef struct {
TEXCOORDGUTS(GLubyte)
} GLtexcoordub;

typedef struct {
TEXCOORDGUTS(GLbyte)
} GLtexcoordb;

typedef struct {
TEXCOORDGUTS(GLushort)
} GLtexcoordus;

typedef struct {
TEXCOORDGUTS(GLshort)
} GLtexcoords;

typedef struct {
TEXCOORDGUTS(GLint)
} GLtexcoordi;

typedef struct {
TEXCOORDGUTS(GLuint)
} GLtexcoordui;

typedef struct {
TEXCOORDGUTS(GLfloat)
} GLtexcoordf;

typedef struct {
TEXCOORDGUTS(GLdouble)
} GLtexcoordd;

#undef VECTORGUTS
#undef COLORGUTS
#undef TEXCOORDGUTS

#define COMPARE_VECTOR(a,b)		((a).x != (b).x || (a).y != (b).y || (a).z != (b).z || (a).w != (b).w)
#define COMPARE_TEXCOORD(a,b)	((a).s != (b).s || (a).t != (b).t || (a).p != (b).p || (a).q != (b).q)
#define COMPARE_COLOR(x,y)		((x).r != (y).r || (x).g != (y).g || (x).b != (y).b || (x).a != (y).a)


#ifdef __cplusplus
}
#endif

#endif
