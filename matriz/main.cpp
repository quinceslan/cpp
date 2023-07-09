#include <iostream>
using namespace std;

const int NUMFIL= 3, NUMCOL= 3;

int main(){
	int matriz[NUMFIL][NUMCOL];
	//Leer matriz
	for(int i= 0; i< NUMFIL; ++i){
		for(int j= 0; j< NUMCOL; ++j){
			cout<<"M["<<i+ 1<<"]["<<j+ 1<<"]= ";
			cin>>matriz[i][j];
		}
	}
	//Ordenar algoritmo burbuja
	const int NUMELE= NUMFIL* NUMCOL;
	for(int i= NUMELE- 2; i>= 0; --i){
		for(int j= 0; j<= i; ++j){
			int &izq= matriz[j/ NUMFIL][j% NUMCOL];
			int k= j+ 1;
			int &der= matriz[k/ NUMFIL][k% NUMCOL];
			if(der> izq)
				std::swap(izq, der);
		}
	}
	//Mostrar matriz
	for(int i= 0; i< NUMFIL; ++i){
		for(int j= 0; j< NUMCOL; ++j){
			cout<<matriz[i][j]<<'\t';
		}
		cout<<'\n';
	}
	return 0;
}
