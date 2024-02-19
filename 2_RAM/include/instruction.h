/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 09 2024
 *
 * @brief Definition of the Instruction interface.
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
#include "utilities.h"
using namespace std;

/** @brief Represents an instruction in the RAM machine. */
class Instruction {
protected:
	string name_;            ///< The name of the instruction.
	string operand_;         ///< The operand of the instruction.
	OperandType type_;       ///< The type of the operand.
public:
	/**
	 * @brief Constructor for the Instruction class.
	 * @param operand The operand of the instruction.
	 * @param type The type of the operand.
	 */
	Instruction(const string& operand, const OperandType& type) : operand_(operand), type_(type) {}

	/**
	 * @brief Executes the instruction, modifying the program counter,
	 * data memory, input tape, output tape, and other relevant parameters.
	 * @param program_counter The program counter.
	 * @param data_memory The data memory of the RAM machine.
	 * @param labels A vector of labels with their corresponding addresses.
	 * @param input_tape The input tape of the RAM machine.
	 * @param output_tape The output tape of the RAM machine.
	 * @param input_tape_index The current index in the input tape.
	 * @param stop A boolean flag indicating whether the execution should stop.
	 */
	virtual void Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                			 const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) = 0;
	
	/**
	 * @brief Getter for the type of the operand.
	 * @return The type of the operand.
	 */
	OperandType GetOperandType() const { return type_; }

	/**
	 * @brief Getter for the operand associated with the instruction.
	 * @return The value of the operand.
	 */
	string GetOperand() const { return operand_; }

	/** @brief Displays information about the instruction: name, type, and value of the operand. */
	void ShowInformation() { cout << name_ << " " << operand_type_to_string(type_) << operand_ << endl; }

	/** @brief Virtual destructor for the Instruction class to ensure proper cleanup of derived classes. */
	virtual ~Instruction() {}
};

#endif // INSTRUCTION_H
