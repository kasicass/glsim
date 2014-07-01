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

%hash = (
	'Color' => {
		types => ['b','ub','s','us','i','ui','f','d'],
		sizes => [3,4],
		default => [0,0,0,1],
		members => ['r', 'g', 'b', 'a'],
		rescale => 1,
		native => 'f'
	},
	'Normal' => {
		types => ['b','s','i','f','d'],
		sizes => [3],
		default => [0,0,0],
		members => ['x', 'y', 'z'],
		rescale => 1,
		native => 'f'
	},
	'TexCoord' => {
		types => ['s','i','f','d'],
		sizes => [1,2,3,4],
		default => [0,0,0,1],
		members => ['s', 't', 'p', 'q'],
		rescale => 0,
		native => 'f'
	},
	'EdgeFlag' => {
		types => ['l'],
		sizes => [1],
		default => [1],
		members => [],
		rescale => 0,
		native => 'l'
	},
	'Index' => {
		types => ['ub','s','i','f','d'],
		sizes => [1],
		default => [0],
		members => [],
		rescale => 0,
		native => 'f'
	}
);

%vtxhash = (
	'Vertex' => {
		types => ['s','i','f','d'],
		sizes => [2,3,4],
		default => [0,0,0,1],
		members => ['x', 'y', 'z', 'w'],
		rescale => 0
	}
);

%ucnameconvert = (
	'COLOR' => 'Color',
	'NORMAL' => 'Normal',
	'TEXCOORD' => 'TexCoord',
	'EDGEFLAG' => 'EdgeFlag',
	'INDEX' => 'Index',
	'VERTEX' => 'Vertex'
);

%gltypes = (
	'l' => {
		type => 'GLboolean',
		size => 1
	},
	'b' => {
		type => 'GLbyte',
		size => 1
	},
	'ub' => {
		type => 'GLubyte',
		size => 1
	},
	's' => {
		type => 'GLshort',
		size => 2
	},
	'us' => {
		type => 'GLushort',
		size => 2
	},
	'i' => {
		type => 'GLint',
		size => 4
	},
	'ui' => {
		type => 'GLuint',
		size => 4
	},
	'f' => {
		type => 'GLfloat',
		size => 4
	},
	'd' => {
		type => 'GLdouble',
		size => 8
	}
);

1;