#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "tokens.h"

#include "lista.h"
#include "symbol_table.h"

/* Programa principal do nico. */
char* progname;
extern int yylineno;
extern FILE* yyin;

symbol_t symbol_table;
FILE* outfile;

int main(int argc, char* argv[]) 
{
   if (argc != 2) {
     printf("uso: %s <input_file>. Try again!\n", argv[0]);
     exit(-1);
   }
   yyin = fopen(argv[1], "r");
   if (!yyin) {
     printf("Uso: %s <input_file>. Could not find %s. Try again!\n", 
         argv[0], argv[1]);
     exit(-1);
   }

   progname = argv[0];

   if (!yyparse()) {
    printf("OKAY.\n");

      //printf("\n\n============= IMPRIMINDO A RAIZ ============\n\n");

   // print_tree(syntax_tree);

    printf("\n\n============= IMPRIMINDO A TAC NO ARQUIVO ============\n\n");
    outfile = fopen("code.tac","w");
    print_tac(outfile, syntax_tree->code);
    system("cat code.tac");
    
   }
      
   else 
      printf("ERROR.\n");
   


  

   return(0);
}

yyerror(char* s) {
  fprintf(stderr, "%s: %s", progname, s);
  fprintf(stderr, "line %d\n", yylineno);
}
