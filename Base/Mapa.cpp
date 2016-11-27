#include "modulos.h"
#include <cassert>
#include <iostream>
#include "aed2.h"

using namespace aed2;
using namespace std;

Mapa::Mapa(){
    this->_tam = 0;
}

Mapa::~Mapa(){

}

void Mapa::AgregarCoord(const Coordenada &nuevaCoor) {

    std::cout << "\nEstoy en mapa AgregarCoord: " << nuevaCoor <<  "\n";
    // if (nuevaCoor.latitud > 120 || nuevaCoor.longitud > 120) {
    //     std::cout << "No seas asi. El mundo no tiene tantas coordenadas\n";
    //     return;
    // }

    // std::cout << "Entro en agregar coordenada " << nuevaCoor << "\n"; 
    Nat maximo = this->max(nuevaCoor.latitud, nuevaCoor.longitud);

    if (maximo+1 > this->_tam) {

        // CREO LA NUEVA GRILLA
        Nat mx = maximo+1;
        Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > nGrilla(mx);

        // Esto que sigue es la funcion this->crearGrilla(), mudarla luego
        // this->crearGrilla(nGrilla, mx);
        // std::cout << "Declaro nGrilla\n";
        for (Nat i = 0; i < mx; i++) {
            nGrilla.Definir(i, Arreglo<Arreglo<Arreglo<bool> > >(mx));
            for (Nat j = 0; j < mx; j++) {
                nGrilla[i].Definir(j, Arreglo<Arreglo<bool> >(mx));
                // for (Nat k = 0; k < mx; k++) {
                //     nGrilla[i][j].Definir(k, Arreglo<bool>(mx));
                // }
            }
        }
        // std::cout << "Defini nGrilla tam:   " << mx << "\n";

        this->copiarCoordenadas(nGrilla, this->_grilla);
        // std::cout << "Copie todas las coordenadas validas a la nueva grilla"<< "\n";

        // std::cout << "Salgo de copiarCoordenadas\n";
        
        this->_grilla = nGrilla;
        
        // std::cout << "Asigno nGrilla\n";
        
        this->_tam = maximo+1;
    }

    std::cout << "Termine el primer if\n";

    // std::cout << "\n---------------------\n\n";
    // std::cout << "lat: " << nuevaCoor.latitud <<"\n";
    // std::cout << "lon: " << nuevaCoor.longitud <<"\n";

    this->_grilla[nuevaCoor.latitud][nuevaCoor.longitud].Definir(nuevaCoor.latitud, Arreglo<bool>(this->_tam));
    this->_grilla[nuevaCoor.latitud][nuevaCoor.longitud][nuevaCoor.latitud].Definir(nuevaCoor.longitud, true);
    // std::cout << "Le pongo true a la actual\n";
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

    std::cout << "Termine el primer acceso\n";

    Conj<Coordenada> coors = this->Coordenadas(); // Esto incluye la que acabo de agregar
    Conj<Coordenada>::Iterador it = coors.CrearIt();
    while (it.HaySiguiente()) {
        Coordenada c = it.Siguiente();
        // std::cout << "Entro a while exterior: " << c << "\n";

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

        // @BUG
        // Deberia poner c en visitadas?? creo que si, para evitar ciclos infinitos
        visitados[c.latitud][c.longitud] = true;


        while (!aRecorrer.EsVacia()) {

            std::cout << "Entro a While principal\n";
            // std::cout << "Entro a while interior: " << c << "\n";
            // Tomo el proximo y desencolo
            Coordenada act = aRecorrer.Primero();
            aRecorrer.Fin(); // Elimina la cabeza

            // std::cout << "\n\nact: " << act << "\n";

            if (act.latitud > 0) {
                std::cout << "Entro a primer caso\n";
                Coordenada laIzquierda = act.CoordenadaALaIzquierda();
                Nat x = laIzquierda.latitud;
                Nat y = laIzquierda.longitud;
                // std::cout << "laIzquierda: " << laIzquierda << "\n";
                if (!visitados[x][y]) {
                    std::cout << "No fue visitada.. " << "\n";
                    visitados[x][y] = true;
                    std::cout << "La asigno visitada true.. " << "\n";
                    if (this->PosExistente(laIzquierda)) {
                        std::cout << "La izquierda existe.. " << "\n";
                        this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);
                        
                        std::cout << "Asigno primer mitad " << "\n";

                        this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);

                        std::cout << "Asigno segunda mitad " << "\n";
                        aRecorrer.AgregarAtras(laIzquierda);
                    }
                }
            }

            if (act.longitud > 0) {
                std::cout << "Entro a segundo caso\n";
                Coordenada laAbajo = act.CoordenadaAbajo();
                Nat x = laAbajo.latitud;
                Nat y = laAbajo.longitud;
                // std::cout << "laAbajo: " << laAbajo << "\n";
                if (!visitados[x][y]) {
                    visitados[x][y] = true;
                    if (this->PosExistente(laAbajo)) {
                        this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);
                        this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);
                        aRecorrer.AgregarAtras(laAbajo);
                    }
                }
            }

            if (act.latitud < (this->_tam - 1)) {
                std::cout << "Entro a tercer caso\n";
                Coordenada laDerecha = act.CoordenadaALaDerecha();
                Nat x = laDerecha.latitud;
                Nat y = laDerecha.longitud;
                // std::cout << "laDerecha: " << laDerecha << "\n";
                if (!visitados[x][y]) {
                    visitados[x][y] = true;
                    if (this->PosExistente(laDerecha)) {
                        this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);
                        this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);
                        aRecorrer.AgregarAtras(laDerecha);
                    }
                }
            }

            if (act.longitud < (this->_tam - 1)) {
                std::cout << "Entro a cuarto caso\n";
                Coordenada laArriba = act.CoordenadaArriba();
                Nat x = laArriba.latitud;
                Nat y = laArriba.longitud;
                // std::cout << "laArriba: " << laArriba << "\n";
                if (!visitados[x][y]) {
                    visitados[x][y] = true;
                    if (this->PosExistente(laArriba)) {
                        this->_grilla[c.latitud][c.longitud].Definir(x, Arreglo<bool>(this->_tam));
                        this->_grilla[c.latitud][c.longitud][x].Definir(y, true);
                        this->_grilla[x][y].Definir(c.latitud, Arreglo<bool>(this->_tam));
                        this->_grilla[x][y][c.latitud].Definir(c.longitud, true);
                        aRecorrer.AgregarAtras(laArriba);
                    }
                }
            }
        }

        std::cout << "Estoy por avanzar el iter\n";
        it.Avanzar(); // No olvidar!
        std::cout << "Termine de avanzar el iter\n";

    }

    std:cout << "Sali de mapa::agregarCoordenada\n";
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
    return this->def(this->_grilla, x, y, x, y);
}

// No estoy 100% seguro que se pregunte asi, peroes lo que hay
bool Mapa::def(
    const Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grilla,    
    Nat x, Nat y, Nat z, Nat w) const {

    return grilla.Definido(x) && 
        grilla[x].Definido(y) &&
        grilla[x][y].Definido(z) &&
        grilla[x][y][z].Definido(w) &&
        grilla[x][y][z][w];
}

bool Mapa::HayCamino(const Coordenada &c1, const Coordenada &c2) const{
    return this->def(this->_grilla, c1.latitud, c1.longitud, c2.latitud, c2.longitud) &&
        this->_grilla[c1.latitud][c1.longitud][c2.latitud][c2.longitud];
}

Nat Mapa::Tam() const{
    return this->_tam;
}


void crearGrilla(
    Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &nuevaGrilla,
    const Nat n) {
std::cout << "EL CODIGO DE CREAR GRILLA UBICARLO ACA\n";
}


void Mapa::imprimir() {
    Nat n = this->_grilla.Tamanho();
    for (Nat i = 0; i < n; i++) {
        for (Nat j = 0; j < n; j++) {
            for (Nat k = 0; k < n; k++) {
                for (Nat l = 0; l < n; l++) {
                    std::cout << this->def(this->_grilla, i, j, k, l) << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void Mapa::copiarCoordenadas(
    Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grillaNueva,
    Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grillaVieja) {

    for (Nat i = 0; i < grillaVieja.Tamanho(); i++) {
        for (Nat j = 0; j < grillaVieja.Tamanho(); j++) {
            if (this->def(grillaVieja, i, j, i, j)) {
                grillaNueva[i][j][i].Definir(j, grillaVieja[i][j][i][j]);
            }
        }
    }
}

Nat Mapa::max(Nat x, Nat y) {
    return (x >= y) ? x : y;
}
