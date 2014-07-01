
#ifndef MYSTATE_H
#define MYSTATE_H


#include "gltypes.h"
#include "glconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	GLint a;
	GLint b;
} GLmystate;


void __glmystate_init (GLmystate *c, GLconfig *cfg);


#ifdef __cplusplus
}
#endif

#endif






