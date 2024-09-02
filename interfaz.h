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
#include "vertice.h" // Incluye la definicion de la clase Vertice de vertice.h
#include "cara.h" // Incluye la definicion de la clase Cara de cara.h

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
    void establecerEnvolventes(std::vector<Envolvente> envolventes);
    void establecerEnvolventeGlobal(Envolvente envolventeGlobal);

    // Métodos operativos
    void cargarObjeto(std::string nombreArchivo);                            // Función para cargar nombre_archivo
    void listado();                                                          // Función para listado
    void listarObjetosEnvolventes();                                         // Función para listar objetos y envolventes
    void envolventeObjeto();                                                 // Función para envolvente nombre_objeto
    void envolvente();                                                       // Función para envolvente
    void descargarObjeto(std::string nombreObjeto);                          // Función para descargar nombre_objeto
    void guardarObjeto(std::string nombreObjeto, std::string nombreArchivo); // Función para guardar nombre_objeto nombre_archivo
    void verticeCercanoEspecifico();                                         // Función para v_cercano px py pz nombre_objeto
    void verticeCercanoGeneral();                                            // Función para v_cercano px py pz
    void verticesCercanosCaja();                                             // Función para v_cercanos_caja nombre_objeto
    void rutaCorta();                                                        // Función para ruta_corta i1 i2 nombre_objeto
    void rutaCortaCentro();                                                  // Función para ruta_corta_centro i1 nombre_objeto

    // Métodos de instancia adicionales
    int posicionObjeto(std::string nombreObjeto);           // Encuentra la posición de un objeto en el vector
    int posicionEnvolvente(std::string nombreObjeto);       // Encuentra la posición de una envolvente en el vector
    void agregarEnvolventeObjeto(std::string nombreObjeto); // Agrega una envolvente a un objeto
    Vertice puntoMinimoGlobal();                            // Encuentra el punto mínimo global
    Vertice puntoMaximoGlobal();                            // Encuentra el punto máximo global
    Envolvente calcularEnvolventeGlobal();                  // Calcula la envolvente global
    void agregarEnvolventeGlobal();                         // Agrega la envolvente global al sistema
    int descargar(std::string nombreObjeto);                // Descarga un objeto
    void procesarComando();                                 // Procesa un comando específico
};

Interfaz::Interfaz() {}

Interfaz::Interfaz(std::vector<Objeto> objetos,
                   std::vector<Envolvente> envolventes,
                   Envolvente envolventeGlobal)
{
    this->objetos = objetos;
    this->envolventes = envolventes;
    this->envolventeGlobal = envolventeGlobal;
}
Interfaz::Interfaz() : envolventeGlobal() {} // Constructor por defecto

// Métodos de acceso

std::string Interfaz::obtenerComando() { return comando; }

std::vector<Objeto> Interfaz::obtenerObjetos() {return objetos;}

std::vector<Envolvente> Interfaz::obtenerEnvolventes() { return envolventes; }

Envolvente Interfaz::obtenerEnvolventeGlobal() { return envolventeGlobal; }

void Interfaz::establecerComando( std::string comando)
{
    this->comando = comando;
}

void Interfaz::establecerObjetos(std::vector<Objeto> objetos)
{
    this->objetos = objetos;
}

void Interfaz::establecerEnvolventes(std::vector<Envolvente> envolventes)
{
    this->envolventes = envolventes;
}

void Interfaz::establecerEnvolventeGlobal(Envolvente envolventeGlobal)
{
    this->envolventeGlobal = envolventeGlobal;
}

void Interfaz::cargarObjeto(std::string nombreArchivo)
{
  // Verifica si el archivo tiene la extensión correcta
  std::string::size_type pos = nombreArchivo.rfind('.');
  if (pos == std::string::npos || nombreArchivo.substr(pos + 1) != "txt")
  {
    std::cout << "Error: El archivo: " << nombreArchivo
              << " no es de extension .txt " << std::endl;
  }

  // Intentar abrir el archivo
  std::ifstream archivo(nombreArchivo);
  if (!archivo.is_open())
  {
    std::cout << "El archivo no existe. El archivo " << nombreArchivo
              << "no existe o es ilegible " << std::endl;
    // return; // sale de la funcion si no puede abrir el archivo
  }

  // lee el nombre del objeto desde el archivo
  std::string linea;
  std::getline(archivo, linea);
  std::string nombre = linea;

  // Verifica si el objeto ya esta cargado en memoria
  int posicion =
      posicionObjeto(nombre); // busca la posicion del objeto en la memoria
  if (posicion != -1)         // si yua esta cargado
  {
    std::cout << "El objeto ya existe. El objeto " << nombre
              << "ya ha sido cargado en memoria" << std::endl;
    archivo.close(); // el archivo se ciuerra antes de salir de la funcion
    // return;// Salir de la funcion si el objeto ya existe
  }

  // crea una instancia de la clase objeto
  Objeto objeto;

  objeto.establecerNombre(nombre);

  // Leer la cantidad de vertices del objeto
  std::getline(archivo, linea); // lee la siguiente linea del archivo
  int cantidadVerticesObjeto =
      std::stoi(linea); // convierte la linea a un entero que representa la
                        // cantidad de vertices

  // establecer la cantidad de vertices
  objeto.establecerCantidadVertices(cantidadVerticesObjeto);

  // Leer las coordenadas de los vertices
  std::vector<Vertice> coordenadasVerticeObjeto; // alamacenar los vertices
  for (int i = 0; i < cantidadVerticesObjeto; i++)
  {
    std::getline(archivo, linea); // lee una linea del archivo
    std::istringstream iss(
        linea); // usa istringstream para leer los datos de la linea
    int x, y, z;
    iss >> x >> y >> z; // lee las coordenadas x, y ,z del vertice
    // iss permite almcenar las coordenadas ej: 10 20 30, con iss en la linea de
    // arriba queda como x sera 10, y sera 20 y z sera 30
    coordenadasVerticeObjeto.push_back(Vertice(x, y, z));
  }
  objeto.establecerCoordenadasVertices(
      coordenadasVerticeObjeto); // guarda los vertices en el objeto

  // leer las caras y calcula la cantidad de aristas
  int cantidadAristasObjeto = 0; // guarda el numero total de aristas
  std::vector<Cara> caras;       // almacena las caras
  while (std::getline(archivo, linea) &&
         linea != "-1") // lee el archivo hasta el encontrar -1
  {
    std::istringstream iss(
        linea); // lee los datos de la linea con ayuda de istringstream
    int cantidadAristasCara;
    iss >> cantidadAristasCara; // Lee la cantidad de aristas de la cara
    cantidadAristasObjeto +=
        cantidadAristasCara; // Suma la contidad del aristas al total
    std::vector<int> indicesVerticesCara(
        cantidadAristasCara);                     // Almacena los indces de los vertices
    for (int i = 0; i < cantidadAristasCara; i++) // recorre cada indice
    {
      iss >> indicesVerticesCara[i]; // lee el indice del vertice
    }
    Cara cara; // crea una instancia de la clase cara
    cara.establecerCantidadAristas(
        cantidadAristasCara); // Indeica la cantidad de aristas en la cara
    cara.establecerIndicesVertices(
        indicesVerticesCara);                     // Indica los indices de los vertices en la cara
    std::vector<Vertice> coordenadasVerticesCara; // Almacena las coordenadas de
                                                  // los vertices de la cara
    for (int indice : indicesVerticesCara)
    {
      int coordenadaX = coordenadasVerticeObjeto[indice].obtenerCoordenadaX();
      int coordenadaY = coordenadasVerticeObjeto[indice].obtenerCoordenadaY();
      int coordenadaZ = coordenadasVerticeObjeto[indice].obtenerCoordenadaZ();

      coordenadasVerticesCara.push_back(
          Vertice(coordenadaX, coordenadaY, coordenadaZ));
    }
    cara.establecerCoordenadasVertices(
        coordenadasVerticesCara); // guarda las coordenadas de los vertices en
                                  // la cara
    caras.push_back(cara);        // agrega la cara al vector caras
  }
  objeto.establecerCantidadAristas(
      cantidadAristasObjeto); // Establece la cantidad total de aristas en el
                              // objeto
  objeto.establecerCantidadCaras(
      caras.size());             // Establece la cantidad de caras dle objeto
  objeto.establecerCaras(caras); // Establece las caras dle objeto

  // agrega el objeto a la lista de objetos
  this->objetos.push_back(objeto); // Agrega el objeto a la lista de objetos

  // Verificar si el objeto se agrego correctamente
  std::cout << "Objeto agregado: " << objeto.obtenerNombre() << std::endl;
  archivo.close(); // Cierra el archivo

  // Mostrar un mensaje de exito
  std::cout << " El objeto: " << nombre
            << " ha sido cargado existosamente desde el archivo "
            << nombreArchivo << std::endl;
}

#endif // INTERFAZ_H
