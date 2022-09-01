/*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *  Autores : Jorge Elías García
 *  Cursos   : 2012-2021
 */

#include "grafo4.h"

void GRAFO ::destroy() {
  for (unsigned i = 0; i < n; i++) {
    LS[i].clear();
    //  A[i].clear();
    if (dirigido == 1) {
      LP[i].clear();
    };
  }
  LS.clear();
  LP.clear();
  // A.clear();
}

void GRAFO ::build(char nombrefichero[85], int &errorapertura) {
  ElementoLista dummy;
  ifstream textfile;
  textfile.open(nombrefichero);

  if (textfile.is_open()) {
    unsigned i, j, k;
    // leemos por conversion implicita el numero de nodos, arcos y el atributo
    // dirigido
    textfile >> (unsigned &)n >> (unsigned &)m >> (unsigned &)dirigido;
    // los nodos internamente se numeran desde 0 a n-1
    // creamos las n listas de sucesores
    LS.resize(n);
    LP.resize(n);
    errorapertura = 0;
    // leemos los m arcos
    for (k = 0; k < m; k++) {
      textfile >> (unsigned &)i >> (unsigned &)j >> (int &)dummy.c;
      // damos los valores a dummy.j y dummy.c
      dummy.j = j - 1;
      dummy.c = dummy.c;
      ElementoLista dummy_inverso{i - 1, dummy.c};
      // Diferenciamos si es dirigido o no. 0 si el grafo es no dirigido y 1 si
      // es dirigido
      if (dirigido == 0) {
        if (i == j) {
          LS[i - 1].push_back(dummy);
        } else {
          LS[i - 1].push_back(dummy);
          LS[dummy.j].push_back(dummy_inverso);
        }

      } else if (dirigido == 1) {
        LS[i - 1].push_back(dummy);
        LP[dummy.j].push_back(dummy_inverso);
      } else {
        errorapertura = 1;
      }
    }
  }

  if (!textfile) {
    errorapertura = 1;
  }
}

GRAFO::~GRAFO() { destroy(); }

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) { build(nombrefichero, errorapertura); }

void GRAFO::actualizar(char nombrefichero[85], int &errorapertura) {
  // Limpiamos la memoria dinamica asumida en la carga previa, como el
  // destructor
  destroy();
  // Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
  build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido() { return dirigido; }

void GRAFO::Info_Grafo() {
  std::cout << "Número de nodos: " << n << "  Número de arcos: " << m << "   Tipo:  ";
  if (Es_dirigido() == 0) {
    std::cout << "NO dirigido " << std::endl;
  } else {
    std::cout << "Dirigido " << std::endl;
  }
}

// Mostrará por pantalla la lista recibida, mostrando los sucesores, precesores
// o adyacentes y costes.
void Mostrar_Lista(vector<LA_nodo> L) {
  for (long unsigned int i{0}; i < L.size(); ++i) {
    if (L[i].size() == 0) {
      std::cout << i + 1 << " = Ø" << std::endl;
    } else {
      std::cout << i + 1 << " = {";
      for (long unsigned int j{0}; j < L[i].size(); ++j) {
        std::cout << " (" << L[i][j].j + 1 << "," << L[i][j].c << ") ";
      }
      std::cout << " }" << std::endl;
    }
  }
}

void GRAFO ::Mostrar_Listas(int l) {
  if (l == 0) {  // Mostramos lista de adyacencia
    for (long unsigned int i{0}; i < LS.size(); ++i) {
      if (LS[i].size() == 0) {
        std::cout << i + 1 << " = Ø" << std::endl;
      } else {
        std::cout << i + 1 << " = { ";
        for (long unsigned int j{0}; j < LS[i].size(); ++j) {
          if (j == LS[i].size() - 1) {
            std::cout << "(";
            std::cout << LS[i][j].j + 1 << "," << LS[i][j].c << ")";
          } else {
            std::cout << "(";
            std::cout << LS[i][j].j + 1 << "," << LS[i][j].c << ")"
                      << ", ";
          }
        }
        std::cout << " }" << std::endl;
      }
    }

  } else if (l == 1) {  // Mostrar lista de sucesores
    for (long unsigned int i{0}; i < LS.size(); ++i) {
      if (LS[i].size() == 0) {
        std::cout << i + 1 << " = Ø" << std::endl;
      } else {
        std::cout << i + 1 << " = { ";
        for (long unsigned int j{0}; j < LS[i].size(); ++j) {
          if (j == LS[i].size() - 1) {
            std::cout << "(";
            std::cout << LS[i][j].j + 1 << "," << LS[i][j].c << ")";
          } else {
            std::cout << "(";
            std::cout << LS[i][j].j + 1 << "," << LS[i][j].c << ")"
                      << ", ";
          }
        }
        std::cout << " }" << std::endl;
      }
    }

  } else if (l == -1) {  // MOstramos lista predecesores
    for (long unsigned int i{0}; i < LP.size(); ++i) {
      if (LP[i].size() == 0) {
        std::cout << i + 1 << " = Ø" << std::endl;
      } else {
        std::cout << i + 1 << " = { ";
        for (long unsigned int j{0}; j < LP[i].size(); ++j) {
          if (j == LP[i].size() - 1) {
            std::cout << "(";
            std::cout << LP[i][j].j + 1 << "," << LP[i][j].c << ")";
          } else {
            std::cout << "(";
            std::cout << LP[i][j].j + 1 << "," << LP[i][j].c << ") , ";
          }
        }
        std::cout << " }" << std::endl;
      }
    }
  } else {
    std::cerr << "Debe introducidr un valor de l = 0, 1 ó -1. " << std::endl;
  }
}

void GRAFO::Mostrar_Matriz()  // Muestra la matriz de adyacencia, tanto los nodos
                              // adyacentes como sus costes
{}

void GRAFO::dfs_num(unsigned i, vector<LA_nodo> L, vector<bool> &visitado, vector<unsigned> &prenum,
                    unsigned &prenum_ind, vector<unsigned> &postnum,
                    unsigned &postnum_ind)  // Recorrido en profundidad recursivo
                                            // con recorridos enum y postnum
{
  visitado[i] = true;
  prenum[prenum_ind++] = i;  // asignamos el orden de visita prenum que corresponde el nodo i
  for (unsigned j = 0; j < L[i].size(); j++)
    if (!visitado[L[i][j].j]) {
      dfs_num(L[i][j].j, L, visitado, prenum, prenum_ind, postnum, postnum_ind);
    };
  postnum[postnum_ind++] = i;  // asignamos el orden de visita posnum que corresponde al nodo i
}

void GRAFO::RecorridoProfundidad() {
  unsigned i;
  std::cout << "Introduzca nodo de partida: [1-" << n << "]" << endl;
  std::cin >> i;
  --i;
  vector<bool> visitado;
  visitado.resize(n, false);
  vector<unsigned> prenum;
  prenum.resize(n, -1);
  unsigned prenum_ind{0};
  vector<unsigned> postum;
  postum.resize(n, -1);
  unsigned postum_ind{0};
  dfs_num(i, LS, visitado, prenum, prenum_ind, postum, postum_ind);
  std::cout << "Orden de visita de los nodos en preorden" << endl;
  for (int i{0}; i < prenum.size(); ++i) {
    // en caso de encontrarnos un -1 son los elementos que rellenó por defecto,
    // por lo que ya no hay más elementos significativos en la lista por lo que
    // salimos del bucle.
    if (prenum[i] == -1) {
      std::cout << "Lisa de preorden finalizada. " << std::endl;
      break;
    }
    if (i == prenum.size() - 1) {
      std::cout << "[" << prenum[i] + 1 << "]" << endl;
    } else {
      std::cout << "[" << prenum[i] + 1 << "] --> ";
    }
  }

  std::cout << "Orden de visita de los nodos en postorden" << endl;
  for (int i{0}; i < postum.size(); ++i) {
    if (postum[i] == -1) {
      std::cout << "lista de postorden finalizada." << endl;
      break;
    }
    if (i == postum.size() - 1) {
      std::cout << "[" << postum[i] + 1 << "]" << endl;
    } else {
      std::cout << "[" << postum[i] + 1 << "] --> ";
    }
  }
}

void GRAFO::bfs_num(unsigned i,         // nodo desde el que realizamos el recorrido en amplitud
                    vector<LA_nodo> L,  // lista que recorremos, LS o LP; por defecto LS
                    vector<unsigned> &pred,  // vector de predecesores en el recorrido
                    vector<unsigned> &d)     // vector de distancias a nodo i+1
// Recorrido en amplitud con la construcci�n de pred y d: usamos la cola
{
  vector<bool> visitado;  // creamos e iniciamos el vector visitado
  visitado.resize(n, false);
  visitado[i] = true;

  pred.resize(n,
              -1);  // creamos e inicializamos pred y d. Inicializo todos los
                    // predecesores a -1, para poder distinguir aquellos que tienen por
                    // predecesor el 1, ya que se presenta con un 0, de aquellos que no
                    // tienen predecesor en el recorrido por lo que se mantendrán en -1.
  d.resize(n, 0);
  pred[i] = i;
  d[i] = 0;

  queue<unsigned> cola;  // creamos e inicializamos la cola
  cola.push(i);          // iniciamos el recorrido desde el nodo i+1

  while (!cola.empty())  // al menos entra una vez al visitar el nodo i+1 y
                         // contin�a hasta que la cola se vac�e
  {
    unsigned k = cola.front();  // cogemos el nodo k+1 de la cola
    cola.pop();                 // lo sacamos de la cola
    // Hacemos el recorrido sobre L desde el nodo k+1
    for (unsigned j = 0; j < L[k].size(); j++)
    // Recorremos todos los nodos u adyacentes al nodo k+1
    // Si el nodo u no est� visitado
    {
      int nodo_actual = L[k][j].j;
      if (visitado[nodo_actual] == false) {
        visitado[nodo_actual] = true;
        cola.push(nodo_actual);
        pred[nodo_actual] = k;
        d[nodo_actual] = d[k] + 1;
      }
    };
    // Hemos terminado pues la cola est� vac�a
  };
}

// Construye un recorrido en amplitud desde un nodo inicial
void GRAFO::RecorridoAmplitud() {
  unsigned i;
  std::cout << "Elija el nodo de partida [1-" << n << "]" << endl;
  std::cin >> i;
  --i;
  vector<unsigned> pred;  // vector de predecesores en el recorrido
  pred.resize(n, -1);
  vector<unsigned> d;
  d.resize(n, 0);
  bfs_num(i, LS, pred, d);
  std::cout << "Lista de predecesores: [nodo]predecesor; " << std::endl;
  for (int j{0}; j < pred.size(); ++j) {
    if (pred[j] == -1) {
      // Si el predecesor es -1, significa que no modificó su valor en el bfs,
      // por lo que no tiene predecesor.
      std::cout << "[" << j + 1 << "] NO PRED; ";
    } else {
      std::cout << "[" << j + 1 << "]" << pred[j] + 1 << "; ";
    }
  }
  std::cout << endl << "Lista de distancias:[nodo]Distancia;  " << std::endl;
  for (int i{0}; i < d.size(); ++i) {
    std::cout << "[" << i + 1 << "]" << d[i] << "; ";
  }
  std::cout << endl;
}

// Ordenamos UN elemento de la lista
void GRAFO::OrdenarListaKruskall(vector<AristaPesada> &Aristas, unsigned contador) {
  int valor_menor = Aristas[contador].peso;  // Inicalizamos el valor menor en la primera posición.
  unsigned posicion_a_intercambiar{contador};  // Nos indicará en que posición encontramos la arista
                                               // con menor peso.

  for (unsigned i{contador}; i < Aristas.size(); ++i) {
    if (Aristas[i].peso < valor_menor) {
      valor_menor = Aristas[i].peso;
      posicion_a_intercambiar = i;
    }
  }
  AristaPesada menor_peso = Aristas[posicion_a_intercambiar];
  AristaPesada aux = Aristas[contador];
  Aristas[contador] = menor_peso;
  Aristas[posicion_a_intercambiar] = aux;
}

// Método de Kruskall
void GRAFO::Kruskal() {
  vector<AristaPesada> Aristas;
  Aristas.resize(m);
  unsigned k = 0;
  // Creamos el vector de Aristas
  for (unsigned i = 0; i < n; i++) {
    for (unsigned j = 0; j < LS[i].size(); j++) {
      if (i < LS[i][j].j) {
        Aristas[k].extremo1 = i;
        Aristas[k].extremo2 = LS[i][j].j;
        Aristas[k++].peso = LS[i][j].c;
      }
    }
  }
  // Inicializamos el vector de componentes conexas
  vector<unsigned> Raiz;
  Raiz.resize(n);
  for (unsigned q = 0; q < n; q++) {
    Raiz[q] = q;
  };

  int coste{0};
  unsigned contador{0};
  int numero_aristas_introducidas{0};
  // Haremos tantas iteraciones como n - 1.
  for (unsigned i{0}; i < n - 1; ++i) {
    OrdenarListaKruskall(Aristas, contador);
    ++contador;
    for (int j{0}; j < Aristas.size(); ++j) {
      if (Raiz[Aristas[j].extremo1] != Raiz[Aristas[j].extremo2]) {
        int raiz_a_cambiar = Raiz[Aristas[j].extremo2];
        // Ponemos todos en la misma componente conexa
        for (int k{0}; k < Raiz.size(); ++k) {
          if (Raiz[k] == raiz_a_cambiar) {
            Raiz[k] = Raiz[Aristas[j].extremo1];
          }
        }
        coste += Aristas[j].peso;
        // Una vez encontrado la arista pertinente y habiéndola incorporada, la mostramos volvemos a
        // ordenar otra arista. Cabe destacar que J me indica la arista definitivamente escogida.
        std::cout << "Arista número " << i + 1 << " incorporada (" << Aristas[j].extremo1 + 1 << ","
                  << Aristas[j].extremo2 + 1 << ") con peso: " << Aristas[j].peso << endl
                  << endl;
        ++numero_aristas_introducidas;
        break;
      } else {
        OrdenarListaKruskall(Aristas, contador);
        ++contador;
      }
    }
  }
  std::cout << "El peso del arbol generador de mínimo coste es " << coste << endl << endl;
  if (numero_aristas_introducidas != n - 1) {
    std::cout << "GRAFO NO CONEXO, ÁRBOL NO CORRECTO" << endl;
  }
}

void MostrarCamino(unsigned s, unsigned i, vector<unsigned> pred) {
  if (i != s) {
    MostrarCamino(s, pred[i], pred);
    cout << pred[i] + 1 << " - ";
  }
}

// Aloritmo de Dijkstra
void GRAFO::Dijkstra() {
  vector<bool> PermanentementeEtiquetado;
  vector<int> d;
  vector<unsigned> pred;
  int min;
  unsigned s, candidato{0};
  // Inicialmente no hay ningun nodo permanentemente etiquetado
  PermanentementeEtiquetado.resize(n, false);
  // Inicialmente todas las etiquetas distancias son infinito
  d.resize(n, maxint);
  // Inicialmente el pred es null
  pred.resize(n, UERROR);
  // Solicitamos al usuario nodo origen
  cout << endl;
  cout << "Caminos minimos: Dijkstra" << endl;
  cout << "Nodo de partida? [1-" << n << "]: ";
  cin >> (unsigned &)s;
  // La etiqueta distancia del nodo origen es 0, y es su propio pred
  d[--s] = 0;
  pred[s] = s;

  // Creamos estas variables para la condición de parada del bucle.
  unsigned nodos_permanentemenete_etiquetados{1};
  bool salir{false};

  do {
    // Inicializamos min al valor maxint, para poder comparar los valores.
    min = maxint;
    for (int i{0}; i < d.size(); ++i) {
      if (d[i] < min && PermanentementeEtiquetado[i] == false) {
        min = d[i];
        candidato = i;
      }
    }
    // Hemos encontrado el mínimo elemento
    if (min == maxint) {
      salir = true;
    } else {
      ++nodos_permanentemenete_etiquetados;
      PermanentementeEtiquetado[candidato] = true;
      // Buscamos atajaos.
      for (int i{0}; i < LS[candidato].size(); ++i) {
        // No nos aseguramos de que además no esté permanentemente etiquetado ya que en Dijkstra eso
        // nunca va a ocurrir. (no contempla costes negativos)
        if (d[LS[candidato][i].j] > d[candidato] + LS[candidato][i].c) {
          d[LS[candidato][i].j] = d[candidato] + LS[candidato][i].c;
          pred[LS[candidato][i].j] = candidato;
        }
      }
    }
    //  std::cout << nodos_permanentemenete_etiquetados;
  } while (nodos_permanentemenete_etiquetados < n && salir != true);  // condición de parada;

  cout << "Soluciones:" << endl;
  for (int i{0}; i < d.size(); ++i) {
    if (d[i] != maxint && s != i) {
      std::cout << "Camino mínimo de " << s + 1 << " a " << i + 1 << ":  ";
      MostrarCamino(s, i, pred);
      std::cout << i + 1 << " de longitud " << d[i] << std::endl;
    } else if (i != s) {
      std::cout << "No hay caminos mínimos desde el " << s + 1 << " hasta " << i + 1 << std::endl;
    }
  }
}