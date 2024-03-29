/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 09 2024
 *
 * @brief Implementation of the RAM machine.
 */

#include "ram_machine.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief Executes the program stored in the RAMMachine's program memory.
 * @param debug Debug mode.
 * If 0 disables the debug mode
 * If 1 shows how many instructions were executed
 * If 2 also shows the instruction information and the current state of the data memory and tapes
 */
void RAMMachine::Execute(unsigned debug) {
  data_memory_.resize(10);
  input_tape_index_ = 0;
  program_counter_ = 0;
  stop_ = false;
  unsigned number_of_instructions = 0;

  if (debug == 2) {
    cout << "RAM initial state:\n";
    show_vector(data_memory_, "Data memory");
    show_vector(input_tape_, "Input tape");
    show_vector(output_tape_, "Output tape");
    cout << endl;
  }

  while (!stop_) {
    if (debug == 2) program_memory_[program_counter_]->ShowInformation();
    program_memory_[program_counter_]->Execute(program_counter_, data_memory_, labels_, input_tape_, output_tape_, input_tape_index_, stop_);
     
    if (!stop_ && debug == 2) {
      show_vector(data_memory_, "Data memory");      
      show_vector(input_tape_, "Input tape");
      cout << "Input tape index: " << input_tape_index_ << endl;
      show_vector(output_tape_, "Output tape");
      cout << "Output tape index: " << output_tape_.size() << endl << endl;
    }    
    ++ number_of_instructions;
  }
  if (debug == 1 || debug == 2) cout << "Number of executed instructions: " << number_of_instructions << endl << endl;
}

/**
 * @brief Loads a program from a file into the RAMMachine. This method reads instructions from the
 * specified file, parses them, and adds them to the program memory of the RAMMachine.
 * @param filename The name of the file containing the program.
 */
void RAMMachine::LoadProgramFromFile(const string& filename) {
  program_info_ = "";
  string program_no_labels = "";
  SearchLabels(filename);
  ifstream file(filename);

  if (file.is_open()) {
    string line;   
    unsigned line_index = 0;

    while (getline(file, line)) {      
      trim_leading_whitespace(line);
      if (line.empty() || line.size() == 0 || line[0] == '#') continue;    
      string::size_type label_end = line.find(':');
      if (label_end != string::npos) {
        string label = line.substr(0, label_end);
        program_info_ += label + ": ";        
        line = line.substr(label_end + 1);
        trim_leading_whitespace(line);
        // Omitir líneas que quedaron vacías después de la etiqueta
        if (line.empty() || line[0] == '#') continue;
      }
      GetInstructionFromTextLine(line);
      ++ line_index;
    }
    file.close();
  } else cerr << "No se pudo abrir el archivo." << endl;
  //cout << "PROGRAMA OBTENIDO:\n" << program_info_;
}

/**
 * @brief Parses a text line from the program file to extract an instruction.
 * @param line The text line to be parsed.
 */
void RAMMachine::GetInstructionFromTextLine(string& line) {
  istringstream iss(line);
  string instruction;
  string operand;
  if (iss >> instruction) {
    iss >> operand;
    OperandType operand_type = DIRECTO;
    if (operand.size() == 2) {      
      operand_type = get_operand_type(string{operand[0]});
      operand = operand[1];
    }
    else if (operand.size() > 2) {
      operand_type = ETIQUETA;
    }
    transform(instruction.begin(), instruction.end(), instruction.begin(), ::tolower);
    AddInstruction(instruction, operand, operand_type);    
    //program_info_ += instruction + " " + operand_type_to_string(operand_type) + " " + operand + "\n";
  } else {
    cerr << "Formato de instrucción inválido: <" << line << ">" << endl;
  }
}

/**
 * @brief Searches for labels in the program file and stores them.
 * @param filename The name of the program file.
 */
void RAMMachine::SearchLabels(const string& filename) {
  ifstream file(filename);
  if (file.is_open()) {
    string line;   
    unsigned line_index = 0; // Índice de línea actual    
    while (getline(file, line)) {
      trim_leading_whitespace(line); // Delete whitespaces
      if (line.empty() || line.size() == 0 || line[0] == '#') continue;
      string::size_type label_end = line.find(':'); // Verificar si la línea contiene una etiqueta
      if (label_end != string::npos) {
        string label = line.substr(0, label_end);
        labels_.push_back(make_pair(label, line_index));
        line = line.substr(label_end + 1); // Avanzar la posición de lectura después de la etiqueta
        trim_leading_whitespace(line);
        // Omitir líneas que quedaron vacías después de la etiqueta
        if (line.empty() || line[0] == '#') continue;
      }
      ++ line_index;
    } //file.close();
  } else cerr << "No se pudo abrir el archivo." << endl;
}

/**
 * @brief Adds a parsed instruction instruction to the program memory.
 * @param instruction The name of the instruction.
 * @param operand The operand of the instruction.
 * @param operand_type The type of the operand.
 */
void RAMMachine::AddInstruction(const string& instruction, const string& operand, const OperandType& operand_type) {
  int label_index = get_label_index(this->labels_, operand);
  if (instruction == "load") {
    this->program_memory_.push_back(new LOAD(operand, operand_type));
  }
  else if (instruction == "store") {
    this->program_memory_.push_back(new STORE(operand, operand_type));
  }
  else if (instruction == "add") {
    this->program_memory_.push_back(new ADD(operand, operand_type));
  }
  else if (instruction == "sub") {
    this->program_memory_.push_back(new SUB(operand, operand_type));
  }
  else if (instruction == "mul") {
    this->program_memory_.push_back(new MUL(operand, operand_type));
  }
  else if (instruction == "div") {
    this->program_memory_.push_back(new DIV(operand, operand_type));
  }
  else if (instruction == "exp") {
    this->program_memory_.push_back(new EXP(operand, operand_type));
  } 
  else if (instruction == "read") {
    this->program_memory_.push_back(new READ(operand, operand_type));
  }
  else if (instruction == "write") {
    this->program_memory_.push_back(new WRITE(operand, operand_type));
  }  
  else if (instruction == "halt") {
    this->program_memory_.push_back(new HALT("", operand_type));
  }
  else if (label_index != -1) {      
    if (instruction == "jump") {
      this->program_memory_.push_back(new JUMP(labels_[label_index].first, ETIQUETA));
    }
    else if (instruction == "jzero") {
      this->program_memory_.push_back(new JZERO(labels_[label_index].first, ETIQUETA));
    }
    else if (instruction == "jgtz") {
      this->program_memory_.push_back(new JGTZ(labels_[label_index].first, ETIQUETA));
    }    
  }
  else cerr << "Instruccion denegada: <" << instruction << ">" << "(index: " << label_index << ")\n";
}

/**
 * @brief Loads an input tape from a file into the RAMMachine. This method reads integers separated by commas from the
 * specified file and adds them to the input tape of the RAMMachine.
 * @param filename The name of the file containing the program.
 */
void RAMMachine::LoadInputTapeFromFile(const string& filename) {
  // Open the file
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error: Unable to open file " << filename << endl;
    return;
  }
  // Read integers separated by commas from the file
  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
      try {
        int value = stoi(token);
        input_tape_.push_back(value);
      } catch (const invalid_argument& e) {
        cerr << "Error: Invalid input format in file " << filename << endl;
        return;
      }
    }
  }
  file.close();
}

/**
 * @brief Writes the current state of the output tape on a file as integers separated by commas. 
 * @param filename The name/path of the output file.
 */
void RAMMachine::WriteOutputTapeOnFile(const string& filename) {
  // Open the file for writing
  ofstream output_file(filename, ios::out);
  if (!output_file.is_open()) {
    cerr << "Error: Unable to open file " << filename << " for writing." << endl;
    return;
  }
  // Write integers from output tape to file separated by commas
  for (unsigned i = 0; i < output_tape_.size(); ++i) {
    output_file << output_tape_[i];
    if (i < output_tape_.size() - 1) {
      output_file << ",";
    }
  }
  output_file.close();
}

/** @brief Displays information about the RAMMachine: stored program and tags. */
void RAMMachine::ShowInformation() {
  for (unsigned i = 0; i < program_memory_.size(); ++i) {
    cout << "[" << i << "] ";
    program_memory_[i]->ShowInformation();
  }
  cout << "ETIQUETAS:\n";
  for (unsigned i = 0; i < labels_.size(); ++i) cout << labels_[i].first + " index: " + to_string(labels_[i].second) + "\n";
}