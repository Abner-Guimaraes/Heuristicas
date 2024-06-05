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
    G->matrizAdjacencia[w][v] = peso;
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
void construcao(Grafo g, int *solucao){
  int n = g->MaxNumeroVertices;

  int cidadeInicial = vertice_aleatorio(g);
  solucao[0] = cidadeInicial;

  for(int i = 1; i < n; i++){
    solucao[i] = vertice_aleatorio(g);
    for(int j = 0; j < i; j++){
      if (solucao[i] == solucao[j]){
        i--;
      }
    }
  }
  
}

int calcDist(Grafo g, int* solucao){
  int dist = 0;
  int n = g->MaxNumeroVertices;
  for(int i = 0; i < n-1; i++){
    dist = dist + g->matrizAdjacencia[solucao[i]][solucao[i+1]];
  }
  dist = dist + g->matrizAdjacencia[solucao[0]][solucao[n-1]];
  return dist;
}

void replicaSolucao(int* s1, int* s2,int n){
    for (int i = 0; i < n; i++)
    {
        s2[i] = s1[i];
    }
    
}

void swap(int *solucao, int i, int j){
  int temp = solucao[i];
  solucao[i] = solucao[j];
  solucao[j] = temp;
}

void twoOptSwap(int* solucao, int i, int j, int n) {
    while (i < j) {
        swap(solucao, i, j);
        i++;
        j--;
    }
}

void VND(Grafo g, int* solucaoAtual, int r) {
    clock_t start, end;
    double cpuTime;

    start = clock();
    int n = g->MaxNumeroVertices;
    int solucao[n];
    int melhora = 0;
    
    for(int iteracao = 0; iteracao < r; iteracao++) {
        for(int i = 0; i < n - 1; i++) {
            for(int j= i + 1; j < n; j++) {
                replicaSolucao(solucaoAtual, solucao, n);
                twoOptSwap(solucao, i, j, n);
                if(calcDist(g, solucao) < calcDist(g, solucaoAtual)) {
                    replicaSolucao(solucao, solucaoAtual, n);
                    melhora = 1;
                }
            }
        }
        if (!melhora) break;
    }
    end = clock();
    cpuTime = ((double) (end - start)) *1000 / CLOCKS_PER_SEC;
    printf("Tempo de Execução (VND) em segundos: %f \n", cpuTime);
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



// Funções do Algoritmo Genético
void inicializaPopulacao(Grafo g, int **populacao, int tamPop) {
  for (int i = 0; i < tamPop; i++) {
    construcao(g, populacao[i]);
  }
}

void avaliarPopulacao(Grafo g, int **populacao, int *fitness, int tamPop) {
  for (int i = 0; i < tamPop; i++) {
    fitness[i] = calcDist(g, populacao[i]);
  }
}

int torneio(int *fitness, int tamPop) {
  int i = rand() % tamPop;
  int j = rand() % tamPop;
  return fitness[i] < fitness[j] ? i : j;
}

void crossover(int *pai1, int *pai2, int *filho, int n) {
  int inicio = rand() % n;
  int fim = rand() % n;
  if (inicio > fim) {
    int temp = inicio;
    inicio = fim;
    fim = temp;
  }

  int* genes = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) genes[i] = -1;

  for (int i = inicio; i <= fim; i++) {
    filho[i] = pai1[i];
    genes[pai1[i]] = 1;
  }

  int geneAtual = 0;
  for (int i = 0; i < n; i++) {
    if (genes[pai2[i]] == -1) {
      while (inicio <= geneAtual && geneAtual <= fim) {
        geneAtual++;
      }
      filho[geneAtual] = pai2[i];
      geneAtual++;
    }
  }

  free(genes);
}

void mutacao(int *individuo, int n) {
  int i = rand() % n;
  int j = rand() % n;
  swap(individuo, i, j);
}

void AG(Grafo g, int *melhorSolucao, int tamPop, int numGeracoes, double taxaCrossover, double taxaMutacao) {
  // começa aqui 

  clock_t start, end;
  double cpuTime;

  start = clock();

  int n = g->MaxNumeroVertices;
  int **populacao = malloc(tamPop * sizeof(int *));
  int *fitness = malloc(tamPop * sizeof(int));
  int *novaPopulacao[tamPop];

  for (int i = 0; i < tamPop; i++) {
    populacao[i] = malloc(n * sizeof(int));
    novaPopulacao[i] = malloc(n * sizeof(int));
  }

  inicializaPopulacao(g, populacao, tamPop);
  avaliarPopulacao(g, populacao, fitness, tamPop);

  for (int geracao = 0; geracao < numGeracoes; geracao++) {
    for (int i = 0; i < tamPop; i++) {
      int pai1 = torneio(fitness, tamPop);
      int pai2 = torneio(fitness, tamPop);

      if ((double)rand() / RAND_MAX < taxaCrossover) {
        crossover(populacao[pai1], populacao[pai2], novaPopulacao[i], n);
      } else {
        replicaSolucao(populacao[pai1], novaPopulacao[i], n);
      }

      if ((double)rand() / RAND_MAX < taxaMutacao) {
        mutacao(novaPopulacao[i], n);
      }
    }

    for (int i = 0; i < tamPop; i++) {
      replicaSolucao(novaPopulacao[i], populacao[i], n);
    }

    avaliarPopulacao(g, populacao, fitness, tamPop);
  }

  int melhorIndice = 0;
  for (int i = 1; i < tamPop; i++) {
    if (fitness[i] < fitness[melhorIndice]) {
      melhorIndice = i;
    }
  }

  end = clock();
  cpuTime = ((double) (end - start)) *1000 / CLOCKS_PER_SEC;
  printf("Tempo de Execução (AG) em segundos: %f \n", cpuTime);
  //termina aqui
  replicaSolucao(populacao[melhorIndice], melhorSolucao, n);
  for (int i = 0; i < tamPop; i++) {
    free(populacao[i]);
    free(novaPopulacao[i]);
  }
  free(populacao);
  free(fitness);
}

void imprime_QualidadeSolucao(int *vetorQualidadesVND, int* vetorQualidadesAG,  FILE *saidaQ) {

  fprintf(saidaQ, "VND AG \n");

  for(int i =0; i< 10; i++){
    fprintf(saidaQ, "%d %d", vetorQualidadesVND[i], vetorQualidadesAG[i]);
    fprintf(saidaQ,"\n");
  }

}

void imprime_TempoSolucao(double *vetorTemposVND, double* vetorTemposAG,  FILE *saidaT) {

  fprintf(saidaT, "VND AG \n");
  for(int i =0; i< 10; i++){
    fprintf(saidaT, "%f %f", vetorTemposVND[i], vetorTemposAG[i]);
    fprintf(saidaT,"\n");
  }

}


int main(void) {
  srand(time(NULL));

  clock_t start, end;
  double cpuTime;


  int PesoMaximo = 50;
  int vetorQualidadesVND[10];
  int vetorQualidadesAG[10];
  double vetorTemposVND[10];
  double vetorTemposAG[10];
  FILE *saidaQ = fopen("qualidade_solucoes", "w");
  FILE *saidaT= fopen("tempo_solucoes", "w");

  int NumeroMaxVertices = rand() % 51 + 25;
  int QuantidadeMaxArestas = NumeroMaxVertices * (NumeroMaxVertices - 1) / 2; // n*(n-1)/2

  for (int i = 0; i < 10; i++) {
    char nome_arquivo[20];
    sprintf(nome_arquivo, "grafo_%d.txt", i); // Nome do arquivo com um número incremental
    FILE *saida = fopen(nome_arquivo, "w");

    if (saida == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return 1;
    }
    printf("Numero total de Vertices: %d\n", NumeroMaxVertices);
    printf("Numero total de Arestas: %d\n", QuantidadeMaxArestas);

    Grafo G = Criacao_grafo_aleatorio(NumeroMaxVertices, QuantidadeMaxArestas, PesoMaximo);
    int solucao[NumeroMaxVertices];
    int s2[NumeroMaxVertices];
    construcao(G, solucao);
    replicaSolucao(solucao,s2, NumeroMaxVertices);
    printf("Solução: ");
    for (int i = 0; i < NumeroMaxVertices; i++)
    {
        printf("%d ",solucao[i]);
        
    }
    printf("| Qualidade primeira solução: %d \n", calcDist(G, solucao));
    start = clock();
    VND(G,solucao,100);
    vetorQualidadesVND[i] = calcDist(G,solucao);

    end = clock();
    cpuTime = ((double) (end - start)) *1000 / CLOCKS_PER_SEC;
    vetorTemposVND[i] = cpuTime;

    printf("Solução: ");
    for (int i = 0; i < NumeroMaxVertices; i++)
    {
        printf("%d ", solucao[i]);
    }
    printf("| Qualidade solução pós-VND: %d \n", calcDist(G, solucao));
    start = clock();
    AG(G, s2, 100, 200, 0.7, 0.01);
    end = clock();
    cpuTime = ((double) (end - start)) *1000 / CLOCKS_PER_SEC;
    vetorQualidadesAG[i] = calcDist(G,s2);
    vetorTemposAG[i] = cpuTime;
    printf("Solução: ");
    for (int i = 0; i < NumeroMaxVertices; i++)
    {
        printf("%d ", s2[i]);
    }
    printf("| Qualidade solução pós-AG: %d \n", calcDist(G, s2));

    imprime_ArquivoGrafo(G, saida);
    free_liberaGrafo(G);
    fclose(saida);
  }
  imprime_QualidadeSolucao(vetorQualidadesVND,vetorQualidadesAG,saidaQ);
  imprime_TempoSolucao(vetorTemposVND,vetorTemposAG,saidaT);

  return 0;
}
