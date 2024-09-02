#ifndef ENVOLVENTE_H
#define ENVOLVENTE_H
// Incluye librerias
#include <string>
// Incluye la definicion de la clase Vertice de vertice.h
#include "vertice.h"

class Envolvente
{
private:
    std::string nombre;
    Vertice puntoMinimo;
    Vertice puntoMaximo;
public:
    // Metodos constructores
    Envolvente();
    Envolvente(Vertice puntoMinimo, Vertice puntoMaximo);
    // Metodos de acceso
    std::string obtenerNombre();
    Vertice obtenerPuntoMinimo();
    Vertice obtenerPuntoMaximo();
    void establecerNombre(std::string nombre);
    void establecerPuntoMinimo(Vertice puntoMinimo);
    void establecerPuntoMaximo(Vertice puntoMaximo);
};

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

#endif //ENVOLVENTE_H