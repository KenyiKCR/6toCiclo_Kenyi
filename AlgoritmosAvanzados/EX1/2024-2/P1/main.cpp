#include <iostream>
#include <climits>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
using namespace std;

int calcularGanancia(int *meses, int n, int K) {
    int dp[K + 1][n]{};

    for (int i = 1; i <= K; i++) {
        for (int j = 1; j < n; j++) {
            int maximo = INT_MIN;
            for (int k = 0; k < j; k++) {
                if (meses[j] - meses[k] >= 0) {
                    maximo = max(maximo, meses[j] - meses[k] + dp[i - 1][k]);
                }
            }
            dp[i][j] = max(maximo, dp[i][j-1]);
        }
    }

    for (int i = 0; i <= K; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return dp[K][n - 1];
}

int main() {
    int n = 8;
    int k = 2;
    int meses[] = {120, 100, 150, 125,120, 150, 200, 250};
    int ganancia = calcularGanancia(meses, n, k);
    cout << "Ganancia: " << ganancia << endl;
    return 0;
}
