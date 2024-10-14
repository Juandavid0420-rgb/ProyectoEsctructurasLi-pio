#include"nodo.h"



Nodo::Nodo(Vertice data){
    this->dato = data;
}

int Nodo::getX(){
    return dato.obtenerCoordenadaX();
}

int Nodo::getY(){
    return dato.obtenerCoordenadaY();
}

int Nodo::getZ(){
    return dato.obtenerCoordenadaZ();
}

Vertice Nodo::getVertice(){
    return dato;
}