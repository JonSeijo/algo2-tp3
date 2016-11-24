/*
 * Diccionario implementado sobre trie cuyas claves son string,
 */

#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include <ostream>
#include <string>
#include "../aed2.h"
#include "../aed2.h"
// #include "./../mini_test.h"
// #include "./../TiposJuego.h"


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

    // @LEAK
    // PARA DEBUG

    static Nat newsNodos;
    static Nat deletesNodos;


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
            Arreglo<Nodo*> siguientes;
            Conj<string>::Iterador itClave;

            Nodo() : definicion(NULL), siguientes(256),  itClave(){}
            // Revisar destructor de nodo
            ~Nodo() {
                delete definicion;
                for (int i = 0; i < 256; i++){
                    if (siguientes.Definido(i)){
                        Nodo* tmp = siguientes[i];
                        siguientes[i] = NULL;
                        delete tmp;
                        DiccString<S>::deletesNodos++;
                        // std::cout << "DELETE: nodo en destructor\n";
                    }
                }
            }
        };

        Conj<string> _claves;
        Nodo* _raiz;

        Lista<Nodo*> _listaNodos;

        Nat CuentaHijos(Nodo* padre) const;
        void BorrarDesde(Nodo* &reserva, Nat rindex, const string &clave);;
};

// @LEAK
template< class S>
Nat DiccString<S>::newsNodos = 0;
template< class S>
Nat DiccString<S>::deletesNodos = 0;


// Implementacion Dicc
template< class S>
DiccString<S>::DiccString()
 : _claves(), _raiz(NULL) {
    DiccString<S>::newsNodos = 0;
    DiccString<S>::deletesNodos = 0;
}

template< class S>
DiccString<S>::~DiccString(){

    Conj<string>::Iterador it = _claves.CrearIt();
    Vector<string> vectorClaves;

    // Workaround para dejar de romper iteradores
    while (it.HaySiguiente()) {
        vectorClaves.AgregarAtras(it.Siguiente());
        it.Avanzar();
    }

    for (Nat i = 0; i < vectorClaves.Longitud(); i++) {
        this->Borrar(vectorClaves[i]);
    }

    // std::cout << "\n\nNEWS:   " << DiccString<S>::newsNodos << " \n";
    // std::cout << "\nDELETES:   " << DiccString<S>::deletesNodos << " \n";

    // if(_raiz != NULL){
    //     std::cout << "DELETE: _raiz desde destructor\n";
    //     Nodo* temp = _raiz;
    //     _raiz = NULL;
    //     delete temp;
    // }
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
    //std::cout << "\nDefiniendo: " << clave << "\n";
    if (this->_raiz == NULL) {
        this->_raiz = new Nodo();
        DiccString<S>::newsNodos++;
    }

    Nodo* nodoActual = this->_raiz;

    // En este for voy recorriendo los nodos correspondientes (o creandolos)
    // Hasta llegar al nodo qu contiene el ultimo caracter
    for (int i = 0; i < clave.size(); i++) {
        // Si donde debe ir el caracter el nodo no esta definido, creo uno
        if (!nodoActual->siguientes.Definido(int(clave[i]))) {
            Nodo* nuevo = new Nodo;
            DiccString<S>::newsNodos++;
            // std::cout << "NEW: nodo caracter:  " << clave[i] << "\n";
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
        nodoActual->itClave = this->_claves.AgregarRapido(clave);
    }

    // Guardo un puntero con la nueva definicion
    nodoActual->definicion = new S(significado);
   // std::cout << "Termino definir: " << clave << "\n";
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
    //std::cout << "Palabra a borrar: " << clave << "\n";

    bool borrarRaiz = (this->_claves.Cardinal() == 1);
    Nodo* nodoReserva = this->_raiz;
    Nat rindex = 0;

    // Notar que la raiz no puede ser null porque hay al menos una clave
    // Recorro toda la clave por los nodos viendo a partir de donde tengo un "camino recto" de nodos
    Nodo* nodoActual = this->_raiz;
    for (Nat i = 0; i < clave.size(); i++) {
        nodoActual = nodoActual->siguientes[int(clave[i])];
        bool definido = ((i != clave.size()-1) && (nodoActual->definicion != NULL));

        if (this->CuentaHijos(nodoActual) > 1 || definido) {
            nodoReserva = nodoActual;
            rindex = i+1;
        }
    }

    // nodoActual contiene el nodo al ultimo caracter
    // por invariante tiene una defincion
   /* if(!nodoActual->itClave.HaySiguiente()) {
        std::cout << "\nHAY UN PROBLEMA\n";
        std::cout << "\nEL NODO NO APUNTA A NINGUNA CLAVE\n";
    }*/

    nodoActual->itClave.EliminarSiguiente();

    if (this->CuentaHijos(nodoActual) > 0) {
        S* tmp = nodoActual->definicion;
        nodoActual->definicion = NULL;
        delete tmp;

    } else {
        this->BorrarDesde(nodoReserva, rindex, clave);
        if (nodoReserva->siguientes[int(clave[rindex])] != NULL) {
            //std::cout << "TENEMOS UN PROBLEMA\n";
        }
    }

    if (borrarRaiz && this->_raiz != NULL) {
        Nodo* tempe = this->_raiz;
        this->_raiz = NULL;
        delete tempe;
        DiccString<S>::deletesNodos++;
        // std::cout << "DELETE: _raiz   desde Borrar\n";
    }

   // std::cout << "Salgo de borrar: " << clave << "\n";
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
void DiccString<S>::BorrarDesde(DiccString<S>::Nodo* &desde, Nat rindex, const string &clave) {

    Vector<Nodo*> aBorrar;

    // Agrego todos los que quiero borrar al vector la reserva no la borro)
    // En peor caso agrego al vector tantos nodos como caracteres:   O(|clave|)
    Nodo* nodoActual = desde;
    for (Nat i = rindex; i < clave.size(); i++) {
        Nodo* tmp = nodoActual->siguientes[int(clave[i])];
        nodoActual->siguientes[int(clave[i])] = NULL;
        aBorrar.AgregarAtras(tmp);
        nodoActual = tmp;
        // std::cout << "Se intenta borrar caracter: " << clave[i] <<"\n";
    }

    // Borro el vector
    desde->siguientes[int(clave[rindex])] = NULL;

    // En peor caso recorro todas los caracteres : O(|clave|)
    for (Nat i = 0; i < aBorrar.Longitud(); i++) {
        Nodo* nodoABorrar = aBorrar[i];

        // O(1), aunque no estoy 100% seguro que sea necesario, podria encargarse el destructor
        for (Nat j = 0; j < 256; j++) {
            if (nodoABorrar->siguientes.Definido(j)) {
                nodoABorrar->siguientes[j] = NULL;
            }
        }
        aBorrar[i] = NULL;
        delete nodoABorrar;
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
DiccString<S>::Iterador::Iterador(DiccString<S> &d) : _itClave(d._claves.CrearIt()){
    *_dicc = d;
    // ASSERT(false);
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
