#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

const int LABELSIZE= 24;

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
    Person(unsigned dni): dni(dni){}
    virtual ~Person(){}
    unsigned getDni() const{ return dni; }
    const string &getName() const{ return name; }
private:
    unsigned dni;
    string name, direction;
};

void read(const string &label, Person &person){
    cout<<label;
    read("Nombre: ", person.name);
    read("Direction: ", person.direction);
}

class Employee: public Person{
public:
    Employee(unsigned dni, unsigned contract): Person(dni), contract(contract){}
    unsigned getContract() const{ return contract; }
private:
    unsigned contract;
};

class LegalPerson: Person{
    friend void read(const string &label, LegalPerson &person);
public:
    LegalPerson(unsigned dni, unsigned nit): Person(dni), nit(nit){}
    unsigned getNit() const{ return nit; }
    const string &getLegalName() const{ return legalName; }
private:
    unsigned nit;
    string legalName;
};

void read(const string &label, LegalPerson &person){
    read("Datos generales:", static_cast<Person&>(person));
    read("Nombre legal: ", person.legalName);
}

class Client: LegalPerson{
};

class Suplier: LegalPerson{
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
private:
    unsigned code;
    string name;
    unsigned stock;
};

void Product::recordSale(unsigned quantity){
    if(quantity> stock){
        throw logic_error("Cantidad a retirar es menor al stock");
    }
    stock-= quantity;
}

void read(const string &label, Product &product){
    cout<<label<<'\n';
    read("Nombre de producto: ", product.name);
    read("Stock inicial: ", product.stock);
}

struct RecordDetail{
    Product *product;
    unsigned quantity;
    double price;
};

void read(const string &label, RecordDetail &detail){
    cout<<label<<'\n';
    read("Ingrese cantidad: ", detail.quantity);
    read("Ingrese precio  : ", detail.price);
}

class Record{
public:
    virtual void recordTransaction()= 0;
    void addProduct(Product *product);
protected:
    virtual bool validate(const RecordDetail &detail) const;
private:
    vector<RecordDetail> recordsList;
};

bool Record::validate(const RecordDetail &detail) const{
    unsigned quantity= detail.quantity;
    for(const RecordDetail &record: recordsList){
        quantity+= record.quantity;
    }
    return detail.product->getStock()>= quantity;
}

void Record::addProduct(Product *product){
    RecordDetail detail;
    detail.product= product;
    read("Ingrese los datos del registro: ", detail);
    if(validate(detail)){
        recordsList.push_back(detail);
    }
    else{
        show_message("Cantidad en existencia insuficiente.");
    }
}

class SaleRecord: public Record{

};

class PurchaseRecord: public Record{

};

class Store{
public:
    void addProduct();
    Product *searchProduct(unsigned code);
private:
    vector<Product> productsList;
};

void Store::addProduct(){
    unsigned code;
    cout<<"Ingrese los datos para el nuevo producto:\n";
    read("Codigo de producto: ", code);
    if(searchProduct(code)){
        show_message("No es posible crear producto, codigo ya registrado.");
        return;
    }
    productsList.emplace_back(code);
    read("Datos del nuevo producto: ", productsList.back());
    show_message("Producto agregado correctamente.");
}

Product *Store::searchProduct(unsigned code){
    for(Product &product: productsList){
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
