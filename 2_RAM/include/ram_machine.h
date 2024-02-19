/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 09 2024
 *
 * @brief Definition of the RAM machine.
 */

#ifndef RAM_MACHINE_H
#define RAM_MACHINE_H

#include "instructions_ram.h"

/**
 * @brief Represents a RAM (Random Access Machine) for executing programs.
 *
 * This class defines a RAM machine that can load programs from files,
 * execute them, display information, and interact with input and output tapes.
 */
class RAMMachine {
public:
  /** @brief Constructor for the RAMMachine class. */
  RAMMachine() {}

  /**
   * @brief Loads a program from a file into the RAMMachine. This method reads instructions from the
   * specified file, parses them, and adds them to the program memory of the RAMMachine.
   * @param filename The name of the file containing the program.
   */
  void LoadProgramFromFile(const string& filename);

  /**
   * @brief Loads an input tape from a file into the RAMMachine. This method reads integers separated by commas from the
   * specified file and adds them to the input tape of the RAMMachine.
   * @param filename The name of the file containing the program.
   */
  void LoadInputTapeFromFile(const string& filename);

  /**
   * @brief Writes the current state of the output tape on a file as integers separated by commas. 
   * @param filename The name/path of the output file.
   */
  void WriteOutputTapeOnFile(const string& filename);

  /** @brief Executes the program stored in the RAMMachine's program memory. */
  void Execute();

  /** @brief Displays information about the RAMMachine: stored program and tags. */
  void ShowInformation();

private:
  vector<Instruction*> program_memory_;        ///< The program memory of the RAMMachine.
  vector<int> data_memory_;                    ///< The data memory of the RAMMachine.
  vector<pair<string, unsigned>> labels_;      ///< A vector of labels with their corresponding addresses.
  unsigned program_counter_;                   ///< The program counter of the RAMMachine.
  vector<int> input_tape_;                     ///< The input tape of the RAMMachine.
  vector<int> output_tape_;                    ///< The output tape of the RAMMachine.
  unsigned input_tape_index_;                  ///< The current index in the input tape.
  bool stop_;                                  ///< A boolean flag indicating whether execution should stop.

  string program_info_;                        ///< Information about the loaded program.

  /**
   * @brief Searches for labels in the program file and stores them.
   * @param filename The name of the program file.
   */
  void SearchLabels(const string& filename);

  /**
   * @brief Parses a text line from the program file to extract an instruction.
   * @param line The text line to be parsed.
   */
  void GetInstructionFromTextLine(string& line);

  /**
   * @brief Adds a parsed instruction instruction to the program memory.
   * @param instruction The name of the instruction.
   * @param operand The operand of the instruction.
   * @param operand_type The type of the operand.
   */
  void AddInstruction(const string& instruction, const string& operand, const OperandType& operand_type);
};
#endif // INSTRUCTION_H
