#include <iostream>
#include <string>
#include <fstream>
#include "Reserva.h"
#include "Libro.h"
#include "Software.h"
#include "Disco.h"

using namespace std;

// menu
// Despliega el menu al Usuario y obtiene la opción del menú que se desea ejecutar
// No recibe ningun parametro
// Regresa variable tipo char, siendo este el caracter de la opcion elegida por el usuario
char menu(){
    char resp;
    bool respCorrecta;
    do {
        cout << "----------------------------------------------------------------------------------------------" << endl;
        cout << "Eliga una opcion introduciendo una de las letras mostradas" << endl;
        cout << "A. Consultar la lista de Materiales " << endl;
        cout << "B. Consultar la lista de reservaciones " << endl;
        cout << "C. Consultar las reservaciones de un material dado " << endl;
        cout << "D. Consultar las reservaciones de una fecha dada " << endl;
        cout << "E. Hacer una reservación " << endl;
        cout << "F. Terminar " << endl;
        cout << "----------------------------------------------------------------------------------------------" << endl;
        cin >> resp;
        resp = toupper(resp);
        if(resp == 'A' || resp == 'B' || resp == 'C' || resp == 'D' || resp == 'E' || resp =='F') {
            respCorrecta = true;
        }
        else {
            respCorrecta = false; 
        }      
    } while(respCorrecta == false);
    return resp;
}

int main(){
    // array of Material pointers
    Material* arrMaterialP[30];
    // array of Reservations
    Reserva arrReservas[60];

    // load info of Materials from input file
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
    archMaterial.close();
    // end of trying to load info from Material file

    // load info of Reservations from input file
    ifstream archReservaciones;
    archReservaciones.open("Reservaciones.txt");
    int dia, mes, anio, idC;
    // counter
    int j = 0;
    while(archReservaciones >> dia >> mes >> anio >> idC >> idM) {
        arrReservas[j].setIdCliente(idC);
        arrReservas[j].setIdMaterial(idM);
        Fecha fechaReserva(dia,mes,anio);
        arrReservas[j].setFecha(fechaReserva);

    }
    archReservaciones.close();
    // end of loading Reservations info from input file

    // run menu function to get the input option
    char respMenu;
    respMenu = menu();
    
       
    return 0;
}