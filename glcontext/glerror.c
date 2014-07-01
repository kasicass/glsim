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

#define ERRORMSG_GUI "An error was generated in the gl state manager:\n%s\nFile: %s\nLine: %d\nAbort: Normal GL error handling, \nRetry: Debug the program, \nIgnore: GL ignores the error."
#define ERRORMSG "An error was generated in the gl state manager:\n%s\nFile: %s\nLine: %d\n"

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <crtdbg.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "glcontext.h"
#include "glerror.h"

int __glerror(int line, char *file, GLenum e, char *msg, ...) {
	GLcontext *g = GetCurrentContext();
	char outtext[1024];
    va_list vl;

	va_start( vl, msg );
	vsprintf(outtext, msg, vl);
	va_end( vl );

#ifdef XXX
	/* _CrtDbgReport(_CRT_WARN, file, line, "", "__glerror"); */

	if ( __config->state_error_gui ) {
		char msgtext[1024];
		int ret;
		sprintf(msgtext, ERRORMSG_GUI, outtext, file, line);
		ret = MessageBox(NULL, msgtext, "GL_ERROR", MB_ABORTRETRYIGNORE | MB_ICONWARNING);
		switch (ret) {
		case IDRETRY:
			assert(0);
			return 1;
		case IDIGNORE:
			return 0;
		case IDABORT:
		default:
			break;
		}
	}
#endif

	fprintf( stderr, ERRORMSG, outtext, file, line );
	fprintf( stderr, "\n");
	fflush ( stderr);

	if (g && g->error == GL_NO_ERROR)
		g->error = e;
	return 1;
}
    
GLEXPORT GLenum GLSTATE_DECL
__glstate_GetError(void) {
	GLcontext *g = GetCurrentContext();
	GLenum ret = g->error;
	g->error = GL_NO_ERROR;
	return ret;
}
