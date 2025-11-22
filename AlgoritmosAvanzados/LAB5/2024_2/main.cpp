#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define ITERACIONES 1000
#define INDIVIDUOS 10
#define TSELECCION 0.5
#define TCASAMIENTO 0.5
#define TMUTACION 0.5

struct Objeto {
    char objeto;
    int ancho;
    int alto;
};

struct Caja {
    vector<vector<int> > map;
    int fitnes;
};

bool cabe(int x, int y, Objeto ob, int N, const Caja &caja) {
    if (x + ob.ancho > N || y + ob.alto > N) return false;
    for (int i = x; i < x + ob.ancho; i++) {
        for (int j = y; j < y + ob.alto; j++) {
            if (caja.map[i][j] != 0) return false;
        }
    }
    return true;
}

int calcularFitnes(vector<int> cromo, vector<Objeto> paq) {
    int suma = 0;
    for (int i = 0; i < cromo.size(); i++) {
        suma+=cromo[i]*(paq[i].alto*paq[i].ancho);
    }
    return suma;
}

Caja nuevaCaja(int N) {
    Caja c;
    vector<int> fila;
    fila.assign(N, 0);
    c.map.assign(N, fila);
    c.fitnes = N * N;
    return c;
}

void colocar(int x, int y, Objeto ob, Caja &caja) {
    for (int i = x; i < x + ob.ancho; i++) {
        for (int j = y; j < y + ob.alto; j++) {
            caja.map[i][j] = ob.objeto;
        }
    }
}

void mostrarCaja(const Caja &caja, int N) {
    cout << "Ocupa: " << caja.fitnes << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (caja.map[i][j])
                cout << (char) caja.map[i][j] << " ";
            else cout << '*' << " ";
        }
        cout << endl;
    }
    cout << endl;
}


bool aberracion(const vector<int> &cromo,
                const vector<Objeto> &paq, int N) {
    Caja caja = nuevaCaja(N);
    for (int j = 0; j < cromo.size(); j++) {
        if (cromo[j]) {
            bool entro = false;
            for (int x = 0; x < N && !entro; x++) {
                for (int y = 0; y < N && !entro; y++) {
                    if (cabe(x, y, paq[j], N, caja)) {
                        colocar(x, y, paq[j], caja);
                        caja.fitnes = calcularFitnes(cromo,paq);
                        entro = true;
                    }
                }
            }
            if (!entro) {
                return true;
            }
        }
    }
    mostrarCaja(caja, N);
    return false;
}

void generaPoblacion(vector<vector<int> > &poblacion,
                     const vector<Objeto> &paq, int N) {
    int i = 0;
    srand(time(NULL));
    while (true) {
        vector<int> cromo;
        for (int j = 0; j < paq.size(); j++)cromo.push_back(rand() % 2);
        if (!aberracion(cromo, paq, N)) {
            poblacion.push_back(cromo);
            i++;
        }
        if (i == INDIVIDUOS) break;
    }
}

void seleccion( vector<vector<int>> & padres, const vector<vector<int>> & poblacion, const vector<Objeto> & paq, int i);

void binpacking2DAG(vector<Objeto> paq, int N) {
    vector<vector<int> > poblacion;
    generaPoblacion(poblacion, paq, N);

    for (int i = 0; i < ITERACIONES; i++) {
        vector<vector<int> > padres;
        seleccion(padres,poblacion,paq,N);
    }
}

int main() {
    vector<Objeto> paq = {
        {'A', 6, 5},
        {'B', 4, 5},
        {'C', 3, 3},
        {'D', 5, 5},
        {'E', 2, 2}
    };
    int dimension = 10;
    binpacking2DAG(paq, dimension);
    return 0;
}
