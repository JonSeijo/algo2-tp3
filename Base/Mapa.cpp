#include "modulos.h"
#include <cassert>
#include <iostream>
#include "aed2.h"

#include <cassert>

using namespace aed2;
using namespace std;

Mapa::Mapa(){
    this->_tam = 0;
}

Mapa::~Mapa(){

}

void Mapa::AgregarCoord(const Coordenada &nuevaCoor) {
    Nat maximo = this->max(nuevaCoor.latitud, nuevaCoor.longitud);

    // Si la nueva coordenada no entra en el mapa
    // Entonces creo una nueva grilla del tam de esa coordenada
    if (maximo+1 > this->_tam) {
        Nat mx = maximo+1;
        Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > nGrilla(mx);

        this->crearGrilla(nGrilla, mx);

        this->copiarCoordenadas(nGrilla, this->_grilla, mx);

        this->_grilla = nGrilla;

        this->_tam = maximo+1;
    }

    if (!this->_grilla[nuevaCoor.latitud][nuevaCoor.longitud].Definido(nuevaCoor.latitud)) {
        this->_grilla[nuevaCoor.latitud][nuevaCoor.longitud].Definir(nuevaCoor.latitud, Arreglo<bool>(this->_tam));
    }
    this->_grilla[nuevaCoor.latitud][nuevaCoor.longitud][nuevaCoor.latitud].Definir(nuevaCoor.longitud, true);

    /*
    Habia un bug groso en el tp2 (que se arregla facil)
    Basicamente se actualizaban los HayCamino para todas las coordenadas en relacion a la nueva que agregaba
    Pero no se actualizaban las viejas con las viejas
    Ej de algo que funcionaba mal:

    Tengo el (0,0) y el (2,0) en el mapa, NO hay camino (esto esta bien)
    Agrego el (0,1) al mapa, ahora SI deberia haber camino (porque estan unidas por la nueva que agregaba)
    Pero esto no estaba siendo actualizado

    La solucion fue recalcular los HayCamino para toda coordenada
    Esto no cambia la complejidad, como maximo hay tam^2 coordenadas (mapa lleno)
    y para cada coordenada la comparo con todas las demas:  tam^2 * tam^2 = tam^4 = O(tam^4)
    */

    Conj<Coordenada> coors = this->Coordenadas(); // Esto incluye la que acabo de agregar
    Conj<Coordenada>::Iterador it = coors.CrearIt();
    while (it.HaySiguiente()) {
        Coordenada c = it.Siguiente();

        // Creo una grilla del tam del mapa, llena de falsos, para representar las que ya visite
        Vector<Vector<bool> > visitados;
        for (Nat i = 0; i < this->_tam; i++) {
            Vector<bool> visitadosAux;
            for (Nat j = 0; j < this->_tam; j++) {
                visitadosAux.AgregarAtras(false);
            }
            visitados.AgregarAtras(visitadosAux);
        }

        // Uso una Lista como si fuese una Cola
        Lista<Coordenada> aRecorrer;
        aRecorrer.AgregarAtras(c);

        visitados[c.latitud][c.longitud] = true;

        while (!aRecorrer.EsVacia()) {
            // Tomo el proximo y desencolo
            Coordenada act = aRecorrer.Primero();
            aRecorrer.Fin(); // Elimina la cabeza

            if (act.latitud > 0) {
                Coordenada laIzquierda = act.CoordenadaALaIzquierda();
                Nat x = laIzquierda.latitud;
                Nat y = laIzquierda.longitud;
                // std::cout << "laIzquierda: " << laIzquierda << "\n";

                // La idea para todas las coors es:
                // Recorro todas las coors que estan "unidas" a la original.
                // Si no fue visitada, la visito y si la izquierda/der/arr/abajo existe,
                // entonces marco que hay camino con la original, y la agrego a la lista para visitar

                if (!visitados[x][y]) {
                    visitados[x][y] = true;
                    if (this->PosExistente(laIzquierda)) {

                        if (!this->_grilla[c.latitud][c.longitud].Definido(x)) {
                            this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        }
                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);

                        if (!this->_grilla[x][y].Definido(c.latitud)) {
                            this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        }

                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);

                        aRecorrer.AgregarAtras(laIzquierda);
                    }
                }
            }

            if (act.longitud > 0) {
                Coordenada laAbajo = act.CoordenadaAbajo();
                Nat x = laAbajo.latitud;
                Nat y = laAbajo.longitud;
                // std::cout << "laAbajo: " << laAbajo << "\n";
                if (!visitados[x][y]) {
                    visitados[x][y] = true;
                    if (this->PosExistente(laAbajo)) {

                        if (!this->_grilla[c.latitud][c.longitud].Definido(x)) {
                            this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        }

                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);

                        if (!this->_grilla[x][y].Definido(c.latitud)) {
                            this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        }

                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);

                        aRecorrer.AgregarAtras(laAbajo);
                    }
                }
            }

            if (act.latitud < (this->_tam - 1)) {
                Coordenada laDerecha = act.CoordenadaALaDerecha();
                Nat x = laDerecha.latitud;
                Nat y = laDerecha.longitud;
                // std::cout << "laDerecha: " << laDerecha << "\n";
                if (!visitados[x][y]) {
                    visitados[x][y] = true;
                    if (this->PosExistente(laDerecha)) {

                        if (!this->_grilla[c.latitud][c.longitud].Definido(x)) {
                            this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        }

                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);

                        if (!this->_grilla[x][y].Definido(c.latitud)) {
                            this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        }

                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);

                        aRecorrer.AgregarAtras(laDerecha);
                    }
                }
            }

            if (act.longitud < (this->_tam - 1)) {
                Coordenada laArriba = act.CoordenadaArriba();
                Nat x = laArriba.latitud;
                Nat y = laArriba.longitud;
                // std::cout << "laArriba: " << laArriba << "\n";
                if (!visitados[x][y]) {
                    visitados[x][y] = true;
                    if (this->PosExistente(laArriba)) {

                        if (!this->_grilla[c.latitud][c.longitud].Definido(x)) {
                            this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        }

                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);

                        if (!this->_grilla[x][y].Definido(c.latitud)) {
                            this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        }

                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);

                        aRecorrer.AgregarAtras(laArriba);
                    }
                }
            }
        }

        it.Avanzar(); // No olvidar!

    }
}

Conj<Coordenada> Mapa::Coordenadas() const{
    Conj<Coordenada> coors;
    for (Nat i = 0; i < this->_tam; i++) {
        for (Nat j = 0; j < this->_tam; j++) {
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
    return this->def(this->_grilla, x, y, x, y) && this->_grilla[x][y][x][y];
}

// Esta funcion no es necesaria, pero me ahorro tipear
bool Mapa::def(
    const Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grilla,
    Nat x, Nat y, Nat z, Nat w) const {

    return grilla.Definido(x) &&
        grilla[x].Definido(y) &&
        grilla[x][y].Definido(z) &&
        grilla[x][y][z].Definido(w);
}

bool Mapa::HayCamino(const Coordenada &c1, const Coordenada &c2) const{
    return this->def(this->_grilla, c1.latitud, c1.longitud, c2.latitud, c2.longitud) &&
        this->_grilla[c1.latitud][c1.longitud][c2.latitud][c2.longitud];
}

Nat Mapa::Tam() const{
    return this->_tam;
}


// nGrilla debe ser una grilla declarada pero sin definir
void Mapa::crearGrilla(
    Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &nGrilla,
    const Nat mx) {

    for (Nat i = 0; i < mx; i++) {
        nGrilla.Definir(i, Arreglo<Arreglo<Arreglo<bool> > >(mx));
        for (Nat j = 0; j < mx; j++) {
            nGrilla[i].Definir(j, Arreglo<Arreglo<bool> >(mx));
        }
    }
}

// La grilla nueva es una grilla vacia, (mas grande)
// Me copio las coordenadas que ya existian en la vieja
void Mapa::copiarCoordenadas(
    Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grillaNueva,
    Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grillaVieja,
    Nat nuevoTam) {

    for (Nat i = 0; i < grillaVieja.Tamanho(); i++) {
        for (Nat j = 0; j < grillaVieja.Tamanho(); j++) {
            if (this->def(grillaVieja, i, j, i, j)) {
                if (!grillaNueva[i][j].Definido(i)) {
                    grillaNueva[i][j].Definir(i, Arreglo<bool>(nuevoTam));
                }
                grillaNueva[i][j][i].Definir(j, grillaVieja[i][j][i][j]);
            }
        }
    }
}

Nat Mapa::max(Nat x, Nat y) {
    return (x >= y) ? x : y;
}

// Solo para testeo
void Mapa::imprimir() {
    Nat n = this->_grilla.Tamanho();
    for (Nat i = 0; i < n; i++) {
        for (Nat j = 0; j < n; j++) {
            std::cout << this->def(this->_grilla, i, j, i, j) << " ";
        }
        std::cout << "\n";
    }
}
