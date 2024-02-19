/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 09 2024
 *
 * @brief Main program to test the RAM machine.
 */

#include "ram_machine.h"

int main() {
  RAMMachine ram;
  ram.LoadProgramFromFile("./input/test7.ram");

  vector<int> input_tape = {1, 2, 3, 4, -5, 100, 2000, 0, -5000, 0};

  ram.ShowInformation();

  ram.Execute(input_tape);

  return 0;
}