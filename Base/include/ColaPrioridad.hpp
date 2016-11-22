#ifndef COLA_PRIORIDAD_H_
#define COLA_PRIORIDAD_H_

#include "../aed2.h"
#include "./../TiposJuego.h"
#include <cassert>
#include <iostream> //Para probar como queda el heap después de encolar y desencolar

template<class T>
class ColaPrioridad{
	public:

		class Iterador;

		ColaPrioridad();
		~ColaPrioridad();

		//Se encola por copia
		Iterador Encolar(const T t);

		bool EsVacia() const;

		T Proximo() const;

		void Desencolar();

		class Iterador{
			
			public:
			
				T& Siguiente(); 
				void Borrar();
				Iterador(): siguiente(NULL), estructura(NULL){};

			private:
				
				typename ColaPrioridad<T>::Nodo* siguiente;
				ColaPrioridad<T>* estructura;

				//En los módulos están privadas estas funciones
				Iterador(typename ColaPrioridad<T>::Nodo* sig, ColaPrioridad<T>* c): siguiente(sig), estructura(c){} ;
				bool iteradorConElemento() const;
				friend typename ColaPrioridad<T>::Iterador ColaPrioridad<T>::Encolar(const T t);

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
		void SwapConHijo(Nodo* a, Nodo* b);
		void SwapConHijoIzquierdo(Nodo* a, Nodo* b);
		void SwapConHijoDerecho(Nodo* a, Nodo* b);
		void SwapDisjunto(Nodo* a, Nodo* b);
		void EliminarUltimo();
		bool HayUnicoNodoEnUltimoNivel() const;
		void SiftDown(Nodo* a);
		bool EsMenorNodos(Nodo* a, Nodo* b) const;

		//Prueba para ver al heap y testear, es algo-order y muestra en este orden:
		// izquierdo, derecho, raiz
		void mostrar(std::ostream&) const;
		friend std::ostream& operator<<(std::ostream& os, const ColaPrioridad<T> &c){
			c.mostrar(os);
			return os;
		};
		void mostrarRecursivo(std::ostream&, const Nodo* puntero) const;
};

template<class T>
ColaPrioridad<T>::ColaPrioridad(){
	this -> raiz = NULL;
	this -> ultimo = NULL;
}


template<class T>
ColaPrioridad<T>::~ColaPrioridad(){
	AsesinarHeap(this -> raiz);
}


template<class T>
typename ColaPrioridad<T>::Iterador ColaPrioridad<T>::Encolar(const T t){
	if(EsVacia()){
		Nodo* nuevoNodo = new Nodo(t, NULL, NULL, NULL); 
		this -> raiz = nuevoNodo;
		this -> ultimo = nuevoNodo;
	}
	else if(EstaCompleto()){
		Nodo* nodoActual = this -> raiz;
		while(nodoActual -> izq != NULL){
			nodoActual = nodoActual -> izq;
		}
		Nodo* nuevoNodo = new Nodo(t, nodoActual, NULL, NULL);
		nodoActual -> izq = nuevoNodo;
		this -> ultimo = nuevoNodo;		
	}
	else if(EsHijoIzquierdo(this -> ultimo)){
		Nodo* nuevoNodo = new Nodo(t, this -> ultimo -> padre, NULL, NULL);
		this -> ultimo -> padre -> der = nuevoNodo;
		this -> ultimo = nuevoNodo;
	}
	else if(EsHijoDerecho(this->ultimo)){
		this -> EncolarSiUltimoEsHijoDerechoNoCompleto(t);
	}
	Nodo* m = this -> ultimo;
	SiftUp(m);
	Nodo* p = m;
	return Iterador(p, this);
}

template<class T>
bool ColaPrioridad<T>::EsVacia() const{
	return (this->raiz == NULL) && (this->ultimo == NULL);
}

template<class T>
T ColaPrioridad<T>::Proximo() const{
	return this->raiz->elem;
}

template<class T>
void ColaPrioridad<T>::Desencolar(){
	SwapNodos(this -> raiz, this -> ultimo);
	EliminarUltimo();
	SiftDown(this -> raiz);
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
	Nodo* intercambiado = this -> estructura -> ultimo;
	(this -> estructura) -> SwapNodos(this -> siguiente, this -> estructura -> ultimo);
	(this -> estructura) -> EliminarUltimo();
	if(intercambiado -> padre != NULL){
		if((intercambiado -> elem) < (intercambiado -> padre -> elem)){	
			(this -> estructura) -> SiftUp(intercambiado);
		}
		else{
			(this -> estructura) -> SiftDown(intercambiado);
		}
	}
	else{
		(this -> estructura) -> SiftDown(intercambiado);
	}
}

template<class T>
T& ColaPrioridad<T>::Iterador::Siguiente(){
	assert(iteradorConElemento());
	return siguiente -> elem;
}


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
	Nodo* nodoActual = this->raiz;
	while(nodoActual -> der != NULL){
		nodoActual = nodoActual -> der;
	}
	return nodoActual == this->ultimo;
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
	Nodo* nuevoUltimoPadre = this->ultimo;
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
	this->ultimo = nuevoNodo; 
}
//Pre: n != NULL
template<class T>
void ColaPrioridad<T>::SiftUp(Nodo* n){
	while(n -> padre != NULL){
		if((n -> elem) < (n -> padre -> elem)){
			SwapNodos(n, n -> padre);
		}
		else{
			break;
		}
	}
}
//Pre: a y b != NULL
template<class T>
void ColaPrioridad<T>::SwapNodos(Nodo* a, Nodo* b){
	if((a -> padre) == b){
		SwapConHijo(b, a);
	}
	else{
		if(b -> padre == a){
			SwapConHijo(a, b);
		}
		else{
			SwapDisjunto(a, b);
		}
	}
	if(this -> raiz == a){
		this -> raiz = b;
	}
	else{
		if(this -> raiz == b){
			this -> raiz = a;
		}
	}
	if(this -> ultimo == a){
		this -> ultimo = b;
	}
	else{
		if(this -> ultimo == b){
			this -> ultimo = a;
		}
	}
}

template<class T>
void ColaPrioridad<T>::SwapConHijo(Nodo* a, Nodo* b){
	if(a -> izq == b){
		SwapConHijoIzquierdo(a, b);
	}
	else{
		if(a -> der == b){
			SwapConHijoDerecho(a, b);
		}
	}
}

template<class T>
void ColaPrioridad<T>::SwapConHijoIzquierdo(Nodo* a, Nodo* b){
	Nodo* tmpderA = a -> der;
	a -> der = b -> der;
	if(a -> der != NULL){
		a -> der -> padre = a;
	}
	b -> der = tmpderA;
	if(b -> der != NULL){
		b -> der -> padre = b;
	}
	if(EsHijoIzquierdo(a)){
		a -> padre -> izq = b;
	}
	else if(EsHijoDerecho(a)){
		a -> padre -> der = b;
	}
	b -> padre = a -> padre;
	if(b -> izq != NULL){
		b -> izq -> padre = a;
	}
	a -> izq = b -> izq;
	b -> izq = a;
	a -> padre = b;
}

template<class T>
void ColaPrioridad<T>::SwapConHijoDerecho(Nodo* a, Nodo* b){
	Nodo* tmpizqA = a -> izq;
	a -> izq = b -> izq;
	if(a -> izq != NULL){
		a -> izq -> padre = a;
	}
	b -> izq = tmpizqA;
	if(b -> izq != NULL){
		b -> izq -> padre = b;
	}
	if(EsHijoIzquierdo(a)){
		a -> padre -> izq = b;
	}
	else if(EsHijoDerecho(a)){
		a -> padre -> der = b;
	}
	b -> padre = a -> padre;
	if(b -> der != NULL){
		b -> der -> padre = a;
	}
	a -> der = b -> der;
	b -> der = a;
	a -> padre = b;
}

template<class T>
void ColaPrioridad<T>::SwapDisjunto(Nodo* a, Nodo* b){
	if(EsHijoIzquierdo(b)){
		b -> padre -> izq = a;
	}
	else{
		if(EsHijoDerecho(b)){
			b -> padre -> der = a;
		}
	}
	if(b -> der != NULL){
		b -> der -> padre = a;
	}
	if(b -> izq != NULL){
		b -> izq -> padre = a;
	}
	if(EsHijoIzquierdo(a)){
		a -> padre -> izq = b;
	}
	else{
	//Acá hay un error en el módulo, en vez de preguntar por a preguntaba por b.
		if(EsHijoDerecho(a)){
			a -> padre -> der = b;
		}
	}
	if(a -> der != NULL){
		a -> der -> padre = b;
	}
	if(a -> izq != NULL){
		a -> izq -> padre = b;
	}
	Nodo* tmpPadreB = b -> padre;
	Nodo* tmpIzqB = b -> izq;
	Nodo* tmpDerB = b -> der;
	b -> padre = a -> padre;
	b -> izq = a -> izq;
	b -> der = a -> der;
	a -> padre = tmpPadreB;
	a -> izq = tmpIzqB;
	a -> der = tmpDerB;
}

template<class T>
void ColaPrioridad<T>::EliminarUltimo(){
	if(this -> ultimo == this -> raiz){
		delete this -> ultimo;
		this -> ultimo = NULL;
		this -> raiz = NULL;
	}
	else{
		if(EsHijoDerecho(this -> ultimo)){
			Nodo* antiguoUltimo = this -> ultimo;
			this -> ultimo = this -> ultimo -> padre -> izq;
			this -> ultimo -> padre -> der = NULL;
			delete antiguoUltimo;
			antiguoUltimo = NULL;
		}
		else{
			if(HayUnicoNodoEnUltimoNivel()){
				this -> ultimo -> padre -> izq = NULL;
				delete this -> ultimo;
				this -> ultimo = NULL;
				Nodo* nodoActual = this -> raiz;
				while(nodoActual -> der != NULL){
					nodoActual = nodoActual -> der;
				}
				this -> ultimo = nodoActual;
			}
			else{
				Nodo* nuevoUltimo = this -> ultimo;
				this -> ultimo -> padre -> izq = NULL;
				while(!EsHijoDerecho(nuevoUltimo)){
					nuevoUltimo = nuevoUltimo -> padre;
				}
				nuevoUltimo = nuevoUltimo -> padre -> izq;
				while(nuevoUltimo -> der != NULL){
					nuevoUltimo = nuevoUltimo -> der;
				}
				delete this -> ultimo;
				this -> ultimo = nuevoUltimo;
			}
		}
	}
}

template<class T>
bool ColaPrioridad<T>::HayUnicoNodoEnUltimoNivel() const{
	Nodo* nodoActual = this -> raiz;
	while(nodoActual -> izq != NULL){
		nodoActual = nodoActual -> izq;
	}
	return nodoActual == this -> ultimo;
}

//Se rompe con n == NULL (pasa cuando desencolamos un heap con un solo elemento)
//No lo tomamos en cuenta en el tp2
template<class T>
void ColaPrioridad<T>::SiftDown(Nodo* n){
	if(n != NULL){
		bool sigueBajando = true;
		while(sigueBajando){
			if(EsMenorNodos(n -> izq, n -> der)){
				if((n -> izq -> elem) < (n -> elem)){
					SwapNodos(n, n -> izq);
				}
				else{
					sigueBajando = false;
				}
			}
			else{
				if(EsMenorNodos(n -> der, n -> izq)){
					if((n -> der -> elem) < (n -> elem)){
						SwapNodos(n, n -> der);
					}
					else{
						sigueBajando = false;
					}
				}
				else{
					sigueBajando = false;
				}
			}
		}
	}
}

template<class T>
bool ColaPrioridad<T>::EsMenorNodos(Nodo* a, Nodo* b) const{
	if(a != NULL || b != NULL){
		if(a == NULL && b != NULL){
			return false;
		}
		else{
			if(a != NULL && b == NULL){
				return true;
			}
			else{
				if((a -> elem) < (b -> elem) || (a -> elem) == (b -> elem)){
					return true;
				}
				//Este else no estaba en los módulos
				else{
					return false;
				}
			}
		}
	}
	else{
		return false;
	}
}

template<class T>
void ColaPrioridad<T>::mostrar(std::ostream& os) const{
	os << "{";
	if(this -> raiz == NULL){
		os << "}";
	}
	else{
		if((this -> raiz -> izq == NULL) && (this -> raiz -> der == NULL)){
			os << raiz -> elem << "}";
		}
		else{
			if((this -> raiz -> izq == NULL) && (this -> raiz -> der != NULL)){
				mostrarRecursivo(os, this -> raiz -> der);
				os << raiz -> elem << "}" << std::endl;
			}
			else{
				if((this -> raiz -> izq != NULL) && (this -> raiz -> der == NULL)){
					mostrarRecursivo(os, this -> raiz -> izq);
					os << raiz -> elem << "}" << std::endl;
				}
				else{
					mostrarRecursivo(os, this -> raiz -> izq);
					mostrarRecursivo(os, this -> raiz -> der);
					os << raiz -> elem << "}" << std::endl;
				}
			}
		}
	}
}

template<class T>
void ColaPrioridad<T>::mostrarRecursivo(std::ostream& os, const Nodo* puntero) const{
	if(puntero != NULL){
		mostrarRecursivo(os, puntero -> izq);
		mostrarRecursivo(os, puntero -> der);
		os << puntero -> elem << ", ";
	}
}

template<class T>
bool ColaPrioridad<T>::Iterador::iteradorConElemento() const{
	return siguiente != NULL;
}

#endif