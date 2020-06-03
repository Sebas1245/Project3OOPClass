#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
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
        cout << "E. Hacer una reservacion " << endl;
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
    // array of Material pointers and global counter of objects in this array
    Material* arrMaterialP[30];
    int objetosMaterial = 0;
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
                Libro *nuevoLibro;
                nuevoLibro = new Libro();
                nuevoLibro -> setIdMaterial(idM);
                nuevoLibro -> setTitulo(titulo);
                nuevoLibro -> setNumPag(intVar);
                nuevoLibro -> setAutor(strVar);
                arrMaterialP[i] = nuevoLibro;
            }
            else if(claveM == 'D') {
                Disco *nuevoDisco;
                nuevoDisco = new Disco();
                nuevoDisco -> setIdMaterial(idM);
                nuevoDisco -> setTitulo(titulo);
                nuevoDisco -> setDuracion(intVar);
                nuevoDisco -> setGenero(strVar);
                arrMaterialP[i] = nuevoDisco;
            }
            else if(claveM == 'S') {
                Software *nuevoSoftware;
                nuevoSoftware = new Software();
                nuevoSoftware -> setIdMaterial(idM);
                nuevoSoftware -> setTitulo(titulo);
                nuevoSoftware -> setVersion(intVar);
                nuevoSoftware -> setSO(strVar);
                arrMaterialP[i] = nuevoSoftware;
            }
            else {
                throw runtime_error("Error al cargar archivo de Materiales, clave no reconocida");
            }
            i++;
            // llevar cuenta de cuantos objetosMaterial tengo
            objetosMaterial = i;
        }
    }
    catch(const runtime_error& e) {
        cout << e.what() << endl;
    }
    archMaterial.close();
    // end of trying to load info from Material file

    // load info of Reservations from input file
    ifstream archReservaciones;
    archReservaciones.open("Reservaciones.txt");
    int dia, mes, anio, idC;
    // counter
    int reservaciones = 0;
    while(archReservaciones >> dia >> mes >> anio >> idM >> idC) {
        arrReservas[reservaciones].setIdCliente(idC);
        arrReservas[reservaciones].setIdMaterial(idM);
        Fecha fechaReserva(dia,mes,anio);
        arrReservas[reservaciones].setFecha(fechaReserva);
        ++reservaciones;
    }
    archReservaciones.close();
    // end of loading Reservations info from input file

    char respMenu;
    do {
        // run menu function to get the input option
        respMenu = menu();
        // declaration of variables that may be used in multiple cases
        Fecha fechaInicio, fechaFin, fechaIntroducida;
        string tituloMaterial;
        int inputIDMat, idCliente, indexFoundID, intentos = 0, noOfReservation = 0;
        bool idValido, fechaValida, newReservation;
        switch (respMenu) {
            case 'A': {
                for(int i = 0; i < objetosMaterial; i++) {
                    if(arrMaterialP[i] -> getIdMaterial() != -1) {
                        arrMaterialP[i] -> muestraDatos();
                    }
                }
                break;
            }
            case 'B': {
                for(int i = 0; i < reservaciones; i++) {
                    fechaInicio = arrReservas[i].getFecha(); 
                    idCliente = arrReservas[i].getIdCliente();
                    tituloMaterial = "N/D";
                    // try to get the end date of Reserva and the name of the material
                    try{
                        for(int j = 0; j < objetosMaterial; j++){
                            if(arrReservas[i].getIdMaterial() == arrMaterialP[j] -> getIdMaterial()) {
                                fechaFin = arrReservas[i].calculaFechaFinReserva(arrMaterialP[j] -> cantidadDiasPrestamo());
                                tituloMaterial = arrMaterialP[j] -> getTitulo();
                                break;
                            }
                        }
                        if (tituloMaterial == "N/D") {
                            throw runtime_error("Material no encontrado para la reservacion del cliente " + idCliente);
                        }
                        
                    }
                    catch(const runtime_error& e) {
                        cout << e.what() << '\n';
                    }
                    cout << "Reserva " << i + 1 << ") ";
                    cout << "Inicio de reserva: " << fechaInicio;
                    cout << " Fin de reserva: " << fechaFin;
                    cout << " Titulo: " << tituloMaterial;
                    cout << " ID Cliente: " << idCliente << endl;    
                }
                break;
            }    
            case 'C': {
                // ask and validate material ID
                do {
                    if(intentos > 0) {
                        cout << "El ID introducido es invalido, intente de nuevo " << endl;
                    }
                    else {
                        cout << "Introduzca el ID del material " << endl;
                    }
                    cin >> inputIDMat;
                    for (int i = 0; i < objetosMaterial; i++){
                        if(arrMaterialP[i] -> getIdMaterial() != inputIDMat) {
                            idValido = false;
                        }
                        else {
                            tituloMaterial = arrMaterialP[i] -> getTitulo();
                            indexFoundID = i;
                            idValido = true;
                            break;
                        }
                    }
                    intentos++;
                }while (!idValido);
                // display name of material 
                cout << "Material: " << tituloMaterial << endl;
                // get reservations with that specific material ID and show info if there is a match
                for (int i = 0; i < reservaciones; i++) {
                    if(arrReservas[i].getIdMaterial() == inputIDMat) {
                        noOfReservation++; 
                        fechaInicio = arrReservas[i].getFecha();
                        fechaFin = arrReservas[i].calculaFechaFinReserva(arrMaterialP[indexFoundID] -> cantidadDiasPrestamo());
                        if(noOfReservation == 1) {
                            cout << "Reservaciones actuales:" << endl;
                        }
                        cout << noOfReservation << ") ";
                        cout << " Fecha inicio de reserva: " << fechaInicio << " \t";
                        cout << " Final de reserva: " << fechaFin << endl;  
                    }
                    else if(noOfReservation == 0 && i == 59) {
                        cout << "No se encontaron reservaciones para " << tituloMaterial << endl;
                    }
                }
                break;
            }
            case 'D':{
                // try to input the date 
                try {
                    cin >> fechaIntroducida;
                    fechaIntroducida.validarFecha();
                    cout << "Reservaciones para " << fechaIntroducida << endl;
                }
                catch(runtime_error& e) {
                    cout << e.what() << endl;
                    break;
                }
                // revisamos para cada Material si la fecha introducida está dentro del rango de una reservación existente
                for(int i = 0; i < objetosMaterial; i++) {
                    // para cada Reservacion reviso el rango de fechas
                    for(int j = 0; j < reservaciones; j++) {
                        if (arrReservas[j].getIdMaterial() == arrMaterialP[i] -> getIdMaterial()){
                            fechaInicio = arrReservas[j].getFecha();
                            fechaFin = arrReservas[j].calculaFechaFinReserva(arrMaterialP[i] -> cantidadDiasPrestamo());
                            if (fechaIntroducida >= fechaInicio && fechaIntroducida <= fechaFin) {
                                noOfReservation++;
                                cout << noOfReservation << ") ";
                                cout << "Material: " << arrMaterialP[i] -> getTitulo() << " \t";
                                cout << "ID Cliente: " << arrReservas[j].getIdCliente() << " \t";
                                cout << "Se renta de " << fechaInicio << " hasta " << fechaFin << endl;
                            }
                            
                        }
                    }
                }
                // noOfReservation only increases if a reservation within the range of date is found
                // if it is at 0 it means there were no reservations in that range of date
                if (noOfReservation == 0) {
                    cout << "No se encontraron reservaciones para esta fecha " << endl;
                }
                break;
            }  
            case 'E': {
                bool issueFound;
                // ask and validate material ID
                do {
                    if(intentos > 0) {
                        cout << "El ID introducido es invalido, intente de nuevo " << endl;
                    }
                    else {
                        cout << "Introduzca el ID del material " << endl;
                    }
                    cin >> inputIDMat;
                    for (int i = 0; i < objetosMaterial; i++){
                        if(arrMaterialP[i] -> getIdMaterial() != inputIDMat) {
                            idValido = false;
                        }
                        else {
                            tituloMaterial = arrMaterialP[i] -> getTitulo();
                            indexFoundID = i;
                            idValido = true;
                            break;
                        }
                    }
                    intentos++;
                }while (!idValido);
                // try to input the date and input client ID
                try {
                    cin >> fechaIntroducida;
                    fechaIntroducida.validarFecha();
                    // ask for client ID
                    cout << "Introduzca el ID del cliente " << endl;
                    cin >> idCliente;
                    if (idCliente < 0) {
                        throw runtime_error("El ID del cliente no puede ser un número negativo");
                    }
                    
                }
                catch(runtime_error& e) {
                    cout << e.what() << endl;
                    break;
                }
                int diasDePrestamoMaterial = arrMaterialP[indexFoundID] -> cantidadDiasPrestamo();
                for(int i = 0; i < reservaciones; i++) {
                    // if the reservation we are at has the same material we have to check everything
                    if(arrReservas[i].getIdMaterial() == arrMaterialP[indexFoundID] -> getIdMaterial()){
                        fechaInicio = arrReservas[i].getFecha();
                        fechaFin = arrReservas[i].calculaFechaFinReserva(diasDePrestamoMaterial);
                        // check if the material is reserved on the same date
                        if (fechaIntroducida >= fechaInicio && fechaIntroducida <= fechaFin) {
                            cout << "El material " << tituloMaterial << " esta reservado para la fecha deseada." << endl;
                            issueFound = true;
                            break;
                        }
                        // the reservation plus the amount of days the material will be lent be in the range of another reservation
                        // date of a reservation as it must be returned prior to the date of an existing reservation 
                        else if((fechaIntroducida + diasDePrestamoMaterial) >= fechaInicio && (fechaIntroducida + diasDePrestamoMaterial) <= fechaFin) {
                            cout << "El material " << tituloMaterial << " esta reservado para la fecha deseada." << endl;
                            issueFound = true;
                            break;
                        }
                    }
                }
                // if none of the validations break the instance of switch statement we add another reservation
                if (reservaciones < 60 && !issueFound) {
                    ++reservaciones;
                    arrReservas[reservaciones-1].setFecha(fechaIntroducida);
                    arrReservas[reservaciones-1].setIdMaterial(inputIDMat);
                    arrReservas[reservaciones-1].setIdCliente(idCliente);
                    cout << "El material fue reservado exitosamente! " << endl;
                    newReservation = true;
                }
                else if(reservaciones >= 60) {
                    cout << "No hay mas espacio para reservaciones; no se puedo realizar la reservacion " << endl;
                }
                else {
                    cout << "No se pudo realizar la reservacion" << endl;
                }
                break;
            }         
            default:{
                cout << "Ha elegido terminar la sesion " << endl;
                if (newReservation) {
                    ofstream archReservaciones;
                    archReservaciones.open("Reservaciones.txt");
                    for (int i = 0; i < reservaciones; i++) {
                    archReservaciones << arrReservas[i].getFecha().getDd() << " ";
                    archReservaciones << arrReservas[i].getFecha().getMm() << " ";                    
                    archReservaciones << arrReservas[i].getFecha().getAa() << " ";
                    archReservaciones << arrReservas[i].getIdMaterial() << " ";
                    archReservaciones << arrReservas[i].getIdCliente() << endl;
                    }
                    archReservaciones.close();
                    cout << "El archivo de Reservaciones ha sido actualizado " << endl;
                }
                else {
                    cout << "No hay cambios en el archivo de Reservaciones " << endl;
                }
                break;
            }
        }
    } while (respMenu != 'F');
    
    // delete pointers to dynamically created objects during execution
    for (int i = 0; i < 30; i++) {
        delete arrMaterialP[i];
    }
    
    return 0;
}