#include"objeto.h"

// Metodos de instancia
// Metodo constructor

Objeto::Objeto()
{

}

//Métodos de acceso

std::string Objeto::obtenerNombre() 
{
    return nombre;
}

int Objeto::obtenerCantidadVertices()
{
    return cantidadVertices;
}

int Objeto::obtenerCantidadAristas()
{
    return cantidadAristas;
}

int Objeto::obtenerCantidadCaras()
{
    return cantidadCaras;
}

std::vector<Vertice> Objeto::obtenerCoordenadasVertices()
{
    return coordenadasVertices;
}

std::vector<Cara> Objeto::obtenerCaras()
{
    return caras;
}

void Objeto::establecerNombre(std::string& nombreObjeto)
{
    nombre = nombreObjeto;
}

void Objeto::establecerCantidadVertices(int cantidadVertices)
{
    this->cantidadVertices = cantidadVertices;
}

void Objeto::establecerCantidadAristas(int cantidadAristas)
{
    this->cantidadAristas = cantidadAristas;
}

void Objeto::establecerCantidadCaras(int cantidadCaras)
{
    this->cantidadCaras = cantidadCaras;
}

void Objeto::establecerCoordenadasVertices(std::vector<Vertice> coordenadasVertices)
{
    this->coordenadasVertices = coordenadasVertices;
}

void Objeto::establecerCaras(std::vector<Cara> caras)
{
    this->caras = caras;
}

Vertice Objeto::puntoMinimo()
{
    Vertice verticeMinimo;

    if (this->coordenadasVertices.empty())
    {
        return verticeMinimo;  // Retorna un vertice con coordenadas (-1,-1,-1) si no hay vertices
    }

    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int minZ = std::numeric_limits<int>::max();

    for(int i = 0; i < this->coordenadasVertices.size(); i++)
    {
        minX = std::min(minX, this->coordenadasVertices[i].obtenerCoordenadaX());
        minY = std::min(minY, this->coordenadasVertices[i].obtenerCoordenadaY());
        minZ = std::min(minZ, this->coordenadasVertices[i].obtenerCoordenadaZ());
    }

    verticeMinimo.establecerCoordenadaX(minX);
    verticeMinimo.establecerCoordenadaY(minY);
    verticeMinimo.establecerCoordenadaZ(minZ);

    return verticeMinimo;
}

Vertice Objeto::puntoMaximo(){
    Vertice verticeMaximo;

    if (this->coordenadasVertices.empty())
    {
        return verticeMaximo;  // Retorna un vertice con coordenadas (-1,-1,-1) si no hay vertices
    }

    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    int maxZ = std::numeric_limits<int>::min();

    for(int i = 0; i < this->coordenadasVertices.size(); i++)
    {
        maxX = std::max(maxX, this->coordenadasVertices[i].obtenerCoordenadaX());
        maxY = std::max(maxY, this->coordenadasVertices[i].obtenerCoordenadaY());
        maxZ = std::max(maxZ, this->coordenadasVertices[i].obtenerCoordenadaZ());
    }

    verticeMaximo.establecerCoordenadaX(maxX);
    verticeMaximo.establecerCoordenadaY(maxY);
    verticeMaximo.establecerCoordenadaZ(maxZ);

    return verticeMaximo;
}

Envolvente Objeto::envolvente()
{
    Envolvente envolvente;

    if(puntoMinimo().obtenerCoordenadaX() < 0 || puntoMaximo().obtenerCoordenadaX() < 0)
    {
        return envolvente;
    }

    std::string prefijo = "env_";
    std::string sufijo = this->nombre;
    std::string nombreEnvolvente = prefijo + sufijo;

    envolvente.establecerNombre(nombreEnvolvente);
    envolvente.establecerPuntoMinimo(puntoMinimo());
    envolvente.establecerPuntoMaximo(puntoMaximo());

    return envolvente;
}

Envolvente Objeto::obtenerEnvolvente()  {
    return envolvente();
}

