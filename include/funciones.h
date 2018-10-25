/// funciones.h
/// Practica 1 Informatica Industrial
/// Jaime Villa Plaza
/// IEIA 3 CURSO 2018/2019

#ifndef FUNCIONES_H
#define FUNCIONES_H

/// includes .h

#include "funciones.h"
#include "Datos.h"

/// librerias

#include <iostream> /// E/S
#include <vector> /// vectores
#include <cmath> /// matematica
#include <fstream> /// ficheros
#include <ctime> /// para mostrar fechas
#include <algorithm> /// para ordenar vectores
#include <iomanip> /// para marcar la precision

using namespace std;

/// Declaración de las funciones friend templatizadas

template <typename U> void escribeFichero (vector<Datos<U>> &v);
template <typename U> ifstream& operator>> (ifstream &fich, Datos<U> &d);
template <typename U> ofstream& operator<< (ofstream &fich, Datos<U> &d);
template <typename U> ostream& operator<< (ostream &out, Datos<U> &d);
template <typename U> void minymax (vector<Datos<U>> &v);
template <typename U> void IntervaloDeTiempo (vector<Datos<U>> &v);
template <typename U> void muestraMediana (vector<Datos<U>> &v);


///Funciones externas
template <typename U> void leeFichero(vector<Datos<U>> &v);
template <typename U> void cargarVector(vector<Datos<U>> &v);
int opcion();
bool repetir();
template <typename U> void mostrarVector(vector<Datos<U>> &v);
void limpiarPantalla();


/// leeFichero()
/// Devuelve: nada
/// Argumentos: un vector de clases "Datos" templatizadas
///CARGA LOS DATOS DE UN FICHERO EN UN VECTOR, recibe por referencia un vector, en el que carga los datos.
///Si no se encuentra el fichero avisa de error
template <typename T>
void leeFichero(vector<Datos<T>> &v)
{
    //string nombre;
    Datos<T> d("SensorNoDetectado",0.0,0.0);
    cout<<"________________________________ "<<endl;
    //cin>>nombre;
    ifstream fich("Fichero de datos.txt");
    if (!fich)
    {
        throw ERROR_OPENING_FILE;
    }
    while (fich)
    {
        fich >> d;

        if(fich)
        {

            v.push_back(d);
        }
    }

    fich.close();
}
/// escribeFichero()
/// Devuelve: nada
/// Argumentos: un vector de clases "Datos" templatizadas
///ESCRIBE EN UN FICHERO LOS DATOS DE UN SENSOR, recibe por referencia un vector, en el cual busca la referencia de un sensor determinado
///Cada vez que encuentra esa referencia, introduce los datos de ese termino.
template <typename T>
void escribeFichero (vector<Datos<T>> &v)
{
    try
    {
        ofstream fich;
        string sensor,nombre;
        int j = 0;
        cout<<"Escribe el nombre del sensor que quiere estudiar: "<<endl;
        cin>>sensor;

        cout<<"Se creara un fichero con la informacion."<<endl;
        cout<<"Por favor, introduzca el nombre del fichero donde quiera guardar la informacion. "<<endl;
        cin>>nombre;
        fich.open(nombre);
        fich<<"Fichero "<<nombre<<endl<<"Datos del sensor "<<sensor<<": "<<endl;
        for (size_t i=0; i!=v.size(); ++i)
        {
            if (v[i].referencia==sensor)
            {
                ++j;
                fich<<v[i];
                cout<<v[i]<<endl;
            }
        }
        if (j==0)
            throw ERROR_NO_SENSOR;
        fich.close();
    }
    catch (int excepcion)
    {
        if (excepcion==ERROR_NO_SENSOR)
            cout<<"ERROR: El sensor introducido no existe."<<endl;
    }


}
/// operator>>()
/// Devuelve: un ifstream
/// Argumentos: un  fichero y una clase "Datos" templatizadas
///OPERADOR DE lECTURA EN FICHEROS
template <typename T>
ifstream& operator>>  (ifstream &fich, Datos<T> &d)
{
    fich >> d.lectura;
    fich >> d.referencia;
    fich >> d.tiempo;
    return fich;
}
/// operator<<()
/// Devuelve: un ofstream
/// Argumentos: un  fichero y una clase "Datos" templatizadas
///OPERADOR DE ESCRITURA EN FICHEROS
template <typename T>
ofstream& operator<< (ofstream &fich, Datos<T> &d)
{
    fich<<d.lectura<<" "<<d.referencia<<" "<<d.tiempo<<endl;
    return fich;
}
/// operator<<()
/// Devuelve: un ostream
/// Argumentos: un  ostream y una clase "Datos" templatizadas
///OPERADOR PARA SACAR POR PANTALLA LA CLASE "Datos"
template <typename T>
ostream& operator<< (ostream &out, Datos<T> &d)
{
    time_t curr_time = d.tiempo;
    out<<d.lectura<<"    ||    "<<d.referencia<<"    ||    "<<ctime(&curr_time)<<endl;
    return out;
}
/// minymax()
/// Devuelve: nada
/// Argumentos: un vector de clases "Datos" templatizadas
///MUESTRA LAS LECTURAS MIN Y MAX Y SU PROCEDENCIA, recibe un vector por referencia, con la funcion sort lo ordenamos y sacamos la lectura min y max
///Esta lecturas lecturas se encuentra en el primer y el ultimo elemento
template <typename T>
void minymax (vector<Datos<T>> &v)
{
    Datos<T> mayor=v[0], menor=v[0];
    sort(v.begin(), v.end());
    menor=v[0];
    mayor=v[v.size()-1];

    cout<<"La mayor lectura es "<<mayor.lectura<<" y viene del sensor: "<<endl;

    for (size_t i=0; i!=v.size(); i++ )///Este bucle busca en que sensores se repite la maxima lectura
    {
        if(mayor.lectura==v[i].lectura)
        {
            cout<<v[i].referencia<<endl;
        }
    }
    cout<<"la menor lectura es "<<menor.lectura<<" y viene del sensor: "<<endl;

    for (size_t i=0; i!=v.size(); i++ )///Este bucle busca en que sensores se repite la minima lectura
    {
        if(menor.lectura==v[i].lectura)
        {
            cout<<v[i].referencia<<endl;
        }
    }

}
/// IntervaloDeTiempo()
/// Devuelve: nada
/// Argumentos: un vector de clases "Datos" templatizadas
///MUESTRA EL INTERVALO DE TIEMPO EN EL QUE SE TOMARON LAS LECTURAS
///Compara y calcula las fechas min y max
template <typename T>
void IntervaloDeTiempo (vector<Datos<T>> &v)
{
    time_t curr_time;
    long tardia= v[0].tiempo, temprana= v[0].tiempo;
    for (size_t i=0; i!=v.size(); i++ )
    {
        if(temprana<v[i].tiempo)
        {
            tardia = v[i].tiempo;
        }
        else if (temprana>v[i].tiempo)
        {
            temprana = v[i].tiempo;
        }
    }
    curr_time = temprana;
    cout<<"Los datos del contenedor de entrada han sido adquiridos entre: "<<endl<<ctime(&curr_time);
    curr_time = tardia;
    cout<<" y  "<<ctime(&tardia)<<endl;

}
/// muestraMediana()
/// Devuelve: nada
/// Argumentos: un vector de clases "Datos" templatizadas
///MUESTRA LA MEDIANA DE LOS VALORES DE UN SENSOR, pide la identificacion de un sensor y calcula la mediana
template <typename T>
void muestraMediana (vector<Datos<T>> &v)
{
    try
    {
        vector<Datos<T>> u;
        string sensor;
        cout<<"Intro nombre del sensor: "<<endl;
        cin>>sensor;
        for (size_t i=0; i!=v.size(); ++i)
        {
            if (v[i].referencia==sensor)
                u.push_back(v[i]);
        }
        if (u.size()==0)
            throw ERROR_NO_SENSOR;
        else
        {
            sort(u.begin(), u.end());
            if(u.size()%2==0)
            {
                double mediana=0.0;
                mediana = (u[u.size()/2].lectura+u[(u.size()/2)-1].lectura)/2;
                cout<<"La mediana de los valores captados por el sensor "<<u[u.size()/2].referencia<<" es : "<<mediana<<endl;
            }
            else
                cout<<"La mediana de los valores captados por el sensor "<<u[u.size()/2].referencia<<" es : "<<u[u.size()/2].lectura<<endl;
        }
    }
    catch (int excepcion)
    {
        if (excepcion==ERROR_NO_SENSOR)
            cout<<"ERROR: El sensor introducido no existe."<<endl;
    }
}
/// cargarVector()
/// Devuelve: nada
/// Argumentos: un vector de clases "Datos" templatizadas
///EJECUTA LA FUNCION "leeFichero" Y COMPRUEBA QUE NO HAYA ERRORES
template <typename T>
void cargarVector(vector<Datos<T>> &v)
{
    try
    {
        leeFichero(v);
    }
    catch (int excepcion)
    {
        if (excepcion==ERROR_OPENING_FILE)
        {
            cout<<"Error al abrir el fichero de datos inicial."<<endl;
        }
    }
}
/// opcion()
/// Devuelve: nada
/// Argumentos: nada
///MUESTRA EL MENU Y PIDE UNA OPCION
int opcion()
{
    int o;
    cout<<"        MENU PRINCIPAL       "<<endl<<"_______________________________________"<<endl<<"Elige una opcion: "<<endl;
    cout<<" \n 1: Mostrar todas las lecturas"<<"\n 2: Mostrar valor min y max"<<"\n 3: Mostrar intervalo de tiempo"<<"\n 4: Generar fichero"<<"\n 5: Mostrar mediana"<<endl;
    cout<<"\n_______________________________________"<<endl;
    cin>>o;
    return o;
}
/// repetir()
/// Devuelve: nada
/// Argumentos: nada
///PREGUNTA AL USUARIO SI QUIERE SEGUIR
bool repetir()
{
    string repetir = "n";
    bool boolrep=false;
    cout<<"\n_______________________________________"<<"\n Quiere seguir? s/n;"<<endl;
    cin>>repetir;
    if (repetir=="s")
    {
        boolrep=true;
    }
    return boolrep;
}
/// mostrarVector()
/// Devuelve: nada
/// Argumentos: un vector de clases "Datos" templatizadas
///SACA POR PANTALLA LOS DATOS DE UN VECTOR
template <typename T>
void mostrarVector(vector<Datos<T>> &v)
{
    for(size_t i = 0; i!=v.size(); ++i)
    {
        cout<<v[i]<<endl;
    }
}
/// limpiarPantalla()
/// Devuelve: nada
/// Argumentos: nada
///LIMPIA LA PANTALLA ELIMINANDO LAS ACCIONES ANTERIORES
void limpiarPantalla()
{
    for (int i=0; i!=500; i++)
    {
        cout<<endl;
    }

}
#endif // FUNCIONES_H
