#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"
#include <cmath>

typedef unsigned int Jugador;
typedef unsigned int Nat;

typedef std::string Pokemon;

struct Coordenada{
	Nat latitud;
	Nat longitud;

	Coordenada(): latitud(0), longitud(0) {}

	Coordenada(Nat latitud, Nat longitud)
	 : latitud(latitud), longitud(longitud) {}

	Coordenada(const Coordenada &otra) : latitud(otra.latitud),
										 longitud(otra.longitud){}


	Nat distEuclidea(const Coordenada& otra){
		Nat x = this->latitud  - otra.latitud;
		Nat y = this->longitud - otra.longitud;

		Nat z = (x*x) + (y*y);

		// TODO: Chequear si redondear o que onda.
		return sqrt(z);
	}								 

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
