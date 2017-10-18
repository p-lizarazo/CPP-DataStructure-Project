#ifndef __MALLAS__HXX__
#define __MALLAS__HXX__

#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <math.h>
#include <iostream>

float punto::distancia(punto& v)
{
    float xx, yy, zz, dist;
    xx = x-v.x;
    xx *= xx;
    yy = y-v.y;
    yy *= yy;
    zz = z-v.z;
    zz *= zz;
    dist = sqrt(xx+yy+zz);
    return dist;
}

Arbol::Nodo::Nodo(int n)
{
    this->vertice = n;
    hijos.push_back(NULL);
    hijos.push_back(NULL);
    hijos.push_back(NULL);
    hijos.push_back(NULL);
    hijos.push_back(NULL);
    hijos.push_back(NULL);
    hijos.push_back(NULL);
    hijos.push_back(NULL);
}
void Arbol::Nodo::setVertice(int n)
{
    this->vertice = n;
}
int Arbol::Nodo::getVertice()
{
    return this->vertice;
}
void Arbol::Nodo::setHijo(int n, Nodo* hijo)
{
    this->hijos[n] = hijo;
}

Arbol::Nodo* Arbol::Nodo::getHijo(int n)
{
    return this->hijos[n];
}

Arbol::Arbol()
{
    this->raiz = new Nodo(0);
}
void Arbol::agregarPunto(vector<punto>& vertices, int n, punto& p)
{
    Nodo* aux = raiz;
    Nodo* padre;
    int i;
    punto* temp;
    while(aux != NULL)
    {
        padre = aux;
        temp = &vertices[aux->getVertice()];
        if(p.x > temp->x)
        {
            if(p.y > temp->y)
            {
                if(p.z > temp->z)
                {
                    i=0;
                    aux = aux->getHijo(0);
                }
                else
                {
                    i=1;
                    aux = aux->getHijo(1);
                }
            }
            else
            {
                if(p.z > temp->z)
                {
                    i=2;
                    aux = aux->getHijo(2);
                }
                else
                {
                    i=3;
                    aux = aux->getHijo(3);
                }
            }
        }
        else
        {
            if(p.y > temp->y)
            {
                if(p.z > temp->z)
                {
                    i=4;
                    aux = aux->getHijo(4);
                }
                else
                {
                    i=5;
                    aux = aux->getHijo(5);
                }
            }
            else
            {
                if(p.z > temp->z)
                {
                    i=6;
                    aux = aux->getHijo(6);
                }
                else
                {
                    i=7;
                    aux = aux->getHijo(7);
                }
            }
        }
    }
    aux = new Nodo(n);
    padre->setHijo(i, aux);
}
Arbol::Nodo* Arbol::getRaiz()
{
    return this->raiz;
}
pair<float, int> Arbol::buscarCercano(vector<punto>& vertices, punto& v)
{
    pair<float, int> par;
    par.first = vertices[this->getRaiz()->getVertice()].distancia(v);
    par.second = this->getRaiz()->getVertice();
    float dist;
    punto* temp;
    int tempo;
    Nodo* aux;
    queue<Nodo*> q;
    queue<int> qi;
    queue<bool> qb;
    vector<int> busq;
    q.push(this->getRaiz());
    qi.push(0);
    aux = this->getRaiz();
    while(aux!=NULL)
    {
        temp = &vertices[aux->getVertice()];
        if(v.x > temp->x)
        {
            if(v.y > temp->y)
            {
                if(v.z > temp->z)
                {
                    busq.push_back(0);
                    aux = aux->getHijo(0);
                    continue;
                }
                else
                {
                    busq.push_back(1);
                    aux = aux->getHijo(1);
                    continue;
                }
            }
            else
            {
                if(v.z > temp->z)
                {
                    busq.push_back(2);
                    aux = aux->getHijo(2);
                    continue;
                }
                else
                {
                    busq.push_back(3);
                    aux = aux->getHijo(3);
                    continue;
                }
            }
        }
        else
        {
            if(v.y > temp->y)
            {
                if(v.z > temp->z)
                {
                    busq.push_back(4);
                    aux = aux->getHijo(4);
                    continue;
                }
                else
                {
                    busq.push_back(5);
                    aux = aux->getHijo(5);
                    continue;
                }
            }
            else
            {
                if(v.z > temp->z)
                {
                    busq.push_back(6);
                    aux = aux->getHijo(6);
                    continue;
                }
                else
                {
                    busq.push_back(7);
                    aux = aux->getHijo(7);
                    continue;
                }
            }
        }
    }
    //Una vez acabado el ciclo sabemos exactamente en que cuadrante está ubicado el punto, por lo tanto sabemos cuales son los elementos que debemos calcular
    while(!q.empty())
    {
        aux = q.front();
        tempo = qi.front();
        qi.pop();
        q.pop();
        dist = vertices[aux->getVertice()].distancia(v);
        if(dist < par.first)
        {
            par.first = dist;
            par.second = aux->getVertice();
        }
        if(tempo!=-1)
        {
            for(int i=0 ; i<8 ; ++i)
                if(aux->getHijo(i)!=NULL)
                {
                    q.push(aux->getHijo(i));
                    if(i != busq[tempo+1])
                        qi.push(tempo+1);
                    else
                        qi.push(-1);
                }
        }
        else
        {
            for(int i=0 ; i<8 ; ++i)
                if(aux->getHijo(i)!=NULL)
                {
                    q.push(aux->getHijo(i));
                    qi.push(-1);
                }
        }
    }
    return par;
}

Objeto::Objeto(string nom)
{
    this->nombre=nom;
}

void Objeto::agregarVertice(float xx,float yy,float zz)
{
    punto aux;
    aux.x=xx;
    aux.y=yy;
    aux.z=zz;
    vertices.push_back(aux);
    this->UbicacionVertices.agregarPunto(vertices, vertices.size()-1, aux);
}

void Objeto::agregarCara(vector<int>& relaciones)
{
    caras.push_back(relaciones);
}

int Objeto::cantAristas()
{
    return aristas.size();
}

void Objeto::agregarArista(int& x, int& y)
{
    pair<int, int> aux;
    if(x<y)
    {
        aux.first = x;
        aux.second = y;
        aristas.insert(aux);
        return;
    }
    else if(y<x)
    {
        aux.second = x;
        aux.first = y;
        aristas.insert(aux);
        return;
    }
    aux.first = x;
    aux.second = y;
    aristas.insert(aux);
}

void Objeto::definirAristas()
{
    aristas.empty();
    int tam = caras.size(), tam2;
    for(int i=0 ; i<tam ; ++i)
    {
        tam2 = caras[i].size();
        for(int j=0 ; j<tam2 ; ++j)
            agregarArista(caras[i][j], caras[i][(j+1)%tam2]);
    }
}


void Objeto::obtVertices(vector<float>& puntos)
{
    puntos[0]=puntos[3]=vertices[0].x;//Asumimos que no está vacio el vector de vertices
    puntos[1]=puntos[4]=vertices[0].y;
    puntos[2]=puntos[5]=vertices[0].z;
    int tam = vertices.size();
    for(int i=1 ; i<tam ; ++i)
    {
        punto n = vertices[i];
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

pair<float, int> Objeto::vCercano(punto& v)
{
    return this->UbicacionVertices.buscarCercano(this->vertices, v);
}

void Objeto::cambiarNombre(string s)
{
    nombre = s;
}

vector<punto>& Objeto::getVert()
{
    return vertices;
}
vector< vector<int> >& Objeto::getCar()
{
    return caras;
}

set<pair<int, int> >& Objeto::getAristas()
{
    return aristas;
}

string& Objeto::getNombre()
{
    return nombre;
}

void Malla::agregarObjeto(Objeto* aux)
{
    objetos[aux->getNombre()] = aux;
}

bool Malla::hayObjeto(string ss)
{
    if(buscarObjeto(ss)==objetos.end())
        return false;
    return true;
}
map<string,Objeto*>::iterator Malla::buscarObjeto(string ss)
{
    return objetos.find(ss);
}


Objeto& Objeto::envolvente()
{
    vector<float> fin (6);
    obtVertices(fin);
    Objeto *env = new Objeto ("Envolvente_"+nombre);
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
    env->definirAristas();
    return *env;
}

Objeto& Malla::envolvente(string s)
{
    return buscarObjeto(s)->second->envolvente();
}

Objeto& Malla::envolvente()
{
    vector<float> fin (6);
    vector<float> temp (6);
    objetos.begin()->second->obtVertices(fin);
    for(map<string, Objeto*>::iterator it = objetos.begin() ; it!=objetos.end() ; ++it)
    {
        if(it->second->getVert().empty())
            continue;
        it->second->obtVertices(temp);
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
    while(hayObjeto("Envolvente_Malla_"+str))
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
    env->definirAristas();
    return *env;
}

pair<pair<float,int>,map<string, Objeto*>::iterator> Malla::vCercano(punto& v)
{
    pair<pair<float, int>, map<string, Objeto*>::iterator > fin;
    pair<float, int> par;
    int tam = objetos.size();
    fin.first = objetos.begin()->second->vCercano(v);
    fin.second = objetos.begin();
    for(map<string, Objeto*>::iterator it=objetos.begin() ; it!=objetos.end() ; ++it)
    {
        par = it->second->vCercano(v);
        if(par.first < fin.first.first)
        {
            fin.first = par;
            fin.second = it;
        }
    }
    return fin;
}

map<string, Objeto*>& Malla::getObjetos()
{
    return objetos;
}

#endif //__MALLAS__HXX__
