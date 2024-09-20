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


#endif //VERTICE_H
