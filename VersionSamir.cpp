#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

struct Nodo{
    int dato;
    Nodo *der;
    Nodo *izq;
};

//Prototipos de funcionaes
void menu();
Nodo *crearNodo(int);
void insertarNodo(Nodo *&, int);

Nodo *arbol = NULL;


int main()
{
    menu();
    getch();
    return 0;
}

//Funcion de menu
void menu(){
    int dato, opcion, contador = 0;
    do{
        cout<<"\t.:MENU:."<<endl;
        cout<<"1. Insertar un nuevo nodo"<<endl;
        cout<<"2. Salir"<<endl;
        cout<<"Elige una opcion: ";
        cin>>opcion;
        switch(opcion){
            case 1:
                cout<<"Ingresa el valor del nodo: ";
                cin>>dato;
                insertarNodo(arbol, dato);
                contador++;
                break;
        }
    }while(opcion != 2);
}

Nodo *crearNodo(int n){
    Nodo *nuevoNodo = new Nodo();
    nuevoNodo->dato = n;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    return nuevoNodo;
}

//Funcion para insertar un nodo en el arbol
void insertarNodo(Nodo *&arbol, int n){
    if(arbol == NULL){
        Nodo *nuevoNodo = crearNodo(n);
        arbol = nuevoNodo;
    }else{
        int valorRaiz = arbol->dato;
        if(n < valorRaiz){
            insertarNodo(arbol->izq, n);
        }else{
            insertarNodo(arbol->der, n);
        }
    } 
}