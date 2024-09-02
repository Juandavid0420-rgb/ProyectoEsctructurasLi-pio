#ifndef CARA_H
#define CARA_H
// Incluye librerias
#include <vector>
// Incluye la definicion de la clase Vertice de vertice.h
#include "vertice.h"


class Cara
{
private:
    int cantidadAristas;
    std::vector<int> indicesVertices;
    std::vector<Vertice> coordenadasVertices;
public:
    // Metodo constructor
    Cara();
    // Metodos de acceso
    int obtenerCantidadAristas();
    std::vector<int> obtenerIndicesVertices();
    std::vector<Vertice> obtenerCoordenadasVertices();
    void establecerCantidadAristas(int cantidadAristas);
    void establecerIndicesVertices(std::vector<int> indicesVertices);
    void establecerCoordenadasVertices(std::vector<Vertice> coordenadasVertices);
};

// Metodo constructor

Cara::Cara()
{

}

//Métodos de acceso

int Cara::obtenerCantidadAristas()
{
    return cantidadAristas;
}

std::vector<int> Cara::obtenerIndicesVertices()
{
    return indicesVertices;
}

std::vector<Vertice> Cara::obtenerCoordenadasVertices()
{
    return coordenadasVertices;
}

void Cara::establecerCantidadAristas(int cantidadAristas)
{
    this->cantidadAristas = cantidadAristas;
}

void Cara::establecerIndicesVertices(std::vector<int> indicesVertices)
{
    this->indicesVertices = indicesVertices;
}

void Cara::establecerCoordenadasVertices(std::vector<Vertice> coordenadasVertices)
{
    this->coordenadasVertices = coordenadasVertices;
}

#endif //CARA_H
