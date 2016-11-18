#include "aed2.h"
#include <cassert>
#include <iostream> 
#include "./include/Coordenada.h"

Coordenada::Coordenada() {
    this->latitud = 0;
    this->longitud = 0;
}

Coordenada::Coordenada(Nat latitud, Nat longitud) {
    this->latitud = latitud;
    this->longitud = longitud;
}

Coordenada::Coordenada(const Coordenada &otra) {
    this->latitud = otra.latitud;
    this->longitud = otra.longitud;
} 

Coordenada::~Coordenada() {

}

Nat Coordenada::Latitud() {
    return this->latitud;
}

Nat Coordenada::Longitud() {
    return this->longitud;
}

Coordenada Coordenada::CoordenadaArriba(){
    return Coordenada(this->latitud, this->longitud+1);
}

Coordenada Coordenada::CoordenadaAbajo(){
    return Coordenada(this->latitud, this->longitud-1);
}

Coordenada Coordenada::CoordenadaALaDerecha(){
    return Coordenada(this->latitud+1, this->longitud);
}

Coordenada Coordenada::CoordenadaALaIzquierda(){
    return Coordenada(this->latitud-1, this->longitud);
}

bool Coordenada::operator == (const Coordenada& c2){
    return this->latitud == c2.latitud and this->longitud == c2.longitud;
}

bool Coordenada::operator != (const Coordenada& c2){
    return this->latitud != c2.latitud || this->longitud != c2.longitud;
}

Nat Coordenada::DistEuclidea(const Coordenada& c2){
    Nat x =  this->latitud  - c2.latitud;
    Nat y =  this->longitud - c2.longitud;

    Nat z = (x*x) + (y*y);

    return z;
}

