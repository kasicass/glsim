##
## 3/06/2001
## http://graphics.stanford.edu/software/wiregl
##
## Copyright 2001
## The Board of Trustees of The Leland Stanford Junior University.
## All rights reserved.
##
## Except for commercial resale, lease, license or other commercial
## transactions, permission is hereby given to use, copy, and/or
## modify this software, provided that the above copyright notice and
## this permission notice appear in all copies of this software.  No
## part of this software or any derivatives thereof may be used in
## graphics systems for resale or for use in a commercial product.
##
## This software is provided "as is" and without warranty of any kind,
## express, implied or otherwise, including without limitation, any
## warranty of merchantability or fitness for a particular purpose.
##

my %params;

while (<>) {
    if (/^(\S+)\s+(GL_\S+)\s+(.*)\s*$/) {
 
	my $type   = $1;
	my $pname  = $2;
	my @params = split /\s+/, $3;

	$params{$pname}->{'type'} = $type;
	$params{$pname}->{'params'} = \@params;
    }
    elsif ( /^\s*$/ ) {
    }
    elsif ( /^\s*\#/ ) {
    }
    else {
	die "line $. confuses me: $_";
    }
}

my $convert = {
	       'GLenum' => {
			  'Boolean' => '(GLboolean) ( %p != 0 )',
			  'Double'  => '(GLdouble) %p',
			  'Float'   => '(GLfloat) %p',
			  'Integer' => '(GLint) %p'
			 },
	       'GLboolean' => {
			  'Boolean' => '(GLboolean) ( %p != 0 )',
			  'Double'  => '(GLdouble) %p',
			  'Float'   => '(GLfloat) %p',
			  'Integer' => '(GLint) %p'
			 },
	       'GLint'  => {
			  'Boolean' => '(GLboolean) ( %p != 0 )',
			  'Double'  => '(GLdouble) %p',
			  'Float'   => '(GLfloat) %p',
			  'Integer' => '(GLint) %p'
			 },
	       'GLfloat' => {
			  'Boolean' => '(GLboolean) ( %p != 0.0f )',
			  'Double'  => '(GLdouble) %p',
			  'Float'   => '%p',
			  'Integer' => '(GLint) %p'
			 },
	       'GLdouble' => {
			  'Boolean' => '(GLboolean) ( %p != 0.0 )',
			  'Double'  => '%p',
			  'Float'   => '(GLfloat) %p',
			  'Integer' => '(GLint) %p'
			 },
	       'GLdefault' => {
			  'Boolean' => '(GLboolean) ( %p != (GLdefault) 0.0 )',
			  'Double'  => '(GLdouble) %p',
			  'Float'   => '(GLfloat) %p',
			  'Integer' => '(GLint) %p'
			 },
	       'GLclampd' => {
			  'Boolean' => '(GLboolean) ( %p != 0.0 )',
			  'Double'  => '%p',
			  'Float'   => '(GLfloat) %p',
			  'Integer' => '__glcontext_clampd_to_int(%p)'
			 },
	       'GLclampf' => {
			  'Boolean' => '(GLboolean) ( %p != 0.0f )',
			  'Double'  => '(GLdouble) %p',
			  'Float'   => '%p',
			  'Integer' => '__glcontext_clampf_to_int(%p)'
			 }
	      };

my @types = ( "Boolean", "Double", "Float", "Integer" );

my %ctypes = ( 
	      'Boolean' => 'GLboolean',
	      'Double'  => 'GLdouble',
	      'Float'   => 'GLfloat',
	      'Integer' => 'GLint'
	     );

binmode STDOUT;

print <<EOF;
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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glcontext.h"
#include "glerror.h"

#if 0

static GLint
__glcontext_double_to_int( GLdouble d )
{
    /* i = (GLint) d, with clamping and rounding */
    if ( d >= 2147483647.5 )
        return 0x7fffffff;
    if ( d < -2147483648.5 )
        return 0x80000000;
    return (GLint) floor( d + 0.5 );
}

static GLint
__glcontext_float_to_int( GLfloat f )
{
    /* i = (GLint) f, with clamping and rounding */
    if ( f >= 2147483647.5f )
        return 0x7fffffff;
    if ( f < -2147483648.5f )
        return 0x80000000;
    return (GLint) floor( f + 0.5f );
}

#endif

static GLint
__glcontext_clampd_to_int( GLdouble d )
{
    /* -1.0 -> MIN_INT, 1.0 -> MAX_INT */
    if ( d > 1.0 )
        return 0x7fffffff;
    if ( d < -1.0 )
        return 0x80000000;
    return (GLint) floor( d * 2147483647.5 );
}

static GLint
__glcontext_clampf_to_int( GLfloat f )
{
    /* -1.0f -> MIN_INT, 1.0f -> MAX_INT */
    if ( f > 1.0f )
        return 0x7fffffff;
    if ( f < -1.0f )
        return 0x80000000;
    return (GLint) floor( f * 2147483647.5f );
}

const GLubyte * GLSTATE_DECL
__glstate_GetString (GLenum pname) {
	GLcontext *g = GetCurrentContext( );

	if (g->current.beginend) 
		if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
			"GetString called in Begin/End"))
			return NULL;

	switch (pname) {
	case GL_VENDOR:
		return (const GLubyte *) g->vendor;
	case GL_VERSION:
		return (const GLubyte *) g->version;
	case GL_RENDERER:
		return (const GLubyte *) g->renderer;
	case GL_EXTENSIONS:
		return (const GLubyte *) g->extensions;
	default:
		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM,
			"GetString with bogus string enum: %d", pname))
			return NULL;
	}
	return NULL;
}



EOF

$header = <<EOF;
{
    GLcontext   *g = GetCurrentContext( );

    if (g->current.beginend)
        if (__glerror(__LINE__, __FILE__, GL_INVALID_OPERATION,
                      "glGet called in Begin/End"))
            return;
  
    switch ( pname ) {

EOF

foreach $rettype (@types) {

  printf ("\n");
  printf ("void GLSTATE_DECL\n");
  printf ("__glstate_Get%sv( GLenum pname, %s *params )\n", $rettype, $ctypes{$rettype});
  print   $header;

  foreach $pname (sort(keys(%params))) {
    printf ("      case %s:\n", $pname);
    my $srctype = $params{$pname}->{'type'};
    my $cvt = $convert->{$srctype}->{$rettype};
	if ($cvt eq "") {
	  print ("			UNIMPLEMENTED();\n");
	}
	else 
	{ 
    $i = 0;
    foreach $param (@{$params{$pname}->{'params'}}) {
      my $expr = $cvt;
      $expr =~ s/%p/$param/g;
      printf ("        params[%d] = %s;\n", $i, $expr );
      $i++;
    }
	}
    printf ("        break;\n");
    printf ("\n");
  }
  
  print "      default:\n";
  print "		if (__glerror(__LINE__, __FILE__, GL_INVALID_ENUM, \"glGet: Unknown enum: 0x%x\", pname))\n";
  print "				return;\n";
  print "    }\n";
  print "}\n";
}

print <<EOF;

/* this file auto-generated by glget.pl */
EOF
