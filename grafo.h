#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include <list>
#include <stack>
#include "objeto.h"

class grafo {
public:
    grafo(Objeto &objeto); // Constructor que recibe un Objeto y construye el grafo
    ~grafo();              // Destructor para liberar memoria

    // Métodos solicitados
    void setVertices(std::vector<Vertice> v);         // Set para los vértices
    std::vector<Vertice> getVertices();               // Get para los vértices
    size_t cantVertices();                            // Retorna la cantidad de vértices
    size_t cantAristas();                             // Retorna la cantidad de aristas
    int buscarVertice(Vertice vert);                  // Busca un vértice y retorna su posición
    bool insertarVertice(Vertice vert);               // Inserta un vértice
    bool insertarArista(int ori, int des); // Inserta una arista con costo opcional
    void mostrarMatrizAdyacencia();                   // Muestra la matriz de adyacencia
    std::vector<int> rutaCorta(std:: string &origen, std:: string &destino);
    int minDistancia(std::vector<int>& dist, std::vector<bool>& pred);
    double distanciaRuta (std:: vector<int>ruta);
    Vertice centroide();

private:
    Objeto obj;
    std::vector<Vertice> vertices; // lista de vértices
    double **aristas;                   // matriz de adyacencia (memoria dinámica)
    size_t cantidadVertices;
    size_t cantidadAristas;

    void inicializarMatriz(); // Inicializa la matriz de adyacencia

};

#endif // GRAFO_H

