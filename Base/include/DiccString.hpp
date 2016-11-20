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
                for (int i = 0; i < 256; i++){
                    if (siguientes.Definido(i)){
                        Nodo* tmp = siguientes[i];
                        siguientes[i] = NULL;
                        delete tmp;
                        DiccString<S>::deletesNodos++;
                        std::cout << "DELETE: nodo en destructor\n";    
                    }
                }
                // definicion = NULL;
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

    std::cout << "\n\nNEWS:   " << DiccString<S>::newsNodos << " \n";
    std::cout << "\nDELETES:   " << DiccString<S>::deletesNodos << " \n";

    if(_raiz != NULL){
        Nodo* temp = _raiz;
        _raiz = NULL;
        delete temp;
    }
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
    std::cout << "Definiendo: " << clave << "\n";
    if (this->_raiz == NULL) {
        this->_raiz = new Nodo();
        DiccString<S>::newsNodos++;
        std::cout << "NEW: _raiz\n";
    }
 
    Nodo* nodoActual = this->_raiz;

    // En este for voy recorriendo los nodos correspondientes (o creandolos)
    // Hasta llegar al nodo qu contiene el ultimo caracter
    for (int i = 0; i < clave.size(); i++) {
        // Si donde debe ir el caracter el nodo no esta definido, creo uno
        if (!nodoActual->siguientes.Definido(int(clave[i]))) {
            Nodo* nuevo = new Nodo;
            DiccString<S>::newsNodos++;
            std::cout << "NEW: nodo caracter:  " << clave[i] << "\n";
            
            nodoActual->siguientes.Definir(int(clave[i]), nuevo);
            // _listaNodos.AgregarAtras(nuevo);
            // Nodo* tmp = nuevo;
            // delete nuevo;
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
    std::cout << "Termino definir: " << clave << "\n";
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
    std::cout << "\n\nPalabra a borrar: " << clave << "\n";
    
    bool borrarRaiz = (this->_claves.Cardinal() == 1);
    // @LEAK
    // Reserva deberia asignarle a null al final?
    Nodo* nodoReserva = this->_raiz; 
    // Nat rindex = int(clave[0]);
    Nat rindex = 0;

    // Notar que la raiz no puede ser null porque hay al menos una clave
    // Recorro toda la clave por los nodos viendo a partir de donde tengo un "camino recto" de nodos
    Nodo* nodoActual = this->_raiz;
    for (Nat i = 0; i < clave.size(); i++) {
        nodoActual = nodoActual->siguientes[int(clave[i])];
        bool definido = ((i != clave.size()-1) && (nodoActual->definicion != NULL));

        if (this->CuentaHijos(nodoActual) > 1 || definido) {
            std::cout << "Muevo la reserva: " << clave[i] << "\n";
            nodoReserva = nodoActual;
            rindex = i+1;
            // rindex = int(clave[i+1]);
            // std::cout << "Actualizo rindex\n";
        }
    }

    // nodoActual contiene el nodo al ultimo caracter
    // por invariante tiene una defincion
    if(!nodoActual->itClave.HaySiguiente()) {
        std::cout << "\nHAY UN PROBLEMA\n";
        std::cout << "\nEL NODO NO APUNTA A NINGUNA CLAVE\n";
    }
    
    // // @LEAK
    // // Elimino el significado
    // nodoActual->itClave.EliminarSiguiente();
    // S* tmp = nodoActual->definicion;
    // nodoActual->definicion = NULL;
    // delete tmp;

    // if (this->CuentaHijos(nodoActual) == 0) {

    std::cout << "---------\ncant:\n"; 
    std::cout << this->CuentaHijos(nodoActual) << "\n";
    std::cout << "---------\n"; 


    nodoActual->itClave.EliminarSiguiente();
    
    if (this->CuentaHijos(nodoActual) > 0) {
        // @LEAK
        // Elimino el significado
        S* tmp = nodoActual->definicion;
        nodoActual->definicion = NULL;
        delete tmp;

    } else {
    // if (this->CuentaHijos(nodoActual) == 0) {
        std::cout << "Entre al borrarDesde\n";
        this->BorrarDesde(nodoReserva, rindex, clave);

        if (nodoReserva->siguientes[int(clave[rindex])] != NULL) {
            std::cout << "TENEMOS UN PROBLEMA\n";
        }
        std::cout << "Sali del borrarDesde\n";

        std::cout << "---------\ncant de reserva:\n"; 
        std::cout << this->CuentaHijos(nodoReserva) << "\n";
        std::cout << "---------\n"; 

        // Nodo* tempor = nodoActual;
        // nodoActual = NULL;
        // delete tempor;
        // std::cout << "nodoActual: " << nodoActual << "\n";
    }

    // else if (this->CuentaHijos(nodoActual) == 0) {
    //     Nodo* tmp = nodoActual;
    //     nodoActual = NULL;
    //     delete tmp;
    //     DiccString<S>::deletesNodos++;
    //     std::cout << "DELETE: ultimoNodo\n";
    // }

    // @LEAK
    // if (this->_raiz->siguientes.Definido(int(clave[0]))) {
    //     std::cout << "PRIMERA LETRA QUEDO DEFINIDA\n";
    // }

    if (borrarRaiz && this->_raiz != NULL) {
        Nodo* tempe = this->_raiz;
        this->_raiz = NULL;
        delete tempe;
        DiccString<S>::deletesNodos++;
        std::cout << "DELETE: _raiz\n";
    }

    std::cout << "Salgo de borrar: " << clave << "\n";
}

template<class S>
Nat DiccString<S>::CuentaHijos(DiccString<S>::Nodo* padre) const{   
    if (padre == NULL) {
        return 0;
    }
    Nat cantHijos = 0;
    for (int i = 0; i < 256; i++) {
        if (padre->siguientes.Definido(i)) {
            std::cout << "Hijo: " << char(i) << "\n";
            cantHijos++;
        }
    }
    return cantHijos;
}

template<class S>
void DiccString<S>::BorrarDesde(DiccString<S>::Nodo* &desde, Nat rindex, const string &clave) {

    std::cout << "rindex: " << rindex << "\n";
    std::cout << "rindex: " << clave[rindex] << "\n";

    // Nodo* aBorrar[clave.size()];
    Vector<Nodo*> aBorrar; 

    // aBorrar.AgregarAtras(desde);

    // Agrego todos los que quiero borrar al array (la reserva no la borro)
    Nodo* nodoActual = desde;
    for (Nat i = rindex; i < clave.size(); i++) {
        // Nodo* anterior = nodoActual;
        // nodoActual = nodoActual->siguientes[int(clave[i])];
        // anterior->siguientes[int(clave[i])] = NULL;
        // std::cout << "Se intenta borrar caracter: " << clave[i] <<"\n";     
        // aBorrar.AgregarAtras(nodoActual);
        Nodo* tmp = nodoActual->siguientes[int(clave[i])];
        nodoActual->siguientes[int(clave[i])] = NULL;
        aBorrar.AgregarAtras(tmp);
        nodoActual = tmp;
        std::cout << "Se intenta borrar caracter: " << clave[i] <<"\n";     

    }

    // Borro el significado
//    cout << "BORRADO: " << nodoActual->definicion << " " << *(nodoActual->definicion) << "\n";

    // en teoria ya lo borre antes
    // T* valor = nodoActual->definicion;
    // nodoActual->definicion = NULL;
    // delete valor;

    // Borro el vector
    // for (Nat i = rindex; i < clave.size(); i++) {
    desde->siguientes[int(clave[rindex])] = NULL;
    for (Nat i = 0; i < aBorrar.Longitud(); i++) {
        Nodo* nodoABorrar = aBorrar[i];

        for (Nat j = 0; j < 256; j++) {
            if (nodoABorrar->siguientes.Definido(j)) {
                // std::cout << "RED FLAG\n";
                nodoABorrar->siguientes[j] = NULL;
            }
        }


        aBorrar[i] = NULL;
        delete nodoABorrar;
        // DiccString<S>::deletesNodos++;
        std::cout << "DELETE: caracter\n";     
    }




    // std::cout << "index: " << index << "\n";
    // std::cout << "caracter de index: " << char(index) << "\n";
    // std::cout << "nodoDesde: " << desde << "\n";    
    // Nodo* nodoActual = desde->siguientes[index];
    // // Nodo* nodoActual = desde;
    // Nodo* inicial = desde->siguientes[index];
    // std::cout << "nodoActual: " << nodoActual << "\n";    
    
    // // Nodo* inicial = desde->siguientes[index];
    // desde->siguientes[index] = NULL;

    // // @LEAK
    // // No estoy dejando el nodoActual "vivo"?
    // // Quiza despues hacer un delete desde->siguientes[index];

    // Vector<Nodo*> aBorrar;

    // bool sigue = true;
    
    // // while cuentahijos nodoActual == 0
    // while (nodoActual != NULL && sigue) {
    //     sigue = false;

    //     for (Nat i = 0; i < 256; i++) {
    //         // std::cout << "entro";
    //         if (nodoActual->siguientes.Definido(i)) {
    //             std::cout << "Toca borrar caracter:  " << char(i) << "\n";
                
    //             sigue = true;
    //             Nodo* tmp = nodoActual->siguientes[i];
    //             aBorrar.AgregarAtras(tmp);
    //             nodoActual->siguientes[i] = NULL;
    //             nodoActual = tmp;
    //             if (this->CuentaHijos(nodoActual) == 0) {
    //                 aBorrar.AgregarAtras(nodoActual);
    //                 sigue = false;
    //             }
    //             // delete tmp;
    //             break;
    //         }
    //     }
    // }

    // if (nodoActual != NULL && nodoActual != inicial) {
    //     // aBorrar.AgregarAtras(nodoActual);
    // }

    // // for (Nat i = 0; i < aBorrar.Longitud(); i++) {
    // for (Nat i = aBorrar.Longitud()-1; i >= 0; i--) {
    //     Nodo* tmp = aBorrar[i];
    //     aBorrar[i] = NULL;
    //     delete tmp;
    //     DiccString<S>::deletesNodos++;
    //     std::cout << "DELETE: en teoria un caracter pero no se\n";       
    // }
    // std::cout << "Sali de borrar los caracteres\n";

    // // desde->siguientes[index] = NULL;
    // delete inicial;
    // // DiccString<S>::deletesNodos++;

    // // std::cout << "Borre el inicial\n";
    
    // if (nodoActual != NULL) {
    //     delete nodoActual;
    //     // Se supone que cuando llego aca, nodoActual recorrio todo
    //     // delete inicial;
    // }
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
