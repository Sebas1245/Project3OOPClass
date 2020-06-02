#pragma once

#include <iostream>
#include <string>
#include "Material.h"

using namespace std;

class Disco : public Material {
    private:
        int duracion;
        string Genero;
    public:
        // constructors
        Disco(int, string, int, string);
        Disco();
        // setters
        void setDuracion(int);
        void setGenero(string);
        // getters
        int getDuracion();
        string getGenero();
        // inherited abstract methods
        void muestraDatos();
        int cantidadDiasPrestamo();
};

// constructors
Disco::Disco(int idM, string titulo, int num, string g):Material(idM,titulo) {
    duracion = num;
    Genero = g;
}

Disco::Disco() {
    duracion = -1;
    Genero = "N/D";
}
// implementation of setters
void Disco::setDuracion(int num) {
    duracion = num;
}
void Disco::setGenero(string g) {
    Genero = g;
}
// implementation of getters
int Disco::getDuracion() {
    return duracion;
}
string Disco::getGenero() {
    return Genero;
}
// implementation of inherited abstract methods
void Disco::muestraDatos() {
    cout << "Tipo de material: Disco \t" << "ID: " << idMaterial << " \t" << "Titulo: " << titulo << " \t";
    cout << "Duracion: " << duracion << " \t" << "Genero: " << Genero << endl;
}
int Disco::cantidadDiasPrestamo() {
    // se presta 7 dias predeterminadamente
    return 2;
}