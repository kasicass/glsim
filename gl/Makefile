LIBRARY = glsim
LIBRARIES = glcontext glcore

FILES = init misc rect unimplemented vertex funcapi exports glx myfunc

SLOP = exports.s funcapi.c funcptrs.h

PRECOMP += funcptrs.h

include ../Makefile.common

exports.s: exports_linux.pl openglapi.txt Makefile 
	@echo "Creating exports.s ..."
	@perl exports_linux.pl < openglapi.txt > exports.s

funcapi.c: funcapi.pl openglapi.txt localfuncs.txt Makefile
	@echo "Creating funcapi.c ..."
	@perl funcapi.pl < openglapi.txt > funcapi.c

funcptrs.h: funcptrs_h.pl openglapi.txt Makefile
	@echo "Creating funcptrs.h ..."
	@perl funcptrs_h.pl < openglapi.txt > funcptrs.h



