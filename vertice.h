#ifndef VERTICE_H
#define VERTICE_H

class Vertice
{
private:
    int coordenadaX;
    int coordenadaY;
    int coordenadaZ;
public:
    // Metodos constructores
    Vertice();
    Vertice(int coordenadaX, int coordenadaY, int coordenadaZ);
    // Metodos de acceso
    int obtenerCoordenadaX();
    int obtenerCoordenadaY();
    int obtenerCoordenadaZ();
    void establecerCoordenadaX(int coordenadaX);
    void establecerCoordenadaY(int coordenadaY);
    void establecerCoordenadaZ(int coordenadaZ);
};

// Metodo constructor

Vertice::Vertice()
{
    this->coordenadaX = -1;
    this->coordenadaY = -1;
    this->coordenadaZ = -1;
}

Vertice::Vertice(int coordenadaX, int coordenadaY, int coordenadaZ)
{
    this->coordenadaX = coordenadaX;
    this->coordenadaY = coordenadaY;
    this->coordenadaZ = coordenadaZ;
}

// Metodos de acceso

int Vertice::obtenerCoordenadaX()
{
    return coordenadaX;
}

int Vertice::obtenerCoordenadaY()
{
    return coordenadaY;
}

int Vertice::obtenerCoordenadaZ()
{
    return coordenadaZ;
}

void Vertice::establecerCoordenadaX(int coordenadaX)
{
    this->coordenadaX = coordenadaX;
}

void Vertice::establecerCoordenadaY(int coordenadaY)
{
    this->coordenadaY = coordenadaY;
}

void Vertice::establecerCoordenadaZ(int coordenadaZ)
{
    this->coordenadaZ = coordenadaZ;
}

#endif //VERTICE_H
