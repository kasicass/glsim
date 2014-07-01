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

#ifndef GLBASE_GL_H
#define GLBASE_GL_H

/* Avoid conflicts with gl.h */
#if !defined( __GL_H__ ) && !defined( GL_H ) && !defined(__gl_h_)

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

/*************************************************************/

/* Extensions */
/* Extensions */


#define GL_EXT_bgra                       1
#define GL_EXT_paletted_texture           1
#define GL_WIN_swap_hint                  1
#define GL_WIN_draw_range_elements        1
// #define GL_WIN_phong_shading              1
// #define GL_WIN_specular_fog               1

#define GL_VERSION_1_1                      1
#define GL_VERSION_1_2                      1
#define GL_EXT_abgr                         1
#define GL_EXT_blend_color                  1
#define GL_EXT_blend_logic_op               1
#define GL_EXT_blend_minmax                 1
#define GL_EXT_blend_subtract               1
#define GL_EXT_cmyka                        1
#define GL_EXT_convolution                  1
#define GL_EXT_copy_texture                 1
#define GL_EXT_histogram                    1
#define GL_EXT_packed_pixels                1
#define GL_EXT_polygon_offset               1
#define GL_EXT_rescale_normal               1
#define GL_EXT_subtexture                   1
#define GL_EXT_texture                      1
#define GL_EXT_texture3D                    1
#define GL_EXT_texture_object               1
#define GL_EXT_vertex_array                 1
#define GL_SGIS_detail_texture              1
#define GL_SGIS_fog_function                1
#define GL_SGIS_generate_mipmap             1
#define GL_SGIS_multisample                 1
#define GL_SGIS_point_line_texgen           1
#define GL_SGIS_point_parameters            1
#define GL_SGIS_sharpen_texture             1
#define GL_SGIS_texture4D                   1
#define GL_SGIS_texture_border_clamp        1
#define GL_SGIS_texture_edge_clamp          1
#define GL_SGIS_texture_filter4             1
#define GL_SGIS_texture_lod                 1
#define GL_SGIS_texture_select              1
#define GL_SGIX_calligraphic_fragment       1
#define GL_SGIX_clipmap                     1
#define GL_SGIX_depth_texture               1
#define GL_SGIX_flush_raster                1
#define GL_SGIX_fog_offset                  1
#define GL_SGIX_framezoom                   1
#define GL_SGIX_impact_pixel_texture        1
#define GL_SGIX_instruments                 1
#define GL_SGIX_interlace                   1
#define GL_SGIX_ir_instrument1              1
#define GL_SGIX_list_priority               1
#define GL_SGIX_pixel_texture               1
#define GL_SGIX_pixel_tiles                 1
#define GL_SGIX_polynomial_ffd              1
#define GL_SGIX_reference_plane             1
#define GL_SGIX_shadow                      1
#define GL_SGIX_shadow_ambient              1
#define GL_SGIX_sprite                      1
#define GL_SGIX_tag_sample_buffer           1
#define GL_SGIX_texture_add_env             1
#define GL_SGIX_texture_lod_bias            1
#define GL_SGIX_texture_multi_buffer        1
#define GL_SGIX_texture_scale_bias          1
#define GL_SGIX_ycrcb                       1
#define GL_SGI_color_matrix                 1
#define GL_SGI_color_table                  1
#define GL_SGI_fft                          1
#define GL_SGI_texture_color_table          1

/* AttribMask */
#define GL_CURRENT_BIT                      0x00000001
#define GL_POINT_BIT                        0x00000002
#define GL_LINE_BIT                         0x00000004
#define GL_POLYGON_BIT                      0x00000008
#define GL_POLYGON_STIPPLE_BIT              0x00000010
#define GL_PIXEL_MODE_BIT                   0x00000020
#define GL_LIGHTING_BIT                     0x00000040
#define GL_FOG_BIT                          0x00000080
#define GL_DEPTH_BUFFER_BIT                 0x00000100
#define GL_ACCUM_BUFFER_BIT                 0x00000200
#define GL_STENCIL_BUFFER_BIT               0x00000400
#define GL_VIEWPORT_BIT                     0x00000800
#define GL_TRANSFORM_BIT                    0x00001000
#define GL_ENABLE_BIT                       0x00002000
#define GL_COLOR_BUFFER_BIT                 0x00004000
#define GL_HINT_BIT                         0x00008000
#define GL_EVAL_BIT                         0x00010000
#define GL_LIST_BIT                         0x00020000
#define GL_TEXTURE_BIT                      0x00040000
#define GL_SCISSOR_BIT                      0x00080000
#define GL_ALL_ATTRIB_BITS                  0x000fffff
#define GL_MULTISAMPLE_BIT_EXT              0x20000000

/* ClearBufferMask */
/*      GL_COLOR_BUFFER_BIT */
/*      GL_ACCUM_BUFFER_BIT */
/*      GL_STENCIL_BUFFER_BIT */
/*      GL_DEPTH_BUFFER_BIT */

/* ClientAttribMask */
#define GL_CLIENT_PIXEL_STORE_BIT           0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT          0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS           0xFFFFFFFF

/* Boolean */
#define GL_FALSE                            0
#define GL_TRUE                             1

/* BeginMode */
#define GL_POINTS                           0x0000
#define GL_LINES                            0x0001
#define GL_LINE_LOOP                        0x0002
#define GL_LINE_STRIP                       0x0003
#define GL_TRIANGLES                        0x0004
#define GL_TRIANGLE_STRIP                   0x0005
#define GL_TRIANGLE_FAN                     0x0006
#define GL_QUADS                            0x0007
#define GL_QUAD_STRIP                       0x0008
#define GL_POLYGON                          0x0009

/* AccumOp */
#define GL_ACCUM                            0x0100
#define GL_LOAD                             0x0101
#define GL_RETURN                           0x0102
#define GL_MULT                             0x0103
#define GL_ADD                              0x0104

/* AlphaFunction */
#define GL_NEVER                            0x0200
#define GL_LESS                             0x0201
#define GL_EQUAL                            0x0202
#define GL_LEQUAL                           0x0203
#define GL_GREATER                          0x0204
#define GL_NOTEQUAL                         0x0205
#define GL_GEQUAL                           0x0206
#define GL_ALWAYS                           0x0207

/* BlendingFactorDest */
#define GL_ZERO                             0
#define GL_ONE                              1
#define GL_SRC_COLOR                        0x0300
#define GL_ONE_MINUS_SRC_COLOR              0x0301
#define GL_SRC_ALPHA                        0x0302
#define GL_ONE_MINUS_SRC_ALPHA              0x0303
#define GL_DST_ALPHA                        0x0304
#define GL_ONE_MINUS_DST_ALPHA              0x0305
/*      GL_CONSTANT_COLOR_EXT */
/*      GL_ONE_MINUS_CONSTANT_COLOR_EXT */
/*      GL_CONSTANT_ALPHA_EXT */
/*      GL_ONE_MINUS_CONSTANT_ALPHA_EXT */

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                        0x0306
#define GL_ONE_MINUS_DST_COLOR              0x0307
#define GL_SRC_ALPHA_SATURATE               0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */
/*      GL_CONSTANT_COLOR_EXT */
/*      GL_ONE_MINUS_CONSTANT_COLOR_EXT */
/*      GL_CONSTANT_ALPHA_EXT */
/*      GL_ONE_MINUS_CONSTANT_ALPHA_EXT */

/* BlendEquationModeEXT */
/*      GL_LOGIC_OP */
/*      GL_FUNC_ADD_EXT */
/*      GL_MIN_EXT */
/*      GL_MAX_EXT */
/*      GL_FUNC_SUBTRACT_EXT */
/*      GL_FUNC_REVERSE_SUBTRACT_EXT */

/* ColorMaterialFace */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* ColorMaterialParameter */
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */
/*      GL_EMISSION */
/*      GL_AMBIENT_AND_DIFFUSE */

/* ColorPointerType */
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* ColorTableParameterPNameSGI */
/*      GL_COLOR_TABLE_SCALE_SGI */
/*      GL_COLOR_TABLE_BIAS_SGI */

/* ColorTableTargetSGI */
/*      GL_COLOR_TABLE_SGI */
/*      GL_POST_CONVOLUTION_COLOR_TABLE_SGI */
/*      GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI */
/*      GL_PROXY_COLOR_TABLE_SGI */
/*      GL_PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI */
/*      GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI */
/*      GL_TEXTURE_COLOR_TABLE_SGI */
/*      GL_PROXY_TEXTURE_COLOR_TABLE_SGI */

/* ConvolutionBorderModeEXT */
/*      GL_REDUCE_EXT */

/* ConvolutionParameterEXT */
/*      GL_CONVOLUTION_BORDER_MODE_EXT */
/*      GL_CONVOLUTION_FILTER_SCALE_EXT */
/*      GL_CONVOLUTION_FILTER_BIAS_EXT */

/* ConvolutionTargetEXT */
/*      GL_CONVOLUTION_1D_EXT */
/*      GL_CONVOLUTION_2D_EXT */

/* CullFaceMode */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* DepthFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* DrawBufferMode */
#define GL_NONE                             0
#define GL_FRONT_LEFT                       0x0400
#define GL_FRONT_RIGHT                      0x0401
#define GL_BACK_LEFT                        0x0402
#define GL_BACK_RIGHT                       0x0403
#define GL_FRONT                            0x0404
#define GL_BACK                             0x0405
#define GL_LEFT                             0x0406
#define GL_RIGHT                            0x0407
#define GL_FRONT_AND_BACK                   0x0408
#define GL_AUX0                             0x0409
#define GL_AUX1                             0x040A
#define GL_AUX2                             0x040B
#define GL_AUX3                             0x040C

/* EnableCap */
/*      GL_FOG */
/*      GL_LIGHTING */
/*      GL_TEXTURE_1D */
/*      GL_TEXTURE_2D */
/*      GL_LINE_STIPPLE */
/*      GL_POLYGON_STIPPLE */
/*      GL_CULL_FACE */
/*      GL_ALPHA_TEST */
/*      GL_BLEND */
/*      GL_INDEX_LOGIC_OP */
/*      GL_COLOR_LOGIC_OP */
/*      GL_DITHER */
/*      GL_STENCIL_TEST */
/*      GL_DEPTH_TEST */
/*      GL_CLIP_PLANE0 */
/*      GL_CLIP_PLANE1 */
/*      GL_CLIP_PLANE2 */
/*      GL_CLIP_PLANE3 */
/*      GL_CLIP_PLANE4 */
/*      GL_CLIP_PLANE5 */
/*      GL_LIGHT0 */
/*      GL_LIGHT1 */
/*      GL_LIGHT2 */
/*      GL_LIGHT3 */
/*      GL_LIGHT4 */
/*      GL_LIGHT5 */
/*      GL_LIGHT6 */
/*      GL_LIGHT7 */
/*      GL_TEXTURE_GEN_S */
/*      GL_TEXTURE_GEN_T */
/*      GL_TEXTURE_GEN_R */
/*      GL_TEXTURE_GEN_Q */
/*      GL_MAP1_VERTEX_3 */
/*      GL_MAP1_VERTEX_4 */
/*      GL_MAP1_COLOR_4 */
/*      GL_MAP1_INDEX */
/*      GL_MAP1_NORMAL */
/*      GL_MAP1_TEXTURE_COORD_1 */
/*      GL_MAP1_TEXTURE_COORD_2 */
/*      GL_MAP1_TEXTURE_COORD_3 */
/*      GL_MAP1_TEXTURE_COORD_4 */
/*      GL_MAP2_VERTEX_3 */
/*      GL_MAP2_VERTEX_4 */
/*      GL_MAP2_COLOR_4 */
/*      GL_MAP2_INDEX */
/*      GL_MAP2_NORMAL */
/*      GL_MAP2_TEXTURE_COORD_1 */
/*      GL_MAP2_TEXTURE_COORD_2 */
/*      GL_MAP2_TEXTURE_COORD_3 */
/*      GL_MAP2_TEXTURE_COORD_4 */
/*      GL_POINT_SMOOTH */
/*      GL_LINE_SMOOTH */
/*      GL_POLYGON_SMOOTH */
/*      GL_SCISSOR_TEST */
/*      GL_COLOR_MATERIAL */
/*      GL_NORMALIZE */
/*      GL_AUTO_NORMAL */
/*      GL_POLYGON_OFFSET_POINT */
/*      GL_POLYGON_OFFSET_LINE */
/*      GL_POLYGON_OFFSET_FILL */
/*      GL_VERTEX_ARRAY */
/*      GL_NORMAL_ARRAY */
/*      GL_COLOR_ARRAY */
/*      GL_INDEX_ARRAY */
/*      GL_TEXTURE_COORD_ARRAY */
/*      GL_EDGE_FLAG_ARRAY */
/*      GL_CONVOLUTION_1D_EXT */
/*      GL_CONVOLUTION_2D_EXT */
/*      GL_SEPARABLE_2D_EXT */
/*      GL_HISTOGRAM_EXT */
/*      GL_MINMAX_EXT */
/*      GL_RESCALE_NORMAL_EXT */
/*      GL_TEXTURE_3D_EXT */
/*      GL_MULTISAMPLE_SGIS */
/*      GL_SAMPLE_ALPHA_TO_MASK_SGIS */
/*      GL_SAMPLE_ALPHA_TO_ONE_SGIS */
/*      GL_SAMPLE_MASK_SGIS */
/*      GL_TEXTURE_4D_SGIS */
/*      GL_CALLIGRAPHIC_FRAGMENT_SGIX */
/*      GL_FOG_OFFSET_SGIX */
/*      GL_FRAMEZOOM_SGIX */
/*      GL_INTERLACE_SGIX */
/*      GL_IR_INSTRUMENT1_SGIX */
/*      GL_PIXEL_TEX_GEN_SGIX */
/*      GL_REFERENCE_PLANE_SGIX */
/*      GL_SPRITE_SGIX */
/*      GL_COLOR_TABLE_SGI */
/*      GL_POST_CONVOLUTION_COLOR_TABLE_SGI */
/*      GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI */
/*      GL_TEXTURE_COLOR_TABLE_SGI */

/* ErrorCode */
#define GL_NO_ERROR                         0
#define GL_INVALID_ENUM                     0x0500
#define GL_INVALID_VALUE                    0x0501
#define GL_INVALID_OPERATION                0x0502
#define GL_STACK_OVERFLOW                   0x0503
#define GL_STACK_UNDERFLOW                  0x0504
#define GL_OUT_OF_MEMORY                    0x0505
/*      GL_TABLE_TOO_LARGE_EXT */
/*      GL_TEXTURE_TOO_LARGE_EXT */

/* FeedbackType */
#define GL_2D                               0x0600
#define GL_3D                               0x0601
#define GL_3D_COLOR                         0x0602
#define GL_3D_COLOR_TEXTURE                 0x0603
#define GL_4D_COLOR_TEXTURE                 0x0604

/* FeedBackToken */
#define GL_PASS_THROUGH_TOKEN               0x0700
#define GL_POINT_TOKEN                      0x0701
#define GL_LINE_TOKEN                       0x0702
#define GL_POLYGON_TOKEN                    0x0703
#define GL_BITMAP_TOKEN                     0x0704
#define GL_DRAW_PIXEL_TOKEN                 0x0705
#define GL_COPY_PIXEL_TOKEN                 0x0706
#define GL_LINE_RESET_TOKEN                 0x0707

/* FfdMaskSGIX */
#define GL_TEXTURE_DEFORMATION_BIT_SGIX     0x00000001
#define GL_GEOMETRY_DEFORMATION_BIT_SGIX    0x00000002

/* FfdTargetSGIX */
/*      GL_GEOMETRY_DEFORMATION_SGIX */
/*      GL_TEXTURE_DEFORMATION_SGIX */

/* FogMode */
/*      GL_LINEAR */
#define GL_EXP                              0x0800
#define GL_EXP2                             0x0801
/*      GL_FOG_FUNC_SGIS */

/* FogParameter */
/*      GL_FOG_COLOR */
/*      GL_FOG_DENSITY */
/*      GL_FOG_END */
/*      GL_FOG_INDEX */
/*      GL_FOG_MODE */
/*      GL_FOG_START */
/*      GL_FOG_OFFSET_VALUE_SGIX */

/* FrontFaceDirection */
#define GL_CW                               0x0900
#define GL_CCW                              0x0901

/* GetColorTableParameterPNameSGI */
/*      GL_COLOR_TABLE_SCALE_SGI */
/*      GL_COLOR_TABLE_BIAS_SGI */
/*      GL_COLOR_TABLE_FORMAT_SGI */
/*      GL_COLOR_TABLE_WIDTH_SGI */
/*      GL_COLOR_TABLE_RED_SIZE_SGI */
/*      GL_COLOR_TABLE_GREEN_SIZE_SGI */
/*      GL_COLOR_TABLE_BLUE_SIZE_SGI */
/*      GL_COLOR_TABLE_ALPHA_SIZE_SGI */
/*      GL_COLOR_TABLE_LUMINANCE_SIZE_SGI */
/*      GL_COLOR_TABLE_INTENSITY_SIZE_SGI */

/* GetConvolutionParameter */
/*      GL_CONVOLUTION_BORDER_MODE_EXT */
/*      GL_CONVOLUTION_FILTER_SCALE_EXT */
/*      GL_CONVOLUTION_FILTER_BIAS_EXT */
/*      GL_CONVOLUTION_FORMAT_EXT */
/*      GL_CONVOLUTION_WIDTH_EXT */
/*      GL_CONVOLUTION_HEIGHT_EXT */
/*      GL_MAX_CONVOLUTION_WIDTH_EXT */
/*      GL_MAX_CONVOLUTION_HEIGHT_EXT */

/* GetHistogramParameterPNameEXT */
/*      GL_HISTOGRAM_WIDTH_EXT */
/*      GL_HISTOGRAM_FORMAT_EXT */
/*      GL_HISTOGRAM_RED_SIZE_EXT */
/*      GL_HISTOGRAM_GREEN_SIZE_EXT */
/*      GL_HISTOGRAM_BLUE_SIZE_EXT */
/*      GL_HISTOGRAM_ALPHA_SIZE_EXT */
/*      GL_HISTOGRAM_LUMINANCE_SIZE_EXT */
/*      GL_HISTOGRAM_SINK_EXT */

/* GetMapQuery */
#define GL_COEFF                            0x0A00
#define GL_ORDER                            0x0A01
#define GL_DOMAIN                           0x0A02

/* GetMinmaxParameterPNameEXT */
/*      GL_MINMAX_FORMAT_EXT */
/*      GL_MINMAX_SINK_EXT */

/* GetPixelMap */
#define GL_PIXEL_MAP_I_TO_I                 0x0C70
#define GL_PIXEL_MAP_S_TO_S                 0x0C71
#define GL_PIXEL_MAP_I_TO_R                 0x0C72
#define GL_PIXEL_MAP_I_TO_G                 0x0C73
#define GL_PIXEL_MAP_I_TO_B                 0x0C74
#define GL_PIXEL_MAP_I_TO_A                 0x0C75
#define GL_PIXEL_MAP_R_TO_R                 0x0C76
#define GL_PIXEL_MAP_G_TO_G                 0x0C77
#define GL_PIXEL_MAP_B_TO_B                 0x0C78
#define GL_PIXEL_MAP_A_TO_A                 0x0C79

/* GetPointervPName */
#define GL_VERTEX_ARRAY_POINTER             0x808E
#define GL_NORMAL_ARRAY_POINTER             0x808F
#define GL_COLOR_ARRAY_POINTER              0x8090
#define GL_INDEX_ARRAY_POINTER              0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER      0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER          0x8093
/*      GL_INSTRUMENT_BUFFER_POINTER_SGIX */

/* GetPName */
#define GL_CURRENT_COLOR                    0x0B00
#define GL_CURRENT_INDEX                    0x0B01
#define GL_CURRENT_NORMAL                   0x0B02
#define GL_CURRENT_TEXTURE_COORDS           0x0B03
#define GL_CURRENT_RASTER_COLOR             0x0B04
#define GL_CURRENT_RASTER_INDEX             0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS    0x0B06
#define GL_CURRENT_RASTER_POSITION          0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID    0x0B08
#define GL_CURRENT_RASTER_DISTANCE          0x0B09
#define GL_POINT_SMOOTH                     0x0B10
#define GL_POINT_SIZE                       0x0B11
#define GL_POINT_SIZE_RANGE                 0x0B12
#define GL_POINT_SIZE_GRANULARITY           0x0B13
#define GL_LINE_SMOOTH                      0x0B20
#define GL_LINE_WIDTH                       0x0B21
#define GL_LINE_WIDTH_RANGE                 0x0B22
#define GL_LINE_WIDTH_GRANULARITY           0x0B23
#define GL_LINE_STIPPLE                     0x0B24
#define GL_LINE_STIPPLE_PATTERN             0x0B25
#define GL_LINE_STIPPLE_REPEAT              0x0B26
#define GL_LIST_MODE                        0x0B30
#define GL_MAX_LIST_NESTING                 0x0B31
#define GL_LIST_BASE                        0x0B32
#define GL_LIST_INDEX                       0x0B33
#define GL_POLYGON_MODE                     0x0B40
#define GL_POLYGON_SMOOTH                   0x0B41
#define GL_POLYGON_STIPPLE                  0x0B42
#define GL_EDGE_FLAG                        0x0B43
#define GL_CULL_FACE                        0x0B44
#define GL_CULL_FACE_MODE                   0x0B45
#define GL_FRONT_FACE                       0x0B46
#define GL_LIGHTING                         0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER         0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE             0x0B52
#define GL_LIGHT_MODEL_AMBIENT              0x0B53
#define GL_SHADE_MODEL                      0x0B54
#define GL_COLOR_MATERIAL_FACE              0x0B55
#define GL_COLOR_MATERIAL_PARAMETER         0x0B56
#define GL_COLOR_MATERIAL                   0x0B57
#define GL_FOG                              0x0B60
#define GL_FOG_INDEX                        0x0B61
#define GL_FOG_DENSITY                      0x0B62
#define GL_FOG_START                        0x0B63
#define GL_FOG_END                          0x0B64
#define GL_FOG_MODE                         0x0B65
#define GL_FOG_COLOR                        0x0B66
#define GL_DEPTH_RANGE                      0x0B70
#define GL_DEPTH_TEST                       0x0B71
#define GL_DEPTH_WRITEMASK                  0x0B72
#define GL_DEPTH_CLEAR_VALUE                0x0B73
#define GL_DEPTH_FUNC                       0x0B74
#define GL_ACCUM_CLEAR_VALUE                0x0B80
#define GL_STENCIL_TEST                     0x0B90
#define GL_STENCIL_CLEAR_VALUE              0x0B91
#define GL_STENCIL_FUNC                     0x0B92
#define GL_STENCIL_VALUE_MASK               0x0B93
#define GL_STENCIL_FAIL                     0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL          0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS          0x0B96
#define GL_STENCIL_REF                      0x0B97
#define GL_STENCIL_WRITEMASK                0x0B98
#define GL_MATRIX_MODE                      0x0BA0
#define GL_NORMALIZE                        0x0BA1
#define GL_VIEWPORT                         0x0BA2
#define GL_MODELVIEW_STACK_DEPTH            0x0BA3
#define GL_PROJECTION_STACK_DEPTH           0x0BA4
#define GL_TEXTURE_STACK_DEPTH              0x0BA5
#define GL_MODELVIEW_MATRIX                 0x0BA6
#define GL_PROJECTION_MATRIX                0x0BA7
#define GL_TEXTURE_MATRIX                   0x0BA8
#define GL_COLOR_MATRIX						0x80B1
#define GL_ATTRIB_STACK_DEPTH               0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH        0x0BB1
#define GL_ALPHA_TEST                       0x0BC0
#define GL_ALPHA_TEST_FUNC                  0x0BC1
#define GL_ALPHA_TEST_REF                   0x0BC2
#define GL_DITHER                           0x0BD0
#define GL_BLEND_DST                        0x0BE0
#define GL_BLEND_SRC                        0x0BE1
#define GL_BLEND                            0x0BE2
#define GL_LOGIC_OP_MODE                    0x0BF0
#define GL_INDEX_LOGIC_OP                   0x0BF1
#define GL_LOGIC_OP                         0x0BF1
#define GL_COLOR_LOGIC_OP                   0x0BF2
#define GL_AUX_BUFFERS                      0x0C00
#define GL_DRAW_BUFFER                      0x0C01
#define GL_READ_BUFFER                      0x0C02
#define GL_SCISSOR_BOX                      0x0C10
#define GL_SCISSOR_TEST                     0x0C11
#define GL_INDEX_CLEAR_VALUE                0x0C20
#define GL_INDEX_WRITEMASK                  0x0C21
#define GL_COLOR_CLEAR_VALUE                0x0C22
#define GL_COLOR_WRITEMASK                  0x0C23
#define GL_INDEX_MODE                       0x0C30
#define GL_RGBA_MODE                        0x0C31
#define GL_DOUBLEBUFFER                     0x0C32
#define GL_STEREO                           0x0C33
#define GL_RENDER_MODE                      0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT      0x0C50
#define GL_POINT_SMOOTH_HINT                0x0C51
#define GL_LINE_SMOOTH_HINT                 0x0C52
#define GL_POLYGON_SMOOTH_HINT              0x0C53
#define GL_FOG_HINT                         0x0C54
#define GL_TEXTURE_GEN_S                    0x0C60
#define GL_TEXTURE_GEN_T                    0x0C61
#define GL_TEXTURE_GEN_R                    0x0C62
#define GL_TEXTURE_GEN_Q                    0x0C63
#define GL_PIXEL_MAP_I_TO_I_SIZE            0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE            0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE            0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE            0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE            0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE            0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE            0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE            0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE            0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE            0x0CB9
#define GL_UNPACK_SWAP_BYTES                0x0CF0
#define GL_UNPACK_LSB_FIRST                 0x0CF1
#define GL_UNPACK_ROW_LENGTH                0x0CF2
#define GL_UNPACK_SKIP_ROWS                 0x0CF3
#define GL_UNPACK_SKIP_PIXELS               0x0CF4
#define GL_UNPACK_ALIGNMENT                 0x0CF5
#define GL_PACK_SWAP_BYTES                  0x0D00
#define GL_PACK_LSB_FIRST                   0x0D01
#define GL_PACK_ROW_LENGTH                  0x0D02
#define GL_PACK_SKIP_ROWS                   0x0D03
#define GL_PACK_SKIP_PIXELS                 0x0D04
#define GL_PACK_ALIGNMENT                   0x0D05
#define GL_MAP_COLOR                        0x0D10
#define GL_MAP_STENCIL                      0x0D11
#define GL_INDEX_SHIFT                      0x0D12
#define GL_INDEX_OFFSET                     0x0D13
#define GL_RED_SCALE                        0x0D14
#define GL_RED_BIAS                         0x0D15
#define GL_ZOOM_X                           0x0D16
#define GL_ZOOM_Y                           0x0D17
#define GL_GREEN_SCALE                      0x0D18
#define GL_GREEN_BIAS                       0x0D19
#define GL_BLUE_SCALE                       0x0D1A
#define GL_BLUE_BIAS                        0x0D1B
#define GL_ALPHA_SCALE                      0x0D1C
#define GL_ALPHA_BIAS                       0x0D1D
#define GL_DEPTH_SCALE                      0x0D1E
#define GL_DEPTH_BIAS                       0x0D1F
#define GL_MAX_EVAL_ORDER                   0x0D30
#define GL_MAX_LIGHTS                       0x0D31
#define GL_MAX_CLIP_PLANES                  0x0D32
#define GL_MAX_TEXTURE_SIZE                 0x0D33
#define GL_MAX_PIXEL_MAP_TABLE              0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH           0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH        0x0D36
#define GL_MAX_NAME_STACK_DEPTH             0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH       0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH          0x0D39

#define GL_MAX_COLOR_STACK_DEPTH			0x80B2

#define GL_MAX_VIEWPORT_DIMS                0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH    0x0D3B
#define GL_SUBPIXEL_BITS                    0x0D50
#define GL_INDEX_BITS                       0x0D51
#define GL_RED_BITS                         0x0D52
#define GL_GREEN_BITS                       0x0D53
#define GL_BLUE_BITS                        0x0D54
#define GL_ALPHA_BITS                       0x0D55
#define GL_DEPTH_BITS                       0x0D56
#define GL_STENCIL_BITS                     0x0D57
#define GL_ACCUM_RED_BITS                   0x0D58
#define GL_ACCUM_GREEN_BITS                 0x0D59
#define GL_ACCUM_BLUE_BITS                  0x0D5A
#define GL_ACCUM_ALPHA_BITS                 0x0D5B
#define GL_NAME_STACK_DEPTH                 0x0D70
#define GL_AUTO_NORMAL                      0x0D80
#define GL_MAP1_COLOR_4                     0x0D90
#define GL_MAP1_INDEX                       0x0D91
#define GL_MAP1_NORMAL                      0x0D92
#define GL_MAP1_TEXTURE_COORD_1             0x0D93
#define GL_MAP1_TEXTURE_COORD_2             0x0D94
#define GL_MAP1_TEXTURE_COORD_3             0x0D95
#define GL_MAP1_TEXTURE_COORD_4             0x0D96
#define GL_MAP1_VERTEX_3                    0x0D97
#define GL_MAP1_VERTEX_4                    0x0D98
#define GL_MAP2_COLOR_4                     0x0DB0
#define GL_MAP2_INDEX                       0x0DB1
#define GL_MAP2_NORMAL                      0x0DB2
#define GL_MAP2_TEXTURE_COORD_1             0x0DB3
#define GL_MAP2_TEXTURE_COORD_2             0x0DB4
#define GL_MAP2_TEXTURE_COORD_3             0x0DB5
#define GL_MAP2_TEXTURE_COORD_4             0x0DB6
#define GL_MAP2_VERTEX_3                    0x0DB7
#define GL_MAP2_VERTEX_4                    0x0DB8
#define GL_MAP1_GRID_DOMAIN                 0x0DD0
#define GL_MAP1_GRID_SEGMENTS               0x0DD1
#define GL_MAP2_GRID_DOMAIN                 0x0DD2
#define GL_MAP2_GRID_SEGMENTS               0x0DD3
#define GL_TEXTURE_1D                       0x0DE0
#define GL_TEXTURE_2D                       0x0DE1
#define GL_FEEDBACK_BUFFER_POINTER          0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE             0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE             0x0DF2
#define GL_SELECTION_BUFFER_POINTER         0x0DF3
#define GL_SELECTION_BUFFER_SIZE            0x0DF4
#define GL_POLYGON_OFFSET_UNITS             0x2A00
#define GL_POLYGON_OFFSET_POINT             0x2A01
#define GL_POLYGON_OFFSET_LINE              0x2A02
#define GL_POLYGON_OFFSET_FILL              0x8037
#define GL_POLYGON_OFFSET_FACTOR            0x8038
#define GL_TEXTURE_BINDING_1D               0x8068
#define GL_TEXTURE_BINDING_2D               0x8069
#define GL_TEXTURE_BINDING_3D               0x806A
#define GL_VERTEX_ARRAY                     0x8074
#define GL_NORMAL_ARRAY                     0x8075
#define GL_COLOR_ARRAY                      0x8076
#define GL_INDEX_ARRAY                      0x8077
#define GL_TEXTURE_COORD_ARRAY              0x8078
#define GL_EDGE_FLAG_ARRAY                  0x8079
#define GL_VERTEX_ARRAY_SIZE                0x807A
#define GL_VERTEX_ARRAY_TYPE                0x807B
#define GL_VERTEX_ARRAY_STRIDE              0x807C
#define GL_NORMAL_ARRAY_TYPE                0x807E
#define GL_NORMAL_ARRAY_STRIDE              0x807F
#define GL_COLOR_ARRAY_SIZE                 0x8081
#define GL_COLOR_ARRAY_TYPE                 0x8082
#define GL_COLOR_ARRAY_STRIDE               0x8083
#define GL_INDEX_ARRAY_TYPE                 0x8085
#define GL_INDEX_ARRAY_STRIDE               0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE         0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE         0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE       0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE           0x808C
/*      GL_LIGHT_MODEL_COLOR_CONTROL */
/*      GL_BLEND_COLOR_EXT */
/*      GL_BLEND_EQUATION_EXT */
/*      GL_PACK_CMYK_HINT_EXT */
/*      GL_UNPACK_CMYK_HINT_EXT */
/*      GL_CONVOLUTION_1D_EXT */
/*      GL_CONVOLUTION_2D_EXT */
/*      GL_SEPARABLE_2D_EXT */
/*      GL_POST_CONVOLUTION_RED_SCALE_EXT */
/*      GL_POST_CONVOLUTION_GREEN_SCALE_EXT */
/*      GL_POST_CONVOLUTION_BLUE_SCALE_EXT */
/*      GL_POST_CONVOLUTION_ALPHA_SCALE_EXT */
/*      GL_POST_CONVOLUTION_RED_BIAS_EXT */
/*      GL_POST_CONVOLUTION_GREEN_BIAS_EXT */
/*      GL_POST_CONVOLUTION_BLUE_BIAS_EXT */
/*      GL_POST_CONVOLUTION_ALPHA_BIAS_EXT */
/*      GL_HISTOGRAM_EXT */
/*      GL_MINMAX_EXT */
/*      GL_POLYGON_OFFSET_BIAS_EXT */
/*      GL_RESCALE_NORMAL_EXT */
/*      GL_TEXTURE_3D_BINDING_EXT */
/*      GL_PACK_SKIP_IMAGES_EXT */
/*      GL_PACK_IMAGE_HEIGHT_EXT */
/*      GL_UNPACK_SKIP_IMAGES_EXT */
/*      GL_UNPACK_IMAGE_HEIGHT_EXT */
/*      GL_TEXTURE_3D_EXT */
/*      GL_MAX_3D_TEXTURE_SIZE_EXT */
/*      GL_VERTEX_ARRAY_COUNT_EXT */
/*      GL_NORMAL_ARRAY_COUNT_EXT */
/*      GL_COLOR_ARRAY_COUNT_EXT */
/*      GL_INDEX_ARRAY_COUNT_EXT */
/*      GL_TEXTURE_COORD_ARRAY_COUNT_EXT */
/*      GL_EDGE_FLAG_ARRAY_COUNT_EXT */
/*      GL_DETAIL_TEXTURE_2D_BINDING_SGIS */
/*      GL_FOG_FUNC_POINTS_SGIS */
/*      GL_MAX_FOG_FUNC_POINTS_SGIS */
/*      GL_GENERATE_MIPMAP_HINT_SGIS */
/*      GL_MULTISAMPLE_SGIS */
/*      GL_SAMPLE_ALPHA_TO_MASK_SGIS */
/*      GL_SAMPLE_ALPHA_TO_ONE_SGIS */
/*      GL_SAMPLE_MASK_SGIS */
/*      GL_SAMPLE_BUFFERS_SGIS */
/*      GL_SAMPLES_SGIS */
/*      GL_SAMPLE_MASK_VALUE_SGIS */
/*      GL_SAMPLE_MASK_INVERT_SGIS */
/*      GL_SAMPLE_PATTERN_SGIS */
/*      GL_POINT_SIZE_MIN_SGIS */
/*      GL_POINT_SIZE_MAX_SGIS */
/*      GL_POINT_FADE_THRESHOLD_SIZE_SGIS */
/*      GL_DISTANCE_ATTENUATION_SGIS */
/*      GL_PACK_SKIP_VOLUMES_SGIS */
/*      GL_PACK_IMAGE_DEPTH_SGIS */
/*      GL_UNPACK_SKIP_VOLUMES_SGIS */
/*      GL_UNPACK_IMAGE_DEPTH_SGIS */
/*      GL_TEXTURE_4D_SGIS */
/*      GL_MAX_4D_TEXTURE_SIZE_SGIS */
/*      GL_TEXTURE_4D_BINDING_SGIS */
/*      GL_CALLIGRAPHIC_FRAGMENT_SGIX */
/*      GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX */
/*      GL_MAX_CLIPMAP_DEPTH_SGIX */
/*      GL_FOG_OFFSET_SGIX */
/*      GL_FOG_OFFSET_VALUE_SGIX */
/*      GL_FRAMEZOOM_SGIX */
/*      GL_FRAMEZOOM_FACTOR_SGIX */
/*      GL_MAX_FRAMEZOOM_FACTOR_SGIX */
/*      GL_INSTRUMENT_MEASUREMENTS_SGIX */
/*      GL_INTERLACE_SGIX */
/*      GL_IR_INSTRUMENT1_SGIX */
/*      GL_PIXEL_TEX_GEN_SGIX */
/*      GL_PIXEL_TEX_GEN_MODE_SGIX */
/*      GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX */
/*      GL_PIXEL_TILE_CACHE_INCREMENT_SGIX */
/*      GL_PIXEL_TILE_WIDTH_SGIX */
/*      GL_PIXEL_TILE_HEIGHT_SGIX */
/*      GL_PIXEL_TILE_GRID_WIDTH_SGIX */
/*      GL_PIXEL_TILE_GRID_HEIGHT_SGIX */
/*      GL_PIXEL_TILE_GRID_DEPTH_SGIX */
/*      GL_PIXEL_TILE_CACHE_SIZE_SGIX */
/*      GL_DEFORMATIONS_MASK_SGIX */
/*      GL_REFERENCE_PLANE_EQUATION_SGIX */
/*      GL_REFERENCE_PLANE_SGIX */
/*      GL_SPRITE_MODE_SGIX */
/*      GL_SPRITE_AXIS_SGIX */
/*      GL_SPRITE_TRANSLATION_SGIX */
/*      GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX */
/*      GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX */
/*      GL_COLOR_MATRIX_SGI */
/*      GL_COLOR_MATRIX_STACK_DEPTH_SGI */
/*      GL_MAX_COLOR_MATRIX_STACK_DEPTH_SGI */
/*      GL_POST_COLOR_MATRIX_RED_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_RED_BIAS_SGI */
/*      GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI */
/*      GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI */
/*      GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI */
/*      GL_COLOR_TABLE_SGI */
/*      GL_POST_CONVOLUTION_COLOR_TABLE_SGI */
/*      GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI */
/*      GL_TEXTURE_COLOR_TABLE_SGI */

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */
#define GL_TEXTURE_WIDTH                    0x1000
#define GL_TEXTURE_HEIGHT                   0x1001
#define GL_TEXTURE_INTERNAL_FORMAT          0x1003
#define GL_TEXTURE_COMPONENTS               0x1003
#define GL_TEXTURE_BORDER_COLOR             0x1004
#define GL_TEXTURE_BORDER                   0x1005
#define GL_TEXTURE_RED_SIZE                 0x805C
#define GL_TEXTURE_GREEN_SIZE               0x805D
#define GL_TEXTURE_BLUE_SIZE                0x805E
#define GL_TEXTURE_ALPHA_SIZE               0x805F
#define GL_TEXTURE_LUMINANCE_SIZE           0x8060
#define GL_TEXTURE_INTENSITY_SIZE           0x8061
#define GL_TEXTURE_PRIORITY                 0x8066
#define GL_TEXTURE_RESIDENT                 0x8067
/*      GL_TEXTURE_DEPTH_EXT */
/*      GL_TEXTURE_WRAP_R_EXT */
/*      GL_DETAIL_TEXTURE_LEVEL_SGIS */
/*      GL_DETAIL_TEXTURE_MODE_SGIS */
/*      GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS */
/*      GL_GENERATE_MIPMAP_SGIS */
/*      GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS */
/*      GL_TEXTURE_FILTER4_SIZE_SGIS */
/*      GL_TEXTURE_MIN_LOD_SGIS */
/*      GL_TEXTURE_MAX_LOD_SGIS */
/*      GL_TEXTURE_BASE_LEVEL_SGIS */
/*      GL_TEXTURE_MAX_LEVEL_SGIS */
/*      GL_DUAL_TEXTURE_SELECT_SGIS */
/*      GL_QUAD_TEXTURE_SELECT_SGIS */
/*      GL_TEXTURE_4DSIZE_SGIS */
/*      GL_TEXTURE_WRAP_Q_SGIS */
/*      GL_TEXTURE_CLIPMAP_CENTER_SGIX */
/*      GL_TEXTURE_CLIPMAP_FRAME_SGIX */
/*      GL_TEXTURE_CLIPMAP_OFFSET_SGIX */
/*      GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX */
/*      GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX */
/*      GL_TEXTURE_CLIPMAP_DEPTH_SGIX */
/*      GL_TEXTURE_COMPARE_SGIX */
/*      GL_TEXTURE_COMPARE_OPERATOR_SGIX */
/*      GL_TEXTURE_LEQUAL_R_SGIX */
/*      GL_TEXTURE_GEQUAL_R_SGIX */
/*      GL_SHADOW_AMBIENT_SGIX */
/*      GL_TEXTURE_LOD_BIAS_S_SGIX */
/*      GL_TEXTURE_LOD_BIAS_T_SGIX */
/*      GL_TEXTURE_LOD_BIAS_R_SGIX */
/*      GL_POST_TEXTURE_FILTER_BIAS_SGIX */
/*      GL_POST_TEXTURE_FILTER_SCALE_SGIX */

/* HintMode */
#define GL_DONT_CARE                        0x1100
#define GL_FASTEST                          0x1101
#define GL_NICEST                           0x1102

/* HintTarget */
/*      GL_PERSPECTIVE_CORRECTION_HINT */
/*      GL_POINT_SMOOTH_HINT */
/*      GL_LINE_SMOOTH_HINT */
/*      GL_POLYGON_SMOOTH_HINT */
/*      GL_FOG_HINT */
/*      GL_PACK_CMYK_HINT_EXT */
/*      GL_UNPACK_CMYK_HINT_EXT */
/*      GL_GENERATE_MIPMAP_HINT_SGIS */
/*      GL_TEXTURE_MULTI_BUFFER_HINT_SGIX */

/* HistogramTargetEXT */
/*      GL_HISTOGRAM_EXT */
/*      GL_PROXY_HISTOGRAM_EXT */

/* IndexPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* LightModelColorControlEXT */
/*      GL_SINGLE_COLOR */
/*      GL_SEPARATE_SPECULAR_COLOR */

/* LightModelParameter */
/*      GL_LIGHT_MODEL_AMBIENT */
/*      GL_LIGHT_MODEL_LOCAL_VIEWER */
/*      GL_LIGHT_MODEL_TWO_SIDE */
/*      GL_LIGHT_MODEL_COLOR_CONTROL */

/* LightParameter */
#define GL_AMBIENT                          0x1200
#define GL_DIFFUSE                          0x1201
#define GL_SPECULAR                         0x1202
#define GL_POSITION                         0x1203
#define GL_SPOT_DIRECTION                   0x1204
#define GL_SPOT_EXPONENT                    0x1205
#define GL_SPOT_CUTOFF                      0x1206
#define GL_CONSTANT_ATTENUATION             0x1207
#define GL_LINEAR_ATTENUATION               0x1208
#define GL_QUADRATIC_ATTENUATION            0x1209

/* ListMode */
#define GL_COMPILE                          0x1300
#define GL_COMPILE_AND_EXECUTE              0x1301

/* DataType */
#define GL_BYTE                             0x1400
#define GL_UNSIGNED_BYTE                    0x1401
#define GL_SHORT                            0x1402
#define GL_UNSIGNED_SHORT                   0x1403
#define GL_INT                              0x1404
#define GL_UNSIGNED_INT                     0x1405
#define GL_FLOAT                            0x1406
#define GL_2_BYTES                          0x1407
#define GL_3_BYTES                          0x1408
#define GL_4_BYTES                          0x1409
#define GL_DOUBLE                           0x140A
#define GL_DOUBLE_EXT                       0x140A

/* ListNameType */
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_2_BYTES */
/*      GL_3_BYTES */
/*      GL_4_BYTES */

/* ListParameterName */
/*      GL_LIST_PRIORITY_SGIX */

/* LogicOp */
#define GL_CLEAR                            0x1500
#define GL_AND                              0x1501
#define GL_AND_REVERSE                      0x1502
#define GL_COPY                             0x1503
#define GL_AND_INVERTED                     0x1504
#define GL_NOOP                             0x1505
#define GL_XOR                              0x1506
#define GL_OR                               0x1507
#define GL_NOR                              0x1508
#define GL_EQUIV                            0x1509
#define GL_INVERT                           0x150A
#define GL_OR_REVERSE                       0x150B
#define GL_COPY_INVERTED                    0x150C
#define GL_OR_INVERTED                      0x150D
#define GL_NAND                             0x150E
#define GL_SET                              0x150F

/* MapTarget */
/*      GL_MAP1_COLOR_4 */
/*      GL_MAP1_INDEX */
/*      GL_MAP1_NORMAL */
/*      GL_MAP1_TEXTURE_COORD_1 */
/*      GL_MAP1_TEXTURE_COORD_2 */
/*      GL_MAP1_TEXTURE_COORD_3 */
/*      GL_MAP1_TEXTURE_COORD_4 */
/*      GL_MAP1_VERTEX_3 */
/*      GL_MAP1_VERTEX_4 */
/*      GL_MAP2_COLOR_4 */
/*      GL_MAP2_INDEX */
/*      GL_MAP2_NORMAL */
/*      GL_MAP2_TEXTURE_COORD_1 */
/*      GL_MAP2_TEXTURE_COORD_2 */
/*      GL_MAP2_TEXTURE_COORD_3 */
/*      GL_MAP2_TEXTURE_COORD_4 */
/*      GL_MAP2_VERTEX_3 */
/*      GL_MAP2_VERTEX_4 */
/*      GL_GEOMETRY_DEFORMATION_SGIX */
/*      GL_TEXTURE_DEFORMATION_SGIX */

/* MaterialFace */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* MaterialParameter */
#define GL_EMISSION                         0x1600
#define GL_SHININESS                        0x1601
#define GL_AMBIENT_AND_DIFFUSE              0x1602
#define GL_COLOR_INDEXES                    0x1603
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */

/* MatrixMode */
#define GL_MODELVIEW                        0x1700
#define GL_PROJECTION                       0x1701
#define GL_TEXTURE                          0x1702

/* MeshMode1 */
/*      GL_POINT */
/*      GL_LINE */

/* MeshMode2 */
/*      GL_POINT */
/*      GL_LINE */
/*      GL_FILL */

/* MinmaxTargetEXT */
/*      GL_MINMAX_EXT */

/* NormalPointerType */
/*      GL_BYTE */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* PixelCopyType */
#define GL_COLOR                            0x1800
#define GL_DEPTH                            0x1801
#define GL_STENCIL                          0x1802

/* PixelFormat */
#define GL_COLOR_INDEX                      0x1900
#define GL_STENCIL_INDEX                    0x1901
#define GL_DEPTH_COMPONENT                  0x1902
#define GL_RED                              0x1903
#define GL_GREEN                            0x1904
#define GL_BLUE                             0x1905
#define GL_ALPHA                            0x1906
#define GL_RGB                              0x1907
#define GL_RGBA                             0x1908
#define GL_LUMINANCE                        0x1909
#define GL_LUMINANCE_ALPHA                  0x190A
/*      GL_ABGR_EXT */
/*      GL_CMYK_EXT */
/*      GL_CMYKA_EXT */
/*      GL_YCRCB_422_SGIX */
/*      GL_YCRCB_444_SGIX */

/* PixelMap */
/*      GL_PIXEL_MAP_I_TO_I */
/*      GL_PIXEL_MAP_S_TO_S */
/*      GL_PIXEL_MAP_I_TO_R */
/*      GL_PIXEL_MAP_I_TO_G */
/*      GL_PIXEL_MAP_I_TO_B */
/*      GL_PIXEL_MAP_I_TO_A */
/*      GL_PIXEL_MAP_R_TO_R */
/*      GL_PIXEL_MAP_G_TO_G */
/*      GL_PIXEL_MAP_B_TO_B */
/*      GL_PIXEL_MAP_A_TO_A */

/* PixelStoreParameter */
/*      GL_UNPACK_SWAP_BYTES */
/*      GL_UNPACK_LSB_FIRST */
/*      GL_UNPACK_ROW_LENGTH */
/*      GL_UNPACK_SKIP_ROWS */
/*      GL_UNPACK_SKIP_PIXELS */
/*      GL_UNPACK_ALIGNMENT */
/*      GL_PACK_SWAP_BYTES */
/*      GL_PACK_LSB_FIRST */
/*      GL_PACK_ROW_LENGTH */
/*      GL_PACK_SKIP_ROWS */
/*      GL_PACK_SKIP_PIXELS */
/*      GL_PACK_ALIGNMENT */
/*      GL_PACK_SKIP_IMAGES_EXT */
/*      GL_PACK_IMAGE_HEIGHT_EXT */
/*      GL_UNPACK_SKIP_IMAGES_EXT */
/*      GL_UNPACK_IMAGE_HEIGHT_EXT */
/*      GL_PACK_SKIP_VOLUMES_SGIS */
/*      GL_PACK_IMAGE_DEPTH_SGIS */
/*      GL_UNPACK_SKIP_VOLUMES_SGIS */
/*      GL_UNPACK_IMAGE_DEPTH_SGIS */
/*      GL_PIXEL_TILE_WIDTH_SGIX */
/*      GL_PIXEL_TILE_HEIGHT_SGIX */
/*      GL_PIXEL_TILE_GRID_WIDTH_SGIX */
/*      GL_PIXEL_TILE_GRID_HEIGHT_SGIX */
/*      GL_PIXEL_TILE_GRID_DEPTH_SGIX */
/*      GL_PIXEL_TILE_CACHE_SIZE_SGIX */

/* PixelTexGenMode */
/*      GL_NONE */
/*      GL_RGB */
/*      GL_RGBA */
/*      GL_LUMINANCE */
/*      GL_LUMINANCE_ALPHA */
/*      GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX */
/*      GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX */
/*      GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX */
/*      GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX */

/* PixelTransferParameter */
/*      GL_MAP_COLOR */
/*      GL_MAP_STENCIL */
/*      GL_INDEX_SHIFT */
/*      GL_INDEX_OFFSET */
/*      GL_RED_SCALE */
/*      GL_RED_BIAS */
/*      GL_GREEN_SCALE */
/*      GL_GREEN_BIAS */
/*      GL_BLUE_SCALE */
/*      GL_BLUE_BIAS */
/*      GL_ALPHA_SCALE */
/*      GL_ALPHA_BIAS */
/*      GL_DEPTH_SCALE */
/*      GL_DEPTH_BIAS */
/*      GL_POST_CONVOLUTION_RED_SCALE_EXT */
/*      GL_POST_CONVOLUTION_GREEN_SCALE_EXT */
/*      GL_POST_CONVOLUTION_BLUE_SCALE_EXT */
/*      GL_POST_CONVOLUTION_ALPHA_SCALE_EXT */
/*      GL_POST_CONVOLUTION_RED_BIAS_EXT */
/*      GL_POST_CONVOLUTION_GREEN_BIAS_EXT */
/*      GL_POST_CONVOLUTION_BLUE_BIAS_EXT */
/*      GL_POST_CONVOLUTION_ALPHA_BIAS_EXT */
/*      GL_POST_COLOR_MATRIX_RED_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI */
/*      GL_POST_COLOR_MATRIX_RED_BIAS_SGI */
/*      GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI */
/*      GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI */
/*      GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI */

/* PixelType */
#define GL_BITMAP                           0x1A00
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_UNSIGNED_BYTE_3_3_2_EXT */
/*      GL_UNSIGNED_SHORT_4_4_4_4_EXT */
/*      GL_UNSIGNED_SHORT_5_5_5_1_EXT */
/*      GL_UNSIGNED_INT_8_8_8_8_EXT */
/*      GL_UNSIGNED_INT_10_10_10_2_EXT */

/* PointParameterNameSGIS */
/*      GL_POINT_SIZE_MIN_SGIS */
/*      GL_POINT_SIZE_MAX_SGIS */
/*      GL_POINT_FADE_THRESHOLD_SIZE_SGIS */
/*      GL_DISTANCE_ATTENUATION_SGIS */

/* PolygonMode */
#define GL_POINT                            0x1B00
#define GL_LINE                             0x1B01
#define GL_FILL                             0x1B02

/* ReadBufferMode */
/*      GL_FRONT_LEFT */
/*      GL_FRONT_RIGHT */
/*      GL_BACK_LEFT */
/*      GL_BACK_RIGHT */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_LEFT */
/*      GL_RIGHT */
/*      GL_AUX0 */
/*      GL_AUX1 */
/*      GL_AUX2 */
/*      GL_AUX3 */

/* RenderingMode */
#define GL_RENDER                           0x1C00
#define GL_FEEDBACK                         0x1C01
#define GL_SELECT                           0x1C02

/* SamplePatternPatternSGIS */
/*      GL_1PASS_SGIS */
/*      GL_2PASS_0_SGIS */
/*      GL_2PASS_1_SGIS */
/*      GL_4PASS_0_SGIS */
/*      GL_4PASS_1_SGIS */
/*      GL_4PASS_2_SGIS */
/*      GL_4PASS_3_SGIS */

/* SeparableTargetEXT */
/*      GL_SEPARABLE_2D_EXT */

/* ShadingModel */
#define GL_FLAT                             0x1D00
#define GL_SMOOTH                           0x1D01

/* StencilFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                             0x1E00
#define GL_REPLACE                          0x1E01
#define GL_INCR                             0x1E02
#define GL_DECR                             0x1E03
/*      GL_INVERT */

/* StringName */
#define GL_VENDOR                           0x1F00
#define GL_RENDERER                         0x1F01
#define GL_VERSION                          0x1F02
#define GL_EXTENSIONS                       0x1F03

/* TexCoordPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* TextureCoordName */
#define GL_S                                0x2000
#define GL_T                                0x2001
#define GL_R                                0x2002
#define GL_Q                                0x2003

/* TextureEnvMode */
#define GL_MODULATE                         0x2100
#define GL_DECAL                            0x2101
/*      GL_BLEND */
/*      GL_REPLACE_EXT */
/*      GL_ADD */
/*      GL_TEXTURE_ENV_BIAS_SGIX */

/* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE                 0x2200
#define GL_TEXTURE_ENV_COLOR                0x2201

/* TextureEnvTarget */
#define GL_TEXTURE_ENV                      0x2300

/* TextureFilterFuncSGIS */
/*      GL_FILTER4_SGIS */

/* TextureGenMode */
#define GL_EYE_LINEAR                       0x2400
#define GL_OBJECT_LINEAR                    0x2401
#define GL_SPHERE_MAP                       0x2402
/*      GL_EYE_DISTANCE_TO_POINT_SGIS */
/*      GL_OBJECT_DISTANCE_TO_POINT_SGIS */
/*      GL_EYE_DISTANCE_TO_LINE_SGIS */
/*      GL_OBJECT_DISTANCE_TO_LINE_SGIS */

/* TextureGenParameter */
#define GL_TEXTURE_GEN_MODE                 0x2500
#define GL_OBJECT_PLANE                     0x2501
#define GL_EYE_PLANE                        0x2502
/*      GL_EYE_POINT_SGIS */
/*      GL_OBJECT_POINT_SGIS */
/*      GL_EYE_LINE_SGIS */
/*      GL_OBJECT_LINE_SGIS */

/* TextureMagFilter */
#define GL_NEAREST                          0x2600
#define GL_LINEAR                           0x2601
/*      GL_LINEAR_DETAIL_SGIS */
/*      GL_LINEAR_DETAIL_ALPHA_SGIS */
/*      GL_LINEAR_DETAIL_COLOR_SGIS */
/*      GL_LINEAR_SHARPEN_SGIS */
/*      GL_LINEAR_SHARPEN_ALPHA_SGIS */
/*      GL_LINEAR_SHARPEN_COLOR_SGIS */
/*      GL_FILTER4_SGIS */
/*      GL_PIXEL_TEX_GEN_Q_CEILING_SGIX */
/*      GL_PIXEL_TEX_GEN_Q_ROUND_SGIX */
/*      GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX */

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST           0x2700
#define GL_LINEAR_MIPMAP_NEAREST            0x2701
#define GL_NEAREST_MIPMAP_LINEAR            0x2702
#define GL_LINEAR_MIPMAP_LINEAR             0x2703
/*      GL_FILTER4_SGIS */
/*      GL_LINEAR_CLIPMAP_LINEAR_SGIX */
/*      GL_PIXEL_TEX_GEN_Q_CEILING_SGIX */
/*      GL_PIXEL_TEX_GEN_Q_ROUND_SGIX */
/*      GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX */

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER               0x2800
#define GL_TEXTURE_MIN_FILTER               0x2801
#define GL_TEXTURE_WRAP_S                   0x2802
#define GL_TEXTURE_WRAP_T                   0x2803
/*      GL_TEXTURE_BORDER_COLOR */
/*      GL_TEXTURE_PRIORITY */
/*      GL_TEXTURE_WRAP_R_EXT */
/*      GL_DETAIL_TEXTURE_LEVEL_SGIS */
/*      GL_DETAIL_TEXTURE_MODE_SGIS */
/*      GL_GENERATE_MIPMAP_SGIS */
/*      GL_DUAL_TEXTURE_SELECT_SGIS */
/*      GL_QUAD_TEXTURE_SELECT_SGIS */
/*      GL_TEXTURE_WRAP_Q_SGIS */
/*      GL_TEXTURE_CLIPMAP_CENTER_SGIX */
/*      GL_TEXTURE_CLIPMAP_FRAME_SGIX */
/*      GL_TEXTURE_CLIPMAP_OFFSET_SGIX */
/*      GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX */
/*      GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX */
/*      GL_TEXTURE_CLIPMAP_DEPTH_SGIX */
/*      GL_TEXTURE_COMPARE_SGIX */
/*      GL_TEXTURE_COMPARE_OPERATOR_SGIX */
/*      GL_SHADOW_AMBIENT_SGIX */
/*      GL_TEXTURE_LOD_BIAS_S_SGIX */
/*      GL_TEXTURE_LOD_BIAS_T_SGIX */
/*      GL_TEXTURE_LOD_BIAS_R_SGIX */
/*      GL_POST_TEXTURE_FILTER_BIAS_SGIX */
/*      GL_POST_TEXTURE_FILTER_SCALE_SGIX */

/* TextureTarget */
/*      GL_TEXTURE_1D */
/*      GL_TEXTURE_2D */
#define GL_PROXY_TEXTURE_1D                 0x8063
#define GL_PROXY_TEXTURE_2D                 0x8064
/*      GL_TEXTURE_3D_EXT */
/*      GL_PROXY_TEXTURE_3D_EXT */
/*      GL_DETAIL_TEXTURE_2D_SGIS */
/*      GL_TEXTURE_4D_SGIS */
/*      GL_PROXY_TEXTURE_4D_SGIS */
/*      GL_TEXTURE_MIN_LOD_SGIS */
/*      GL_TEXTURE_MAX_LOD_SGIS */
/*      GL_TEXTURE_BASE_LEVEL_SGIS */
/*      GL_TEXTURE_MAX_LEVEL_SGIS */

/* TextureWrapMode */
#define GL_CLAMP                            0x2900
#define GL_REPEAT                           0x2901
/*      GL_CLAMP_TO_BORDER_SGIS */
/*      GL_CLAMP_TO_EDGE_SGIS */

/* PixelInternalFormat */
#define GL_R3_G3_B2                         0x2A10
#define GL_ALPHA4                           0x803B
#define GL_ALPHA8                           0x803C
#define GL_ALPHA12                          0x803D
#define GL_ALPHA16                          0x803E
#define GL_LUMINANCE4                       0x803F
#define GL_LUMINANCE8                       0x8040
#define GL_LUMINANCE12                      0x8041
#define GL_LUMINANCE16                      0x8042
#define GL_LUMINANCE4_ALPHA4                0x8043
#define GL_LUMINANCE6_ALPHA2                0x8044
#define GL_LUMINANCE8_ALPHA8                0x8045
#define GL_LUMINANCE12_ALPHA4               0x8046
#define GL_LUMINANCE12_ALPHA12              0x8047
#define GL_LUMINANCE16_ALPHA16              0x8048
#define GL_INTENSITY                        0x8049
#define GL_INTENSITY4                       0x804A
#define GL_INTENSITY8                       0x804B
#define GL_INTENSITY12                      0x804C
#define GL_INTENSITY16                      0x804D
#define GL_RGB4                             0x804F
#define GL_RGB5                             0x8050
#define GL_RGB8                             0x8051
#define GL_RGB10                            0x8052
#define GL_RGB12                            0x8053
#define GL_RGB16                            0x8054
#define GL_RGBA2                            0x8055
#define GL_RGBA4                            0x8056
#define GL_RGB5_A1                          0x8057
#define GL_RGBA8                            0x8058
#define GL_RGB10_A2                         0x8059
#define GL_RGBA12                           0x805A
#define GL_RGBA16                           0x805B
/*      GL_RGB2_EXT */
/*      GL_DUAL_ALPHA4_SGIS */
/*      GL_DUAL_ALPHA8_SGIS */
/*      GL_DUAL_ALPHA12_SGIS */
/*      GL_DUAL_ALPHA16_SGIS */
/*      GL_DUAL_LUMINANCE4_SGIS */
/*      GL_DUAL_LUMINANCE8_SGIS */
/*      GL_DUAL_LUMINANCE12_SGIS */
/*      GL_DUAL_LUMINANCE16_SGIS */
/*      GL_DUAL_INTENSITY4_SGIS */
/*      GL_DUAL_INTENSITY8_SGIS */
/*      GL_DUAL_INTENSITY12_SGIS */
/*      GL_DUAL_INTENSITY16_SGIS */
/*      GL_DUAL_LUMINANCE_ALPHA4_SGIS */
/*      GL_DUAL_LUMINANCE_ALPHA8_SGIS */
/*      GL_QUAD_ALPHA4_SGIS */
/*      GL_QUAD_ALPHA8_SGIS */
/*      GL_QUAD_LUMINANCE4_SGIS */
/*      GL_QUAD_LUMINANCE8_SGIS */
/*      GL_QUAD_INTENSITY4_SGIS */
/*      GL_QUAD_INTENSITY8_SGIS */
/*      GL_DEPTH_COMPONENT16_SGIX */
/*      GL_DEPTH_COMPONENT24_SGIX */
/*      GL_DEPTH_COMPONENT32_SGIX */

/* InterleavedArrayFormat */
#define GL_V2F                              0x2A20
#define GL_V3F                              0x2A21
#define GL_C4UB_V2F                         0x2A22
#define GL_C4UB_V3F                         0x2A23
#define GL_C3F_V3F                          0x2A24
#define GL_N3F_V3F                          0x2A25
#define GL_C4F_N3F_V3F                      0x2A26
#define GL_T2F_V3F                          0x2A27
#define GL_T4F_V4F                          0x2A28
#define GL_T2F_C4UB_V3F                     0x2A29
#define GL_T2F_C3F_V3F                      0x2A2A
#define GL_T2F_N3F_V3F                      0x2A2B
#define GL_T2F_C4F_N3F_V3F                  0x2A2C
#define GL_T4F_C4F_N3F_V4F                  0x2A2D

/* VertexPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* ClipPlaneName */
#define GL_CLIP_PLANE0                      0x3000
#define GL_CLIP_PLANE1                      0x3001
#define GL_CLIP_PLANE2                      0x3002
#define GL_CLIP_PLANE3                      0x3003
#define GL_CLIP_PLANE4                      0x3004
#define GL_CLIP_PLANE5                      0x3005

/* LightName */
#define GL_LIGHT0                           0x4000
#define GL_LIGHT1                           0x4001
#define GL_LIGHT2                           0x4002
#define GL_LIGHT3                           0x4003
#define GL_LIGHT4                           0x4004
#define GL_LIGHT5                           0x4005
#define GL_LIGHT6                           0x4006
#define GL_LIGHT7                           0x4007

/* EXT_abgr */
#define GL_ABGR_EXT                         0x8000

/* EXT_blend_color */
#define GL_CONSTANT_COLOR                   0x8001
#define GL_CONSTANT_COLOR_EXT               0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR         0x8002
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT     0x8002
#define GL_CONSTANT_ALPHA                   0x8003
#define GL_CONSTANT_ALPHA_EXT               0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA         0x8004
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT     0x8004
#define GL_BLEND_COLOR                      0x8005
#define GL_BLEND_COLOR_EXT                  0x8005

/* EXT_blend_minmax */
#define GL_FUNC_ADD                         0x8006
#define GL_FUNC_ADD_EXT                     0x8006
#define GL_MIN                              0x8007
#define GL_MIN_EXT                          0x8007
#define GL_MAX                              0x8008
#define GL_MAX_EXT                          0x8008
#define GL_BLEND_EQUATION                   0x8009
#define GL_BLEND_EQUATION_EXT               0x8009

/* EXT_blend_subtract */
#define GL_FUNC_SUBTRACT                    0x800A
#define GL_FUNC_SUBTRACT_EXT                0x800A
#define GL_FUNC_REVERSE_SUBTRACT            0x800B
#define GL_FUNC_REVERSE_SUBTRACT_EXT        0x800B

/* EXT_cmyka */
#define GL_CMYK_EXT                         0x800C
#define GL_CMYKA_EXT                        0x800D
#define GL_PACK_CMYK_HINT_EXT               0x800E
#define GL_UNPACK_CMYK_HINT_EXT             0x800F

/* EXT_convolution */
#define GL_CONVOLUTION_1D                   0x8010
#define GL_CONVOLUTION_1D_EXT               0x8010
#define GL_CONVOLUTION_2D                   0x8011
#define GL_CONVOLUTION_2D_EXT               0x8011
#define GL_SEPARABLE_2D                     0x8012
#define GL_SEPARABLE_2D_EXT                 0x8012
#define GL_CONVOLUTION_BORDER_MODE          0x8013
#define GL_CONVOLUTION_BORDER_MODE_EXT      0x8013
#define GL_CONVOLUTION_FILTER_SCALE         0x8014
#define GL_CONVOLUTION_FILTER_SCALE_EXT     0x8014
#define GL_CONVOLUTION_FILTER_BIAS          0x8015
#define GL_CONVOLUTION_FILTER_BIAS_EXT      0x8015
#define GL_REDUCE                           0x8016
#define GL_REDUCE_EXT                       0x8016
#define GL_CONVOLUTION_FORMAT               0x8017
#define GL_CONVOLUTION_FORMAT_EXT           0x8017
#define GL_CONVOLUTION_WIDTH                0x8018
#define GL_CONVOLUTION_WIDTH_EXT            0x8018
#define GL_CONVOLUTION_HEIGHT               0x8019
#define GL_CONVOLUTION_HEIGHT_EXT           0x8019
#define GL_MAX_CONVOLUTION_WIDTH            0x801A
#define GL_MAX_CONVOLUTION_WIDTH_EXT        0x801A
#define GL_MAX_CONVOLUTION_HEIGHT           0x801B
#define GL_MAX_CONVOLUTION_HEIGHT_EXT       0x801B
#define GL_POST_CONVOLUTION_RED_SCALE       0x801C
#define GL_POST_CONVOLUTION_RED_SCALE_EXT   0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE     0x801D
#define GL_POST_CONVOLUTION_GREEN_SCALE_EXT 0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE      0x801E
#define GL_POST_CONVOLUTION_BLUE_SCALE_EXT  0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE     0x801F
#define GL_POST_CONVOLUTION_ALPHA_SCALE_EXT 0x801F
#define GL_POST_CONVOLUTION_RED_BIAS        0x8020
#define GL_POST_CONVOLUTION_RED_BIAS_EXT    0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS      0x8021
#define GL_POST_CONVOLUTION_GREEN_BIAS_EXT  0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS       0x8022
#define GL_POST_CONVOLUTION_BLUE_BIAS_EXT   0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS      0x8023
#define GL_POST_CONVOLUTION_ALPHA_BIAS_EXT  0x8023

/* EXT_histogram */
#define GL_HISTOGRAM                        0x8024
#define GL_HISTOGRAM_EXT                    0x8024
#define GL_PROXY_HISTOGRAM                  0x8025
#define GL_PROXY_HISTOGRAM_EXT              0x8025
#define GL_HISTOGRAM_WIDTH                  0x8026
#define GL_HISTOGRAM_WIDTH_EXT              0x8026
#define GL_HISTOGRAM_FORMAT                 0x8027
#define GL_HISTOGRAM_FORMAT_EXT             0x8027
#define GL_HISTOGRAM_RED_SIZE               0x8028
#define GL_HISTOGRAM_RED_SIZE_EXT           0x8028
#define GL_HISTOGRAM_GREEN_SIZE             0x8029
#define GL_HISTOGRAM_GREEN_SIZE_EXT         0x8029
#define GL_HISTOGRAM_BLUE_SIZE              0x802A
#define GL_HISTOGRAM_BLUE_SIZE_EXT          0x802A
#define GL_HISTOGRAM_ALPHA_SIZE             0x802B
#define GL_HISTOGRAM_ALPHA_SIZE_EXT         0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE         0x802C
#define GL_HISTOGRAM_LUMINANCE_SIZE_EXT     0x802C
#define GL_HISTOGRAM_SINK                   0x802D
#define GL_HISTOGRAM_SINK_EXT               0x802D
#define GL_MINMAX                           0x802E
#define GL_MINMAX_EXT                       0x802E
#define GL_MINMAX_FORMAT                    0x802F
#define GL_MINMAX_FORMAT_EXT                0x802F
#define GL_MINMAX_SINK                      0x8030
#define GL_MINMAX_SINK_EXT                  0x8030
#define GL_TABLE_TOO_LARGE                  0x8031
#define GL_TABLE_TOO_LARGE_EXT              0x8031

/* EXT_packed_pixels */
#define GL_UNSIGNED_BYTE_3_3_2              0x8032
#define GL_UNSIGNED_BYTE_3_3_2_EXT          0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4           0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT       0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1           0x8034
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT       0x8034
#define GL_UNSIGNED_INT_8_8_8_8             0x8035
#define GL_UNSIGNED_INT_8_8_8_8_EXT         0x8035
#define GL_UNSIGNED_INT_10_10_10_2          0x8036
#define GL_UNSIGNED_INT_10_10_10_2_EXT      0x8036

/* EXT_polygon_offset */
#define GL_POLYGON_OFFSET_EXT               0x8037
#define GL_POLYGON_OFFSET_FACTOR_EXT        0x8038
#define GL_POLYGON_OFFSET_BIAS_EXT          0x8039

/* EXT_rescale_normal */
#define GL_RESCALE_NORMAL                   0x803A
#define GL_RESCALE_NORMAL_EXT               0x803A

/* EXT_texture */
#define GL_ALPHA4_EXT                       0x803B
#define GL_ALPHA8_EXT                       0x803C
#define GL_ALPHA12_EXT                      0x803D
#define GL_ALPHA16_EXT                      0x803E
#define GL_LUMINANCE4_EXT                   0x803F
#define GL_LUMINANCE8_EXT                   0x8040
#define GL_LUMINANCE12_EXT                  0x8041
#define GL_LUMINANCE16_EXT                  0x8042
#define GL_LUMINANCE4_ALPHA4_EXT            0x8043
#define GL_LUMINANCE6_ALPHA2_EXT            0x8044
#define GL_LUMINANCE8_ALPHA8_EXT            0x8045
#define GL_LUMINANCE12_ALPHA4_EXT           0x8046
#define GL_LUMINANCE12_ALPHA12_EXT          0x8047
#define GL_LUMINANCE16_ALPHA16_EXT          0x8048
#define GL_INTENSITY_EXT                    0x8049
#define GL_INTENSITY4_EXT                   0x804A
#define GL_INTENSITY8_EXT                   0x804B
#define GL_INTENSITY12_EXT                  0x804C
#define GL_INTENSITY16_EXT                  0x804D
#define GL_RGB2_EXT                         0x804E
#define GL_RGB4_EXT                         0x804F
#define GL_RGB5_EXT                         0x8050
#define GL_RGB8_EXT                         0x8051
#define GL_RGB10_EXT                        0x8052
#define GL_RGB12_EXT                        0x8053
#define GL_RGB16_EXT                        0x8054
#define GL_RGBA2_EXT                        0x8055
#define GL_RGBA4_EXT                        0x8056
#define GL_RGB5_A1_EXT                      0x8057
#define GL_RGBA8_EXT                        0x8058
#define GL_RGB10_A2_EXT                     0x8059
#define GL_RGBA12_EXT                       0x805A
#define GL_RGBA16_EXT                       0x805B
#define GL_TEXTURE_RED_SIZE_EXT             0x805C
#define GL_TEXTURE_GREEN_SIZE_EXT           0x805D
#define GL_TEXTURE_BLUE_SIZE_EXT            0x805E
#define GL_TEXTURE_ALPHA_SIZE_EXT           0x805F
#define GL_TEXTURE_LUMINANCE_SIZE_EXT       0x8060
#define GL_TEXTURE_INTENSITY_SIZE_EXT       0x8061
#define GL_REPLACE_EXT                      0x8062
#define GL_PROXY_TEXTURE_1D_EXT             0x8063
#define GL_PROXY_TEXTURE_2D_EXT             0x8064
#define GL_TEXTURE_TOO_LARGE_EXT            0x8065

/* EXT_texture_object */
#define GL_TEXTURE_PRIORITY_EXT             0x8066
#define GL_TEXTURE_RESIDENT_EXT             0x8067
#define GL_TEXTURE_1D_BINDING_EXT           0x8068
#define GL_TEXTURE_2D_BINDING_EXT           0x8069
#define GL_TEXTURE_3D_BINDING_EXT           0x806A

/* EXT_texture3D */
#define GL_PACK_SKIP_IMAGES                 0x806B
#define GL_PACK_SKIP_IMAGES_EXT             0x806B
#define GL_PACK_IMAGE_HEIGHT                0x806C
#define GL_PACK_IMAGE_HEIGHT_EXT            0x806C
#define GL_UNPACK_SKIP_IMAGES               0x806D
#define GL_UNPACK_SKIP_IMAGES_EXT           0x806D
#define GL_UNPACK_IMAGE_HEIGHT              0x806E
#define GL_UNPACK_IMAGE_HEIGHT_EXT          0x806E
#define GL_TEXTURE_3D                       0x806F
#define GL_TEXTURE_3D_EXT                   0x806F
#define GL_PROXY_TEXTURE_3D                 0x8070
#define GL_PROXY_TEXTURE_3D_EXT             0x8070
#define GL_TEXTURE_DEPTH                    0x8071
#define GL_TEXTURE_DEPTH_EXT                0x8071
#define GL_TEXTURE_WRAP_R                   0x8072
#define GL_TEXTURE_WRAP_R_EXT               0x8072
#define GL_MAX_3D_TEXTURE_SIZE              0x8073
#define GL_MAX_3D_TEXTURE_SIZE_EXT          0x8073

/* EXT_vertex_array */
#define GL_VERTEX_ARRAY_EXT                 0x8074
#define GL_NORMAL_ARRAY_EXT                 0x8075
#define GL_COLOR_ARRAY_EXT                  0x8076
#define GL_INDEX_ARRAY_EXT                  0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT          0x8078
#define GL_EDGE_FLAG_ARRAY_EXT              0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT            0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT            0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT          0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT           0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT            0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT          0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT           0x8080
#define GL_COLOR_ARRAY_SIZE_EXT             0x8081
#define GL_COLOR_ARRAY_TYPE_EXT             0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT           0x8083
#define GL_COLOR_ARRAY_COUNT_EXT            0x8084
#define GL_INDEX_ARRAY_TYPE_EXT             0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT           0x8086
#define GL_INDEX_ARRAY_COUNT_EXT            0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT     0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT     0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT   0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT    0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT       0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT        0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT         0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT         0x808F
#define GL_COLOR_ARRAY_POINTER_EXT          0x8090
#define GL_INDEX_ARRAY_POINTER_EXT          0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT  0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT      0x8093

/* SGIX_interlace */
#define GL_INTERLACE_SGIX                   0x8094

/* SGIS_detail_texture */
#define GL_DETAIL_TEXTURE_2D_SGIS           0x8095
#define GL_DETAIL_TEXTURE_2D_BINDING_SGIS   0x8096
#define GL_LINEAR_DETAIL_SGIS               0x8097
#define GL_LINEAR_DETAIL_ALPHA_SGIS         0x8098
#define GL_LINEAR_DETAIL_COLOR_SGIS         0x8099
#define GL_DETAIL_TEXTURE_LEVEL_SGIS        0x809A
#define GL_DETAIL_TEXTURE_MODE_SGIS         0x809B
#define GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS  0x809C

/* SGIS_multisample */
#define GL_MULTISAMPLE_SGIS                 0x809D
#define GL_SAMPLE_ALPHA_TO_MASK_SGIS        0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_SGIS         0x809F
#define GL_SAMPLE_MASK_SGIS                 0x80A0
#define GL_1PASS_SGIS                       0x80A1
#define GL_2PASS_0_SGIS                     0x80A2
#define GL_2PASS_1_SGIS                     0x80A3
#define GL_4PASS_0_SGIS                     0x80A4
#define GL_4PASS_1_SGIS                     0x80A5
#define GL_4PASS_2_SGIS                     0x80A6
#define GL_4PASS_3_SGIS                     0x80A7
#define GL_SAMPLE_BUFFERS_SGIS              0x80A8
#define GL_SAMPLES_SGIS                     0x80A9
#define GL_SAMPLE_MASK_VALUE_SGIS           0x80AA
#define GL_SAMPLE_MASK_INVERT_SGIS          0x80AB
#define GL_SAMPLE_PATTERN_SGIS              0x80AC

/* SGIS_sharpen_texture */
#define GL_LINEAR_SHARPEN_SGIS              0x80AD
#define GL_LINEAR_SHARPEN_ALPHA_SGIS        0x80AE
#define GL_LINEAR_SHARPEN_COLOR_SGIS        0x80AF
#define GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS 0x80B0

/* SGI_color_matrix */
#define GL_COLOR_MATRIX                     0x80B1
#define GL_COLOR_MATRIX_SGI                 0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH         0x80B2
#define GL_COLOR_MATRIX_STACK_DEPTH_SGI     0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH     0x80B3
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH_SGI 0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE      0x80B4
#define GL_POST_COLOR_MATRIX_RED_SCALE_SGI  0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE    0x80B5
#define GL_POST_COLOR_MATRIX_GREEN_SCALE_SGI 0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE     0x80B6
#define GL_POST_COLOR_MATRIX_BLUE_SCALE_SGI 0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE    0x80B7
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE_SGI 0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS       0x80B8
#define GL_POST_COLOR_MATRIX_RED_BIAS_SGI   0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS     0x80B9
#define GL_POST_COLOR_MATRIX_GREEN_BIAS_SGI 0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS      0x80BA
#define GL_POST_COLOR_MATRIX_BLUE_BIAS_SGI  0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS     0x80BB
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS_SGI 0x80BB

/* SGI_texture_color_table */
#define GL_TEXTURE_COLOR_TABLE_SGI          0x80BC
#define GL_PROXY_TEXTURE_COLOR_TABLE_SGI    0x80BD

/* SGIX_texture_add_env */
#define GL_TEXTURE_ENV_BIAS_SGIX            0x80BE

/* SGIX_shadow_ambient */
#define GL_SHADOW_AMBIENT_SGIX              0x80BF

/* SGI_color_table */
#define GL_COLOR_TABLE                      0x80D0
#define GL_COLOR_TABLE_SGI                  0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE     0x80D1
#define GL_POST_CONVOLUTION_COLOR_TABLE_SGI 0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE    0x80D2
#define GL_POST_COLOR_MATRIX_COLOR_TABLE_SGI 0x80D2
#define GL_PROXY_COLOR_TABLE                0x80D3
#define GL_PROXY_COLOR_TABLE_SGI            0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE 0x80D4
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE_SGI 0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE 0x80D5
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE_SGI 0x80D5
#define GL_COLOR_TABLE_SCALE                0x80D6
#define GL_COLOR_TABLE_SCALE_SGI            0x80D6
#define GL_COLOR_TABLE_BIAS                 0x80D7
#define GL_COLOR_TABLE_BIAS_SGI             0x80D7
#define GL_COLOR_TABLE_FORMAT               0x80D8
#define GL_COLOR_TABLE_FORMAT_SGI           0x80D8
#define GL_COLOR_TABLE_WIDTH                0x80D9
#define GL_COLOR_TABLE_WIDTH_SGI            0x80D9
#define GL_COLOR_TABLE_RED_SIZE             0x80DA
#define GL_COLOR_TABLE_RED_SIZE_SGI         0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE           0x80DB
#define GL_COLOR_TABLE_GREEN_SIZE_SGI       0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE            0x80DC
#define GL_COLOR_TABLE_BLUE_SIZE_SGI        0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE           0x80DD
#define GL_COLOR_TABLE_ALPHA_SIZE_SGI       0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE       0x80DE
#define GL_COLOR_TABLE_LUMINANCE_SIZE_SGI   0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE       0x80DF
#define GL_COLOR_TABLE_INTENSITY_SIZE_SGI   0x80DF

/* ARB_bgra */
#define GL_BGR                              0x80E0
#define GL_BGRA                             0x80E1

/* ARB_draw_range_elements */
#define GL_MAX_ELEMENTS_VERTICES            0x80E8
#define GL_MAX_ELEMENTS_INDICES             0x80E9

/* SGIS_texture_select */
#define GL_DUAL_ALPHA4_SGIS                 0x8110
#define GL_DUAL_ALPHA8_SGIS                 0x8111
#define GL_DUAL_ALPHA12_SGIS                0x8112
#define GL_DUAL_ALPHA16_SGIS                0x8113
#define GL_DUAL_LUMINANCE4_SGIS             0x8114
#define GL_DUAL_LUMINANCE8_SGIS             0x8115
#define GL_DUAL_LUMINANCE12_SGIS            0x8116
#define GL_DUAL_LUMINANCE16_SGIS            0x8117
#define GL_DUAL_INTENSITY4_SGIS             0x8118
#define GL_DUAL_INTENSITY8_SGIS             0x8119
#define GL_DUAL_INTENSITY12_SGIS            0x811A
#define GL_DUAL_INTENSITY16_SGIS            0x811B
#define GL_DUAL_LUMINANCE_ALPHA4_SGIS       0x811C
#define GL_DUAL_LUMINANCE_ALPHA8_SGIS       0x811D
#define GL_QUAD_ALPHA4_SGIS                 0x811E
#define GL_QUAD_ALPHA8_SGIS                 0x811F
#define GL_QUAD_LUMINANCE4_SGIS             0x8120
#define GL_QUAD_LUMINANCE8_SGIS             0x8121
#define GL_QUAD_INTENSITY4_SGIS             0x8122
#define GL_QUAD_INTENSITY8_SGIS             0x8123
#define GL_DUAL_TEXTURE_SELECT_SGIS         0x8124
#define GL_QUAD_TEXTURE_SELECT_SGIS         0x8125

/* SGIS_point_parameters */
#define GL_POINT_SIZE_MIN_SGIS              0x8126
#define GL_POINT_SIZE_MAX_SGIS              0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_SGIS   0x8128
#define GL_DISTANCE_ATTENUATION_SGIS        0x8129

/* SGIS_fog_function */
#define GL_FOG_FUNC_SGIS                    0x812A
#define GL_FOG_FUNC_POINTS_SGIS             0x812B
#define GL_MAX_FOG_FUNC_POINTS_SGIS         0x812C

/* SGIS_texture_border_clamp */
#define GL_CLAMP_TO_BORDER_SGIS             0x812D

/* SGIX_texture_multi_buffer */
#define GL_TEXTURE_MULTI_BUFFER_HINT_SGIX   0x812E

/* SGIS_texture_edge_clamp */
#define GL_CLAMP_TO_EDGE                    0x812F
#define GL_CLAMP_TO_EDGE_SGIS               0x812F

/* SGIS_texture4D */
#define GL_PACK_SKIP_VOLUMES_SGIS           0x8130
#define GL_PACK_IMAGE_DEPTH_SGIS            0x8131
#define GL_UNPACK_SKIP_VOLUMES_SGIS         0x8132
#define GL_UNPACK_IMAGE_DEPTH_SGIS          0x8133
#define GL_TEXTURE_4D_SGIS                  0x8134
#define GL_PROXY_TEXTURE_4D_SGIS            0x8135
#define GL_TEXTURE_4DSIZE_SGIS              0x8136
#define GL_TEXTURE_WRAP_Q_SGIS              0x8137
#define GL_MAX_4D_TEXTURE_SIZE_SGIS         0x8138

/* SGIX_pixel_texture */
#define GL_PIXEL_TEX_GEN_SGIX               0x8139
#define GL_PIXEL_TEX_GEN_MODE_SGIX          0x832B

/* SGIS_texture_lod */
#define GL_TEXTURE_MIN_LOD                  0x813A
#define GL_TEXTURE_MIN_LOD_SGIS             0x813A
#define GL_TEXTURE_MAX_LOD                  0x813B
#define GL_TEXTURE_MAX_LOD_SGIS             0x813B
#define GL_TEXTURE_BASE_LEVEL               0x813C
#define GL_TEXTURE_BASE_LEVEL_SGIS          0x813C
#define GL_TEXTURE_MAX_LEVEL                0x813D
#define GL_TEXTURE_MAX_LEVEL_SGIS           0x813D

/* SGIX_pixel_tiles */
#define GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX   0x813E
#define GL_PIXEL_TILE_CACHE_INCREMENT_SGIX  0x813F
#define GL_PIXEL_TILE_WIDTH_SGIX            0x8140
#define GL_PIXEL_TILE_HEIGHT_SGIX           0x8141
#define GL_PIXEL_TILE_GRID_WIDTH_SGIX       0x8142
#define GL_PIXEL_TILE_GRID_HEIGHT_SGIX      0x8143
#define GL_PIXEL_TILE_GRID_DEPTH_SGIX       0x8144
#define GL_PIXEL_TILE_CACHE_SIZE_SGIX       0x8145

/* SGIS_texture_filter4 */
#define GL_FILTER4_SGIS                     0x8146
#define GL_TEXTURE_FILTER4_SIZE_SGIS        0x8147

/* SGIX_sprite */
#define GL_SPRITE_SGIX                      0x8148
#define GL_SPRITE_MODE_SGIX                 0x8149
#define GL_SPRITE_AXIS_SGIX                 0x814A
#define GL_SPRITE_TRANSLATION_SGIX          0x814B
#define GL_SPRITE_AXIAL_SGIX                0x814C
#define GL_SPRITE_OBJECT_ALIGNED_SGIX       0x814D
#define GL_SPRITE_EYE_ALIGNED_SGIX          0x814E

/* SGIS_texture4D */
#define GL_TEXTURE_4D_BINDING_SGIS          0x814F

/* ARB_convolution_border_modes */
#define GL_IGNORE_BORDER                    0x8150
#define GL_CONSTANT_BORDER                  0x8151
#define GL_WRAP_BORDER                      0x8152
#define GL_REPLICATE_BORDER                 0x8153
#define GL_CONVOLUTION_BORDER_COLOR         0x8154

/* SGIX_clipmap */
#define GL_LINEAR_CLIPMAP_LINEAR_SGIX       0x8170
#define GL_TEXTURE_CLIPMAP_CENTER_SGIX      0x8171
#define GL_TEXTURE_CLIPMAP_FRAME_SGIX       0x8172
#define GL_TEXTURE_CLIPMAP_OFFSET_SGIX      0x8173
#define GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX 0x8174
#define GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX  0x8175
#define GL_TEXTURE_CLIPMAP_DEPTH_SGIX       0x8176
#define GL_MAX_CLIPMAP_DEPTH_SGIX           0x8177
#define GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX   0x8178

/* SGIX_texture_scale_bias */
#define GL_POST_TEXTURE_FILTER_BIAS_SGIX    0x8179
#define GL_POST_TEXTURE_FILTER_SCALE_SGIX   0x817A
#define GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX 0x817B
#define GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX 0x817C

/* SGIX_reference_plane */
#define GL_REFERENCE_PLANE_SGIX             0x817D
#define GL_REFERENCE_PLANE_EQUATION_SGIX    0x817E

/* SGIX_ir_instrument1 */
#define GL_IR_INSTRUMENT1_SGIX              0x817F

/* SGIX_instruments */
#define GL_INSTRUMENT_BUFFER_POINTER_SGIX   0x8180
#define GL_INSTRUMENT_MEASUREMENTS_SGIX     0x8181

/* SGIX_list_priority */
#define GL_LIST_PRIORITY_SGIX               0x8182

/* SGIX_calligraphic_fragment */
#define GL_CALLIGRAPHIC_FRAGMENT_SGIX       0x8183

/* SGIX_impact_pixel_texture */
#define GL_PIXEL_TEX_GEN_Q_CEILING_SGIX     0x8184
#define GL_PIXEL_TEX_GEN_Q_ROUND_SGIX       0x8185
#define GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX       0x8186
#define GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX 0x8187
#define GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX 0x8188
#define GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX      0x8189
#define GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX      0x818A

/* SGIX_framezoom */
#define GL_FRAMEZOOM_SGIX                   0x818B
#define GL_FRAMEZOOM_FACTOR_SGIX            0x818C
#define GL_MAX_FRAMEZOOM_FACTOR_SGIX        0x818D

/* SGIX_texture_lod_bias */
#define GL_TEXTURE_LOD_BIAS_S_SGIX          0x818E
#define GL_TEXTURE_LOD_BIAS_T_SGIX          0x818F
#define GL_TEXTURE_LOD_BIAS_R_SGIX          0x8190

/* SGIS_generate_mipmap */
#define GL_GENERATE_MIPMAP_SGIS             0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS        0x8192

/* SGIX_polynomial_ffd */
#define GL_GEOMETRY_DEFORMATION_SGIX        0x8194
#define GL_TEXTURE_DEFORMATION_SGIX         0x8195
#define GL_DEFORMATIONS_MASK_SGIX           0x8196
#define GL_MAX_DEFORMATION_ORDER_SGIX       0x8197

/* SGIX_fog_offset */
#define GL_FOG_OFFSET_SGIX                  0x8198
#define GL_FOG_OFFSET_VALUE_SGIX            0x8199

/* SGIX_shadow */
#define GL_TEXTURE_COMPARE_SGIX             0x819A
#define GL_TEXTURE_COMPARE_OPERATOR_SGIX    0x819B
#define GL_TEXTURE_LEQUAL_R_SGIX            0x819C
#define GL_TEXTURE_GEQUAL_R_SGIX            0x819D

/* SGIX_depth_texture */
#define GL_DEPTH_COMPONENT16_SGIX           0x81A5
#define GL_DEPTH_COMPONENT24_SGIX           0x81A6
#define GL_DEPTH_COMPONENT32_SGIX           0x81A7

/* SGIX_ycrcb */
#define GL_YCRCB_422_SGIX                   0x81BB
#define GL_YCRCB_444_SGIX                   0x81BC

/* SGIS_point_line_texgen */
#define GL_EYE_DISTANCE_TO_POINT_SGIS       0x81F0
#define GL_OBJECT_DISTANCE_TO_POINT_SGIS    0x81F1
#define GL_EYE_DISTANCE_TO_LINE_SGIS        0x81F2
#define GL_OBJECT_DISTANCE_TO_LINE_SGIS     0x81F3
#define GL_EYE_POINT_SGIS                   0x81F4
#define GL_OBJECT_POINT_SGIS                0x81F5
#define GL_EYE_LINE_SGIS                    0x81F6
#define GL_OBJECT_LINE_SGIS                 0x81F7

/* ARB_separate_specular_color */
#define GL_LIGHT_MODEL_COLOR_CONTROL        0x81F8
#define GL_SINGLE_COLOR                     0x81F9
#define GL_SEPARATE_SPECULAR_COLOR          0x81FA

/* EXT_packed_pixels */
#define GL_UNSIGNED_SHORT_5_6_5             0x8362
#define GL_UNSIGNED_SHORT_5_6_5_EXT         0x8362
#define GL_UNSIGNED_BYTE_2_3_3_REV          0x8363
#define GL_UNSIGNED_BYTE_2_3_3_REV_EXT      0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV         0x8364
#define GL_UNSIGNED_SHORT_5_6_5_REV_EXT     0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV       0x8365
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT   0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV       0x8366
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT   0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV         0x8367
#define GL_UNSIGNED_INT_8_8_8_8_REV_EXT     0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV      0x8368
#define GL_UNSIGNED_INT_2_10_10_10_REV_EXT  0x8368

/*************************************************************/


/* EXT_vertex_array */
#define GL_VERTEX_ARRAY_EXT               0x8074
#define GL_NORMAL_ARRAY_EXT               0x8075
#define GL_COLOR_ARRAY_EXT                0x8076
#define GL_INDEX_ARRAY_EXT                0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT        0x8078
#define GL_EDGE_FLAG_ARRAY_EXT            0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT          0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT          0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT        0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT         0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT          0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT        0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT         0x8080
#define GL_COLOR_ARRAY_SIZE_EXT           0x8081
#define GL_COLOR_ARRAY_TYPE_EXT           0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT         0x8083
#define GL_COLOR_ARRAY_COUNT_EXT          0x8084
#define GL_INDEX_ARRAY_TYPE_EXT           0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT         0x8086
#define GL_INDEX_ARRAY_COUNT_EXT          0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT   0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT   0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT 0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT  0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT     0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT      0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT       0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT       0x808F
#define GL_COLOR_ARRAY_POINTER_EXT        0x8090
#define GL_INDEX_ARRAY_POINTER_EXT        0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT 0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT    0x8093
//#define GL_DOUBLE_EXT                     GL_DOUBLE

/* EXT_bgra */
#define GL_BGR_EXT                        0x80E0
#define GL_BGRA_EXT                       0x80E1

/* EXT_paletted_texture */

/* These must match the GL_COLOR_TABLE_*_SGI enumerants */
#define GL_COLOR_TABLE_FORMAT_EXT         0x80D8
#define GL_COLOR_TABLE_WIDTH_EXT          0x80D9
#define GL_COLOR_TABLE_RED_SIZE_EXT       0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_EXT     0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_EXT      0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT     0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT 0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT 0x80DF

#define GL_COLOR_INDEX1_EXT               0x80E2
#define GL_COLOR_INDEX2_EXT               0x80E3
#define GL_COLOR_INDEX4_EXT               0x80E4
#define GL_COLOR_INDEX8_EXT               0x80E5
#define GL_COLOR_INDEX12_EXT              0x80E6
#define GL_COLOR_INDEX16_EXT              0x80E7

/* WIN_draw_range_elements */
#define GL_MAX_ELEMENTS_VERTICES_WIN      0x80E8
#define GL_MAX_ELEMENTS_INDICES_WIN       0x80E9

/* WIN_phong_shading */
#define GL_PHONG_WIN                      0x80EA 
#define GL_PHONG_HINT_WIN                 0x80EB 

/* WIN_specular_fog */
#define GL_FOG_SPECULAR_TEXTURE_WIN       0x80EC

#ifdef __cplusplus
}
#endif

#endif

#endif /* GLCONTEXT_GL_H */

