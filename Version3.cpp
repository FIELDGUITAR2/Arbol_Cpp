#include <algorithm>   // para std::max y std::min
#include <vector>
#include <limits>

// Nodo del árbol: tu compañero es quien arma la estructura real,
// esto es solo lo que la función necesita de cada nodo.
struct Nodo {
    int valor;                 // valor heurístico (solo se usa si es hoja)
    std::vector<Nodo*> hijos;  // hijos del nodo (vacío si es hoja)
    bool esTerminal;           // true si es hoja (fin del juego o profundidad máxima)
};

int minimax(Nodo* nodo, int profundidad, bool esMaximizador, int alfa, int beta) {
    // Caso base: llegamos a una hoja
    if (nodo->esTerminal) {
        return nodo->valor;
    }

    if (esMaximizador) {
        int mejor = std::numeric_limits<int>::min();
        for (Nodo* hijo : nodo->hijos) {
            int valor = minimax(hijo, profundidad + 1, false, alfa, beta);
            mejor = std::max(mejor, valor);
            alfa = std::max(alfa, mejor);
            if (beta <= alfa) {
                break; // poda: el minimizador no va a dejar llegar hasta aquí
            }
        }
        return mejor;
    } else {
        int mejor = std::numeric_limits<int>::max();
        for (Nodo* hijo : nodo->hijos) {
            int valor = minimax(hijo, profundidad + 1, true, alfa, beta);
            mejor = std::min(mejor, valor);
            beta = std::min(beta, mejor);
            if (beta <= alfa) {
                break; // poda: el maximizador no va a dejar llegar hasta aquí
            }
        }
        return mejor;
    }
}

// Ejemplo de uso una vez que el árbol ya esté armado:
// int resultado = minimax(raiz, 0, true,
//                          std::numeric_limits<int>::min(),
//                          std::numeric_limits<int>::max());