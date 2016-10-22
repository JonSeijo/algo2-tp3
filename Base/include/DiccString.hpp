/*
 * Diccionario implementado sobre trie cuyas claves son string,
 *
 * Created on HOY VIEJA....
 */

#ifndef DICC_STRING_H_
#define	DICC_STRING_H_

#include <ostream>
#include <string.h>
#include "../aed2/Conj.h"


template<class S>
class DiccString{
  public:

    class Iterador;

    DiccString();

    //no esta en el modulo.
    DiccString(const DiccString<S>& otro);

    void Definir(const string& clave, const S& significado);

    bool Definido(const string& clave) const;

    //Creo que siempre se devuelve como referencia modificable
    const S& Significado(const string& clave) const;

    S& Significado(const string& clave);

    void Borrar(const string& clave);

    Nat CantClaves() const;

  private:

    Conj<string> _claves;

    Nodo* _raiz;

};

template<class K, class S>
std::ostream& operator << (std::ostream &os, const Dicc<K,S>& d);

// Implementacion Dicc

template<class K, class S>
DiccString<S>::DiccString()
 : _claves(), _raiz(NULL)
{}


//Constructor por copia.
template<class S>
DiccString<S>::DiccString(const DiccString<S>& otro){
  //TODO:	No esta en el modulo.
}



template<class K, class S>
void DiccString<S>::Definir(const string& clave, const S& significado){
  assert(false);
  //TODO:
}


template<class S>
bool DiccString<S>::Definido(const string& clave) const{
  return Buscar(clave).HaySiguiente();
}

template< class S>
const S& DiccString<S>::Significado(const string& clave) const {
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  return Buscar(clave).SiguienteSignificado();
}

template<class S>
S& DiccString<S>::Significado(const stirng& clave)
{
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  return Buscar(clave).SiguienteSignificado();
}

template<class K, class S>
void DiccString<S>::Borrar(const string& clave){
  #ifdef DEBUG
  assert( Definido(clave) );
  #endif

  Buscar(clave).EliminarSiguiente();
}

template<class S>
Nat DiccString<S>::CantClaves() const{
  return _claves.Longitud();
}


template< class S>
std::ostream& operator << (std::ostream& os, const DiccString<S>& d){
  return Mostrar(os, d, '{', '}');
}




#endif	//DICC_STRING_
