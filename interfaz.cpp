#include "interfaz.h"


Interfaz::Interfaz() {}

Interfaz::Interfaz(std::vector<Objeto> objetos,
                   std::vector<Envolvente> envolventes,
                   Envolvente envolventeGlobal)
{
  this->objetos = objetos;
  this->envolventes = envolventes;
  this->envolventeGlobal = envolventeGlobal;
}

std::string Interfaz::obtenerComando() { return comando; }

std::vector<Objeto> Interfaz::obtenerObjetos() { return objetos; }

std::vector<Envolvente> Interfaz::obtenerEnvolventes() { return envolventes; }

Envolvente Interfaz::obtenerEnvolventeGlobal() { return envolventeGlobal; }

void Interfaz::establecerComando(std::string comando)
{
  this->comando = comando;
}

void Interfaz::establecerObjetos(std::vector<Objeto> objetos)
{
  this->objetos = objetos;
}

void Interfaz::establecerObjeto(Objeto objeto)
{
  this->objetos.push_back(objeto);
}

void Interfaz::establecerEnvolventes(std::vector<Envolvente> envolventes)
{
  this->envolventes = envolventes;
}

void Interfaz::establecerEnvolventeGlobal(Envolvente envolventeGlobal)
{
  this->envolventeGlobal = envolventeGlobal;
}

void Interfaz::cargarArchivo(std::string nombreArchivo)
{
  std::cout << nombreArchivo << std::endl;
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

void Interfaz::listado()
{
  std::cout << "Listado de objetos cargados en memoria: " << std::endl;

  if (objetos.empty())
  {
    std::cout << "Ningun objeto ha sido cargado en memoria";
  }
  else
  {
    std::cout << "Hay " << objetos.size() << " objetos en memoria" << std::endl
              << std::endl;
    for (auto &objeto : objetos)
    {
      std::cout << " - " << objeto.obtenerNombre()
                << " contiene: " << objeto.obtenerCantidadVertices()
                << " vertices, " << objeto.obtenerCantidadAristas()
                << " aristas y " << objeto.obtenerCantidadCaras()
                << " caras" << std::endl;
    }
  }
};

void Interfaz::listarObjetosEnvolventes()
{
  int cantidadObjetos = this->objetos.size();
  int cantidadEnvolventes = this->envolventes.size();
  int totalObjetos = cantidadObjetos + cantidadEnvolventes;
  if (this->envolventeGlobal.obtenerPuntoMaximo().obtenerCoordenadaX() > 0)
  {
    totalObjetos++;
  }

  if (cantidadObjetos <= 0 && cantidadEnvolventes <= 0)
  {
    std::cout << "Memoria vacia. Ningun objeto ha sido cargado en memoria"
              << std::endl;
    return;
  }

  std::cout << "Resultado existoso. Hay " << totalObjetos
            << " objetos en memoria:" << std::endl
            << std::endl;

  for (auto &objeto : this->objetos)
  {
    std::cout << objeto.obtenerNombre() << " contiene "
              << objeto.obtenerCantidadVertices() << " vertices, "
              << objeto.obtenerCantidadAristas() << " aristas y "
              << objeto.obtenerCantidadCaras() << " caras" << std::endl;

    std::cout << "Coordenadas de los vertices:" << std::endl;
    for (auto &vertice : objeto.obtenerCoordenadasVertices())
    {
      std::cout << vertice.obtenerCoordenadaX() << " "
                << vertice.obtenerCoordenadaY() << " "
                << vertice.obtenerCoordenadaZ() << std::endl;
    }

    std::cout << "Aristas e indices de las caras:" << std::endl;
    for (auto &cara : objeto.obtenerCaras())
    {
      std::cout << cara.obtenerCantidadAristas() << " ";
      for (int indice : cara.obtenerIndicesVertices())
      {
        std::cout << indice << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  for (auto &envolvente : this->envolventes)
  {
    std::cout << envolvente.obtenerNombre() << std::endl;
    std::cout << "Punto Minimo: "
              << envolvente.obtenerPuntoMinimo().obtenerCoordenadaX() << ", "
              << envolvente.obtenerPuntoMinimo().obtenerCoordenadaY() << ", "
              << envolvente.obtenerPuntoMinimo().obtenerCoordenadaZ()
              << std::endl;
    std::cout << "Punto Maximo: "
              << envolvente.obtenerPuntoMaximo().obtenerCoordenadaX() << ", "
              << envolvente.obtenerPuntoMaximo().obtenerCoordenadaY() << ", "
              << envolvente.obtenerPuntoMaximo().obtenerCoordenadaZ()
              << std::endl;
    std::cout << std::endl;
  }

  if (this->envolventeGlobal.obtenerPuntoMinimo().obtenerCoordenadaX() != -1)
  {
    std::cout << this->envolventeGlobal.obtenerNombre() << std::endl;
    std::cout
        << "Punto Minimo: "
        << this->envolventeGlobal.obtenerPuntoMinimo().obtenerCoordenadaX()
        << ", "
        << this->envolventeGlobal.obtenerPuntoMinimo().obtenerCoordenadaY()
        << ", "
        << this->envolventeGlobal.obtenerPuntoMinimo().obtenerCoordenadaZ()
        << std::endl;
    std::cout
        << "Punto Maximo: "
        << this->envolventeGlobal.obtenerPuntoMaximo().obtenerCoordenadaX()
        << ", "
        << this->envolventeGlobal.obtenerPuntoMaximo().obtenerCoordenadaY()
        << ", "
        << this->envolventeGlobal.obtenerPuntoMaximo().obtenerCoordenadaZ()
        << std::endl;
  }
}

int Interfaz::posicionEnvolvente(std::string nombreObjeto)
{
  for (int i = 0; i < this->envolventes.size(); i++)
  {
    if (this->envolventes[i].obtenerNombre() == nombreObjeto)
    {
      return i;
    }
  }
  return -1;
}

int Interfaz::posicionObjeto(std::string nombreObjeto)
{
  for (int i = 0; i < this->objetos.size(); i++)
  {
    if (this->objetos[i].obtenerNombre() == nombreObjeto)
    {
      return i;
    }
  }
  return -1;
}

void Interfaz::agregarEnvolventeObjeto(std::string nombreObjeto)
{
  int objetoPosicion = posicionObjeto(nombreObjeto);

  if (objetoPosicion == -1)
  {
    std::cout << "Objeto no existe. El objeto " << nombreObjeto
              << " no ha sido cargado en memoria" << std::endl;
    return;
  }

  int envolventePosicion = posicionEnvolvente(nombreObjeto);

  if (envolventePosicion != -1)
  {
    std::cout << "Envolvente ya existe. El envolvente de " << nombreObjeto
              << " ya ha sido cargado en memoria" << std::endl;
    return;
  }

  Envolvente envolventeObjeto = this->objetos[objetoPosicion].envolvente();

  if (envolventeObjeto.obtenerPuntoMaximo().obtenerCoordenadaX() >= 0)
  {
    this->envolventes.push_back(envolventeObjeto);
    std::cout << "Resultado exitoso. La caja envolvente del objeto "
              << nombreObjeto << " se ha generado con el" << std::endl;
    std::cout << "nombre " << envolventeObjeto.obtenerNombre()
              << " y se ha agregado a los objetos en memoria" << std::endl;
    std::cout << "Punto minimo: "
              << envolventeObjeto.obtenerPuntoMinimo().obtenerCoordenadaX()
              << " "
              << envolventeObjeto.obtenerPuntoMinimo().obtenerCoordenadaY()
              << " "
              << envolventeObjeto.obtenerPuntoMinimo().obtenerCoordenadaZ()
              << std::endl;
    std::cout << "Punto maximo: "
              << envolventeObjeto.obtenerPuntoMaximo().obtenerCoordenadaX()
              << " "
              << envolventeObjeto.obtenerPuntoMaximo().obtenerCoordenadaY()
              << " "
              << envolventeObjeto.obtenerPuntoMaximo().obtenerCoordenadaZ()
              << std::endl;
  }
}

Vertice Interfaz::puntoMinimoGlobal()
{
  Vertice verticeMinimoGlobal;

  if (this->objetos.empty())
  {
    return verticeMinimoGlobal;
  }

  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();
  int minZ = std::numeric_limits<int>::max();

  for (int i = 0; i < this->objetos.size(); i++)
  {
    for (int j = 0; j < this->objetos[i].obtenerCoordenadasVertices().size();
         j++)
    {
      minX = std::min(minX, this->objetos[i]
                                .obtenerCoordenadasVertices()[j]
                                .obtenerCoordenadaX());
      minY = std::min(minY, this->objetos[i]
                                .obtenerCoordenadasVertices()[j]
                                .obtenerCoordenadaY());
      minZ = std::min(minZ, this->objetos[i]
                                .obtenerCoordenadasVertices()[j]
                                .obtenerCoordenadaZ());
    }
  }

  verticeMinimoGlobal.establecerCoordenadaX(minX);
  verticeMinimoGlobal.establecerCoordenadaY(minY);
  verticeMinimoGlobal.establecerCoordenadaZ(minZ);

  return verticeMinimoGlobal;
}

Vertice Interfaz::puntoMaximoGlobal()
{
  Vertice verticeMaximoGlobal;

  if (this->objetos.empty())
  {
    return verticeMaximoGlobal;
  }

  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
  int maxZ = std::numeric_limits<int>::min();

  for (int i = 0; i < this->objetos.size(); i++)
  {
    for (int j = 0; j < this->objetos[i].obtenerCoordenadasVertices().size();
         j++)
    {
      maxX = std::max(maxX, this->objetos[i]
                                .obtenerCoordenadasVertices()[j]
                                .obtenerCoordenadaX());
      maxY = std::max(maxY, this->objetos[i]
                                .obtenerCoordenadasVertices()[j]
                                .obtenerCoordenadaY());
      maxZ = std::max(maxZ, this->objetos[i]
                                .obtenerCoordenadasVertices()[j]
                                .obtenerCoordenadaZ());
    }
  }

  verticeMaximoGlobal.establecerCoordenadaX(maxX);
  verticeMaximoGlobal.establecerCoordenadaY(maxY);
  verticeMaximoGlobal.establecerCoordenadaZ(maxZ);

  return verticeMaximoGlobal;
}

Envolvente Interfaz::calcularEnvolventeGlobal()
{
  Envolvente nulo;
  if (this->objetos.empty())
  {
    std::cout << "No hay objetos en la lista." << std::endl;
    return nulo;
  }

  // Inicializar los valores mínimos y máximos con las coordenadas del primer objeto
  Objeto primerObjeto = this->objetos[0];
  int xMin = primerObjeto.obtenerCoordenadasVertices()[0].obtenerCoordenadaX();
  int xMax = xMin;
  int yMin = primerObjeto.obtenerCoordenadasVertices()[0].obtenerCoordenadaY();
  int yMax = yMin;
  int zMin = primerObjeto.obtenerCoordenadasVertices()[0].obtenerCoordenadaZ();
  int zMax = zMin;

  // Recorrer cada objeto
  for (auto &objeto : this->objetos)
  {
    for (auto &vertice : objeto.obtenerCoordenadasVertices())
    {
      // Actualizar mínimos y máximos para cada eje
      xMin = std::min(xMin, vertice.obtenerCoordenadaX());
      xMax = std::max(xMax, vertice.obtenerCoordenadaX());
      yMin = std::min(yMin, vertice.obtenerCoordenadaY());
      yMax = std::max(yMax, vertice.obtenerCoordenadaY());
      zMin = std::min(zMin, vertice.obtenerCoordenadaZ());
      zMax = std::max(zMax, vertice.obtenerCoordenadaZ());
    }
  }
  Vertice vertMin(xMin, yMin, zMin);
  Vertice vertMax(xMax, yMax, zMax);
  Envolvente calcular(vertMin, vertMax);
  std::cout << "Envolvente global calculada:" << std::endl;
  std::cout << "X: [" << xMin << ", " << xMax << "]" << std::endl;
  std::cout << "Y: [" << yMin << ", " << yMax << "]" << std::endl;
  std::cout << "Z: [" << zMin << ", " << zMax << "]" << std::endl;
  return calcular;
}

void Interfaz::agregarEnvolventeGlobal()
{
  Envolvente envolventeObjetos = calcularEnvolventeGlobal();

  if (envolventeObjetos.obtenerPuntoMaximo().obtenerCoordenadaX() >= 0)
  {
    establecerEnvolventeGlobal(envolventeObjetos);
    std::cout << "Resultado exitoso. La caja envolvente de los objetos en "
                 "memoria se ha generado con el nombre"
              << std::endl;
    std::cout << "env_global y se ha agregado a los objetos en memoria"
              << std::endl;
    std::cout << "Punto minimo: "
              << envolventeObjetos.obtenerPuntoMinimo().obtenerCoordenadaX()
              << " "
              << envolventeObjetos.obtenerPuntoMinimo().obtenerCoordenadaY()
              << " "
              << envolventeObjetos.obtenerPuntoMinimo().obtenerCoordenadaZ()
              << std::endl;
    std::cout << "Punto maximo: "
              << envolventeObjetos.obtenerPuntoMaximo().obtenerCoordenadaX()
              << " "
              << envolventeObjetos.obtenerPuntoMaximo().obtenerCoordenadaY()
              << " "
              << envolventeObjetos.obtenerPuntoMaximo().obtenerCoordenadaZ()
              << std::endl;
  }
  else
  {
    std::cout << "Memoria vacia. Ningun objeto ha sido cargado en memoria"
              << std::endl;
  }
}

int Interfaz::descargar(std::string nombreObjeto)
{
  if (objetos.empty())
  {
    std::cout << "Ningun objeto ha sido cargado en memoria";
    return (1);
  }
  std::vector<Objeto>::iterator miIteratorDesc;
  for (miIteratorDesc = objetos.begin(); miIteratorDesc != objetos.end();
       miIteratorDesc++)
  {
    if (miIteratorDesc->obtenerNombre() == nombreObjeto)
    {
      objetos.erase(miIteratorDesc);
      return (0);
    }
  }
  return (1);
};

void Interfaz::descargarArchivo(std::string nombreObjeto)
{
  int objetoPosicion = posicionObjeto(nombreObjeto);

  int envolventePosicion = posicionEnvolvente(nombreObjeto);

  if (objetoPosicion != -1)
  {
    std::vector<Objeto>::iterator iteradorObjetos =
        this->objetos.begin() + objetoPosicion;

    this->objetos.erase(iteradorObjetos);

    std::cout << "Resultado exitoso. El objeto " << nombreObjeto
              << " ha sido eliminado de la memoria" << std::endl;
    std::cout << "de trabajo" << std::endl;
    return;
  }
  else if (envolventePosicion != -1)
  {
    std::vector<Envolvente>::iterator iteradorEnvolventes =
        this->envolventes.begin() + envolventePosicion;

    this->envolventes.erase(iteradorEnvolventes);

    std::cout << "Resultado exitoso. El objeto " << nombreObjeto
              << " ha sido eliminado de la memoria" << std::endl;
    std::cout << "de trabajo" << std::endl;
    return;
  }
  else if (this->envolventeGlobal.obtenerNombre() == nombreObjeto)
  {
    Envolvente envolvente;
    establecerEnvolventeGlobal(envolvente);
    std::cout << "Resultado exitoso. El objeto " << nombreObjeto
              << " ha sido eliminado de la memoria" << std::endl;
    std::cout << "de trabajo" << std::endl;
    return;
  }
  else if (envolventePosicion == -1 || objetoPosicion == -1)
  {
    std::cout << "Objeto no existe. El objeto " << nombreObjeto
              << " no ha sido cargado en memoria" << std::endl;
    return;
  }
}

void Interfaz::guardarArchivo(std::string nombreObjeto,
                              std::string nombreArchivo)
{
  // manejar archivos de salida
  std::ofstream archivo;

  // Se obtiene la posición del objeto con ayuda del nombre proporcionado
  int posicion = posicionObjeto(nombreObjeto);

  // Verificar si el objeto no fue encontrado (posicion es -1)
  if (posicion == -1)
  {
    // Mostrar un mensaje de error si el objeto no existe
    std::cout << "Objeto no existe. El objeto " << nombreObjeto
              << " no se encontr en memoria" << std::endl;
    // Terminar la función si el objeto no está en memoria
    return;
  }

  // Abrir el archivo especificado para escritura
  archivo.open(nombreArchivo);

  // Verificar si el archivo se abrió correctamente
  if (!archivo.is_open())
  {
    // Mostrar un mensaje de error si el archivo no se pudo abrir
    std::cout << "Archivo no existe. El archivo " << nombreArchivo
              << " no se pudo abrir" << std::endl;
    // Terminar la función si el archivo no se pudo abrir
    return;
  }

  // Escribir la información del objeto en el archivo

  // Escribir el nombre del objeto
  archivo << this->objetos[posicion].obtenerNombre() << std::endl;
  // Escribir la cantidad de vértices del objeto
  archivo << this->objetos[posicion].obtenerCantidadVertices() << std::endl;

  // Escribir las coordenadas de los vértices
  for (auto &vertice : this->objetos[posicion].obtenerCoordenadasVertices())
  {
    // Escribir las coordenadas X, Y y Z del vértice, separadas por espacios
    archivo << vertice.obtenerCoordenadaX() << " "
            << vertice.obtenerCoordenadaY() << " "
            << vertice.obtenerCoordenadaZ() << std::endl;
  }

  // Escribir la información de las caras
  for (auto &cara : this->objetos[posicion].obtenerCaras())
  {
    // Escribir la cantidad de aristas de la cara
    archivo << cara.obtenerCantidadAristas() << " ";
    // Iterar sobre cada índice de vértice de la cara
    for (int indice : cara.obtenerIndicesVertices())
    {
      // Escribir cada índice separado por espacios
      archivo << indice << " ";
    }
    // Terminar la línea después de los índices
    archivo << std::endl;
  }

  // Escribir un indicador del final del archivo
  archivo << "-1" << std::endl;

  // Mostrar un mensaje de éxito indicando que la información se ha guardado
  std::cout << "Resultado exitoso. La información del objeto " << nombreObjeto
            << " ha sido guardada exitosamente" << std::endl;
  std::cout << "en el archivo " << nombreArchivo << std::endl;

  // Cerrar el archivo
  archivo.close();
}

void Interfaz::verticeCercano(std::string coordenadas)
{
  // Verifica que la cadena de coordenadas no esté vacía
  if (coordenadas.empty())
  {
    cout << "Error: La entrada de coordenadas está vacía." << std::endl;
    return;
  }

  // Encuentra las posiciones de los espacios
  size_t pos1 = coordenadas.find(' ');
  size_t pos2 = coordenadas.find(' ', pos1 + 1);

  // Asegura que haya al menos tres coordenadas
  if (pos1 == std::string::npos || pos2 == std::string::npos)
  {
    cout << "Error: Se requieren tres coordenadas." << std::endl;
    return;
  }

  // Extrae las coordenadas x, y y z
  string x = coordenadas.substr(0, pos1);
  string y = coordenadas.substr(pos1 + 1, pos2 - pos1 - 1);
  string z = coordenadas.substr(pos2 + 1, coordenadas.find(' ', pos2 + 1) - pos2 - 1);

  // Si hay "extra", se asegura de que haya un espacio después de z
  string extra = coordenadas.substr(pos2 + z.length() + 1);
  extra.erase(remove(extra.begin(), extra.end(), ' '), extra.end()); // Elimina espacios en extra

  if (extra.empty())
  {
    std::vector<Nodo> nodos;
    for (int i = 0; i < objetos.size(); i++)
    {
      vector<Vertice> vertices = this->objetos[i].obtenerCoordenadasVertices();
      for (int j = 0; j < vertices.size(); j++)
      {
        Nodo Node = Nodo(vertices[j]);
        nodos.push_back(Node);
      }
    }
    KDTree tree(nodos);
    int nX = stoi(x);
    int nY = stoi(y);
    int nZ = stoi(z);
    Vertice vcercano(nX, nY, nZ);
    Nodo vnodo(vcercano);
    Nodo nearest = tree.nearestNeighbor(vnodo);
    int indice = -1;
    string nomCercano;

    for (int i = 0; i < objetos.size(); i++)
    {
      vector<Vertice> vertices = this->objetos[i].obtenerCoordenadasVertices();
      for (int j = 0; j < vertices.size(); j++)
      {
        if (vertices[j].obtenerCoordenadaX() == nearest.getX())
        {
          if (vertices[j].obtenerCoordenadaY() == nearest.getY())
          {
            if (vertices[j].obtenerCoordenadaZ() == nearest.getZ())
            {
              indice = j;
              nomCercano = objetos[i].obtenerNombre();
            }
          }
        }
      }
    }

    cout << "El objeto al que pertenece el vertice mas cercano es " << nomCercano << endl
         << " con el indice y las coordenadas: " << indice << "(" << nearest.getX() << "," << nearest.getY() << "," << nearest.getZ() << ")" << endl
         << " a una distancia de: " << tree.distance(nearest, vnodo);
  }
  else
  {
    for (int h = 0; h < objetos.size(); h++)
    {
      if (this->objetos[h].obtenerNombre() == extra)
      {

        std::vector<Nodo> nodos;
        vector<Vertice> vertices = this->objetos[h].obtenerCoordenadasVertices();
        for (int j = 0; j < vertices.size(); j++)
        {
          Nodo Node = Nodo(vertices[j]);
          nodos.push_back(Node);
        }

        KDTree tree(nodos);
        int nX = stoi(x);
        int nY = stoi(y);
        int nZ = stoi(z);
        Vertice vcercano(nX, nY, nZ);
        Nodo vnodo(vcercano);
        Nodo nearest = tree.nearestNeighbor(vnodo);
        int indice = -1;

        for (int l = 0; l < vertices.size(); l++)
        {
          Nodo comp(vertices[l]);
          if (vertices[l].obtenerCoordenadaX() == nearest.getX())
          {
            if (vertices[l].obtenerCoordenadaY() == nearest.getY())
            {
              if (vertices[l].obtenerCoordenadaZ() == nearest.getZ())
              {
                indice = l;
              }
            }
          }
        }
        cout << "El vertice mas cercano del objeto " << extra << " es: " << endl
             << " con el indice y las coordenadas: " << indice << "(" << nearest.getX() << "," << nearest.getY() << "," << nearest.getZ() << ")" << endl
             << " a una distancia de: " << tree.distance(nearest, vnodo);
        return;
      }
    }
    cout << "El objeto " << extra << " no ha sido cargado en memoria";
  }
}

Envolvente Interfaz::obtenerEnvolvente(std::string &nombreObjeto)
{
  // std::cout << "Buscando el objeto: " << nombreObjeto << " en el vector de objetos" << std::endl;
  //  recorre la lista de objeto cargados
  for (auto &objeto : objetos)
  { // compara el nombre del objeto con le nombre que pasa el usuari
    if (objeto.obtenerNombre() == nombreObjeto)
    {
      return objeto.obtenerEnvolvente();
    }
  }
  // si no lo encuentra, muetra un mensaje de error y devuelve la envolvente vacia
  std::cout << " El objeto :" << nombreObjeto << "/ no se encontro el memoria" << std::endl;
  return Envolvente();
}

void Interfaz::verticesCercanosCaja(std::string &nombreObjeto)
{
  // std::cout << "Llamando a verticesCercanosCaja para el objeto: " << nombreObjeto << std::endl;

  if (nombreObjeto.empty())
  {
    std::cout << "El objeto " << nombreObjeto << "no ha sido cargado en memoria" << std::endl;
  }
  else
  {
    // Buscamos el nombre del objeto
    Envolvente envolvete = obtenerEnvolvente(nombreObjeto);
    // esquinas de la envolvente
    std::vector<Vertice> esquinas = envolvete.obtenerEsquinas();
    // Cree un KDTree con los vertices del objeto
    std::vector<Nodo> nodos;
    for (auto &objeto : objetos)
    {
      std::vector<Vertice> vertices = objeto.obtenerCoordenadasVertices();
      for (auto &vertice : vertices)
      {
        nodos.push_back(Nodo(vertice)); // crea un nodo a partir de cada vertice
      }
    }
    KDTree tree(nodos); // hacemos un KDTree con los nodos

    // almacenar resultados
    std::vector<std::tuple<Vertice, Nodo, int>> resultado;

    // buscamos el vertice mas cercano para cada esquina
    for (auto &esquina : esquinas)
    {
      Nodo nodoEsquina(esquina);
      Nodo verticeCercano = tree.nearestNeighbor(nodoEsquina);
      int distancia = tree.distance(nodoEsquina, verticeCercano);

      resultado.push_back(std::make_tuple(esquina, verticeCercano, distancia));
    }
    // resultados en formato de tabla
    std::cout << std::left
              << std::setw(20) << "Esquina"
              << std::setw(25) << "Vertice Cercano"
              << "Distancia" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    for (auto &resultado : resultado)
    {
      Vertice esquina = std::get<0>(resultado);
      Nodo vertice = std::get<1>(resultado);
      int distancia = std::get<2>(resultado);

      std::cout << std::left
                << std::setw(20) << ("(" + std::to_string(esquina.obtenerCoordenadaX()) + ", " + std::to_string(esquina.obtenerCoordenadaY()) + ", " + std::to_string(esquina.obtenerCoordenadaZ()) + ")")
                << std::setw(25) << ("(" + std::to_string(vertice.getX()) + ", " + std::to_string(vertice.getY()) + ", " + std::to_string(vertice.getZ()) + ")")
                << distancia << std::endl;
    }
  }
}

Objeto Interfaz::obtenerObjetoPorNombre(const std::string &nombreObjeto)
{
  for (const auto& objeto : objetos) // Recorre la lista de objetos
    {
        if (objeto.obtenerNombre() == nombreObjeto) // Compara el nombre
        {
            return objeto; // Devuelve el objeto si coincide
        }
    }
    std::cerr << "Error: El objeto " << nombreObjeto << " no se encuentra en memoria." << std::endl;
    return Objeto(); // Devuelve un objeto vacío o puedes lanzar una excepción

}

void Interfaz::ProbarGrafo(std::string &nombreObjeto)
{
  //Encuentra el objeto por nombre
  Objeto objeto = obtenerObjetoPorNombre(nombreObjeto);

  //Verificamos si el objeto tiene vertices
  if (objeto.obtenerCantidadVertices() == 0)
  {
    std::cout << "Error: El objeto no tiene vertices"  << std::endl;
    return;

  }


  grafo Grafo(objeto);

  Grafo.mostrarMatrizAdyacencia();
}

void Interfaz::rutaCorta(std:: string &comando)
 {
   size_t pos = comando.find(' ');
        string objeto = (pos == string::npos) ? comando : comando.substr(0, pos);
        string origen = (pos == string::npos) ? "" : comando.substr(pos + 1);
        string destino = (pos == string::npos) ? "" : comando.substr(pos + 2);
        
    Objeto objetoRC;
    objetoRC = obtenerObjetoPorNombre(objeto);

    grafo Grafo(objetoRC);
    std::vector<int> camino = Grafo.rutaCorta(origen, destino);
    

    //distancia total
    double dt;
    dt=Grafo.distanciaRuta(camino);
    //std::cout << "Camino size" <<camino.size()<<endl;
    std::cout << "Ruta mas corta que conecta los vertices  " << camino[camino.size()-1] << " y " << destino << " del objeto "<<
    objeto <<" pasa por: ";
    for (int i = camino.size() - 1; i >= 0; i--){
         std::cout << camino[i] << " - ";
    }
    std::cout << endl <<  "con una longitud de "<< dt ;
}

void Interfaz::rutaCortaCentro(std::string comando)
{
  size_t pos = comando.find(' ');
  string indiceOrigen = (pos == string::npos) ? comando : comando.substr(0, pos);
  string nombreObjeto = (pos == string::npos) ? "" : comando.substr(pos + 1);

  Objeto objetoCe;
  objetoCe = obtenerObjetoPorNombre(nombreObjeto);
  grafo Grafo(objetoCe);
  Vertice PuntoCentro= Grafo.centroide();
  cout<<"El verctice ubicado en el centro de "<<nombreObjeto<<" es:";
  cout<<"("<<PuntoCentro.obtenerCoordenadaX()<<","<<PuntoCentro.obtenerCoordenadaY()<<","<<PuntoCentro.obtenerCoordenadaZ()<<")";
  vector<Vertice> puntos =objetoCe.obtenerCoordenadasVertices();
  cout<<endl;

//punto cercano al centroide
  int puntoMinimo = 0;
  double distanciaMinima = std::sqrt(
    (PuntoCentro.obtenerCoordenadaX() - puntos[0].obtenerCoordenadaX()) * (PuntoCentro.obtenerCoordenadaX() - puntos[0].obtenerCoordenadaX()) +
    (PuntoCentro.obtenerCoordenadaY() - puntos[0].obtenerCoordenadaY()) * (PuntoCentro.obtenerCoordenadaY() - puntos[0].obtenerCoordenadaY()) +
    (PuntoCentro.obtenerCoordenadaZ() - puntos[0].obtenerCoordenadaZ()) * (PuntoCentro.obtenerCoordenadaZ() - puntos[0].obtenerCoordenadaZ()));

  for (int i = 1; i < objetoCe.obtenerCantidadVertices(); i++) {
    double dist = std::sqrt(
      (PuntoCentro.obtenerCoordenadaX() - puntos[i].obtenerCoordenadaX()) * (PuntoCentro.obtenerCoordenadaX() - puntos[i].obtenerCoordenadaX()) +
      (PuntoCentro.obtenerCoordenadaY() - puntos[i].obtenerCoordenadaY()) * (PuntoCentro.obtenerCoordenadaY() - puntos[i].obtenerCoordenadaY()) +
      (PuntoCentro.obtenerCoordenadaZ() - puntos[i].obtenerCoordenadaZ()) * (PuntoCentro.obtenerCoordenadaZ() - puntos[i].obtenerCoordenadaZ()));
    if (dist < distanciaMinima) {
      puntoMinimo = i;
      distanciaMinima = dist;
    }
  }
  
  std::string indiceMin=to_string(puntoMinimo);
  std::vector<int>rutaCentro = Grafo.rutaCorta(indiceOrigen,indiceMin);
  
  double dt;
  dt=Grafo.distanciaRuta(rutaCentro);
    //std::cout << "Camino size" <<rutaCentro.size()<<endl;
    std::cout << "La ruta mas corta que conecta el vertice " << indiceOrigen << " con el centro del objeto " << nombreObjeto 
    << " , ubicado en ct  "<< "("<<PuntoCentro.obtenerCoordenadaX()<<","<<PuntoCentro.obtenerCoordenadaY()<<","
    <<PuntoCentro.obtenerCoordenadaZ()<<")" <<" pasa por: ";
    for (int i = rutaCentro.size() - 1; i >= 0; i--){
         std::cout << rutaCentro[i] << " - ";
    }
    std::cout<< "ct";
    std::cout << endl <<  "con una longitud de "<< dt+distanciaMinima ;

}

