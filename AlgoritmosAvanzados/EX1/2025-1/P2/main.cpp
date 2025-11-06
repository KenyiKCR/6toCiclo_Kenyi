#include <iostream>
#include <vector>
#include  <algorithm>
using namespace std;

struct Orden {
    int id;
    int cantidadBotellas;
};

struct Linea {
    int id;
    vector<Orden> ordenes;
    double cargarTotal;
};

bool compara(const Linea &L1, const Linea &L2) {
    return L1.cargarTotal < L2.cargarTotal or
    (L1.cargarTotal ==  L2.cargarTotal and L1.id < L2.id);
}

bool comparaLineas(const Linea &L1, const Linea &L2) {
    return L1.id < L2.id ;
}

void calculoVoraz(vector<Orden> ordenes, vector<Linea> &lineas) {
    for (int i = 0; i < ordenes.size(); i++) {
        sort(lineas.begin(), lineas.end(), compara);
        lineas[0].ordenes.push_back(ordenes[i]);
        lineas[0].cargarTotal += ordenes[i].cantidadBotellas * 6;
    }
    sort(lineas.begin(), lineas.end(), comparaLineas);
}

int main() {
    vector<Orden> ordenesAsignadas = {
        {1, 103},
        {2, 58},
        {3, 88},
        {4, 126},
        {5, 195},
        {6, 90},
        {7, 54},
        {8, 195},
        {9, 124},
        {10, 113},
        {11, 193},
        {12, 55},
        {13, 97},
        {14, 97},
        {15, 169},
        {16, 50},
        {17, 167},
        {18, 74},
        {19, 79},
        {20, 109}
    };
    vector<Linea> lineas = {
        {1,{}, 0},
        {2,{}, 0},
        {3,{}, 0},
        {4,{}, 0},
        {5,{}, 0}
    };

    calculoVoraz(ordenesAsignadas, lineas);

    for (int i = 0; i < lineas.size(); i++) {
        cout << "Linea " << lineas[i].id ;
        for (int j = 0; j < lineas[i].ordenes.size(); j++) {
            cout << "," << lineas[i].ordenes[j].id << "(" << lineas[i].ordenes[j].cantidadBotellas << ")";
        }
        cout << ", " << lineas[i].cargarTotal << endl;
    }

    return 0;
}
