/*
 *  transform.c
 *
 *  Vertex transformation routines.  Transforms and lights vertices.
 *
 *  Kekoa Proudfoot
 *  11/3/01
 */

#include <assert.h>
#include <math.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "transform.h"
#include "vec.h"

#include <glcontext/glcontext.h>

static void
compute_lighting (GLcontext *g, GL_float color[4], GL_float position[4],
		  GL_float normal[3], GL_material *material)
{
    GL_float projpos[4];
    GL_float primary[4];
    GL_float secondary[4];
    GL_float ambient[3];
    GL_float diffuse[3] = { 0.0f, 0.0f, 0.0f };
    GL_float specular[3] = { 0.0f, 0.0f, 0.0f };
    GL_float temp[3];
    GL_float E[3];
    int i;

    /* projected position */
    if (position[3] == 0.0f) {
	if (position[3] < 0.0f)
	    vscale3(projpos, position, -1.0f);
	else
	    vcopy3(projpos, position);
	vnorm3(projpos, projpos);
    }
    else {
	GL_float scale = 1.0f / position[3];
	vscale3(projpos, position, scale);
    }

    /* global ambient */
    vinit3_col(ambient, g->lighting.lightmodelambient);

    /* eye vector */
    if (g->lighting.lightmodellocalviewer) {
	vscale3(E, projpos, -1.0f);
	vnorm3(E, E);
    }
    else {
	vinit3(E, 0.0f, 0.0f, 1.0f);
    }

    /* lights */
    for (i = 0; i < g->lighting.maxlights; i++) {
	GLlight *light = &g->lighting.light[i];

	if (light->enable) {
	    GL_float lightpos[4];
	    GL_float L[3], H[3];
	    GL_float kd, ks;
	    GL_float atten = 1.0f;
	    GL_float dist, distsq;

	    /* light position */
	    vinit_vec(lightpos, light->position);

	    /* light vector */
	    if (lightpos[3] == 0.0f) {
		if (lightpos[3] < 0.0f)
		    vscale3(L, lightpos, -1.0f);
		else
		    vcopy3(L, lightpos);
		vnorm3(L, L);
		if (position[3] == 0.0f) {
		    vsub3(L, L, projpos);
		    vnorm3(L, L);
		}
	    }
	    else {
		if (position[3] == 0.0f)
		    vscale3(L, projpos, -1.0f);
		else {
		    GL_float scale = 1.0f / lightpos[3];
		    vscale3(L, lightpos, scale);
		    vsub3(L, L, projpos);
		    distsq = vdot3(L, L);
		    dist = sqrt(distsq);
		    scale = 1.0f / dist;
		    vscale(L, L, scale);
		}
	    }

	    /* halfangle vector */
	    vadd3(H, L, E);
	    vnorm3(H, H);

	    /* diffuse reflection coefficient */
	    kd = vdot3(normal, L);
	    kd = max(kd, 0.0f);

	    /* specular reflection coefficient */
	    ks = vdot3(normal, H);
	    ks = max(ks, 0.0f);
	    ks = (kd > 0.0f) * pow(ks, material->shininess);

	    /* attenuation */
	    if (lightpos[3] != 0.0f) {
		GL_float ac = light->constantattenuation;
		GL_float al = light->linearattenuation;
		GL_float aq = light->quadraticattenuation;
		if (position[3] != 0.0f)
		    atten /= (ac + al * dist + aq * distsq);
		else if (al == 0.0f && aq == 0.0f)
		    atten /= ac;
		else
		    atten = 0.0f;
	    }

	    /* spot factor */
	    if (light->spotcutoff != 180.0f) {
		GL_float S[3], exponent, cutoffcos, anglecos;
		vinit3_vec(S, light->spotdirection);
		exponent = light->spotexponent;
		cutoffcos = cos(light->spotcutoff);
		anglecos = -vdot3(L, S);
		anglecos = max(anglecos, 0.0f);
		if (anglecos < cutoffcos)
		    atten *= pow(anglecos, exponent);
		else
		    atten = 0.0f;
	    }

	    /* accumulate ambient */
	    vinit3_col(temp, light->ambient);
	    vscale3(temp, temp, atten);
	    vadd3(ambient, ambient, temp);

	    /* accumulate diffuse */
	    vinit3_col(temp, light->diffuse);
	    vscale3(temp, temp, kd * atten);
	    vadd3(diffuse, diffuse, temp);

	    /* accumulate specular */
	    vinit3_col(temp, light->specular);
	    vscale3(temp, temp, ks * atten);
	    vadd3(specular, specular, temp);
	}
    }

    /* primary color */
    vcopy3(primary, material->emission);
    vmul3(ambient, ambient, material->ambient);
    vadd3(primary, primary, ambient);
    vmul3(diffuse, diffuse, material->diffuse);
    vadd3(primary, primary, diffuse);
    primary[3] = material->diffuse[3];

    /* secondary color */
    vmul3(secondary, specular, material->specular);
    secondary[3] = 0.0f;

    /* computer overall color, no separate specular */
    vadd(color, primary, secondary);
}

void
__glcore_transform_vertices (GLcontext *g)
{
    GLrenderstate *r = g->renderstate;
    GL_vertex *verts = r->verts;
    GL_procvert *procverts = r->procverts;
    int i;

    GL_float modelview[4][4];
    GL_float projection[4][4];
    GL_float texture[4][4];
    GL_float composite[4][4];
    GL_float invmodelview[4][4];

    minit(modelview, g->trans.modelview[g->trans.modelviewdepth]);
    minit(projection, g->trans.projection[g->trans.projectiondepth]);
    minit(texture, g->trans.texture[g->trans.texturedepth]);    
    mmult(composite, projection, modelview);
    minvtrans(invmodelview, modelview);

    for (i = 0; i < r->nverts; i++) {
	/* position */
	mmultv(procverts[i].position, composite, verts[i].position);

	/* eye position */
	mmultv(procverts[i].eyeposition, modelview, verts[i].position);

	/* color */
	if (g->lighting.lighting) {
	    GL_float objnormal[4];
	    GL_float normal[4];

	    /* object space normal */
	    vcopy(objnormal, verts[i].normal);
	    objnormal[3] = 0.0f;
	    if (verts[i].position[3] != 0.0f) {
		objnormal[3] = -vdot3(objnormal, verts[i].position);
		objnormal[3] /= verts[i].position[3];
	    }

	    /* eye space normal */
	    mmultv(normal, invmodelview, objnormal);
	    if (g->current.normalize)
		vnorm3(normal, normal);

	    /* front color */
	    compute_lighting(g, procverts[i].frontcolor,
			     procverts[i].eyeposition, normal,
			     &verts[i].frontmaterial);

	    /* back color */
	    if (g->lighting.lightmodeltwoside) {
		vscale(normal, normal, -1.0f);
		compute_lighting(g, procverts[i].backcolor,
				 procverts[i].eyeposition, normal,
				 &verts[i].backmaterial);
	    }
	}
	else {
	    vcopy(procverts[i].frontcolor, verts[i].color);
	    vcopy(procverts[i].backcolor, verts[i].color);
	}
	vclamp(procverts[i].frontcolor, procverts[i].frontcolor, 0.0f, 1.0f);
	vclamp(procverts[i].backcolor, procverts[i].backcolor, 0.0f, 1.0f);

	/* no texture coordinate generation */

	/* texture coords */
	mmultv(procverts[i].texcoord, texture, verts[i].texcoord);
    }
}
