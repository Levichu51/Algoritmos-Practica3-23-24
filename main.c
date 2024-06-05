#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "monticulo.h"


void inicializar_semilla();
void aleatorio(int v[], int n);
void aleatorioAscendente(int v[], int n);
void aleatorioDescendente(int v[], int n);
void imprimirVector(int v[], int n);
int esOrdenado(int v[], int n);
double microsegundos();


void demostracionMonticulo(void (*ordenacion)(int v[], int n, pmonticulo m), void (*generador)(int v[], int n), int n);
void calculosTiemposDemostracion(int n, double time);
void DemostrarComplejidadMonticulo();


void test(void (*ordenacion)(int v[], int n), void (*generador)(int v[], int n), int n);
void calculosTiempos(int n,  double time);
void analizarTiempos(void (*ordenacion)(int v[], int n), void (*generador)(int v[], int n),int num_sizes);
void ComplejidadMonticulo();




void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v [], int n) {
    int i, m = 2*n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void aleatorioAscendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void aleatorioDescendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
}

void imprimirVector(int v[], int n) {
    printf("[");
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", v[i]);
    }
    printf("]  \t");
}

int esOrdenado(int v[], int n){
    if (n <= 1) {
        return 1;
    }

    for (int i = 1; i < n; i++) {
        if (v[i] < v[i - 1]) {
            return 0;
        }
    }

    return 1;
}

double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void demostracionMonticulo(void (*ordenacion)(int v[], int n, pmonticulo M), void (*generador)(int v[], int n), int n) { //lo del else
    inicializar_semilla();
    int k;
    double elapsed_time1, start_time, end_time, t1, t2;
    int *v;
    pmonticulo M;

    M = malloc(sizeof (struct monticulo));
    v = malloc(n * sizeof (int));

    generador(v, n);

    start_time = microsegundos();
    ordenacion(v, n, M);
    end_time = microsegundos();
    elapsed_time1 = end_time - start_time;

    if (elapsed_time1 < 500) {
        printf("(*)");
        start_time = microsegundos();

        for (k = 0; k < 100; k++) {
            generador(v, n);
            ordenacion(v, n, M);
        }
        end_time = microsegundos();
        t1 = end_time - start_time;
        start_time = microsegundos();

        for (k = 0; k < 100; k++) {
            generador(v, n);
        }
        end_time = microsegundos();
        t2 = end_time - start_time;

        elapsed_time1 = (t1 - t2) / 100;
        calculosTiemposDemostracion(n, elapsed_time1);

    } else {
        calculosTiemposDemostracion(n, elapsed_time1);
    }
    free(v);
    free(M);
}

void calculosTiemposDemostracion(int n, double time){
    double time1, time2, time3;

    time1 = time / (pow(n, 0.80));
    time2 = time / (pow(n, 1));
    time3 = time / (pow(n, 1.2));

    printf("\t% 8d\t\t% 15.3lf\t\t% 14.8lf\t\t% 14.8lf\t\t% 14.8lf\n", n, time, time1, time2, time3);
}


void DemostrarComplejidadMonticulo(){
    int i;

    printf("Ordenacion aleatoria\n");
    printf("\t       n\t\t\t  t(n)\t\t   t(n) / n^0.8\t\t   t(n) / n^1\t          t(n) / n^1.2\n");
    for(i = 500; i <= 256000; i = i * 2){
        demostracionMonticulo(CrearMonticulo, aleatorio, i);
    }
    printf("\n\n");

    printf("Ordenacion ascendente\n");
    printf("\t       n\t\t\t  t(n)\t\t   t(n) / n^0.8\t\t   t(n) / n^1\t          t(n) / n^1.2\n");
    for(i = 500; i <= 256000; i = i * 2){
        demostracionMonticulo(CrearMonticulo, aleatorioAscendente, i);
    }
    printf("\n\n");

    printf("Ordenacion descendente\n");
    printf("\t       n\t\t\t  t(n)\t\t   t(n) / n^0.8\t\t   t(n) / n^1\t          t(n) / n^1.2\n");
    for(i = 500; i <= 256000; i = i * 2){
        demostracionMonticulo(CrearMonticulo, aleatorioDescendente, i);
    }
    printf("\n\n");

}

void analizarTiempos(void (*ordenacion)(int v[], int n), void (*generador)(int v[], int n), int n) { //mejorar el else
    inicializar_semilla();
    int k;
    double elapsed_time1, start_time, end_time, t1, t2;
    int *v;

    v = malloc(n * sizeof (int));

    generador(v, n);

    start_time = microsegundos();
    ordenacion(v, n);
    end_time = microsegundos();
    elapsed_time1 = end_time - start_time;

    if (elapsed_time1 < 500) {
        printf("(*)");
        start_time = microsegundos();

        for (k = 0; k < 100; k++) {
            generador(v, n);
            ordenacion(v, n);
        }
        end_time = microsegundos();
        t1 = end_time - start_time;
        start_time = microsegundos();

        for (k = 0; k < 100; k++) {
            generador(v, n);
        }
        end_time = microsegundos();
        t2 = end_time - start_time;

        elapsed_time1 = (t1 - t2) / 100;
        calculosTiempos(n, elapsed_time1);

    } else {
        calculosTiempos(n, elapsed_time1);
    }
    free(v);
}

void calculosTiempos(int n, double time){
    double time1, time2, time3;

    time1 = time / (pow(n, 0.85));
    time2 = time / (pow(n, 1) * log2(n));
    time3 = time / (pow(n, 1.33));

    printf("\t% 8d\t\t% 15.3lf\t\t% 14.8lf\t\t% 14.8lf\t\t% 14.8lf\n", n, time, time1, time2, time3);
}

void ComplejidadMonticulo(){
    int i;

    printf("Ordenacion aleatoria\n");
    printf("\t       n\t\t\t  t(n)\t\t t(n) / n^0.85\t        t(n) / n^1*log2(n)\t    t(n) / n^1.33\n");
    for(i = 500; i <= 256000; i = i * 2){
        analizarTiempos(OrdenarPorMonticulos, aleatorio, i);
    }
    printf("\n\n");

    printf("Ordenacion ascendente\n");
    printf("\t       n\t\t\t  t(n)\t\t t(n) / n^0.85\t        t(n) / n^1*log2(n)\t    t(n) / n^1.33\n");
    for(i = 500; i <= 256000; i = i * 2){
        analizarTiempos(OrdenarPorMonticulos, aleatorioAscendente, i);
    }
    printf("\n\n");

    printf("Ordenacion descendente\n");
    printf("\t       n\t\t\t  t(n)\t\t t(n) / n^0.85\t        t(n) / n^1*log2(n)\t    t(n) / n^1.33\n");
    for(i = 500; i <= 256000; i = i * 2){
        analizarTiempos(OrdenarPorMonticulos, aleatorioDescendente, i);
    }
    printf("\n\n");

}

void test(void (*ordenacion)(int v[], int n), void (*generador)(int v[], int n), int n) {
    int v[n];
    pmonticulo M;
    M = malloc(sizeof (struct monticulo));

    generador(v, n);

    CrearMonticulo(v, n, M);
    printf("Monticulo: \n");
    imprimirMonticulo(&M);

    printf("\n");
    imprimirVector(v, n);

    printf("\n");

    if (esOrdenado(v, n)) {
        printf("ordenado? 1\n");
    } else {
        printf("ordenado? 0\n");
    }

    ordenacion(v, n);

    printf("Ordenacion\n");
    imprimirVector(v, n);
    printf("\n");

    if (esOrdenado(v, n)) {
        printf("ordenado? 1\n");
    } else {
        printf("ordenado? 0\n");
    }

    free(M);
}

void testMax(void (*ordenacion)(int v[], int n), void (*generador)(int v[], int n), int n) {
    int v[n];
    pmonticulo M;
    M = malloc(sizeof (struct monticulo));

    generador(v, n);

    CrearMonticuloMax(v, n, M);
    printf("Monticulo: \n");
    imprimirMonticulo(&M);

    printf("\n");
    imprimirVector(v, n);

    printf("\n");

    if (esOrdenado(v, n)) {
        printf("ordenado? 1\n");
    } else {
        printf("ordenado? 0\n");
    }

    ordenacion(v, n);

    printf("Ordenacion\n");
    imprimirVector(v, n);
    printf("\n");

    if (esOrdenado(v, n)) {
        printf("ordenado? 1\n");
    } else {
        printf("ordenado? 0\n");
    }

    free(M);
}


int main() {
    inicializar_semilla();

    ///test
    printf("Inicializacion aleatoria\n\n");
    test(&OrdenarPorMonticulos, &aleatorio, 10);
    printf("\n\n");
    printf("Inicializacion descendente\n\n");
    test(&OrdenarPorMonticulos, &aleatorioDescendente, 10);
    printf("\n\n");
    printf("Inicializacion ascendente\n\n");
    test(&OrdenarPorMonticulos, &aleatorioAscendente, 10);

    printf("\n\n");
    printf("\n\n");
    printf("MONTICULOS MAXIMOS TEST\n");

    ///testMax
    printf("Inicializacion aleatoria\n\n");
    testMax(&OrdenarPorMonticulos, &aleatorio, 10);
    printf("\n\n");
    printf("Inicializacion descendente\n\n");
    testMax(&OrdenarPorMonticulos, &aleatorioDescendente, 10);
    printf("\n\n");
    printf("Inicializacion ascendente\n\n");
    testMax(&OrdenarPorMonticulos, &aleatorioAscendente, 10);

    printf("\n\n\n");

    ///Análisis de la complejidad de HeapSort y Demostración de que CrearMonticulo es O(n)
    printf("Demostracion de CrearMonticulo\n\n");
    DemostrarComplejidadMonticulo();

    printf("\n\n\n\n");

    printf("Análisis de la complejidad de HeapSort\n\n");
    ComplejidadMonticulo();




    return 0;
}
