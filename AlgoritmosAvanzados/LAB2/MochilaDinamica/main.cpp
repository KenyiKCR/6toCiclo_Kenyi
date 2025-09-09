#include <iostream>
#include <cmath>

using namespace std;


void mochilaDinamica(int (*matrizSol)[5], int *arrMochila, int *arrPesos) {
	int a,b;
	for (int i = 1; i < 5; i++) {
        for (int j = 1; j < 5; j++) {
            a=matrizSol[j-1][i];
            if (i>=arrPesos[j-1]) {
                b=matrizSol[j-1][i-arrPesos[j-1]]+arrMochila[j-1];
            }
            else {
                b=0;
            }
            matrizSol[j][i]=max(a,b);
        }
    }
}

int main() {
    int matrizSol[5][5]{};
    int arrMochila[] = {12, 10, 20, 15};
    int arrPesos[] = {2, 1, 3, 2};
    mochilaDinamica(matrizSol, arrMochila, arrPesos);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrizSol[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Valor de matrizSol:" << matrizSol[4][4]<<endl;
    return 0;
}
