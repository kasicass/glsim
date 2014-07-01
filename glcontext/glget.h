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

#ifndef GLGET_H
#define GLGET_H

#include "gltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

GLEXPORT void		GLSTATE_DECL __glstate_GetBooleanv( GLenum pname, GLboolean *params );
GLEXPORT void		GLSTATE_DECL __glstate_GetIntegerv( GLenum pname, GLint *params );
GLEXPORT void		GLSTATE_DECL __glstate_GetFloatv( GLenum pname, GLfloat *params );
GLEXPORT void		GLSTATE_DECL __glstate_GetDoublev( GLenum pname, GLdouble *params );
GLEXPORT GLboolean	GLSTATE_DECL __glstate_IsEnabled (GLenum pname);
GLEXPORT const GLubyte * GLSTATE_DECL __glstate_GetString (GLenum pname);

#ifdef __cplusplus
}
#endif

#endif

