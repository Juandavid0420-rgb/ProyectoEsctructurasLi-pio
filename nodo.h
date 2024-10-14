#ifndef NODO_H
#define NODO_H
#include"vertice.h"

class Nodo {
private:
    Vertice dato;
    Nodo *left;
    Nodo *right;
public:
    Nodo(Vertice data);
    int getX();
    int getY();
    int getZ();
    Vertice getVertice();
};

#endif //NODO_H