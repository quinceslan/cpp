#include <iostream>
#include <vector>

using namespace std;

struct Socio{
    char tipo;
    string nombreTipo;
    double cuota, aniversario, canchas;
};

const Socio socios[]= {
    {'A', "Vip"      ,  90.00, 20.0, 4.0},
    {'R', "Regular"  , 120.00, 25.0, 6.0},
    {'N', "Nuevo"    , 170.00, 30.0, 8.0},
    {'V', "Vitalicio",  60.00,  0.0, 0.0}
};

string obtenerTipos(){
    string tipos;
    for(const Socio &socio: socios){
        tipos.push_back(socio.tipo);
        tipos+= " "+ socio.nombreTipo;
        tipos.push_back('\n');
    }
    return tipos;
}

bool esTipoPermitido(char tipo){
    for(const Socio &socio: socios){
        if(tipo== socio.tipo){
            return true;
        }
    }
    return false;
}

struct TipoPago{
    char tipo;
    string descripcion;
};

const TipoPago tipoPagos[]= {
    {'E', "Efectivo"},
    {'T', "Tarjeta"},
    {'D', "Deposito"}
};

string obtenerTipoPagos(){
    string tipos;
    for(const TipoPago &tipo: tipoPagos){
        tipos.push_back(tipo.tipo);
        tipos+= " "+ tipo.descripcion;
        tipos.push_back('\n');
    }
    return tipos;
}

bool esTipoPagoPermitido(char tipo){
    for(const TipoPago &tipoPago: tipoPagos){
        if(tipoPago.tipo== tipo){
            return true;
        }
    }
    return false;
}

struct PagoPorHijo{
    unsigned hijos;
    double pago;
};

const PagoPorHijo pagosPorHijo[]{
    {1, 30.00},
    {2, 30.00},
    {3, 50.00},
    {4, 50.00},
    {5, 70.00},
    {6, 70.00}
};

struct Registro{
    string nombre;
    char tipo;
    unsigned edad, hijos;
    char pago;
    unsigned canchas;
};

template<typename T>
void leer(const string &etiqueta, T &dato){
    do{
        cout<<etiqueta;
        cin>>dato;
        if(cin.good() && cin.get()== '\n') break;
        cout<<"Error en formato de entrada\n\n";
        cin.clear();
        while(cin.get()!= '\n');
    }while(true);
}

template<>
void leer(const string &etiqueta, string &cadena){
    do{
        cout<<etiqueta;
        getline(cin, cadena);
        if(cadena.size()>= 3 && cadena.size()< 15) break;
        cout<<"Ingrese entre 3 y 15 caracteres\n\n";
    }while(true);
}

template<>
void leer(const string &etiqueta, Registro &registro){
    cout<<etiqueta<<'\n';
    leer("Nombre: ", registro.nombre);
    string menu= "Escoja un tipo:\n";
    menu+= obtenerTipos();
    menu+= "Opcion: ";
    do{
        leer(menu, registro.tipo);
        if(esTipoPermitido(registro.tipo)) break;
        cout<<"Ingrese un tipo de la lista\n\n";
    }while(true);
    do{
        leer("Edad : ", registro.edad);
        if(registro.edad>0 && registro.edad<= 110) break;
        cout<<"Ingrese una edad entre 1 - 110\n\n";
    }while(true);
    do{
        leer("Hijos : ", registro.hijos);
        if(registro.hijos> 0 && registro.hijos<= 6) break;
        cout<<"Numero de hijos entre 1 - 6\n\n";
    }while(true);
    menu= "Opcions de pago:\n";
    menu+= obtenerTipoPagos();
    menu+= "Opcion: ";
    do{
        leer(menu, registro.pago);
        if(esTipoPagoPermitido(registro.pago)) break;
        cout<<"Ingrese un tipo de pago de la lista\n\n";
    }while(true);
    leer("Canchas: ", registro.canchas);
}

unsigned canchasOcupadas(const vector<Registro> &registros){
    unsigned canchas= 0;
    for(const Registro &registro: registros){
        canchas+= registro.canchas;
    }
    return canchas;
}

int main(){
    unsigned stock= 20;
    int opcion;
    vector<Registro> registros;
    Registro nuevoRegistro;

    registros.reserve(stock);
    string menu= "   Alquiler de canchas\n";
    menu+= "  1. Registrar socio\n";
    menu+= "  2. Aumentar Stock\n";
    menu+= "  0. Salir\n";
    menu+= "Opcion: ";
    do{
        leer(menu, opcion);
        switch(opcion){
            case 1:
                leer("Ingrese nuevo registro: ", nuevoRegistro);
                if((canchasOcupadas(registros)+ nuevoRegistro.canchas)> stock){
                    cout<<"No has canchas disponibles\n\n";
                }
                else{
                    registros.push_back(nuevoRegistro);
                    cout<<"Registro agregado exitosamente\n\b";
                }
                break;
            case 2:
                unsigned nuevoStock;
                leer("Ingrese el nuevo stock: ", nuevoStock);
                stock+= nuevoStock;
                break;
            case 0:
                cout<<"Saliendo...\n\n";
                break;
            default:
                cout<<"Opcion incorrecta.\n\n";
        }
    }while(opcion!= 0);
    return 0;
}
