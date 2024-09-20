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

