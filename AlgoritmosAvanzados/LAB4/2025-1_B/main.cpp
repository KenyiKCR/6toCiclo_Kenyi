#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
#include <source_location>

using namespace std;
#define ITERACIONES 10000
#define alfa 0.21

struct Orden {
    int id;
    int cant;
    int prioridad;
};

struct Linea {
    int id;
    int makespan;
    vector<Orden> ordenes;
};

bool compara(const Orden &o1, const Orden &o2) {
    return o1.prioridad > o2.prioridad or
           (o1.prioridad == o2.prioridad and o1.cant > o2.cant);
}

bool comparaS(const Linea &l1, const Linea &l2) {
    return l1.id < l2.id;
}


int buscarInd(const vector<Orden> &ordens, double rcl) {
    int cont = 0;
    for (int i = 0; i < ordens.size(); i++) {
        if (ordens[i].prioridad >= rcl) {
            cont++;
        }
    }
    return cont;
}

int buscarInd(const vector<Linea> &linea, double rcl) {
    int cont = 0;
    for (int i = 0; i < linea.size(); i++) {
        if (linea[i].makespan <= rcl) {
            cont++;
        }
    }
    return cont;
}


bool comparaL(const Linea &l1, const Linea &l2) {
    return l1.makespan < l2.makespan;
}

void graspBotella(vector<Orden> od) {
    srand(time(NULL));
    vector<Linea> solucion;
    solucion.clear();
    int mejor = INT_MAX;
    sort(od.begin(), od.end(), compara);

    for (int i = 0; i < ITERACIONES; ++i) {
        vector<Linea> resultado = {
            {1, 0, {}},
            {2, 0, {}},
            {3, 0, {}},
            {4, 0, {}},
            {5, 0, {}},
        };
        vector<Orden> ordenes = od;
        int makespanTotal = 0;
        while (!ordenes.empty()) {
            int betaO = ordenes.front().prioridad;
            int taoO = ordenes.back().prioridad;
            double rcl = betaO - alfa * (betaO - taoO);
            int ind = buscarInd(ordenes, rcl);
            int indAO = rand() % ind;

            sort(resultado.begin(), resultado.end(), comparaL);
            int betaL = resultado.front().makespan;
            int taoL = resultado.back().makespan;
            double rclL = betaL + alfa * (taoL - betaL);
            int indL = buscarInd(resultado, rclL);
            int indAL = rand() % indL;

            resultado[indAL].makespan += ordenes[indAO].cant * 6;
            resultado[indAL].ordenes.push_back(ordenes[indAO]);

            ordenes.erase(ordenes.begin() + indAO);
        }
        for (int i = 0; i < resultado.size(); i++) {
            if (resultado[i].makespan > makespanTotal) {
                makespanTotal = resultado[i].makespan;
            }
        }

        if (makespanTotal < mejor) {
            mejor = makespanTotal;
            solucion = resultado;
        }
    }

    sort(solucion.begin(), solucion.end(), comparaS);

    cout << "Mejor Makespan: " << mejor << endl;
    for (int i = 0; i < solucion.size(); i++) {
        cout << "Linea: " << solucion[i].id << " ";
        for (int j = 0; j < solucion[i].ordenes.size(); j++) {
            cout << solucion[i].ordenes[j].id << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<Orden> ordenes = {
        {1, 103, 2},
        {2, 58, 1},
        {3, 88, 3},
        {4, 126, 1},
        {5, 195, 2},
        {6, 90, 2},
        {7, 54, 3},
        {8, 195, 1},
        {9, 124, 2},
        {10, 113, 3},
        {11, 193, 2},
        {12, 55, 1},
        {13, 97, 1},
        {14, 97, 2},
        {15, 169, 2},
        {16, 50, 2},
        {17, 167, 3},
        {18, 74, 1},
        {19, 79, 2},
        {20, 109, 1}
    };

    for (int i = 0; i < 10; i++) {
        graspBotella(ordenes);
    }
    return 0;
}
