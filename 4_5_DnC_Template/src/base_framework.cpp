/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Diseño y Análisis de Algoritmos
 *
 * @author Roberto Carrazana Pernia
 * @date: Feb 25 2024
 *
 * @brief 'Divide and Conquer' Framework class implementation.
 * 
 */
#include "base_framework.h"

/**
 * @brief Divide and Conquer method.
 * Solves a problem and store the result on a given solution pointer.
 * @param problem - problem to solve
 * @param solution - solution pointer to store the solution
 */
template <typename T>
void DnCFramework<T>::Solve(Problem<T>* problem, Solution<T>* solution, unsigned current_depth) {
	//cout << "Current depth: " << current_depth; cout << " _ Recursion call: " << recursive_calls_ << endl;
	recursive_calls_ += 1;
	
	if (problem->Small()){
		problem->SolveSmall(solution);
		if (current_depth > maximum_depth_) maximum_depth_ = current_depth;
	}
	else{		
		// Modificacion
		//recursive_calls_ += 1;	

		pair<Problem<T>*, Problem<T>*> sub_problems;
		pair<Solution<T>*, Solution<T>*> sub_solutions;
		sub_problems = problem->Divide();
		sub_solutions.first = solution->GetInstance();
		sub_solutions.second = solution->GetInstance();
		Solve(sub_problems.first, sub_solutions.first, current_depth + 1);
		Solve(sub_problems.second, sub_solutions.second, current_depth + 1);
		solution->Combine(sub_solutions);
	}
};

template <typename T>
void DnCFramework<T>::SetAlgorithm(Solution<T>* solution) {
	algorithm_ = solution;
}

template <typename T>
string DnCFramework<T>::GetRecurrence() {
	return algorithm_->GetRecurrence();
}

template <typename T>
void DnCFramework<T>::ResetRecursiveCalls() {
	recursive_calls_ = 0;
}

template <typename T>
void DnCFramework<T>::ResetMaximumDepth() {
	maximum_depth_ = 0;
}


