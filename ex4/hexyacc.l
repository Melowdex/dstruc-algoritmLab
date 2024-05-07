%{
    #include "hexyacc.tab.h"
%}
 /* definitions section (declare names for complex regex's) */

%%
 /* rules section */

[ \t]	    { }                                 /*skip witte ruimte */
\n|.	    { return yytext[0]; }                /* alle andere sym doorgeven yacc \n nodig */
%%
 /* user code block at end of output file */
