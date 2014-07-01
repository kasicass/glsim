LIBRARY = glcontext

FILES = glbuffer glclient glconfig glcontext glcurrent \
        glenable glerror gleval glfog glhint glimaging \
	gllighting glline gllists glmisc glpixel glpolygon \
	glrasterpos glrect glselection glstencil gltexture \
	gltrans glviewport glmystate  \
	glcurrent_gen glget glisenabled


SLOP = glcurrent_gen.c glget.c glisenabled.c

include ../Makefile.common

glcurrent_gen.c: glcurrent.pl glcurrent_types.pl Makefile
	@echo "Creating glcurrent_gen.c ..."
	@perl glcurrent.pl > glcurrent_gen.c

glget.c: glget.txt glget.pl Makefile
	@echo "Creating glget.c ..."
	@perl glget.pl < glget.txt > glget.c

glisenabled.c: glisenabled.txt glisenabled.pl Makefile
	@echo "Creating glisenabled.c ..."
	@perl glisenabled.pl < glisenabled.txt > glisenabled.c

