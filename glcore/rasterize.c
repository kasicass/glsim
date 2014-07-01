/*
 *  rasterize.c
 *
 *  Routines to scan convert primitives.  Scan-converted primitives result
 *  in a stream of fragments.  This code invokes other code to process
 *  those fragments.
 *
 *  Kekoa Proudfoot
 *  11/5/01
 */

#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "glcore.h"
#include "glcoretypes.h"
#include "rasterize.h"
#include "fragment.h"
#include "util.h"
#include "vec.h"

#include <glcontext/glcontext.h>

static void
rasterize_point (GL_primitive *p, GLcontext *g)
{
    /* unimplemented */
}

static void
rasterize_line (GL_primitive *p, GLcontext *g)
{
    /* unimplemented */
}

#define getvals(vals,a,val) vinit3(vals,(a)[0]->val,(a)[1]->val,(a)[2]->val)
#define getprojvals(vals,a,val,w) do { getvals(vals,a,val); vmul3(vals,vals,w); } while (0)

static void
compute_triangle_interpolants (GL_primitive *p, GLcontext *g, int n,
			       GL_fragment *f)
{
    GL_float invw[3];
    GL_float depth[3];
    GL_float color[4][3];
    GL_float texcoord[4][3];
    GL_float texcoorddx[3][3];
    GL_float texcoorddy[3][3];

    int flat = (g->lighting.shademodel == GL_FLAT);
    int twoside = (g->lighting.lighting && g->lighting.lightmodeltwoside);
    int front = (!twoside || p->front);

    GL_procvert *colorverts[3];

    GL_float dx01, dx12;
    GL_float dy01, dy12;
    GL_float invarea;
    GL_float d01[4], d12[4];
    GL_float dx[4], dy[4];

    int i;    

    getvals(invw, p->verts, windowpos[3]);

    getvals(depth, p->verts, windowpos[2]);

    colorverts[0] = p->verts[0];
    colorverts[1] = p->verts[(flat) ? 0 : 1];
    colorverts[2] = p->verts[(flat) ? 0 : 2];

    if (front) {
	getvals(color[0], colorverts, frontcolor[0]);
	getvals(color[1], colorverts, frontcolor[1]);
	getvals(color[2], colorverts, frontcolor[2]);
	getvals(color[3], colorverts, frontcolor[3]);
    }
    else {
	getvals(color[0], colorverts, backcolor[0]);
	getvals(color[1], colorverts, backcolor[1]);
	getvals(color[2], colorverts, backcolor[2]);
	getvals(color[3], colorverts, backcolor[3]);
    }

    getprojvals(texcoord[0], p->verts, texcoord[0], invw);
    getprojvals(texcoord[1], p->verts, texcoord[1], invw);
    getprojvals(texcoord[2], p->verts, texcoord[2], invw);
    getprojvals(texcoord[3], p->verts, texcoord[3], invw);

    /* extra things needed to compute texture lod... */

    /* compute edge deltas */
    dx01 = p->verts[1]->windowpos[0] - p->verts[0]->windowpos[0];
    dx12 = p->verts[2]->windowpos[0] - p->verts[1]->windowpos[0];
    dy01 = p->verts[1]->windowpos[1] - p->verts[0]->windowpos[1];
    dy12 = p->verts[2]->windowpos[1] - p->verts[1]->windowpos[1];

    /* compute parallelogram area reciprocal */
    invarea = 1.0f / (dx01 * dy12 - dx12 * dy01);

    /* normalize edge deltas */
    dx01 *= invarea;
    dx12 *= invarea;
    dy01 *= invarea;
    dy12 *= invarea;

    /* compute x and y gradients */
    for (i = 0; i < 4; i++) {
	d01[i] = texcoord[i][1] - texcoord[i][0];
	d12[i] = texcoord[i][2] - texcoord[i][1];
	dx[i] = d01[i] * dy12 - d12[i] * dy01;
	dy[i] = d12[i] * dx01 - d01[i] * dx12;
    }

    /* compute s/q, t/q, r/q x and y gradient numerators */
    for (i = 0; i < 3; i++) {
	GL_float qdpdx[3];
	GL_float pdqdx[3];
	GL_float qdpdy[3];
	GL_float pdqdy[3];

	vscale3(qdpdx, texcoord[3], dx[i]);
	vscale3(pdqdx, texcoord[i], dx[3]);
	vsub3(texcoorddx[i], qdpdx, pdqdx);

	vscale3(qdpdy, texcoord[3], dy[i]);
	vscale3(pdqdy, texcoord[i], dy[3]);
	vsub3(texcoorddy[i], qdpdy, pdqdy);
    }

    for (i = 0; i < n; i++) {
	GL_float wts[3] = { f[i].w0, f[i].w1, 1.0f - f[i].w0 - f[i].w1 };
	/* GL_float w = 1.0f / vdot3(invw, wts); */

	f[i].depth = vdot3(depth, wts);
	f[i].color[0] = vdot3(color[0], wts);
	f[i].color[1] = vdot3(color[1], wts);
	f[i].color[2] = vdot3(color[2], wts);
	f[i].color[3] = vdot3(color[3], wts);
	if (g->renderstate->texobj) {
	    GL_float invq = 1.0f / vdot3(texcoord[3], wts);
	    GL_float invqsq = invq * invq;
	    f[i].texcoord[0] = vdot3(texcoord[0], wts) * invq;
	    f[i].texcoord[1] = vdot3(texcoord[1], wts) * invq;
	    f[i].texcoord[2] = vdot3(texcoord[2], wts) * invq;
	    f[i].texcoorddx[0] = vdot3(texcoorddx[0], wts) * invqsq;
	    f[i].texcoorddx[1] = vdot3(texcoorddx[1], wts) * invqsq;
	    f[i].texcoorddx[2] = vdot3(texcoorddx[2], wts) * invqsq;
	    f[i].texcoorddy[0] = vdot3(texcoorddy[0], wts) * invqsq;
	    f[i].texcoorddy[1] = vdot3(texcoorddy[1], wts) * invqsq;
	    f[i].texcoorddy[2] = vdot3(texcoorddy[2], wts) * invqsq;
	}
    }
}

#define vswap(a,b) do { GL_procvert *v=(a); (a)=(b); (b)=v; } while (0)

static void
rasterize_triangle (GL_primitive *p, GLcontext *g)
{
    GL_procvert *v0, *v1, *v2;
    GL_procvert *l, *m, *h;

    int xmin, xmax;
    int ymin, ymid, ymax;

    int sxmin, sxmax;
    int symin, symax;

    GL_float xl, xm, xh;
    GL_float yl, ym, yh;

    GL_float dxlm, dxmh, dxhl;
    GL_float dylm, dymh, dyhl;
    GL_float dxdylm, dxdymh, dxdyhl;
    GL_float area, invarea;

    GL_float dlm, dmh;

    GL_float a, rowa, dadx, dady;
    GL_float b, rowb, dbdx, dbdy;

    int i;

    GL_float ldxdy, rdxdy;
    GL_float lx, rx;
    GL_float frac;

    int ycur, ystop;
    int xcur, xstart, xstop;

    GL_fragment frags[4096];
    GL_fragment *frag = frags;

    int numfrags = 0;

    l = v0 = p->verts[0];
    m = v1 = p->verts[1];
    h = v2 = p->verts[2];

    /* sort vertices by y coordinate */
    if (l->windowpos[1] > m->windowpos[1]) vswap(l, m);
    if (m->windowpos[1] > h->windowpos[1]) vswap(m, h);
    if (l->windowpos[1] > m->windowpos[1]) vswap(l, m);    

    /* get x and y coordinates and offset */
    xl = l->windowpos[0] + 0.5f;
    xm = m->windowpos[0] + 0.5f;
    xh = h->windowpos[0] + 0.5f;
    yl = l->windowpos[1] + 0.5f;
    ym = m->windowpos[1] + 0.5f;
    yh = h->windowpos[1] + 0.5f;

    /* find rasterization bounding box and middle y */
    xmin = floor(min(min(xl, xm), xh));
    xmax = floor(max(max(xl, xm), xh));
    ymin = floor(yl);
    ymid = floor(ym);
    ymax = floor(yh);

    /* get scissor rectangle */
    __glcore_get_scissor_rect(g, &sxmin, &sxmax, &symin, &symax);

    /* bounding box with zero width or height? reject */
    /* if (xmin == xmax || ymin == ymax) return; */

    /* bounding box outside scissor rectangle? reject */
    /* if (xmin >= sxmax) return; */
    /* if (xmax <= sxmin) return; */
    /* if (ymin >= symax) return; */
    /* if (ymax <= symin) return; */

    /* adjust bounding box to scissor rectangle */
    xmin = max(xmin, sxmin);
    xmax = min(xmax, sxmax);
    ymin = max(ymin, symin);
    ymid = min(ymid, symax);
    ymax = min(ymax, symax);

    /* scissored bounding box with zero width or height? reject */
    if (xmin >= xmax || ymin >= ymax)
	return;

    /* compute edge deltas */
    dxlm = xm - xl;
    dxmh = xh - xm;
    dxhl = xl - xh;
    dylm = ym - yl;
    dymh = yh - ym;
    dyhl = yl - yh;

    /* compute parallelogram area */
    /* if area > 0, m to right of hl edge */
    area = dxlm * dymh - dxmh * dylm; 

    /* zero area? reject */
    if (area == 0.0f)
	return;

    /* compute edge slopes */
    dxdyhl = dxhl / dyhl;
    dxdylm = (ymin < ymid) ? dxlm / dylm : 0.0f;
    dxdymh = (ymid < ymax) ? dxmh / dymh : 0.0f;

    /* normalize lm and mh edge deltas */
    invarea = 1.0f / area;
    dxlm *= invarea;
    dxmh *= invarea;
    dylm *= invarea;
    dymh *= invarea;

    /* compute w0 gradients */
    dlm = (v0 == m) - (v0 == l);
    dmh = (v0 == h) - (v0 == m);
    rowa = (v0 == l);
    dadx = dlm * dymh - dmh * dylm;
    dady = dmh * dxlm - dlm * dxmh;

    /* compute w1 gradients */
    dlm = (v1 == m) - (v1 == l);
    dmh = (v1 == h) - (v1 == m);
    rowb = (v1 == l);
    dbdx = dlm * dymh - dmh * dylm;
    dbdy = dmh * dxlm - dlm * dxmh;

    /* process the bottom and top halves of the triangle */
    for (i = 0; i < 2; i++) {
	if (i == 0) {
	    /* start bottom half */
	    ycur = ymin;
	    ystop = ymid;
	    frac = 1.0f + ycur - yl;
	    if (area > 0.0f) {
		ldxdy = dxdyhl;
		rdxdy = dxdylm;
	    }
	    else {
		ldxdy = dxdylm;
		rdxdy = dxdyhl;
	    }
	    lx = xl + frac * ldxdy;
	    rx = xl + frac * rdxdy;
	    rowa = rowa + frac * dady;
	    rowb = rowb + frac * dbdy;
	}
	else {
	    /* start top half */
	    ycur = ymid;
	    ystop = ymax;
	    frac = 1.0f + ycur - ym;
	    if (area > 0.0f) {
		rdxdy = dxdymh;
		rx = xm + frac * rdxdy;
	    }
	    else {
		ldxdy = dxdymh;
		lx = xm + frac * ldxdy;
	    }
	}
	/* process current half */
	for ( ; ycur < ystop; ycur++, lx += ldxdy, rx += rdxdy,
		              rowa += dady, rowb += dbdy) {
	    
	    /* find scanline limits */
	    xstart = max(floor(lx), xmin);
	    xstop = min(floor(rx), xmax);

	    /* find scanline fractional offset */
	    frac = 1.0f + xstart - xl;

	    /* compute w0, w1 for first fragment */
	    a = rowa + frac * dadx;
	    b = rowb + frac * dbdx;

	    /* emit fragments */
	    for (xcur = xstart; xcur < xstop; xcur++) {
		if (frag - frags == (sizeof(frags) / sizeof(frags[0]))) {
		    compute_triangle_interpolants(p, g, frag - frags, frags);
		    __glcore_process_fragments(g, frag - frags, frags);
		    numfrags += frag - frags;
		    frag = frags;
		}

		frag->x = xcur;
		frag->y = ycur;
		frag->w0 = a;
		frag->w1 = b;

		frag++;

		a += dadx;
		b += dbdx;
	    }
	}
    }

    compute_triangle_interpolants(p, g, frag - frags, frags);
    __glcore_process_fragments(g, frag - frags, frags);
    numfrags += frag - frags;

    g->renderstate->numtris++;
    g->renderstate->numfrags += numfrags;
}

void
__glcore_rasterize_primitives (GL_primitive_list *pl, GLcontext *g)
{
    GLrenderstate *r = g->renderstate;
    GL_primitive *p;

    for (p = pl->head; p; p = p->next) {
	switch (p->nverts) {
	case 1: rasterize_point(p, g); break;
	case 2: rasterize_line(p, g); break;
	case 3: rasterize_triangle(p, g); break;
	}
    }
}

