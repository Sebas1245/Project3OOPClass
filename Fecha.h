#pragma once

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Fecha {
    private:
        int dd, mm, aa;
        // method returns month of the objetc in text
        string nombreMes();
        // method calculates if it is leap year
        bool bisiesto(int );
    public:
        // constructors
        Fecha();
        Fecha(int d, int m, int a);
        // access methods
        int getDd();
        int getMm();
        int getAa();
        // operator overload
        Fecha operator+(int diasAg);
        bool operator<(Fecha f2);
        bool operator>(Fecha f2);
        bool operator>=(Fecha f2);
        bool operator<=(Fecha f2);
        bool operator==(Fecha f2);
        friend ostream &operator<<(ostream &output,Fecha &F);
        friend istream &operator>>(istream &input, Fecha &F);
        // other method(s)
        void setFecha(int, int, int);
        // validates that the objects date is correct 
        void validarFecha();
};

// constructors
Fecha::Fecha(){
    dd = -1;
    mm = -1;
    aa = -1;
}

Fecha::Fecha(int d, int m, int a) {
    dd = d;
    mm = m;
    aa = a;
}
// getters 
int Fecha::getDd(){
    return dd;
}
int Fecha::getMm(){
    return mm;
}
int Fecha::getAa(){
    return aa;
}
// operator overloads
Fecha Fecha::operator+(int diasAgregar){
    int ddNuevo, mmNuevo = mm, aaNuevo = aa;
    // sumamos los dias
    ddNuevo = dd + diasAgregar;
    bool ddNuevoExcede;
    if(ddNuevo > 28) {
        ddNuevoExcede = true;
    }
    while(ddNuevoExcede) {
        // revisamos si el año de la Fecha es bisiesto
        bool esBisiesto = bisiesto(aaNuevo);
        // revisamos primero el mes de febrero
        if (mmNuevo == 2 && (ddNuevo > 28 || ddNuevo > 29)) {
            // si es bisiesto no puede sobrepasar los 28 dias, agregamos 1 al mes
            if(!esBisiesto){
                ddNuevo -= 28;
                mmNuevo++;
            }
            // si es Bisiesto restamos 29
            else if(esBisiesto){
                ddNuevo -= 29;
                mmNuevo++;
            }
        }
        // revisamos diciembre
        else if(mmNuevo == 12 && ddNuevo > 31) {
            // si excede 31 ponemos el mes nuevo en 1 y agregamos 1 al año 
                mmNuevo = 1;
                aaNuevo++;
                ddNuevo -= 31;
        }
        // para los meses con 31 dias
        else if((mmNuevo == 1 || mmNuevo == 3 || mmNuevo == 5 || mmNuevo == 7 || mmNuevo == 8 || mmNuevo == 10) && ddNuevo > 31){
                ddNuevo -= 31;
                mmNuevo++;
        }
        // para los meses con 30 dias
        else if((mmNuevo == 4 || mmNuevo == 6 || mmNuevo == 9 || mmNuevo == 11) && ddNuevo > 30){
            ddNuevo -= 30;
            mmNuevo++;
        }
        // si no excede 28 ya no puede haber ningun tipo de problema por lo que salgo del ciclo
        else {
            ddNuevoExcede = false;
        }
    }
    // declaramos nueva fecha y la regresamos
    Fecha fechaN(ddNuevo,mmNuevo,aaNuevo);
    return fechaN;
}
bool Fecha::operator<(Fecha f2) {
    if (aa < f2.aa){
        return true;
    }
    else if (aa > f2.aa){
        return false;
    }
    else {
        if (mm < f2.mm){
            return true;
        }
        else if(mm > f2.mm) {
            return false;
        }
        else {
            if(dd < f2.dd) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}
bool Fecha::operator>(Fecha f2) {
    if (aa > f2.aa){
        return true;
    }
    else if (aa < f2.aa){
        return false;
    }
    else {
        if (mm > f2.mm){
            return true;
        }
        else if(mm < f2.mm) {
            return false;
        }
        else {
            if(dd > f2.dd) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}
bool Fecha::operator<=(Fecha f2){
    if ((aa == f2.aa) && (mm == f2.mm) && (dd == f2.dd)){
        return true;
    }
    else {
        if(aa < f2.aa){
            return true;
        }
        else {
            if(mm < f2.mm){
                return true;
            }
            else {
                if(dd < f2.dd) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
}
bool Fecha::operator>=(Fecha f2){
    if (aa > f2.aa){
        return true;
    }
    else if (aa < f2.aa){
        return false;
    }
    else {
        if (mm > f2.mm){
            return true;
        }
        else if(mm < f2.mm) {
            return false;
        }
        else {
            if(dd > f2.dd) {
                return true;
            }
            else if(dd == f2.dd) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}
bool Fecha::operator==(Fecha f2){
    if ((aa == f2.aa) && (mm == f2.mm) && (dd == f2.dd)){
        return true;
    }
    else{
        return false;
    }
}
ostream &operator<<(ostream &out, Fecha &F) {
    out << F.dd << "/" << F.nombreMes() << "/" << F.aa; 
    return out;
}
istream &operator>>(istream &input,Fecha &F) {
    cout << "Ingrese la fecha en el formato dd/mm/aa : " << endl;
    input >> F.dd;
    input >> F.mm;
    input >> F.aa;
    return input;
}
// other methods
string Fecha::nombreMes(){
    switch(mm){
        case 1: 
            return "Ene";
        case 2: 
            return "Feb";
        case 3:
            return "Mar";
        case 4:
            return "Abr";
        case 5:
            return "May";
        case 6:
            return "Jun";
        case 7:
            return "Jul";
        case 8:
            return "Ago";
        case 9:
            return "Sep";
        case 10:
            return "Oct";
        case 11:
            return "Nov";
        case 12:
            return "Dec";
        default:
            return "Mes incorrecto";
    }
}
void Fecha::setFecha(int d, int m, int a){
    dd = d;
    mm = m;
    aa = a;
}
bool Fecha::bisiesto(int a){
    if (a % 4 == 0 && a % 100 != 0 || a % 400 == 0){
        return true;
    }
    else {
        return false;
    }
}

void Fecha::validarFecha(){
    // revisamos si el año de la Fecha es bisiesto
    bool esBisiesto = bisiesto(aa);
    // revisamos primero el mes de febrero
    if (mm == 2 && dd > 28 && !esBisiesto) {
        throw runtime_error("La fecha es invalida debido al dia");
    }
    else if(mm == 2 && dd > 29 && esBisiesto) {
        throw runtime_error("La fecha es invalida debido al dia");
    }
    // para los meses con 31 dias
    else if((mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12) && dd > 31){
        throw runtime_error("La fecha es invalida debido al dia");
    }
    // para los meses con 30 dias
    else if((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd > 30){
        throw runtime_error("La fecha es invalida debido al dia");
    }
    // revisar si es un mes invalido
    else if(nombreMes() == "Mes incorrecto") {
        throw runtime_error("La fecha es invalida debido al mes");
    }
    else if(dd < 1) {
        throw runtime_error("El dia no puede ser 0 o negativo");
    }
    else if(aa < 1 ) {
        throw runtime_error("El anio es invalido ");
    }
}