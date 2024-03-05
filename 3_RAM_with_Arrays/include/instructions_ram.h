/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 09 2024
 *
 * @brief Definition of the RAM machine instructions.
 */

#ifndef INSTRUCTIONS_RAM_H
#define INSTRUCTIONS_RAM_H

#include <cmath>
#include "instruction.h"

/** @brief Class for the LOAD instruction. */
class LOAD : public Instruction {
public:
	/** @brief Constructor for the LOAD instruction class. */
	LOAD(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index)  { name_ = "LOAD"; };
	
	/**
	 * @brief Executes de LOAD instruction. Store in R0 a value based on the operand.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the STORE instruction. */
class STORE : public Instruction {
public:
	/** @brief Constructor for the STORE instruction class. */
	STORE(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "STORE"; };

	/**
	 * @brief Executes de STORE instruction. Store the R0 value on memory based on the operand.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the READ instruction. */
class READ : public Instruction {
public:
	/** @brief Constructor for the READ instruction class. */
	READ(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "READ"; };

	/**
 * @brief Executes de READ instruction. Reads a value from the input tape and store it on memory based on the operand.
 * To know about the parameters @see Instruction::Execute(...)
 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the WRITE instruction. */
class WRITE : public Instruction {
public:
	/** @brief Constructor for the WRITE instruction class. */
	WRITE(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "WRITE"; };

	/**
	 * @brief Executes de WRITE instruction. Writes the value given by the operand on the output tape.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the ADD instruction. */
class ADD : public Instruction {
public:
	/** @brief Constructor for the ADD instruction class. */
	ADD(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "ADD"; };

	/**
	 * @brief Executes de ADD instruction. Add a given operand to the R0 value.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the SUB instruction. */
class SUB : public Instruction {
public:
	/** @brief Constructor for the SUB instruction class. */
	SUB(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "SUB"; };

	/**
	 * @brief Executes de SUB instruction. Subtract a given operand to the R0 value.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the MUL instruction. */
class MUL : public Instruction {
public:
	/** @brief Constructor for the MUL instruction class. */
	MUL(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "MUL"; };

	/**
	 * @brief Executes de MUL instruction. Multiply a given operand to the R0 value.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the DIV instruction. */
class DIV : public Instruction {
public:
	/** @brief Constructor for the DIV instruction class. */
	DIV(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "DIV"; };

	/**
	 * @brief Executes de DIV instruction. Divide a given operand to the R0 value.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the EXP instruction. */
class EXP : public Instruction {
public:
	/** @brief Constructor for the DIV instruction class. */
	EXP(const string& operand, const OperandType& type,  bool array_behaviour, unsigned index)
	  : Instruction(operand, type, array_behaviour, index) { name_ = "EXP"; };

	/**
	 * @brief Executes de EXP instruction. Calculate the value of R0 to a certain power.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the JUMP instruction. */
class JUMP : public Instruction {
public:
	/** @brief Constructor for the JUMP instruction class. */
	JUMP(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "JUMP"; };

	/**
	 * @brief Executes de JUMP instruction. Set program counter based on a given tag.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the JZERO instruction. */
class JZERO : public Instruction {
public:
	/** @brief Constructor for the JZERO instruction class. */
	JZERO(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "JZERO"; };

	/**
	 * @brief Executes de JZERO instruction. Set program counter based on a given tag if R0 == 0
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the JGTZ instruction. */
class JGTZ : public Instruction {
public:
	/** @brief Constructor for the JGTZ instruction class. */
	JGTZ(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "JGTZ"; };

	/**
	 * @brief Executes de JGTZ instruction. Set program counter based on a given tag if R0 > 0
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

/** @brief Class for the HALT instruction. */
class HALT : public Instruction {
public:
	/** @brief Constructor for the HALT instruction class. */
	HALT(const string& operand, const OperandType& type, bool array_behaviour, unsigned index)
		: Instruction(operand, type, array_behaviour, index) { name_ = "HALT"; };

	/**
	 * @brief Executes de HALT instruction. Stops the program execution.
	 * To know about the parameters @see Instruction::Execute(...)
	 */
	void Execute(unsigned& program_counter, vector<vector<int>>& data_memory, const vector<pair<string, unsigned>>& labels,
               const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) override;
};

#endif // INSTRUCTIONS_RAM_H
