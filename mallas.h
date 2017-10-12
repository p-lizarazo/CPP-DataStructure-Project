#ifndef __MALLAS__H__
#define __MALLAS__H__
#include <vector>
#include <set>
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
    Objeto(string nom);
    void agregarVertice(float xx, float yy,float zz);
    void agregarCara( vector<int> relaciones);
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
    vector< vector<int> > caras;
    set<pair<int, int> > aristas;
    string nombre;
    // posible algo de aristas
};

class Malla
{
public:
    void agregarObjeto(Objeto& aux);
    int buscarObjeto(string ss);
    vector<Objeto>& getObjetos();
    pair<pair<float,int>,int> vCercano(punto& v);
    Objeto& envolvente();
    Objeto& envolvente(string s);

    // faltan mas funciones
protected:
    vector<Objeto> objetos;
    // posible algo de aristas
};




#include "mallas.hxx"

#endif // __MALLAS__H__
