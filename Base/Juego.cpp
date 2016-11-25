#include "modulos.h"
#include <iostream>
#include <string>
#include "aed2.h"
#include "TiposJuego.h"


using namespace aed2;

Juego::Juego(const Mapa &map) : _cantPokemon(), _cantPokemonesTotales(0), _mapa(),
 _jugadores(), _jugadoresNoEliminados(), _grillaJugadores(), _pokenodos(), _posPokemons(){

    // *_mapa = map;
    this->_mapa = new Mapa(map);

    for (Nat i = 0; i < map.Tam(); i++) {
        Vector < Lista <Jugador> > inter;

        for (Nat j = 0; j < map.Tam(); j++) {
            Lista < Jugador > vacia;
            inter.AgregarAtras(vacia);
        }

        _grillaJugadores.AgregarAtras(inter);
    }

    for (Nat i = 0; i < map.Tam(); i++) {
        Vector<pokeStruc*> inter;

        for (Nat j = 0; j < map.Tam(); j++) {
            pokeStruc* nuevo = NULL;
            inter.AgregarAtras(nuevo);
        }

        _pokenodos.AgregarAtras(inter);
    }

}

Juego::~Juego(){

    for (Nat i = 0; i < _pokenodos.Longitud(); i++) {
        for (Nat j = 0; j < _pokenodos[i].Longitud(); j++) {
            delete _pokenodos[i][j];
        }

    }
    delete _mapa;

}

void Juego::AgregarPokemon(const Pokemon &p, const Coordenada &c){
    // Aumenta en uno la cantidad de pokemones en el juego.
    _cantPokemonesTotales++;

    // Se agregua el pokemon al conjunto.
    _posPokemons.AgregarRapido(c);


    // Se aumenta en uno la cantidad de la misma especie.
    if (_cantPokemon.Definido(p)) {
        Nat cant = _cantPokemon.Significado(p);
        _cantPokemon.Definir(p, cant + 1);
    } else {
        _cantPokemon.Definir(p, 1);
    }

    // Se crea el pokenodo.
    Nat x = c.latitud;
    Nat y = c.longitud;
    _pokenodos[x][y] = new pokeStruc(p);


    // Se agregan los jugadores, que podrian capturar, al pokenodo.
    Vector<Jugador> posibles = DameJugadoreseEnPokerango(c);
    Nat i = 0;
    while (i < posibles.Longitud()) {
        Nat cant = _jugadores[posibles[i] ]._cantCap;
        jugYCantCapt aInsertar(posibles[i], cant);
        _jugadores[posibles[i] ]._itAEntrenadores =
                                                _pokenodos[x][y]->_entrenadores.Encolar(aInsertar);

        i++;
    }


}

Nat Juego::AgregarJugador(){
    Nat proxId = this->_jugadores.Longitud();
    Coordenada pos = Coordenada(0, 0);
    // dicc de pokes se crea vacio en constructor
    // itEntrenadores no apunta a nada
    // iteradorAPos no apunta a nada

    Conj<Jugador>::Iterador iteradorAJuego = _jugadoresNoEliminados.AgregarRapido(proxId);
    
    jugStruc e(proxId, pos, iteradorAJuego);
    
    _jugadores.AgregarAtras(e);

    return proxId;
}

void Juego::Conectarse(Jugador e, const Coordenada &c){
    // Se conecta el jugador.
    _jugadores[e]._conectado = true;

    // Se lo ubica en la posicion correspondiente.
    Nat x = c.latitud;
    Nat y = c.longitud;

    _jugadores[e]._itAPos = _grillaJugadores[x][y].AgregarAtras(e);
    _jugadores[e]._pos = Coordenada(x, y);

    // Se verifica si el jugador entra en un pokenodo.
    if (HayPokemonCercano(c)) {
        if (_mapa->HayCamino(c, PosPokemonCercano(c))) {

            Nat latPok = PosPokemonCercano(c).latitud;
            Nat lonPok = PosPokemonCercano(c).longitud;

            // Se reinicia el contador.
            _pokenodos[latPok][lonPok]->_contador = 0;

            // Se encola el jugador en el pokenodo.
            jugYCantCapt t(e, _jugadores[e]._cantCap);
            _jugadores[e]._itAEntrenadores =
                        _pokenodos[latPok][lonPok]->_entrenadores.Encolar(t);

        }
    }


}

void Juego::Desconectarse(Jugador e){
    // Se desconecta al jugador.

    _jugadores[e]._conectado = false;

    _jugadores[e]._itAPos.EliminarSiguiente();

    Coordenada c(_jugadores[e]._pos);


     // Se verifica si el jugador estaba en un pokenodo.
    if (HayPokemonCercano(c)) {                

        if (_mapa->HayCamino(c, PosPokemonCercano(c))) {

        /*    Nat latPok = PosPokemonCercano(c).latitud;
            Nat lonPok = PosPokemonCercano(c).longitud;*/
            // Se lo elimina del pokenodo
            _jugadores[e]._itAEntrenadores.Borrar();
        }
    }


}

void Juego::Moverse(Jugador e, const Coordenada &c){
    // Si el movimiento no es valido...
    if (!MovValido(e, c)) {
        // Se sanciona al jugador.
        _jugadores[e]._sanciones++;

        // Si tiene 5 o mas sanciones...
        if (_jugadores[e]._sanciones >= 5) {

            // Se borra al jugador de la posicion y de los jugadores.
            _jugadores[e]._itAPos.EliminarSiguiente();
            _jugadores[e]._itAJuego.EliminarSiguiente();

            // Se eliminan sus pokemones.
            Conj<string>::const_Iterador it = _jugadores[e]._pokemons.Claves();
            while (it.HaySiguiente()) {
                string actual = it.Siguiente();

                Nat cant = _jugadores[e]._pokemons.Significado(actual);

                Nat n = _cantPokemon.Significado(actual);
                _cantPokemon.Definir(actual, n - cant);

                it.Avanzar();
            }
            _cantPokemonesTotales -= _jugadores[e]._cantCap;

            // Si esta en un pokenodo...
            // TODO: Falta ver si hay camino?
            if (HayPokemonCercano(_jugadores[e]._pos)) {
                if (_mapa->HayCamino(_jugadores[e]._pos, PosPokemonCercano(_jugadores[e]._pos))) {
                     // Se lo borra del pokenodo.
                    _jugadores[e]._itAEntrenadores.Borrar();
                }
            }


        }
        else{
            //NOTA MENTAL: FALTA LO DE SUMAR LOS CONTADORES
            //Nota mental: la niña sabe demasiado

            // Se lo saca de la posicion anterior.
            _jugadores[e]._itAPos.EliminarSiguiente();

            // Se lo agrega en la posicion nueva.
            _jugadores[e]._itAPos = _grillaJugadores[c.latitud][c.longitud].AgregarAtras(e);
        }
    }// Si el movimiento es valido..
    else{
        Coordenada posAntes(_jugadores[e]._pos);

        bool hayPokAntes = HayPokemonCercano(posAntes);
        bool hayPokDesp  = HayPokemonCercano(c);

        if (hayPokDesp) {
            if (!hayPokAntes) {
                CasoMov3(e, posAntes, c);
            } else if (PosPokemonCercano(posAntes) == PosPokemonCercano(c)) {
                CasoMov1(e, posAntes, c);

            } else {
                CasoMov5(e, posAntes, c);
            }
        } else if (hayPokAntes) {
            CasoMov2(e, posAntes, c);
        } else {
            CasoMov4(e, posAntes, c);
        }

    // Se lo saca de la posicion anterior.
    _jugadores[e]._itAPos.EliminarSiguiente();

    // Se lo agrega en la posicion nueva.
    _jugadores[e]._itAPos = _grillaJugadores[c.latitud][c.longitud].AgregarAtras(e);

    }
    _jugadores[e]._pos = c;

}

Mapa& Juego::mapa(){
    return *_mapa;
}

Conj<Jugador>::Iterador Juego::Jugadores(){
    return this->_jugadoresNoEliminados.CrearIt();
}

Nat Juego::Sanciones(Jugador e) const{
    return _jugadores[e]._sanciones;
}

Coordenada Juego::Posicion(Jugador e) const{
    return _jugadores[e]._pos;
}

DiccString<Nat>::Iterador Juego::Pokemons(Jugador e){
    return _cantPokemon.CrearIt();
}

bool Juego::EstaConectado(Jugador e) const{
    return _jugadores[e]._conectado;
}

Conj<Jugador> Juego::Expulsados() const{
    Conj<Jugador> expulsados;

    // Itero todos los jugadores.
    for (Nat i = 0; i < _jugadores.Longitud(); i++) {

        // Si tiene mas de 5 sanciones...
        if (_jugadores[i]._sanciones >= 5) {
            // Lo agrego al conjunto de expulsados.
            expulsados.AgregarRapido(_jugadores[i]._id);
        }
    }

    return expulsados;
}

const Conj<Coordenada>& Juego::PosConPokemons() const{
    return _posPokemons;
}

const Pokemon& Juego::PokemonEnPos(const Coordenada &c) const{
    Nat x = c.latitud;
    Nat y = c.longitud;
    return _pokenodos[x][y]->_poke;
}

Nat Juego::CantMovimientosParaCaptura(const Coordenada &c) const{
    return _pokenodos[c.latitud][c.longitud]->_contador;
}

bool Juego::HayPokemonCercano(const Coordenada &c) const{
    Nat x = c.latitud;
    Nat y = c.longitud;

    Nat m = _mapa->Tam();


    // Esto es para evitar problemas, podria quitarse peeeeero..
    if (x >= m || y >= m) {
        return false;
    }

    bool hayPokemon = false;

    // Hay un pokemon en (x, y).
    hayPokemon |= (_pokenodos[x][y] != NULL);

    // Hay un pokemon en ( x -1, y).
    hayPokemon |= ((x > 0) && (_pokenodos[x - 1][y] != NULL));

    // Hay un pokemon en ( x-1, y-1).
    hayPokemon |= ((x > 0 && y > 0) && (_pokenodos[x - 1][y-1] != NULL));

    // Hay un pokemon en (x-1, y+1).
    hayPokemon |= ((x > 0 && y + 1 < m) && (_pokenodos[x-1][y+1] != NULL));

    // Hay un pokemon en (x-2, y).
    hayPokemon |= ((x > 1) && (_pokenodos[x-2][y] != NULL));

    // Hay un pokemon en (x, y-1).
    hayPokemon |= ((y > 0) && (_pokenodos[x][y-1] != NULL));

    // Hay un pokemon en (x, y-2).
    hayPokemon |= ((y > 1) && (_pokenodos[x][y-2] != NULL));

    // Hay un pokemon en (x, y+1).
    hayPokemon |= ((y + 1 < m) && (_pokenodos[x][y+1] != NULL));

    // Hay un pokemon en (x, y+2).
    hayPokemon |= ((m > 1 && y+2 < m) && (_pokenodos[x][y+2] != NULL));

    // Hay un pokemon en (x+1, y).
    hayPokemon |= ((x + 1 < m) && (_pokenodos[x+1][y] != NULL));

    // Hay un pokemon en (x+1, y-1).
    hayPokemon |= ((x + 1 < m && y > 0) && (_pokenodos[x+1][y-1] != NULL));

    // Hay un pokemon en (x+1, y+1).
    hayPokemon |= ((y + 1 < m && x + 1 < m) && (_pokenodos[x+1][y+1] != NULL));

    // Hay un pokemon en (x+2, y).
    hayPokemon |= ((m > 1 && x + 2 < m) && (_pokenodos[x+2][y] != NULL));


    return hayPokemon;

}

Coordenada Juego::PosPokemonCercano(const Coordenada &c) const{
    Nat x = c.latitud;
    Nat y = c.longitud;

    Nat m = _mapa->Tam();

    Coordenada posConPoke;
    if (_pokenodos[x][y] != NULL) {
        posConPoke = Coordenada(x, y);
    }
    if (x > 0) {

        if ( _pokenodos[x-1][y] != NULL) {
            posConPoke = Coordenada(x-1, y);
        }

        if (y > 0 && (_pokenodos[x-1][y-1] != NULL)) {
            posConPoke = Coordenada(x-1, y-1);
        }

        if (y + 1 < m  && (_pokenodos[x-1][y+1] != NULL)) {
            posConPoke = Coordenada(x-1, y+1);
        }
        if (x > 1  && (_pokenodos[x-2][y] != NULL)) {
            posConPoke = Coordenada(x-2, y);
        }

    }

    if (y > 0) {
        if (_pokenodos[x][y-1] != NULL) {
            posConPoke = Coordenada(x, y-1);
        }
        // @BUG cambio < por >
        if (y > 1  && (_pokenodos[x][y-2] != NULL)) {
            posConPoke = Coordenada(x, y-2);
        }

    }

    if (y + 1 < m) {

        if (_pokenodos[x][y+1] != NULL) {
            posConPoke = Coordenada(x, y+1);
        }
        if (m > 1 && y + 2 < m  && (_pokenodos[x][y+2] != NULL)) {
            posConPoke = Coordenada(x, y+2);
        }

    }
    if (x + 1 < m) {
        if (_pokenodos[x+1][y] != NULL) {
            posConPoke = Coordenada(x+1, y);
        }

        if (y > 0 && (_pokenodos[x+1][y-1] != NULL)) {
            posConPoke = Coordenada(x+1, y-1);
        }

        if (y + 1 < m && (_pokenodos[x+1][y+1] != NULL)) {
            posConPoke = Coordenada(x+1, y+1);
        }

    }

    if (m > 1 && x + 2 < m  && (_pokenodos[x+2][y] != NULL)) {
        posConPoke = Coordenada(x+2, y);
    }

    return posConPoke;
}

bool Juego::PuedoAgregarPokemon(const Coordenada& c) const{
    // Si la posicion existe en el mapa.
    bool puedo = _mapa->PosExistente(c);

    // Y no hay un pokemon cerca.
    puedo &= !HayPokemonEnTerritorioRango5(c);

    return puedo;
}


Conj<Jugador> Juego::EntrenadoresPosibles(const Coordenada &c, const Conj<Jugador> &es) const{

    Conj< Jugador > posibles;
    Coordenada pokeCoor(PosPokemonCercano(c));
    Vector<Jugador> jugsEnNodo = DameJugadoreseEnPokerango(pokeCoor);

    // Itero sobre es.
    Conj<Jugador>::const_Iterador itPosibles = es.CrearIt();

    while (itPosibles.HaySiguiente()) {

        // Lo agrego si pertenece al nodo.
        for (Nat i = 0; i < jugsEnNodo.Longitud(); i++) {
            if (itPosibles.Siguiente() == jugsEnNodo[i]) {
                posibles.AgregarRapido(itPosibles.Siguiente());
            }
        }
        itPosibles.Avanzar();
    }

    return posibles;

}

Nat Juego::IndiceRareza(const Pokemon &p) const{
    Nat pokeCant = _cantPokemon.Significado(p);
    return 100 - (100 * pokeCant / _cantPokemonesTotales);
}

Nat Juego::CantPokemnsTotales() const{
    return this->_cantPokemonesTotales;
}

Nat Juego::CantMismaEspecie(const Pokemon &p) const{
    return _cantPokemon.Significado(p);
}


/*********************/
/*Funciones privadas */
/*********************/

Vector<Jugador> Juego::DameJugadoreseEnPokerango(const Coordenada& c) const{
    Vector<Jugador> jugsRadio;
    Nat x = c.latitud;
    Nat y = c.longitud;

    Nat m = _mapa->Tam();

    if (!_grillaJugadores[x][y].EsVacia()) {
        AgregarAtrasJugsQueEstanEnPos(jugsRadio,x, y);
    }
    if (x > 0) {

        if (!_grillaJugadores[x-1][y].EsVacia()) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x-1, y);
        }

        if (y > 0 && (!_grillaJugadores[x-1][y-1].EsVacia() && this -> _mapa -> HayCamino(Coordenada(x, y), Coordenada(x-1, y-1)))) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x-1, y-1);
        }

        if (y + 1 < m  && (!_grillaJugadores[x-1][y+1].EsVacia() && this -> _mapa -> HayCamino(Coordenada(x, y), Coordenada(x-1, y+1)))) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x-1, y+1);
        }
        if (x > 1  && (!_grillaJugadores[x-2][y].EsVacia() && this -> _mapa -> HayCamino(Coordenada(x, y), Coordenada(x-2, y)))) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x-2, y);
        }

    }

    if (y > 0) {
        if (!_grillaJugadores[x][y-1].EsVacia()) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x, y-1);
        }
        // @BUG cambio < por >
        if (y > 1  && (!_grillaJugadores[x][y-2].EsVacia() && this -> _mapa -> HayCamino(Coordenada(x, y), Coordenada(x, y-2)))) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x, y-2);
        }

    }

    if (y + 1 < m) {

        if (!_grillaJugadores[x][y+1].EsVacia()) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x, y+1);
        }
        if (m > 1 && y + 2 < m  && (!_grillaJugadores[x][y+2].EsVacia() && this -> _mapa -> HayCamino(Coordenada(x, y), Coordenada(x, y+2)))) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x, y+2);
        }

    }
    if (x + 1 < m) {
        if (!_grillaJugadores[x+1][y].EsVacia()) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x+1, y);
        }

        if (y > 0 && (!_grillaJugadores[x+1][y-1].EsVacia())) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x+1, y-1);
        }

        if (y + 1 < m && (!_grillaJugadores[x+1][y+1].EsVacia() && this -> _mapa -> HayCamino(Coordenada(x, y), Coordenada(x+1, y+1)))) {
            AgregarAtrasJugsQueEstanEnPos(jugsRadio,x+1, y+1);
        }

    }

    if (m > 1 && x + 2 < m  && (!_grillaJugadores[x+2][y].EsVacia() && this -> _mapa -> HayCamino(Coordenada(x, y), Coordenada(x+2, y)))) {
        AgregarAtrasJugsQueEstanEnPos(jugsRadio,x+2, y);
    }

    return jugsRadio;

}

void Juego::AgregarAtrasJugsQueEstanEnPos(Vector<Jugador> &jugs, Nat x, Nat y) const {
    Lista <Jugador>::const_Iterador it = _grillaJugadores[x][y].CrearIt();

    Coordenada c(x, y);
    // Itero sobre los jugadores en esa posicion.
    while (it.HaySiguiente()) {
        Nat e = it.Siguiente();

        // Si esta conectado y puede llegar al pokemon...
        if(EstaConectado(e) && _mapa->HayCamino(Posicion(e), c)){
            jugs.AgregarAtras(e);
        }
        it.Avanzar();
    }
}

void Juego::CasoMov1(Jugador e, const Coordenada& antes, const Coordenada& desp){

    // El pokenodo al que entro el jugador.
    Coordenada pokePos = PosPokemonCercano(desp);

    // Itero sobre los pokenodos
    Conj<Coordenada>::Iterador it = _posPokemons.CrearIt();

    while (it.HaySiguiente()) {

        Nat x = it.Siguiente().latitud;
        Nat y = it.Siguiente().longitud;

        // Si no es al que entro el jugador...
        if (it.Siguiente() != pokePos) {

            pokeStruc* pokeNodo = _pokenodos[x][y];
            // Aumento su contador.
            pokeNodo->_contador++;


            // Si el contador llego a 10...
            if (pokeNodo->_contador == 10) {
                // Agrego el pokemon al entrenador que captura.
                SumarUnoEnJug(pokeNodo->_poke, pokeNodo->_entrenadores.Proximo().id);

                // Borro el pokenodo.
                it.EliminarSiguiente();

                delete pokeNodo;
                _pokenodos[x][y] = NULL;
            }
        }

        it.Avanzar();
    }

}


void Juego::CasoMov2(Jugador e, const Coordenada& antes, const Coordenada& desp){
    // Lo borro de entrenadores.
    _jugadores[e]._itAEntrenadores.Borrar();

        // Itero sobre los pokenodos
    Conj<Coordenada>::Iterador it = _posPokemons.CrearIt();

    while (it.HaySiguiente()) {

        Nat x = it.Siguiente().latitud;
        Nat y = it.Siguiente().longitud;

        pokeStruc* pokeNodo = _pokenodos[x][y];

        // Aumento su contador.
        pokeNodo->_contador++;

        // Si el contador llego a 10...
        if (pokeNodo->_contador == 10) {
            // Agrego el pokemon al entrenador que captura.
            SumarUnoEnJug(pokeNodo->_poke, pokeNodo->_entrenadores.Proximo().id);

            // Borro el pokenodo.
            it.EliminarSiguiente();

            delete pokeNodo;
            _pokenodos[x][y] = NULL;
        }


        it.Avanzar();
    }
}

void Juego::CasoMov3(Jugador e, const Coordenada& antes, const Coordenada& desp){
    // El pokenodo al que entro el jugador.
    Coordenada pokePos = PosPokemonCercano(desp);

    Nat lat = pokePos.latitud;
    Nat lon = pokePos.longitud;

    // Agrego el entrenador al pokenodo.
    jugYCantCapt jug(e, _jugadores[e]._cantCap);
    _jugadores[e]._itAEntrenadores = _pokenodos[lat][lon]->_entrenadores.Encolar(jug);


    // Itero sobre los pokenodos
    Conj<Coordenada>::Iterador it = _posPokemons.CrearIt();

    while (it.HaySiguiente()) {

        Nat x = it.Siguiente().latitud;
        Nat y = it.Siguiente().longitud;

        pokeStruc* pokeNodo = _pokenodos[x][y];

        // Si no es al que entro el jugador...
        if (it.Siguiente() == pokePos) {

            // Aumento su contador.
            pokeNodo->_contador = 0;


        } else if (pokeNodo->_contador == 10) {
                // Si el contador llego a 10...

                // Agrego el pokemon al entrenador que captura.
                SumarUnoEnJug(pokeNodo->_poke, pokeNodo->_entrenadores.Proximo().id);

                // Borro el pokenodo.
                it.EliminarSiguiente();

                delete pokeNodo;
                _pokenodos[x][y] = NULL;
        }


        it.Avanzar();
    }
}

void Juego::CasoMov4(Jugador e, const Coordenada& antes, const Coordenada& desp){

    // Itero sobre los pokenodos
    Conj<Coordenada>::Iterador it = _posPokemons.CrearIt();

    while (it.HaySiguiente()) {

        Nat x = it.Siguiente().latitud;
        Nat y = it.Siguiente().longitud;

        pokeStruc* pokeNodo = _pokenodos[x][y];

        // Aumento el contador del pokenodo.
        pokeNodo->_contador++;

        // Si no es al que entro el jugador...
        if (pokeNodo->_contador == 10 && !pokeNodo->_entrenadores.EsVacia()) {
                // Si el contador llego a 10...

                // Agrego el pokemon al entrenador que captura.
                SumarUnoEnJug(pokeNodo->_poke, pokeNodo->_entrenadores.Proximo().id);

                // Borro el pokenodo.
                it.EliminarSiguiente();

                delete pokeNodo;
                _pokenodos[x][y] = NULL;
        }


        it.Avanzar();
    }
}

void Juego::CasoMov5(Jugador e, const Coordenada& antes, const Coordenada& desp){
    // El pokenodo al que entro el jugador.
    Coordenada pokePos = PosPokemonCercano(desp);

    Nat lat = pokePos.latitud;
    Nat lon = pokePos.longitud;

    //Borro al jugador del heap anterior
    _jugadores[e]._itAEntrenadores.Borrar();

    // Agrego el entrenador al pokenodo.
    jugYCantCapt jug(e, _jugadores[e]._cantCap);
    _jugadores[e]._itAEntrenadores = _pokenodos[lat][lon]->_entrenadores.Encolar(jug);


    // Itero sobre los pokenodos
    Conj<Coordenada>::Iterador it = _posPokemons.CrearIt();

    while (it.HaySiguiente()) {

        Nat x = it.Siguiente().latitud;
        Nat y = it.Siguiente().longitud;

        pokeStruc* pokeNodo = _pokenodos[x][y];


        // Si no es al que entro el jugador...
        if (it.Siguiente() == pokePos) {

            // Aumento su contador.
            pokeNodo->_contador = 0;


        } else {
            // Si no es al que entro el jugador...

            // Aumento el contador del pokenodo.
            pokeNodo->_contador++;

            if (pokeNodo->_contador == 10) {
            // Si el contador llego a 10...

            // Agrego el pokemon al entrenador que captura.
            SumarUnoEnJug(pokeNodo->_poke, pokeNodo->_entrenadores.Proximo().id);

            // Borro el pokenodo.
            it.EliminarSiguiente();

            delete pokeNodo;
            _pokenodos[x][y] = NULL;
        }

    }


        it.Avanzar();
    }

}

bool Juego::MovValido(Jugador e, const Coordenada& c) const{
    bool camino = _mapa->HayCamino(c, _jugadores[e]._pos);
    bool distancia = distEuclidea(c, _jugadores[e]._pos) <= 100;

    // Hay camino y esta a menos de 100 de dsitancia.
    return camino && distancia;

}


void Juego::SumarUnoEnJug(Pokemon p, Jugador e){
    // Si ya tiene alguna de la misma especie...
    if (_jugadores[e]._pokemons.Definido(p)) {
        // Le sumo uno.
        Nat actual = _jugadores[e]._pokemons.Significado(p);
        _jugadores[e]._pokemons.Definir(p, actual + 1);
    } else {
        // Si no lo defino en 1.
        _jugadores[e]._pokemons.Definir(p, 1);
    }
}

bool Juego::HayPokemonEnTerritorioRango5(const Coordenada &c) const{
    Nat x = c.latitud;
    Nat y = c.longitud;

    //En teoría PosExistente se fija si se pasa del tamaño del mapa.
    if(x < 5){
        if(y < 5){
            //std::cout << "Entre al caso 1" << std::endl;
            for(Nat i = 0; i <= x + 4; i++){
                for(Nat j = 0; j <= y + 4; j++){
                    if(this -> _mapa -> PosExistente(Coordenada(i, j))){
                        if(this -> _pokenodos[i][j] != NULL && distEuclidea(Coordenada(x, y), Coordenada(i, j)) < 25){
                            return true;
                        }
                    }
                }
            }
        }
        else{
            //std::cout << "Entre al caso 2" << std::endl;
            for(Nat i = 0; i <= x + 4; i++){
                for(Nat j = y - 4; j <= y + 4; j++){
                    if(this -> _mapa -> PosExistente(Coordenada(i, j))){
                        if(this -> _pokenodos[i][j] != NULL && distEuclidea(Coordenada(x, y), Coordenada(i, j)) < 25){
                            return true;
                        }
                    }
                }
            }
        }
    }
    else{
        if(y < 5){
            //std::cout << "Entre al caso 3" << std::endl;
            for(Nat i = x - 4; i <= x + 4; i++){
                for(Nat j = 0; j <= y + 4; j++){
                    if(this -> _mapa -> PosExistente(Coordenada(i, j))){
                        if(this -> _pokenodos[i][j] != NULL && distEuclidea(Coordenada(x, y), Coordenada(i, j)) < 25){
                            return true;
                        }
                    }
                }
            }
        }
        else{
            //std::cout << "Entre al caso 4" << std::endl;
            for(Nat i = x - 4; i <= x + 4; i++){
                for(Nat j = y - 4; j <= y + 4; j++){
                    if(this -> _mapa -> PosExistente(Coordenada(i, j))){
                        if(this -> _pokenodos[i][j] != NULL && distEuclidea(Coordenada(x, y), Coordenada(i, j)) < 25){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}