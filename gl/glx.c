/* opengl_stub/glx.c */

#include <X11/X.h>
#include <GL/glx.h>
#include <stdio.h>

#include "gllocal.h"
#include "glcore/glcore.h"
#include "glcontext/glcontext.h"
#include "glcontext/glconfig.h"

/* XXX: Only support one window */
static Display     *cur_display;
static Drawable     cur_drawable;
static XVisualInfo *cur_visinfo;
static GC           cur_gc;
static int          cur_width;
static int          cur_height;

static int
find_shift (unsigned int mask)
{
    int shift;
    for (shift = 31; shift > 0; shift--)
	if (mask & (1 << shift))
	    break;
    return shift;
}

#define RED_MASK   0x000000ff
#define GREEN_MASK 0x0000ff00
#define BLUE_MASK  0x00ff0000

#define max(a,b) (((a)>(b))?(a):(b))

/* note: image data is unsigned int 0xaarrggbb */
void
__gllocal_Draw (unsigned int *data, int x, int y, int w, int h, int dy)
{
    static XImage *img = NULL;
    static imgarea = -1;

    int rlshift, glshift, blshift;
    int rrshift, grshift, brshift;
    int rmask, gmask, bmask;
    int bpp;
    int xx, yy;
  
    if (!img) {
	img = XCreateImage (cur_display, cur_visinfo->visual,
			    cur_visinfo->depth, ZPixmap, 0, NULL, cur_width,
			    cur_height, 8, 0);
    }

    bpp = img->bits_per_pixel / 8;

    if (cur_width * cur_height > imgarea) {
	if (img->data)
	    free(img->data);
	img->data = malloc(bpp * cur_width * cur_height);
	imgarea = cur_width * cur_height;
    }

    img->width = w;
    img->height = h;
    img->xoffset = 0;
    img->bytes_per_line = bpp * w;

    rrshift = find_shift(RED_MASK) - find_shift(img->red_mask);
    grshift = find_shift(GREEN_MASK) - find_shift(img->green_mask);
    brshift = find_shift(BLUE_MASK) - find_shift(img->blue_mask);

    rlshift = max(-rrshift, 0); rrshift = max(rrshift, 0);
    glshift = max(-grshift, 0); grshift = max(grshift, 0);
    blshift = max(-brshift, 0); brshift = max(brshift, 0);

    rmask = RED_MASK & ((img->red_mask << rrshift) >> rlshift);
    gmask = GREEN_MASK & ((img->green_mask << grshift) >> glshift);
    bmask = BLUE_MASK & ((img->blue_mask << brshift) >> blshift);

    for (yy = 0; yy < h; yy++) {
	unsigned int *row = &data[(h - 1 - yy) * dy];
	for (xx = 0; xx < w; xx++) {
	    int srcval = *row++;
	    int dstval = ((((srcval & rmask) >> rrshift) << rlshift) |
			  (((srcval & gmask) >> grshift) << glshift) |
			  (((srcval & bmask) >> brshift) << blshift));
	    XPutPixel(img, xx, yy, dstval);
	}
    }

    XPutImage (cur_display, cur_drawable, cur_gc, img, 0, 0, x, y, w, h);
}

void __gllocal_Sync (void)
{
  XSync(cur_display, 0);
}

static XVisualInfo *
ReasonableVisual( Display *dpy, int screen )
{
  int i, n;
  XVisualInfo vis_template, *visual, *best;
  
  /* find the set of all visuals for this display/screen */
  vis_template.screen = screen;
  visual = XGetVisualInfo( dpy, VisualScreenMask, &vis_template, &n );
  if ( visual == NULL || n < 1 )
    {
      fprintf( stderr, "glXChooseVisual: "
	       "XGetVisualInfo() found no matches?" );
      return NULL;
    }
  
  /* now see if we can find a TrueColor/DirectColor visual */
  best = NULL;
  for ( i = 0; i < n; i++ )
    {
      if ( visual[i].class == TrueColor || visual[i].class == DirectColor )
	{
	  best = &visual[i];
	}
    }
  
  if ( best ) {
    XVisualInfo *besttrue, *bestdirect;
    
    besttrue = bestdirect = NULL;
    
    /* okay, select the RGB visual with the most depth */
    for ( i = 0; i < n; i++ )
      {
	if ( visual[i].class == TrueColor &&
	     (besttrue == NULL || 
	      (visual[i].depth > besttrue->depth) ||
	      ((visual[i].depth == besttrue->depth) &&
	       visual[i].bits_per_rgb > besttrue->bits_per_rgb)) )
	  {
	    besttrue = &visual[i];
	  }
	if ( visual[i].class == DirectColor &&
	     (bestdirect == NULL ||
	      (visual[i].depth > bestdirect->depth) ||
	      ((visual[i].depth == bestdirect->depth) &&
	       visual[i].bits_per_rgb > bestdirect->bits_per_rgb)) )
	  {
	    bestdirect = &visual[i];
	  }
      }
    best = besttrue;
    if(best == NULL ||
       (bestdirect != NULL
	&& ((bestdirect->depth > best->depth) ||
	    ((bestdirect->depth == best->depth) &&
	     (bestdirect->bits_per_rgb > best->bits_per_rgb)))))
      best = bestdirect;
  }
  else
    {
      /* no RGB visuals, select the deepest colorindex visual */
      /* NOTE: this code is likely never ever executed */
      /* we don't have to check for TrueColor/DirectColor, since
       * we know none of those exist */
      best = &visual[0];
      for ( i = 1; i < n; i++ )
	{
	  if ( visual[i].depth > best->depth )
	    {
	      best = &visual[i];
	    }
	}
    }
  
  vis_template.screen = screen;
  vis_template.visualid = best->visualid;
  
  XFree( visual );
  
  visual = XGetVisualInfo( dpy, VisualScreenMask | VisualIDMask,
			   &vis_template, &n );
  
  if ( visual == NULL || n != 1 )
    {
      fprintf( stderr, "glXChooseVisual: XGetVisualInfo( visualid=%d ) failed!",
	       vis_template.visualid );
      return NULL;
    }
  
  return visual;
}

XVisualInfo *
glXChooseVisual( Display *dpy, int screen, int *attribList )
{
  int *attrib;
  int wants_rgb = 0;
  int wants_doublebuffer = 0;

  XVisualInfo *visinfo;
    
  for ( attrib = attribList; *attrib != None; attrib++ )
    {
      switch ( *attrib )
	{
	case GLX_USE_GL:
	  /* ignored, this is mandatory */
	  break;
	  
	case GLX_BUFFER_SIZE:
	  /* this is for color-index visuals, which we don't support */
	  attrib++;
	  break;
	  
	case GLX_LEVEL:
	  {
	    int level = attrib[1];
	    if ( level != 0 )
	      {
		fprintf( stderr, "glXChooseVisual: "
			 "level=%d unsupported\n", level );
		return NULL;
	      }
	  }
	  attrib++;
	  break;
	  
	case GLX_RGBA:
	  wants_rgb = 1;
	  break;
	  
	case GLX_DOUBLEBUFFER:
	  wants_doublebuffer = 1;
	  break;
	  
	case GLX_STEREO:
	  fprintf( stderr, "glXChooseVisual: stereo "
		   "unsupported\n" );
	  return NULL;
	  
	case GLX_AUX_BUFFERS:
	  {
	    int aux_buffers = attrib[1];
	    if ( aux_buffers != 0 )
	      {
		fprintf( stderr, "glXChooseVisual: "
			 "aux_buffers=%d unsupported\n", aux_buffers );
		return NULL;
	      }
	  }
	  attrib++;
	  break;
	  
	case GLX_RED_SIZE:
	case GLX_GREEN_SIZE:
	case GLX_BLUE_SIZE:
	case GLX_ALPHA_SIZE:
	case GLX_DEPTH_SIZE:
	case GLX_STENCIL_SIZE:
	  /* ignored */
	  attrib++;
	  break;
	  
	case GLX_ACCUM_RED_SIZE:
	case GLX_ACCUM_GREEN_SIZE:
	case GLX_ACCUM_BLUE_SIZE:
	case GLX_ACCUM_ALPHA_SIZE:
	  /* unsupported */
	  {
	    int accum_size = attrib[1];
	    if ( accum_size != 0 )
	      {
		fprintf( stderr, "glXChooseVisual: "
			 "accum_size=%d unsupported\n", accum_size );
		return NULL;
	      }
	  }
	  attrib++;
	  break;
	  
	default:
	  fprintf( stderr, "glXChooseVisual: bad "
		   "attrib=0x%x", *attrib );
	  return NULL;
	}
    }
  
  if ( !wants_rgb )
    {
      fprintf( stderr, "glXChooseVisual: didn't request "
	       "RGB visual?" );
      return NULL;
    }

  visinfo = ReasonableVisual( dpy, screen );

  /* Hack!  Choose a visual id so we can identify user's wants later. */
  /* We don't interpret visual id.  User should not interpret visual id. */
  /* So we can use visual id to store user's wants. */

  visinfo->visualid = wants_doublebuffer;

  return visinfo;
}

#if 0

void
glXCopyContext( Display *dpy, GLXContext src, GLXContext dst, GLuint mask )
{
  fprintf( stderr, "Unsupported GLX Call: glXCopyContext()" );
}

#endif

GLXContext
glXCreateContext( Display *dpy, XVisualInfo *vis, GLXContext share,
                  Bool direct )
{
  static int first = 1;
  GLconfig *cfg;
  GLcontext *ctx;
  
  if (!first) {
    fprintf( stderr, "glXCreateContext() called more than once, "
	     "but WireGL only allows 1 window!" );
    return NULL;
  }

  first = 0;
  cur_visinfo = vis;

  cfg = __glconfig_CreateDefaultConfig();
  cfg->doublebuffer = vis->visualid;
  ctx = __gllocal_CreateContext(cfg);
  __glconfig_FreeConfig(cfg);
    
  return (GLXContext)ctx;
}

GLXPixmap
glXCreateGLXPixmap( Display *dpy, XVisualInfo *vis, Pixmap pixmap )
{
  fprintf( stderr, "Unsupported GLX Call: glXCreateGLXPixmap()" );
  return (GLXPixmap) 0;
}

void
glXDestroyContext( Display *dpy, GLXContext ctx )
{
  fprintf( stderr, "Unsupported GLX Call: glXDestroyContext()" );
}

void
glXDestroyGLXPixmap( Display *dpy, GLXPixmap pix )
{
  fprintf( stderr, "Unsupported GLX Call: glXDestroyGLXPixmap()" );
}

int
glXGetConfig( Display *dpy, XVisualInfo *vis, int attrib, int *value )
{
  switch ( attrib ) {
    
  case GLX_USE_GL:
    *value = 1;
    break;
    
  case GLX_BUFFER_SIZE:
    *value = 32;
    break;
    
  case GLX_LEVEL:
    *value = 0;
    break;
    
  case GLX_RGBA:
    *value = 1;
    break;
    
  case GLX_DOUBLEBUFFER:
    *value = vis->visualid;
    break;
    
  case GLX_STEREO:
    *value = 0;
    break;
    
  case GLX_AUX_BUFFERS:
    *value = 0;
    break;
    
  case GLX_RED_SIZE:
    *value = 8;
    break;
    
  case GLX_GREEN_SIZE:
    *value = 8;
    break;
    
  case GLX_BLUE_SIZE:
    *value = 8;
    break;
    
  case GLX_ALPHA_SIZE:
    *value = 8;
    break;
    
  case GLX_DEPTH_SIZE:
    *value = 24;
    break;
    
  case GLX_STENCIL_SIZE:
    *value = 8;
    break;

  case GLX_ACCUM_RED_SIZE:
    *value = 0;
    break;
    
  case GLX_ACCUM_GREEN_SIZE:
    *value = 0;
    break;
    
  case GLX_ACCUM_BLUE_SIZE:
    *value = 0;
    break;
    
  case GLX_ACCUM_ALPHA_SIZE:
        *value = 0;
        break;
	
  default:
    return GLX_BAD_ATTRIBUTE;
  }
  
  return 0;
}

GLXContext
glXGetCurrentContext( void )
{
  static int first = 1;

  if (first) {
    fprintf( stderr, "glXGetCurrentContext() is a baldface stub!" );
    first = 0;
  }
  return (GLXContext) __gllocal_GetCurrentContext();
}

GLXDrawable
glXGetCurrentDrawable( void )
{
  fprintf( stderr, "Unsupported GLX Call: glXGetCurrentDrawable()" );
  return (GLXDrawable) 0;
}

Bool
glXIsDirect( Display *dpy, GLXContext ctx )
{
  return 1;
}

void
__glX_WindowGetSize( Display *display, GLXDrawable drawable,
                     unsigned int *width_retval,
                     unsigned int *height_retval )
{
  Window       root;
  int          x, y;
  unsigned int width, height, border, depth;
  
  if ( !XGetGeometry( display, drawable, &root, &x, &y,
		      &width, &height, &border, &depth ) )
    fprintf( stderr, "__glX_WindowGetSize( ): XGetGeometry() failed!" );
  
  *width_retval  = width;
  *height_retval = height;
}


Bool
glXMakeCurrent( Display *dpy, GLXDrawable drawable, GLXContext ctx )
{
  int width, height;
  static GLframebuffer *fb;

  __glX_WindowGetSize(dpy, drawable, &width, &height);

  if (!cur_drawable) {
      fb = __glcore_CreateFrameBuffer(width, height, cur_visinfo->visualid,
				      __gllocal_Draw,
				      __gllocal_Sync);
  }
  else if (dpy == cur_display && drawable == cur_drawable) {
      if (width != cur_width || height != cur_height)
	  __glcore_ResizeFrameBuffer(fb, width, height);
  }
  else {
      fprintf(stderr, "No support for multiple drawables in glXMakeCurrent!");
      exit(1);
  }

  cur_drawable = drawable;
  cur_display = dpy;
  cur_gc = XCreateGC (cur_display, cur_drawable, 0, NULL);

  cur_width = width;
  cur_height = height;

  __gllocal_MakeCurrent(fb, (GLcontext *) ctx);

  return True;
}

Bool
glXQueryExtension( Display *dpy, int *errorBase, int *eventBase )
{
  return 1; // You BET we do...
}

Bool
glXQueryVersion( Display *dpy, int *major, int *minor )
{
  *major = 1;
  *minor = 3;
  
  return 1;
}

void
glXSwapBuffers( Display *dpy, GLXDrawable drawable )
{
  __gllocal_SwapBuffers();
}

void
glXWaitGL( void )
{
}

void
glXWaitX( void )
{
}

const char *
glXQueryExtensionsString( Display *dpy, int screen )
{
  static const char *retval = "";
  return retval;
}

const char *
glXGetClientString( Display *dpy, int name )
{
  const char *retval;
  switch ( name ) {
    
  case GLX_VENDOR:
    retval  = "GLSim";
    break;
    
  case GLX_VERSION:
    retval  = "1.0 GLSim";
    break;
    
  case GLX_EXTENSIONS:
    retval  = "";
    break;
    
  default:
    retval  = NULL;
  }
  
  return retval;
}

const char *
glXQueryServerString( Display *dpy, int screen, int name )
{
  return glXGetClientString(dpy, name);
}
