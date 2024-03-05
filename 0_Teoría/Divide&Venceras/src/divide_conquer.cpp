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
#include "divide_conquer.h"

// La lista DEBER ESTAR ordenada
int busqueda_binaria(vector<int>& lista, int x, unsigned izquierda, unsigned derecha, unsigned& complejidad) {
	if (izquierda > derecha) return -1;   // El elemento no está en la lista 
	complejidad ++; 
	unsigned centro = (izquierda + derecha) / 2;
	if (lista[centro] == x) return centro;  // Elemento encontrado en la posición central
	else if (lista[centro] < x) return busqueda_binaria(lista, x, centro + 1, derecha, complejidad);  // Buscar en la mitad derecha
	else return busqueda_binaria(lista, x, izquierda, centro - 1, complejidad);   // Buscar en la mitad izquierda 
}
    


void ordenacion_por_insercion(vector<int>& lista, int n, unsigned& complejidad) {
  if (n > 0) { // La lista NO está ordenada
    ordenacion_por_insercion(lista, n - 1, complejidad);  // Ordenar la sublista A[1..n-1]
    //insertar_en_orden(lista, n);  // Insertar A[n] en la sublista ordenada A[1..n-1]
    int elemento = lista[n];
    int i = n - 1;
    while ((i >= 0) && (lista[i] > elemento)) {			
      lista[i + 1] = lista[i];
      i = i - 1;

			complejidad += 2;
    }
    lista[i + 1] = elemento;
		complejidad ++;
  }    
}

/**
* @brief Prints a vector of integers
* @param integer_vector
*/
void show_vector(const vector<int>& integer_vector){
  unsigned size = integer_vector.size();
  for (unsigned i = 0; i < size; ++i){
    cout << integer_vector[i];
    if (i < (size - 1)) cout << ", ";
  }
  cout << endl;
}