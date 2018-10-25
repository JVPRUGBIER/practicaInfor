/// main.cpp
/// Practica 1 Informatica Industrial
/// Jaime Villa Plaza
/// IEIA 3 CURSO 2018/2019

#include "funciones.h"
#include "Datos.h"

/// librerias

#include <iostream> /// E/S
#include <vector> /// vectores
#include <cmath> /// matematica
#include <fstream> /// ficheros
#include <ctime> /// para mostrar fechas
#include <algorithm> /// para ordenar vectores
#include <iomanip> /// para marcar la precision (setprecision) y para fijarla (fixed)

using namespace std;

int main()
{
    cout<<setprecision(2)<<fixed; ///Precision 2 DECIMALES
do /// Se utiliza para ejecutar el menu una vez y preguntar si quiere volver a ejecutarlo
{
    limpiarPantalla();
    vector <Datos<float>> v;
    cargarVector(v); ///carga los datos del fichero en un vector
    switch(opcion())///llama a la funcion para mostrar el menu
    {
case 1:
    mostrarVector(v);///Saca por pantalla todos los datos
    break;
case 2:
    minymax(v);///Muestra el minimo y el maximo
    break;
case 3:
    IntervaloDeTiempo(v);///Muestra las fechas de captura de datos
    break;
case 4:
    escribeFichero(v);///Pide la identificación de un sensor y nos escribe su info en un fichero
    break;
case 5:
    muestraMediana(v);///Pide la identificación de un sensor y nos muestra la mediana de sus lecturas
    break;
default:
    cout<<"Opcion no valida."<<endl;
    break;
    }
}while(repetir());///Pregunta al usuario si quiere seguir
cout<<"FIN DE PROGRAMA."<<endl;
return 0;
}
