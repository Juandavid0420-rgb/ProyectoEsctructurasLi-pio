#include "envolvente.h"

// Metodo constructor

Envolvente::Envolvente()
{
    this->puntoMinimo.establecerCoordenadaX(-1);
    this->puntoMinimo.establecerCoordenadaY(-1);
    this->puntoMinimo.establecerCoordenadaZ(-1);
    this->puntoMaximo.establecerCoordenadaX(-1);
    this->puntoMaximo.establecerCoordenadaY(-1);
    this->puntoMaximo.establecerCoordenadaZ(-1);
}


Envolvente::Envolvente(Vertice puntoMinimo, Vertice puntoMaximo)
{
    this->puntoMinimo = puntoMinimo;
    this->puntoMaximo = puntoMaximo;
}

//Métodos de acceso

std::string Envolvente::obtenerNombre()
{
    return nombre;
}

Vertice Envolvente::obtenerPuntoMaximo()
{
    return puntoMaximo;
}

Vertice Envolvente::obtenerPuntoMinimo()
{
    return puntoMinimo;
}

void Envolvente::establecerNombre(std::string nombre)
{
    this->nombre = nombre;
}

void Envolvente::establecerPuntoMaximo(Vertice puntoMaximo)
{
    this->puntoMaximo = puntoMaximo;
}

void Envolvente::establecerPuntoMinimo(Vertice puntoMinimo)
{
    this->puntoMinimo = puntoMinimo;
}

//Obtener las 8 esquinas de la caja
std::vector<Vertice> Envolvente::obtenerEsquinas() {
    std::vector<Vertice> esquinas;
    int xmin = puntoMinimo.obtenerCoordenadaX();
    int ymin = puntoMinimo.obtenerCoordenadaY();
    int zmin = puntoMinimo.obtenerCoordenadaZ();
    int xmax = puntoMaximo.obtenerCoordenadaX();
    int ymax = puntoMaximo.obtenerCoordenadaY();
    int zmax = puntoMaximo.obtenerCoordenadaZ();

// si el objeto es plano XY (zmin == zmax), solo genera esquinas en este plano
if (zmin==zmax)
{

    esquinas.push_back(Vertice(xmin, ymin, zmin));
    esquinas.push_back(Vertice(xmin, ymax, zmin));
    esquinas.push_back(Vertice(xmax, ymin, zmin));
    esquinas.push_back(Vertice(xmax, ymax, zmin));
} else
{
   // 8 posibles combinaciones de un objeto 3D
    esquinas.push_back(Vertice(xmin,ymin,zmin));
    esquinas.push_back(Vertice(xmin,ymin,zmax));
    esquinas.push_back(Vertice(xmin,ymax,zmin));
    esquinas.push_back(Vertice(xmin,ymax,zmax));
    esquinas.push_back(Vertice(xmax,ymin,zmin));
    esquinas.push_back(Vertice(xmax,ymin,zmax));
    esquinas.push_back(Vertice(xmax,ymax,zmin));
    esquinas.push_back(Vertice(xmax,ymax,zmax));
}

 


return esquinas;

}
