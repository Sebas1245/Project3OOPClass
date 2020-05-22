#pragma once

#include <iostream>
#include <string>
#include "Material.h"

using namespace std;

class Software: public Material {
    private: 
        int  Version;
        string SO;
    public:
        // constructors
        Software();
        Software(int, string, int, string);
        // setters
        void setVersion(int);
        void setSO(string);
        // getters
        int getVersion();
        string getSO();
        // inherited abstract methods
        void muestraDatos();
        int cantidadDiasPrestamo();
};

// constructor implementation
Software::Software(int idM, string titulo,int v, string so):Material(idM,titulo) {
    Version = v;
    SO = so;
}
Software::Software() {
    Version = -1;
    SO = "N/D";
}
// setters implementation
void Software::setVersion(int v) {
    Version = v;
}
void Software::setSO(string so) {
    SO = so;
}
// getters implementation
int Software::getVersion() {
    return Version;
}
string Software::getSO() {
    return SO;
}
// implementation of inherited abstract methods
void Software::muestraDatos() {
    cout << "Tipo de material: Software \t" << "ID: " << idMaterial << " \t" << "Titulo: " << titulo << " \t";
    cout << "Version: " << Version << " \t" << "Sistema operativo: " << SO << endl;  
}

int Software::cantidadDiasPrestamo() {
    // Se presta solamente 1 dia predeterminadamente
    return 1;
}