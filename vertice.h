#ifndef VERTICE_H
#define VERTICE_H

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
    int obtenerCoordenadaX();
    int obtenerCoordenadaY();
    int obtenerCoordenadaZ();
    void establecerCoordenadaX(int coordenadaX);
    void establecerCoordenadaY(int coordenadaY);
    void establecerCoordenadaZ(int coordenadaZ);
    //Metodo de Comparacion
    bool esIgual(const Vertice& otroVertice);
};


#endif //VERTICE_H
