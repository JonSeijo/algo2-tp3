/*
 * Diccionario implementado sobre trie cuyas claves son string,
 */

#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include <ostream>
#include <string>
#include "../aed2.h"

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

            Nodo() : definicion(NULL), siguientes(256),  itClave(){   }
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
 : _claves(), _raiz(NULL)
{}


template< class S>
DiccString<S>::~DiccString(){

    Conj<string>::Iterador it = _claves.CrearIt();

    // DiccString<S>::Iterador it;

    // while(this->_claves.Cardinal() != 0){

    for (int i = 0; i < this->_claves.Cardinal(); i++) {

        // std::cout << "\nSalgo del borrar estoy en destructor\n";
        if (it.HaySiguiente()) {
            std::cout << "\n\nclave actual:    " << it.Siguiente() << "\n\n";
            Borrar(it.Siguiente());
            // std::cout << "Hay siguiente?" << std::endl;
            //  COMO PUEDE SER QUE HAYSIGUENTE SI LA CANTIDAD DE CLAVES ES CERO??
            // std::cout << "cant claves: " << _claves.Cardinal() << std::endl;
            
            // it.Avanzar();
            
            // if (it.HaySiguiente()) {
            //     std::cout << "Hay siguiente 22222?" << std::endl;
            //     //  COMO PUEDE SER QUE HAYSIGUENTE SI LA CANTIDAD DE CLAVES ES CERO??
            //     std::cout << "2222cant claves: " << _claves.Cardinal() << std::endl;
            // }
        }

    }
    std::cout << "\nSalgo del while destructor" << std::endl;


    // if(_raiz != NULL){
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
}



template<class S>
void DiccString<S>::Definir(const string& clave, const S& significado){
    if (_claves.Cardinal() == 0 || _raiz == NULL) { 
    _raiz = new Nodo();
  }

  Nodo* nodoActual = _raiz;

  for (Nat i = 0; i < clave.size(); i++) {


    if (!nodoActual->siguientes.Definido(int(clave[i]))) {
        Nodo* nuevo = new Nodo();
        nodoActual->siguientes.Definir(int(clave[i]), nuevo);
    }

    nodoActual = nodoActual->siguientes[int(clave[i])];
  }

    if(nodoActual->definicion != NULL){

        S* valor = nodoActual->definicion;
        nodoActual->definicion = NULL;
        delete valor;

    } else {
    //Conj<string>::Iterador* it = new Conj<string>::Iterador();
    //*it = _claves.AgregarRapido(clave);
    nodoActual->itClave = _claves.AgregarRapido(clave);
  }

    nodoActual->definicion = new S(significado);


}


template<class S>
bool DiccString<S>::Definido(const string& clave) const{

  Nodo* nodoActual = _raiz;

  for (Nat i = 0; i < clave.size(); i++) {

    if (!nodoActual->siguientes.Definido(int(clave[i]))) {
      return false;
    }
 
    nodoActual = nodoActual->siguientes[int(clave[i])];
  }


  return nodoActual->definicion != NULL;
}

template< class S>
const S& DiccString<S>::Significado(const string& clave) const {

  Nodo* nodoActual = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {

        if (nodoActual->siguientes.Definido(int(clave[i]))) {
          nodoActual = nodoActual->siguientes[int(clave[i])];

        }

    }



  return *nodoActual->definicion;
}

template<class S>
S& DiccString<S>::Significado(const string& clave) {

  Nodo* nodoActual = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {

        if (nodoActual->siguientes.Definido(int(clave[i]))) {
          nodoActual = nodoActual->siguientes[int(clave[i])];

        }

    }



  return *nodoActual->definicion;

}

template<class S>
void DiccString<S>::Borrar(const string& clave){

    bool borrarRaiz = _claves.Cardinal() == 1;

    Nat rindex = 0;

    Nodo* nodoActual = _raiz;
    Nodo* reserva = _raiz;

    for (Nat i = 0; i < clave.size(); i++) {
        if (nodoActual->siguientes.Definido(int(clave[i]))) {
            nodoActual = nodoActual->siguientes[int(clave[i])];
        }
        bool definido = i != clave.size() - 1 &&
                      nodoActual->definicion != NULL;

        if (CuentaHijos(nodoActual) > 1 || definido) {
            reserva = nodoActual;
            rindex = i + 1;
        }
    }

    std::cout << "Salgo del primer for\n";


    // POSIBLE ERROR
    // EL ITERADOR SE ASIGNA AL ULTIMO VALOR DE LA PALABRA, ACA LO ESTARIA BORRANDO ANTES
    // if (nodoActual != NULL ) {
    
    //     // if (nodoActual->itClave != NULL) {

    //     if( nodoActual->itClave.HaySiguiente()) {
    //         std::cout << "\nHAY SIGUIENTE EN ITER\n";
    //         std::cout << "Cardinal:   " << this->_claves.Cardinal() << "\n";
    //         nodoActual->itClave.EliminarSiguiente();
    //         std::cout << "\nELIMINE SIGUIENTE EN ITER\n";
    //         std::cout << "Cardinal:   " << this->_claves.Cardinal() << "\n";
    //     }
    //     //}
    //     // delete (nodoActual->itClave);
    //     //nodoActual->itClave = NULL;
    // }

    Nat hijos = CuentaHijos(nodoActual);
    std::cout << "Salgo del cuenta hijos\n";

    if(hijos > 1){
        S* valor = nodoActual->definicion;
        nodoActual->definicion = NULL;
        delete valor;
    }
    else if (hijos == 0) {
        BorrarDesde(reserva, rindex);
        std::cout << "Sali del borrar desde";
    }
    else if (borrarRaiz) {
        // Esta mierda es para que no muera al borrar un diccString
        /*for (Nat i = 0; i < 256; i++) {
          _raiz->siguientes.Definir(i, new Nodo);
          
        }*/
        Nodo* t = _raiz;
        _raiz = NULL;
        delete t;
    }
    std::cout << "Salgo del borrar";
}

template<class S>
Nat DiccString<S>::CuentaHijos(DiccString<S>::Nodo* padre) const{
  Nat hijos = 0;
  for (Nat i = 0; i < 256; i++) {
    if(padre->siguientes.Definido(i)){
      hijos++;
    }

  }
  return hijos;
}

template<class S>
void DiccString<S>::BorrarDesde(DiccString<S>::Nodo* &inicial, Nat index) {
    std::cout << "\nEntro a BorrarDesde \n";
    Nodo* tempIni = inicial;
    Nodo* nodoActual = inicial;

    while (nodoActual != NULL) {
        Nat posHijo = -1;
        for (Nat i = 0; i < 256; i++) {
            if (nodoActual->siguientes.Definido(i)) {
                posHijo = i;
                break;
            }
        }

        std::cout << "Salgo del for\n";

        if (posHijo != -1) {
            Nodo* tmp = nodoActual;
            nodoActual = nodoActual->siguientes[posHijo];
            delete tmp;
        } else {
            // delete nodoActual;
                if (nodoActual != NULL ) {
    
                    // if (nodoActual->itClave != NULL) {

                    if( nodoActual->itClave.HaySiguiente()) {
                        std::cout << "\nHAY SIGUIENTE EN ITER\n";
                        std::cout << "Cardinal:   " << this->_claves.Cardinal() << "\n";
                        nodoActual->itClave.EliminarSiguiente();
                        std::cout << "\nELIMINE SIGUIENTE EN ITER\n";
                        std::cout << "Cardinal:   " << this->_claves.Cardinal() << "\n";
                    }
                    //}
                    // delete (nodoActual->itClave);
                    //nodoActual->itClave = NULL;
                }
            nodoActual = NULL;
        }
    }
    std::cout << "Salgo del while\n";

    // delete tempIni;
    std::cout << "Salgo de BorrarDesde \n";
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
