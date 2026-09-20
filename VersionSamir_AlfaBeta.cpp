#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <climits>
#include <algorithm>

using namespace std;

struct Nodo{
    int dato;
    Nodo *der;
    Nodo *izq;
};

//Prototipos de funciones
void menu();
Nodo *crearNodo(int);
Nodo *construirArbol(int nivelActual, int profundidad);
int minimax(Nodo *nodo, int nivel, bool esMaximizador);
int alfabeta(Nodo *nodo, int nivel, int alfa, int beta, bool esMaximizador);
void liberarArbol(Nodo *&);

Nodo *arbol = NULL;
int profundidadArbol = 0;

int main()
{
    menu();
    getch();
    return 0;
}

//Funcion de menu
void menu(){
    int opcion;
    do{
        cout<<"\n\t.:MENU MINIMAX / ALFA-BETA:."<<endl;
        cout<<"1. Construir arbol de juego (ingresar valores de las hojas)"<<endl;
        cout<<"2. Ejecutar Minimax (sin poda)"<<endl;
        cout<<"3. Ejecutar Minimax con poda Alfa-Beta"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Elige una opcion: ";
        cin>>opcion;
        switch(opcion){
            case 1:{
                if(arbol != NULL){
                    liberarArbol(arbol);
                }
                cout<<"Ingresa la profundidad del arbol (numero de niveles, ej. 3): ";
                cin>>profundidadArbol;
                if(profundidadArbol < 1){
                    cout<<"La profundidad debe ser al menos 1."<<endl;
                    break;
                }
                cout<<"Se construira un arbol binario completo. Ingresa el valor de evaluacion de cada hoja:"<<endl;
                arbol = construirArbol(0, profundidadArbol);
                cout<<"Arbol construido correctamente."<<endl;
                break;
            }
            case 2:{
                if(arbol == NULL){
                    cout<<"Primero debes construir el arbol (opcion 1)."<<endl;
                    break;
                }
                int resultado = minimax(arbol, 0, true);
                cout<<"Valor optimo (Minimax): "<<resultado<<endl;
                break;
            }
            case 3:{
                if(arbol == NULL){
                    cout<<"Primero debes construir el arbol (opcion 1)."<<endl;
                    break;
                }
                int resultado = alfabeta(arbol, 0, INT_MIN, INT_MAX, true);
                cout<<"Valor optimo (Alfa-Beta): "<<resultado<<endl;
                break;
            }
        }
    }while(opcion != 4);
}

Nodo *crearNodo(int n){
    Nodo *nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    return nuevoNodo;
}

//Construye un arbol binario completo. En las hojas (nivelActual == profundidad)
//se pide el valor de evaluacion; los nodos internos calculan su valor despues,
//dentro de minimax/alfabeta.
Nodo *construirArbol(int nivelActual, int profundidad){
    Nodo *nodo = crearNodo(0);
    if(nivelActual == profundidad){
        cout<<"  Valor hoja (nivel "<<nivelActual<<"): ";
        cin>>nodo->dato;
    }else{
        nodo->izq = construirArbol(nivelActual + 1, profundidad);
        nodo->der = construirArbol(nivelActual + 1, profundidad);
    }
    return nodo;
}

//Minimax puro (sin poda): recorre todo el arbol.
//esMaximizador alterna en cada nivel: true = jugador MAX, false = jugador MIN.
int minimax(Nodo *nodo, int nivel, bool esMaximizador){
    if(nodo->izq == NULL && nodo->der == NULL){
        return nodo->dato; //Nodo hoja: valor terminal
    }

    if(esMaximizador){
        int valIzq = minimax(nodo->izq, nivel + 1, false);
        int valDer = minimax(nodo->der, nivel + 1, false);
        nodo->dato = max(valIzq, valDer);
    }else{
        int valIzq = minimax(nodo->izq, nivel + 1, true);
        int valDer = minimax(nodo->der, nivel + 1, true);
        nodo->dato = min(valIzq, valDer);
    }
    return nodo->dato;
}

//Minimax con poda Alfa-Beta.
//alfa: mejor valor garantizado para MAX hasta el momento.
//beta: mejor valor garantizado para MIN hasta el momento.
int alfabeta(Nodo *nodo, int nivel, int alfa, int beta, bool esMaximizador){
    if(nodo->izq == NULL && nodo->der == NULL){
        return nodo->dato; //Nodo hoja: valor terminal
    }

    if(esMaximizador){
        int mejor = INT_MIN;

        mejor = max(mejor, alfabeta(nodo->izq, nivel + 1, alfa, beta, false));
        alfa = max(alfa, mejor);
        if(beta <= alfa){
            cout<<"  [Poda] nivel "<<nivel<<" (nodo MAX): se descarta la rama derecha, beta("<<beta<<") <= alfa("<<alfa<<")"<<endl;
            nodo->dato = mejor;
            return mejor;
        }

        mejor = max(mejor, alfabeta(nodo->der, nivel + 1, alfa, beta, false));
        nodo->dato = mejor;
        return mejor;
    }else{
        int mejor = INT_MAX;

        mejor = min(mejor, alfabeta(nodo->izq, nivel + 1, alfa, beta, true));
        beta = min(beta, mejor);
        if(beta <= alfa){
            cout<<"  [Poda] nivel "<<nivel<<" (nodo MIN): se descarta la rama derecha, beta("<<beta<<") <= alfa("<<alfa<<")"<<endl;
            nodo->dato = mejor;
            return mejor;
        }

        mejor = min(mejor, alfabeta(nodo->der, nivel + 1, alfa, beta, true));
        nodo->dato = mejor;
        return mejor;
    }
}

//Libera la memoria del arbol (recursivo, postorden)
void liberarArbol(Nodo *&nodo){
    if(nodo == NULL) return;
    liberarArbol(nodo->izq);
    liberarArbol(nodo->der);
    delete nodo;
    nodo = NULL;
}
