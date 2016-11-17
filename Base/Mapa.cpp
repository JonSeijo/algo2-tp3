#include "modulos.h"
#include <cassert>
#include <iostream>
#include "aed2.h"

using namespace aed2;
using namespace std;

Mapa::Mapa(){
    cout << "Creando mapa" << endl;
    this->_tam = 0;
    this->_grilla;
}

Mapa::~Mapa(){

}

void Mapa::AgregarCoord(const Coordenada &c) {
    Nat maximo = this->max(c.latitud, c.longitud);

    if (maximo > this->_tam) {
        Vector<Vector<Vector<Vector<bool> > > > nGrilla;
        nGrilla = this->crearGrilla(maximo);
        this->copiarCoordenadas(nGrilla, this->_grilla);
        this->_grilla = nGrilla;
        this->_tam = maximo;
    }

    this->_grilla[c.latitud][c.longitud][c.latitud][c.longitud] = true;

    // Ya no puedo hacer esto en teoria lpm ...
    // Vector<Vector<bool> > visitados = Vector<Vector<bool> >(this->_tam,
    //                                      Vector<bool>(this->_tam, false));

    // ACA NECESITO USAR UNA COLA, QUE NO ESTA IMPLEMENTADA.
    // DESPUES VEO DE COPIAR LA DEL TALLER Y SEGUIR CON EL ALGORITMO

    // linea 20 tp2

}

Conj<Coordenada> Mapa::Coordenadas() const{
    Conj<Coordenada> coors;
    for (int i = 0; i < this->_tam; i++) {
        for (int j = 0; j < this->_tam; j++) {
            if (this->PosExistente(Coordenada(i,j))) {
                coors.AgregarRapido(Coordenada(i,j));
            }
        }
    }
    return coors;
}

bool Mapa::PosExistente(const Coordenada &c) const{

    if (c.latitud < 0 || c.longitud < 0) {
        return false;
    }

    if (c.latitud >= this->_tam || c.longitud >= this->_tam) {
        return false;
    }

    Nat x = c.latitud;
    Nat y = c.longitud;
    return this->_grilla[x][y][x][y];
}


bool Mapa::HayCamino(const Coordenada &c1, const Coordenada &c2) const{
    return this->_grilla[c1.latitud][c1.longitud][c2.latitud][c2.longitud];   
}

Nat Mapa::Tam() const{
    return this->_tam;
}

Vector<Vector<Vector<Vector<bool> > > > Mapa::crearGrilla(const Nat n) {
    Vector<Vector<Vector<Vector<bool> > > > nuevaGrilla;

    for (int i = 0; i < n; i++) {
        Vector<Vector<Vector<bool> > > nGrilla2;

        for (int j = 0; j < n; j++) {
            Vector<Vector<bool> > nGrilla3;

            for (int k = 0; k < n; k++) {
                Vector<bool> nGrilla4;
                for (int l = 0; l < n; l++) {
                    nGrilla4.AgregarAtras(false);
                }
                nGrilla3.AgregarAtras(nGrilla4);
            }            
            nGrilla2.AgregarAtras(nGrilla3);
        }        
        nuevaGrilla.AgregarAtras(nGrilla2);
    }

    return nuevaGrilla;
}   

void Mapa::copiarCoordenadas(
    Vector<Vector<Vector<Vector<bool> > > > grillaNueva,
    Vector<Vector<Vector<Vector<bool> > > > grillaVieja) {

    for (int i = 0; i < grillaVieja.Longitud(); i++) {
        for (int j = 0; j < grillaVieja.Longitud(); j++) {
            grillaNueva[i][j][i][j] = grillaVieja[i][j][i][j];
        }        
    }
}

Nat Mapa::max(Nat x, Nat y) {
    return (x >= y) ? x : y;
}