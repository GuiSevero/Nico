/* Secao das declaracoes */

%option yylineno
%{

  #define YY_USER_ACTION yylloc.first_line = yylineno;
  #define YY_USER_INIT yylineno = 1;

%}

%option noyywrap
  /* Sera copiado no .c final */
%{
    #include <stdlib.h>
    #include <string.h>
   
    /* este include eh importante... */
    #include "tokens.h"

    int VAL_INT;
    double VAL_DOUBLE;
  
%}
 
  /* Definicoes regulares (A COMPLETAR conforme a especificacao) */
digito     [0-9]
letraMaiscula [A-Z]
letraMinuscula [a-z]
underline "_"
espaco " "
tab \t
novaLinha \n
aspasDupla \"

%%

 /* Secao das Regras de traducao */
 /* O que consta aqui eh puramente ilustrativo... A COMPLETAR ! 
  * Ver tambem "tokens.h".
  */
integer { return(INT); } 
double { return(DOUBLE); }
real { return(REAL); }
char { return(CHAR); }
string { return(STRING); }
"*"    { return('*');}
"+"	{ return('+'); }
"-" { return('-');}
"/" { return('/');}
"," { return(',');}
";" { return(';');}
":" { return(':');}
"'" { return(QUOTE);}
"(" { return('('); }
")" { return(')'); }
"[" { return('['); }
"]" { return(']'); }
"{" { return('{'); }
"}" { return('}'); }
"<->" { return(SWAP); }
"<" { return('<'); }
">" { return('>'); }
"=" { return('='); }
"<=" { return(LE); }
">=" { return(GE); }
"==" { return(EQ); }
"!=" { return(NE); }
"&&" { return(AND); }
"||" { return(OR); }
"!" {return(NOT); }
"print" { return(PRINTF); }
if { return(IF); }
then { return(THEN); }
else { return(ELSE); }
while { return(WHILE); }
end { return(END); }
true { return(TRUE); }
false {return(FALSE); }


({espaco}|{tab}|{novaLinha})+ { 
  /*printf("SPACE\n");*/ 
  if(yytext[0] == "\n")
    yylineno++;
}

({letraMinuscula}|{underline})+({letraMinuscula}|{letraMaiscula}|{underline}|{digito})* { 
  /*printf("%s", yytext);*/
  yylval.cadeia = strdup(yytext);
  return(IDF);
}

{letraMaiscula}+({underline}|{letraMaiscula}|{digito})* {
  /*printf("%s", yytext);*/
  yylval.cadeia = strdup(yytext);
  return(CONST);
}

{aspasDupla}({letraMinuscula}|{letraMaiscula}|{digito}|{espaco})*{aspasDupla} {
  /*printf("%s", yytext);*/
  yylval.cadeia = strdup(yytext);
  return(STR_LIT);
}


{digito}*"."{digito}*(([e]|[E])("+"|"-")?{digito}+)? {
  VAL_DOUBLE = atof(yytext);
  yylval.cadeia = strdup(yytext);
  return(F_LIT);
}

{digito}+ {
  VAL_INT = atoi(yytext);
  yylval.cadeia=(char*)malloc((strlen(yytext)+1)*sizeof(char));
  strcpy(yylval.cadeia, yytext); 
  return(INT_LIT);
}


  /* Tratamento dos erros lexicais: a regra seguinte pega tudo o que nao
   * fechou com uma Regexp anterior.
   */
. { printf("Erro léxico: caractere desconhecido '%c' (%d).\n",
        yytext[0], yytext[0]); exit(70); }
%%
 

/* Secao dos  Procedimentos auxiliares  */

 /** Para redefinir a entrada padrao do LEX. 
  * Redefinir a variavel 'yyin' para ler de um arquivo. Por exemplo:
     yyin = fopen("Meu_programa.c", "r");
  * ira mandar ler o programa a ser compilado pelo analisador lexical
  * em 'Meu_programa.c'.
  * O default eh ler da entrada standard (o teclado).
  */

extern FILE *yyin;