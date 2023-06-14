#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

template<typename T>
void leer(const string &etiqueta, T &valor){
	do{
		cout<<etiqueta;
		cin>>valor;
		if(cin.good() && cin.get() == '\n') break;
		cout<<"Error en el formato de entrada.\n\n";
		cin.clear();
		while(cin.get()!= '\n');
	}while(true);
}

template<>
void leer<string>(const string &etiqueta, string &cadena){
	do{
		cout<<etiqueta;
		getline(cin, cadena);
		if(cadena.size() >= 3 && cadena.size() <= 12) break;
		cout<<"Ingrese de 3 a 12 caracteres.\n\n";
	}while(true);
}

void mostrar_mensaje(const string &mensaje){
	cout<<mensaje<<'\n';
	while(cin.get() != '\n');
}

struct Asiento
{
	bool    libre{true};
	string  nombre, apellido;
	int     identificacion;
};

void registrar_pasajero(Asiento &asiento){
	asiento.libre= false;
	leer("Nombre        : ", asiento.nombre);
	leer("Apellido      : ", asiento.apellido);
	leer("Identificacion: ", asiento.identificacion);
}

const unsigned NUMFIL = 10;
const unsigned NUMCOL = 5;
using Moneda = unsigned long;
const Moneda PREFERENCIAL= 600000;
const Moneda GENERAL= 450000;

struct Vuelo
{
	Asiento asientos[NUMFIL][NUMCOL];
	Moneda  total;
};

bool esta_libre(const Vuelo &vuelo, unsigned fil, unsigned col){
	if(fil>= NUMFIL || col>= NUMCOL) return false;
	return vuelo.asientos[fil][col].libre;
}

void registrar_tiquet(Vuelo &vuelo){
	cout<<"     Ingrese los datos necesarios para registrar un tiquet:\n\n";
	unsigned fil, col;
	leer("Ingrese fila       : ", fil);
	leer("Ingrese No. asiento: ", col);
	if(esta_libre(vuelo, fil, col) == false){
		mostrar_mensaje("El asiento seleccionado no esta disponible.\n");
		return;
	}
	registrar_pasajero(vuelo.asientos[fil][col]);
	vuelo.total= fil<= 4? PREFERENCIAL: GENERAL;
	mostrar_mensaje("Tiquet registrado exitosamente.\n");
}

void mostrar_resumen_ingresos(const Vuelo &vuelo){
	cout<<"     Mostrando ingresos por categoria.\n\n";
	Moneda preferencial= 0, general= 0;
	unsigned numFila= 0;
	for(const auto &fila: vuelo.asientos){
		for(const auto& asiento: fila){
			if(asiento.libre== false){
				if(numFila<= 4) preferencial+= PREFERENCIAL;
				else general+= GENERAL;
			}
		}
		numFila+= 1;
	}
	string mensaje= "Total preferencial: "+ to_string(preferencial)+ "\n";
	mensaje+=       "Total general     : "+ to_string(general);
	mostrar_mensaje(mensaje);
}

void buscar_por_nombre(const Vuelo &vuelo){
	cout<<"     Ingrese los datos requeridos para la busqueda.\n\n";
	string nombre;
	leer("Ingrese nombre: ", nombre);
	for(unsigned i= 0; i< NUMFIL; ++i){
		for(unsigned j= 0; j< NUMCOL; ++j){
			if(vuelo.asientos[i][j].nombre== nombre){
				string mensaje= nombre+ " encontrado en la fila ";
				mensaje+= to_string(i)+ " asiento "+ to_string(j);
				mostrar_mensaje(mensaje);
				return;
			}
		}
	}
	mostrar_mensaje(nombre+ " no se encuentra en el vuelo.");
}

void mostrar_resumen_asientos(const Vuelo &vuelo){
	cout<<"     Mostrando resumen de asientos\n\n";
	cout<<setw(12* 5+ 5+ 1)<<setfill('-')<<""<<'\n'<<setfill(' ');
	for(const auto &fila: vuelo.asientos){
		cout<<'|';
		for(const auto &asiento: fila){
			cout<<left<<setw(12)<<asiento.nombre<<'|';
		}
		cout<<"\n|";
		for(const auto &asiento: fila){
			cout<<setw(12)<<asiento.apellido<<'|';
		}
		cout<<"\n|";
		for(const auto &asiento: fila){
			if(asiento.identificacion== 0){
				cout<<setw(12)<<' '<<'|';
			}
			else{
				cout<<setw(12)<<asiento.identificacion<<'|';
			}
		}
		cout<<"\n"<<setw(12* 5+ 5)<<setfill('-')<<""<<'\n'<<setfill(' ');
	}
	mostrar_mensaje("Contenido del vuelo mostrado.");
}

int main()
{
	Vuelo vuelo{};
	int opcion;
	string menu= "\n     REGISTRO DE TIQUETES\n\n";
	menu+= "  1. Registrar tiquet\n";
	menu+= "  2. Ver resumen de ingreso\n";
	menu+= "  3. Buscar por nombre\n";
	menu+= "  4. Mostrar resumen de asientos\n";
	menu+= "  0. Salir\n\n";
	menu+= "opcion: ";
	do{
		leer(menu, opcion);
		switch(opcion){
			case 1: registrar_tiquet(vuelo); break;
			case 2: mostrar_resumen_ingresos(vuelo); break;
			case 3: buscar_por_nombre(vuelo); break;
			case 4: mostrar_resumen_asientos(vuelo); break;
			case 0: cout<<"Saliendo...\n"; break;
			default: cout<<"Opcion incorrecta.\n";
		}
	}while(opcion!= 0);
	return 0;
}