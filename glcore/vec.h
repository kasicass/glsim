/*
 *  vec.h
 *
 *  Vector/matrix routines.
 *
 *  Kekoa Proudfoot
 *  11/2/01
 */

#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#include "glcoretypes.h"

#ifdef WIN32
#pragma warning(disable : 4244)
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define lerp(a,b,f) ((a)+((b)-(a))*(f))
#define clamp(v,l,h) (max(l,min(v,h)))
#define ispow2(a) (((a)&((a)-1))==0)
#define log2int(a) __glcore_log2int(a)

#define vinit(v,x,y,z,w) do { (v)[0]=x;(v)[1]=y;(v)[2]=z;(v)[3]=w; } while(0)
#define vinit_vec(v,vec) vinit(v,(vec).x,(vec).y,(vec).z,(vec).w)
#define vinit_col(v,col) vinit(v,(col).r,(col).g,(col).b,(col).a)
#define vinit_tex(v,tex) vinit(v,(tex).s,(tex).t,(tex).p,(tex).q)
#define vcopy(v,vec) vinit(v,(vec)[0],(vec)[1],(vec)[2],(vec)[3])
#define vunpack(v,x,y,z,w) do { x=(v)[0];y=(v)[1];z=(v)[2];w=(v)[3]; } while(0)

#define vadd(r,a,b) vinit(r,(a)[0]+(b)[0],(a)[1]+(b)[1],(a)[2]+(b)[2],(a)[3]+(b)[3])
#define vsub(r,a,b) vinit(r,(a)[0]-(b)[0],(a)[1]-(b)[1],(a)[2]-(b)[2],(a)[3]-(b)[3])
#define vmul(r,a,b) vinit(r,(a)[0]*(b)[0],(a)[1]*(b)[1],(a)[2]*(b)[2],(a)[3]*(b)[3])
#define vscale(r,v,s) vinit(r,(v)[0]*(s),(v)[1]*(s),(v)[2]*(s),(v)[3]*(s))
#define vdot(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2]+(a)[3]*(b)[3])
#define vinterp(v,a,b,f) vinit(v,lerp(a[0],b[0],f),lerp(a[1],b[1],f),lerp(a[2],b[2],f),lerp(a[3],b[3],f))
#define vclamp(v,a,l,h) vinit(v,clamp(a[0],l,h),clamp(a[1],l,h),clamp(a[2],l,h),clamp(a[3],l,h))
#define vlen(v) sqrt(vdot((v),(v)))
#define vnorm(v,a) do { GL_float s = 1.0f/vlen(a); vscale(v,a,s); } while(0)

#define vinit3(v,x,y,z) do { (v)[0]=x;(v)[1]=y;(v)[2]=z; } while(0)
#define vinit3_vec(v,vec) vinit3(v,(vec).x,(vec).y,(vec).z)
#define vinit3_col(v,col) vinit3(v,(col).r,(col).g,(col).b)
#define vcopy3(v,vec) vinit3(v,(vec)[0],(vec)[1],(vec)[2])
#define vadd3(r,a,b) vinit3(r,(a)[0]+(b)[0],(a)[1]+(b)[1],(a)[2]+(b)[2])
#define vsub3(r,a,b) vinit3(r,(a)[0]-(b)[0],(a)[1]-(b)[1],(a)[2]-(b)[2])
#define vmul3(r,a,b) vinit3(r,(a)[0]*(b)[0],(a)[1]*(b)[1],(a)[2]*(b)[2])
#define vscale3(r,v,s) vinit3(r,(v)[0]*(s),(v)[1]*(s),(v)[2]*(s))
#define vdot3(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define vlen3(v) sqrt(vdot3((v),(v)))
#define vnorm3(v,a) do { GL_float s=1.0f/vlen3(a); vscale3(v,a,s); } while(0)

#define minit(m,mat) do { \
                       vinit(m[0],(mat).m00,(mat).m10,(mat).m20,(mat).m30); \
                       vinit(m[1],(mat).m01,(mat).m11,(mat).m21,(mat).m31); \
                       vinit(m[2],(mat).m02,(mat).m12,(mat).m22,(mat).m32); \
                       vinit(m[3],(mat).m03,(mat).m13,(mat).m23,(mat).m33); \
                     } while (0)
#define mmult(m,l,r) __glcore_matrix_mult(m,l,r)
#define mmultv(r,m,v) vinit(r,vdot((m)[0],v),vdot((m)[1],v),vdot((m)[2],v),vdot((m)[3],v))
#define minvtrans(r,m) __glcore_matrix_inv_trans(r,m)

#define cftob(c) ((unsigned char)(255.0f * (c) + 0.5f))
#define cjoin(r,g,b,a) (((a)<<24)|((b)<<16)|((g)<<8)|((r)<<0))
#define cpack(v) (cjoin(cftob(v[0]),cftob(v[1]),cftob(v[2]),cftob(v[3])))

#define cbtof(c) ((c) * (1.0f / 255.0f))
#define cindex(c,i) (cbtof(((c)>>(8*i))&0xff))
#define cunpack(v,c) vinit(v,cindex(c,0),cindex(c,1),cindex(c,2),cindex(c,3))

int __glcore_log2int (unsigned int x);
void __glcore_matrix_mult (GL_float m[4][4], GL_float l[4][4], GL_float r[4][4]);
void __glcore_matrix_inv_trans (GL_float r[4][4], GL_float m[4][4]);

#endif /* VEC_H_INCLUDED */
