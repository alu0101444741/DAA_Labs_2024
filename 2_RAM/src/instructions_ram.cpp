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

#include "instructions_ram.h"

/**
 * @brief Executes de LOAD instruction. Store in R0 a value based on the operand.
 * To know about the parameters @see Instruction::Execute(...)
 */
void LOAD::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (type_ == INMEDIATO) data_memory[0] = operand_value;
  else if (type_ == INDIRECTO) data_memory[0] = data_memory[data_memory[operand_value]];
  else data_memory[0] = data_memory[operand_value];

  program_counter ++;
}

/**
 * @brief Executes de STORE instruction. Store the R0 value on memory based on the operand.
 * To know about the parameters @see Instruction::Execute(...)
 */
void STORE::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (type_ == DIRECTO) data_memory[operand_value] = data_memory[0];
  else if (type_ == INDIRECTO) data_memory[data_memory[operand_value]] = data_memory[0];
  else {
    cerr << "ERROR: Instrucción STORE con operando de tipo INMEDIATO línea " << program_counter << endl;
    stop = true;
  }
  program_counter ++;
}

/**
 * @brief Executes de READ instruction. Reads a value from the input tape and store it on memory based on the operand.
 * To know about the parameters @see Instruction::Execute(...)
 */
void READ::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (operand_value == 0) {
    cerr << "ERROR: Instrucción READ 0 línea " << program_counter << endl;
    stop = true;
  }
	if (type_ == DIRECTO) data_memory[operand_value] = input_tape[input_tape_index];
  else if (type_ == INDIRECTO) data_memory[data_memory[operand_value]] = input_tape[input_tape_index];
  else {
    cerr << "ERROR: Instrucción READ con operando de tipo INMEDIATO línea " << program_counter << endl;
    stop = true;
  }
  program_counter ++;
  input_tape_index ++; cout << "(!) Input index: " << input_tape_index << endl;
}

/**
 * @brief Executes de WRITE instruction. Writes the value given by the operand on the output tape.
 * To know about the parameters @see Instruction::Execute(...)
 */
void WRITE::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                    const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (operand_value == 0) {
    cerr << "ERROR: Instrucción WRITE 0 línea " << program_counter << endl;
    stop = true;
  }
  if (type_ == DIRECTO) output_tape.push_back(data_memory[operand_value]);
  else if (type_ == INDIRECTO) output_tape.push_back(data_memory[data_memory[operand_value]]);
  else output_tape.push_back(operand_value);
  program_counter ++;
}

/**
 * @brief Executes de ADD instruction. Add a given operand to the R0 value.
 * To know about the parameters @see Instruction::Execute(...)
 */
void ADD::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (type_ == INMEDIATO) data_memory[0] += operand_value;
  else if (type_ == INDIRECTO) data_memory[0] += data_memory[data_memory[operand_value]];
  else data_memory[0] += data_memory[operand_value];

  program_counter ++;
}

/**
 * @brief Executes de SUB instruction. Subtract a given operand to the R0 value.
 * To know about the parameters @see Instruction::Execute(...)
 */
void SUB::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (type_ == INMEDIATO) data_memory[0] -= operand_value;
  else if (type_ == INDIRECTO) data_memory[0] -= data_memory[data_memory[operand_value]];
  else data_memory[0] -= data_memory[operand_value];

  program_counter ++;
}

/**
 * @brief Executes de MUL instruction. Multiply a given operand to the R0 value.
 * To know about the parameters @see Instruction::Execute(...)
 */
void MUL::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (type_ == INMEDIATO) data_memory[0] *= operand_value;
  else if (type_ == INDIRECTO) data_memory[0] *= data_memory[data_memory[operand_value]];
  else data_memory[0] *= data_memory[operand_value];

  program_counter ++;
}

/**
 * @brief Executes de DIV instruction. Divide a given operand to the R0 value.
 * To know about the parameters @see Instruction::Execute(...)
 */
void DIV::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  int operand_value = stoi(operand_);
  if (type_ == INMEDIATO) data_memory[0] /= operand_value;
  else if (type_ == INDIRECTO) data_memory[0] /= data_memory[data_memory[operand_value]];
  else data_memory[0] /= data_memory[operand_value];

  program_counter ++;
}

/**
 * @brief Executes de JUMP instruction. Set program counter based on a given tag.
 * To know about the parameters @see Instruction::Execute(...)
 */
void JUMP::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  for (unsigned i = 0; i < labels.size(); ++i) {
    if (labels[i].first == operand_) {
      program_counter = labels[i].second; cout << "<--- Saltando a " <<  labels[i].second << endl;
      break;
    }
  }
}

/**
 * @brief Executes de JZERO instruction. Set program counter based on a given tag if R0 == 0
 * To know about the parameters @see Instruction::Execute(...)
 */
void JZERO::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                    const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  if (data_memory[0] == 0) {
    for (unsigned i = 0; i < labels.size(); ++i) {
      if (labels[i].first == operand_) {
        program_counter = labels[i].second; cout << "<--- Saltando a " <<  labels[i].second << endl;
        break;
      }
    }
  }
  else program_counter ++;
}

/**
 * @brief Executes de JGTZ instruction. Set program counter based on a given tag if R0 > 0
 * To know about the parameters @see Instruction::Execute(...)
 */
void JGTZ::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  if (data_memory[0] > 0) {
    for (unsigned i = 0; i < labels.size(); ++i) {
      if (labels[i].first == operand_) {
        program_counter = labels[i].second;
        break;
      }
    }
  }
  else program_counter ++;
}

/**
 * @brief Executes de HALT instruction. Stops the program execution.
 * To know about the parameters @see Instruction::Execute(...)
 */
void HALT::Execute(unsigned& program_counter, vector<int>& data_memory, const vector<pair<string, unsigned>>& labels,
                   const vector<int>& input_tape, vector<int>& output_tape, unsigned& input_tape_index, bool& stop) {
  stop = true;
}

