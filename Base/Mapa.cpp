#include "modulos.h"
#include <cassert>
#include <iostream>
#include "aed2.h"
#include <vector>

using namespace aed2;
using namespace std;

Mapa::Mapa(){
    cout << "Creando mapa" << endl;
    this->_tam = 0;
    this->_grilla = vector<vector<vector<vector<bool> > > >(0,
                        vector<vector<vector<bool> > >(0, 
                            vector<vector<bool> >(0, 
                                vector<bool>(0, false))));
}

Mapa::~Mapa(){

}

void Mapa::AgregarCoord(const Coordenada &c){
    assert(false);
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
    assert(false);
}

Nat Mapa::Tam() const{
    return this->_tam;
}
