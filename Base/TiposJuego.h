#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"


typedef unsigned int Jugador;
typedef unsigned int Nat;

typedef std::string Pokemon;

struct jugYCantCapt{
	Nat id;
	Nat cant;

	jugYCantCapt(Nat id, Nat cant) : id(id), cant(cant) {}

	jugYCantCapt(const jugYCantCapt &otro) : id(otro.id), cant(otro.cant) {}

};


inline bool operator < (const jugYCantCapt & j1, const jugYCantCapt & j2) {
	if (j1.cant == j2.cant) {
		return j1.id < j2.id;
	}
	return j1.cant < j2.cant;
}

#endif
