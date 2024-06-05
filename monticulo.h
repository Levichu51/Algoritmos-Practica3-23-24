//
// Created by levixhu on 27/10/23.
//

#ifndef P3_ALGO_MONTICULO_H
#define P3_ALGO_MONTICULO_H

#define TAM 256000
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;


void CrearMonticulo(int v[], int n, pmonticulo M);
int quitarMenor(pmonticulo m);
void Hundir(pmonticulo M, int i);
void OrdenarPorMonticulos(int V[], int n);
void imprimirMonticulo(pmonticulo *M);

//Monticulo de Máximos
void CrearMonticuloMax(int v[], int n, pmonticulo M);
void InicializarMonticuloMax(pmonticulo M);
int MonticuloVacioMax(pmonticulo M);
void FlotarMax(pmonticulo M, int i);
void InsertarMax(int x, pmonticulo M);
void HundirMax(pmonticulo M, int i);
int EliminarMax(pmonticulo M);




#endif //P3_ALGO_MONTICULO_H
