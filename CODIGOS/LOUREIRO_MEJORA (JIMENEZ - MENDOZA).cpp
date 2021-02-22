// Para cambiar el tamaño de la tabla, se tiene que cambiar manualmente la variable definida N, en la linea 12.
// Integrantes:
// Jimenez Vivanco, Katherine Virginia
// Mendoza Alejandro, Oscar Andree
#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <ctime>

#define N 79
#define NCUAD N*N
#define VAR_X 0
#define VAR_Y 0

using namespace std;

int long long t[N][N];
const int h[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
const int v[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };
int long long iter=0;

void ShowTable(double time){
	cout<<"VALORES INICIALES -> X: "<<VAR_X<<" , Y: "<<VAR_Y<<"  |  NUMERO DE ITERACIONES: "<<iter<<endl<<endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			cout<<t[i][j]<<"\t";
		}
		cout<<"\n";
	}
	cout<<endl<<"TIEMPO DE EJECUCION: "<<time;
}

void Counter(int x, int y, vector< pair<int, int> > &ops) {
	for (int i = 0; i < 8; i++)
	{
		int xn1 = x + h[i];
		int yn1 = y + v[i];
		if (xn1 >= 0 && xn1 < N && yn1 >= 0 && yn1 < N)
		{
			if(t[xn1][yn1] == 0){
				ops.push_back( make_pair(0,i) );
				for (int j = 0; j < 8; j++)
				{
					int xn2 = xn1 + h[j];
					int yn2 = yn1 + v[j];
					if (xn2 >= 0 && xn2 < N && yn2 >= 0 && yn2 < N)
					{
						if(t[xn2][yn2] == 0){
							ops.back().first = ops.back().first + 1;
						}
					}
				}
			}
		}
	}
	sort(ops.begin(), ops.end());
}

void Tenta(int i, int x, int y, int *q){
	vector< pair<int,int> > ops;
	Counter(x, y, ops);
	
	int m, xn, yn;
	m = 0;
	*q = 0;
	do {
		xn = x + h[ops[m].second];
		yn = y + v[ops[m].second];
		if (xn >= 0 && xn < N && yn >= 0 && yn < N) {
			if (t[xn][yn] == 0) {
				t[xn][yn] = i;
				if (i < NCUAD) {
					Tenta(i+1,xn,yn,q);
					if (!*q){
						t[xn][yn] = 0;
					}
				}
				else *q = 1;
			}
		}
		m=m+1;
		iter=iter+1;
	} while (!*q && m < ops.size());
}

void PasseioDoCavalo(){
	int i,j,q;
	unsigned t0, t1;
	
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			t[i][j] = 0;
		}
	}
	
	t[VAR_X][VAR_Y] = 1;
	t0=clock();
	Tenta(2,VAR_X,VAR_Y,&q);
	t1=clock();
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	
	if (q) {
		ShowTable(time);
		cout<<"VALORES INICIALES -> X: "<<VAR_X<<" , Y: "<<VAR_Y<<"  |  NUMERO DE ITERACIONES: "<<iter<<endl;
		cout<<endl<<"TIEMPO DE EJECUCION: "<<time;
	}
	else{
		cout<<"No existe solucion"<<endl;
	}
}
	
int main(){
	PasseioDoCavalo();
	return 0;
}
