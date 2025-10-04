#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Producto {
    string nombre;
    int requerimiento;
    int logitud;
    int altura;
};

bool compara(const Producto &p1, const Producto &p2) {
    return p1.logitud*p1.altura > p2.logitud*p2.altura;
}

struct Solucion {
    int numeroLaminas;
    int mermaAcumumlada;
};

void calcularVoraz(vector<Producto>  productos) {
    sort(productos.begin(), productos.end(),compara);
    for (int i=0; i<productos.size(); i++) {
        cout << productos[i].nombre << endl;
    }
    int lamina=2500;
    Solucion solucion;
    solucion.numeroLaminas = 0;
    solucion.mermaAcumumlada = 0;
    for (int i=0; i<productos.size(); i++) {
        for (int j=0; j<productos[i].requerimiento; j++) {
            if (productos[i].logitud*productos[i].altura <= lamina) {
                lamina -= productos[i].altura*productos[i].logitud;
            }
            else {
                solucion.numeroLaminas++;
                solucion.mermaAcumumlada += lamina;
                lamina = 2500;
            }
        }
    }

    cout << "Numero de laminas: "<<solucion.numeroLaminas << endl;
    cout << "Merma acumulada: "<<solucion.mermaAcumumlada << endl;
}

int main() {
    vector<Producto> productos = {
        {"Mentolato", 5, 2, 3},
        {"Crema Nivea", 10, 9,3},
        {"Atun",15,14,7},
        {"Conserva",20,15,20},
        {"Aceite Industrial",20,22,18}
    };

    calcularVoraz(productos);

    return 0;
}
