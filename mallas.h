#ifndef __MALLAS__H__
#define __MALLAS__H__
#include <vector>
#include <set>
#include <map>
using namespace std;

struct punto
{
    float x;
    float y;
    float z;
    float distancia(punto& v);
};

class Arbol
{
    class Nodo
    {
    public:
        Nodo(int n);
        void setVertice(int n);
        int getVertice();
        void setHijo(int n, Nodo* hijo);
        Nodo* getHijo(int n);
    private:
        int vertice;
        vector<Nodo*> hijos;
    };
public:
    Arbol();
    void agregarPunto(vector<punto>& vertices, int n, punto& p);
    Nodo* getRaiz();
    pair<float, int> buscarCercano(vector<punto>& vertices, punto& v);
private:
    Nodo* raiz;
};

class Objeto
{
public:
    Objeto(string nom);
    void agregarVertice(float xx, float yy,float zz);
    void agregarCara(vector<int>& relaciones);
    int cantAristas();
    void agregarArista(int& x, int& y);
    void definirAristas();
    void obtVertices(vector<float>& puntos);
    pair<float,int> vCercano(punto& v);
    Objeto& envolvente();

    void cambiarNombre(string s);
    vector<punto>& getVert();
    vector< vector<int> >& getCar();
    set< pair<int, int> >& getAristas();
    string& getNombre();
    // faltan mas funciones
protected:
    vector<punto> vertices;
    Arbol UbicacionVertices;
    vector< vector<int> > caras;
    set<pair<int, int> > aristas;
    string nombre;
    // posible algo de aristas
};

class Malla
{
public:
    void agregarObjeto(Objeto* aux);
    bool hayObjeto(string ss);
    map<string,Objeto*>::iterator buscarObjeto(string ss);
    map<string,Objeto*>& getObjetos();
    pair<pair<float,int>,map<string, Objeto*>::iterator> vCercano(punto& v);
    Objeto& envolvente();
    Objeto& envolvente(string s);

    // faltan mas funciones
protected:
    map<string, Objeto*> objetos;
    // posible algo de aristas
};




#include "mallas.hxx"

#endif // __MALLAS__H__
