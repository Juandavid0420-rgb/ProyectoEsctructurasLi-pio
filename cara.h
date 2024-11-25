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
    int obtenerCantidadAristas() const;
    std::vector<int> obtenerIndicesVertices() const;
    std::vector<Vertice> obtenerCoordenadasVertices() const;
    void establecerCantidadAristas(int cantidadAristas);
    void establecerIndicesVertices(std::vector<int> indicesVertices);
    void establecerCoordenadasVertices(std::vector<Vertice> coordenadasVertices);
};


#endif //CARA_H


