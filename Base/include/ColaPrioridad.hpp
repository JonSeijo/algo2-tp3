#ifndef COLA_PRIORIDAD_H_
#define COLA_PRIORIDAD_H_
//NOTA PARA MÁS TARDE: TERMINAR ENCOLAR Y SWAP NODOS CON TODAS SUS AUXILIARES

#include "../aed2.h"
#include <cassert>


template<class T>
class ColaPrioridad{
	public:

		class Iterador;

		ColaPrioridad();
		~ColaPrioridad();

		//Se encola por copia
		Iterador Encolar(const T t);

		bool EsVacia() const;

		Iterador Proximo() const;

		void Desencolar();

		class Iterador{
			
			public:
			
				T& Siguiente(); 
				void Borrar();

			private:
				
				typename ColaPrioridad<T>::Nodo* siguiente;
				ColaPrioridad<T>* estructura;

				//En los módulos están privadas estas funciones
				Iterador(): siguiente(NULL), estructura(NULL){};
				Iterador(typename ColaPrioridad<T>::Nodo* sig, ColaPrioridad<T> &c): siguiente(sig), estructura(&c){} ;
				bool iteradorConElemento() const;

		};

	private:
		//Estructura del nodo
		struct Nodo{
			T elem;
			Nodo* padre;
			Nodo* izq;
			Nodo* der;
			Nodo(const T elemento, Nodo* p, Nodo* i, Nodo* d): elem(elemento), padre(p), izq(i), der(d){ };
		};
		
		//Estructura del heap
		Nodo* raiz;
		Nodo* ultimo;
		
		//Funciones privadas

		void AsesinarHeap(Nodo* aBorrar);
		bool pertenece(const ColaPrioridad<T>::Nodo* buscador, const T& aBuscar) const;
		bool EstaCompleto() const;
		bool EsHijoIzquierdo(const Nodo* nodoEnCuestion) const;
		bool EsHijoDerecho(const Nodo* nodoEnCuestion) const;
		void EncolarSiUltimoEsHijoDerechoNoCompleto(const T t);
		void SiftUp(Nodo* n);
		void SwapNodos(Nodo* a, Nodo* b);
};

template<class T>
ColaPrioridad<T>::ColaPrioridad(){
	raiz = NULL;
	ultimo = NULL;
}


template<class T>
ColaPrioridad<T>::~ColaPrioridad(){
	AsesinarHeap(raiz);
}


template<class T>
typename ColaPrioridad<T>::Iterador ColaPrioridad<T>::Encolar(const T t){
	if(EsVacia()){
		Nodo* nuevoNodo = new Nodo(t, NULL, NULL, NULL); 
		raiz = nuevoNodo;
		ultimo = nuevoNodo;
	}
	else if(EstaCompleto()){
		Nodo* nodoActual = raiz;
		while(nodoActual -> izq != NULL){
			nodoActual = nodoActual -> izq;
		}
		Nodo* nuevoNodo = new Nodo(t, nodoActual, NULL, NULL);
		nodoActual -> izq = nuevoNodo;
		ultimo = nuevoNodo;		
	}
	else if(EsHijoIzquierdo(ultimo)){
		Nodo* nuevoNodo = new Nodo(t, ultimo -> padre, NULL, NULL);
		ultimo -> padre -> der = nuevoNodo;
		ultimo = nuevoNodo;
	}
	else if(EsHijoDerecho(ultimo)){
		EncolarSiUltimoEsHijoDerechoNoCompleto(t);
	}

}

template<class T>
bool ColaPrioridad<T>::EsVacia() const{
	return (raiz == NULL) && (ultimo == NULL);
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
/*
template<class T>
ColaPrioridad<T>::Iterador::Iterador(){
	assert(false);
}
*/
template<class T>
void ColaPrioridad<T>::Iterador::Borrar(){
	assert(false);
}

template<class T>
T& ColaPrioridad<T>::Iterador::Siguiente(){
	assert(iteradorConElemento());
	return siguiente -> elemento;
}
#endif

template<class T>
void ColaPrioridad<T>::AsesinarHeap(Nodo* aBorrar){
	if(aBorrar != NULL){
		AsesinarHeap(aBorrar -> izq);
		AsesinarHeap(aBorrar -> der);
		delete aBorrar;
		aBorrar = NULL;
	}
}

template<class T>
bool ColaPrioridad<T>::pertenece(const ColaPrioridad<T>::Nodo* buscador, const T& aBuscar) const{
	if(buscador == NULL){
		return false;
	}
	else if(buscador -> elemento == aBuscar){
		return true;
	}
	else{
		return pertenece(buscador -> izq)||pertenece(buscador -> der);
	}
}

//Pre: No es vacio
template<class T>
bool ColaPrioridad<T>::EstaCompleto() const{
	assert(!EsVacia());
	Nodo* nodoActual = raiz;
	while(nodoActual -> der != NULL){
		nodoActual = nodoActual -> der;
	}
	return nodoActual == ultimo;
}

//Pre: nodoEnCuestion no es NULL
template<class T>
bool ColaPrioridad<T>::EsHijoIzquierdo(const Nodo* nodoEnCuestion) const{
	if(nodoEnCuestion -> padre == NULL){
		return false;
	}
	else{
		return nodoEnCuestion -> padre -> izq == nodoEnCuestion;
	}
}

//Pre: nodoEnCuestion no es NULL (copypasta del de arriba)
template<class T>
bool ColaPrioridad<T>::EsHijoDerecho(const Nodo* nodoEnCuestion) const{
	if(nodoEnCuestion -> padre == NULL){
		return false;
	}
	else{
		return nodoEnCuestion -> padre -> der == nodoEnCuestion;
	}
}

template<class T>
void ColaPrioridad<T>::EncolarSiUltimoEsHijoDerechoNoCompleto(const T t){
	Nodo* nuevoUltimoPadre = ultimo;
	while(!EsHijoIzquierdo(nuevoUltimoPadre)){
		nuevoUltimoPadre = nuevoUltimoPadre -> padre;
	}
	if(nuevoUltimoPadre -> padre == NULL){
		nuevoUltimoPadre = nuevoUltimoPadre -> der;
	}
	else{
		nuevoUltimoPadre = nuevoUltimoPadre -> padre -> der;
	}
	while(nuevoUltimoPadre -> izq != NULL){
		nuevoUltimoPadre = nuevoUltimoPadre -> izq;
	}
	Nodo* nuevoNodo = new Nodo(t, nuevoUltimoPadre, NULL, NULL);
	nuevoUltimoPadre -> izq = nuevoNodo;
	ultimo = nuevoNodo; 
}

template<class T>
void ColaPrioridad<T>::SiftUp(Nodo* n){
	while(n -> padre != NULL){
		if((n -> elemento) < (n -> padre -> elemento)){
			SwapNodos(n, n -> padre);
		}
		else{
			break;
		}
	}
}

template<class T>
void ColaPrioridad<T>::SwapNodos(Nodo* a, Nodo* b){
	
}

template<class T>
bool ColaPrioridad<T>::Iterador::iteradorConElemento() const{
	return siguiente != NULL;
}