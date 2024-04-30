/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 29 2024
 *
 * @brief Swap movement.
 * 
 */

#ifndef SWAP_MOVEMENT_H_
#define SWAP_MOVEMENT_H_

#include "solution.h"



/** @brief Represents a movement to swap tasks between machines in a solution. */
class SwapMovement {
private:
  pair<unsigned, unsigned> indexes_;
  float value_;
public:
  static const SwapMovement kNullSwapMovement;
  /**
   * @brief Constructs a SwapMovement object.
   * @param first_index
   * @param second_index
   */
  SwapMovement(unsigned first_index, unsigned second_index, float value)
  : indexes_(pair<unsigned, unsigned>(first_index, second_index)), value_(value) {}

  /**
   * @brief Checks if two SwapMovement objects are equal.
   * @param other The other SwapMovement object to compare with.
   * @return True if the two SwapMovement objects are equal, false otherwise.
   */
  bool operator == (const SwapMovement& other) const;

  /**
   * @brief Get the assigned value for the movement
   * @return value assigned
   */
  float GetValue() const { return value_; }

  /**
   * @brief Set a new assigned value
   * @param new_value New value assigned
   */
  void SetValue(float new_value) { value_ = new_value; }

  /**
   * @brief Get the stored indexes of the movement
   * @return pair of indexes
   */
  pair<unsigned, unsigned> GetIndexes () const { return indexes_; }

  /**
   * @brief Gets a string representation of the swap movement.
   * @return A string representing the swap movement.
   */
  string GetInfo() const;
};

#endif // SWAP_MOVEMENT_H_ 