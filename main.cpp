#include <iostream>
#include <vector>
#include <string>
#include "interfaz.h"

using namespace std;

// Vector global que almacenará pares de comandos y sus descripciones
vector<pair<string, string>> descripcionesComandos;

void InicializarDescripcionesComandos() {
    descripcionesComandos.push_back(make_pair("cargarArchivo", "Carga la información del objeto 'nombre_objeto' desde el archivo 'nombre_archivo'."));
    descripcionesComandos.push_back(make_pair("listado", "Muestra una lista de todos los objetos cargados."));
    descripcionesComandos.push_back(make_pair("envolventeObjeto", "Muestra la envolvente convexa del objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("envolvente", "Muestra la envolvente convexa de todos los objetos."));
    descripcionesComandos.push_back(make_pair("descargar", "Descarga el objeto especificado."));
    descripcionesComandos.push_back(make_pair("guardarObjeto", "Guarda el objeto 'nombre_objeto' en el archivo 'nombre_archivo'."));
    descripcionesComandos.push_back(make_pair("v_cercanoEspecifico", "Encuentra el vértice más cercano al punto (px, py, pz) en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("v_cercanoGeneral", "Encuentra el vértice más cercano al punto (px, py, pz) en todos los objetos."));
    descripcionesComandos.push_back(make_pair("v_cercanoCaja", "Encuentra los vértices más cercanos en una caja delimitadora en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("rutaCorta", "Encuentra la ruta más corta entre dos puntos en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("rutaCortaCentro", "Encuentra la ruta más corta desde el centro al punto i1 en el objeto 'nombre_objeto'."));
    descripcionesComandos.push_back(make_pair("ayuda", "Muestra una lista de todos los comandos disponibles."));
    descripcionesComandos.push_back(make_pair("ayuda comando", "Muestra la descripción de un comando específico."));
    descripcionesComandos.push_back(make_pair("salir", "Termina el programa."));
}

void MostrarComandoAyuda(const string &comando) {
    bool encontrado = false;
    for (const auto &par : descripcionesComandos) {
        if (par.first == comando) {
            cout << par.second << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró ayuda para el comando: " << comando << endl;
    }
}

void MostrarComandosDisponibles() {
    cout << "Comandos Disponibles: " << endl;
    for (const auto &par : descripcionesComandos) {
        cout << " - " << par.first << endl;
    }
    cout << endl;
}

int main() {
    Interfaz interfaz;
    InicializarDescripcionesComandos();

    string comando;
    string subComando;

    do {
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

        if (cmd == "ayuda") {
            if (args.empty()) {
                MostrarComandosDisponibles();
            } else if (args == "comando") {
                cout << "Ingrese el comando para obtener ayuda: ";
                getline(cin, subComando);
                MostrarComandoAyuda(subComando);
            } else {
                MostrarComandoAyuda(args);
            }
        } else if (cmd == "cargarArchivo") {
            interfaz.cargarArchivo();
        } else if (cmd == "listado") {
            interfaz.listado();
        } else if (cmd == "envolventeObjeto") {
            interfaz.envolventeObjeto();
        } else if (cmd == "envolvente") {
            interfaz.envolvente();
        } else if (cmd == "descargar") {
            interfaz.descargarObjeto();
        } else if (cmd == "guardarObjeto") {
            interfaz.guardarObjeto();
        } else if (cmd == "v_cercanoEspecifico") {
            interfaz.verticeCercanoEspecifico();
        } else if (cmd == "v_cercanoGeneral") {
            interfaz.verticeCercanoGeneral();
        } else if (cmd == "v_cercanoCaja") {
            interfaz.verticesCercanosCaja();
        } else if (cmd == "rutaCorta") {
            interfaz.rutaCorta();
        } else if (cmd == "rutaCortaCentro") {
            interfaz.rutaCortaCentro();
        } else if (cmd == "salir") {
            cout << "Terminando el programa..." << endl;
        } else {
            cout << cmd << " no se reconoce como comando interno. Escriba 'ayuda' si necesita ayuda." << endl;
        }

    } while (comando != "salir");

    return 0;
}
