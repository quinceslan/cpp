#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
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
//	Cliente(int dni): id(dni){}

	static void encabezados(ostream &salida){
		salida<<right<<setw(MAXID)<<"DNI  "<<' ';
		salida<<left<<setw(MAXNOM- 1)<<"  NOMBRE";
		salida<<' '<<setw(MAXNOM- 1)<<"  APELLIDO";
		salida<<'\n';
	}
};

void tabular(ostream &salida, const Cliente &cli){
	salida<<right<<setw(MAXID)<<cli.id<<' ';
	salida<<left<<setw(MAXNOM- 1)<<cli.nombre<<' ';
	salida<<setw(MAXNOM-1)<<cli.apellido<<'\n';
}

void leer(Cliente &cliente){
	leer("Nombre  : ", cliente.nombre, MAXNOM);
	leer("Apellido: ", cliente.apellido, MAXNOM);
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

void escribir(const Cliente &cli){
	escribirln("DNI     : ", cli.id);
	escribirln("Nombre  : ", cli.nombre);
	escribirln("Apellido: ", cli.apellido);
}

int main(){
	escribirln("Hola mundo");
	int dato;
	leer("ingrese un entero: ", dato);
	escribirln("Valor leido: ", dato);
	string cadena;
	leer("ingrese una cadena: ", cadena);
	escribirln("cadena leida: ", cadena);
	Cliente cliente;
	cliente.id= 4882980;
	leer(cliente);
	Cliente::encabezados(cout);
	tabular(cout, cliente);
	escribir(cliente);
	Admin<int, Cliente> admin("clientes.dat");
	bool ok= admin.guardarNuevo(cliente);
	cout<<"guardado: "<<ok<<'\n';
	cliente.id= 0;
	ok= admin.leer(4882980, cliente);
	cout<<"leido: "<<ok<<'\n';
	escribir(cliente);
	return 0;
}
