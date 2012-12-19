#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct tac* create_inst_tac(const char* res, const char* arg1, const char* op, const char* arg2) {
   struct tac* i = (struct tac*) malloc(sizeof(struct tac));

   i->res = (char*) malloc(sizeof(char) * (1+strlen(res)));
   i->arg1 = (char*) malloc(sizeof(char) * (1+strlen(arg1)));
   i->op = (char*) malloc(sizeof(char) * (1+strlen(op)));
   i->arg2 = (char*) malloc(sizeof(char) * (1+strlen(arg2)));

   strcpy(i->res, res);
   strcpy(i->arg1, arg1);
   strcpy(i->op, op);
   strcpy(i->arg2, arg2);
   return i;
}

/** \brief Funcao que imprime o conteudo de uma instrucao TAC 
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a instrucao.
 * @param i a instrucao a ser impressa.
 */
void print_inst_tac(FILE* out, struct tac i) {
    if (!strcmp(i.op, ":="))
        fprintf(out, "%s := %s\n", i.res, i.arg1);
    // PRINT
    else if (* i.arg1 == '\0')
        fprintf(out, "%s %s\n", i.op, i.arg2);
    else
        fprintf(out, "%s := %s %s %s\n", i.res, i.arg1, i.op, i.arg2);
}

/** \brief Imprime no arquivo apontado por 'out' o conteudo da lista apontada
 * por 'code'.
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a lista (uma linha por elemento).
 * @param code o ponteiro para a lista a ser impressa.
 *
 * Obs.: cada linha impressa no arquivo deve comecar por um numero inteiro
 * (3 digitos) seguido de ':'. O numero deve ser o numero da linha.
 * Exemplo:
 *   001:  instrucao_qualquer
 *   002:  outra_instrucao
 *    .....
 *   999:  ultima_instrucao
 *   000:  agora_tem_instrucao_demais
 */
void print_tac(FILE* out, struct node_tac * code) {

   fprintf(out, "%d\n%d\n", vars_size,temps_size);
   
    while (code) {
        fprintf(out, "%03d:   ", code->number);
        print_inst_tac(out, *code->inst);
        code = code->next;
    }
}


/*
* Concatena uma isntrução TAC numa lista de instruções
*/
void append_inst_tac(struct node_tac ** code, struct tac * inst) {
    struct node_tac *new = (struct node_tac *) malloc(sizeof(struct node_tac));
    new->number = 0;
    new->inst = inst;
    new->next = NULL;
    new->prev = NULL;
    cat_tac(code, &new);
}

/**
* Concatena duas listas de tac
*/

void cat_tac(struct node_tac ** code_a, struct node_tac ** code_b) {
    int i = 1;
    struct node_tac * temp = * code_a;

    if (* code_b) {
        if (* code_a) {
            while (temp->next) {
               temp = temp->next;
               i++; //i guarda a posição da ultima instrução de A para depois atualizar B
            }
            //bota a lista B na cauda da lista A
            temp->next = *code_b;

            //bota o prev da lista B na lista A
            (* code_b)->prev = temp;
            temp = * code_b;
            do {
                temp->number = i++; //Atualiza o numero de instrucoes em B
            } while (temp = temp->next);
        } else {
           * code_a = * code_b;
        }
    }
}

