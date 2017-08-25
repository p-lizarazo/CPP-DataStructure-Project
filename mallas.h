#ifndef __MALLAS__H__
#define __MALLAS__H__
#include <vector>
using namespace std;

struct punto{
    int x;
    int y;
    int z;
};

class Objeto{
    public:
        Objeto(string nom);
        void agregarVertice(int xx, int yy,int zz);
        void agregarCara( vector<int> relaciones);

        vector<punto> getVert();
        vector< vector<int> > getCar();
        string getNombre();
    // faltan mas funciones
    protected:
        vector<punto> vertices;
        vector< vector<int> > caras;
        string nombre;
    // posible algo de aristas
};

class Malla{
    public:
    void agregarObjeto(Objeto aux);
    Objeto buscarObjeto(string ss);
    // faltan mas funciones
    protected:
    vector< Objeto > objetos;
    // posible algo de aristas
};




#include "mallas.hxx"

#endif // __MALLAS__H__
