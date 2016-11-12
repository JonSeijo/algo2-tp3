#include "modulos.h"
#include <cassert>
#include <iostream>
#include "aed2.h"
#include "TiposJuego.h"


using namespace aed2;

Juego::Juego(const Mapa &map) : _cantPokemon(), _cantPokemonesTotales(0), _mapa(NULL),
 _jugadores(), _jugadoresNoEliminados(), _grillaJugadores(), _pokenodos(), _posPokemons(){

  *_mapa = map; 

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
    for (Nat j = 0; _pokenodos[i].Longitud(); j++) {
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

  Coordenada c = Coordenada(0, 0);
  jugStruc e(proxId, c);

  _jugadoresNoEliminados.AgregarRapido(e);

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

  _jugadores[e]._pos.latitud  = x;
  _jugadores[e]._pos.longitud = y;


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
      
      Nat latPok = PosPokemonCercano(c).latitud;
      Nat lonPok = PosPokemonCercano(c).longitud;


      // Se lo elimina del pokenodo
      _jugadores[e]._itAEntrenadores.Borrar();

    }
  }


}

void Juego::Moverse(Jugador e, const Coordenada &c){
  assert(false);
}

Mapa& Juego::mapa(){
  assert(false);
}

Conj<Jugador>::Iterador Juego::Jugadores(){
  assert(false);
}

Nat Juego::Sanciones(Jugador e) const{
  assert(false);
}

Coordenada Juego::Posicion(Jugador e) const{
  assert(false);
}

DiccString<Pokemon>::Iterador Juego::Pokemons(Jugador e){
  assert(false);
}

const Conj<Jugador>& Juego::Expulsados() const{
  assert(false);
}

const Conj<Coordenada>& Juego::PosConPokemons() const{
  assert(false);
}

const Pokemon& Juego::PokemonEnPos(const Coordenada &c) const{
  assert(false);
}

Nat Juego::CantMovimientosParaCaptura(const Coordenada &c) const{
  assert(false);
}

bool Juego::HayPokemonCercano(const Coordenada &c) const{
  assert(false);
}

const Coordenada& Juego::PosPokemonCercano(const Coordenada &c) const{
  assert(false);
}

const Conj<Jugador>& Juego::EntrenadoresPosibles(const Coordenada &c, const Conj<Jugador> &es) const{
  assert(false);
}

Nat Juego::IndiceRareza(const Pokemon &p) const{
  assert(false);
}

Nat Juego::CantPokemnsTotales() const{
  assert(false);
}

Nat Juego::CantMismaEspecie(const Pokemon &p) const{
  assert(false);
}


/*********************/
/*Funciones privadas */
/*********************/

Vector<Jugador> Juego::DameJugadoreseEnPokerango(const Coordenada& otro) const{
  assert(false);
}
