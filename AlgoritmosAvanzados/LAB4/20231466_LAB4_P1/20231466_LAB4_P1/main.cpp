#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <climits>
#include <iomanip>
using namespace std;
#define ITERACIONES 1000
#define alfa 0.3

struct Paquete {
    int id;
    char ob;
    int ancho;
    int alto;
    int area;
};

struct Contenedor {
    int espacio;
    vector<vector<int> > contenedor;
};

bool compara(const Paquete &o1, const Paquete &o2) {
    return o1.area > o2.area;
}

Contenedor nuevoContenedor(int tamanho) {
    Contenedor c;
    vector<int> fila;
    fila.assign(tamanho, 0);
    c.espacio = tamanho * tamanho;
    c.contenedor.assign(tamanho, fila);
    return c;
}

int buscarInd(const vector<Paquete> &paq, double rcl) {
    int contador = 0;
    for (int i = 0; i < paq.size(); i++) {
        if (paq[i].area >= rcl) contador++;
    }
    return contador;
}

int buscarInd(const vector<Contenedor> &cont, double rcl) {
    int contador = 0;
    for (int i = 0; i < cont.size(); i++) {
        if (cont[i].espacio >= rcl) contador++;
    }
    return contador;
}

bool cabe(int x, int y, Paquete paq, int N, Contenedor &cont) {
    if (x + paq.alto > N || y + paq.ancho > N) return false;
    for (int i = x; i < x + paq.alto; i++) {
        for (int j = y; j < y + paq.ancho; j++) {
            if (cont.contenedor[i][j] != 0)return false;
        }
    }

    return true;
}

void colocar(int x, int y, Paquete paq, int N, Contenedor &cont) {
    for (int i = x; i < x + paq.alto; i++) {
        for (int j = y; j < y + paq.ancho; j++) {
            cont.contenedor[i][j] = paq.id;
        }
    }
}

bool comparaC(const Contenedor &c1, const Contenedor &c2) {
    return c1.espacio > c2.espacio;
}

void imprimirContenedor(Contenedor cont) {
    for (int i = 0; i < cont.contenedor.size(); i++) {
        for (int j = 0; j < cont.contenedor[i].size(); j++) {
            cout <<setw(4)<< cont.contenedor[i][j] ;
        }
        cout << endl;
    }
}

void imprimirContenedores(const vector<Contenedor> &vector) {
    for (int i = 0; i < vector.size(); i++) {
        cout << "Contenedor " << i + 1 << endl;
        imprimirContenedor(vector[i]);
        cout << endl;
    }
}

void grasp2D(vector<Paquete> paq, int N) {
    srand(time(NULL));
    sort(paq.begin(), paq.end(), compara);
    vector<Contenedor> solucion;
    int cantidadMejor = INT_MAX;

    for (int i = 0; i < ITERACIONES; i++) {
        vector<Paquete> paquetes = paq;
        vector<Contenedor> contenedor = {nuevoContenedor(N)};
        while (!paquetes.empty()) {
            int betaP = paquetes.front().area;
            int tauP = paquetes.back().area;
            double rcl = betaP - alfa * (betaP - tauP);
            int ind = buscarInd(paquetes, rcl);
            int indA = rand() % ind;

            sort(contenedor.begin(), contenedor.end(), comparaC);
            int betaC = contenedor[0].espacio;
            int tauC = contenedor.back().espacio;
            double rclC = betaC - alfa * (betaC - tauC);
            int indC = buscarInd(contenedor, rclC);
            int indAC = rand() % indC;

            bool coloco = false;
            for (int x = 0; x < N and !coloco; x++) {
                for (int y = 0; y < N and !coloco; y++) {
                    if (cabe(x, y, paquetes[indA], N, contenedor[indAC])) {
                        // se muere aqui cuando quiere verificar el cabe
                        colocar(x, y, paquetes[indA], N, contenedor[indAC]);
                        contenedor[indAC].espacio -= paquetes[indA].area;
                        coloco = true;
                    }
                }
            }

            if (!coloco) {
                contenedor.push_back(nuevoContenedor(N));
                colocar(0, 0, paquetes[indA], N, contenedor.back());
                contenedor.back().espacio -= paquetes[indA].area;
            }
            paquetes.erase(paquetes.begin() + indA);
        }

        if (contenedor.size() < cantidadMejor) {
            cantidadMejor = contenedor.size();
            solucion = contenedor;
        }
    }

    cout << cantidadMejor << endl;
    imprimirContenedores(solucion);
}

int main() {
    vector<Paquete> objetos = {
        {1, 'A', 6, 5, 30},
        {2, 'B', 4, 5, 20},
        {3, 'C', 3, 3, 9},
        {4, 'D', 5, 5, 25},
        {5, 'E', 2, 1, 2},
        {6, 'F', 7, 3, 21},
        {7, 'G', 3, 7, 21},
        {8, 'H', 2, 6, 12},
        {9, 'I', 4, 4, 16},
        {10, 'J', 5, 2, 10},
        {11, 'K', 1, 7, 7},
        {12, 'L', 7, 1, 7}
    };


    int dimensionContenedor = 10;
    grasp2D(objetos, dimensionContenedor);

    return 0;
}
