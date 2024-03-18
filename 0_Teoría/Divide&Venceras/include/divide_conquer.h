/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 27 2024
 *
 * @brief Some 'Divide and Conquer' algorithms. Implementation.
 * 
 */

#ifndef DIVIDE_CONQUER_H_
#define DIVIDE_CONQUER_H_

#include <iostream>
#include <vector>
using namespace std;

int busqueda_binaria(vector<int>& lista, int x, unsigned izquierda, unsigned derecha, unsigned& complejidad);

void ordenacion_por_insercion(vector<int>& lista, int n, unsigned& complejidad);

template <typename T>
void show_vector(const vector<T>& integer_vector);

#endif /* DIVIDE_CONQUER_H_ */
