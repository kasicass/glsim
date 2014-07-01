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

#include <windows.h>
#include <stdio.h>

#include "gllocal.h"
#include "glcore/glcore.h"
#include "glcontext/glcontext.h"

#define check_for_gdi_error() check_for_gdi_error_func(__FILE__, __LINE__); 

static const PIXELFORMATDESCRIPTOR glsim_pfd = {
    sizeof(glsim_pfd),    /* nSize */
    1,                    /* nVersion */
    PFD_DRAW_TO_WINDOW | 
    PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,   /* dwFlags */
    PFD_TYPE_RGBA,        /* iPixelType */
    32,                   /* cColorBits */
    8,                    /* cRedBits */
    24,                   /* cRedShift */ 
    8,                    /* cGreenBits */    
    16,                   /* cGreenShift */
    8,                    /* cBlueBits */
    8,                    /* cBlueShift */
    8,                    /* cAlphaBits */
    0,                    /* cAlphaShift */
    0,                    /* cAccumBits */
    0,                    /* cAccumRedBits */
    0,                    /* cAccumGreenBits */
    0,                    /* cAccumBlueBits */
    0,                    /* cAccumAlphaBits */
    32,                   /* cDepthBits */
    8,                    /* cStencilBits */
    0,                    /* cAuxBuffers */
    PFD_MAIN_PLANE,       /* iLayerType */
    0,                    /* bReserved */
    0,                    /* dwLayerMask */
    0,                    /* dwVisableMask */
    0                     /* dwDamageMask */
};
    
typedef struct fblist *fblist_p;
typedef struct fblist {
  HDC hdc;
  GLframebuffer *fb;
  fblist_p next;
} fblist;

fblist *fbroot = NULL;
HDC cur_hdc = NULL;
HWND cur_hwnd = NULL;

BOOL WINAPI
DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
  UNUSED(hinstDLL);
  UNUSED(fdwReason);
  UNUSED(lpvReserved);

  return 1;
}

static void
check_for_gdi_error_func (char *file, int line) {
  int iErr;
  LPVOID lpMsgBuf;
  char msg[2048];

  sprintf (msg, "Error: %s:%d", file, line);

  iErr = GetLastError();
    
  if (iErr) {
    FormatMessage( 
      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM | 
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      iErr,
      0, // Default language
      (LPTSTR) &lpMsgBuf,
      0,
      NULL 
      );
    // Process any inserts in lpMsgBuf.
    // ...
    // Display the string.
    MessageBox( NULL, (LPCTSTR)lpMsgBuf, msg, MB_OK | MB_ICONINFORMATION );
    // Free the buffer.
    LocalFree( lpMsgBuf );    
  }
}

/* note: image data is unsigned int 0xaarrggbb */
void
__gllocal_Draw (unsigned int *data, int x, int y, int w, int h, int dy)
{
  static BITMAPINFO *img;
  static BITMAPV4HEADER *bmi;

  HDC hdc;

  if (!img && !bmi) {
    img = (BITMAPINFO *) malloc (sizeof (BITMAPV4HEADER));
    bmi = (BITMAPV4HEADER *) &img->bmiHeader;
  }

  memset(bmi, 0, sizeof(bmi));
  bmi->bV4Size          = sizeof(BITMAPINFOHEADER);
  bmi->bV4Width         = w;
  bmi->bV4Height        = h;
  bmi->bV4Planes        = 1;
  bmi->bV4BitCount      = 32;
  bmi->bV4V4Compression = BI_BITFIELDS;
  bmi->bV4SizeImage     = 0;
  bmi->bV4BlueMask      = 0x00ff0000;
  bmi->bV4GreenMask     = 0x0000ff00;
  bmi->bV4RedMask       = 0x000000ff;

  SetLastError(0);
  
  hdc = GetDC(cur_hwnd);

  check_for_gdi_error();
  
  SetDIBitsToDevice(hdc,
    0,0,
    w,h,
    0,0,
    0,h,
    data,
    img, DIB_RGB_COLORS);

  check_for_gdi_error();

  ReleaseDC(cur_hwnd, hdc);

  check_for_gdi_error();
}

void __gllocal_Sync(void) {
  /* Do nothing */
}

int WINAPI
wglChoosePixelFormat_prox( HDC hdc, CONST PIXELFORMATDESCRIPTOR *pfd )
{
  DWORD okayFlags;

  if ( pfd->nSize != sizeof(*pfd) || pfd->nVersion != 1 ) {
    fprintf( stderr, "wglChoosePixelFormat: bad pfd\n" );
    return 0;
  }


  okayFlags = ( PFD_DRAW_TO_WINDOW        |
    PFD_SUPPORT_GDI           |
    PFD_SUPPORT_OPENGL        |
    PFD_DOUBLEBUFFER          |
    PFD_DOUBLEBUFFER_DONTCARE |
    PFD_STEREO_DONTCARE       |
    PFD_DEPTH_DONTCARE        );

  if ( pfd->dwFlags & ~okayFlags ) {
    fprintf ( stderr, "wglChoosePixelFormat: only "
      "support flags=0x%x", okayFlags );
    fprintf ( stderr, "wglChoosePixelFormat: you gave "
      "me flags=0x%x", pfd->dwFlags );
    return 0;
  }
  
  if ( pfd->iPixelType != glsim_pfd.iPixelType ) {
    fprintf ( stderr , "wglChoosePixelFormat: only "
      "support RGBA\n" );
    return 0;
  }
  
  if ( pfd->cColorBits > glsim_pfd.cColorBits ||
    pfd->cRedBits   > glsim_pfd.cRedBits  ||
    pfd->cGreenBits > glsim_pfd.cGreenBits  ||
    pfd->cBlueBits  > glsim_pfd.cBlueBits  ||
    pfd->cAlphaBits > glsim_pfd.cAlphaBits ) {
    fprintf ( stderr , "wglChoosePixelFormat: too much "
      "color precision requested\n" );
    return 0;
  }
  
  if ( pfd->cAccumBits   > glsim_pfd.cAccumBits ||
    pfd->cAccumRedBits   > glsim_pfd.cAccumRedBits ||
    pfd->cAccumGreenBits > glsim_pfd.cAccumGreenBits ||
    pfd->cAccumBlueBits  > glsim_pfd.cAccumBlueBits ||
    pfd->cAccumAlphaBits > glsim_pfd.cAccumAlphaBits ) {
    fprintf ( stderr , "wglChoosePixelFormat: asked for "
      "accumulation buffer, ignoring\n" );
  }
  
  if ( pfd->cDepthBits > glsim_pfd.cDepthBits ) {
    fprintf ( stderr , "wglChoosePixelFormat; asked for "
      "too many depth bits\n" );
    return 0;
  }
  
  if ( pfd->cStencilBits > glsim_pfd.cStencilBits ) {
    fprintf ( stderr , "wglChoosePixelFormat: asked for "
      "too many stencil bits\n" );
    return 0;
  }
  
  if ( pfd->cAuxBuffers > glsim_pfd.cAuxBuffers ) {
    fprintf ( stderr , "wglChoosePixelFormat: asked for "
      "aux buffers\n" );
    return 0;
  }
  
  if ( pfd->iLayerType != glsim_pfd.iLayerType ) {
    fprintf ( stderr , "wglChoosePixelFormat: asked for "
      "a strange layer\n" );
    return 0;
  }
  

  return 1;
}

BOOL WINAPI
wglSetPixelFormat_prox( HDC hdc, int pixelFormat, 
						CONST PIXELFORMATDESCRIPTOR *pdf )
{  
  fblist *f = (fblist *) malloc (sizeof (fblist));
  GLframebuffer *fb;
  HWND hwnd;
  RECT rect;
  int width, height;

  if ( pixelFormat != 1 ) {
    fprintf ( stderr , "wglSetPixelFormat: "
      "pixelFormat=%d?\n", pixelFormat );
    return 0;
  }

  SetLastError(0);
  
  /* Get the window width, height */
  hwnd = WindowFromDC(hdc);
  GetClientRect(hwnd, &rect);
  width = rect.right - rect.left;
  height = rect.bottom - rect.top;

  check_for_gdi_error();

  /* Create a framebuffer */
  fb = __glcore_CreateFrameBuffer(width, height, 
    pdf->dwFlags & PFD_DOUBLEBUFFER,
    (GLDrawFunc) __gllocal_Draw,
    (GLSyncFunc) __gllocal_Sync);

  f->fb = fb;
  f->hdc = hdc;
  f->next = fbroot;
  fbroot = f;

  return 1;
}

BOOL WINAPI
wglDeleteContext_prox( HGLRC hglrc )
{
  fprintf ( stderr , "wglDeleteContext: ignoring" );
  return 1;
}

BOOL WINAPI
wglMakeCurrent_prox( HDC hdc, HGLRC hglrc )
{
  fblist *f;
  /* Find the framebuffer */
  for (f=fbroot; f && f->hdc != hdc; f = f->next);

  if (!f) {
    fprintf ( stderr, "wglMakeCurrent: Unable to find framebuffer for hdc");
    return 0;
  }

  SetLastError(0);
  
  __gllocal_MakeCurrent(f->fb, (GLcontext *) hglrc);

  check_for_gdi_error();

  cur_hdc = hdc;
  cur_hwnd = WindowFromDC(hdc);

  check_for_gdi_error();

	return 1;
}

HGLRC WINAPI
wglGetCurrentContext_prox( void )
{
	return (HGLRC) __gllocal_GetCurrentContext();
}

HDC WINAPI
wglGetCurrentDC_prox( void )
{	
	return cur_hdc;
}

int WINAPI
wglGetPixelFormat_prox( HDC hdc )
{

	/* this is what we call our generic pixelformat, regardless of the HDC */
	return 1;
}

int WINAPI
wglDescribePixelFormat_prox( HDC hdc, int pixelFormat, UINT nBytes,
							 LPPIXELFORMATDESCRIPTOR pfd )
{
  
  /* if pfd is null, then its a query */
  if ( pfd == NULL )
  {
  /*  Note that we return 2 when we really
  **  only export 1.  This is to fix a 
  **  common glut bug since it assumes that
  **  identifiers start with 0.  LAME!
  */
    return 2;
  }
  
  if ( pixelFormat != 1 ) {
    fprintf ( stderr , "wglDescribePixelFormat: "
      "pixelFormat=%d?\n", pixelFormat );
    
    if (pfd && nBytes)
      memset (pfd, 0, nBytes);
    
    return 0;
  }
  
  if ( nBytes != sizeof(*pfd) ) {
    fprintf ( stderr , "wglDescribePixelFormat: "
      "nBytes=%u?\n", nBytes );
    return 0;
  }
  
  *pfd = glsim_pfd;
  
  /* the max PFD index */
  return 1;
}

HGLRC WINAPI
wglCreateContext_prox( HDC hdc )
{
  GLconfig *cfg;
  HGLRC hglrc;

  cfg = __glconfig_CreateDefaultConfig();
	hglrc = (HGLRC) 	__gllocal_CreateContext( cfg );
  __glconfig_FreeConfig(cfg);

  return hglrc;
}

BOOL WINAPI
wglSwapBuffers_prox( HDC hdc )
{

  if (hdc != cur_hdc) {
    MessageBox(NULL, "Error", "hdc != cur_hdc", MB_OK);
    return 0;
  }
	__gllocal_SwapBuffers( );
	return 1;
}


/************** 
** Everthing below here is unsupported
***************/

BOOL WINAPI
wglShareLists_prox( HGLRC hglrc1, HGLRC hglrc2 )
{

	fprintf ( stderr , "wglShareLists: unsupported" );
	return 0;
}


BOOL WINAPI
wglCopyContext_prox( HGLRC src, HGLRC dst, UINT mask )
{

	fprintf ( stderr ,"wglCopyContext: unsupported" );
	return 0;
}

HGLRC WINAPI
wglCreateLayerContext_prox( HDC hdc, int layerPlane )
{

	fprintf ( stderr ,"wglCreateLayerContext: unsupported" );
	return 0;
}

PROC WINAPI
wglGetProcAddress_prox( LPCSTR name )
{
	fprintf ( stderr ,"wglGetProcAddress: unsupported" );
	return (PROC) 0;
}

BOOL WINAPI
wglUseFontBitmapsA_prox( HDC hdc, DWORD first, DWORD count, DWORD listBase )
{
	fprintf ( stderr, "wglUseFontBitmapsA: unsupported" );
	return 0;
}

BOOL WINAPI
wglUseFontBitmapsW_prox( HDC hdc, DWORD first, DWORD count, DWORD listBase )
{

	fprintf ( stderr , "wglUseFontBitmapsW: unsupported" );
	return 0;
}

BOOL WINAPI
wglDescribeLayerPlane_prox( HDC hdc, int pixelFormat, int layerPlane,
							UINT nBytes, LPLAYERPLANEDESCRIPTOR lpd )
{
	fprintf ( stderr ,"wglDescribeLayerPlane: unimplemented" );
	return 0;
}

int WINAPI
wglSetLayerPaletteEntries_prox( HDC hdc, int layerPlane, int start,
								int entries, CONST COLORREF *cr )
{
	fprintf ( stderr , "wglSetLayerPaletteEntries: unsupported" );
	return 0;
}

int WINAPI
wglGetLayerPaletteEntries_prox( HDC hdc, int layerPlane, int start,
								int entries, COLORREF *cr )
{
	fprintf ( stderr , "wglGetLayerPaletteEntries: unsupported" );
	return 0;
}

BOOL WINAPI
wglRealizeLayerPalette_prox( HDC hdc, int layerPlane, BOOL realize )
{

	fprintf ( stderr , "wglRealizeLayerPalette: unsupported" );
	return 0;
}

DWORD WINAPI
wglSwapMultipleBuffers_prox( UINT a, CONST void *b )
{

	fprintf ( stderr , "wglSwapMultipleBuffer: unsupported" );
	return 0;
}

BOOL WINAPI
wglUseFontOutlinesA_prox( HDC hdc, DWORD first, DWORD count, DWORD listBase,
						  FLOAT deviation, FLOAT extrusion, int format,
						  LPGLYPHMETRICSFLOAT gmf )
{

	fprintf ( stderr , "wglUseFontOutlinesA: unsupported" );
	return 0;
}

BOOL WINAPI
wglUseFontOutlinesW_prox( HDC hdc, DWORD first, DWORD count, DWORD listBase,
						  FLOAT deviation, FLOAT extrusion, int format,
						  LPGLYPHMETRICSFLOAT gmf )
{
	fprintf ( stderr , "wglUseFontOutlinesW: unsupported" );
	return 0;
}

BOOL WINAPI
wglSwapLayerBuffers_prox( HDC hdc, UINT planes )
{

	fprintf ( stderr , "wglSwapLayerBuffers: unsupported" );
	return 0;
}
