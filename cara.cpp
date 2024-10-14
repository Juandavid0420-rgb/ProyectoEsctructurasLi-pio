#include "cara.h"


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



