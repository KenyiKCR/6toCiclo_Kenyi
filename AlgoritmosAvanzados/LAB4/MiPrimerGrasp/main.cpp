#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
#define ITERACIONES 10000
#define alfa 0.3
using namespace  std;

bool compara(int a, int b) {
    return a > b;
}
int buscaind(vector<int>paquete,double maxrcl) {
    int cont=0;
    for (int i=0;i<paquete.size();i++)
        if (paquete[i]>=maxrcl)
            cont++;
    return cont;
}

void graspmochila(int *paq,int peso,int n) {
    vector<int> maxsolu;
    int mejorres=INT_MAX;
    srand(time(NULL));
    sort(paq, paq + n, compara);
    for(int i=0;i<ITERACIONES;i++) {

        vector<int>solucion;
        vector<int>paquete;
        paquete.insert(paquete.begin(),paq,paq+n);
        int residual=peso;

        while (!paquete.empty()) {

            int beta=paquete[0];
            int tau=paquete[paquete.size()-1];
            double rcl= beta - alfa*(beta-tau);
            int ind=buscaind(paquete,rcl);
            int indale=rand()%ind;
            if (residual-paquete[indale]>=0) {
                residual-=paquete[indale];
                solucion.push_back(paquete[indale]);
            }
            paquete.erase(paquete.begin()+indale);
        }

        if (residual<=mejorres) {
            mejorres=residual;
            maxsolu.clear();
            maxsolu.insert(maxsolu.begin(),solucion.begin(),solucion.end());
        }
    }
    for(int i=0;i<maxsolu.size();i++) {
        cout << maxsolu[i] << " ";
    }
    cout << endl << mejorres << endl;
}


int main() {
    int paq[]={14,12,15,14,20,11,5,17,14,28,15,27,12,10,30,16,10};
    int peso=102;
    int n=sizeof(paq)/sizeof(paq[0]);
    graspmochila(paq,peso,n);

    return 0;
}