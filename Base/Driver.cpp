#include "Driver.h"
using namespace aed2;

// Instanciar un mapa y un juego
Driver::Driver(const Conj< Coordenada > & cs){
  assert(false);
}

Driver::~Driver(){
  assert(false);
}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c){
  assert(false);
}


Jugador Driver::agregarJugador(){
  assert(false);
}


void Driver::conectarse(const Jugador & j, const Coordenada & c){
  assert(false);
}


void Driver::desconectarse(const Jugador & j){
  assert(false);
}


void Driver::moverse(const Jugador & j, const Coordenada & c){
  assert(false);
}


Conj< Coordenada > Driver::mapa() const{
  assert(false);
}


bool Driver::hayCamino(const Coordenada & c1, const Coordenada & c2) const{
  assert(false);
}


bool Driver::posExistente(const Coordenada & c) const{
  assert(false);
}


Conj< Jugador > Driver::jugadores() const{
  assert(false);
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
