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

    Conj<string>::const_Iterador Claves() const; 

    /***************************************/
    /* Iterador de DiccString, modificable */
    /***************************************/
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

      DiccString<S>::Iterador& operator = (const DiccString<S>::Iterador& otro) {
        this->_dicc = otro._dicc;
        this->_itClave = otro._itClave;
        return *this;
      }

    private:


      DiccString<S>* _dicc;

      Conj<string>::Iterador _itClave;


    };

  private:

    struct Nodo {
      S* definicion;
      Arreglo< Nodo* > siguientes;
      Conj<string>::Iterador* itClave;

      Nodo() : definicion(NULL), siguientes(), itClave(NULL){

  		    siguientes = Arreglo<Nodo*>(256);

  		};
    };

    Conj<string> _claves;

    Nodo* _raiz;


    Nat CuentaHijos(Nodo* padre) const;
    void BorrarDesde(Nodo* &reserva, Nat rindex);;


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

		*(nodoActual->itClave) = _claves.AgregarRapido(clave);
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



  return *nodoActual->definicion;
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



  return *nodoActual->definicion;

}

template<class S>
void DiccString<S>::Borrar(const string& clave){
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  bool borrarRaiz = _claves.Cardinal() == 1;

  Nat rindex = 0;

  Nodo* nodoActual = _raiz;
  Nodo* reserva = _raiz;

  for (Nat i = 0; i < clave.size(); i++) {

    nodoActual = nodoActual->siguientes[int(clave[i])];
    bool definido = i != clave.size() - 1 &&
                  nodoActual->definicion != NULL;

    if (CuentaHijos(nodoActual) > 1 || definido) {
      reserva = nodoActual;
      rindex = i + 1;
    }

  }
  // No existe EliminarSiguiente
  //nodoActual->itClave->EliminarSiguiente();
  delete nodoActual->itClave;
  nodoActual->itClave = NULL;

  Nat hijos = CuentaHijos(nodoActual);

  if(hijos > 1){

		S* valor = nodoActual->definicion;
		nodoActual->definicion = NULL;
		delete valor;

	}

  if (hijos == 0) {
    BorrarDesde(reserva, rindex);
  }
  if (borrarRaiz) {
    delete _raiz;
    _raiz = NULL;
  }


}
template<class S>
Nat DiccString<S>::CuentaHijos(DiccString<S>::Nodo* padre) const{
  Nat hijos = 0;
  for (Nat i = 0; i < 256; i++) {
    if(padre->siguientes[i] != NULL){
      hijos++;
    }

  }
  return hijos;
}

template<class S>
void DiccString<S>::BorrarDesde(DiccString<S>::Nodo* &desde, Nat index) {

  desde = desde->siguientes[index];
  bool sigue = false;
  while (desde != NULL) {
    Nodo* temp = desde;
    for (Nat i = 0; i < 256; i++) {
      if(desde->siguientes[i] != NULL){
        desde = desde->siguientes[i];
        sigue = true;
      }
    }
    delete temp;
  }
  if(!sigue){
    delete desde;
  }

}
template<class S>
Nat DiccString<S>::CantClaves() const{
  return _claves.Cardinal();
}

template<class S>
Conj<string>::const_Iterador DiccString<S>::Claves() const{
  return _claves.CrearIt();
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
DiccString<S>::Iterador::~Iterador(){


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
