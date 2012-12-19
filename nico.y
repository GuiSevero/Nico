
%error-verbose

%{
  /* Aqui, pode-se inserir qualquer codigo C necessario ah compilacao
   * final do parser. Sera copiado tal como esta no inicio do y.tab.c
   * gerado por Yacc.
   */
  #include <stdio.h>
  #include <stdlib.h>
  #include "node.h"

  #include "lista.h"
  #include "lista.c"
  #include "symbol_table.h"
  #include "symbol_table.c"


     //Definicoes de tamanho de variaveis e erros
   	#define UNDEFINED_SYMBOL_ERROR -21
    #define CHAR_TYPE   0
    #define INT_TYPE    1
    #define REAL_TYPE   2
    #define DOUBLE_TYPE 3

    #define CHAR_SIZE   1
    #define INT_SIZE    4
    #define REAL_SIZE   4
    #define DOUBLE_SIZE 8 

    extern symbol_t symbol_table;
    int tipo_idf = 0;
    int vars_size = 0;
    int temps_size = 0;
    
    char* gera_temp(int type) {
        int size = 0;
        switch (type) {
            case CHAR_TYPE:     size = CHAR_SIZE; break;
            case INT_TYPE:      size = INT_SIZE; break;
            case REAL_TYPE:     size = REAL_SIZE; break;
            case DOUBLE_TYPE:   size = DOUBLE_SIZE; break;
        }
        //TEMP = REGISTRADOR Rx + DESLOCAMENTO DE Rx.
        //ddd(Rx) ddd é o valor da variável temps_size(Tamanho da pilha)
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(Rx)", temps_size);//retorna topo da pilha
        temps_size += size;//incrementa a pilha com o tamanho do tipo
        return ret;
    }
    
    void AddSymbolOnTable(char *lexeme){
    	if(!lookup(symbol_table, lexeme)){//testa se já existe esta entrada na tabela
					
		 entry_t* new_entry=(entry_t *) malloc(sizeof(entry_t));
    		
		    new_entry->name = lexeme;
		    new_entry->type = tipo_idf;
		    new_entry->desloc = vars_size;

		    switch(tipo_idf){
		        	case INT_TYPE:		new_entry->size = INT_SIZE;
						    vars_size += INT_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case DOUBLE_TYPE:	new_entry->size = DOUBLE_SIZE;
						    vars_size += DOUBLE_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case REAL_TYPE:		new_entry->size = REAL_SIZE;
						    vars_size += REAL_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case CHAR_TYPE:		new_entry->size = CHAR_SIZE;
						    vars_size += CHAR_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
		    }
		    if(insert(&symbol_table, new_entry)){
			    printf("Ocorreu um erro ao alocar o simbolo %s na tabela de simbolos.\n",lexeme);
			    exit(0);
		    }

	}
	    else{
	    	printf("Símbolo %s foi definido múltiplas vezes. \n", lexeme);
			exit(0);		   
	    }
    }
    
 /*
    Essa funcao consulta a tabela atras de um identificador e retorna o conteudo para 
    a string "local" caso o identificador esteja na tabela, caso contrario retorna o proprio identificador
    */
    
	char* lookupOnTable(char* identificador) {
        entry_t* entrada;
        entrada = lookup(symbol_table, identificador);
        if(entrada == NULL)
        return NULL;
        
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(SP)", entrada->desloc);
        return ret;
    }


    /*
    * Cria um nodo auxiliar
    */
    Node* cnode(Node_type t, char* lexeme){
    	return create_node(0, t, lexeme, NULL);
    }     
   

%}

%union {
  char* cadeia;
  struct _node * no;
}

%token<cadeia> IDF
%token<cadeia> INT
%token<cadeia> DOUBLE
%token<cadeia> REAL
%token<cadeia> CHAR
%token<cadeia> QUOTE
%token<cadeia> SWAP
%token<cadeia> LE
%token<cadeia> GE
%token<cadeia> EQ
%token<cadeia> NE
%token<cadeia> AND
%token<cadeia> OR
%token<cadeia> NOT
%token<cadeia> IF
%token<cadeia> THEN
%token<cadeia> ELSE
%token<cadeia> WHILE
%token<cadeia> INT_LIT
%token<cadeia> F_LIT
%token<cadeia> END
%token<cadeia> TRUE
%token<cadeia> FALSE
%token<cadeia> STRING
%token<cadeia> CONST
%token<cadeia> STR_LIT
%token<cadeia> FOR
%token<cadeia> NEXT
%token <cadeia> PRINTF

%token<cadeia> ';'
%token<cadeia> ':'
%token<cadeia> ','
%token<cadeia> '['
%token<cadeia> ']'
%token<cadeia> '('
%token<cadeia> ')'
%token<cadeia> '{'
%token<cadeia> '}'
%token<cadeia> '='
%token<cadeia> '+'
%token<cadeia> '-'
%token<cadeia> '*'
%token<cadeia> '/'
%token<cadeia> '>'
%token<cadeia> '<'

%type<no> code
%type<no> declaracoes 
%type<no> declaracao
%type<no> listadeclaracao
%type<no> tipo
%type<no> tipounico
%type<no> tipolista
%type<no> listadupla
%type<no> acoes
%type<no> comando
%type<no> lvalue
%type<no> listaexpr
%type<no> expr
%type<no> chamaproc
%type<no> bloco
%type<no> fiminstcontrole
%type<no> expbool
%type<no> enunciado

%left	OR
%left	AND
%left	NOT
%left	'+' '-'  
%left	'*' '/'


%start code

 /* A completar com seus tokens - compilar com 'yacc -d' */

%%



code: declaracoes acoes { 

					$$ = create_node(@1.first_line, code_node, "code", $1, $2, NULL); 
					cat_tac(&($$->code), &($2->code)); //new 

					FILE * out = fopen("teste_raiz", "w"); 
							print_tac(out, $$->code);
							fclose(out);

					syntax_tree = $$;
					}

	| acoes			{ 
					$$ = $1; 

					syntax_tree = $$;  
					}
;

declaracoes: declaracao ';'		{ 
					$$ = create_node(@1.first_line, declaracoes_node, "declaracoes", $1, cnode(semicolon_node, ";"), NULL); 
					}

| declaracoes declaracao ';'		{					
					$$ = create_node(@1.first_line, declaracoes_node, "declaracoes", $1, $2, cnode(semicolon_node, ";"), NULL); 
					}
;

declaracao: tipo ':' listadeclaracao	{					
					$$ = create_node(@1.first_line, declaracao_node, "declaracao", $1, cnode(colon_node, ":"), $3, NULL); 
					}
;

listadeclaracao: IDF			{$$ = create_node(@1.first_line, idf_node, $1, NULL); AddSymbolOnTable($1);  }				

| IDF "," listadeclaracao		{
					$$ = create_node(@1.first_line, listadeclaracao_node, "listadeclaracao", create_node(@1.first_line, idf_node, $1, NULL), cnode(comma_node, ","), $3, NULL); 
					AddSymbolOnTable($1);
					}
;

tipo: tipounico				{ $$ = $1; }
| tipolista				{ $$ = $1; }
;

tipounico: 
  DOUBLE				{ $$ = create_node(@1.first_line, double_node, "double", NULL);  tipo_idf = DOUBLE_TYPE;}
| REAL					{ $$ = create_node(@1.first_line, real_node, "real", NULL); tipo_idf = REAL_TYPE; }
| CHAR					{ $$ = create_node(@1.first_line, char_node, "char", NULL);  tipo_idf = CHAR_TYPE; }
| INT			{ $$ = create_node(@1.first_line, int_node, "int", NULL); tipo_idf = INT_TYPE; }
;

tipolista: INT '(' listadupla ')'	{			 	
					$$ = create_node(@1.first_line, tipolista_node, "tipolista"
							, create_node(@1.first_line, int_node, "int", NULL)
							, create_node(@1.first_line, openpar_node, "(", NULL)
							, $3
							, create_node(@1.first_line, closepar_node, ")", NULL)
							, NULL); 
					}

| DOUBLE '(' listadupla ')'		{

					$$ = create_node(@1.first_line, tipolista_node, "tipolista"
						, create_node(@1.first_line, double_node, "double", NULL)
						, create_node(@1.first_line, openpar_node, "(", NULL)
						, $3
						, create_node(@1.first_line, closepar_node, ")", NULL)
						, NULL); 
					}

| REAL '(' listadupla ')'		{
 	
					$$ = create_node(@1.first_line, tipolista_node, "tipolista"
						, create_node(@1.first_line, real_node, "real", NULL)
						, create_node(@1.first_line, openpar_node, "(", NULL)
						, $3
						, create_node(@1.first_line, closepar_node, ")", NULL)
						, NULL); 

					}

| CHAR '(' listadupla ')'		{
					 	
					$$ = create_node(@1.first_line, tipolista_node, "tipolista"
						, create_node(@1.first_line, char_node, "char", NULL)
						, create_node(@1.first_line, openpar_node, "(", NULL)
						, $3
						, create_node(@1.first_line, closepar_node, ")", NULL)
						, NULL); 
					}
;

listadupla: INT_LIT ':' INT_LIT		{
				
					$$ = create_node(@1.first_line, listadupla_node, "listadupla"
						, create_node(@1.first_line, intlit_node, $1, NULL)
						, create_node(@1.first_line, colon_node, ":", NULL)
						, create_node(@1.first_line, intlit_node, $3, NULL)
						, NULL); 
					}

| INT_LIT ':' INT_LIT ',' listadupla	{ 
							
							$$ = create_node(@1.first_line, listadupla_node, "listadupla"
								, create_node(@1.first_line, intlit_node, $1, NULL)
								, create_node(@1.first_line, colon_node, ":", NULL)
								, create_node(@1.first_line, intlit_node, $3, NULL)
								, create_node(@1.first_line, comma_node, ",", NULL)
								, $5
								, NULL); 
							}
;

acoes: comando 				{  
	$$ = $1;  	

}

| comando acoes				{  
				$$ = create_node(@1.first_line, acoes_node, "acoes", $1, $2, NULL);

							
				cat_tac(&($$->code), &($1->code)); //new
             	cat_tac(&($$->code), &($2->code)); //new
		
         }

;

comando: lvalue '=' expr ';'		{
					
					$$ = create_node(@1.first_line, comando_node, "comando"
						, $1
						, create_node(@1.first_line, atb_node, "=", NULL)
						, $3
						, create_node(@1.first_line, semicolon_node, ";", NULL)
						, NULL); 



					
        			cat_tac(&($$->code), &($3->code));

        			struct tac* new_tac = create_inst_tac($1->local,$3->local,"","");        			
			        append_inst_tac(&($$->code),new_tac);					

					}

| lvalue SWAP lvalue ';'		{
					 
					$$ = create_node(@1.first_line, comando_node, "comando"
						, $1
						, create_node(@1.first_line, swap_node, "SWAP", NULL)
						, $3
						, create_node(@1.first_line, semicolon_node, ";", NULL)
						, NULL);


					//A SWAP B:
					//temp = A
					//A = B
					//B = temp
					
					char * temp = gera_temp(INT_TYPE);
                    struct tac* new_tac1 = create_inst_tac(temp,$1->local,"","");
                    struct tac* new_tac2 = create_inst_tac($1->local,$3->local,"","");
                    struct tac* new_tac3 = create_inst_tac($3->local,temp,"","");
                    					
           			append_inst_tac(&($$->code),new_tac1);
          			append_inst_tac(&($$->code),new_tac2);
           			append_inst_tac(&($$->code),new_tac3); 

					}

| expr ';'				{
					
					$$ = create_node(@1.first_line, comando_node, "comando", $1, cnode(semicolon_node, ";"), NULL);
					$$->local = $1->local;	
				    cat_tac(&($$->code), &($1->code));
					}

| bloco					{  $$ = $1;  }

| enunciado	{ $$ = $1; }
;


enunciado: PRINTF expr ';' { 
							$$ = create_node(@1.first_line, enunciado_node, "enunciado"
							, create_node(@1.first_line, printf_node, $1, NULL)
							, $2							
							, create_node(@1.first_line, semicolon_node, ";", NULL)
							, NULL);

							cat_tac(&($$->code), &($2->code));							
							append_inst_tac(&($$->code), create_inst_tac("", "","PRINT", $2->local)) ;	

							

						}
;
	
lvalue: IDF				{ 
						

							char *temp = lookupOnTable($1);
				                    if(temp) {
										$$ = create_node(@1.first_line, idf_node, $1, NULL);                 
								    	$$->local = temp;

								    	printf("============= %s\n", temp);
				                    }
				                    else {
						                printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", $1);
							            return( UNDEFINED_SYMBOL_ERROR );
								}
						
						
											
				}

| IDF '[' listaexpr ']'			{
					 
					$$ = create_node(@1.first_line, lvalue_node, "lvalue"
						, create_node(@1.first_line, idf_node, $1, NULL)
						, create_node(@1.first_line, openbra_node, "[", NULL)
						, $3
						, create_node(@1.first_line, closebra_node, "]", NULL)
						, NULL); 
					}
;

listaexpr: expr				{ $$ = $1; }

| expr ',' listaexpr			{ 
					
					$$ = create_node(@1.first_line, listaexpr_node, "listaexpr", $1, cnode(comma_node, ","), $3, NULL); 
					}


;

expr: expr '+' expr			{
					
					$$ = create_node(@1.first_line, expr_node, "expr", $1, cnode(plus_node, "+"), $3, NULL); 

					$$->local = gera_temp(INT_TYPE);
				   struct tac* new_tac = create_inst_tac($$->local,$1->local,"ADD",$3->local);
       			    cat_tac(&($$->code), &($1->code));
       			    cat_tac(&($$->code), &($3->code));
       			    append_inst_tac(&($$->code),new_tac);

					}

| expr '-' expr				{
					
					$$ = create_node(@1.first_line, expr_node, "expr", $1, cnode(minus_node, "-"), $3, NULL); 

					$$->local = gera_temp(INT_TYPE);
				    struct tac* new_tac = create_inst_tac($$->local,$1->local,"SUB",$3->local);
       			    cat_tac(&($$->code), &($1->code));
       			    cat_tac(&($$->code), &($3->code));
       			    append_inst_tac(&($$->code),new_tac);

   					}

| expr '*' expr				{
					
					$$ = create_node(@1.first_line, expr_node, "expr", $1, cnode(mult_node, "*"), $3, NULL); 

					$$->local = gera_temp(INT_TYPE);
				    struct tac* new_tac = create_inst_tac($$->local,$1->local,"MUL",$3->local);
       			    cat_tac(&($$->code), &($1->code));
       			    cat_tac(&($$->code), &($3->code));
       			    append_inst_tac(&($$->code),new_tac);

					}

| expr '/' expr				{
					
					$$ = create_node(@1.first_line, expr_node, "expr", $1, cnode(div_node, "/"), $3, NULL);

					$$->local = gera_temp(INT_TYPE);
				    struct tac* new_tac = create_inst_tac($$->local,$1->local,"DIV",$3->local);
       			    cat_tac(&($$->code), &($1->code));
       			    cat_tac(&($$->code), &($3->code));
       			    append_inst_tac(&($$->code),new_tac);  

					}

| '(' expr ')'				{
					
					$$ = create_node(@1.first_line, expr_node, "expr"
						, create_node(@1.first_line, openpar_node, "(", NULL)
						, $2
						, create_node(@1.first_line, closepar_node, ")", NULL)
						, NULL); 


					//TAC
					$$->local = $2->local;	 
               		cat_tac(&($$->code), &($2->code));
					}

| INT_LIT				{ $$ = create_node(@1.first_line, intlit_node, $1, NULL); $$->local = $1 }

| F_LIT					{ $$ = create_node(@1.first_line, flit_node, $1, NULL); $$->local = $1 }

| lvalue				{ $$ = $1; }

| chamaproc				{ $$ = $1; }
;

chamaproc: IDF '(' listaexpr ')'	{

					$$ = create_node(@1.first_line, chamaproc_node, "chamaproc"
						, create_node(@1.first_line, idf_node, $1, NULL)
						, create_node(@1.first_line, openpar_node, "(", NULL)
						, $3
						, create_node(@1.first_line, closepar_node, ")", NULL)
						, NULL); 
					}
;

bloco: IF '(' expbool ')' THEN acoes fiminstcontrole	{
												 					
							$$ = create_node(@1.first_line, bloco_node, "bloco"
								, create_node(@1.first_line, if_node, "IF", NULL)
								, create_node(@1.first_line, openpar_node, "(", NULL)
								, $3
								, create_node(@1.first_line, closepar_node, ")", NULL)
								, create_node(@1.first_line, then_node, "THEN", NULL)
								, $6
								, $7
								, NULL); 
							}

| WHILE '(' expbool ')' '{' acoes '}'			{
											 						
							$$ = create_node(@1.first_line, bloco_node, "bloco"
								, create_node(@1.first_line, while_node, "WHILE", NULL)
								, create_node(@1.first_line, openpar_node, "(", NULL)
								, $3
								, create_node(@1.first_line, closepar_node, ")", NULL)
								, create_node(@1.first_line, opencur_node, "{", NULL)
								, $6
								, create_node(@1.first_line, closecur_node, "}", NULL)
								, NULL); 
							}
;

fiminstcontrole: END			{ $$ = create_node(@1.first_line, end_node, "END", NULL); }

| ELSE acoes END			{ 
					
					$$ = create_node(@1.first_line, fiminstcontrole_node, "fiminstcontrole"
						, create_node(@1.first_line, else_node, "ELSE", NULL)
						, $2
						, create_node(@1.first_line, end_node, "END", NULL)
						, NULL); }
;

expbool: TRUE 				{ $$ = create_node(@1.first_line, true_node, "true", NULL); }

| FALSE 				{ $$ = create_node(@1.first_line, false_node, "false", NULL); }

| '(' expbool ')' 			{
														
					$$ = create_node(@1.first_line, expbool_node, "expbool"
						, create_node(@1.first_line, openpar_node, "(", NULL)
						, $2
						, create_node(@1.first_line, closepar_node, ")", NULL)
						, NULL); 
					}

| expbool AND expbool			{ 
							
					$$ = create_node(@1.first_line, expbool_node, "expbool"
						, $1
						, create_node(@1.first_line, and_node, "AND", NULL)
						, $3
						, NULL); 
					}

| expbool OR expbool 			{ 
								
					$$ = create_node(@1.first_line, expbool_node, "expbool", $1, cnode(or_node, "GE"), $3, NULL); 
					}

| NOT expbool 				{ 
					
					$$ = create_node(@1.first_line, expbool_node, "expbool", cnode(not_node, "NOT"), $2, NULL); 
					}

| expr '>' expr				{ 
					
					$$ = create_node(@1.first_line, expbool_node, "expbool", $1, cnode(greater_node, ">"), $3, NULL); 
					}

| expr '<' expr 			{ 
					
					$$ = create_node(@1.first_line, expbool_node, "expbool", $1, cnode(less_node, "<"), $3, NULL); 
					}

| expr LE expr 				{ 
							
					$$ = create_node(@1.first_line, expbool_node, "expbool", $1, cnode(le_node, "GE"), $3, NULL); 
					}

| expr GE expr 				{ 
					$2 = create_node(@1.first_line, ge_node, "GE", NULL);			
					$$ = create_node(@1.first_line, expbool_node, "expbool", $1, cnode(ge_node, "GE"), $3, NULL); 
					}

| expr EQ expr				{ 
					
					$$ = create_node(@1.first_line, expbool_node, "expbool", $1, cnode(eq_node, "EQ"), $3, NULL); 
					}

| expr NE expr				{ 
					
					$$ = create_node(@1.first_line, expbool_node, "expbool", $1, cnode(ne_node, "NE"), $3, NULL); 
					}
;


%%