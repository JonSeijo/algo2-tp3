#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include <ostream>
#include "aed2/TiposBasicos.h"


typedef unsigned int Jugador;
typedef unsigned int Nat;

typedef std::string Pokemon;

struct Coordenada{
    Nat latitud;
    Nat longitud;

    Coordenada(): latitud(0), longitud(0) {}

    Coordenada(Nat latitud, Nat longitud)
     : latitud(latitud), longitud(longitud) {}

    Coordenada(const Coordenada &otra) : latitud(otra.latitud),
                                         longitud(otra.longitud){}


    Coordenada& operator =(const Coordenada &otra) {
        this->latitud  = otra.latitud;
        this->longitud = otra.longitud;

        return *this;
    } 
    Coordenada CoordenadaArriba(){
        return Coordenada(this->latitud, this->longitud+1);
    }

    Coordenada CoordenadaAbajo(){
        return Coordenada(this->latitud, this->longitud-1);
    }

    Coordenada CoordenadaALaDerecha(){
        return Coordenada(this->latitud+1, this->longitud);
    }

    Coordenada CoordenadaALaIzquierda(){
        return Coordenada(this->latitud-1, this->longitud);
    }

};

inline bool operator == (const Coordenada& c1, const Coordenada& c2){
    return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

inline bool operator != (const Coordenada& c1, const Coordenada& c2){
    return not (c1 == c2);
}

inline std::ostream& operator << (std::ostream& os, const Coordenada& c) {
    os << "<" << c.latitud << "," << c.longitud << ">";
    return os; 
}

inline Nat distEuclidea(const Coordenada& c1, const Coordenada& c2){
    // Nat x =  c1.latitud  - c2.latitud;
    // Nat y =  c1.longitud - c2.longitud;

    // Nat z = (x*x) + (y*y);

    // return z;

    // Siguiendo la spec tal cual 

    Nat x = 0;
    if (c1.latitud > c2.latitud) {
        x = (c1.latitud - c2.latitud) * (c1.latitud - c2.latitud);
    } else {
        x = (c2.latitud - c1.latitud) * (c2.latitud - c1.latitud);
    }

    Nat y = 0;
    if (c1.longitud > c2.longitud) {
        y = (c1.longitud - c2.longitud) * (c1.longitud - c2.longitud);
    } else {
        y = (c2.longitud - c1.longitud) * (c2.longitud - c1.longitud);
    }

    return x + y;
}


struct jugYCantCapt{
    Nat id;
    Nat cant;

    jugYCantCapt(Nat id, Nat cant) : id(id), cant(cant) {}

    jugYCantCapt(const jugYCantCapt &otro) : id(otro.id), cant(otro.cant) {}

};

inline bool operator < (const jugYCantCapt & j1, const jugYCantCapt & j2) {
    if (j1.cant == j2.cant) {
        return j1.id < j2.id;
    }
    return j1.cant < j2.cant;
}

inline bool operator == (const jugYCantCapt & j1, const jugYCantCapt & j2) {
    return (j1.id == j2.id) && (j1.cant == j2.cant);
}

#endif
