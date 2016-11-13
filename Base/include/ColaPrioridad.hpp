#ifndef COLA_PRIORIDAD_H_
#define COLA_PRIORIDAD_H_

#include "../aed2.h"
#include <cassert>


template<class T>
class ColaPrioridad{
	public:

		class Iterador;

		ColaPrioridad();
		~ColaPrioridad();

		Iterador Encolar(const T &t);

		bool EsVacia() const;

		Iterador Proximo() const;

		void Desencolar();

		class Iterador{
			public:
				Iterador();
				void Borrar();
		};

	private:

};

template<class T>
ColaPrioridad<T>::ColaPrioridad(){
	assert(false);

}


template<class T>
ColaPrioridad<T>::~ColaPrioridad(){
	assert(false);

}


template<class T>
typename ColaPrioridad<T>::Iterador ColaPrioridad<T>::Encolar(const T &t){
	assert(false);
}

template<class T>
bool ColaPrioridad<T>::EsVacia() const{
	assert(false);
}

template<class T>
typename ColaPrioridad<T>::Iterador ColaPrioridad<T>::Proximo() const{
	assert(false);
}

template<class T>
void ColaPrioridad<T>::Desencolar(){
	assert(false);
}

/*******************************/
/* IMPLEMENTACION DEL ITERADOR */
/*******************************/

template<class T>
ColaPrioridad<T>::Iterador::Iterador(){
	assert(false);
}

template<class T>
void ColaPrioridad<T>::Iterador::Borrar(){
	assert(false);
}

#endif
