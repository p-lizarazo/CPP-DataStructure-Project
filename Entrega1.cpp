/*
    Proy EDDdfgdfgdfgfd
    Dorian Moreno y Santiago Lizarazo
*/
#include <sstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "mallas.h"
#include <iostream>
#include <fstream>

using namespace std;
/*
    Declaracion de funciones
*/
void imprimirMenu();
void cargarArchivo(Malla& mal, string ss);
bool buscarArista(vector< pair<int, int> > aristas, int x, int y);
int noAristas(Objeto obj);
void listarObjeto(Objeto obj);
void listar(Malla mal);
void eliminarObjeto(Malla& mal, string ss);
void obtVertices(Objeto obj, vector<float>& puntos);
void envolvente(Malla& mal, string ss);
void envolvente(Malla& mal);


int main(){
    Malla mal;
    string fileName;
    int op;
    bool inf=true;
    while(inf){
        imprimirMenu();
        cin >> op;
        switch(op){
        case 1:
            printf("\nEscribe el nombre del archivo a abrir: ");
            cin >> fileName;
            cargarArchivo(mal, fileName);
            break;
        case 2:
            listar(mal);
            break;
        case 3:
            printf("\nEscribe el nombre del Objeto a calcular envolvente: ");
            cin >> fileName;
            envolvente(mal, fileName);

            break;
        case 4:
            envolvente(mal);
            break;
        case 5:
            printf("\nEscribe el nombre del objeto a borrar: ");
            cin >> fileName;
            eliminarObjeto(mal, fileName);
            break;
        case 6:
            break;
        case 7:
            inf=false;
            break;
        }
        printf("\n");
    }
    return 0;
}

void imprimirMenu(){
    cout << "Escoja una opcion:\n";
    cout << " 1. Cargar Objeto en memoria\n";
    cout << " 2. Listar Objetos en memoria\n";
    cout << " 3. Crear envolvente para un objeto\n";
    cout << " 4. Crear envolvente para los objetos cargados en memoria\n" ;
    cout << " 5. Eliminar objeto\n" ;
    cout << " 6. Guardar objeto en archivo\n" ;
    cout << " 7. Salir del programa\n\n" ;

}

void cargarArchivo(Malla& mal, string ss)
{
    const char* rr=ss.c_str();
    ifstream in(rr);
    if(in.is_open())
    {
        string nom;
        in>>nom;
        int busq = mal.buscarObjeto(nom);
        if(busq!=-1)
        {
            cout<<"El objeto "<<nom<<" ya ha sido cargado en memoria\n";
            return;
        }
        Objeto *temp = new Objeto(nom);
        int cant;
        in >> cant;
        if(cant == 0){
            cout << "El archivo no contiene un objeto 3D valido\n";
            return;
        }
        while(cant--){
            float x,y,z;
            in>>x;
            in>>y;
            in>>z;
            (*temp).agregarVertice(x,y,z);
        }
        while(in>>cant && cant!=-1){
            vector<int> vertices;
            int x;
            while(cant--){
                in>>x;
                vertices.push_back(x);
            }
            (*temp).agregarCara(vertices);
        }

        mal.agregarObjeto((*temp));
        cout << "El objeto " << nom << " ha sido cargado exitosamente del archivo " << rr <<endl;
        in.close();
    }
    else
    {
        cout << "El archivo " << rr<< " No existe o es ilegible\n";
    }
}

bool buscarArista(vector< pair<int, int> > aristas, int x, int y)
{
    if(aristas.empty())
        return true;
    for(int i=0 ; i<aristas.size() ; ++i)
        if((aristas[i].first == x && aristas[i].second == y)||(aristas[i].first == y && aristas[i].second == x))
            return false;
    return true;
}

int noAristas(Objeto obj)
{
    if(obj.getCar().empty())
        return 0;
    vector< pair<int, int> > aristas;
    pair<int, int> p;
    int n = obj.getVert().size();
    int tam = obj.getCar().size();
    for(int i=0 ; i<tam ; ++i)
    {
        if(obj.getCar()[i].empty())
            continue;
        int t = obj.getCar()[i].size();
        for(int j=0 ; j<t-1 ; ++j)
        {
            if(buscarArista(aristas, obj.getCar()[i][j], obj.getCar()[i][j+1]))
            {
                p.first=obj.getCar()[i][j];
                p.second=obj.getCar()[i][j+1];
                aristas.push_back(p);
            }
        }
        if(buscarArista(aristas, obj.getCar()[i][0], obj.getCar()[i][t-1]))
        {
            p.first=obj.getCar()[i][0];
            p.second=obj.getCar()[i][t-1];
            aristas.push_back(p);
        }
    }
    return aristas.size();
}

void listarObjeto(Objeto obj)
{
    cout<<" - "<<obj.getNombre()<<" "<<obj.getVert().size()<<" vertices, "<<noAristas(obj)<<" aristas y "<<obj.getCar().size()<<" caras.";
}

void listar(Malla mal)
{
    int n=mal.getObjetos().size();
    if(n==0)
    {
        printf("ERROR: No hay objetos cargados\n");
        return;
    }
    cout<<"Hay "<<n<<" objeto(s) en memoria:\n";
    for(int i=0 ; i<n ; ++i)
    {
        listarObjeto(mal.getObjetos()[i]);
        printf("\n");
    }
}

void eliminarObjeto(Malla& mal, string ss)
{
    int t = mal.buscarObjeto(ss);
    if(t==-1)
    {
        cout<<"El Objeto "<<ss<<" no esta cargado actualmente\n";
        return;
    }
    mal.getObjetos().erase(mal.getObjetos().begin()+t);
    cout<<"El objeto "<<ss<<" fue eliminado de la memoria\n";
}

void obtVertices(Objeto obj, vector<float>& puntos)
{
    puntos[0]=puntos[3]=obj.getVert()[0].x;//Asumimos que no está vacio el vector de vertices
    puntos[1]=puntos[4]=obj.getVert()[0].y;
    puntos[2]=puntos[5]=obj.getVert()[0].z;
    for(int i=1 ; i<obj.getVert().size() ; ++i)
    {
        punto n = obj.getVert()[i];
        if(puntos[0]<n.x)
            puntos[0]=n.x;
        if(puntos[1]<n.y)
            puntos[1]=n.y;
        if(puntos[2]<n.z)
            puntos[2]=n.z;
        if(puntos[3]>n.x)
            puntos[3]=n.x;
        if(puntos[4]>n.y)
            puntos[4]=n.y;
        if(puntos[5]>n.z)
            puntos[5]=n.z;
    }
}

void envolvente(Malla& mal, string ss)
{
    int pos = mal.buscarObjeto(ss);
    if(pos==-1)
    {
        printf("El objeto no esta cargado en memoria.\n");
        return;
    }
    Objeto obj = mal.getObjetos()[pos];
    vector<float> fin (6);
    obtVertices(obj, fin);
    Objeto *env = new Objeto ("Envolvente_"+obj.getNombre());
    //Agregamos los 8 vertices al objeto combinando coordenadas
    (*env).agregarVertice(fin[0], fin[1], fin[2]);  //x y z
    (*env).agregarVertice(fin[0], fin[1], fin[5]);  //x y -z
    (*env).agregarVertice(fin[0], fin[4], fin[2]);  //x -y z
    (*env).agregarVertice(fin[0], fin[4], fin[5]);  //x -y -z
    (*env).agregarVertice(fin[3], fin[1], fin[2]);  //-x y z
    (*env).agregarVertice(fin[3], fin[1], fin[5]);  //-x y -z
    (*env).agregarVertice(fin[3], fin[4], fin[2]);  //-x -y z
    (*env).agregarVertice(fin[3], fin[4], fin[5]);  //-x -y -z
    //Agregamos las 12 caras que compondrán la envolvente
    int quemador[36] = {1,2,3, 0,1,2, 2,5,6, 0,2,5, 0,4,5, 0,1,4, 4,5,7, 5,6,7, 3,6,7, 2,3,6, 1,3,4, 3,4,7};
    for(int i=0 ; i<12 ; ++i)
    {
        vector<int> r;
        r.push_back(quemador[3*i]);
        r.push_back(quemador[3*i+1]);
        r.push_back(quemador[3*i+2]);
        (*env).agregarCara(r);
    }
    mal.agregarObjeto(*env);
    cout<<"La caja envolvente del objeto "<<ss<<" ha sido cargada exitosamente con el nombre "<<(*env).getNombre()<<".\n";
}

void envolvente(Malla& mal)
{
    if(mal.getObjetos().empty())
    {
        printf("ERROR: La malla esta vacia\n");
        return;
    }
    vector<float> fin (6);
    vector<float> temp (6);
    obtVertices(mal.getObjetos()[0], fin);
    for(int i=1 ; i<mal.getObjetos().size() ; ++i)
    {
        if(mal.getObjetos()[i].getVert().empty())
            continue;
        obtVertices(mal.getObjetos()[i], temp);
        for(int j=0 ; j<3 ; ++j)
            if(temp[j]>fin[j])
                fin[j]=temp[j];
        for(int j=3 ; j<6 ; ++j)
            if(temp[j]<fin[j])
                fin[j]=temp[j];
    }
    int a = 1;
    stringstream ss;
    ss << a;
    string str = ss.str();
    while(mal.buscarObjeto("Envolvente_Malla_"+str)!=-1)
    {
        a++;
        ss.str("");
        ss << a;
        str = ss.str();
    }
    Objeto *env = new Objeto ("Envolvente_Malla_"+str);
    //Agregamos los 8 vertices al objeto combinando coordenadas
    (*env).agregarVertice(fin[0], fin[1], fin[2]);  //x y z
    (*env).agregarVertice(fin[0], fin[1], fin[5]);  //x y -z
    (*env).agregarVertice(fin[0], fin[4], fin[2]);  //x -y z
    (*env).agregarVertice(fin[0], fin[4], fin[5]);  //x -y -z
    (*env).agregarVertice(fin[3], fin[1], fin[2]);  //-x y z
    (*env).agregarVertice(fin[3], fin[1], fin[5]);  //-x y -z
    (*env).agregarVertice(fin[3], fin[4], fin[2]);  //-x -y z
    (*env).agregarVertice(fin[3], fin[4], fin[5]);  //-x -y -z
    //Agregamos las 12 caras que compondrán la envolvente
    int quemador[36] = {1,2,3, 0,1,2, 2,5,6, 0,2,5, 0,4,5, 0,1,4, 4,5,7, 5,6,7, 3,6,7, 2,3,6, 1,3,4, 3,4,7};
    for(int i=0 ; i<12 ; ++i)
    {
        vector<int> r;
        r.push_back(quemador[3*i]);
        r.push_back(quemador[3*i+1]);
        r.push_back(quemador[3*i+2]);
        (*env).agregarCara(r);
    }
    mal.agregarObjeto(*env);
    cout<<"La caja envolvente de los objetos en memoria se ha generado exitosamente con el nombre "<<(*env).getNombre()<<".\n";
}

