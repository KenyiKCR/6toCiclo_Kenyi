#include <iostream>
using namespace std;
#define K 4

int y = 0;

int estados[]{1, 1, 1, 1, 1, 1};
int estadosLocal[]{1, 1, 1, 1, 1, 1};

int pedidosAtender(int *paq, int pos, int cant, int peso, int *arrSol, int m) {
    if (pos == cant or peso < 0)
        return 0;

    if (paq[pos] == peso) {
        arrSol[m] = paq[pos]; // cambio de estados

        cout << "RESULTADOS:";
        for (int i = 0; i <= m; i++)
            cout << arrSol[i] << " ";
        cout << endl;
        return 0;
    }

    arrSol[m] = paq[pos];


    if (pedidosAtender(paq, pos + 1, cant, peso - paq[pos], arrSol, m + 1)) return 1;
    else {
        arrSol[m] = 0;
        return pedidosAtender(paq, pos + 1, cant, peso, arrSol, m);
    }
}

int main() {
    int arrPaq[] = {2, 8, 9, 6, 7, 6};
    int n = sizeof(arrPaq) / sizeof(arrPaq[0]);
    int peso = 15;
    int arrSol[n];
    pedidosAtender(arrPaq, 0, n, peso, arrSol, 0);
    cout << "se puede atender: " << y << endl;
    return 0;
}
