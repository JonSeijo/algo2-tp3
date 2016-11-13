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

void Mapa::AgregarCoord(const Coordenada &c) {
    Nat maximo = this->max(c.latitud, c.longitud);

    if (maximo > this->_tam) {
        vector<vector<vector<vector<bool> > > > nGrilla;
        nGrilla = this->crearGrilla(maximo);
        this->copiarCoordenadas(nGrilla, this->_grilla);
        this->_grilla = nGrilla;
        this->_tam = maximo;
    }

    this->_grilla[c.latitud][c.longitud][c.latitud][c.longitud] = true;

    vector<vector<bool> > visitados = vector<vector<bool> >(this->_tam,
                                         vector<bool>(this->_tam, false));

    // ACA NECESITO USAR UNA COLA, QUE NO ESTA IMPLEMENTADA.
    // DESPUES VEO DE COPIAR LA DEL TALLER Y SEGUIR CON EL ALGORITMO


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

vector<vector<vector<vector<bool> > > > Mapa::crearGrilla(const Nat n) {
    vector<vector<vector<vector<bool> > > > nuevaGrilla;
    nuevaGrilla = vector<vector<vector<vector<bool> > > >(n,
                    vector<vector<vector<bool> > >(n, 
                        vector<vector<bool> >(n, 
                            vector<bool>(n, false))));
}   

void Mapa::copiarCoordenadas(
    vector<vector<vector<vector<bool> > > > grillaNueva,
    vector<vector<vector<vector<bool> > > > grillaVieja) {

    for (int i = 0; i < grillaVieja.size(); i++) {
        for (int j = 0; j < grillaVieja.size(); j++) {
            grillaNueva[i][j][i][j] = grillaVieja[i][j][i][j];
        }        
    }
}

Nat Mapa::max(Nat x, Nat y) {
    return (x >= y) ? x : y;
}