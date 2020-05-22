#include <iostream>
#include <string>
#include <fstream>
#include "Reserva.h"
#include "Libro.h"
#include "Software.h"
#include "Disco.h"

using namespace std;

int main(){
    // array of Material pointers
    Material *arrMaterialP[30];
    // array of Reservations
    Reserva arrReservas[60];

    // load info from input file
    ifstream archMaterial;
    archMaterial.open("Material.txt");
    // specific variables for Material, every type has an int attribute and a string attribute (intVar and strVar)
    int idM, intVar;
    string titulo, strVar;
    char claveM;
    try {
        // counter
        int i = 0;
        while (archMaterial >> idM >> titulo >> claveM >> intVar >> strVar) {
            if(claveM == 'L') {
                Libro libroNuevo(idM,titulo,intVar, strVar);
                arrMaterialP[i] = &libroNuevo;
            }
            else if(claveM == 'D') {
                Disco discoNuevo(idM,titulo,intVar,strVar);
                arrMaterialP[i] = &discoNuevo;
            }
            else if(claveM == 'S') {
                Software softwareNuevo(idM,titulo,intVar,strVar);
                arrMaterialP[i] = &softwareNuevo;
            }
            else {
                throw runtime_error("Error al cargar archivo de Materiales, clave no reconocida");
            }
            i++;
        }
        
    }
    catch(const runtime_error& e) {
        cerr << e.what() << endl;
    }
    
    return 0;
}