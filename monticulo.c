//
// Created by levixhu on 27/10/23.
//

#include "monticulo.h"

void InicializarMonticulo(pmonticulo M) {
    M->ultimo = -1;
}

void CrearMonticulo(int v[], int n, pmonticulo M) {
    InicializarMonticulo(M);

    for (int i = 0; i < n; i++) { // Copiar v en M->vector
        M->vector[i] = v[i];
    }

    M->ultimo = n - 1;

    // Aplicar Hundir a los nodos desde n/2 hasta 0
    for (int i = n / 2; i >= 0; i--) {
        Hundir(M, i);
    }
}

int quitarMenor(pmonticulo M) {
    int x;

    if (M == NULL || M->ultimo < 0) {
        perror("Monticulo vacio");
    }

    x = M->vector[0]; // El elemento más pequeño está en la raíz del montículo
    M->vector[0] = M->vector[M->ultimo];
    M->ultimo = M->ultimo - 1;

    if (M->ultimo > 0) {
        Hundir(M, 0); // Llama a la función Hundir con el montículo y la posición 0
    }

    return x; // Devuelve el valor eliminado (el menor).
}

void Hundir(pmonticulo M, int i) {
    int HijoIzq, HijoDer, j;
    int temp;
    j = i;

    do {
        HijoIzq = 2 * i + 1;
        HijoDer = 2 * i + 2;

        if (HijoIzq <= M->ultimo && M->vector[HijoIzq] < M->vector[i] && (HijoDer > M->ultimo || M->vector[HijoIzq] <= M->vector[HijoDer])) {
            i = HijoIzq;
        } else if (HijoDer <= M->ultimo && M->vector[HijoDer] < M->vector[i]) {
            i = HijoDer;
        }

        if (j != i) {
            // Intercambiar M->vector[j] y M->vector[i]
            temp = M->vector[j];
            M->vector[j] = M->vector[i];
            M->vector[i] = temp;
        } else {
            // Si j == i, el nodo alcanzó su posición final
            break;
        }

        j = i;
    } while (1);
}

void OrdenarPorMonticulos(int v[], int n) {
    // Crear un montículo a partir de V
    pmonticulo M = malloc(sizeof(struct monticulo));
    CrearMonticulo(v, n, M);

    // Extraer elementos del montículo y ordenar V
    for (int i = 0; i < n; i++) {
        v[i] = quitarMenor(M);
    }

    free(M); // Liberar la memoria utilizada por el montículo
}

void imprimirMonticulo(pmonticulo *M) {
    if (M == NULL || (*M)->ultimo < 0) {
        printf("Montículo vacío\n");
        return;
    }

    int nivel = 1;
    int elementos_nivel = 1;
    int elementos_impresos = 0;

    for (int i = 0; i <= (*M)->ultimo; i++) {
        printf("%d ", (*M)->vector[i]);
        elementos_impresos++;

        if (elementos_impresos == elementos_nivel) {
            printf("\n");  // Cambiar de línea para el siguiente nivel
            nivel++;
            elementos_nivel = (int) pow(2, nivel - 1);

            elementos_impresos = 0;
        }
    }

    printf("\n");
}

//Implementación de un montículo de Máximos

void CrearMonticuloMax(int v[], int n, pmonticulo M) {
    InicializarMonticuloMax(M);

    for (int i = 0; i < n; i++) { // Copiar v en M->vector
        M->vector[i] = v[i];
    }

    M->ultimo = n - 1;

    // Aplicar Hundir a los nodos desde n/2 hasta 0
    for (int i = n / 2; i >= 0; i--) {
        HundirMax(M, i);
    }
}

void InicializarMonticuloMax(pmonticulo M) {
    M->ultimo = -1;
}

// Función para verificar si el montículo está vacío
int MonticuloVacioMax(pmonticulo M) {
    return M->ultimo == -1;
}

// Procedimiento para flotar el elemento en la posición i
void FlotarMax(pmonticulo M, int i) {
    int temp;
    while (i > 0 && M->vector[(i - 1) / 2] < M->vector[i]) {
        // Intercambiar M->VectorMonticulo[(i-1)/2] y M->VectorMonticulo[i]
        temp = M->vector[(i - 1) / 2];
        M->vector[(i - 1) / 2] = M->vector[i];
        M->vector[i] = temp;

        i = (i - 1) / 2;
    }
}

// Procedimiento para insertar un elemento en el montículo
void InsertarMax(int x, pmonticulo M) {
    if (M->ultimo == TAM - 1) {
        perror("Error: Montículo lleno");
    } else {
        M->ultimo++;
        M->vector[M->ultimo - 1] = x; // Ajuste del índice
        FlotarMax(M, M->ultimo - 1); // Ajuste del índice
    }
}

// Procedimiento para hundir el elemento en la posición i
void HundirMax(pmonticulo M, int i) {
    int HijoIzq, HijoDer, j;
    int temp;
    do {
        HijoIzq = 2 * i + 1;
        HijoDer = 2 * i + 2;
        j = i;

        if (HijoDer <= M->ultimo && M->vector[HijoDer] > M->vector[i]) {
            i = HijoDer;
        }

        if (HijoIzq <= M->ultimo && M->vector[HijoIzq] > M->vector[i]) {
            i = HijoIzq;
        }

        // Intercambiar M->vector[j] y M->vector[i]
        if (j != i) {
            temp = M->vector[j];
            M->vector[j] = M->vector[i];
            M->vector[i] = temp;
        } else {
            // Si j == i, el nodo alcanzó su posición final
            break;
        }
    } while (1);
}

// Función para eliminar el elemento máximo del montículo
int EliminarMax(pmonticulo M) {
    int x = 0;

    if (MonticuloVacioMax(M)) {
        perror("Error: Montículo vacío");

    } else {
        x = M->vector[0]; // Ajuste del índice
        M->vector[0] = M->vector[M->ultimo - 1]; // Ajuste del índice
        M->ultimo--;

        if (M->ultimo > 0) {
            HundirMax(M, 0); // Ajuste del índice
        }
    }
    return x;
}