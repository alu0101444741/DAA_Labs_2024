### Práctica 8: . Algoritmos aproximados

#### Entrega 16/04/2024
Cálculo erróneo del TCT. No se multiplicaba por k (en este caso, tamaño de la máquina menos el índice de tarea actual)
```cpp
// Antes
    machine_completion_time += ((machine_size - j) * (setup_time + solution_[machine_index][j]->time_));
// Ahora
    machine_completion_time += (setup_time + solution_[machine_index][j]->time_);
```
De igual manera los cálculos siguen siendo incorrectos. Debo buscar donde está la causa.

#### Entrega 09/04/2024
Nada que reseñar.

##### Clase Solución:
* General: Incluir las operaciones que se realizan en la misma (insertar, swap, calcularTCT) para simplificar su manipulación y mejorar la legibilidad de los bucles de los algoritmos. **[Hecho]**
* TCT: Muchas veces el ćalculo o actualización del TCT incluye cálculos innecesarios. Por ello, se incluirá un atributo total_TCT y el TCT de cada máquina. **[Hecho]** Se actualizará el valor de cada máquina cada vez que se realice un movimiento en ella.

##### Porcentajes de mejora:
* GRASP: Para cada iteración, almacenar el porcentaje de mejora de la solución con respecto a su mejora (LocalSearch). **[Hecho]** Adicionalmente, hay código comentado para ejecutar todas las búsquedas locales en el mismo GRASP y guardar la mejora de todas ellas.