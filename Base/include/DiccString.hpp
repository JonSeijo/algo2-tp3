/*
 * Diccionario implementado sobre trie cuyas claves son string,
 */

#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include <ostream>
#include <string>
#include "../aed2.h"
#include "./../mini_test.h"

using namespace aed2;
using namespace std;

template<class S>
class DiccString{
  public:
    class Iterador;
    struct par;

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
    Iterador CrearIt();
    Conj<string>::const_Iterador Claves() const; 
    struct par {
        S dato;
        string clave;
        par(const S &d, const string &c) : dato(d), clave(c){}
    };
    /***************************************/
    /* Iterador de DiccString, modificable */
    /***************************************/
    class Iterador{
        public:
            Iterador();
            Iterador(DiccString<S> &d);
            ~Iterador();

            bool HayMas() const;
            par Actual() const;
            void Avanzar();
     
            DiccString<S>::Iterador& operator = (const DiccString<S>::Iterador& otro) {
                this->_dicc = otro._dicc;
                this->_itClave(otro._itClave);
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
            Conj<string>::Iterador itClave;

            Nodo() : definicion(NULL), siguientes(256),  itClave(){}
            // Revisar destructor de nodo
            ~Nodo() {
                delete definicion;
            }
        };

        Conj<string> _claves;
        Nodo* _raiz;
        Nat CuentaHijos(Nodo* padre) const;
        void BorrarDesde(Nodo* &reserva, Nat rindex);;
};

// Implementacion Dicc
template< class S>
DiccString<S>::DiccString()
 : _claves(), _raiz(NULL) {}


template< class S>
DiccString<S>::~DiccString(){
    // ASSERT(false);
    std::cout << "\n!!!Falta hacer el destructor de dicc!!!\n";
}

//Constructor por copia.
template<class S>
typename DiccString<S>::Iterador DiccString<S>::CrearIt(){
    return Iterador(*this);
}

//Constructor por copia.
template<class S>
DiccString<S>::DiccString(const DiccString<S>& otro){
    //TODO:   No esta en el modulo.
    //  Habria que borrar todo e ir definiendo las claves del otro dicc
}


template<class S>
void DiccString<S>::Definir(const string& clave, const S& significado){
    ASSERT(false);
}


template<class S>
bool DiccString<S>::Definido(const string& clave) const{
    Nat i = 0;
    bool pertenece = true;
    
    if (this->_raiz == NULL) {
        return false;
    }

    Nodo* nodoActual = this->_raiz;

    // Recorro la clave siguiendo el camino de nodos
    for (Nat i = 0; i < clave.size(); i++) {
        if (nodoActual->siguientes[int(clave[i])] == NULL) {
            return false;
        }
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }

    return nodoActual->definicion != NULL;
}

template< class S>
const S& DiccString<S>::Significado(const string& clave) const {
    ASSERT(false);
}

template<class S>
S& DiccString<S>::Significado(const string& clave) {
    ASSERT(false);
}

template<class S>
void DiccString<S>::Borrar(const string& clave){
    ASSERT(false);
}

template<class S>
Nat DiccString<S>::CuentaHijos(DiccString<S>::Nodo* padre) const{
    ASSERT(false);
}

template<class S>
void DiccString<S>::BorrarDesde(DiccString<S>::Nodo* &inicial, Nat index) {
    ASSERT(false);
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
DiccString<S>::Iterador::Iterador(DiccString<S> &d) : _itClave(d._claves.CrearIt()){
    *_dicc = d;
    ASSERT(false);
}

template <class S>
DiccString<S>::Iterador::~Iterador(){
    // delete _itClave;
}

template <class S>
bool DiccString<S>::Iterador::HayMas() const{
  return _itClave.HaySiguiente();
}

template <class S>
typename DiccString<S>::par DiccString<S>::Iterador::Actual() const{

    string clave = _itClave.Siguiente();
    S def(_dicc->Significado(clave));
    DiccString<S>::par res(def, clave);

    return res;
}

template <class S>
void DiccString<S>::Iterador::Avanzar(){
    _itClave.Avanzar();
}


#endif  //DICC_STRING_
