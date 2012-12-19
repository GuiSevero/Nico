/** @file node.h
 *  @version 1.2
 */

#ifndef _NODE_H_
#define _NODE_H_

#ifdef __GNUC__
    /* If using gcc, warn about missing sentinel NULLs */
    #define NULL_TERMINATED __attribute__((sentinel))
#else
    #define NULL_TERMINATED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



typedef int Node_type;

/* Serie de constantes que servirao para definir tipos de nos (na arvore). 
 * Essa serie pode ser completada ou alterada a vontade.
 */
#define tipo_node      		298
#define code_node      		299
#define idf_node       		300
#define int_node       		301
#define float_node     		302
#define listaexpr_node   	303
#define listadupla_node  	304
#define chamaproc_node 		305
#define declaracoes_node	306
#define declaracao_node		307
#define listadeclaracao_node	308
#define fiminstcontrole_node 	309
#define expbool_node     	310
#define colon_node       	311
#define if_node        		312
#define while_node     		313
#define bloco_node   		314
#define openbra_node     	315
#define closebra_node    	316
#define or_node        		317
#define and_node       		318
#define eq_node        		319
#define ne_node       		320
#define greater_node       	321
#define less_node       	322
#define ge_node    		323
#define le_node    		324
#define plus_node      		325
#define minus_node     		326
#define mult_node      		327
#define div_node       		328
#define lvalue_node    		329
#define then_node        	330
#define not_node       		331
#define char_node      		332
#define flit_node    		334
#define exprp_node		335
#define expboolp_node		336
#define end_node	        337
#define else_node            	338
#define semicolon_node   	339
#define comma_node       	340 
#define double_node      	341
#define real_node        	342
#define opencur_node     	343
#define closecur_node    	344
#define tipolista_node   	345
#define intlit_node      	346
#define acoes_node       	347
#define atb_node      		348
#define comando_node     	349
#define expr_node        	350
#define openpar_node     	351
#define closepar_node    	352
#define true_node		353
#define false_node		354
#define swap_node		354
#define printf_node 355
 #define enunciado_node 355





/** Estrutura de dados parcial para o no da arvore. */
typedef struct _node {
   int line_num;   /**< numero de linha. */
   char* lexeme;   /**< o lexema retornado pelo analizador lexical. */
   Node_type type; /**< Um dos valores definidos acima pelos # defines. */
   void* attribute;/**< Qualquer coisa por enquanto. */
   
  /* Dados adicionais usados */
  struct _node** children; /* Lista de filhos do nó */
  int num_children; /* Numero de filhos do nó */

  //Especificacao do TAC
  struct node_tac * code; // ponteiro para uma estrutura node_tac
  char* local;

} Node;

extern Node *syntax_tree;
 
  
/**
 *  * Node constructor.
 *
 * @param nl: line number where this token was found in the source code.
 * @param t: node type (one of the values #define'd above). Must abort
 *             the program if the type is not correct.
 * @param lexeme: whatever string you want associated to this node.
 * @param attr: a semantical attribute.
 * @param children: NULL-terminated list of pointers to children Node*'s.
 *     See the extra file 'exemplo_func_var_arg.c' for an example.
 *     Callers are expected to pass *only Node pointers* as arguments.
 *     To create a leaf, use just NULL.
 * @return a pointer to a new Node.
 */
NULL_TERMINATED
Node* create_node(int nl, Node_type t,
        char* lexeme,  /* Node* children */ ...);

/** Accessor to the number of children of a Node.
 *  Must abort the program if 'n' is NULL.
 */
int nb_of_children(Node* n);

/** Tests if a Node is a leaf.
 *  Must abort the program if 'n' is NULL.
 *  @return 1 if n is a leaf, 0 else.
 */
int is_leaf(Node* n);

/** accessor to the i'th child of a Node.
 * @param n : the node to be consulted. Must abort the program if 'n' is NULL.
 * @param i : the number of the child that one wants. Given a node degree d,
 *       valid values for i are: 0 <= i < d.
 *       Must abort the program if i is not correct.
 * @return a pointer to a Node.
 */
Node* child(Node* n, int i) ;

/** Destructor of a Node. Deallocates
 * (recursively) all of the tree rooted at 'n'.
 */
int deep_free_node(Node* n) ;

/** returns the height of the tree rooted by 'n'.
 *  The height of a leaf is 1. 
 */
int height(Node *n) ;

/** Prints into a file the lexemes contained in the node rooted by 'n'.
 *  Lexemes must be printed in a depth-first order.
 *  @param outfile : the file to which the lexemes are printed.
 *  @param n : the root node of the tree. Must abort the program if 'n' is NULL.
 *
 */
void uncompile(FILE* outfile, Node *n) ;

/**
* @param Node *n - uma arvore para imprimir recursivamente
*/
void print_tree(Node *n);


#endif

