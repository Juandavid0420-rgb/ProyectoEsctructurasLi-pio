#ifndef VERTICE_H
#define VERTICE_H
#include "cmath"
class Vertice
{

public:

int coordenadaX;
    int coordenadaY;
    int coordenadaZ;
    // Metodos constructores
    Vertice();
    Vertice(int coordenadaX, int coordenadaY, int coordenadaZ);
    // Metodos de acceso
    int obtenerCoordenadaX() ;
    int obtenerCoordenadaZ() ;
    int obtenerCoordenadaY() ;
    void establecerCoordenadaX(int coordenadaX);
    void establecerCoordenadaY(int coordenadaY);
    void establecerCoordenadaZ(int coordenadaZ);
    // Método para calcular la distancia entre dos vértices
    float distancia(const Vertice& otro) const {
        return std::sqrt(std::pow(coordenadaX - otro.coordenadaX, 2) +
                         std::pow(coordenadaY - otro.coordenadaY, 2) +
                         std::pow(coordenadaZ - otro.coordenadaZ, 2));
    }
};


#endif //VERTICE_H
