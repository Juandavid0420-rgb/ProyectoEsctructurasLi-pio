#include <iostream>
#include <vector>
#include <string>
#include "interfaz.h"

using namespace std;

// Vector global que almacenará pares de comandos y sus descripciones
vector<pair<string, string>> descripcionesComandos;

void InicializarDescripcionesComandos()
{
    descripcionesComandos.push_back(make_pair("cargar", "Carga la información del objeto 'nombre_objeto' desde el archivo 'nombre_archivo'."));
    descripcionesComandos.push_back(make_pair("listado", "Muestra una lista de todos los objetos cargados."));
    descripcionesComandos.push_back(make_pair("envolventeOb", "Muestra la envolvente convexa del objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("envolvente", "Muestra la envolvente convexa de todos los objetos."));
    descripcionesComandos.push_back(make_pair("descargar", "Descarga el objeto especificado."));
    descripcionesComandos.push_back(make_pair("guardar", "Guarda el objeto 'nombre_objeto' en el archivo 'nombre_archivo'."));
    descripcionesComandos.push_back(make_pair("v_cercanoEspecifico", "Encuentra el vértice más cercano al punto (px, py, pz) en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("v_cercanoGeneral", "Encuentra el vértice más cercano al punto (px, py, pz) en todos los objetos."));
    descripcionesComandos.push_back(make_pair("v_cercano_caja", "Encuentra los vértices más cercanos en una caja delimitadora en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("ruta_corta", "Encuentra la ruta más corta entre dos puntos en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("ruta_corta_centro", "Encuentra la ruta más corta desde el centro al punto i1 en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("ayuda", "Muestra una lista de todos los comandos disponibles."));
    descripcionesComandos.push_back(make_pair("ayuda comando", "Muestra la descripción de un comando específico."));
    descripcionesComandos.push_back(make_pair("salir", "Termina el programa."));
}

void MostrarComandoAyuda(const string &comando)
{
    bool encontrado = false;
    for (const auto &par : descripcionesComandos)
    {
        if (par.first == comando)
        {
            cout << "asdasas" << endl;
            cout << par.second << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "No se encontró ayuda para el comando: " << comando << endl;
    }
}

void MostrarComandosDisponibles()
{
    cout << "Comandos Disponibles: " << endl;
    for (const auto &par : descripcionesComandos)
    {
        cout << " - " << par.first << endl;
    }
    cout << endl;
}

int main()
{
    vector<Objeto> objetos;
    vector<Envolvente> envolventes;
    Envolvente envolventeGlobal;
    // Se crea la interfaz entre el usuario y el programa
    Interfaz interfaz(objetos, envolventes, envolventeGlobal);

    InicializarDescripcionesComandos();
    string NombreObjeto = "";
    string comando;
    string subComando;

    do
    {
        cout << endl;
        cout << "Bienvenido" << endl;
        cout << "La palabra 'ayuda' despliega la lista de comandos" << endl;
        cout << "La palabra 'ayuda comando', le pregunta cual es el comando del que requiere informacion" << endl;
        cout << "Para salir, escriba 'salir'" << endl;
        cout << "Ingrese un comando" << endl;

        cout << "$ ";
        getline(cin, comando);
        cout << endl;

        size_t pos = comando.find(' ');
        string cmd = (pos == string::npos) ? comando : comando.substr(0, pos);
        string args = (pos == string::npos) ? "" : comando.substr(pos + 1);

        if (cmd == "ayuda")
        {
            if (args.empty())
            {
                MostrarComandosDisponibles();
                // } else if (args == comando) {
                //      cout << "Ingrese el comando para obtener ayuda: ";
                //     getline(cin, subComando);
                //     cout << subComando << endl;
                //     MostrarComandoAyuda(subComando);
            }
            else
            {
                MostrarComandoAyuda(args);
            }
        }
        else if (cmd == "cargar")
        {

            interfaz.cargarArchivo(args);
        }
        else if (cmd == "listado")
        {
            interfaz.listado();
        }
        else if (cmd == "listadoEnvolventes")
        {
            interfaz.listarObjetosEnvolventes();
        }

        else if (cmd == "envolvente")
        {
            if (args.empty())
            {
                interfaz.agregarEnvolventeGlobal();
            }
            else
            {
                interfaz.agregarEnvolventeObjeto(args);
            }
        }
        else if (cmd == "descargar")
        {
            interfaz.descargarArchivo(NombreObjeto);
        }
        else if (cmd == "guardar")
        {
            interfaz.guardarArchivo(NombreObjeto, args);
        }
        else if (cmd == "cercano")
        {

            interfaz.verticeCercano(args);
        }
        else if (cmd == "cercanoCaja")
        {
            interfaz.verticesCercanosCaja(args);
        }
        else if (cmd == "ruta_corta")
        {
            interfaz.rutaCorta(args);
        }
        else if (cmd == "ProbarGrafo")
        {
            interfaz.ProbarGrafo(args);
        }
        else if (cmd == "ruta_corta_centro")
        {
            interfaz.rutaCortaCentro(args);
        }
        else if (cmd == "salir")
        {
            cout << "Terminando el programa..." << endl;
        }
        else
        {
            cout << cmd << " no se reconoce como comando interno. Escriba 'ayuda' si necesita ayuda." << endl;
        }

    } while (comando != "salir");

    return 0;
}
//d