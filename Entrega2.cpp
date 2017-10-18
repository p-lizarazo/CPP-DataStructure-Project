/*
    Proy EDD
    Dorian Moreno y Santiago Lizarazo
*/
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "mallas.h"
#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

/*
    Declaracion de funciones
*/
void cargarArchivo(Malla& mal, string ss);
void listarObjeto(Objeto& obj);
void listar(Malla mal);
void eliminarObjeto(Malla& mal, string ss);
void envolvente(Malla& mal, string ss);
void envolvente(Malla& mal);
void guardarObjeto(Malla& mal,string fileName,string objName);
void vCercano(Malla& mal, string s, punto v);
void vCercano(Malla& mal, punto v);
void vCercanoCaja(Malla& mal, string s);
int cantDig(float n);


int main()
{
    Malla mal;
    string fileName, op, act;
    bool inf=true;
    while(inf)
    {
        printf("$ ");
        stringstream ss;
        getline(cin, op);
        act="";
        ss << op;
        ss >> act;
        if(act == "ayuda")
        {
            ss >> act;
            if(act == "ayuda")
            {
                printf("Los comandos validos son los siguientes:\ncargar\t\tlistado\t\tenvolvente\ndescargar\tguardar\t\tsalir\nv_cercano\tv_cercanos_caja\n\n");
                ss.str("");
                continue;
            }
            if(act == "cargar")
            {
                printf("cargar nombre_archivo\n\nCarga en memoria la informacion del objeto nombre_objeto contenida en el archivo identificado por nombre_archivo.\n\n");
                ss.str("");
                continue;
            }
            if(act == "listado")
            {
                printf("listado\n\nLista todos los objetos en memoria. Dando: su nombre, # de vertices, # de caras y # de aristas.\n\n");
                ss.str("");
                continue;
            }
            if(act == "envolvente")
            {
                printf("envolvente\nenvolvente nombre_objeto\n\nCrea una caja envolvente que cubre todos los objetos o uno en particular, luego la guarda en la malla de objetos.\n\n");
                ss.str("");
                continue;
            }
            if(act == "descargar")
            {
                printf("descargar nombre_objeto\n\nDescarga un objeto de memoria.\n\n");
                ss.str("");
                continue;
            }
            if(act == "guardar")
            {
                printf("guardar nombre_objeto nombre_archivo\n\nGuarda en un archivo de texto la informacion basica de un objeto.\n\n");
                ss.str("");
                continue;
            }
            if(act == "salir")
            {
                printf("salir\n\nCierra el programa\n\n");
                ss.str("");
                continue;
            }
            if(act == "v_cercano")
            {
                printf("v_cercano px py pz nombre_objeto\nv_cercano px py pz\n\nIdentifica el vertice del objeto nombre_objeto (o de entre todos los objetos si no se proporciona el nombre) mas cercano (en terminos de la distancia euclidiana) al punto indicado por las coordenadas px, py y pz. Informa en pantalla el indice del vertice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado.\n\n");
                ss.str("");
                continue;
            }
            if(act == "v_cercanos_caja")
            {
                printf("v_cercanos_caja nombre_objeto\n\nIdentifica los vertices del objeto nombre_objeto mas cercanos (en terminos de la distancia euclidiana) a los puntos (vertices) que definen la respectiva caja envolvente del objeto. Informa en pantalla, en una tabla, las coordenadas de cada una de las esquinas de la caja envolvente, y para cada una de ellas, el indice del vertice mas cercano, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra de la respectiva esquina.\n\n");
                ss.str("");
                continue;
            }
        }
        bool acc = true;
        if(act == "cargar")
        {
            act="";
            ss >> act;
            if(act=="")
                printf("No se han ingresado argumentos suficientes.\n\n");
            else
            {
                ss >> act;
                cargarArchivo(mal, act);
            }
            ss.str("");
            continue;
        }
        if(act == "listado")
        {
            ss >> act;
            if(act!="listado")
                cout<<act<<" no es un argumento valido de listado.\n\n";
            else
                listar(mal);
            ss.str("");
            continue;
        }
        if(act == "envolvente")
        {
            act = "";
            ss >> act;
            if(act=="")
            {
                envolvente(mal);
            }
            else
            {
                envolvente(mal, act);
            }

            ss.str("");
            continue;
        }
        if(act == "descargar")
        {
            act = "";
            ss >> act;
            if(act == "")
                printf("No hay argumentos suficientes para la funcion descargar\n\n");
            else
                eliminarObjeto(mal, act);
            ss.str("");
            continue;
        }
        if(act == "guardar")
        {
            string act2 = act = "";
            ss >> act;
            ss >> act2;
            if(act2 == "")
                printf("No hay argumentos suficientes para la funcion guardar\n\n");
            else
                guardarObjeto(mal, act2, act);
            ss.str("");
            continue;
        }
        if(act == "v_cercano")
        {
            stringstream ss2;
            ss2.str("");
            for(int i = 0 ; i<3 ; ++i)
            {
                act = "";
                ss >> act;
                if(act=="")
                {
                    cout<<"No hay argumentos suficientes\n\n";
                    ss.str("");
                    continue;
                }
                for(int j = 0 ; j<act.size() ; ++j)
                    if((act[j]<'0' || act[j]>'9') && act[j]!='.' && act[j]!=',' && act[j]!='-')
                    {
                        cout<<"Parametros de entrada invalida\n\n";
                        ss.str("");
                        continue;
                    }
                ss2 << act;
                ss2 << " ";
            }
            punto v;
            ss2 >> v.x;
            ss2 >> v.y;
            ss2 >> v.z;
            act = "";
            ss >> act;
            if(act=="")
            {
                vCercano(mal, v);
            }
            else
            {
                vCercano(mal, act, v);
            }
            ss.str("");
            continue;
        }
        if(act == "v_cercanos_caja")
        {
            ss >> act;
            if(act == "")
                printf("No hay argumentos suficientes para la funcion v_cercanos_caja\n\n");
            else
                vCercanoCaja(mal, act);
            ss.str("");
            continue;
        }
        if(act == "salir")
        {
            inf=false;
            continue;
        }
        if(act == "")
        {
            continue;
        }
        cout<<"El comando '"<<act<<"' no esta definido, escriba ayuda para mas informacion\n\n";
    }
    return 0;
}

void cargarArchivo(Malla& mal, string ss)
{
    const char* rr=ss.c_str();
    ifstream in(rr);
    if(in.is_open())
    {
        string nom;
        in>>nom;
        if(mal.hayObjeto(nom))
        {
            cout<<"El objeto "<<nom<<" ya ha sido cargado en memoria\n";
            in.close();
            return;
        }
        Objeto *temp = new Objeto(nom);
        int cant;
        in >> cant;
        if(cant == 0)
        {
            cout << "El archivo no contiene un objeto 3D valido\n";
            in.close();
            return;
        }
        while(cant--)
        {
            float x,y,z;
            in>>x;
            in>>y;
            in>>z;
            (*temp).agregarVertice(x,y,z);
        }
        while(in>>cant && cant!=-1)
        {
            vector<int>* vertices = new vector<int>;
            int x;
            while(cant--)
            {
                in>>x;
                vertices->push_back(x);
            }
            temp->agregarCara(*vertices);
        }
        temp->definirAristas();
        mal.agregarObjeto(temp);
        cout << "El objeto " << nom << " ha sido cargado exitosamente del archivo " << rr <<endl;
        in.close();
    }
    else
    {
        cout << "El archivo " << rr<< " No existe o es ilegible\n";
    }
}

void listarObjeto(Objeto& obj)
{
    cout<<" - "<<obj.getNombre()<<" "<<obj.getVert().size()<<" vertices, "<<obj.cantAristas()<<" aristas y "<<obj.getCar().size()<<" caras.";
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
    for(map<string, Objeto*>::iterator it=mal.getObjetos().begin() ; it!=mal.getObjetos().end() ; ++it)
    {
        listarObjeto(*(it->second));
        printf("\n");
    }
}

void eliminarObjeto(Malla& mal, string ss)
{
    if(!mal.hayObjeto(ss))
    {
        cout<<"El Objeto "<<ss<<" no esta cargado actualmente\n";
        return;
    }
    mal.getObjetos().erase(mal.buscarObjeto(ss));
    cout<<"El objeto "<<ss<<" fue eliminado de la memoria\n";
}

void envolvente(Malla& mal, string ss)
{
    if(!mal.hayObjeto(ss))
    {
        printf("El objeto no esta cargado en memoria.\n");
        return;
    }
    Objeto* obj;
    obj = &mal.envolvente(ss);
    mal.agregarObjeto(obj);
    cout<<"La caja envolvente del objeto "<<ss<<" ha sido cargada exitosamente con el nombre "<<obj->getNombre()<<".\n";
}

void envolvente(Malla& mal)
{
    if(mal.getObjetos().empty())
    {
        printf("ERROR: La malla esta vacia\n");
        return;
    }
    Objeto *env;
    env = &mal.envolvente();
    mal.agregarObjeto(env);
    cout<<"La caja envolvente de los objetos en memoria se ha generado exitosamente con el nombre "<<env->getNombre()<<".\n";
}

void guardarObjeto(Malla& mal,string fileName,string objName)
{
    const char* rr=fileName.c_str();
    if(!mal.hayObjeto(objName))
    {
        cout << "El objeto " << objName << " no ha sido cargado en memoria.\n";
        return;
    }
    else
    {
        map<string, Objeto*>::iterator it = mal.buscarObjeto(objName);
        ofstream out (rr);
        out << it->second->getNombre() << endl;
        vector < punto > vert=it->second->getVert();
        out << vert.size() << endl;
        for(int i=0; i<vert.size(); i++)
        {
            out << vert[i].x << " " << vert[i].y << " " << vert[i].z << endl;
        }
        vector < vector<int> > c = it->second->getCar();
        for(int i=0; i<c.size(); i++)
        {
            out << c[i].size() << " ";
            for(int j=0; j<c[i].size(); j++)
            {
                out << c[i][j] << " ";
            }
            out << endl;
        }
        out << "-1\n";
        cout << "La informacion del objeto " << objName << " ha sido guardada exitosamente en el archivo " << fileName<<"\n";
        return;
    }
}

void vCercano(Malla& mal, string s, punto v)
{
    if(!mal.hayObjeto(s))
    {
        cout<<"El objeto "<<s<<" no esta cargado en memoria\n";
        return;
    }
    Objeto* obj;
    obj = mal.buscarObjeto(s)->second;
    if(obj->getVert().empty())
    {
        cout<<"No hay vertices cargados para este objeto\n";
        return;
    }
    pair<float, int> par = obj->vCercano(v);
    punto p = obj->getVert()[par.second];
    cout<<"El vertice "<<par.second+1<<" ("<<p.x<<","<<p.y<<","<<p.z<<") del objeto "<<obj->getNombre()<<" es el mas cercano al punto ("<<v.x<<","<<v.y<<","<<v.z<<"), a una distancia de "<<par.first<<"\n";
}

void vCercano(Malla& mal, punto v)
{
    if(mal.getObjetos().empty())
    {
        cout<<"No hay objetos cargados en la malla\n";
        return;
    }
    pair<pair<float, int>, map<string, Objeto*>::iterator > par = mal.vCercano(v);
    Objeto* obj;
    obj = par.second->second;
    punto p = obj->getVert()[par.first.second];
    cout<<"El vertice "<<par.first.second+1<<" ("<<p.x<<","<<p.y<<","<<p.z<<") del objeto "<<obj->getNombre()<<" es el mas cercano al punto ("<<v.x<<","<<v.y<<","<<v.z<<"), a una distancia de "<<par.first.first<<"\n";
}

void vCercanoCaja(Malla& mal, string s)
{
    if(!mal.hayObjeto(s))
    {
        cout<<"El objeto "<<s<<" no esta cargado en memoria\n";
        return;
    }
    Objeto* obj;
    obj = mal.buscarObjeto(s)->second;
    Objeto* env;
    env = &obj->envolvente();
    punto temp1, temp2;
    int tam = env->getVert().size(), tabs, aux;
    pair<float, int> par;
    printf("Esquina\t\t\t\tVertice\t\t\t\t\tDistancia\n");
    for(int i=0 ; i<tam ; ++i)
    {
        tabs=0;
        temp2 = env->getVert()[i];
        par = obj->vCercano(temp2);
        temp1 = obj->getVert()[par.second];
        printf("%d (%.3f, ", i+1, temp2.x);
        aux = cantDig(temp2.x) + 9;
        printf("%.3f, ", temp2.y);
        aux += cantDig(temp2.y) + 6;
        printf("%.3f) ", temp2.z);
        aux += cantDig(temp2.z) + 6;
        tabs = aux/8;
        aux %= 8;
        tabs = 4 - tabs;
        for(int j=0 ; j<tabs ; ++j)
            printf("\t");
        aux=0;
        printf("%d\t(%.3f, ", par.second + 1, temp1.x);
        aux += cantDig(temp1.x) + 15;
        printf("%.3f, ", temp1.y);
        aux += cantDig(temp1.y) + 6;
        printf("%.3f) ", temp1.z);
        aux += cantDig(temp1.z) + 6;
        tabs = aux/8;
        aux %= 8;
        tabs = 5 - tabs;
        for(int j=0 ; j<tabs ; ++j)
            printf("\t");
        printf("%f\n", par.first);
    }
}

int cantDig(float n)
{
    int i=0;
    if(n<0)
        i++;
    if((int)n==0)
        return i+1;
    while((int)n!=0)
    {
        ++i;
        n/=10;
    }
    return i;
}
