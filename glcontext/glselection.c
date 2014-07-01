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

#include "glcontext.h"
#include "glerror.h"

void
__glselection_initbits (GLselectionbits *s, GLconfig *cfg) {
	/* Unimplemented */
	UNUSED(s);
	UNUSED(cfg);
}

void
__glselection_switch (GLselectionbits *s, GLbitvalue b,
					   GLselectionstate *c, GLselectionstate *t) {
	/* Unimplemented */
	UNUSED(s);
	UNUSED(b);
	UNUSED(c);
	UNUSED(t);
}

void
__glselection_sync (GLselectionbits *s, GLbitvalue b,
					   GLselectionstate *c, GLselectionstate *t) {
	/* Unimplemented */
	UNUSED(s);
	UNUSED(b);
	UNUSED(c);
	UNUSED(t);
}

void
__glselection_init (GLselectionstate *s, GLconfig *c) {
	s->maxnamestackdepth = c->maxnamestackdepth;
}

void
__glselection_destroy (GLselectionstate *s) {
	/* do nothing */
	UNUSED(s);
}
