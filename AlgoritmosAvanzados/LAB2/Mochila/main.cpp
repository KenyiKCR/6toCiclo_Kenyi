#include <iostream>
#include <cmath>
using namespace std;



void mochila(int *peso,int *val, int n, int capa) {
    int dp[n+1][capa+1];

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= capa; i++) {
        dp[0][i] = 0;
    }
    int a,b;
    for (int i = 1; i <= capa; i++) {
        for (int j = 1; j <= n; j++) {
            if (i>=peso[j-1]) {
                dp[i][j]=max(dp[j-1][i-peso[j-1]]+val[j-1],dp[j-1][j]);
            }
            else  dp[i][j] = dp[j-1][j];;

        }
    }

    for (int i = 0; i <= capa; i++) {
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

}

int main() {
    int peso[]={2,1,3,2};
    int n=sizeof(peso)/sizeof(peso[0]);
    int valor[]={12,10,20,15};
    int capa=sizeof(valor)/sizeof(valor[0]);

    mochila(peso,valor,n,capa);


    return 0;
}