### Práctica 7: PMSP. Algoritmos aproximados

#### Entrega 09/04/2024
Nada que reseñar.

##### Clase Solución:
* General: Incluir las operaciones que se realizan en la misma (insertar, swap, calcularTCT) para simplificar su manipulación y mejorar la legibilidad de los bucles de los algoritmos. **[Hecho]**
* TCT: Muchas veces el ćalculo o actualización del TCT incluye cálculos innecesarios. Por ello, se incluirá un atributo total_TCT y el TCT de cada máquina. **[Hecho]** Se actualizará el valor de cada máquina cada vez que se realice un movimiento en ella.

##### Porcentajes de mejora:
* GRASP: Para cada iteración, almacenar el porcentaje de mejora de la solución con respecto a su mejora (LocalSearch). **[No hecho]** Las búsquedas locales no presentan mejoras.




#### Entrega 02/04/2024
Suspenso debido mayormente a un insuficiente entendimiento del algoritmo voraz.

##### Estructura de clases:
* Clase Problema: contiene los atributos que tiene la clase PMSP y el CreateFromFile.
* Clase Solucion: básicamente una clase con el **vector<vector<Task*>>**
* Clase Algoritmo: mi misma clase PMSP pero eliminando lo que debo mover a Problema.

##### GRASP:
* En la creación de candidatos, debo restringirlo para que escoja los N mejores. Siendo N un número predefinido por mi.

##### Greedy:
* Entenderlo mejor para poder explicarlo decentemente.

##### Otros:
* El cálculo del TCT creo que está mal.