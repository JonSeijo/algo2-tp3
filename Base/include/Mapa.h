
#ifndef MAPA_H_
#define	MAPA_H_

#include "../TiposJuego.h"
#include "../aed2/Conj.h"
#include "../aed2/Arreglo.h"

using namespace aed2;

class Mapa {
  public:

    Mapa();
    void AgregarCoord( const Coordenada &c);

    Conj<Coordenada> Coordenadas() const;

    bool PosExistente(const Coordenada &c) const;

    bool HayCamino(const Coordenada &c1, const Coordenada &c2) const;

    Nat Tam() const;

  private:

}

#endif
