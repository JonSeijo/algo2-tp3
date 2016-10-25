/*
 * Diccionario implementado sobre trie cuyas claves son string,
 */

#ifndef DICC_STRING_H_
#define	DICC_STRING_H_

#include <ostream>
#include <string>
#include "../aed2.h"

using namespace aed2;
using namespace std;

template<class S>
class DiccString{
  public:

    class Iterador;

    DiccString();
    ~DiccString();


    //no esta en el modulo.
    DiccString(const DiccString<S>& otro);

    void Definir(const string &clave, const S& significado);

    bool Definido(const string &clave) const;

    //Creo que siempre se devuelve como referencia modificable
    const S& Significado(const string& clave) const;

    S& Significado(const string& clave);

    void Borrar(const string& clave);

    Nat CantClaves() const;

    /**********************************
     * Iterador de DiccString, modificable *
     **********************************/
    class Iterador{
    public:

      struct par;

      Iterador(const DiccString<S> &d);

      ~Iterador();

      bool HayMas() const;

      par& Actual() const;

      void Avanzar();
      struct par {
          S dato;
          string clave;

          par(const S &d, const string &c) : dato(d), clave(c){}
      };

    private:


      /*
       * En el modulo no es un puntero pero es una desgracia, si desaprobamos
       * hay que modificarlo a puntero.
       */
      DiccString<S>* _dicc;

      Conj<string>::Iterador _itClave;


    };

  private:

    struct Nodo {
      S* definicion;
      Arreglo< Nodo* > siguientes;
      DiccString<S>::Iterador* itClave;

      Nodo() : definicion(NULL), siguientes(), itClave(NULL){

  		    siguientes = Arreglo<Nodo*>(256);

  		};
    };

    Conj<string> _claves;

    Nodo* _raiz;

};


// Implementacion Dicc

template< class S>
DiccString<S>::DiccString()
 : _claves(), _raiz(NULL)
{}


template< class S>
DiccString<S>::~DiccString(){

	Conj<string>::Iterador it = _claves.CrearIt();

	while(it.HaySiguiente()){

		Borrar(it.Siguiente());

		it.Avanzar();
	}

	if(_raiz != NULL){
		Nodo* temp = _raiz;
		delete temp;
		_raiz = NULL;
	}
}




//Constructor por copia.
template<class S>
DiccString<S>::DiccString(const DiccString<S>& otro){
  //TODO:	No esta en el modulo.
}



template<class S>
void DiccString<S>::Definir(const string& clave, const S& significado){
	if (_claves.Cardinal() == 0 || _raiz == NULL) {
        _raiz = new Nodo;
    }

    Nodo* nodoActual = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {

        if (nodoActual->siguientes[int(clave[i])] == NULL) {
            nodoActual->siguientes[int(clave[i])] = new Nodo();
        }

        nodoActual = nodoActual->siguientes[int(clave[i])];
    }

	if(nodoActual->definicion != NULL){

		S* valor = nodoActual->definicion;
		nodoActual->definicion = NULL;
		delete valor;

	}else{


		nodoActual->definicion = new S(significado);

		*nodoActual->itClave = _claves.AgregarRapido(clave);
	}


}


template<class S>
bool DiccString<S>::Definido(const string& clave) const{

      Nodo* nodoActual = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {

        if (nodoActual->siguientes[int(clave[i])] == NULL) {
            nodoActual->siguientes[int(clave[i])] = new Nodo();
        }

        nodoActual = nodoActual->siguientes[int(clave[i])];
    }


  return nodoActual->definicion != NULL;
}

template< class S>
const S& DiccString<S>::Significado(const string& clave) const {
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif
  Nodo* nodoActual = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {

        if (nodoActual->siguientes[int(clave[i])] == NULL) {
            nodoActual->siguientes[int(clave[i])] = new Nodo();
        }

        nodoActual = nodoActual->siguientes[int(clave[i])];
    }



  return nodoActual->definicion;
}

template<class S>
S& DiccString<S>::Significado(const string& clave) {
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  Nodo* nodoActual = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {

        if (nodoActual->siguientes[int(clave[i])] == NULL) {
            nodoActual->siguientes[int(clave[i])] = new Nodo();
        }

        nodoActual = nodoActual->siguientes[int(clave[i])];
    }



  return nodoActual->definicion;

}

template<class S>
void DiccString<S>::Borrar(const string& clave){
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif


	Nodo* nodoActual = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {

        if (nodoActual->siguientes[int(clave[i])] == NULL) {
            nodoActual->siguientes[int(clave[i])] = new Nodo();
        }

        nodoActual = nodoActual->siguientes[int(clave[i])];
    }

	if(nodoActual->definicion != NULL){

		S* valor = nodoActual->definicion;
		nodoActual->definicion = NULL;
		delete valor;

		nodoActual->itClave->EliminarSiguiente();

	}
}

template<class S>
Nat DiccString<S>::CantClaves() const{
  return _claves.Cardinal();
}

/*******************************/
/* IMPLEMENTACION DEL ITERADOR */
/*******************************/
template <class S>
DiccString<S>::Iterador::Iterador(const DiccString<S> &d){

    *_dicc = d;
   _itClave = d._claves.CrearIt();

}

template <class S>
bool DiccString<S>::Iterador::HayMas() const{
  return _itClave.HaySiguiente();
}

template <class S>
typename DiccString<S>::Iterador::par& DiccString<S>::Iterador::Actual() const{

  string clave = _itClave.Siguiente();
  S def(_dicc->Obtener(clave));
  typename DiccString<S>::Iterador::par res(clave, def);

  return res;
}

template <class S>
void DiccString<S>::Iterador::Avanzar(){
  _itClave.Avanzar();
}



#endif	//DICC_STRING_
