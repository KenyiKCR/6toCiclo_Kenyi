#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
#define N 10000
#define ALFA 0.3
#define K 20
struct Motorizado{
    int id;
    int costo;
};

struct Ciudad {
    string nombre;
    int costo;
};

bool comparaC(Ciudad a, Ciudad b) {
    return a.costo < b.costo;
}

bool comparaM(Motorizado a, Motorizado b) {
    return a.costo < b.costo;
}

int buscarInd(const map<string, vector<Motorizado>>::mapped_type & mapped, double rcl_m) {
    int contador = 0;
    for(auto it = mapped.begin(); it != mapped.end(); it++) {

    }
}

void graspEntregas( map<string, vector<Motorizado>> & map,  vector<Ciudad> & ciud) {
    srand(time(NULL));

    vector<Ciudad> solucion;
    sort(ciud.begin(), ciud.end(), comparaC);
    for (int i = 0; i < N; i++) {
        vector<Ciudad> ciudades;
        ciudades.insert(ciudades.end(), ciud.begin(), ciud.end());
        vector<Ciudad> resultado;
        while (!ciudades.empty()) {
            int betaC = ciudades[0].costo;
            int tauC = ciudades[ciudades.size() - 1].costo;
            double rclC = betaC + ALFA(tauC-betaC);
            int indC = buscarInd(ciudades,rclC);
            int indAC = rand() % indC;

            sort(map[ciudades[indAC].nombre].begin(), map[ciudades[indAC].nombre].end(), comparaM);
            int betaM = map[ciudades[indAC].nombre][0].costo;
            int tauM = map[ciudades[indAC].nombre][map[ciudades[indAC].nombre].size()-1].costo;
            double rclM = betaM + ALFA(tauM-betaM);
            int indM = buscarInd(map[ciudades[indAC].nombre], rclM);
            int indAM = rand()%indM;

            if (ciudades[indAC].costo + map[ciudades[indAC].nombre][indAM].costo <= K) {
                ciudades[indAC].costo+=map[ciudades[indAC].nombre][indAM].costo;
                resultado.push_back(ciudades[indAC]);
            }
            map[ciudades[indAC].nombre].erase(map[ciudades[indAC].nombre].begin()+indAM);
        }

    }


}

int main() {

    map<string, vector<Motorizado>> mapa = {
        {"A",{{1,3},{2,5},{3,7},{4,8},{5,4}}},
        {"B",{{1,4},{2,2},{3,5},{4,7},{5,3}}},
        {"C",{{1,5},{2,3},{3,4},{4,5},{5,7}}},
        {"D",{{1,6},{2,4},{3,2},{4,1},{5,5}}}
    };

    vector<Ciudad> ciudades = {
        {"A",16},
        {"B",15},
        {"C",12},
        {"D",18}
    };
    graspEntregas(mapa, ciudades);
    return 0;
}
