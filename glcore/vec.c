/*
 *  vec.c
 *
 *  Vector/matrix routines.
 *
 *  Kekoa Proudfoot
 *  11/3/01
 */

#include <stdio.h>

#include "vec.h"

#define EXPONENT_SHIFT 23
#define EXPONENT_BIAS 127

int
__glcore_log2int (unsigned int x)
{
    float r = x;
    return ((*(unsigned int *)&r) >> EXPONENT_SHIFT) - EXPONENT_BIAS;
}

void
__glcore_matrix_mult (GL_float m[4][4], GL_float l[4][4], GL_float r[4][4])
{
    GL_float l00 = l[0][0], l01 = l[0][1], l02 = l[0][2], l03 = l[0][3];
    GL_float l10 = l[1][0], l11 = l[1][1], l12 = l[1][2], l13 = l[1][3];
    GL_float l20 = l[2][0], l21 = l[2][1], l22 = l[2][2], l23 = l[2][3];
    GL_float l30 = l[3][0], l31 = l[3][1], l32 = l[3][2], l33 = l[3][3];
    GL_float r00 = r[0][0], r01 = r[0][1], r02 = r[0][2], r03 = r[0][3];
    GL_float r10 = r[1][0], r11 = r[1][1], r12 = r[1][2], r13 = r[1][3];
    GL_float r20 = r[2][0], r21 = r[2][1], r22 = r[2][2], r23 = r[2][3];
    GL_float r30 = r[3][0], r31 = r[3][1], r32 = r[3][2], r33 = r[3][3];
 
    m[0][0] = l00 * r00 + l01 * r10 + l02 * r20 + l03 * r30;
    m[0][1] = l00 * r01 + l01 * r11 + l02 * r21 + l03 * r31;
    m[0][2] = l00 * r02 + l01 * r12 + l02 * r22 + l03 * r32;
    m[0][3] = l00 * r03 + l01 * r13 + l02 * r23 + l03 * r33;
    m[1][0] = l10 * r00 + l11 * r10 + l12 * r20 + l13 * r30;
    m[1][1] = l10 * r01 + l11 * r11 + l12 * r21 + l13 * r31;
    m[1][2] = l10 * r02 + l11 * r12 + l12 * r22 + l13 * r32;
    m[1][3] = l10 * r03 + l11 * r13 + l12 * r23 + l13 * r33;
    m[2][0] = l20 * r00 + l21 * r10 + l22 * r20 + l23 * r30;
    m[2][1] = l20 * r01 + l21 * r11 + l22 * r21 + l23 * r31;
    m[2][2] = l20 * r02 + l21 * r12 + l22 * r22 + l23 * r32;
    m[2][3] = l20 * r03 + l21 * r13 + l22 * r23 + l23 * r33;
    m[3][0] = l30 * r00 + l31 * r10 + l32 * r20 + l33 * r30;
    m[3][1] = l30 * r01 + l31 * r11 + l32 * r21 + l33 * r31;
    m[3][2] = l30 * r02 + l31 * r12 + l32 * r22 + l33 * r32;
    m[3][3] = l30 * r03 + l31 * r13 + l32 * r23 + l33 * r33;
}

void
__glcore_matrix_inv_trans (GL_float r[4][4], GL_float m[4][4])
{
    GL_float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
    GL_float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
    GL_float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
    GL_float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

#define det33(a1,a2,a3,b1,b2,b3,c1,c2,c3) \
    (a1*(b2*c3-b3*c2) + b1*(c2*a3-a2*c3) + c1*(a2*b3-a3*b2))

    GL_float cof00 =  det33(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    GL_float cof01 = -det33(m12, m13, m10, m22, m23, m20, m32, m33, m30);
    GL_float cof02 =  det33(m13, m10, m11, m23, m20, m21, m33, m30, m31);
    GL_float cof03 = -det33(m10, m11, m12, m20, m21, m22, m30, m31, m32);
    GL_float cof10 = -det33(m21, m22, m23, m31, m32, m33, m01, m02, m03);
    GL_float cof11 =  det33(m22, m23, m20, m32, m33, m30, m02, m03, m00);
    GL_float cof12 = -det33(m23, m20, m21, m33, m30, m31, m03, m00, m01);
    GL_float cof13 =  det33(m20, m21, m22, m30, m31, m32, m00, m01, m02);
    GL_float cof20 =  det33(m31, m32, m33, m01, m02, m03, m11, m12, m13);
    GL_float cof21 = -det33(m32, m33, m30, m02, m03, m00, m12, m13, m10);
    GL_float cof22 =  det33(m33, m30, m31, m03, m00, m01, m13, m10, m11);
    GL_float cof23 = -det33(m30, m31, m32, m00, m01, m02, m10, m11, m12);
    GL_float cof30 = -det33(m01, m02, m03, m11, m12, m13, m21, m22, m23);
    GL_float cof31 =  det33(m02, m03, m00, m12, m13, m10, m22, m23, m20);
    GL_float cof32 = -det33(m03, m00, m01, m13, m10, m11, m23, m20, m21);
    GL_float cof33 =  det33(m00, m01, m02, m10, m11, m12, m20, m21, m22);

#undef det33

    GL_float det0  = m30 * cof30 + m31 * cof31 + m32 * cof32 + m33 * cof33;
    GL_float inv0  = (det0 == 0.0f) ? 0.0f : 1.0f / det0;

    r[0][0] = cof00 * inv0;
    r[0][1] = cof01 * inv0;
    r[0][2] = cof02 * inv0;
    r[0][3] = cof03 * inv0;
     	   	   
    r[1][0] = cof10 * inv0;
    r[1][1] = cof11 * inv0;
    r[1][2] = cof12 * inv0;
    r[1][3] = cof13 * inv0;
     	   	   
    r[2][0] = cof20 * inv0;
    r[2][1] = cof21 * inv0;
    r[2][2] = cof22 * inv0;
    r[2][3] = cof23 * inv0;
     	   	   
    r[3][0] = cof30 * inv0;
    r[3][1] = cof31 * inv0;
    r[3][2] = cof32 * inv0;
    r[3][3] = cof33 * inv0;
}
