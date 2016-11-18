#ifndef COORDENADA_H_
#define COORDENADA_H_

#include "../aed2.h"
#include <cassert>
#include <iostream> 

class Coordenada{
    public:
        Coordenada();
        Coordenada(Nat latitud, Nat longitud);        
        Coordenada(const Coordenada &otra);

        ~Coordenada();

        Nat Latitud();
        Nat Longitud();

        Nat DistEuclidea(const Coordenada& c2);

        Coordenada CoordenadaArriba();
        Coordenada CoordenadaAbajo();
        Coordenada CoordenadaALaDerecha();
        Coordenada CoordenadaALaIzquierda();

        bool operator == (const Coordenada& c2);
        bool operator != (const Coordenada& c2);

    private:
        Nat latitud;
        Nat longitud;                
};

#endif