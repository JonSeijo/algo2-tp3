#ifndef JUEGO_H_
#define JUEGO_H_


#include "./../modulos.h"
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
        bool EstaConectado(Jugador e) const;


        DiccString<Nat>::Iterador Pokemons(Jugador e);

        Conj<Jugador> Expulsados() const;

        const Conj<Coordenada>& PosConPokemons() const;

        const Pokemon& PokemonEnPos(const Coordenada &c) const;

        Nat CantMovimientosParaCaptura(const Coordenada &c) const;

        bool HayPokemonCercano(const Coordenada &c) const;

        bool PuedoAgregarPokemon(const Coordenada&) const;

        Coordenada PosPokemonCercano(const Coordenada &c) const;

        Conj<Jugador> EntrenadoresPosibles(const Coordenada &c, const Conj<Jugador> &es) const;

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

            jugStruc(Nat id, Coordenada pos, Conj<Jugador>::Iterador iteradorAJuego)
             : _id(id), _sanciones(0), _conectado(false), _pos(pos), _pokemons(),
                 _itAJuego(iteradorAJuego), _itAEntrenadores(), _itAPos(), _cantCap(0){};

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

        Conj<Jugador> _jugadoresNoEliminados;
        Vector< Vector < Lista <Jugador> > > _grillaJugadores;

        Vector< Vector<pokeStruc*> > _pokenodos;

        Conj<Coordenada> _posPokemons;


        /**********************/
        /* Funciones privadas */
        /**********************/


        Vector<Jugador> DameJugadoreseEnPokerango(const Coordenada&) const;


        bool MovValido(Jugador, const Coordenada&) const;

        void CasoMov1(Jugador , const Coordenada&, const Coordenada&);
        void CasoMov2(Jugador , const Coordenada&, const Coordenada&);
        void CasoMov3(Jugador , const Coordenada&, const Coordenada&);
        void CasoMov4(Jugador , const Coordenada&, const Coordenada&);
        void CasoMov5(Jugador , const Coordenada&, const Coordenada&);

        void SumarUnoEnJug(Pokemon, Jugador);

        void AgregarAtrasJugsQueEstanEnPos(Vector<Jugador> &jugs, Nat, Nat) const;

        bool HayPokemonEnTerritorioRango5(const Coordenada &c) const;

};


#endif // JUEGO_H_
