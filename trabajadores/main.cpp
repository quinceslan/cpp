#include <iostream>
#include <iomanip>

using namespace std;

struct Employee{
    string name;
    int seniority;
};

const int MAXLIST= 30;

int main(){
    Employee list[MAXLIST];
    int count= 0;
    cout<<"Ingrese la lista de empleados a evaluar:\n\n";
    cout<<"Para terminar ingrese en nombre una cadena vacía:\n\n";
    do{
        cout<<"Nombre    : ";
        getline(cin, list[count].name);
        if(list[count].name.size()== 0) break;
        cout<<"Antiguedad: ";
        cin>>list[count].seniority;
        cin.ignore();
        count+= 1;
        cout<<'\n';
    }while(count< MAXLIST);
    // Ordenando de mayor a menor antiguedad por
    // algoritmo de selection sort
    for(int i= 0; i< count- 1; ++i){
        for(int j= i+ 1; j< count; ++j){
            if(list[j].seniority> list[i].seniority){
                swap(list[i], list[j]);
            }
        }
    }
    //mostrando lista
    for(int i= 0; i< count; ++i){
        cout<<setw(3)<<list[i].seniority<<' '<<list[i].name<<'\n';
    }
    return 0;
}
