 /* code block at begin of output file */
 /* mind the space before every comment! */
%{
    #include "hash.h"
    int result;

    #define HEX   -1     /* tokens zelf def als je zonder yacc werkt*/
    #define REG   -2
%}
 /* definitions section (declare names for complex regex's) */
hex    0x[0-9a-fA-F]+
var    [a-zA-Z]+

%%
 /* rules section */
{hex}  { result = strtol(yytext, NULL, 0); 
        return HEX; };

{var}   { result = ht_install(yytext);
        return REG; };

%%
 /* user code block at end of output file */

int main(int argc,char *argv[]) {
    int code;

    ht_init();
    do {
        code = yylex();
        if (code == REG) printf("index : %4d | %s\n", result, yytext);
        if (code == HEX) printf("getal : %4d | %s\n", result, yytext);
    } while( code != 0 );

    ht_print();
    return 0;
}