#include <iostream>
#include <string>

using namespace std;

class Material {
protected:
    int idMaterial;
    string titulo;
public:
    // constructors
    Material(int,string);
    Material();
    // setters
    void setIdMaterial(int);
    void setTitulo(string);
    //  getters
    int getIdMaterial();
    string getTitulo();
    // abstract methods
    virtual void muestraDatos() = 0;
    virtual int cantidadDiasPrestamo() = 0;
};

// constructor implementation
Material::Material(int id, string t) {
    idMaterial = id;
    titulo = t;
}

Material::Material() {
    idMaterial = -1;
    titulo = "N/A";
}

// setters implementation
void Material::setIdMaterial(int id) {
    idMaterial = id;
}

void Material::setTitulo(string t) {
    titulo = t;
}

// getters
int Material::getIdMaterial() {
    return idMaterial;
}

string Material::getTitulo() {
    return titulo;
}


