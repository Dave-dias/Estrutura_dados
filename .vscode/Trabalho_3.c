// Trabalho Estrutura de dados - Benchmark de pesquisa - Arvores
// Alunos: David Augusto, Henrique Oliveira, Carlos Vinicius, Italo Bueno

// Constants 
const char* ALGORITIMO_BINARIA = "arvore-binaria";
const char* ALGORITIMO_AVL = "arvore-avl";

// Importações de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Implementação feita na sala de aula da arvore binaria 
// modificado para armazenar strings em seus nós

// PtrNoArvore = NoArvore* -> PtrNoArvore
typedef struct NoArvore* PtrNoArvore;
// NoArvore
typedef struct NoArvore {
  char* chave;
  PtrNoArvore direita;
  PtrNoArvore esquerda;
} NoArvore;

// ---------------------------------------
// ---------------------------------------

// destruicao
// remover 
// pesquisar
// maximo (int) * | rec | iterativo (while)
// minimo (int) * | rec | iterativo (while)
// tamanho (int) *
// percurso (em ordem, pre ordem, pos Ordem)
// ---------------------------------------
// ---------------------------------------
void iniciaArvoreBinaria(PtrNoArvore *r) {
  (*r) = NULL;
}

bool estaVaziaArvoreBinaria(PtrNoArvore *r) {
  return((*r) == NULL);
}
// ---------------------------------------
// ---------------------------------------
//bool inserirArvoreBinaria(PtrNoArvore *no, int valor) {
bool inserirArvoreBinaria(PtrNoArvore *no, char* valor) {
  // clausulas base (true, false)
  // 1. NULL (ponto de inserção)
  // Toda vez que achar um NULL � onde vamos inserir o novo elemento:
  if((*no) == NULL) {
    (*no) = malloc(sizeof(NoArvore));
    //(*no)->chave = valor;
    strcpy((*no)->chave, valor);
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    return (true);
  }
  // 2. no que j� possui o valor que eu quero inserir
//  if((*no)->chave == valor) return (false); // warning
  if(strcmp((*no)->chave, valor)==0) return (false); // warning

  // clausula recursiva
//  if(valor > (*no)->chave) {
  if(strcmp(valor,(*no)->chave)==1){
    return(inserirArvoreBinaria(&(*no)->direita, valor));
  } else{
    return(inserirArvoreBinaria(&(*no)->esquerda, valor));
  }
}

// ---------------------------------------
// ---------------------------------------

// print, dir, esq
//PREORDEM
// 1 Printa
// 2 PREORDEM(Esq)
// 3 PREORDEM(Dir)
void PreOrdemArvoreBinaria(PtrNoArvore *no) {
  if((*no) == NULL) return; //clausula base
  printf("%d ", (*no)->chave);
  PreOrdemArvoreBinaria(&(*no)->esquerda);
  PreOrdemArvoreBinaria(&(*no)->direita);
}

void PreOrdemPrincipal(PtrNoArvore *no) {
  printf("PreOrdem = { ");
  PreOrdemArvoreBinaria(&(*no));
  printf("}\n");
}

//EMORDEM
// 1 EMORDEM(Esq)
// 2 Printa
// 3 EMORDEM(Dir)
void EmOrdemArvoreBinaria(PtrNoArvore *no) {
  if((*no) == NULL) return; //clausula base
  EmOrdemArvoreBinaria(&(*no)->esquerda);
  printf("%d ", (*no)->chave);
  EmOrdemArvoreBinaria(&(*no)->direita);
}

void EmOrdemPrincipal(PtrNoArvore *no) {
  printf("EmOrdem = { ");
  EmOrdemArvoreBinaria(&(*no));
  printf("}\n");
}

//POSORDEM
//1. POSORDEM(Esq)
//2. POSORDEM(Dir)
//3. Printa

// ---------------------------------------
// ---------------------------------------

bool pesquisaArvoreBinaria(PtrNoArvore *no, char* valor) {
  // clausulas base - recursao
  // se o elemento nao existir -> false [ ptr == NULL] [X]
  if((*no) == NULL) return false;
  // se existir o elemento -> true [X]
  if((*no)->chave == valor) return (true);
  // recursiva
  if(strcmp(valor,(*no)->chave) == 1) {
    return(pesquisaArvoreBinaria(&(*no)->direita, valor));
  } else { // <
    return(pesquisaArvoreBinaria(&(*no)->esquerda, valor));
  }
}
// ---------------------------------------
// ---------------------------------------

PtrNoArvore pegarMaiorElemento(PtrNoArvore *no) {
  // vai ter que andar p direita, até que ...
  // o ultimo n� aponta para nulo (dir)
  while ((*no)->direita != NULL) {
    (*no) = (*no)->direita;
  }
  // terminou o while, (*no) cont�m o maior elemento
  // esse cara � quem a gente precisa retornar
  PtrNoArvore ret = (*no);
  (*no) = (*no)->esquerda; // NULL ou não NULL
  return(ret);
}

// ---------------------------------------
// ---------------------------------------

bool removerArvoreBinaria(PtrNoArvore *no, char* valor) {
  if((*no) == NULL) return false;
  if((*no)->chave == valor) {
    PtrNoArvore rm = (*no);
    // Aqui dentro tem um tratamento maior
    // 4 casos de remo��o
    //  c1: n� que possui filho da direita, mas n�o tem o da esquerda (sub-arvore da esquerda � nula)
    if((*no)->esquerda == NULL && (*no)->direita != NULL) {
      printf("Debug: caso 1 - sub-arvore esquerda nula\n");
      (*no) = (*no)->direita;
    }
    // c2: n� que � folha (n�o tem subarvore direita, nem esquerda)
    else if((*no)->direita == NULL && (*no)->esquerda == NULL) {
      printf("Debug: caso 2 - folha\n");
      (*no) = NULL;
    }
    // c3: n� que possui filho da esquerda, mas n�o tem o da direita (sub-arvore direita � nula)
    else if((*no)->esquerda != NULL && (*no)->direita == NULL) {
      printf("Debug: caso 3 - sub-arvore direita nula\n");
      (*no) = (*no)->esquerda;
    }
    // **c4**: n� que tem ambas as sub-arvores
    else {  // op1: maior da subarvore esquerda
      printf("Debug: caso 4 - existem ambas sub-arvores\n");
      rm = pegarMaiorElemento(&(*no)->esquerda);
      // AQUI (no) = no->esq
      (*no)->chave = rm->chave;
    }
    free(rm);
    return true;
  }
  // recursiva
  if(strcmp(valor, (*no)->chave) > 0) {
    return(removerArvoreBinaria(&(*no)->direita, valor));
  } else { // <
    return(removerArvoreBinaria(&(*no)->esquerda, valor));
  }
}
//     op2: menor da subarvore direita
//          f_aux = menor da subarvore dir (ref)
//                 salvar em um ptr (return)
//                 no = no->dir

////////////////////////////////////////////////////////


// Implementação feita na sala de aula da arvore avl
// modificado para armazenar strings em seus nós

//NoAVL* PtrNoAVL
typedef struct NoAVL* PtrNoAVL;

typedef struct NoAVL{
  PtrNoAVL dir, esq;
  char* chave;
  int altura; // novidade no nó de AVL
} NoAVL;

//------------------------------------
//------------------------------------

void iniciaArvoreAVL(PtrNoAVL *no){
  (*no) = NULL;
}

bool estaVaziaArvoreAVL(PtrNoAVL *no) {
  return((*no) == NULL);
}

void preOrdemAVL(PtrNoAVL *no) {
  if((*no) == NULL) return;
  // print
  printf("%d ", (*no)->chave);
  // esq (recursivamente)
  preOrdemAVL(&(*no)->esq);
  // dir (recursivamente)
  preOrdemAVL(&(*no)->dir);
}

void preOrdemPrincipal(PtrNoAVL *no){
  printf("Pre-ordem = {");
  preOrdemAVL(no);
  printf("}\n");
}
//------------------------------------
//------------------------------------

int alturaArvoreAVL(PtrNoAVL *no) {
  if ((*no) == NULL) return 0;
  else return (*no)->altura;
}

int atualizaAlturaNoAVL(PtrNoAVL *esq, PtrNoAVL *dir) {
  int ae, ad, ret;
  ae = alturaArvoreAVL(&(*esq));
  ad = alturaArvoreAVL(&(*dir));

  if(ae >= ad) {
    ret = ae + 1;
  } else { // ad > ae
    ret = ad + 1;
  }
  return (ret);
}

void rotacaoSimplesDireita(PtrNoAVL *p) {
  printf(" - Rotação Simples Direita ... \n");
  PtrNoAVL v = (*p)->esq;
  (*p)->esq  = v->dir;
  v->dir     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoSimplesEsquerda(PtrNoAVL *p) {
  printf(" - Rotação Simples Esquerda ... \n");
  PtrNoAVL v = (*p)->dir;
  (*p)->dir  = v->esq;
  v->esq     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoDuplaDireita(PtrNoAVL *p) {
  printf(" - Rotação Dupla Direita ... \n");

  PtrNoAVL u = (*p)->esq;
  PtrNoAVL v = u->dir;
  u->dir     = v->esq;
  (*p)->esq  = v->dir;
  v->esq     = u;
  v->dir     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura    = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}

void rotacaoDuplaEsquerda(PtrNoAVL *p){
  printf(" - Rotação Dupla Esquerda ... \n");
  PtrNoAVL u = (*p)->dir;
  PtrNoAVL v = u->esq;
  u->esq     = v->dir;
  (*p)->dir  = v->esq;
  v->esq     = (*p);
  v->dir     = u;
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura    = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}


void aplicarRotacoes(PtrNoAVL *no) {  // se entrou, o FB do *no é -2, ou 2
  int ae, ad, fatorBalanceamento;
  ae = alturaArvoreAVL(&(*no)->esq);
  ad = alturaArvoreAVL(&(*no)->dir);
  fatorBalanceamento = ad - ae;
  PtrNoAVL u;
  int aUdir, aUesq;
  if(fatorBalanceamento == -2) {
    u = (*no)->esq;
    aUdir = alturaArvoreAVL(&u->dir);
    aUesq = alturaArvoreAVL(&u->esq);
    //Rotacoes p Direita {Simples, Dupla}
    if(aUesq >= aUdir) {
      rotacaoSimplesDireita(&(*no));
    } else {
      rotacaoDuplaDireita(&(*no));
    }
  } else { // == +2
    u = (*no)->dir;
    aUdir = alturaArvoreAVL(&u->dir);
    aUesq = alturaArvoreAVL(&u->esq);
    //Rotacoes p Esquerda {Simples, Dupla}
    if(aUdir >= aUesq) {
      rotacaoSimplesEsquerda(&(*no));
    } else {
      rotacaoDuplaEsquerda(&(*no));
    }
  }
}

bool insereArvoreAVL(PtrNoAVL *no, char* valor) {

  // verificacoes, clausulas de fim de recursao
  //  - ponto de insercao (true)
  if((*no) == NULL) {
    (*no) = malloc(sizeof(NoAVL));
    (*no)->esq = NULL;
    (*no)->dir = NULL;
    (*no)->chave = valor;
    (*no)->altura = 1;  // novidade na AVL
    printf("Inserindo valor = %s\n", valor);
    return true;
  }
  //  - não insere (valor duplicado) (false)
  if((*no)->chave == valor) {
    printf("Warning: elemento duplicado, não inserindo\n");
    return false;
  }

// clausulas recursivas
//  valor > no->chave: chamada recursiva direita
//  valor < no->chave: chamada recursiva esquerda
  bool ret;
  if(strcmp(valor, (*no)->chave) > 0) {
    ret = insereArvoreAVL(&(*no)->dir, valor);
  } else {
    ret = insereArvoreAVL(&(*no)->esq, valor);
  }
  // --------------------------
  // Daqui p baixo é novidade da AVL
  // --------------------------

  // nao inseriu elemento, nao desbalanceou
  if(!ret) return false;
  // PODE ter desbalanceamento (*no)
  int ad, ae, fatorBalanceamento;
  ad = alturaArvoreAVL(&(*no)->dir);
  ae = alturaArvoreAVL(&(*no)->esq);
  fatorBalanceamento = ad - ae;
  //fb = {-2, -1, 0, 1, 2}
  // valores aceitaveis = {-1, 0, 1}
  // valor desbalanceamento = {-2, +2}
  if(fatorBalanceamento == 2 || fatorBalanceamento == -2) {
    aplicarRotacoes(&(*no));
  }
  //atualizar a altura do no atual (*no)
  (*no)->altura = atualizaAlturaNoAVL(&(*no)->esq, &(*no)->dir);
  return true;
}

////////////////// Codigo implementado ///////////////////////

// Verifica se o arquivo é vazio
bool isArquivoVazio(FILE *texto){

    fseek (texto, 0, SEEK_END);
    
    if (ftell(texto) == 0){
        
        return false;
    }
    
    rewind(texto);
}

//Passa por todos os characteres escritos para veficar se eles são
bool isArquivoValido(FILE *texto) {

    if (isArquivoVazio(texto)){
        
        return false;
    }
    
    char c;
 
    while (((c = fgetc(texto)) != EOF)){
        
        if (c != '\n' && c != '\0'){
                
        
        }
        
    } 

    rewind(texto);
    return true; 
}

bool isAlgoritimoArvoreBinaria(char* algoritimo){

    return algoritimo == ALGORITIMO_BINARIA;
}

bool isAlgoritimoEscolhidoValido(char* algoritimo){

    return isAlgoritimoArvoreBinaria(algoritimo) || algoritimo == ALGORITIMO_AVL;
}

int main(int argc, const char * argv[]) {

    FILE *texto;

    texto = fopen(argv[1], "r");

    if (texto == NULL || !isArquivoValido(texto)){

        printf("Arquivo inválido!");
        return 0;
    }

    char* algoritmoEscolhido;
    
    strcpy(algoritmoEscolhido, argv[2]);

    if (!isAlgoritimoEscolhidoValido(algoritmoEscolhido)){

        printf("Algoritimo inválido ou não disponivel!");
        return 0;
    }

    if (isAlgoritimoArvoreBinaria(algoritmoEscolhido)){


    } else {


    }

    fclose(texto);
    return 0;
}
