#include <math.h>
#include <stdio.h>

#define NUM_CLIENTES 5
#define NUM_CLUSTERS 3

typedef struct {
  double gasto;
  int visitas;
  int cluster;
} Cliente;

double distanciaEuclidiana(double gasto1, int visitas1, double gasto2,
                           int visitas2) {
  return sqrt(pow(gasto1 - gasto2, 2) + pow(visitas1 - visitas2, 2));
}

void atribuirClusters(Cliente clientes[], Cliente centroides[]) {
  for (int i = 0; i < NUM_CLIENTES; i++) {
    double minDistancia =
        distanciaEuclidiana(clientes[i].gasto, clientes[i].visitas,
                            centroides[0].gasto, centroides[0].visitas);
    int cluster = 0;
    for (int j = 1; j < NUM_CLUSTERS; j++) {
      double distancia =
          distanciaEuclidiana(clientes[i].gasto, clientes[i].visitas,
                              centroides[j].gasto, centroides[j].visitas);
      if (distancia < minDistancia) {
        minDistancia = distancia;
        cluster = j;
      }
    }
    clientes[i].cluster = cluster;
  }
}

void recalcularCentroides(Cliente clientes[], Cliente centroides[]) {
  int contagem[NUM_CLUSTERS] = {0};
  double somaGasto[NUM_CLUSTERS] = {0};
  int somaVisitas[NUM_CLUSTERS] = {0};

  for (int i = 0; i < NUM_CLIENTES; i++) {
    int cluster = clientes[i].cluster;
    contagem[cluster]++;
    somaGasto[cluster] += clientes[i].gasto;
    somaVisitas[cluster] += clientes[i].visitas;
  }

  for (int j = 0; j < NUM_CLUSTERS; j++) {
    if (contagem[j] > 0) {
      centroides[j].gasto = somaGasto[j] / contagem[j];
      centroides[j].visitas = somaVisitas[j] / contagem[j];
    }
  }
}

void salvarClusters(Cliente clientes[], const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  for (int i = 0; i < NUM_CLIENTES; i++) {
    fprintf(file, "%f %d %d\n", clientes[i].gasto, clientes[i].visitas,
            clientes[i].cluster);
  }

  fclose(file);
}

int main() {
  Cliente clientes[NUM_CLIENTES] = {
      {300, 4, 0}, {600, 8, 0}, {150, 3, 0}, {800, 12, 0}, {200, 5, 0}};

  Cliente centroides[NUM_CLUSTERS] = {{300, 4, 0}, {600, 8, 0}, {150, 3, 0}};

  // Primeira iteração
  atribuirClusters(clientes, centroides);
  recalcularCentroides(clientes, centroides);

  // Salvar os dados dos clusters
  salvarClusters(clientes, "clusters.dat");

  return 0;
}
