#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Nodo del arbol de juego
struct Nodo {
    vector<Nodo*> hijos;
    int valor;
    bool esHoja;
};

Nodo* crearNodo() {
    Nodo* n = new Nodo();
    n->valor = 0;
    n->esHoja = false;
    return n;
}

// contador de hojas ya leidas, para saber cual valor toca pedir
int contadorHojas = 0;

// funcion que lee un numero de forma segura (si el usuario escribe
// algo raro, no se queda pegado pidiendo infinito, sino que avisa y reintenta)
int leerNumero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();                 // limpia el error
            cin.ignore(1000, '\n');      // bota lo que quedo mal escrito
            cout << "   Eso no es un numero valido, intenta otra vez.\n";
        } else {
            return valor;
        }
    }
}

// Arma el arbol completo de una vez, usando siempre el mismo numero
// de hijos por nodo (factor de ramificacion) hasta llegar a la profundidad pedida.
// Cuando llega a profundidad 0, ese nodo es hoja y ahi se pide su valor.
Nodo* construirArbol(int profundidad, int ramificacion) {
    Nodo* actual = crearNodo();

    if (profundidad == 0) {
        actual->esHoja = true;
        contadorHojas++;
        actual->valor = leerNumero("Valor de la hoja #" + to_string(contadorHojas) + ": ");
        return actual;
    }

    for (int i = 0; i < ramificacion; i++) {
        Nodo* hijo = construirArbol(profundidad - 1, ramificacion);
        actual->hijos.push_back(hijo);
    }

    return actual;
}

int podas = 0; // cuantas veces se corto una rama

// esMax = true -> en este nivel se busca el valor mas alto (maximizador)
// esMax = false -> en este nivel se busca el valor mas bajo (minimizador)
int minimaxAlfaBeta(Nodo* nodo, int alfa, int beta, bool esMax) {

    if (nodo->esHoja) {
        return nodo->valor;
    }

    if (esMax) {
        int mejor = INT_MIN;
        for (int i = 0; i < (int)nodo->hijos.size(); i++) {
            int val = minimaxAlfaBeta(nodo->hijos[i], alfa, beta, false);
            if (val > mejor) mejor = val;
            if (mejor > alfa) alfa = mejor;

            // poda: ya no hace falta revisar los demas hermanos
            if (beta <= alfa) {
                podas++;
                break;
            }
        }
        return mejor;
    } else {
        int mejor = INT_MAX;
        for (int i = 0; i < (int)nodo->hijos.size(); i++) {
            int val = minimaxAlfaBeta(nodo->hijos[i], alfa, beta, true);
            if (val < mejor) mejor = val;
            if (mejor < beta) beta = mejor;

            if (beta <= alfa) {
                podas++;
                break;
            }
        }
        return mejor;
    }
}

int main() {
    cout << "====================================" << endl;
    cout << "  MINIMAX CON PODA ALFA-BETA" << endl;
    cout << "====================================" << endl;

    cout << "\nPrimero dime como es la forma del arbol.\n";
    int profundidad = leerNumero("Cuantos niveles de profundidad tiene el arbol (sin contar la raiz)? ");
    int ramificacion = leerNumero("Cuantos hijos tiene cada nodo (igual para todos)? ");

    int totalHojas = 1;
    for (int i = 0; i < profundidad; i++) totalHojas *= ramificacion;
    cout << "\nEn total vas a meter " << totalHojas << " valores (uno por cada hoja), en orden de izquierda a derecha.\n\n";

    Nodo* raiz = construirArbol(profundidad, ramificacion);

    cout << "\nQuien empieza jugando en la raiz?" << endl;
    cout << "1. Maximizador (quiere el valor mas alto)" << endl;
    cout << "2. Minimizador (quiere el valor mas bajo)" << endl;
    int opcion = leerNumero("Elija 1 o 2: ");

    bool empiezaMax = (opcion == 1);

    int resultado = minimaxAlfaBeta(raiz, INT_MIN, INT_MAX, empiezaMax);

    cout << "\n====================================" << endl;
    cout << "El valor optimo que se obtiene es: " << resultado << endl;
    cout << "Cantidad de veces que se poda una rama: " << podas << endl;
    cout << "====================================" << endl;

    return 0;
}