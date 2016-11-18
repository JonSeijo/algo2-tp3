#include <iostream>

#include "Driver.h"
using namespace aed2;

// Instanciar un mapa y un juego
Driver::Driver(const Conj< Coordenada > & cs) : _juego(NULL){

  Mapa map;

  Conj< Coordenada >::const_Iterador it = cs.CrearIt();

  while (it.HaySiguiente()) {

    map.AgregarCoord(it.Siguiente());

    it.Avanzar();
  }

  // ESTO PROVOCA SEG FAULT !!!
  this->_juego = new Juego(map);
}

Driver::~Driver(){
	delete _juego;
}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c){
	_juego->AgregarPokemon(p, c);
}


Jugador Driver::agregarJugador(){
  return _juego->AgregarJugador();
}


void Driver::conectarse(const Jugador & j, const Coordenada & c){
  _juego->Conectarse(j, c);
}


void Driver::desconectarse(const Jugador & j){
  _juego->Desconectarse(j);
}


void Driver::moverse(const Jugador & j, const Coordenada & c){
  _juego->Moverse(j, c);
}


Conj< Coordenada > Driver::mapa() const{
  return _juego->mapa().Coordenadas();
}


bool Driver::hayCamino(const Coordenada & c1, const Coordenada & c2) const{
  return _juego->mapa().HayCamino(c1, c2);
}


bool Driver::posExistente(const Coordenada & c) const{
	return _juego->mapa().PosExistente(c);
}


Conj< Jugador > Driver::jugadores() const{
  Conj< Jugador > jugadores;
  Conj< Jugador >::Iterador  it;
  for ( it = _juego->Jugadores(); it.HaySiguiente(); it.Avanzar() ) {
      jugadores.AgregarRapido(it.Siguiente());
  }

  return jugadores;
}


bool Driver::estaConectado(const Jugador & j) const{
  return _juego->EstaConectado(j);
}


Nat Driver::sanciones(const Jugador & j) const{
  return _juego->Sanciones(j);
}


Coordenada Driver::posicion(const Jugador & j) const{
  return _juego->Posicion(j);
}


Dicc< Pokemon , Nat > Driver::pokemons(const Jugador & j) const{
  Dicc< Pokemon , Nat > d;

  DiccString<Nat>::Iterador it = _juego->Pokemons(j);

  while (it.HayMas()) {

    d.DefinirRapido(it.Actual().clave, it.Actual().dato);

    it.Avanzar();

  }

  return d;
}


Conj< Jugador > Driver::expulsados() const{
  return _juego->Expulsados();
}


Conj< Coordenada > Driver::posConPokemons() const{
  return _juego->PosConPokemons();
}


Pokemon Driver::pokemonEnPos(const Coordenada & c) const{
  return _juego->PokemonEnPos(c);
}


Nat Driver::cantMovimientosParaCaptura(const Coordenada & c) const{
  return _juego->CantMovimientosParaCaptura(c);
}


bool Driver::puedoAgregarPokemon(const Coordenada & c) const{
  return _juego->PuedoAgregarPokemon(c);
}


bool Driver::hayPokemonCercano(const Coordenada & c) const{
  return _juego->HayPokemonCercano(c);
}


Coordenada Driver::posPokemonCercano(const Coordenada & c) const{
  return _juego->PosPokemonCercano(c);
}


Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada & c) const{
  return _juego->EntrenadoresPosibles(c, jugadores());
}


Nat Driver::indiceRareza(const Pokemon& p) const{
  return _juego->IndiceRareza(p);
}


Nat Driver::cantPokemonsTotales() const{
  return _juego->CantPokemnsTotales();
}


Nat Driver::cantMismaEspecie(const Pokemon& p) const{
  return _juego->CantMismaEspecie(p);
}
