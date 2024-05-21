%{
    #include "hexyacc.tab.h"
    #include "hash.h"
%}
 /* definitions section (declare names for complex regex's) */

hex    0x[0-9a-fA-F]+
var    [a-zA-Z]+

%%
 /* rules section */

[ \t]	    { }                                 /*skip witte ruimte */
\n|.	    { return yytext[0]; }                /* alle andere sym doorgeven yacc \n nodig */

{hex}  { sscanf(yytext, "%x", &yylval); 
        return HEX; };

{var}   { yylval = ht_install(yytext);
        return REG; };
%%
 /* user code block at end of output file */
