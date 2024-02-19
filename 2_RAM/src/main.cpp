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
  // RAM's program initialization
  RAMMachine ram;  
  ram.LoadProgramFromFile("./data/test7.ram");

  // Reading input tape from file
  ram.LoadInputTapeFromFile("./data/tape_input/tape_2.input");
  //vector<int> input_tape = {1, 2, 3, 4, -5, 100, 2000, 0, -5000, 0};

  // Show the stored program and tags
  ram.ShowInformation();

  // Program execution
  ram.Execute();

  // Writting output tape on a file
  ram.WriteOutputTapeOnFile("./data/tape_output/tape_X.output");

  return 0;
}