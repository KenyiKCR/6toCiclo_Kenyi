#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
#define N 1
#define ALFA 0.15
#define D 10
struct Objeto {
    string ID;
    int weight;
    int height;
    int area;
};

struct Contenedor {
    vector<vector<int>> mapa;
    int espacioRestante;
};

bool comparaO(const Objeto &a, const Objeto &b) {
    return a.area > b.area;
}

bool comparaC(const Contenedor &a, const Contenedor &b) {
    return a.espacioRestante>b.espacioRestante;
}


int buscarInd(double rcl, const vector<Objeto> & vector) {
    int count = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].area >= rcl) {
            count++;
        }
    }
    return count;
}

int buscarInd(double rcl, const vector<Contenedor> & vector) {
    int count = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].espacioRestante >= rcl) {
            count++;
        }
    }
    return count;
}

bool entra(int x,int y, Contenedor &contenedore, const Objeto & objeto) {
    if (x+objeto.height >= D || y+objeto.weight >= D) {
        return false;
    }

    for (int i = x; i < x+objeto.height; i++) {
        for (int j = y; j < y+objeto.weight; j++) {
            if (contenedore.mapa[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

void meterContenedor(int x,int y, Contenedor &contenedore, const Objeto & objeto) {
    for (int i = x; i < x+objeto.height; i++) {
        for (int j = y; j < y+objeto.weight; j++) {
            contenedore.mapa[i][j] = objeto.area;
        }
    }
}

void grasp2D( vector<Objeto> & obj,Contenedor & cont) {
    srand(time(NULL));
    sort(obj.begin(),obj.end(),comparaO);
    vector<Contenedor> solucion;
    int mejor = INT_MAX;
    for (int i = 0; i < N; i++) {
        vector<Objeto> objetos;
        objetos.insert(objetos.end(),obj.begin(),obj.end());
        vector<Contenedor> contenedores;
        contenedores.push_back(cont);
        while (!objetos.empty()) {
            int betaO = objetos[0].area;
            int tauO = objetos[objetos.size()-1].area;
            double rclO = betaO - ALFA*(betaO-tauO);
            int indO = buscarInd(rclO, objetos);
            int indAO = rand()%indO;

            sort(contenedores.begin(),contenedores.end(),comparaC);
            int betaC = contenedores[0].espacioRestante;
            int tauC = contenedores[contenedores.size()-1].espacioRestante;
            double rclC = betaC - ALFA*(betaC-tauC);
            int indC = buscarInd(rclC, contenedores);
            int indAC = rand()%indC;

            bool colocado = false;

            for (int j = 0; j < 10 && !colocado; j++) {
                for (int k = 0; k < 10 && !colocado; k++) {
                   if (entra(j, k, contenedores[indAC], objetos[indAO])) {
                       colocado = true;
                       contenedores[indAC].espacioRestante -= objetos[indAO].area;
                       meterContenedor(j, k, contenedores[indAC], objetos[indAO]);
                   }
                }
            }
            if (!colocado) {
                contenedores.push_back(cont);
                contenedores[contenedores.size()-1].espacioRestante -= objetos[indAO].area;
                meterContenedor(0, 0, contenedores[contenedores.size()-1], objetos[indAO]);
            }

            objetos.erase(objetos.begin()+indAO);
        }

        if (contenedores.size() < mejor) {
            mejor = contenedores.size();
            solucion = contenedores;
        }
    }

    for (int i = 0 ; i < solucion.size(); i++) {
        cout << "Contenedor " << i+1 << ": " << endl;
        for (int j =0; j < D; j++) {
            for (int k = 0; k < D; k++) {
                cout << setw(3) << solucion[i].mapa[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

}

int main() {
    vector<Objeto> objetos = {
        {"A", 6, 5},
        {"B", 4, 5},
        {"C", 3, 3},
        {"D", 5, 5},
        {"E", 2, 1},
        {"F", 7, 3},
        {"G", 3, 7},
        {"H", 2, 6},
        {"I", 4, 4},
        {"J", 5, 2},
        {"K", 1, 7},
        {"L", 7, 1}
    };

    for (auto & objeto : objetos) {
        objeto.area = objeto.weight * objeto.height;
    }

    int height = 10;
    int weight = 10;
    Contenedor contenedorVacio;
    contenedorVacio.mapa.assign(height,vector<int>(weight,0));
    contenedorVacio.espacioRestante = height*weight;
    grasp2D(objetos, contenedorVacio);




    return 0;
}
