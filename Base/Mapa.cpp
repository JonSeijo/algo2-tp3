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
    return this->_grilla[c1.latitud][c1.longitud][c2.latitud][c2.longitud];   
}

Nat Mapa::Tam() const{
    return this->_tam;
}

void AgregarCoord(Coordenada c) {

}

vector<vector<vector<vector<bool> > > > crearGrilla(const Nat n) {
    vector<vector<vector<vector<bool> > > > nuevaGrilla;
    nuevaGrilla = vector<vector<vector<vector<bool> > > >(n,
                    vector<vector<vector<bool> > >(n, 
                        vector<vector<bool> >(n, 
                            vector<bool>(n, false))));
}   

void copiarCoordenadas(
    vector<vector<vector<vector<bool> > > > grillaNueva,
    vector<vector<vector<vector<bool> > > > grillaVieja) {

    for (int i = 0; i < grillaVieja.size(); i++) {
        for (int j = 0; j < grillaVieja.size(); j++) {
            grillaNueva[i][j][i][j] = grillaVieja[i][j][i][j];
        }        
    }
}

Nat max(Nat x, Nat y) {
    return (x >= y) ? x : y;
}