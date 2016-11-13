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
    assert(false);
}

bool Mapa::PosExistente(const Coordenada &c) const{
    assert(false);
}


bool Mapa::HayCamino(const Coordenada &c1, const Coordenada &c2) const{
    assert(false);
}

Nat Mapa::Tam() const{
    return this->_tam;
}
