#ifndef FUNCIONES_SENKU
#define FUNCIONES_SENKU

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include "Funciones.h"
using namespace std;

char** generar_tablero(int filas_columnas, int centro, int borde_1, int borde_2, int tab);
void imprimir_tablero(char** tablero, int filas_columnas);
bool posiciones_invalidas(char** tablero, int fila1, int columna1, int fila2, int columna2, int filas_columnas);
void mover_ficha(char** tablero, int filas_columnas);
bool quedan_movimientos(char** tablero, int filas_columnas, int borde);
void resultados(char** tablero, int filas_columnas);
void eliminar_tablero(char** tablero, int filas_columnas);
void tablero_ingles();
void tablero_aleman();
void tablero_diamante();
void menu();

#endif