%{
/* a simple program */
#include <stdio.h>
#include <stdlib.h>
#include <include/parserDefines.h>
%}

%%
[\t ]+ /*ignore a space*/{}
[a-zA-Z]+ {return WORD;}
-?[0-9]+ {return NUMBER;}
\n {}
: {}
[@#$%^&:;"'<>,.?/)_(]+[a-zA-Z0-9]+[@#$%^&:;"'<>,.?/)_(]* {}
^VmData: {return VM;}
%%
//-?[0-9]+\n? {return NUMBER;}
int yywrap()
{
return 1;
}
