#include "Driver.h"
using namespace aed2;

// Instanciar un mapa y un juego
Driver::Driver(const Conj< Coordenada > & cs) : _juego(NULL){
	//Mapa map(cs);
		
	//this->_juego = new Juego(map);
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
  assert(false);
}


Nat Driver::sanciones(const Jugador & j) const{
  assert(false);
}


Coordenada Driver::posicion(const Jugador & j) const{
  assert(false);
}


Dicc< Pokemon , Nat > Driver::pokemons(const Jugador & j) const{
  assert(false);
}


Conj< Jugador > Driver::expulsados() const{
  assert(false);
}


Conj< Coordenada > Driver::posConPokemons() const{
  assert(false);
}


Pokemon Driver::pokemonEnPos(const Coordenada & c) const{
  assert(false);
}


Nat Driver::cantMovimientosParaCaptura(const Coordenada & c) const{
  assert(false);
}


bool Driver::puedoAgregarPokemon(const Coordenada & c) const{
  assert(false);
}


bool Driver::hayPokemonCercano(const Coordenada & c) const{
  assert(false);
}


Coordenada Driver::posPokemonCercano(const Coordenada & c) const{
  assert(false);
}


Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada & c) const{
  assert(false);
}


Nat Driver::indiceRareza(const Pokemon & p) const{
  assert(false);
}


Nat Driver::cantPokemonsTotales() const{
  assert(false);
}


Nat Driver::cantMismaEspecie(const Pokemon & p) const{
  assert(false);
}
