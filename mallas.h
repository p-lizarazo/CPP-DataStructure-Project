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

class Objeto
{
public:
    Objeto(string nom, int cant);
    void agregarVertice(float xx, float yy,float zz);
    void agregarCara(vector<int>& relaciones);
    int cantAristas();
    void definirCentro(punto& pnt);
    void agregarArista(int& x, int& y);
    void definirAristas();
    void obtVertices(vector<float>& puntos);
    pair<vector<int>*, float> ruta(int v, int final);
    pair<float,int> vCercano(punto& v);
    Objeto& envolvente();

	void cambiarNombre(string s);
    vector<punto>& getVert();
    vector< vector<int> >& getCar();
    set< pair<int, int> >& getAristas();
    pair<float, int>& getCentro();
    string& getNombre();
    // faltan mas funciones
protected:
    vector<punto> vertices;
    vector< vector<int> > caras;
    vector<vector<pair<float, int> > > grafo;
    set<pair<int, int> > aristas;
    string nombre;
    pair<float, int> centro;
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
