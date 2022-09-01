/*
 *  Programa principal.
 *
 *
 *               Autores : Jorge Elías
 *               Cursos  : 2012-2021
 */

#include <string.h>

#include "grafo4.h"

void menu(unsigned dirigido, char &opcion)
// Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
{
  cout << "Optimizacion en Grafos, 2021-2022 Jorge Elías García" << endl;
  cout << "c. [c]argar grafo desde fichero" << endl;
  if (dirigido == 0)  // Grafo no dirigido
  {
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
    cout << "m. Mostrar el recorrido en a[m]plitud del grafo" << endl;
    cout << "P. Mostrar el recorrido en [P]rofundidad del grafo" << endl;
    cout << "k. Mostrar árbol generador de mínimo coste. Algoritmo de [k]ruskal" << endl;
    cout << "d. Mostrar el camino mínimo coste. Algoritmo de [d]ijkstra " << endl; 
    // Aquí se añaden más opciones al menú del grafo no dirigido
  } else {
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
    cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
    cout << "m. Mostrar el recorrido en a[m]plitud del grafo" << endl;
    cout << "P. Mostrar el recorrido en [P]rofundidad del grafo" << endl;
    cout << "k. Mostrar árbol generador de mínimo coste. Algoritmo de [k]ruskal" << endl;
    cout << "d. Mostrar el camino mínimo coste. Algoritmo de [d]ijkstra " << endl; 
    // Aquí se añaden más opciones al menú del grafo dirigido
  };
  cout << "q. Finalizar el programa" << endl;
  cout << "Introduce la letra de la accion a ejecutar  > ";
  cin >> opcion;
};

// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no
// dirigido, y un menú inicial si no hay un grafo cargado
int main(int argc, char *argv[]) {
  int error_apertura;
  char nombrefichero[85], opcion;
  // clrscr();
  // Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos
  // cargar, si no, lo pedimos desde teclado
  if (argc > 1) {
    cout << "Cargando datos desde el fichero dado como argumento" << endl;
    strcpy(nombrefichero, argv[1]);
  } else {
    cout << "Introduce el nombre completo del fichero de datos" << endl;
    cin >> nombrefichero;
  };
  GRAFO G(nombrefichero, error_apertura);
  if (error_apertura == 1) {
    cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
    exit(EXIT_SUCCESS);
    // pressanykey();
    // clrscr();
  } else {
    cout << "Grafo cargado desde el fichero " << nombrefichero << endl;
    // pressanykey();
    // clrscr();
    do {
      menu(G.Es_dirigido(), opcion);
      switch (opcion) {
        case 'c':
          // clrscr();
          cout << "Introduce el nombre completo del fichero de datos" << endl;
          cin >> nombrefichero;
          G.actualizar(nombrefichero, error_apertura);
          if (error_apertura == 1) {
            cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a "
                    "intentarlo"
                 << endl;
          } else {
            cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
          };
          cout << endl;
          // pressanykey();
          // clrscr();
          break;

        case 'i':
          // clrscr();
          cout << "Grafo cargado desde " << nombrefichero << endl;
          G.Info_Grafo();
          // pressanykey();
          // clrscr();
          break;

        case 's':
          cout << "Lista de sucesores del grafo: " << endl;
          G.Mostrar_Listas(1);
          break;

        case 'p':
          cout << "Lista de predecesores del grafo: " << endl;
          G.Mostrar_Listas(-1);
          // pressanykey();
          // clrscr();
          break;

        case 'a':
          cout << "Lista de adyacencia del grafo: " << endl;
          G.Mostrar_Listas(1);
          // pressanykey();
          // clrscr();
          break;

        case 'm':
          std::cout << "Recorrido en Amplitud. " << std::endl;
          G.RecorridoAmplitud();
          // pressanykey();
          // clrscr();
          break;

        case 'P':
          std::cout << "Recorrido en Profundidad. " << std::endl;
          G.RecorridoProfundidad();
          // pressanykey();
          // clrscr();
          break;

        case 'k':
          std::cout << "Árbol generador de mínimo coste. " << std::endl << std::endl; 
          G.Kruskal();
          break;

        case 'd': 
          std::cout << "Camino mínimo coste. Algoritmo de Dijkstra. " << std::endl; 
          G.Dijkstra(); 
          break; 

        case 'q':
          std::cout << "FIN" << std::endl;
          exit(EXIT_SUCCESS);
          break;

        default:
          break;
      }
    } while (opcion != 'q');
  }
  return 0;
}