#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

Node * syntax_tree;

//Construtor do nodo
//PARAMETROS:
//	nl = linha onde está o token no código fonte.
//	t  = valor do nodo.
//  lexeme = o que vai ser associado ao nodo.
//	attr: valor semantico.
// 	children: lista de ponteiros para os nodos filhos.
// 	See the extra file 'exemplo_func_var_arg.c' for an example.
//RETORNO
//	um ponteiro para um novo nodo.
NULL_TERMINATED
Node* create_node(int nl, Node_type t, char* lexeme,  /* Node* children */ ...) {
	
	Node *n; 	//Armazenará o novo nodo.
	Node *arg; 	//ponteiro para a lista de filhos a serem adicionados
	int i;
	int num_children = 0; //constructortador para os filhos.	
	va_list ap; 		//variável das listas va

	//Conta o número de argumentos, ou seja, número de filhos. - Precisamos saber para a alocação adequada de memória.
    va_start(ap, lexeme); //Inicia lista de argumentos da funcao.
	for (arg = va_arg(ap, Node*), num_children = 0;  arg != NULL;  arg = va_arg(ap,  Node*)) {
		num_children++;
    } 
    va_end(ap); //finaliza lista de parametro

    //Alocação do Nodo
    n = (Node*)malloc(sizeof(Node));	
	n->line_num = nl; 					
	n->lexeme = strdup(lexeme); 		
	n->type = t; 						
	n->num_children = num_children; 	//armazena o numero de filhos do nodo
	n->children = NULL;
	n->children = (Node**)malloc(sizeof(Node *)*(n->num_children + 1)); //Aloca memória para os filhos.

	//Lista de filhos
    n->children[n->num_children] = NULL; // coloca sentinela para termino da lista.
    va_start(ap, lexeme); //Inicia lista de argumentos da funcao.
	/* preenche a lista de filhos */
    for (arg = va_arg(ap, Node*), i=0; arg != NULL;  arg = va_arg(ap, Node*), i++) {	
        n->children[i] = arg;
    }
    va_end(ap); //finaliza lista de parametros.
    return n; //Retorna o novo nodo.	
}


// Devolve o número de filhos de um nodo.
//PARAMETROS:
//	n = um nodo 
//RETORNO
//	Numero de filhos de um nodo.
int nb_of_children(Node* n){
	return n->num_children; //já calculamos na criação do nodo, apenas precisamos retornar esse atributo.
}


// Realiza um teste se o nodo é folha
//PARAMETROS:
//	n = um nodo
//RETORNO
//	1 se for folha. 0 se não for.
int is_leaf(Node* n){

	//Como especificado, quando n for NULL devemos abortar.
	if(n == NULL)
		exit(1);
	
	//Se children for NULL quer dizer que não temos filhos, logo o nodo representa uma folha.
	if(n->num_children > 0){
		return 0; //0 nodo é uma folha
	}
	//1 nodo não é uma folha
	return 1;

}

//Acessa o n-ésimo filho de um Node
//PARAMETROS
//	n = o nodo que vai ser consultado.
//  i = o número do filho que vai ser consultado.
//RETORNO
//	ponteiro para o Node.
Node* child(Node* n, int i) {
	
	//Não é possivel acessar este filho, i inválido
	if( i >= n->num_children){
		printf("Nao foi possivel acessar este filho. Erro!\n\n");
		exit(1);
	} else {
		return n->children[i];
	}
}

//Destrói o Node recursivamente
//PARAMETROS
//	n = o nodo que será desalocado
//RETORNO
//
 
int deep_free_node(Node* n) {
 	
	int ret=0; /*retorno da função*/
	int i; 	/*auxiliar para laço*/
	/*verifica se há algo para liberar*/
   	if(n == NULL){
    	printf("Nodo null\n");
    	return 0;
    }

   	/*libera todos os filhos*/
   	if(n->num_children > 0){
       for(i=0; i < n->num_children; i++){
           ret += deep_free_node(child(n, i));
    	}       
    }

   /*apaga esse próprio nó*/
    if(n != NULL){
    	free(n);
    	 if(n->children[0] != NULL){
    	 	for(i=0; i < n->num_children; i++){
    			free(n->children[i]);
    			n->children[i] = NULL;
    		}
    	}
    	n = NULL;
    }

    return ret + 1;


}

//Devolve a altura da árvore com raiz n.
//PARAMETROS
//	n = a raiz do Node
//RETORNO
// a altura da árvore
int height(Node *n) {
	int h = 0;		//armazenará a altura da árvore
	int h_aux=0;
	int i;
	
	//Erro! Casos nodo não exista
	if(n == NULL){
		exit(1);
	}

	//Se não tem filhos, é folha
	if(n->num_children == 0)
		return 1;
	
	for(i = 0; i < n->num_children; i++){
		h_aux = height(child(n,i)) ;
		if(h_aux > h) //selecao da subarvore de maior altura
			h = h_aux; 
	}		
	return h + 1; 
}


//Imprime a árvore
void print_tree(Node *n){
    int i;

     if(n->num_children > 0){
         for(i=0; i < n->num_children; i++){
                print_tree(child(n, i));
                
        }
    }

    if(is_leaf(n) == 1){
        printf("Folha: ");
    }


    if(is_leaf(n) == 0){
        printf("No: ");
    }

    printf("%s\n", n->lexeme);

}