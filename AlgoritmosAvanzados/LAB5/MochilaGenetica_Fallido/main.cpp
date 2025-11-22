#include <iostream>
#include <map>
#include <algorithm>
#include <ctime>
#include <vector>
#include <climits>
#include <cmath>
#include <math.h>
#include <queue>

using namespace std;
#define ITERACIONES 1000
#define NUMIND 20
#define TSELECCION 50

int calcularFitness(vector<int> cromo, vector<int> paq) {
    int contador = 0;
    for (int i = 0; i < cromo.size(); i++) {
        if (cromo[i]) contador+=paq[i];
    }
    return contador;
}


void generaPoblacion(map<int, vector<int> > &map, const vector<int> &paq, int size, int peso) {
    int cont = 0;
    srand(time(NULL));
    while (cont < NUMIND) {
        vector<int> individuo;
        double pesoTotal = 0;
        for (int i = 0; i < size; i++) {
            int valor = rand() % 2;
            individuo.push_back(rand() % 2);
            pesoTotal += valor * (paq[i]);
        };
        if (pesoTotal <= peso) {
            map[cont] = individuo;
            cont++;
        }
    }
}

void muestraPoblacion(map<int, vector<int> > &map) {
    for (auto m : map) {
        for (int c : m.second) {
            cout << c << " ";
        }
        cout << endl;
    }
}

void calcularSupervivencia(map<int, vector<int> > poblacion,
    vector<double> &supervivencia, vector<int> paq, int n, int peso) {
    int sumaFitness = 0;
    for (auto m: poblacion) {
        sumaFitness += calcularFitness(m.second, paq);
    }
    for (auto m: poblacion) {
        int superfit;
        superfit = 100*(double)calcularFitness(m.second, paq) / sumaFitness;
        supervivencia.push_back(superfit);
    }
}

void cargarRuleta(vector<double> supervivencia, int * ruleta) {
    int contador = 0;
    for (int i=0; i < supervivencia.size(); i++) {
        for (int j=0; j < supervivencia.size(); j++) {
            ruleta[contador++]=i;
        }
    }
}

void seleccion( map<int, vector<int>> poblacion,map<int, vector<int>> &padres, vector<int> paq, int n, int pesoMax ) {
    int ruleta[100]{-1};
    vector<double> supervivencia;
    calcularSupervivencia(poblacion, supervivencia, paq, n, pesoMax);
    cargarRuleta(supervivencia,ruleta);
    int npadre= round(poblacion.size()*TSELECCION);

    for (int i = 0; i < npadre; i++) {
        int ticket = rand()%100;
        padres[i].push_back(poblacion[ticket[]]);
    }
}

void mochilaAG(vector<int> paq, int peso) {
    map<int, vector<int>> poblacion;

    for (int i = 0; i < ITERACIONES; i++) {
        generaPoblacion(poblacion, paq, paq.size(), peso);
        muestraPoblacion(poblacion);

    }
}

int main() {
    vector<int> paq = {1, 2, 2, 12, 4};
    int peso = 15;
    mochilaAG(paq, peso);
    return 0;
}
