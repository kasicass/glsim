
print << 'EOF';

/* Generated by exports.pl */
#include "funcptrs.h"
#ifdef WIN32
#define NAKED __declspec(naked)
#else
#define NAKED
#endif

#ifdef __cplusplus
extern "C" {
#endif

EOF

do {
  $_ = <STDIN>;
  chomp;
  
  if ($_ =~ /(.*) (.*)/) {
	  print "NAKED gl$1() {\n";
	  print "\t__asm jmp [__glim_$1]\n";
	  print "}\n\n"
  }
} until eof();

printf << 'EOF'

#ifdef __cplusplus
}
#endif

EOF
