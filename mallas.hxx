#ifndef __MALLAS__HXX__
#define __MALLAS__HXX__

#include <vector>
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

Objeto::Objeto(string nom)
{
    nombre=nom;
}

void Objeto::agregarVertice(float xx,float yy,float zz)
{
    punto aux;
    aux.x=xx;
    aux.y=yy;
    aux.z=zz;
    vertices.push_back(aux);
}

void Objeto::agregarCara(vector<int> relaciones)
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
    pair<float, int> par;
    float dist;
    punto temp;
    par.first = vertices[0].distancia(v);
    par.second = 0;
    int tam = vertices.size();
    for(int i=1 ; i<tam ; ++i)
    {
    	dist = vertices[i].distancia(v);
    	if(dist<par.first)
    	{
    		par.first = dist;
    		par.second = i;
    	}
    }
    return par;
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

void Malla::agregarObjeto(Objeto& aux)
{
	if(buscarObjeto(aux.getNombre())==-1)
	{
    	objetos.push_back(aux);
		return;
	}
    aux.cambiarNombre(aux.getNombre()+"*");
    objetos.push_back(aux);
}

int Malla::buscarObjeto(string ss)
{
    if(objetos.empty())
        return -1;
    for(int i=0; i<objetos.size(); i++)
    {
        if(objetos[i].getNombre() == ss )
            return i;
    }
    return -1;
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
    return objetos[buscarObjeto(s)].envolvente();
}

Objeto& Malla::envolvente()
{
    vector<float> fin (6);
    vector<float> temp (6);
    objetos[0].obtVertices(fin);
    int tam=objetos.size();
    for(int i=1 ; i<tam ; ++i)
    {
        if(objetos[i].getVert().empty())
            continue;
        objetos[i].obtVertices(temp);
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
    while(buscarObjeto("Envolvente_Malla_"+str)!=-1)
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

pair<pair<float,int>,int> Malla::vCercano(punto& v)
{
	pair<pair<float, int>, int> fin;
	pair<float, int> par;
	int tam = objetos.size();
	fin.first = objetos[0].vCercano(v);
	fin.second = 0;
	for(int i=1 ; i<tam ; ++i)
	{
		par = objetos[i].vCercano(v);
		if(par.first < fin.first.first)
		{
			fin.first = par;
			fin.second = i;
		}
	}
	return fin;
}

vector<Objeto>& Malla::getObjetos()
{
    return objetos;
}

#endif //__MALLAS__HXX__
