%{
    #define YYSTYPE int             /* type van yylval variable */
    extern int yylex();             /* generated by flex in .l file */
    extern int yyerror(char *);     /* called on error, can be overridden */
%}

%token  HEX
 /* prioriteit van laag naar hoog */


%%
input :   /* lege input */  { }
        | input command     { }                         /* parse lijn en zoek command, alles voor command is terug input */
;
command :  '\n'             { }                         /* command is gewoon een enter, doe niets */
;
%%

int main(int argc,char *argv[]) {
    yyparse();
    return 0;
}


