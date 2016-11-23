
#ifndef MAPA_H_
#define MAPA_H_

#include "../TiposJuego.h"
#include "../aed2.h"

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

    private:

        void copiarCoordenadas(
            Vector<Vector<Vector<Vector<bool> > > > &grillaNueva,
            Vector<Vector<Vector<Vector<bool> > > > &grillaVieja
        );

        Vector<Vector<Vector<Vector<bool> > > > crearGrilla(
            Vector<Vector<Vector<Vector<bool> > > > &nuevaGrilla,
            const Nat n
        );

        Vector<Vector<Vector<Vector<bool> > > > _grilla;
        Nat _tam;

        Nat max(Nat x, Nat y);

        void imprimir();

};

#endif
