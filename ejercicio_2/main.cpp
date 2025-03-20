#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

/*La primer funcion lo que hace simplemente es abrir el archivo sin borrar lo anterior y escribe el mensaje con
el formato pedido, digamos, la severidad entre corchetes, y el mensaje a su lado, tambien chequea que se haya abierto
correctamente el archivo, para escribir el mensaje se le pasa por int el nivel y con un switch hay correspondientes
para cada numero (explico luego xq uso int)
La segunda funcion tiene las mismas similitudes, solo que se le pasa el archivo y lo abre sin borrar lo anterior
esta funcion escribe directamente ERROR entre corchetes, y pone el mensaje del error que se le pase por
parametro, tambien se dice la linea del error
La tercera , muy similar a la segunda, se le pasa el usuario, un mensaje de acceso y se abre el archivo escribiendo
security entre corchetes, el usuario y si el acceso fue denegado etc. (el mensaje) Le paso por string este ultimo
y es por esto que en la primera funcion le pase el nivel de severidad por int y no string, para no tener las dos 
funciones con dos parametros que se le pasan y del mismo tipo ambos.
En el main hice la verificacion con switch cases para que el usuario ingrese por teclado los mensajes y todo
meti que printee las 5 opciones y por teclado se va seleccionando*/

void logMessage(const string& mensaje, int nivelSeveridad) {
    ofstream logFile("log.txt", ios::app);
    if (!logFile) {
        cerr << "Error abriendo el archivo." << endl;
        return;
    }
    string etiqueta;
    switch (nivelSeveridad) {
        case 0: etiqueta = "DEBUG"; break;
        case 1: etiqueta = "INFO"; break;
        case 2: etiqueta = "WARNING"; break;
        case 3: etiqueta = "ERROR"; break;
        case 4: etiqueta = "CRITICAL"; break;
        default: etiqueta = "UNKNOWN"; break;
    }

    logFile << "[" << etiqueta << "] " << mensaje << endl;
    logFile.close();
}

void logMessage(const string& mensajeError, const string& archivo, int linea) {
    ofstream logFile("log.txt", ios::app);
    if (!logFile) {
        cerr << "Error abriendo." << endl;
        return;
    }
    logFile << "[ERROR] " << mensajeError << " (" << archivo << ":" << linea << ")" << endl;
    logFile.close();
}

void logMessage(const string& usuario, const string& mensajeAcceso) {
    ofstream logFile("log.txt", ios::app);
    if (!logFile) {
        cerr << "Error abriendo." << endl;
        return;
    }
    logFile << "[SECURITY] Usuario: " << usuario << " - " << mensajeAcceso << endl;
    logFile.close();
}

int main() {
    int opcion;
    while (true) {
        cout << "\nSeleccione una de las siguientes opciones:\n"
             << "1. Mensaje general\n"
             << "2. Mensaje de error\n"
             << "3. Acceso de usuario\n"
             << "4. Simular error en runtime\n"
             << "5. Salir\n"
             << "Opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 5) break;

        string mensaje, extra;
        int severidad;
        switch (opcion) {
            case 1:
                cout << "Ingrese su mensaje deseado a continuación: ";
                getline(cin, mensaje);
                cout << "Ingrese severidad (0: DEBUG, 1: INFO, 2: WARNING, 3: ERROR, 4: CRITICAL): ";
                cin >> severidad;
                cin.ignore();
                
                if (severidad < 0 || severidad > 4) {
                    cout << "Nivel de severidad inválido. Usando INFO por defecto.\n";
                    severidad = 1;  // INFO por defecto
                }

                logMessage(mensaje, severidad);
                break;

            case 2:
                cout << "Ingrese el mensaje de error a continuación: ";
                getline(cin, mensaje);
                logMessage(mensaje, __FILE__, __LINE__);
                break;

            case 3:
                cout << "Ingrese su usuario a continuación: ";
                getline(cin, extra);
                cout << "Ingrese estado de acceso (Access Granted, Access Denied): ";
                getline(cin, mensaje);
                logMessage(extra, mensaje);
                break;

            case 4:
                logMessage("Acceso a puntero nulo", __FILE__, __LINE__);
                throw runtime_error("Error crítico en runtime.");
        }
    }
    cout << "Terminamos de testear. Mirar el archivo log.txt\n";
    return 0;}