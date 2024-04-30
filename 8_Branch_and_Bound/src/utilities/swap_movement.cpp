/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Apr 29 2024
 *
 * @brief Swap movement class implementation.
 * 
 */

#include "../../include/utilities/swap_movement.h"

const SwapMovement SwapMovement::kNullSwapMovement(0, 0, -INT_MAX);

/**
 * @brief Checks if two SwapMovement objects are equal.
 * @param other The other SwapMovement object to compare with.
 * @return True if the two SwapMovement objects are equal, false otherwise.
 */
bool SwapMovement::operator == (const SwapMovement& other) const {
  return  ((indexes_.first == other.indexes_.first) && (indexes_.second == other.indexes_.second)) ||
          ((indexes_.first == other.indexes_.second) && (indexes_.second == other.indexes_.first));
}

/**
 * @brief Gets a string representation of the swap movement.
 * @return A string representing the swap movement.
 */
string SwapMovement::GetInfo() const {
  return "From [" + to_string(indexes_.first) + "] to [" + to_string(indexes_.second) + "]";
}