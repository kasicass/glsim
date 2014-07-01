
do {
  $_ = <STDIN>;
  chomp;

  if ($_ =~ /(.*) (.*)/) {
    print ".align 4\n";
    print ".globl gl$1\n";
    print "	.type gl$1,\@function\n";
    print "gl$1:\n";
    print "     movl __glim_$1 , \%eax\n";
    print "	jmp *\%eax\n";
    print "\n";
  } 

} until eof();

