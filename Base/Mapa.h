
#ifndef MAPA_H_
#define MAPA_H_

#include "TiposJuego.h"
#include "aed2.h"

using namespace aed2;
using namespace std;

class Mapa {
    public:

        Mapa();
        ~Mapa();
        void AgregarCoord(const Coordenada &c);

        Conj<Coordenada> Coordenadas() const;

        bool PosExistente(const Coordenada &c) const;

        bool HayCamino(const Coordenada &c1, const Coordenada &c2) const;

        Nat Tam() const;

        // ESTO ESTA PARA DEBBUGUEAR
        void imprimir();


    private:

        bool def(
            const Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grilla,
            Nat x, Nat y, Nat z, Nat w) const;

        void copiarCoordenadas(
            Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grillaNueva,
            Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &grillaVieja
        );

        void crearGrilla(
            Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > &nuevaGrilla,
            const Nat n
        );

        Arreglo<Arreglo<Arreglo<Arreglo<bool> > > > _grilla;
        Nat _tam;

        Nat max(Nat x, Nat y);
};

#endif
