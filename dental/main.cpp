#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <ctime>
using namespace std;

template<typename T>
void escribir(const T &dato){
	cout<<dato;
}

template<typename T, typename ...Args>
void escribir(const T &dato, Args...args){
	escribir(dato);
	escribir(args...);
}

template<typename ...Args>
void escribirln(Args...args){
	escribir(args..., '\n');
}

template<typename T>
void leer(const string &etiqueta, T &dato){
	do{
		escribir(etiqueta);
		cin>>dato;
		if(cin.good() && cin.get()== '\n') break;
		escribirln("Error en formato de entrada.\n");
		cin.clear();
		while(cin.get()!= '\n');
	}while(true);
}

void leer(const string &etiqueta, string &dato){
	escribir(etiqueta);
	getline(cin, dato);
}

void leer(const string &e, char *cad, unsigned n){
	do{
		escribir(e);
		for(unsigned i= 0; i< n; ++i){
			cad[i]= cin.get();
			if(cad[i]== '\n'){
				cad[i]= '\0';
				return;
			}
		}
		escribirln("Entrada maxima ", n- 1, 
				" caracteres.\n");
		while(cin.get()!= '\n');
	}while(true);
}

const int MAXNOM= 15;
const int MAXID= 10;

struct Cliente{
	int		id;
	char	nombre[MAXNOM], apellido[MAXNOM];
	static void encabezados(ostream &salida);
};

void Cliente::encabezados(ostream &salida){
	salida<<right<<setw(MAXID)<<"DNI  "<<' ';
	salida<<left<<setw(MAXNOM- 1)<<"  NOMBRE";
	salida<<' '<<setw(MAXNOM- 1)<<"  APELLIDO";
	salida<<'\n';
}

void tabular(ostream &salida, const Cliente &cli){
	salida<<right<<setw(MAXID)<<cli.id<<' ';
	salida<<left<<setw(MAXNOM- 1)<<cli.nombre<<' ';
	salida<<setw(MAXNOM-1)<<cli.apellido<<'\n';
}

void escribir(const Cliente &cli){
	escribirln("DNI     : ", cli.id);
	escribirln("Nombre  : ", cli.nombre);
	escribirln("Apellido: ", cli.apellido);
}

void leer_id(Cliente &cliente){
	leer("DNI     : ", cliente.id);
}

void leer(Cliente &cliente){
	leer("Nombre  : ", cliente.nombre, MAXNOM);
	leer("Apellido: ", cliente.apellido, MAXNOM);
}

class Fecha{
	friend ostream &operator<<(ostream &salida, const Fecha &fecha);
	friend istream &operator>>(istream &entrada, Fecha &fecha);
public:
	Fecha(): tiempo(time(nullptr)){}

	bool operator<(Fecha derecha) const{
		return tiempo< derecha.tiempo;
	}

	bool operator<=(Fecha derecha) const{
		return tiempo<= derecha.tiempo;
	}
private:
	time_t	tiempo;
};

ostream &operator<<(ostream &salida, const Fecha &fecha){
	tm *info= localtime(&fecha.tiempo);
	char fillChar= salida.fill('0');
	salida<<setw(2)<<right<<info->tm_mday<<'/';
	salida<<setw(2)<<info->tm_mon+ 1<<'/';
	salida<<info->tm_year+ 1900<<' ';
	salida<<setw(2)<<info->tm_hour<<':';
	salida<<setw(2)<<info->tm_min<<':';
	salida<<setw(2)<<info->tm_sec;
	return salida<<setfill(fillChar);
}

istream &operator>>(istream &entrada, Fecha &fecha){
	char sep;
	tm *info= localtime(&fecha.tiempo);
	entrada>>info->tm_mday>>sep>>info->tm_mon;
	entrada>>sep>>info->tm_year;
	if(info->tm_mon< 1 || info->tm_mon> 12){
		entrada.setstate(ios::failbit);
		return entrada;
	}
	int diasMes;
	switch(info->tm_mon){
		case 4: case 6: case 9: case 11:
		diasMes= 30;
		break;
		case 2:
		//Un año es bisiesto en el calendario
		//Gregoriano, si es divisible entre 4 
		//y no divisible entre 100, y también
		//si es divisible entre 400.
		if(info->tm_year% 400== 0) diasMes= 29;
		else if(info->tm_year% 100 == 0) diasMes= 28;
		else if(info->tm_year% 4 == 0) diasMes= 29;
		else diasMes= 28;
		break;
		default:
		diasMes= 31;
	}
	if(info->tm_mday< 1 || info->tm_mday> diasMes){
		entrada.setstate(ios::failbit);
		return entrada;
	}
	entrada>>info->tm_hour>>sep>>info->tm_min;
	entrada>>sep>>info->tm_sec;
	if(info->tm_hour< 0 || info->tm_hour> 23){
		entrada.setstate(ios::failbit);
		return entrada;
	}
	if(info->tm_min< 0 || info->tm_min> 59){
		entrada.setstate(ios::failbit);
		return entrada;
	}
	if(info->tm_sec< 0 || info->tm_sec> 59){
		entrada.setstate(ios::failbit);
		return entrada;
	}
	info->tm_year-= 1900;
	info->tm_mon-= 1;
	time_t tiempo= mktime(info);
	if(tiempo== -1){
		entrada.setstate(ios::failbit);
	}
	else{
		fecha.tiempo= tiempo;
	}
	return entrada;
}

template<typename K, typename T>
class Admin{
public:
	Admin(const string& fichero): fichero(fichero){
		construirIndice();
	}

	bool guardarNuevo(const T &reg){
		if(index.find(reg.id)!= index.end())
			return false;
		ofstream sal(fichero, ios::app|ios::binary);
		if(!sal.is_open()){
			string error= "Error al abrir '"+ fichero;
			error+= "' para agregar datos";
			throw logic_error(error);
		}
		streampos pos= sal.tellp();
		sal.write((const char*)&reg, sizeof(T));
		sal.flush();
		index.emplace(reg.id, pos);
		return sal.good();
	}

	bool leer(K id, T &reg){
		auto it= index.find(id);
		if(it== index.end()) return false;
		ifstream in(fichero, ios::binary);
		if(!in.is_open()){
			string error= "Error al abrir '"+ fichero;
			error+= "' para leer datos";
			throw logic_error(error);
		}
		in.seekg(it->second);
		in.read((char*)&reg, sizeof(T));
		return in.good();
	}

	template<typename Contenedor>
	void leerSi(function<bool(const T&)> pred,
			Contenedor &c){
		ifstream in(fichero, ios::binary);
		if(!in.is_open()){
			string error= "Error al abrir '"+ fichero;
			error+= "' para lectura";
			throw logic_error(error);
		}
		T reg;
		while(in.read((char*)&reg, sizeof(T))){
			if(pred(reg)) c.push_back(reg);
		}
	}
private:
	string	fichero;
	map<int, streampos>	index;

	void construirIndice(){
		ifstream entrada(fichero);
		if(entrada.is_open()){
			T reg;
			streampos pos= 0;
			while(entrada.read((char*)&reg,
						sizeof(T))){
				index.emplace(reg.id, pos);
				pos= entrada.tellg();
			}
		}
		else{
			ofstream salida(fichero, ios::app);
			if(!salida.is_open()){
				string error= "No se puede crear ";
				error+= fichero+ " para escritura";
				throw logic_error(error);
			}
		}
	}
};

int main(){
	Fecha actual;
	escribirln("Fecha actual: ", actual);
	Fecha fecha;
	leer("Ingrese una fecha: ", fecha);
	escribirln("Fecha leida: ", fecha);
	return 0;
}
