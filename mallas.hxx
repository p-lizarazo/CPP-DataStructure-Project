#ifndef __MALLAS__HXX__
#define __MALLAS__HXX__

#include <vector>

Objeto::Objeto(string nom){
    nombre=nom;
}

void Objeto::agregarVertice(int xx,int yy,int zz){
    punto aux;
    aux.x=xx; aux.y=yy; aux.z=zz;
    vertices.push_back(aux);
}

void Objeto::agregarCara(vector<int> relaciones){
    caras.push_back(relaciones);
}

vector<punto> Objeto::getVert(){
    return vertices;
}
vector< vector<int> > Objeto::getCar(){
    return caras;
}

string Objeto::getNombre(){
    return nombre;
}

void Malla::agregarObjeto(Objeto aux){
    objetos.push_back(aux);
}

Objeto& Malla::buscarObjeto(string ss){
    Objeto temp("noexiste");
    for(int i=0;i<objetos.size();i++){
        if(objetos[i].getNombre() == ss ) return objetos[i];
    }
    return temp;
}

#endif //__MALLAS__HXX__
