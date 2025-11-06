#include <iostream>

using namespace std;

double matriz[6][6] = {
    {0.00, 2.24, 2.69, 4.00, 2.06, 3.35},
    {2.24, 0.00, 4.50, 5.39, 1.50, 5.59},
    {2.69, 4.50, 0.00, 5.59, 4.74, 2.55},
    {4.00, 5.39, 5.59, 0.00, 4.03, 3.91},
    {2.06, 1.50, 4.74, 4.03, 0.00, 5.10},
    {3.35, 5.59, 2.55, 3.91, 5.10, 0.00}
};

int arrSol[6]{};
int arrVisitado[6]{};
int solucionesTotales = 0;

bool fueVisitado(int i) {
    for (int j = 1; j < 6; j++) {
        if (arrVisitado[j] == i) return true;
    }
    return false;
}

int calcularRuta(int pos, int n, double &distanciaMin, double distaciaAcumulada, int cantVisitas) {
    if (cantVisitas == n) {
        solucionesTotales++;
        distaciaAcumulada += matriz[pos][0];
        if (distanciaMin > distaciaAcumulada) {
            distanciaMin = distaciaAcumulada;
            for (int i = 0; i < 6; i++) {
                arrSol[i] = arrVisitado[i];
            }
        }
        return 0;
    }
    for (int i = 1; i < n; i++) {
        if (!fueVisitado(i)) {
            arrVisitado[cantVisitas] = i;
            cantVisitas++;
            distaciaAcumulada += matriz[pos][i];
            if (calcularRuta(i, n, distanciaMin, distaciaAcumulada, cantVisitas)) {
                return 1;
            } else {
                cantVisitas--;
                arrVisitado[cantVisitas] = 0;
                distaciaAcumulada -= matriz[pos][i];
            }
        }
    }
    return 0;
}

int main() {
    double distanciaMin = 999;
    calcularRuta(0, 6, distanciaMin, 0, 1);
    cout << "Numero de rutas generadas: " << solucionesTotales << endl;
    cout << "Ruta optima: ";
    for (int i = 0; i < 6; i++) {
        cout <<arrSol[i] << " ";
    }
    cout <<  "(distancia " << distanciaMin <<")"<< endl;
}
