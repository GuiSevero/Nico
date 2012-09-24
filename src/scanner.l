 /* Secao das declaracoes */

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
float { return(FLOAT); }
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
if { return(IF); }
then { return(THEN); }
else { return(ELSE); }
for { return(FOR); }
next { return(NEXT); }
while { return(WHILE); }
end { return(END); }
true { return(TRUE); }
false {return(FALSE); }


({espaco}|{tab}|{novaLinha})+ { printf("SPACE\n"); }

({letraMinuscula}|{underline})+({letraMinuscula}|{letraMaiscula}|{underline}|{digito})* { 
  printf("%s", yytext); 
  return(IDF);
}

{letraMaiscula}+({underline}|{letraMaiscula}|{digito})* {
  printf("%s", yytext);
  return(CONST);
}

{aspasDupla}({letraMinuscula}|{letraMaiscula}|{digito}|{espaco})*{aspasDupla} {
  printf("%s", yytext);
  return(STR_LIT);
}


{digito}*"."{digito}*(([e]|[E])("+"|"-")?{digito}+)? {
  VAL_DOUBLE = atof(yytext);
  return(F_LIT);
}

{digito}+ {
  VAL_INT = atoi(yytext);
  return(INT_LIT);
}




  /* Tratamento dos erros lexicais: a regra seguinte pega tudo o que nao
   * fechou com uma Regexp anterior.
   */
. { printf("Erro léxico: caractere desconhecido '%c' (%d).\n",
        yytext[0], yytext[0]); exit(70); }
%%
 /* Secao dos  Procedimentos auxiliares  */

 /* Para redefinir a entrada padrao do LEX. 
  * Redefinir a variavel 'yyin' para ler de um arquivo. Por exemplo:
     yyin = fopen("Meu_programa.c", "r");
  * ira mandar ler o programa a ser compilado pelo analisador lexical
  * em 'Meu_programa.c'.
  * O default eh ler da entrada standard (o teclado).
  */

extern FILE *yyin;
int main(int argc, char* argv[]) {
   int token;
   if (argc != 2) {
     printf("uso: %s <input_file>. Try again!\n", argv[0]);
     exit(50);
   }
   yyin = fopen(argv[1], "r");
   if (!yyin) {
     printf("Uso: %s <input_file>. Could not find %s. Try again!\n", 
         argv[0], argv[1]);
     exit(55);
   }
  /* agora a entrada padrao eh o arquivo especificado como 1o argumento ao
   * executavel (argv[1]).
   * Soh chama o analisador lexical default fornecido pelo output do Flex:
   */
  while (token=yylex()) { 
     /* neste laco, obtem-se "palavra por palavra" os tokens reconhecidos
      * pelo scanner fornecido pelo Lex. Poderia ser feita a analise
      * sintatica... Sera feito depois!
      */
     printf("Meu analisador lexical reconheceu o token %d\n", token);
  }
  return(0);
}