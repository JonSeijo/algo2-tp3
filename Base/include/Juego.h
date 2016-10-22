#ifndef JUEGO_H_
#define JUEGO_H_


#include "../TiposJuego.h"
#include "../aed2/Conj.h"
#include "../aed2/Arreglo.h"

#include "Mapa.h"
#include "DiccString.h"

using namespace aed2;

class Juego{
  public:

    Juego(const Mapa &map);
    ~Juego();

    void AgregarPokemon(const Pokemon &p, const Coordenada &c);
    Nat AgregarJugador();

    void Conectarse(Jugador e, const Coordenada &c);
    void Desconectarse(Jugador e);

    void Moverse(Jugador e, const Coordenada &c);

    Mapa& Mapa();

    Conj<Jugador>::Iterador Jugadores();

    Nat Sanciones(Jugador e) const;

    Coordenada Posicion(Jugador e) const;

    DiccString<Pokemon>::Iterador Pokemons(Jugador e);

    const Conj<Jugador>& Expulsados() const;

    const Conj<Coordenada>& PosConPokemons() const;

    const Pokemon& PokemonEnPos(const COordenada &c) const;

    Nat CantMovimientosParaCaptura(const Coordenada &c) const;

    bool HayPokemonCercano(const Coordenada &c) const;

    const Coordenada& PosPokemonCercano(const Coordenada &c) const;

    const Conj<Jugador>& EntrenadoresPosibles(const COordenada &c, const Conj<Jugador> &es) const;

    Nat IndiceRareza(const Pokemon &p) const;

    Nat CantPokemnsTotales() const;

    Nat CantMismaEspecie(const Pokemon &p) const;

  private:

}




#endif // JUEGO_H_
