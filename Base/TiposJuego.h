#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"

typedef unsigned int Jugador;
typedef unsigned int Nat;

typedef std::string Pokemon;

struct Coordenada{
	Nat latitud;
	Nat longitud;

	Coordenada(Nat latitud, Nat longitud)
	 : latitud(latitud), longitud(longitud) {}

};

inline bool operator == (const Coordenada& c1, const Coordenada& c2){
 return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
}

inline bool operator != (const Coordenada& c1, const Coordenada& c2){
 return not (c1 == c2);
}


struct jugYCantCapt{
	Nat id;
	Nat cant;

	jugYCantCapt(Nat id, Nat cant) : id(id), cant(cant) {}

	jugYCantCapt(const jugYCantCapt &otro) : id(otro.id), cant(otro.cant) {}

};


//TODO: Implementar...
inline bool operator < (const jugYCantCapt & j1, const jugYCantCapt & j2) {
	return false;
}

#endif
