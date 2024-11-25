#ifndef OBJETO_H
#define OBJETO_H
// Incluye librerias
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
// Incluye la definicion de la clase Vertice de vertice.h
#include "vertice.h"
// Incluye la definicion de la clase Envolvente de envolvente.h
#include "cara.h"
// Incluye la definicion de la clase Envolvente de envolvente.h
#include "envolvente.h"

class Objeto
{
private:
    std::string nombre;
    int cantidadVertices;
    int cantidadAristas;
    int cantidadCaras;
    std::vector<Vertice> coordenadasVertices;
    std::vector<Cara> caras;
    
public:
    // Metodo constructor
    Objeto();


    // Metodos de acceso
    std::string obtenerNombre() const;
    int obtenerCantidadVertices();
    int obtenerCantidadAristas();
    int obtenerCantidadCaras();
    std::vector<Vertice> obtenerCoordenadasVertices();
    std::vector<Cara> obtenerCaras();
    void establecerNombre(std::string& nombreObjeto);
    void establecerCantidadVertices(int cantidadVertices);
    void establecerCantidadAristas(int cantidadAristas);
    void establecerCantidadCaras(int cantidadCaras);
    void establecerCoordenadasVertices(std::vector<Vertice> coordenadasVertices);
    void establecerCaras(std::vector<Cara> caras);
    // Metodos de instancia
    Vertice puntoMinimo();
    Vertice puntoMaximo();
    Envolvente envolvente();
    Envolvente obtenerEnvolvente(); 
    std::vector<std::pair<int,int>> obtenerConexiones(); //obtener conexiones
    double distancia(int a, int b);
};


#endif //OBJETO_H
