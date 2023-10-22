/*
Nomes:
      - David Augusto Souza Dias
      - Italo Kaique Bertini Bueno
      - Henrique Oliveira
      - Carlos vinicius
*/

// Compilar: [https://jmeubank.github.io/tdm-gcc/download/] - Comando: gcc -g Trabalho_3.c
// Executar:
/*
cd C:\Git\Estrutura_dados\.vscode\output
.\ED1-2023-3-AT03-Benchmark-ItaloDaividHenriqueCarlos C:\Git\Estrutura_dados\.vscode\arquivos\teste.txt arvore-binaria
.\ED1-2023-3-AT03-Benchmark-ItaloDaividHenriqueCarlos C:\Git\Estrutura_dados\.vscode\arquivos\teste.txt arvore-avl
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// TAD
typedef struct contadores
{
  int compBI, compAVL;
  size_t tempBI, tempAVL;
} cont;

// -------------ARVORE BINARIA------------
// ---------------------------------------
typedef struct NoArvore *PtrNoArvore;
typedef struct NoArvore
{
  char chave[30];
  int qntde;
  PtrNoArvore direita;
  PtrNoArvore esquerda;
} NoArvore;

// ---------------------------------------
//----------------ARVORE AVL--------------

typedef struct NoAVL *PtrNoAVL;

typedef struct NoAVL
{

  PtrNoAVL dir, esq;
  int qntde;
  char chave[30];
  int altura;
} NoAVL;
cont conta;
//--------------------------------------------------------------
//--------------------------------------------------------------

//__________________________________________________________ARVORE AVL FUN��ES___________________________________________________________________
// iniciar arvore avl
// altura avl
// atualizaAVL
// atualizaALTURA
// rota��esSimples(direita e esquerda)
// rota��esDupla(direita e esquerda)
// aplicar rota��es
// insere na avl
// imprimirOrdem
// LimparAVL
// ---------------------------------------
// ---------------------------------------

void iniciaAVL(PtrNoAVL *no)
{
  (*no) = NULL;
}

// Funcao que retorna Altura da Arvore AVL.
int alturaAVL(PtrNoAVL *no)
{
  if ((*no) == NULL)
    return 0;
  else
    return (*no)->altura;
}

// Funcao pra atualizar a Altura da Arvore AVL.
int atualizaAlturaNoAVL(PtrNoAVL *esq, PtrNoAVL *dir)
{
  int ae, ad, ret;
  ae = alturaAVL(&(*esq));
  ad = alturaAVL(&(*dir));

  if (ae >= ad)
  {
    ret = ae + 1;
  }
  else
  {
    ret = ad + 1;
  }
  return (ret);
}

// Funcoes de Rotacao da Arvore AVL.
void rotacaoSimplesDireita(PtrNoAVL *p)
{
  PtrNoAVL v = (*p)->esq;
  (*p)->esq = v->dir;
  v->dir = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoSimplesEsquerda(PtrNoAVL *p)
{
  PtrNoAVL v = (*p)->dir;
  (*p)->dir = v->esq;
  v->esq = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoDuplaDireita(PtrNoAVL *p)
{
  PtrNoAVL u = (*p)->esq;
  PtrNoAVL v = u->dir;
  u->dir = v->esq;
  (*p)->esq = v->dir;
  v->esq = u;
  v->dir = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}

void rotacaoDuplaEsquerda(PtrNoAVL *p)
{
  PtrNoAVL u = (*p)->dir;
  PtrNoAVL v = u->esq;
  u->esq = v->dir;
  (*p)->dir = v->esq;
  v->esq = (*p);
  v->dir = u;
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}

void aplicarRotacoes(PtrNoAVL *no)
{
  int ae, ad, fatorBalanceamento;
  ae = alturaAVL(&(*no)->esq);
  ad = alturaAVL(&(*no)->dir);
  fatorBalanceamento = ad - ae;
  PtrNoAVL u;
  int aUdir, aUesq;
  if (fatorBalanceamento == -2)
  {
    u = (*no)->esq;
    aUdir = alturaAVL(&u->dir);
    aUesq = alturaAVL(&u->esq);
    if (aUesq >= aUdir)
    {
      rotacaoSimplesDireita(&(*no));
    }
    else
    {
      rotacaoDuplaDireita(&(*no));
    }
  }
  else
  {
    u = (*no)->dir;
    aUdir = alturaAVL(&u->dir);
    aUesq = alturaAVL(&u->esq);
    if (aUdir >= aUesq)
    {
      rotacaoSimplesEsquerda(&(*no));
    }
    else
    {
      rotacaoDuplaEsquerda(&(*no));
    }
  }
}

bool insereAVL(PtrNoAVL *no, char *valor)
{
  int i;
  conta.compAVL++;
  if ((*no) == NULL)
  {
    (*no) = malloc(sizeof(NoAVL));
    (*no)->esq = NULL;
    (*no)->dir = NULL;
    strcpy((*no)->chave, valor);
    (*no)->qntde = 1;
    (*no)->altura = 1;
    printf("Inserindo valor = %s\n", valor);
    return true;
  }
  conta.compAVL++;
  if (strcmp((*no)->chave, valor) == 0)
  {
    printf("elemento duplicado\n");
    (*no)->qntde++;
    return false;
  }
  bool ret;
  int tam, p = 0;
  if (strlen(valor) >= strlen((*no)->chave))
  {
    tam = strlen(valor);
  }
  else
  {
    tam = strlen((*no)->chave);
  }
  for (i = 0; i < tam && p == 0; i++)
  {
    if (valor[i] > (*no)->chave[i])
    {
      ret = insereAVL(&(*no)->dir, valor);
      p = 1;
    }
    else if (valor[i] < (*no)->chave[i])
    {
      ret = insereAVL(&(*no)->esq, valor);
      p = 1;
    }
  }
  if (!ret)
    return false;
  int ad, ae, fatorBalanceamento;
  ad = alturaAVL(&(*no)->dir);
  ae = alturaAVL(&(*no)->esq);
  fatorBalanceamento = ad - ae;
  if (fatorBalanceamento == 2 || fatorBalanceamento == -2)
  {
    aplicarRotacoes(&(*no));
  }
  (*no)->altura = atualizaAlturaNoAVL(&(*no)->esq, &(*no)->dir);
  return true;
}

void EmOrdemAvl(PtrNoAVL *no)
{
  if ((*no) == NULL)
    return;
  EmOrdemAvl(&(*no)->esq);
  printf("\t%s: %d\n", (*no)->chave, (*no)->qntde);
  EmOrdemAvl(&(*no)->dir);
}

void LimpaAVL(PtrNoAVL *no)
{
  if ((*no) == NULL)
  {
    return;
  }
  LimpaAVL(&(*no)->esq);
  LimpaAVL(&(*no)->dir);
  free((*no));
}

//__________________________________________________________ARVORE BINARIA FUN��ES___________________________________________________________________
// iniciar arvore
// inserir na arvore
// imprimirOrdem(crescente)
// LimparArvore
// ---------------------------------------
// ---------------------------------------

void iniciaBinaria(PtrNoArvore *r)
{
  (*r) = NULL;
}

bool inserirBinaria(PtrNoArvore *no, char *valor)
{
  int i;
  conta.compBI++;
  if ((*no) == NULL)
  {
    (*no) = malloc(sizeof(NoArvore));
    strcpy((*no)->chave, valor);
    (*no)->qntde = 1;
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    printf("Inserindo valor = %s\n", valor);
    return (true);
  }
  conta.compBI++;
  if (strcmp((*no)->chave, valor) == 0)
  {
    (*no)->qntde++;
    printf("Elemento duplicado\n");
    return (false);
  }
  int p = 0, tam;
  bool ret;
  if (strlen(valor) >= strlen((*no)->chave))
  {
    tam = strlen(valor);
  }
  else
  {
    tam = strlen((*no)->chave);
  }
  for (i = 0; i < tam && p == 0; i++)
  {
    if (valor[i] > (*no)->chave[i])
    {
      ret = inserirBinaria(&(*no)->direita, valor);
      p = 1;
    }
    else if (valor[i] < (*no)->chave[i])
    {
      ret = inserirBinaria(&(*no)->esquerda, valor);
      p = 1;
    }
  }
  return ret;
}

void EmOrdemBinaria(PtrNoArvore *no)
{
  if ((*no) == NULL)
    return;
  EmOrdemBinaria(&(*no)->esquerda);
  printf("\t%s: %d\n", (*no)->chave, (*no)->qntde);
  EmOrdemBinaria(&(*no)->direita);
}

void LimparBinaria(PtrNoArvore *no)
{
  if ((*no) == NULL)
  {
    return;
  }
  LimparBinaria(&(*no)->esquerda);
  LimparBinaria(&(*no)->direita);
  free((*no));
}

int main(int argc, char *argv[])
{
  PtrNoAVL comeco;
  PtrNoArvore comecoBI;
  // Declara��o das variaveis
  int i = 0;
  int aux = 1;
  char palavra[20] = " ";

  conta.compAVL = 0;
  conta.compBI = 0;
  // Marca��o de tempo
  size_t auxI, auxF;

  iniciaAVL(&comeco);
  iniciaBinaria(&comecoBI);

  // Teste de Args
  if (argc > 3)
  {

    printf("Muitos Argumentos!\n%d", argc);

    return;
  }
  else if (argc < 3)
  {

    printf("Sem Argumentos Suficientes!\n%d", argc);

    return;
  }
  FILE *entrada = fopen(argv[1], "r"); // abrindo arquivo de entrada para leitura
  // testando abertura de arquivo
  if (entrada == NULL)
  {

    printf("Erro ao Abrir arquivo!\n");

    exit(1);
  }

  // Leitura para Arvore AVL.
  auxI = clock();

  aux = fscanf(entrada, "%s ", palavra);

  while (aux == 1)
  {

    for (i = 0; palavra[i] != '\0'; i++)
    {

      palavra[i] = tolower(palavra[i]);

      switch (palavra[i])
      {

      case '.':
      case ',':
      case ';':
      case ' ':

        palavra[i] = '\0';
      }
    }
    if (strlen(palavra) > 0)
    {

      printf("\n\nlido: \"%s\"\n", palavra);

      insereAVL(&comeco, palavra);
    }

    aux = fscanf(entrada, "%s", palavra);
  }
  // finalizando a leitura
  fclose(entrada);

  // marcando o tempo final
  auxF = clock();

  // calculo do tempo
  conta.tempAVL = auxF - auxI;

  // Leitura para Arvore Binaria.
  entrada = fopen(argv[1], "r");
  // testando a abertura do arquivo
  if (entrada == NULL)
  {

    printf("Erro ao Abrir arquivo!\n");

    exit(1);
  }
  // tempo inicial
  auxI = clock();

  aux = fscanf(entrada, "%s ", palavra);

  while (aux == 1)
  {

    for (i = 0; palavra[i] != '\0'; i++)
    {

      palavra[i] = tolower(palavra[i]);

      switch (palavra[i])
      {

      case '.':
      case ',':
      case ';':
      case ' ':

        palavra[i] = '\0';
      }
    }
    if (strlen(palavra) > 0)
    {

      printf("\n\nlido: \"%s\"\n", palavra);

      inserirBinaria(&comecoBI, palavra);
    }

    aux = fscanf(entrada, "%s", palavra);
  }
  // tempo final
  auxF = clock();
  // calculo do tempo da Binaria
  conta.tempBI = auxF - auxI;
  system("cls");

  // Imprimindo resultados finais ap�s a leitura.
  if (conta.tempAVL <= conta.tempBI)
  {

    printf("Arvore AVL:\n\n\t%d ", conta.compAVL);

    printf("Comparacoes\n\t%.2f ", (float)conta.tempAVL / 100);

    printf("Segundos\n\nArvore Binaria:\n\n\t%d ", conta.compBI);

    printf("Comparacoes\n\t%.2f Segundos\n\n", (float)conta.tempBI / 100);
  }
  else
  {

    printf("Arvore Binaria:\n\n\t%d ", conta.compBI);

    printf("Comparacoes\n\t%.2f ", (float)conta.tempBI / 100);

    printf("Segundos\n\nArvore AVL:\n\n\t%d ", conta.compAVL);

    printf("Comparacoes\n\t%.2f Segundos\n\n", (float)conta.tempAVL / 100);
  }

  printf("Frequencia das Palavras:\n\n");

  if (strcmp(argv[2], "arvore-binaria") == 0)
  {

    EmOrdemBinaria(&comecoBI);
  }
  else if (strcmp(argv[2], "arvore-avl") == 0)
  {

    EmOrdemAvl(&comeco);
  }
  else
  {

    printf("\tParametro de Arvore Invalido!\n");
  }

  // Fechando arquivo
  fclose(entrada);

  // Limpando arvores
  LimparBinaria(&comecoBI);
  LimpaAVL(&comeco);

  return 0;
}
