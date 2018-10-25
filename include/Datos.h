/// Datos.h
/// Practica 1 Informatica Industrial
/// Jaime Villa Plaza
/// IEIA 3 CURSO 2018/2019

#ifndef DATOS_H
#define DATOS_H

/// includes .h
#include "Datos.h"
#include "funciones.h"


/// librerias

#include <iostream> /// E/S
#include <vector> /// vectores
#include <cmath> /// matematica
#include <fstream> /// ficheros
#include <ctime> /// para mostrar fechas
#include <algorithm> /// para ordenar vectores
#include <iomanip> /// para marcar la precision

using namespace std;

/// CONSTANTES SIMBÓLICAS DE ERROR
const int ERROR_OPENING_FILE = 1;
const int ERROR_NO_SENSOR = 2;

/// Definicion
template <typename T>
class Datos
{
    string referencia;
    T lectura;
    long tiempo;

public:

    ///Constructores
    Datos (string r, T l, long t)
    {
        referencia = r;
        lectura = l;
        tiempo = t;
    }
    Datos ()
    {
        referencia = "SensorNoDetectado";
        lectura = 0.0;
        tiempo = 0.0;
    }

    /// operator<
    /// Devuelve: una variable booleana
    /// Argumentos: una clase "Datos" templatizada
    /// sobrecargamos el operador <
    bool operator< (const Datos<T> &d)
    {
        if (lectura<d.lectura)
            return true;
        else
            return false;
    }

    /// operator>
    /// Devuelve: una variable booleana
    /// Argumentos: una clase "Datos" templatizada
    /// sobrecargamos el operador >
    bool operator> (const Datos<T> &d)
    {
        if (lectura>d.lectura)
            return true;
        else
            return false;
    }

    /// Funciones friend templatizadas

    template <typename U> bool operator< (const Datos<U> &d);
    template <typename U> bool operator> (const Datos<U> &d);
    template <typename U> friend ifstream& operator>> (ifstream &fich, Datos<U> &d);
    template <typename U> friend ofstream& operator<< (ofstream &fich, Datos<U> &d);
    template <typename U> friend ostream& operator<< (ostream &out, Datos<U> &d);
    template <typename U> friend void minymax (vector<Datos<U>> &v);
    template <typename U> friend void IntervaloDeTiempo (vector<Datos<U>> &v);
    template <typename U> friend void muestraMediana (vector<Datos<U>> &v);
    template <typename U> friend void escribeFichero (vector<Datos<U>> &v);





};
#endif // DATOS_H
