/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 10 de junio de 2025, 03:18 PM
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iterator>
#include <map>
#include <algorithm>
#define IND 15
#define ITERACIONES 1000
#define TSELECCION 0.5
#define TCASAMIENTO 0.5
#define TMUTACION 0.5

int *gpaq;

using namespace std;


int calculafitness(vector<int>cromo,int *paq){
    // miralo
    int cont=0;
    for(int i=0;i<cromo.size();i++)
        cont+=cromo[i]*paq[i];
    
    return cont;
}

void muestrapoblacion(vector<vector<int>> poblacion,int *paq){
    for(int i=0;i<poblacion.size();i++){
        for(int j=0;j<poblacion[i].size();j++){
            cout << poblacion[i][j] << "  ";
        }
        cout <<" fo="<< calculafitness(poblacion[i],paq) <<endl;
    }
    cout <<endl;
}
        

bool aberracion(vector<int>vcromo,int *paq,int peso){
    //no tocar se puede caer!!!
    int total=0;
    for(int i=0;i<vcromo.size();i++)
        total+=vcromo[i]*paq[i];
    return total>peso;
}

void generapoblacioninicial(vector<vector<int>>&poblacion,
    int *paq,int n,int peso){
    int cont=0;
    
    srand(time(NULL));  
    while(cont<IND){
        vector<int>vcromo;
        for(int j=0;j<n;j++)
            vcromo.push_back(rand()%2);
        if(!aberracion(vcromo,paq,peso)){
            poblacion.push_back(vcromo);
            cont++;
        }
    }
}
void calculosupervivencia(vector<vector<int>>poblacion,
    vector<int>&vsupervivencia,int *paq,int peso,int n){
    // !!!sigue adelante!!!
    int suma=0;
    
    for(int i=0;i<poblacion.size();i++)
        suma+=calculafitness(poblacion[i],paq);
    for(int i=0;i<poblacion.size();i++){
        int porsup= round(100*calculafitness(poblacion[i],paq)/suma);
        vsupervivencia.push_back(porsup);
    }
}
void cargaruleta(vector<int>vsupervivencia,int *ruleta){
    //!considerar en el desarrollo
    int ind=0;
    for(int i=0;i<vsupervivencia.size();i++)
        for(int j=0;j<vsupervivencia[i];j++)
            ruleta[ind++]=i;
}

void seleccion(vector<vector<int>>&padres,
        vector<vector<int>>poblacion,int *paq,int n,int peso){

    int ruleta[100];
    for(int i=0;i<100;i++)
        ruleta[i]=-1;
    vector<int>vsupervivencia;
    calculosupervivencia(poblacion,vsupervivencia,paq,peso,n);
    cargaruleta(vsupervivencia,ruleta);
    int nselect=TSELECCION*poblacion.size();
    for(int i=0;i<nselect;i++){
        int ind=rand()%100;
        if(ruleta[ind]>-1)
            padres.push_back(poblacion[ruleta[ind]]);
    }
   // cout <<endl;
}

void generahijo(vector<int>padre,vector<int>madre,
        vector<int>&hijo){
    // Con punto de corte
  
    int pos=round(padre.size()*TCASAMIENTO);  
    for(int i=0;i<pos;i++)
        hijo.push_back(padre[i]);
    for(int i=pos;i<madre.size();i++)
        hijo.push_back(madre[i]);
}


void casamiento(vector<vector<int>> padres,
    vector<vector<int>>&poblacion,int*paq,int peso){
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if(i!=j){
                vector<int>hijo;
                generahijo(padres[i],padres[j],hijo);
                if(!aberracion(hijo,paq,peso))
                    poblacion.push_back(hijo);
            }   

}

void inversion(vector<vector<int>>&poblacion,
        vector<vector<int>>padres,int*paq,int peso){
    // !modificar segun caso
    for(int i=0;i<padres.size();i++){
        vector<int>nsol;
        for(int j=0;j<padres[i].size();j++){
         if(padres[i][j]==0)
             nsol.push_back(1);
         else
             nsol.push_back(0);
        }
        //cout << i <<endl;
        if(!aberracion(nsol,paq,peso))
            poblacion.push_back(nsol);
    }
}

int calculadecimal(vector<int>cromo){
    int num=0;
    for(int i=0;i<cromo.size();i++)
        num+=pow(2,i)*cromo[i]; 
    return num;
}


void eliminarepetidos(vector<vector<int>>&poblacion){
    map<int,vector<int>>municos;
    
    for(int i=0;i<poblacion.size();i++){
        int dec=calculadecimal(poblacion[i]);
        municos[dec]=poblacion[i];
    }
    poblacion.clear();
    for(map<int,vector<int>>::iterator it=municos.begin();
            it!=municos.end();it++)
        poblacion.push_back(it->second);    
}
bool compara(vector<int>a,vector<int>b){
    int fa=calculafitness(a,gpaq);
    int fb=calculafitness(b,gpaq);
    return fa>fb;
}


void generarelite(vector<vector<int>>&poblacion,
        int*paq){
    gpaq=paq;
    sort(poblacion.begin(),poblacion.end(),compara);
    poblacion.erase(poblacion.begin()+IND,poblacion.end()); 
}

void mutacion(vector<vector<int>>&poblacion, 
        vector<vector<int>>padres,int*paq,int peso){
    
    int nmuta=round(padres[0].size()*TMUTACION);
    
    for(int i=0;i<padres.size();i++){
        int cont=0;
        while(cont<nmuta){
            int ind=rand()%padres[0].size();
            if(padres[i][ind]==1)
                padres[i][ind]=0;
            else
                padres[i][ind]=1;
            cont++;
        }
        if(!aberracion(padres[i],paq,peso))
            poblacion.push_back(padres[i]);
    }
    
    
    
}
void mochilagenetica(int *paq,int n,int peso){
    int cont=0;
    vector<vector<int>> poblacion;
    
    generapoblacioninicial(poblacion,paq,n,peso);
    
    while(1){
        vector<vector<int>>padres;
        seleccion(padres,poblacion,paq,n,peso);
        casamiento(padres,poblacion,paq,peso);
        inversion(poblacion,padres,paq,peso);
        mutacion(poblacion,padres,paq,peso);
        eliminarepetidos(poblacion);
        generarelite(poblacion,paq);
        cont++;
        if(cont==ITERACIONES) break;
    }
    muestrapoblacion(poblacion,paq); 
}


int main(int argc, char** argv) {
    
    int paq[]={4,9,10,3,15,11,9,20,12,9,10,11,18,27,14,15};
    int peso=53;
    int n=sizeof(paq)/sizeof(paq[0]);
    
    mochilagenetica(paq,n,peso);

    return 0;
}

