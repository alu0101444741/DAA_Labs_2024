/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief Functions to test the Template Framework. (Definition)
 */

#ifndef TEST_FRAMEWORK_H_
#define TEST_FRAMEWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include "base_framework.h"
#include "mergesort_problem.h"
#include "quicksort_problem.h"

const string kTableDelimiter = "--------------";
const int kMaximumVectorValue = 100;

/**
* @brief Execute Mergesort and Quicksort algorithms on a given amount of arrays.
* These arrays will be sized from 2 to a given size and will contain integer numbers only.
* @param test_amount - how many arrays will be sorted
* @param minimum_size - minimum vector size to test
* @param maximum_size - maximum vector size to test
*/
void sort_tests(unsigned test_amount, unsigned minimum_size, unsigned maximum_size);

/**
 * @brief Time measure of an algorithm using the provided framework, solution, and problem.
 * @param name - Name of the algorithm being tested.
 * @param framework - Pointer to the Divide and Conquer framework.
 * @param solution - Pointer to the solution object.
 * @param problem - Pointer to the problem object.
 */
void test_algorithm(const string& name, DnCFramework* framework, Solution* solution, Problem* problem);



#endif /* TEST_FRAMEWORK_H_*/