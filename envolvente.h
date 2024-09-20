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

#endif //ENVOLVENTE_H