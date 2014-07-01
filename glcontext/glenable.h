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

#ifndef GLENABLE_H
#define GLENABLE_H

#include "gltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

GLEXPORT void GLSTATE_DECL __glstate_Enable (GLenum cap);
GLEXPORT void GLSTATE_DECL __glstate_Disable (GLenum cap);

#ifdef __cplusplus
}
#endif


#endif
