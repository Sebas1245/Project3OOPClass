#pragma once

#include <iostream>
#include <string>
#include "Material.h"

using namespace std;

class Libro : public Material {
    private:
        int numPag;
        string autor;
    public:
        // constructors
        Libro(int, string);
        Libro();
        // setters
        void setNumPag(int);
        void setAutor(string);
        // getters
        int getNumPag();
        string getAutor();
        // inherited abstract methods
        void muestraDatos();
        int cantidadDiasPrestamo();
};

// constructors
Libro::Libro(int num, string a) {
    numPag = num;
    autor = a;
}

Libro::Libro() {
    numPag = -1;
    autor = "N/D";
}
// implementation of setters
void Libro::setNumPag(int num) {
    numPag = num;
}
void Libro::setAutor(string a) {
    autor = a;
}
// implementation of getters
int Libro::getNumPag() {
    return numPag;
}
string Libro::getAutor() {
    return autor;
}
// implementation of inherited abstract methods
void Libro::muestraDatos() {
    cout << "Tipo de material: Libro \t" << "ID: " << idMaterial << " \t" << "Titulo: " << titulo << " \t";
    cout << "Autor: " << autor << " \t" << "Num de Pgs: " << numPag << endl;
}
int Libro::cantidadDiasPrestamo() {
    // se presta 7 dias predeterminadamente
    return 7;
}