#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>

using namespace std;

const int LABELSIZE= 24;
const int NAMESIZE= 12;

void read(const string &label, unsigned &number){
    cout<<right<<setw(LABELSIZE)<<label;
    cin>>number;
    cin.ignore();
}

void read(const string &label, double &value){
    cout<<right<<setw(LABELSIZE)<<label;
    cin>>value;
    cin.ignore();
}

void read(const string &label, string &value){
    cout<<right<<setw(LABELSIZE)<<label;
    getline(cin, value);
}

void show_message(const string &message){
    cout<<message<<'\n';
    while(cin.get()!= '\n');
}

class Person{
    friend void read(const string &label, Person &person);
public:
    virtual ~Person(){}
    unsigned getDni() const{ return dni; }
    const string &getName() const{ return name; }
    const string &getDirection() const{ return direction; }
    static void printHeaders(ostream &output);
    virtual void printTabulate(ostream &output) const;
protected:
    Person(unsigned dni): dni(dni){}
private:
    unsigned dni;
    string name, direction;
};

void read(const string &label, Person &person){
    cout<<label;
    read("Nombre: ", person.name);
    read("Direction: ", person.direction);
}

void Person::printHeaders(ostream &output){
    output<<right<<setw(10)<<"DNI  "<<' ';
    output<<left<<setw(NAMESIZE)<<"  NOMBRE";
}

void Person::printTabulate(ostream &output) const{
    output<<right<<setw(10)<<dni<<' ';
    output<<left<<setw(NAMESIZE)<<name;
}

class Employee: public Person{
    friend void read(const string &label, Employee &employee);
public:
    Employee(unsigned id, unsigned dni): Person(dni), id(id){}
    unsigned getId() const{ return id; }
    static void printHeaders(ostream &output);
    void printTabulate(ostream &output) const override;
private:
    unsigned id;
};

void read(const string &label, Employee &employee){
    read(label, static_cast<Person&>(employee));
}

void Employee::printHeaders(ostream &output){
    output<<right<<setw(10)<<"ID  "<<' ';
    Person::printHeaders(output);
    output<<'\n';
}

void Employee::printTabulate(ostream &output) const{
    output<<right<<setw(10)<<id<<' ';
    Person::printTabulate(output);
}

class LegalPerson: Person{
    friend void read(const string &label, LegalPerson &person);
public:
    unsigned getNit() const{ return nit; }
    const string &getLegalName() const{ return legalName; }
    static void printHeaders(ostream &output);
    void printTabulate(ostream &output) const override;
protected:
    LegalPerson(unsigned nit, unsigned dni): Person(dni), nit(nit){}
private:
    unsigned nit;
    string legalName;
};

void read(const string &label, LegalPerson &person){
    read(label, static_cast<Person&>(person));
    read("Nombre legal: ", person.legalName);
}

void LegalPerson::printHeaders(ostream &output){
    output<<right<<setw(10)<<"NIT  "<<' ';
    Person::printHeaders(output);
    output<<left<<setw(NAMESIZE)<<"  NOMBRE LEGAL"<<'\n';
}

void LegalPerson::printTabulate(ostream &output) const{
    output<<right<<setw(10)<<nit<<' ';
    Person::printTabulate(output);
    output<<left<<setw(NAMESIZE)<<legalName;
}

class Client: LegalPerson{
public:
    Client(unsigned nit, unsigned dni): LegalPerson(nit, dni){}
};

class Suplier: LegalPerson{
public:
    Suplier(unsigned nit, unsigned dni): LegalPerson(nit, dni){}
};

class Product{
    friend void read(const string &label, Product &product);
public:
    Product(unsigned code): code(code){}
    unsigned getCode() const{ return code; }
    const string &getName() const{ return name; }
    unsigned getStock() const{ return stock; }
    void recordSale(unsigned quantity);
    void recordPurchase(unsigned quantity){ stock+= quantity; }
    static void printHeaders(ostream &output);
    void printTabulate(ostream &output) const;
    bool operator==(const Product &other) const{ return code== other.code; }
private:
    unsigned code;
    string name;
    unsigned stock;
    double salePrice, purchasePrice;
};

void Product::recordSale(unsigned quantity){
    if(quantity> stock){
        throw logic_error("Cantidad a retirar es menor al stock");
    }
    stock-= quantity;
}

void read(const string &label, Product &product){
    cout<<label<<'\n';
    read("Nombre: ", product.name);
    read("Precio de venta: ", product.salePrice);
    read("Precio de compra: ", product.purchasePrice);
    read("Stock inicial: ", product.stock);
}

void Product::printHeaders(ostream &output){
    output<<right<<setw(10)<<"CODIGO  "<<' ';
    output<<left<<setw(NAMESIZE)<<"  NOMBRE"<<' ';
    output<<right<<setw(10)<<"STOCK  "<<' ';
    output<<setw(10)<<"P. VENTA "<<' ';
    output<<setw(19)<<"P. COMPRA "<<'\n';
}

void Product::printTabulate(ostream &output) const{
    output<<right<<setw(10)<<code<<' ';
    output<<left<<setw(NAMESIZE)<<name<<' ';
    output<<right<<setw(10)<<stock<<' ';
    output<<setw(10)<<salePrice<<' ';
    output<<setw(19)<<purchasePrice;
}

struct RecordDetail{
    Product *product;
    unsigned quantity;
    double price;
    
    static void printHeaders(ostream &output);
    void printTabulate(ostream &output) const;
};

void RecordDetail::printHeaders(ostream &output){
    output<<right<<setw(10)<<"CODIGO "<<' ';
    output<<left<<setw(NAMESIZE)<<" NOMBRE"<<' ';
    output<<right<<setw(10)<<"CANTIDAD "<<' ';
    output<<setw(10)<<"PRECIO "<<' ';
    output<<setw(10)<<"SUBTOTAL "<<'\n';
}

void RecordDetail::printTabulate(ostream &output) const{
    output<<right<<setw(10)<<product->getCode()<<' ';
    output<<left<<setw(NAMESIZE)<<product->getName()<<' ';
    output<<right<<setw(10)<<quantity<<' ';
    output<<setw(10)<<price<<' ';
    output<<setw(10)<<price* quantity;
}

void read(const string &label, RecordDetail &detail){
    cout<<label<<'\n';
    read("Ingrese cantidad: ", detail.quantity);
    read("Ingrese precio: ", detail.price);
}

class Record{
public:
    virtual void commit()= 0;
    void addProduct(Product *product);
protected:
    Record(const string &description, const LegalPerson &person)
        : description(description), person(&person){}
    virtual bool validate(const RecordDetail &) const{ return true; };
    vector<RecordDetail> &getDetailList(){ return detailList; }
    const vector<RecordDetail> &getDetailList() const{ return detailList; }
private:
    string description;
    const LegalPerson *person;
    bool isCommited;
    vector<RecordDetail> detailList;
};

void Record::addProduct(Product *product){
    RecordDetail detail;
    detail.product= product;
    read("Ingrese los datos del registro: ", detail);
    if(validate(detail)){
        detailList.push_back(detail);
    }
    else{
        show_message("Cantidad en existencia insuficiente.");
    }
}

class SaleRecord: public Record{
public:
    SaleRecord(const string &descrption, const LegalPerson &person)
        : Record(descrption, person){}
    void commit() override;
protected:
    bool validate(const RecordDetail &detail) const override;
};

void SaleRecord::commit(){
    for(RecordDetail &detail: getDetailList()){
        detail.product->recordSale(detail.quantity);
    }
}

bool SaleRecord::validate(const RecordDetail &detail) const{
    unsigned quantity= detail.quantity;
    for(const RecordDetail &current: getDetailList()){
        if(current.product->getCode()== detail.product->getCode()){
            quantity+= current.quantity;
        }
    }
    return detail.product->getStock()>= quantity;
}

class PurchaseRecord: public Record{
public:
    PurchaseRecord(const string &description, const LegalPerson &person)
        : Record(description, person){}
    void commit() override;
};

void PurchaseRecord::commit(){
    for(RecordDetail &detail: getDetailList()){
        detail.product->recordPurchase(detail.quantity);
    }
}

template<typename T, typename Container>
bool existMember(const T &member, Container &container){
    for(const T &current: container){
        if(member== current){
            return true;
        }
    }
    return false;
}

template<typename T, typename Container>
void addMember(const string &label, T &member, Container& container){
    if(existMember(member, container)){
        show_message("No se puede agregar el registro");
        return;
    }
    read(label, member);
    container.push_back(member);
    show_message("Registro agregago correctamente");
}

class Store{
public:
    void addProduct();
    Product *searchProduct(unsigned code);
private:
    vector<Product> productList;
};

void Store::addProduct(){
    unsigned code;
    cout<<"Ingrese los datos para el nuevo producto:\n";
    read("Codigo de producto: ", code);
    Product product(code);
    addMember("Datos para el producto: ", product, productList);
}

Product *Store::searchProduct(unsigned code){
    for(Product &product: productList){
        if(product.getCode()== code){
            return &product;
        }
    }
    return nullptr;
}

class App{
};

int main(){
    cout<<"Hola mundo"<<endl;
    return 0;
}
