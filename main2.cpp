#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

string charToBinary(char c) {
    return bitset<8>(c).to_string();
}

string codificacionMetodo1(const string &binario, int n) {
    string codificado;
    for (int i = 0; i < binario.length(); i += n) {
        string bloque = binario.substr(i, n);
        if (bloque.length() < n) break;

        if (codificado.empty()) {
            for (char &bit : bloque) {
                bit = (bit == '0') ? '1' : '0';
            }
        } else {
            int contador1 = 0, contador0 = 0;

            for (char bit : bloque) {
                if (bit == '1') {
                    contador1++;
                } else {
                    contador0++;
                }
            }

            if (contador1 == contador0) {
                for (char &bit : bloque) {
                    bit = (bit == '0') ? '1' : '0';
                }
            } else if (contador0 > contador1) {
                for (int j = 0; j < bloque.length(); j += 2) {
                    if (j < bloque.length()) {
                        bloque[j] = (bloque[j] == '0') ? '1' : '0';
                    }
                    if (j + 1 < bloque.length()) {
                        bloque[j + 1] = (bloque[j + 1] == '0') ? '1' : '0';
                    }
                }
            } else {
                for (int j = 0; j < bloque.length(); j += 3) {
                    for (int k = 0; k < 3 && j + k < bloque.length(); k++) {
                        bloque[j + k] = (bloque[j + k] == '0') ? '1' : '0';
                    }
                }
            }
        }
        codificado += bloque;
    }
    return codificado;
}

string codificacionMetodo2(const string &binario, int n) {
    string codificado;
    for (int i = 0; i < binario.length(); i += n) {
        string bloque = binario.substr(i, n);
        if (bloque.length() < n) break;

        string desplazado;
        for (int j = n - 1; j >= 0; --j) {
            desplazado += bloque[j];
        }
        codificado += desplazado;
    }
    return codificado;
}

int main() {
    string nombreArchivoEntrada, nombreArchivoSalida;
    int n, metodo;

    cout << "Ingrese el nombre del archivo fuente: ";
    cin >> nombreArchivoEntrada;
    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> nombreArchivoSalida;
    cout << "Ingrese la semilla de codificacion (n): ";
    cin >> n;
    cout << "Seleccione el metodo de codificacion (1 o 2): ";
    cin >> metodo;

    ifstream archivoEntrada(nombreArchivoEntrada);
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo fuente." << endl;
        return 1;
    }

    string binario;
    char ch;
    while (archivoEntrada.get(ch)) {
        binario += charToBinary(ch);
    }
    archivoEntrada.close();

    string codificado;
    if (metodo == 1) {
        codificado = codificacionMetodo1(binario, n);
    } else if (metodo == 2) {
        codificado = codificacionMetodo2(binario, n);
    } else {
        cerr << "Metodo de codificacion invalido." << endl;
        return 1;
    }

    ofstream archivoSalida(nombreArchivoSalida, ios::binary);
    if (!archivoSalida) {
        cerr << "Error al crear el archivo de salida." << endl;
        return 1;
    }

    archivoSalida.write(codificado.c_str(), codificado.length());
    archivoSalida.close();

    cout << "Archivo codificado guardado como: " << nombreArchivoSalida << endl;
    return 0;
}
