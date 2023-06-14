#include <iostream>
using namespace std;

const int NUMDEPOSITOS= 4;

void leer(const string &etiqueta, int &valor, int max){
    do{
        cout<<etiqueta;
        cin>>valor;
        if(cin.good() && cin.get()== '\n'){
            if(valor> 0 && valor<= max) return;
            cout<<"Ingrese un valor entre 1 y "<<max<<"\n\n";
            continue;
        }
        cout<<"Ingrese un numero entero.\n\n";
        cin.clear();
        while(cin.get()!= '\n');
    }while(true);
}

int main(){
    int depositos[NUMDEPOSITOS][2]= {{1, 0}, {2, 0}, {3, 0}, {4, 0}};
    int deposito, articulo, vendedor, venta;
    int maxVenta= 0, maxDeposito= 0, maxArticulo= 0, maxVendedor= 0;
    do{
        cout<<"\nIngrese detalles de la venta:\n";
        leer("No. deposito: ", deposito, 5);
        if(deposito== 5) break;
        leer("No. articulo: ", articulo, 10);
        leer("No. vendedor: ", vendedor, 12);
        leer("Valor venta : ", venta, 10000000);
        if(venta> maxVenta){
            maxVenta= venta;
            maxDeposito= deposito;
            maxArticulo= articulo;
            maxVendedor= vendedor;
        }
        depositos[deposito- 1][1]+= venta;
    }while(true);
    cout<<"\nVenta maxima: "<<maxVenta<<'\n';
    cout<<"No. deposito: "<<maxDeposito<<'\n';
    cout<<"No. Articulo: "<<maxArticulo<<'\n';
    cout<<"No. Vendedor: "<<maxVendedor<<"\n\n";
    for(int i= 0; i< NUMDEPOSITOS- 1; ++i){
        for(int j= i+ 1; j< NUMDEPOSITOS; ++j){
            if(depositos[j][1]> depositos[i][1]){
                swap(depositos[i], depositos[j]);
            }
        }
    }
    cout<<"\nMostrando ventas totales por deposito:\n\n";
    for(const auto &dep: depositos){
        cout<<"N0. dep: "<<dep[0]<<" Total ventas: "<<dep[1]<<'\n';
    }
    return 0;
}
