#ifndef INTERFAZ_H
#define INTERFAZ_H

// Incluye librerias
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "objeto.h"     /// Incluye la definicion de la clase Objeto de objeto.h
#include "envolvente.h" // Incluye la definicion de la clase Envolvente de envolvente.h
#include "vertice.h"    // Incluye la definicion de la clase Vertice de vertice.h
#include "cara.h"       // Incluye la definicion de la clase Cara de cara.h

using namespace std;

class Interfaz
{
private:
    std::string comando;
    std::vector<Objeto> objetos;
    std::vector<Envolvente> envolventes;
    Envolvente envolventeGlobal;

public:
    // Métodos constructores
    Interfaz();
    Interfaz(std::vector<Objeto> objetos, std::vector<Envolvente> envolventes,
             Envolvente envolventeGlobal);

    // Métodos de acceso
    std::string obtenerComando();
    std::vector<Objeto> obtenerObjetos();
    std::vector<Envolvente> obtenerEnvolventes();
    Envolvente obtenerEnvolventeGlobal();
    void establecerComando(std::string comando);
    void establecerObjetos(std::vector<Objeto> objetos);
    void establecerObjeto(Objeto objeto);
    void establecerEnvolventes(std::vector<Envolvente> envolventes);
    void establecerEnvolventeGlobal(Envolvente envolventeGlobal);

    // Métodos operativos
    void cargarArchivo(std::string nombreArchivo);                            // Función para cargar nombre_archivo
    void listado();                                                          // Función para listado
    void listarObjetosEnvolventes();                                         // Función para listar objetos y envolventes
    void descargarArchivo(std::string nombreObjeto);                          // Función para descargar nombre_objeto
    void guardarArchivo(std::string nombreObjeto, std::string nombreArchivo); // Función para guardar nombre_objeto nombre_archivo
    //  void v_Cercano(int CoordenadaX,int CoordenadaY,int CoordenadaZ,std::string nombreObjeto);   
    //   void v_cercano(int CoordenadaX,int CoordenadaY,int CoordenadaZ);                                 // Función para v_cercano px py pz nombre_objeto
    //  void v_Cercano_Caja(std::string nombreObjeto);                                             // Función para v_cercanos_caja nombre_objeto
    // void rutaCorta();                                                        // Función para ruta_corta i1 i2 nombre_objeto
    // void rutaCortaCentro();                                                  // Función para ruta_corta_centro i1 nombre_objeto

    // Métodos de instancia adicionales
    int posicionObjeto(std::string nombreObjeto);           // Encuentra la posición de un objeto en el vector
    int posicionEnvolvente(std::string nombreObjeto);       // Encuentra la posición de una envolvente en el vector
    void agregarEnvolventeObjeto(std::string nombreObjeto); // Agrega una envolvente a un objeto
    Vertice puntoMinimoGlobal();                            // Encuentra el punto mínimo global
    Vertice puntoMaximoGlobal();                            // Encuentra el punto máximo global
    Envolvente calcularEnvolventeGlobal();                  // Calcula la envolvente global
    void agregarEnvolventeGlobal();                         // Agrega la envolvente global al sistema
    int descargar(std::string nombreObjeto);
       //void procesarComando();                                 // Procesa un comando específico
};
//Interfaz::Interfaz() : envolventeGlobal() {} // Constructor por defecto

#endif // INTERFAZ_H
