#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>
#define ITERACIONES 1000
#define NUMIND 10
#define TSELECCION 0.3
#define PCASAMIENTO 0.5
#define TMUTACION 0.5
using namespace std;


double calculafitness(vector<int> ind, vector<int> paq, vector<int> cam) {
    int sum = 0;

    for (int i = 0; i < ind.size(); i++) {
        if (ind[i] != 0) {
            cam[ind[i] - 1] -= paq[i];
        }
    }
    for (int i = 0; i < cam.size(); i++) {
        sum += cam[i];
    }

    return 1.0 / sum;
}


void muestrapoblacion(vector<vector<int> > poblacion, vector<int> paq,
                      vector<int> cam) {
    for (int i = 0; i < poblacion.size(); i++) {
        for (int j = 0; j < poblacion[i].size(); j++) {
            cout << poblacion[i][j] << " ";
        }
        cout << " fo=" << 1 / calculafitness(poblacion[i], paq, cam) << endl;
    }
}

bool aberracion(vector<int> ind, vector<int> cam, vector<int> paq) {
    for (int i = 0; i < ind.size(); i++) {
        if (ind[i] != 0) {
            if (cam[ind[i] - 1] - paq[i] <= 0)
                return true;
            cam[ind[i] - 1] -= paq[i];
        }
    }
    return false;
}

void generapoblacion(vector<vector<int> > &poblacion, vector<int> paq, vector<int> cam) {
    int contador = 0;
    while (contador < NUMIND) {
        vector<int> individuo;
        for (int i = 0; i < paq.size(); i++)
            individuo.push_back(rand() % (cam.size()+1));
        if (!aberracion(individuo, cam, paq)) {
            poblacion.push_back(individuo);
            muestrapoblacion(poblacion, paq, cam);
            cout << endl;
            contador++;
        }
    }
}

string decimal(vector<int> ind) {
    string num;
    for (int i = 0; i < ind.size(); i++) {
        num += to_string(ind[i]);
    }
    return num;
}

void mataclon(vector<vector<int> > &poblacion) {
    map<string, vector<int> > indunicos;

    for (int i = 0; i < poblacion.size(); i++) {
        string dec = decimal(poblacion[i]);
        indunicos[dec] = poblacion[i];
    }
    poblacion.clear();
    for (map<string, vector<int> >::iterator it = indunicos.begin();
         it != indunicos.end(); it++) {
        poblacion.push_back(it->second);
    }
}

void ordenarElite(vector<vector<int> > &poblacion, vector<int> paq, vector<int> cam) {
    sort(poblacion.begin(), poblacion.end(),
         [paq,cam](const vector<int> &a, const vector<int> &b) {
             double fifaA = 0, fifaB = 0;
             fifaA = calculafitness(a, paq, cam);
             fifaB = calculafitness(b, paq, cam);
             return fifaA > fifaB;
         }
    );
    if (poblacion.size() > NUMIND)
        poblacion.erase(poblacion.begin() + NUMIND, poblacion.end());
}


void calculasupervivencia(vector<vector<int> > poblacion,
                          vector<int> &supervivencia, vector<int> paq, vector<int> cam) {
    double sumafitness = 0;

    for (int i = 0; i < poblacion.size(); i++)
        sumafitness += calculafitness(poblacion[i], paq, cam);
    for (int i = 0; i < poblacion.size(); i++) {
        int superfit;
        superfit = round(100 * (double) calculafitness(poblacion[i], paq, cam) / sumafitness);
        supervivencia.push_back(superfit);
    }
}

void cargaruleta(vector<int> supervivencia, int *ruleta) {
    int cont = 0;
    for (int i = 0; i < supervivencia.size(); i++)
        for (int j = 0; j < supervivencia[i]; j++) {
            ruleta[cont++] = i;
        }
}


void seleccion(vector<vector<int> > poblacion, vector<vector<int> > &padres,
               vector<int> paq, vector<int> cam) {
    int ruleta[100]{-1};
    vector<int> supervivencia;
    calculasupervivencia(poblacion, supervivencia, paq, cam);
    cargaruleta(supervivencia, ruleta);
    int npadres = round(poblacion.size() * TSELECCION);

    for (int i = 0; i < npadres; i++) {
        int ticket = rand() % 100;
        if (ruleta[ticket] != -1)
            padres.push_back(poblacion[ruleta[ticket]]);
    }
}

void creahijo(vector<int> padre, vector<int> madre,
              vector<int> &hijo) {
    int posi = round(padre.size() * PCASAMIENTO);

    for (int i = 0; i < posi; i++)
        hijo.push_back(padre[i]);
    for (int i = posi; i < madre.size(); i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int> > &poblacion, vector<vector<int> > padres,
                vector<int> paq, vector<int> cam) {
    for (int i = 0; i < padres.size(); i++)
        for (int j = 0; j < padres.size(); j++) {
            if (i != j) {
                vector<int> hijo;
                creahijo(padres[i], padres[j], hijo);
                if (!aberracion(hijo, cam, paq))
                    poblacion.push_back(hijo);
            }
        }
}

void inversion(vector<vector<int> > &poblacion,
               vector<vector<int> > &padres, vector<int> paq, vector<int> cam) {
    for (int i = 0; i < padres.size(); i++) {
        vector<int> nsol;
        for (int j = 0; j < padres[i].size(); j++) {
            nsol.push_back(cam.size() - padres[i][j]);
        }
        //cout << i <<endl;
        if (!aberracion(nsol, cam, paq))
            poblacion.push_back(nsol);
    }
}

void mutacion(vector<vector<int> > &poblacion,
               vector<vector<int> > &padres, vector<int> paq, vector<int> cam) {
    int nmuta=round(padres[0].size()*TMUTACION);

    for(int i=0;i<padres.size();i++){
        int cont=0;
        while(cont<nmuta){
            int ind=rand()%padres[0].size();
            padres[i][ind]=rand()%(cam.size()+1);
            cont++;
        }
        if(!aberracion(padres[i],cam,paq))
            poblacion.push_back(padres[i]);
    }


}

void mochilaAG(vector<int> cam, vector<int> paq) {
    vector<vector<int> > poblacion;
    generapoblacion(poblacion, paq, cam);
    muestrapoblacion(poblacion, paq, cam);
    for (int i = 0; i < ITERACIONES; i++) {
        cout << "Generacion " << i << endl;
        vector<vector<int> > padre;
        seleccion(poblacion, padre, paq, cam);
        casamiento(poblacion, padre, paq, cam);
        inversion(poblacion, padre, paq, cam);
        mutacion(poblacion,padre, paq, cam);
        mataclon(poblacion);
        ordenarElite(poblacion, paq, cam);
        muestrapoblacion(poblacion, paq, cam);
        cout << endl;
    }
}


int main() {
    vector<int> camiones = {250, 200, 200, 100};
    vector<int> paquetes = {150, 100, 180, 50, 120, 10};

    srand(time(NULL));
    mochilaAG(camiones, paquetes);
    //en ocasiones el algoritmo se queda en bucle, porque no encuentra un buen individuo, ya que las posibilidades son muy bajas
    //existen 2^24=16,777,216, y las combinaciones posibles son muy pocas por loque las probabilidades de encontrar una buenas son muy bajas
    // por lo tanto, en caso el programa se queda en bucle es por la probabilidad de obtencion de individuos
    // ya lo hable con piero :)
    return 0;
}
