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

#ifndef GLERROR_H
#define GLERROR_H

#include "gltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

GLEXPORT int __glerror(int line, char *file, GLenum e, char *msg, ...);

#define UNIMPLEMENTED() __glerror(__LINE__, __FILE__, GL_NO_ERROR, "Unimplemented")

#ifdef __cplusplus
}
#endif

#endif



