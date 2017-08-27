#ifndef __MALLAS__H__
#define __MALLAS__H__
#include <vector>
using namespace std;

struct punto{
    float x;
    float y;
    float z;
};

class Objeto{
    public:
        Objeto(string nom);
        void agregarVertice(float xx, float yy,float zz);
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
    void agregarObjeto(Objeto& aux);
    int buscarObjeto(string ss);
    vector<Objeto>& getObjetos();
    // faltan mas funciones
    protected:
    vector<Objeto> objetos;
    // posible algo de aristas
};




#include "mallas.hxx"

#endif // __MALLAS__H__
