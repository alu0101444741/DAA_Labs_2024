/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 27 2024
 *
 * @brief Main program. Divide and Conquer algorithms.
 */

#ifndef MAIN_
#define MAIN_
#include "divide_conquer.h"

/** @brief Main function */
int main(){
  vector<int> array = {200, 18, 9, 1, 0, -5, -200};//{1, -5, 18, 0, 9, 200, -200};
  unsigned size = array.size();
  int elemento = 200;
  unsigned complejidad = 1;

  cout << "[ Inserción ] ";
  ordenacion_por_insercion(array, (int)size - 1, complejidad);
  show_vector(array);
  cout << "Complejidad: " << complejidad << endl;
  

  cout << "[ Búsqueda Binaria ] ";
  complejidad = 0;
  cout << "El elemento " << elemento << " está en la posición " << busqueda_binaria(array, elemento, 0, size - 1, complejidad) << endl;
  cout << "Complejidad: " << complejidad << endl;

  
};

#endif /* MAIN_ */