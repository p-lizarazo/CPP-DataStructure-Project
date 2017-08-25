/*
    Proy EDD
    Dorian Moreno y Santiago Lizarazo
*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "mallas.h"
#include <iostream>

using namespace std;

void imprimirMenu();
void cargarArchivo(string ss);


int main(){

    string fileName;
    int op;
    bool inf=true;
    while(inf){
        imprimirMenu();
        cin >> op;
        switch(op){
        case 1:
            cargarArchivo(fileName);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            inf=false;
            break;
        }

    }
    return 0;
}

void imprimirMenu(){

    cout <<"1. Cargar Objeto en memoria\n";
    cout << "2. Listar Objetos en memoria\n";
    cout << "3. Crear envolvente para un objeto\n";
    cout << "4. Crear envolvente para los objetos cargados en memoria\n" ;
    cout << "5. Eliminar objeto\n" ;
    cout << "6. Guardar objeto en archivo\n" ;
    cout << "7. Salir del programa\n" ;
}

void cargarArchivo(string ss){
    const char* rr=ss.c_str();
    ifstream in(rr);

}

