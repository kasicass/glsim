
print << 'EOF';
DESCRIPTION ""
EXPORTS
DllMain
wglChoosePixelFormat=wglChoosePixelFormat_prox
wglSetPixelFormat=wglSetPixelFormat_prox
wglDeleteContext=wglDeleteContext_prox
wglMakeCurrent=wglMakeCurrent_prox
wglGetCurrentContext=wglGetCurrentContext_prox
wglGetCurrentDC=wglGetCurrentDC_prox
wglGetPixelFormat=wglGetPixelFormat_prox
wglDescribePixelFormat=wglDescribePixelFormat_prox
wglCreateContext=wglCreateContext_prox
wglSwapBuffers=wglSwapBuffers_prox
wglShareLists=wglShareLists_prox
wglCopyContext=wglCopyContext_prox
wglCreateLayerContext=wglCreateLayerContext_prox
wglGetProcAddress=wglGetProcAddress_prox
wglUseFontBitmapsA=wglUseFontBitmapsA_prox
wglUseFontBitmapsW=wglUseFontBitmapsW_prox
wglDescribeLayerPlane=wglDescribeLayerPlane_prox
wglSetLayerPaletteEntries=wglSetLayerPaletteEntries_prox
wglGetLayerPaletteEntries=wglGetLayerPaletteEntries_prox
wglRealizeLayerPalette=wglRealizeLayerPalette_prox
wglSwapMultipleBuffers=wglSwapMultipleBuffers_prox
wglUseFontOutlinesA=wglUseFontOutlinesA_prox
wglUseFontOutlinesW=wglUseFontOutlinesW_prox
wglSwapLayerBuffers=wglSwapLayerBuffers_prox

glMyFunc

EOF

do {
  $_ = <STDIN>;
  chomp;
  if ($_ =~ /(.*) (.*)/) {
    print "gl$1\@$2=gl$1\n";
  }
} until eof();

