#ifndef JUEGO_H_
#define JUEGO_H_


#include "../TiposJuego.h"
#include "../aed2/Conj.h"
#include "../aed2/Arreglo.h"

#include "Mapa.h"
#include "ColaPrioridad.hpp"
#include "DiccString.hpp"

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

    Mapa& mapa();

    Conj<Jugador>::Iterador Jugadores();

    Nat Sanciones(Jugador e) const;

    Coordenada Posicion(Jugador e) const;

    DiccString<Pokemon>::Iterador Pokemons(Jugador e);

    const Conj<Jugador>& Expulsados() const;

    const Conj<Coordenada>& PosConPokemons() const;

    const Pokemon& PokemonEnPos(const Coordenada &c) const;

    Nat CantMovimientosParaCaptura(const Coordenada &c) const;

    bool HayPokemonCercano(const Coordenada &c) const;

    const Coordenada& PosPokemonCercano(const Coordenada &c) const;

    const Conj<Jugador>& EntrenadoresPosibles(const Coordenada &c, const Conj<Jugador> &es) const;

    Nat IndiceRareza(const Pokemon &p) const;

    Nat CantPokemnsTotales() const;

    Nat CantMismaEspecie(const Pokemon &p) const;

  private:
    struct jugStruc{
      Nat _id;
      Nat _sanciones;
      bool _conectado;
      Coordenada _pos;
      DiccString<Nat> _pokemons;
      ColaPrioridad<jugYCantCapt>::Iterador _itAEntrenadores;
      Lista<Nat>::Iterador _itAPos;
      Conj<Jugador>::Iterador _itAJuego;
      Nat _cantCap;

      jugStruc(Nat id, Coordenada pos)
       : _id(id), _sanciones(0), _conectado(true), _pos(pos), _pokemons(),
         _itAJuego(), _itAEntrenadores(), _itAPos(), _cantCap(0){};

    };

    struct pokeStruc{
      Pokemon _poke;
      Nat _contador;
      ColaPrioridad<jugYCantCapt> _entrenadores;

      pokeStruc(Pokemon p) : _poke(p), _contador(0), _entrenadores() {};

    };

    DiccString<Nat> _cantPokemon;

    Nat _cantPokemonesTotales;

    Mapa* _mapa;

    Vector<jugStruc> _jugadores;

    Conj<jugStruc> _jugadoresNoEliminados;
    Vector< Vector < Lista <Jugador> > > _grillaJugadores;

    Vector< Vector<pokeStruc*> > _pokenodos;

    Conj<Coordenada> _posPokemons;


    /**********************/
    /* Funciones privadas */
    /**********************/


    Vector<Jugador> DameJugadoreseEnPokerango(const Coordenada&) const;
};




#endif // JUEGO_H_
