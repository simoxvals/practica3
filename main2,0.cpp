#include <iostream>      // ejercicio de sistema de banco
#include <fstream>
#include <string>

using namespace std;

const int MAX_USUARIOS = 100;

bool verificarAcceso(const string &clave) {
    string claveEncriptada;
    ifstream archivo("sudo.txt");
    if (archivo.is_open()) {
        getline(archivo, claveEncriptada);
        archivo.close();
        return clave == claveEncriptada;
    }
    return false;
}

void registrarUsuario(string cedulas[], string claves[], double saldos[], int &cantidadUsuarios) {
    if (cantidadUsuarios >= MAX_USUARIOS) {
        cout << "No se pueden registrar más usuarios." << endl;
        return;
    }

    string cedula, clave;
    double saldo;

    cout << "Ingrese cedula: ";
    cin >> cedula;
    cout << "Ingrese clave: ";
    cin >> clave;
    cout << "Ingrese saldo: ";
    cin >> saldo;

    cedulas[cantidadUsuarios] = cedula;
    claves[cantidadUsuarios] = clave;
    saldos[cantidadUsuarios] = saldo;
    cantidadUsuarios++;

    cout << "Usuario registrado exitosamente." << endl;
}

int buscarUsuario(const string cedulas[], const string claves[], int cantidadUsuarios, const string &cedula, const string &clave) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (cedulas[i] == cedula && claves[i] == clave) {
            return i;
        }
    }
    return -1;
}

void accesoUsuario(string cedulas[], string claves[], double saldos[], int cantidadUsuarios) {
    string cedula, clave;
    cout << "Ingrese cedula: ";
    cin >> cedula;
    cout << "Ingrese clave: ";
    cin >> clave;

    int indice = buscarUsuario(cedulas, claves, cantidadUsuarios, cedula, clave);

    if (indice != -1) {
        cout << "Acceso concedido." << endl;
        saldos[indice] -= 1000;

        while (true) {
            cout << "Seleccione operacion: 1. Consultar saldo    2. Retirar dinero    3. Salir: ";
            int opcion;
            cin >> opcion;

            if (opcion == 1) {
                cout << "Su saldo es: " << saldos[indice] << " COP." << endl;
            } else if (opcion == 2) {
                double cantidad;
                cout << "Ingrese la cantidad a retirar: ";
                cin >> cantidad;
                if (cantidad <= saldos[indice]) {
                    saldos[indice] -= cantidad;
                    cout << "Retiro exitoso. Su nuevo saldo es: " << saldos[indice] << " COP." << endl;
                } else {
                    cout << "Saldo insuficiente." << endl;
                }
            } else if (opcion == 3) {
                break;
            } else {
                cout << "Opcion invalida." << endl;
            }
        }
    } else {
        cout << "Acceso denegado. Cedula o clave incorrecta." << endl;
    }
}

int main() {
    string cedulas[MAX_USUARIOS], claves[MAX_USUARIOS];
    double saldos[MAX_USUARIOS];
    int cantidadUsuarios = 0;
    int opcion;

    cout << "1. Ingresar como administrador 2. Salir: ";
    cin >> opcion;

    if (opcion == 1) {
        string claveAdmin;
        cout << "Ingrese clave de administrador: ";
        cin >> claveAdmin;

        if (verificarAcceso(claveAdmin)) {
            cout << "Acceso de administrador concedido." << endl;
            while (true) {
                cout << "Seleccione opcion: 1. Registrar usuario 2. Acceso usuario 3. Salir: ";
                cin >> opcion;

                if (opcion == 1) {
                    registrarUsuario(cedulas, claves, saldos, cantidadUsuarios);
                } else if (opcion == 2) {
                    accesoUsuario(cedulas, claves, saldos, cantidadUsuarios);
                } else if (opcion == 3) {
                    break;
                } else {
                    cout << "Opcion invalida." << endl;
                }
            }
        } else {
            cout << "Clave de administrador incorrecta." << endl;
        }
    }

    return 0;
}
