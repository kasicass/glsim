/*
 *  glcoretypes.h
 *
 *  Internal glcore types.
 *
 *  Kekoa Proudfoot
 *  11/2/01
 */

#ifndef GLCORETYPES_H_INCLUDED
#define GLCORETYPES_H_INCLUDED

#include "glcore.h"

/* Internal types */

typedef unsigned char GL_bool;
typedef float GL_float;

typedef struct GL_material {
    GL_float ambient[4];
    GL_float diffuse[4];
    GL_float specular[4];
    GL_float emission[4];
    GL_float shininess;
} GL_material;

typedef struct GL_vertex {
    GL_float position[4];
    GL_float color[4];
    GL_float texcoord[4];
    GL_float normal[4];
    GL_material frontmaterial;
    GL_material backmaterial;
} GL_vertex;

typedef struct GL_processed_vertex {
    GL_float position[4];
    GL_float eyeposition[4];
    GL_float frontcolor[4];
    GL_float backcolor[4];
    GL_float texcoord[4];
    /* windowpos computed during project */
    GL_float windowpos[4];
} GL_procvert;

typedef struct GL_primitive {
    struct GL_primitive *next;
    int nverts; /* 1 = point, 2 = line, 3 = triangle */
    GL_procvert *verts[3];
    int front;
} GL_primitive;

typedef struct GL_clipvert {
    struct GL_clipvert *next;
    GL_procvert procvert;
} GL_clipvert;

typedef struct GL_primitive_list {
    GL_primitive *head, *tail;
    GL_clipvert *clipverts;
} GL_primitive_list;

typedef struct GL_fragment {
    /* interpolants generated during rasterization */
    unsigned short x, y;
    GL_float w0, w1;         /* barycentric weights */
    /* interpolants computed after rasterization */
    GL_float depth;
    GL_float color[4];
    GL_float texcoord[3];
    GL_float texcoorddx[3];
    GL_float texcoorddy[3];
} GL_fragment;

/* Hidden type definitions */

#define ASSEMBLE_START 0
#define ASSEMBLE_CONTINUE (1<<0)
#define ASSEMBLE_END (1<<1)

struct GLtextureobj;

struct GLrenderstate {
    int nverts;
    int lastvert;
    int maxverts;
    GL_vertex *verts;
    GL_procvert *procverts;
    int assembleflags;

    struct GLtextureobj *texobj;

    int numtris;
    int numfrags;
};

struct GLframebuffer {
    int width;
    int height;
    int isdouble;
    unsigned int *color[2];
    float *depth;
    GLDrawFunc drawfunc;
    GLSyncFunc syncfunc;
};

#endif /* GLCORETYPES_H_INCLUDED */
