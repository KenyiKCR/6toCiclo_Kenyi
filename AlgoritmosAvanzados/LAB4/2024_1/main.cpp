#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
#include <map>
using namespace std;
#define ITERACIONES 100000
#define alfa 0

struct Tablas {
    int id;
    int cap;
    int velocidad;
};

struct Discos {
    int id;
    int cap;
    int velocidad;
};

struct Solucion {
    int disco;
    vector<int> tablas;
};

bool comparaT(const Tablas &t1, const Tablas &t2) {
    return t1.velocidad > t2.velocidad;
}

bool comparaD(const Discos &d1, const Discos &d2) {
    return d1.velocidad > d2.velocidad;
}

int buscarIndice(const vector<Tablas> &vector, double rcl_t) {
    int indice = 0;
    bool found = false;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].velocidad >= rcl_t) {
            indice++;
            if (vector[i].velocidad == rcl_t) break;
        }
    }
    return indice;
}

int buscarIndice(const vector<Discos> &vector, double rcl_t) {
    int indice = 0;
    bool found = false;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].velocidad >= rcl_t) {
            indice++;
            if (vector[i].velocidad     == rcl_t) break;
        }
    }
    return indice;
}

void graspBD(vector<Tablas> tbl, vector<Discos> ds) {
    sort(tbl.begin(), tbl.end(), comparaT);
    map<int, vector<int> > solucion;
    int mejor = INT_MIN;
    srand(time(NULL));
    for (int i = 0; i < ITERACIONES; i++) {
        vector<Discos> discos;
        vector<Tablas> tablas;
        map<int, vector<int> > resultado;
        discos.insert(discos.begin(), ds.begin(), ds.end());
        tablas.insert(tablas.begin(), tbl.begin(), tbl.end());
        while (!tablas.empty()) {
            int betaT = tablas[0].velocidad;
            int taoT = tablas[tablas.size() - 1].velocidad;
            double rclT = betaT - alfa * (betaT - taoT);
            int indT = buscarIndice(tablas, rclT);
            int indaT = rand() % indT;

            sort(discos.begin(), discos.end(), comparaD);
            int betaD = discos[0].velocidad;
            int taoD = discos[discos.size() - 1].velocidad;
            double rclD = betaD - alfa * (betaD - taoD);
            int indD = buscarIndice(discos, rclD);
            int indaD = rand() % indD;

            if (discos[indaD].velocidad - tablas[indaT].velocidad >= 0) {
                discos[indaD].velocidad -= tablas[indaT].velocidad;
                resultado[discos[indaD].id].push_back(tablas[indaT].id);
            }
            tablas.erase(tablas.begin() + indaT);
        }
        sort(discos.begin(), discos.end(), comparaD);
        int residual = discos[discos.size() - 1].velocidad;
        if (residual > mejor) {
            mejor = residual;
            solucion.clear();
            solucion = resultado;
        }
    }

    for (auto m: solucion) {
        cout << "Disco " << m.first << ": ";
        for (auto v: m.second) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << "Velociad minimo: " << mejor << endl;
}

int main() {
    vector<Tablas> tablas = {
        {1, 20, 150},
        {2, 10, 100},
        {3, 15, 80},
        {4, 100, 50},
        {5, 50, 120},
        {6, 100, 10}
    };

    vector<Discos> discos = {
        {1, 800, 250,},
        {2, 750, 200},
        {3, 850, 200}
    };

    graspBD(tablas, discos);

    return 0;
}
