#pragma once

#include <iostream>
#include "Fecha.h"

using namespace std;

class Reserva {
    private:
        int idMaterial, idCliente;
        Fecha fechaReservacion;
    public:
        // constructors
        Reserva();
        Reserva(int, int, Fecha);
        // setters
        void setIdMaterial(int);        
        void setIdCliente(int);           
        void setFecha(Fecha);
        // getters
        int getIdMaterial();        
        int getIdCliente();
        Fecha getFecha();
        // method for calculating end date of reservation
        Fecha calculaFechaFinReserva(int cantDias);
};
// constructors
Reserva::Reserva() {
    idMaterial = -1;
    idCliente = -1;
    fechaReservacion.setFecha(-1,-1,-1);
}

Reserva::Reserva(int idM, int idC, Fecha f) {
    idMaterial = idM;
    idCliente = idC;
    fechaReservacion.setFecha(f.getDd(),f.getMm(),f.getAa());
}

// setters
void Reserva::setIdCliente(int idC){
    idCliente = idC;
}
void Reserva::setIdMaterial(int idM){
    idMaterial = idM;
}
void Reserva::setFecha(Fecha f) {
    fechaReservacion.setFecha(f.getDd(),f.getMm(),f.getAa());
}

// getters
int Reserva::getIdMaterial(){
    return idMaterial;
}
int Reserva::getIdCliente(){
    return idCliente;
}
Fecha Reserva::getFecha(){
    return fechaReservacion;
}

// method for calculating end date of reservation
Fecha Reserva::calculaFechaFinReserva(int cantDias) {
    Fecha fechaFinal;
    fechaFinal = fechaReservacion + cantDias;
    return fechaFinal;
}