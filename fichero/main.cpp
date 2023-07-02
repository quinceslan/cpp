#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
using namespace std;

// crear dos ficheros de texto 'origen1.md' y 'origen2.md' para la ejecucion del programa
// no se han comprobaciones de error mas que verificar si el fichero esta abierto o no

void copiar_informacion_a(const string &origen, const string &destino){
    ifstream entrada(origen, ios::binary);            //entrada y salida abiertos en binario
    ofstream salida(destino, ios::app | ios::binary); //salida abierto en 'app' para agregar al final
    if(!entrada.is_open()){
        cout<<"Error al abrir '"<<origen<<"' para lectura de informacion"<<endl;
        exit(EXIT_FAILURE);
    }
    if(!salida.is_open()){
        cout<<"Error al abrir '"<<destino<<"' para agregar informacion"<<endl;
        exit(EXIT_FAILURE);
    }
    char info;
    while(entrada.read(&info, sizeof(char))){
        salida.write(&info, sizeof(char));
    }
    entrada.close();
    salida.close();
}

void intercambiar_mayusculas_a_minusculas(const string &origen, const string &destino){
    ifstream entrada(origen);
    ofstream salida(destino, ios::trunc);   //se abre con 'trunc' para eliminar el contenido anterior
    if(!entrada.is_open()){
        cout<<"Error al abrir '"<<origen<<"' para lectura de informacion"<<endl;
        exit(EXIT_FAILURE);
    }
    if(!salida.is_open()){
        cout<<"Error al abrir '"<<destino<<"' para agregar informacion"<<endl;
        exit(EXIT_FAILURE);
    }
    char info= entrada.get();
    while(!entrada.eof()){      //se hace la comprobacion de eof() después de una lectura
        if(isupper(info)){      //si es mayuscula
            info= tolower(info);//convertimos a minuscula
        }
        else if(islower(info)){ //si es minuscula
            info= toupper(info);//convertimos a mayuscula
        }
        salida.put(info);
        info= entrada.get();    //se lee el siguiente caracter
    }
    entrada.close();
    salida.close();
}

int contar_palabras_de(const string &origen){
    ifstream entrada(origen);
    if(!entrada.is_open()){
        cout<<"Error al abrir '"<<origen<<"' para lectura de informacion"<<endl;
        exit(EXIT_FAILURE);
    }
    string palabra;
    int contador= 0;
    while(entrada>>palabra){
        //cada lectura exitosa es una palabra
        //esto cuando se usa el operador >> y destino un string
        contador+= 1;
    }
    entrada.close();
    return contador;
}

int main(){
    const string ORIGEN1= "origen1.md", ORIGEN2= "origen2.md";
    const string DESTINO_COPIA= "copia.md";
    const string DESTINO_CAMBIO= "cambio.md";

    //efectuamos la copia de dos archivos a un tercero
    remove(DESTINO_COPIA.c_str());    //si 'copia.md' existe lo eliminamos
    copiar_informacion_a(ORIGEN1, DESTINO_COPIA);
    copiar_informacion_a(ORIGEN2, DESTINO_COPIA);

    //efectuamos el cambio de mayusculas a minusculas y viceversa
    intercambiar_mayusculas_a_minusculas(ORIGEN1, DESTINO_CAMBIO);

    //Contamos las palabras de origen2
    int num_palabras= contar_palabras_de(ORIGEN2);
    cout<<"En el archivo origen2.md hay "<<num_palabras<<" palabras."<<endl;

    return 0;
}
