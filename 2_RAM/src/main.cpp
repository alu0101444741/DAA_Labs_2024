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

void manual_ram_execution(string test_filename, string input_tape_filename, string output_tape_filename);

int main(int argc, char* argv[]) {

  manual_ram_execution("test_modificacion", "tape_mod", "tape_outmod"); return 0;

  // Arguments validation
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " test.ram filename.input filename.output debug" << endl;
    return 1;
  }
  string program_file = argv[1], input_file  = argv[2], output_file = argv[3];

  // Debug mode validation
  int debug = atoi(argv[3]);
  if (debug < 0 || debug > 2) {
    cerr << "Error: Debug must be between 0 and 2." << endl;
    return 1;
  }
  // RAM's program initialization
  RAMMachine ram;  
  ram.LoadProgramFromFile(program_file);  
  ram.LoadInputTapeFromFile("./data/tape_input/tape_2.input"); // Reading input tape from file  
  //ram.ShowInformation(); // Show the stored program and tags  
  ram.Execute(2); // Program execution  
  ram.WriteOutputTapeOnFile("./data/tape_output/tape_X.output"); // Writting output tape on a file
  return 0;
}

void manual_ram_execution(string test_filename, string input_tape_filename, string output_tape_filename) {
  RAMMachine ram;
  const string folder_name = "./data/";
  ram.LoadProgramFromFile(folder_name + test_filename + ".ram");
  ram.LoadInputTapeFromFile(folder_name + "tape_input/" + input_tape_filename + ".input");
  //vector<int> input_tape = {1, 2, 3, 4, -5, 100, 2000, 0, -5000, 0};
  ram.Execute(2);
  ram.WriteOutputTapeOnFile(folder_name + "tape_output/" + output_tape_filename + ".output");
}