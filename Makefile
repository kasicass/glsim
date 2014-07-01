

all: glcore glcontext gl

gl: gl/libglsim.so
glcore: glcore/libglcore.so
glcontext: glcontext/libglcontext.so

glcore/libglcore.so:
	@make -C glcore

glcontext/libglcontext.so:
	@make -C glcontext

gl/libglsim.so:
	@make -C gl

clean:
	@make -C glcore clean
	@make -C glcontext clean
	@make -C gl clean
