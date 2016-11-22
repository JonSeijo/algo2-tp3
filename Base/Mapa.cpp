// #include "modulos.h"
#include "./include/Mapa.h"
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
        nGrilla = this->crearGrilla(maximo+1);
        this->copiarCoordenadas(nGrilla, this->_grilla);
        this->_grilla = nGrilla;
        this->_tam = maximo+1;
    }

    // ACA TENGO QUE USAR EL .DEFINIR .... 4 VECES creo
    this->_grilla[c.latitud][c.longitud][c.latitud][c.longitud] = true;

    Vector<Vector<bool> > visitados;
    for (int i = 0; i < this->_tam; i++) {
        Vector<bool> visitadosAux;
        for (int j = 0; j < this->_tam; j++) {
            visitadosAux.AgregarAtras(false);
        }
        visitados.AgregarAtras(visitadosAux);
    }

    // Uso una Lista como si fuese una Cola
    Lista<Coordenada> aRecorrer; 
    aRecorrer.AgregarAtras(c);

    // @BUG
    // Deberia poner c en visitadas?? creo que si, para evitar ciclos infinitos
    visitados[c.latitud][c.longitud] = true;

    while (!aRecorrer.EsVacia()) {
        // Tomo el proximo y desencolo
        Coordenada act = aRecorrer.Primero();
        aRecorrer.Fin(); // Elimina la cabeza

        if (c.latitud > 0) {
            Coordenada laIzquierda = act.CoordenadaALaIzquierda();
            Nat x = laIzquierda.latitud;
            Nat y = laIzquierda.longitud;
            if (!visitados[x][y]) {
                visitados[x][y] = true;
                if (this->PosExistente(laIzquierda)) {
                    this->_grilla[c.latitud][c.longitud][x][y] = true;
                    this->_grilla[x][y][c.latitud][c.longitud] = true;
                    aRecorrer.AgregarAtras(laIzquierda);
                }
            }
        }

        if (c.longitud > 0) {
            Coordenada laAbajo = act.CoordenadaAbajo();
            Nat x = laAbajo.latitud;
            Nat y = laAbajo.longitud;
            if (!visitados[x][y]) {
                visitados[x][y] = true;
                if (this->PosExistente(laAbajo)) {
                    this->_grilla[c.latitud][c.longitud][x][y] = true;
                    this->_grilla[x][y][c.latitud][c.longitud] = true;
                    aRecorrer.AgregarAtras(laAbajo);
                }
            }
        }

        if (c.latitud < (this->_tam - 1)) {
            Coordenada laDerecha = act.CoordenadaALaDerecha();
            Nat x = laDerecha.latitud;
            Nat y = laDerecha.longitud;
            if (!visitados[x][y]) {
                visitados[x][y] = true;
                if (this->PosExistente(laDerecha)) {
                    this->_grilla[c.latitud][c.longitud][x][y] = true;
                    this->_grilla[x][y][c.latitud][c.longitud] = true;
                    aRecorrer.AgregarAtras(laDerecha);
                }
            }
        }

        if (c.longitud < (this->_tam - 1)) {
            Coordenada laArriba = act.CoordenadaArriba();
            Nat x = laArriba.latitud;
            Nat y = laArriba.longitud;
            if (!visitados[x][y]) {
                visitados[x][y] = true;
                if (this->PosExistente(laArriba)) {
                    this->_grilla[c.latitud][c.longitud][x][y] = true;
                    this->_grilla[x][y][c.latitud][c.longitud] = true;
                    aRecorrer.AgregarAtras(laArriba);
                }
            }
        }
    }
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

    // std::cout << "n: " << n << "\n";
    // std::cout << "tam: " << nuevaGrilla.longitud << "\n";

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
