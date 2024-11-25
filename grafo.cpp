#include "grafo.h"
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include <iomanip>
#include <climits>
#include <stack>
#include "objeto.h"

using namespace std;

// Constructor
grafo::grafo(Objeto &objeto)
{
    obj = objeto;

    cantidadVertices = objeto.obtenerCantidadVertices(); // Obtiene la cantidad de vértices del objeto

    std::cout << "Construyendo grafo..." << std::endl;

    // Obtener los vértices primero
    std::vector<Vertice> verticesObjeto = objeto.obtenerCoordenadasVertices();
    vertices = verticesObjeto;
    // Comprobar si hay vértices

    if (verticesObjeto.empty())
    {
        std::cout << "Error: El objeto no contiene vértices" << std::endl;
        return;
    }

    // Asignar la cantidad de vértices basada en el tamaño real del vector
    cantidadVertices = verticesObjeto.size();

    std::cout << "Cantidad de vertices encontrados: " << cantidadVertices << std::endl;

    // Inicializar la matriz con el tamaño correcto

    inicializarMatriz();

    // Crear las conexiones entre vértices
    std::vector<std::pair<int, int>> conexiones = objeto.obtenerConexiones();
    //    for (const auto& par : conexiones) {
    //         std::cout << "(" << par.first << ", " << par.second << ")" << std::endl;
    //     }

    for (const auto &conexion : conexiones)
    {
        insertarArista(conexion.first, conexion.second);
    }

    std::cout << "Matriz de adyacencia inicializada con " << cantidadVertices
              << " vertices. " << std::endl;
}

grafo::~grafo()
{
    // Libera memoria de la matriz de adyacencia
    for (int i = 0; i < cantidadVertices; i++)
    {
        delete[] aristas[i];
    }
    delete[] aristas;
}

// Inicializa la matriz de adyacencia
void grafo::inicializarMatriz()
{
    if (cantidadVertices <= 0)
    {
        std::cout << "Error: Cantidad de vertices invalida" << std::endl;
        return;
    }
    // memoria para la matriz
    aristas = new double *[cantidadVertices];
    for (int i = 0; i < cantidadVertices; i++)
    {
        aristas[i] = new double[cantidadVertices];
        // la matriz comienza con todos sus  valores en 0

        for (int j = 0; j < cantidadVertices; j++)
        {
            if (i == j)
            {
                aristas[i][j] = 1; // asigna 1 si estamos en la diagonal de la matriz
            }
            else
            {
                aristas[i][j] = 0; // asigna 0 a los demas elementos de la matriz
            }
        }
    }

    std::cout << "Matriz inicializada correctamente" << std::endl;
}

// Muestra la matriz
void grafo::mostrarMatrizAdyacencia()
{
    if (cantidadVertices <= 0)
    {
        std::cout << "El grafo esta vacio (no hay vertices)" << std::endl;
        return;
    }

    if (aristas == nullptr)
    {
        std::cout << "La matriz de aristas no está inicializada" << std::endl;
        return;
    }

    // Verifica que cada fila de la matriz esté inicializada
    for (int i = 0; i < cantidadVertices; i++)
    {
        if (aristas[i] == nullptr)
        {
            std::cout << "Error: La fila " << i << " de la matriz no está inicializada" << std::endl;
            return;
        }
    }

    // Muestra la matriz
    std::cout << "Matriz de Adyacencia (" << cantidadVertices << "x" << cantidadVertices << "):" << std::endl;

    std::cout << "   ";
    for (int j = 0; j < cantidadVertices; j++)
    {
        std::cout << j << " "; // Muestra el índice de columnas
    }
    std::cout << std::endl;

    for (int i = 0; i < cantidadVertices; i++)
    {
        std::cout << std::setw(3) << i << ": "; // Muestra el índice de la fila
        for (int j = 0; j < cantidadVertices; j++)
        {
            double dist = aristas[i][j];
            // Verificamos si el valor es entero
            if (dist == static_cast<int>(dist))
            {
                std::cout << std::setw(7)<< static_cast<int>(dist) ; // mosrar como entero
            }
            else
            {
                std::cout << std::setw(7)<< std::fixed << std::setprecision(2) << dist  ; // mostrar como 2 decimales
            }
        }
        std::cout << std::endl;
    }
}

// insertar una arista
bool grafo::insertarArista(int ori, int des)
{ // verifica si los indices estan dentro del  rango

    if (ori < 0 || ori >= cantidadVertices || des < 0 || des >= cantidadVertices)
    {
        std::cout << "Error: Índices fuera de rango (" << ori << ", " << des << ")" << std::endl;
        return false; // Índices fuera de rango
    }
    double dist = obj.distancia(ori, des);
    // le pone costo ala arista en ambas direcciones
    aristas[ori][des] = dist + 1;
    aristas[des][ori] = dist + 1;
    return true;
}

std::vector<int> grafo::rutaCorta(std::string &origen, std::string &destino)
{
    const int INF = INT_MAX;
    int tam = vertices.size();
    vector<int> dist(tam, INF);  // dist[i] guarda la distancia mínima desde src hasta i
    vector<bool> SQ(tam, false); // SQ[i] será verdadero si el vértice i está incluido en el árbol de caminos más cortos
    vector<int> pred(tam);

    int orig = stoi(origen);
    int dest = stoi(destino);
    dist[orig] = 0; // La distancia del nodo fuente a sí mismo es siempre 0

    // Encuentra el camino más corto para todos los vértices
    for (int j = 0; j < tam - 1; j++)
    {
        int u = minDistancia(dist, SQ);
        SQ[u] = true;

        // Actualiza el valor de distancia de los vértices adyacentes al vértice seleccionado
        for (int v = 0; v < tam; v++)
        {
            if (!SQ[v] && aristas[u][v] && dist[u] != INF && dist[u] + aristas[u][v] < dist[v])
            {
                dist[v] = dist[u] + aristas[u][v] - 1;
                pred[v] = u;
            }
        }
    }
    // recorre la linea de predecesores hasta encontrar el camino, esta parte es la que hace la funcion
    std::vector<int> ruta;
    ruta.push_back(dest);
    int d = dest;
    while (d != orig)
    {
        d = pred[d];
        ruta.push_back(d);
    }

    // Imprime la distancia desde el nodo fuente a cada nodo
    cout << "Nodo\tDistancia desde la fuente\tPredecesor" << endl;
    for (int i = 0; i < tam; i++)
    {
        cout << i << "\t" << (dist[i] == INF ? "INF" : to_string(dist[i])) << "\t" << pred[i] << endl;
    }

    return ruta;
}

int grafo::minDistancia(vector<int> &dist, vector<bool> &SQ)
{
    const int INF = INT_MAX;
    int min = INF, min_index = -1;

    for (int v = 0; v < vertices.size(); v++)
    {
        if (!SQ[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

double grafo::distanciaRuta(std::vector<int> ruta)
{
    double dist;
    int h = ruta.size();
    if (h < 2)
    {
        return 0.0;
    }
    for (int i = 0; i < h - 1; i++)
    {
        int origen = ruta[i];
        int destino = ruta[i + 1];
        double d = obj.distancia(origen, destino);
        dist += d;
    }
    return dist;
}

Vertice grafo::centroide()
{
    int sumaX = 0;
    int sumaY = 0;
    int sumaZ = 0;
    int n = obj.obtenerCantidadVertices();
    vector<Vertice> puntos = obj.obtenerCoordenadasVertices();

    for (int i = 0; i < n; i++)
    {
        int X = puntos[i].obtenerCoordenadaX(); // Suma de coordenadas x
        sumaX += X;
        int Y = puntos[i].obtenerCoordenadaY(); // Suma de coordenadas y
        sumaY += Y;
        int Z = puntos[i].obtenerCoordenadaZ(); // Suma de coordenadas z
        sumaZ += Z;
    }

    sumaX = sumaX / n;
    sumaY = sumaY / n;
    sumaZ = sumaZ / n;

    Vertice centro(sumaX, sumaY, sumaZ);
    return centro;
}
