#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;
#define ITERACIONES 10000
#define alfa  0.4

struct Destino {
    char destino;
    int pago;
};

struct Solucion {
    int ganancia;
    vector<Destino> destinos;
};



bool compara(const Destino &d1, const Destino &d2) {
    return d1.pago > d2.pago;
}

int buscarInd(const vector<Destino> &destinos, double rcl) {
    int contador = 0;
    for (int i = 0; i < destinos.size(); i++) {
        if (destinos[i].pago >= rcl) contador++;
    }
    return contador;
}

void graspRappi(const map<char, vector<Destino> > &dest) {
    Solucion sol = {INT_MIN, {}};
    srand(time(NULL));
    for (int i = 0; i < ITERACIONES; i++) {
        map<char, vector<Destino> > destino = dest;
        Solucion res = {0, {}};
        char pos = 'A';
        while (!destino[pos].empty()) {
            sort(destino[pos].begin(), destino[pos].end(), compara);
            int beta = destino[pos].front().pago;
            int tao = destino[pos].back().pago;
            double rcl = beta - alfa * (beta - tao);
            int ind = buscarInd(destino[pos], rcl);
            int indA = rand() % ind;

            res.destinos.push_back(destino[pos][indA]);
            res.ganancia += destino[pos][indA].pago;
            pos = destino[pos][indA].destino;
        }

        if (sol.ganancia < res.ganancia) {
            sol.ganancia = res.ganancia;
            sol.destinos = res.destinos;
        }
    }

    cout << "Ganancia = " << sol.ganancia << endl;
    for (int i = 0; i < sol.destinos.size(); i++) { cout << sol.destinos[i].destino << " "; }
}

int main() {
    map<char, vector<Destino> > caminos = {
        {'A', {{'B', 20}, {'C', 30}, {'D', 40}, {'E', 40}, {'H', 50}}},
        {'B', {{'C', 30}, {'D', 40}, {'F', 40}, {'H', 50}}},
        {'C', {{'F', 40}}},
        {'D', {}},
        {'E', {{'C', 30}, {'F', 40},{'G',10}}},
        {'F', {}},
        {'G', {}},
        {'H', {}}
    };

    graspRappi(caminos);


    return 0;
}
