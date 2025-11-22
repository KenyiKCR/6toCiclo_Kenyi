#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
#include <map>
using namespace std;

#define ITERACIONES 10000
#define alfa 0



struct Caja {
    int residuo;
    vector<int> paquetes;
};

bool compara(const Caja &a, const Caja &b) {
    return a.residuo > b.residuo; // orden descendente (más disponible primero)
}

bool comparaP(const int &a, const int &b) {
    return a > b; // orden descendente (más disponible primero)
}


int buscarIndice(vector<Caja> cajas, double rcl_val) {
    int cont = 0;
    for (int i = 0; i < cajas.size(); i++)
        if (cajas[i].residuo >= rcl_val)
            cont++;
    return cont;
}

int buscarIndice(vector<int> paq, double rcl_val) {
    int cont = 0;
    for (int i = 0; i < paq.size(); i++)
        if (paq[i] >= rcl_val)
            cont++;
    return cont;
}

void graspEmpaque(vector<int> paq, vector<Caja> cj) {
    vector<Caja> mejorSolucion;
    int mejor = INT_MAX;
    srand(time(NULL));
    sort(paq.begin(), paq.end(),comparaP);
    for (int i = 0; i < ITERACIONES; i++) {
        vector<Caja> cajas;
        vector<int> paquetes;
        int solucion = 1;
        paquetes.insert(paquetes.begin(), paq.begin(), paq.end());
        cajas.insert(cajas.begin(), cj.begin(), cj.end());
        while (!paquetes.empty()) {
            int betaP = paquetes[0];
            int taoP = paquetes[paquetes.size() - 1];
            double rclP = betaP - alfa * ( betaP - taoP);
            int indice = buscarIndice(paquetes, rclP);
            int indaP = rand() % indice;

            sort(cajas.begin(), cajas.end(), compara);
            int beta = cajas[0].residuo;
            int tao = cajas[cajas.size() - 1].residuo;
            double rcl = beta - alfa * (beta - tao);
            int ind = buscarIndice(cajas, rcl);
            int inda = rand() % ind;

            if (cajas[inda].residuo - paquetes[indaP] >= 0) {
                cajas[inda].paquetes.push_back(paquetes[indaP]);
                cajas[inda].residuo -= paquetes[indaP];
            } else {
                cajas.push_back(Caja(10 - paquetes[indaP], {paquetes[indaP]}));
                solucion++;
            }

            paquetes.erase(paquetes.begin()+indaP);
        }
        if (mejor > solucion) {
            mejorSolucion = cajas;
            mejor = solucion;
        }
    }
    for (int i = 0; i < mejorSolucion.size(); i++) {
        cout << "Contenido " << i + 1 << ": ";
        for (auto p: mejorSolucion[i].paquetes) {
            cout << p << " ";
        }
        cout << endl;
    }
    cout << mejorSolucion.size() << endl;
}

int main() {
    vector<int> paquetes = {4, 8, 1, 4, 2, 1};
    vector<Caja> cajas = {{10, {}}};

    graspEmpaque(paquetes, cajas);
    return 0;
}
