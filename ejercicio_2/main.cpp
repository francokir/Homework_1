#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

void logMessage(const string& mensaje, const string& nivelSeveridad) {
    ofstream logFile("log.txt", ios::app);
    if (!logFile) {
        cerr << "Error abriendo." << endl;
        return;
    }
    logFile << "[" << nivelSeveridad << "] " << mensaje << endl;
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

void logMessage(const string& usuario, const string& mensajeAcceso, bool isSecurity) {
    ofstream logFile("log.txt", ios::app);
    if (!logFile) {
        cerr << "Error abriendo." << endl;
        return;
    }
    logFile << "[SECURITY] Usuario: " << usuario << " - " << mensajeAcceso << endl;
    logFile.close();
}

int main() {
    try {
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
            switch (opcion) {
                case 1:
                    cout << "Ingrese su mensaje deseado a continuacion: ";
                    getline(cin, mensaje);
                    cout << "Ingrese severidad (INFO, DEBUG, WARNING, ERROR, CRITICAL): ";
                    getline(cin, extra);
                    logMessage(mensaje, extra);
                    break;

                case 2:
                    cout << "Ingrese el mensaje de error a continuacion: ";
                    getline(cin, mensaje);
                    logMessage(mensaje, __FILE__, __LINE__);
                    break;

                case 3:
                    cout << "Ingrese su usuario a continuacion: ";
                    getline(cin, extra);
                    cout << "Ingrese estado de acceso (Access Granted, Access Denied): ";
                    getline(cin, mensaje);
                    logMessage(extra, mensaje, true);
                    break;

                case 4:
                    logMessage("Acceso a puntero nulo", __FILE__, __LINE__);
                    throw runtime_error("Error crítico en runtime.");
            }
        }

    } catch (const exception& e) {
        cerr << "Excepción atrapada: " << e.what() << endl;
        return 1;
    }

    cout << "Termino el testeo. Mire el archivo log.txt\n";
    return 0;
}