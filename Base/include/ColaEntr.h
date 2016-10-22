#ifndef COLA_ENTR_H_
#define COLA_ENTR_H_

#include "../modulos.h"
#include "../aed2.h"

using namespace aed2;

class ColaEntr{
	public:

		class Iterador;

		ColaEntr();
		~ColaEntr();

		Iterador Encolar(Jugador e);

		bool EsVacia() const;

		Iterador Proximo() const;

		void Desencolar();

		class Iterador{
			public:
				Iterador();
				void Borrar();
		}

	private:

}


#endif
