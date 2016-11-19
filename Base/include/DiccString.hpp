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
            void BorrarActual();
     
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
            Arreglo<Nodo*> siguientes;
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
    if (this->_raiz == NULL) {
        this->_raiz = new Nodo();
    }
 
    Nodo* nodoActual = this->_raiz;

    // En este for voy recorriendo los nodos correspondientes (o creandolos)
    // Hasta llegar al nodo qu contiene el ultimo caracter
    for (int i = 0; i < clave.size(); i++) {
        // Si donde debe ir el caracter el nodo no esta definido, creo uno
        if (!nodoActual->siguientes.Definido(int(clave[i]))) {
            Nodo* nuevo = new Nodo();
            nodoActual->siguientes.Definir(int(clave[i]), nuevo);
        }

        // Avanzo el nodo actual hasta donde corresponda
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }

    // Si ya existia otra definicion, la elimino
    if (nodoActual->definicion != NULL) {
        S* tmp = nodoActual->definicion;
        nodoActual->definicion = NULL;
        delete tmp;
    } else {
        // Agrego la clave a mi conjunto de claves,
        // Me guardo un iterador a la clave en el conjunto

        // @LEAK 
        // Tengo que ver si este iterador se mantiene en cuando modifico el conjunto
        // Porque de ultima, en vez de un conjunto podria usar una lista y chau, PENSAR
        nodoActual->itClave = this->_claves.AgregarRapido(clave);
    }
    
    // Guardo un puntero con la nueva definicion
    nodoActual->definicion = new S(significado);
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
        if (! (nodoActual->siguientes.Definido(int(clave[i])))) {
            return false;
        }
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }

    return nodoActual->definicion != NULL;
}

template< class S>
const S& DiccString<S>::Significado(const string& clave) const {
    Nodo* nodoActual = this->_raiz;
    // Recorro la clave siguiendo el camino de nodos
    for (Nat i = 0; i < clave.size(); i++) {
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }
    return *(nodoActual->definicion);
}

template<class S>
S& DiccString<S>::Significado(const string& clave) {
    Nodo* nodoActual = this->_raiz;
    // Recorro la clave siguiendo el camino de nodos
    for (Nat i = 0; i < clave.size(); i++) {
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }
    return *(nodoActual->definicion);
}

template<class S>
void DiccString<S>::Borrar(const string& clave){
    ASSERT(false);
}

template<class S>
Nat DiccString<S>::CuentaHijos(DiccString<S>::Nodo* padre) const{   
    if (padre == NULL) {
        return 0;
    }
    Nat cantHijos = 0;
    for (int i = 0; i < 256; i++) {
        if (padre->siguientes.Definido(i)) {
            cantHijos++;
        }
    }
    return cantHijos;
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

// @LEAK
// Nueva para probar en el destructor
template <class S>
void DiccString<S>::Iterador::BorrarActual(){
    string clave = _itClave.Siguiente();
    this->Borrar(clave);
    if (_itClave.HaySiguiente()) {
        _itClave.Avanzar();
    }
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
