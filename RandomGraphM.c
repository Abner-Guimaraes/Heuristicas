#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*+-----------------------------------------------------------+
 | UNIFAL – Universidade Federal de Alfenas.                   |
 | BACHARELADO EM CIENCIA DA COMPUTACAO.                       |
 | Trabalho: Algoritmos em Grafos                              |
 | Disciplina: Algoritmos e Estrutura de Dados II – Pratica    |
 | Professor: Iago Augusto Carvalho                            |
 | Aluno(s): Abner Gomes Guimarães - Felipe Araújo Correia     |
 |                                                             |
 |                                                             |
 | Data: 05/06/2024                                            |
 +-------------------------------------------------------------+
*/

typedef struct grafo {
  int **matrizAdjacencia;
  int MaxNumeroVertices;
  int QuantidadeArestas;
} * Grafo;

// Entrega um vertice aleatorio para a criação de aresta entre dois vertices;
int vertice_aleatorio(Grafo G) {
  double r;
  r = (double)rand() / ((double)RAND_MAX + 1.0);
  return (int)(r * G->MaxNumeroVertices);
}

// Cria um grafo com n vertices e 0 arestas;
Grafo iniciar_Grafo(int n) {
  Grafo G = malloc(sizeof *G);
  G->MaxNumeroVertices = n;
  G->QuantidadeArestas = 0;

  G->matrizAdjacencia = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    G->matrizAdjacencia[i] = malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      G->matrizAdjacencia[i][j] = 0; // Inicializa com 0 (sem aresta)
    }
  }
  return G;
}

// Insere uma aresta no grafo
void insere_aresta(Grafo G, int v, int w, int peso) {
  if (G->matrizAdjacencia[v][w] == 0) {
    G->matrizAdjacencia[v][w] = peso;
    G->QuantidadeArestas++;
  }
}

// Faz um grafo aleatorio, utilizando parametros definidos e utilizando funções acima;
Grafo Criacao_grafo_aleatorio(int n, int m, int PesoMaximo) {
  Grafo G = iniciar_Grafo(n);
  while (G->QuantidadeArestas < m) {
    int v = vertice_aleatorio(G);
    int w = vertice_aleatorio(G);
    if (v != w) {
      int peso = rand() % PesoMaximo + 1;
      insere_aresta(G, v, w, peso);
    }
  }
  return G;
}

// Faz a impressão de um grafo em um arquivo;
void imprime_ArquivoGrafo(Grafo G, FILE *saida) {
  int resposta = 0;

  fprintf(saida, "Numero de Vertices: %d\n", G->MaxNumeroVertices);
  fprintf(saida, "Numero de Arestas: %d\n", G->QuantidadeArestas);

  while (resposta != 1 && resposta != 2) {
    printf("Escolha a opção com peso ou sem peso para escrever no arquivo txt:");
    printf("\n1. Digite 1 para mostrar sem peso\n2. Digite 2 para mostrar com peso\n> ");
    scanf("%d", &resposta);
  }

  switch (resposta) {
    case 1:
      for (int i = 0; i < G->MaxNumeroVertices; i++) {
        fprintf(saida, "Vertice %d:", i);
        for (int j = 0; j < G->MaxNumeroVertices; j++) {
          if (G->matrizAdjacencia[i][j] != 0) {
            fprintf(saida, " %d", j);
          }
        }
        fprintf(saida, "\n");
      }
      break;
    case 2:
      for (int i = 0; i < G->MaxNumeroVertices; i++) {
        fprintf(saida, "Vertice %d:", i);
        for (int j = 0; j < G->MaxNumeroVertices; j++) {
          if (G->matrizAdjacencia[i][j] != 0) {
            fprintf(saida, " (%d peso %d)", j, G->matrizAdjacencia[i][j]);
          }
        }
        fprintf(saida, "\n");
      }
      break;
    default:
      printf("\nOpção inválida!\n");
      break;
  }
}

// Free em tudo do grafo no final do código;
void free_liberaGrafo(Grafo G) {
  if (G == NULL)
    return;

  for (int i = 0; i < G->MaxNumeroVertices; i++) {
    free(G->matrizAdjacencia[i]);
  }

  free(G->matrizAdjacencia);
  free(G);
}

int main(void) {
  srand(time(NULL));

  int PesoMaximo = 50;

  for (int i = 0; i < 10; i++) {
    char nome_arquivo[20];
    sprintf(nome_arquivo, "grafo_%d.txt", i); // Nome do arquivo com um número incremental
    FILE *saida = fopen(nome_arquivo, "w");

    if (saida == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return 1;
    }

    int NumeroMaxVertices = rand() % 51 + 25;
    printf("Numero total de Vertices: %d\n", NumeroMaxVertices);
    int QuantidadeMaxArestas = NumeroMaxVertices * (NumeroMaxVertices - 1) / 2; // n*(n-1)/2
    printf("Numero total de Arestas: %d\n", QuantidadeMaxArestas);

    Grafo G = Criacao_grafo_aleatorio(NumeroMaxVertices, QuantidadeMaxArestas, PesoMaximo);
    imprime_ArquivoGrafo(G, saida);
    free_liberaGrafo(G);
    fclose(saida);
  }

  return 0;
}
