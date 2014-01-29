%{
/* a simple program */
#include <stdio.h>
#include <stdlib.h>
#define NUMBER 1
#define WORD 2
#define EOL 3
#define BRACKET 4
#define DIRECTORY 5
#define ALPHANUM 6
%}

%%
[\t ]+ /*ignore a space*/{}
[a-zA-Z]+ {return WORD;}
-?[0-9]+ {return NUMBER;}
\n {}
%%
//-?[0-9]+\n? {return NUMBER;}
int yywrap()
{
return 1;
}
