#include "modulos.h"
#include <cassert>
#include <iostream>
#include "aed2.h"

using namespace aed2;

Juego::Juego(const Mapa &map){
  assert(false);
}

Juego::~Juego(){
  assert(false);
}

void Juego::AgregarPokemon(const Pokemon &p, const Coordenada &c){
  assert(false);
}

Nat Juego::AgregarJugador(){
  assert(false);
}

void Juego::Conectarse(Jugador e, const Coordenada &c){
  assert(false);
}

void Juego::Desconectarse(Jugador e){
  assert(false);
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
