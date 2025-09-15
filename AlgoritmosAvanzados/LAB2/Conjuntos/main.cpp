#include <iostream>

using namespace std;


void subconjunto(int *paq,int n,int pesos) {
    int dp[n+1][pesos+1];

    for(int i=0;i<=n;i++) {
       dp[i][0]=1;
    }

    for(int i=1;i<=pesos;i++) {
        dp[0][i]=0;
    }

    for(int j=0;j<=n;j++) {
        for(int i=0;i<=pesos;i++) {
            cout << dp[j][i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int paq[]={2,3,6};
    int pesos=10;
    int n = sizeof(paq)/sizeof(paq[0]);
    subconjunto(paq,n,pesos);
    return 0;
}