#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>
#define ITERACIONES 100
#define NUMIND 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.5
#define TMUTACION 0.3

using namespace std;

bool aberracion(vector<int> individuo, vector<int> barras, vector<int> pedido) {
    for (int i = 0; i < individuo.size(); i++) {
        if (individuo[i] != 0) {
            if (barras[individuo[i] - 1] - pedido[i] < 0)
                return true;
            barras[individuo[i] - 1] -= pedido[i];
        }
        else return true;
    }
    return false;
}

double calculafitness(vector<int> individuo, vector<int> barras, vector<int> pedido) {
    int sum = 0;
    for (int i = 0; i < individuo.size(); i++) {
        if (individuo[i] != 0) {
            barras[individuo[i] - 1] -= pedido[i];
        }
    }
    for (int i = 0; i < barras.size(); i++) {
        if (barras[i] != 10) {
            sum += barras[i];
            if (barras[i]!=0)
                sum += 1000;
        }
    }
    return 1.0 / sum;
}

void muestrapoblacion(vector<vector<int> > poblacion, vector<int> barras, vector<int> pedido) {
    for (int i = 0; i < poblacion.size(); i++) {
        for (int j = 0; j < poblacion[i].size(); j++) {
            cout << poblacion[i][j] << " ";
        }
        cout << " fo=" << 1 / calculafitness(poblacion[i], barras, pedido) << endl;
    }
}


void generapoblacion(vector<vector<int> > &poblacion,
                     vector<int> barras, vector<int> pedido) {
    int cont = 0;
    srand(time(NULL));
    while (cont < NUMIND) {
        vector<int> individuo;
        // aqui también cambiar
        for (int i = 0; i < pedido.size(); i++)
            individuo.push_back(rand() % barras.size() + 1);
        if (!aberracion(individuo, barras, pedido)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,vector<int> barras, vector<int> pedido) {
    double sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],barras,pedido);
    for (int i=0;i<poblacion.size();i++) {
        double superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],barras,pedido)/sumafitness);
        supervivencia.push_back(superfit);
    }
}

void cargaruleta(vector<int >supervivencia,int *ruleta) {
    int cont=0;
    for (int i=0;i<supervivencia.size();i++)
        for (int j=0;j<supervivencia[i];j++) {
            ruleta[cont++]=i;
        }
}

void seleccion(vector<vector<int> > &poblacion,
    vector<vector<int> > &padres,
    vector<int> barras,vector<int> pedidos) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,barras,pedidos);
    cargaruleta(supervivencia,ruleta);
    int npadres=round(poblacion.size()*TSELECCION);

    for (int i=0;i<npadres;i++) {
        int ticket=rand()%100;
        if (ruleta[ticket]!=-1)
            padres.push_back(poblacion[ruleta[ticket]]);
    }
}

void creahijo(vector<int>padre,vector<int>madre,
    vector<int>&hijo) {
    int posi=round(padre.size()*PCASAMIENTO);

    for (int i=0;i<posi;i++)
        hijo.push_back(padre[i]);
    for (int i=posi;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int> > &poblacion,
    vector<vector<int> > &padres,
    vector<int> barras,vector<int> pedidos) {
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,barras,pedidos))
                    poblacion.push_back(hijo);
            }


        }
}

void mutacion(vector<vector<int> > &poblacion,
    vector<vector<int> > &padres,
    vector<int> barras,vector<int> pedidos) {
    int nmutaciones=round(padres[0].size()*TMUTACION);
    for (int i=0;i<padres.size();i++) {
        int cont=0;
        while (cont<nmutaciones) {
            int gen=rand()%padres[i].size();
            //aqui hay que cambiar si son numeros enteros

            padres[i][gen]=rand()%(barras.size()+1);
            cont++;
        }
        if (!aberracion(padres[i],barras,pedidos))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int> > &poblacion,
    vector<vector<int> > &padres,
    vector<int> barras,vector<int> pedidos) {
    for (int i=0;i<padres.size();i++) {
        for (int j=0;j<padres[i].size();j++) {
            //cambiar para numeros enteros
            padres[i][j]=barras.size() - padres[i][j];
        }
        if (!aberracion(padres[i],barras,pedidos))
            poblacion.push_back(padres[i]);
    }
}

string decimal(vector<int>ind) {
    string num="";
    for (int i=0;i<ind.size();i++)
        num+=ind[i];
    return num;
}

void mataclon(vector<vector<int>> &poblacion) {
    map<string,vector<int>> indunicos;

    for(int i=0;i<poblacion.size();i++) {
        string dec=decimal(poblacion[i]);
        indunicos[dec]=poblacion[i];
    }
    poblacion.clear();
    for(map<string,vector<int>>::iterator it=indunicos.begin();
        it!=indunicos.end();it++) {
        poblacion.push_back(it->second);
        }
}

void regenera(vector<vector<int> > &poblacion,
    vector<vector<int> > &padres,
    vector<int> barras,vector<int> pedidos) {

    sort(poblacion.begin(), poblacion.end(),
         [barras,pedidos](const vector<int>& a, const vector<int>& b) {
            double fifaA,fifaB;
             fifaA=calculafitness(a,barras,pedidos);
             fifaB=calculafitness(b,barras,pedidos);
            return fifaA > fifaB;
         });
    if (poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,poblacion.end());
}


int muestramejor(vector<vector<int>> poblacion,
        vector<int> barras,vector<int>pedidos){
    int mejor=0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],barras,pedidos)<calculafitness(poblacion[i],barras,pedidos))
            mejor=i;

    cout << endl<<"La mejor solucion es:" << 1/calculafitness(poblacion[mejor],barras,pedidos)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++)
        cout << poblacion[mejor][i] << "  ";

    cout << endl;
    return calculafitness(poblacion[mejor],barras,pedidos);
}

void geneticoBarras(vector<int> barras, vector<int> pedido) {
    vector<vector<int> > poblacion;
    generapoblacion(poblacion, barras, pedido);
    muestrapoblacion(poblacion, barras, pedido);
    for (int i = 0; i < ITERACIONES; i++) {
        vector<vector<int>> padres;
        seleccion(poblacion,padres,barras,pedido);
        casamiento(poblacion,padres,barras,pedido);
        mutacion(poblacion,padres,barras,pedido);
        inversion(poblacion,padres,barras,pedido);
        mataclon(poblacion);
        regenera(poblacion,padres,barras,pedido);
        muestramejor(poblacion,barras,pedido);
    }
}



int main() {
    vector<int> barras;
    int longitud = 10;
    int nbarras = 9;
    barras.assign(nbarras, longitud);
    vector<int> pedido = {5, 2, 3, 10, 3, 7, 2, 10};

    geneticoBarras(barras, pedido);

    return 0;
}
