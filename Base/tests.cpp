// Compilar usando:
//  g++ -g tests.cpp -o tests
//  valgrind --leak-check=full ./tests

#include <iostream>
#include "Driver.cpp"
#include "modulos.h"
#include "mini_test.h"

using namespace aed2;

void ag(Conj<Coordenada> &cc, Nat x, Nat y) {
    cc.Agregar(Coordenada(x, y));
}

Conj<Coordenada> mapaTipo0() {
    /*
      0 1 2
    0 - - -
    1 - X -
    2 - - X

    */

    Conj<Coordenada> cc;
    ag(cc, 1, 1);
    ag(cc, 2, 2);
    return cc;
}

Conj<Coordenada> mapaTipo1() {
    /*
    Mapa tipo 1 tiene esta pinta:
    (X son las posisiones validas)
    Tamanio: 10x10

         0 1 2 3 4 5 6 7 8 9
    0    X X X - - - - - - -
    1    X X X - - - - - - -
    2    X X X X X - - - - -
    3    - - X X X - - - - -
    4    - - X X X - - - - -
    5    - - - - X X X X - -
    6    - - - - - X X X - -
    7    - - - - - X X X - -
    8    - - - - - - - - - -
    9    - - - - - - - - - X
    */

    Conj<Coordenada> cc;
    ag(cc, 0, 0);  ag(cc, 1, 0);    ag(cc, 2, 0);
    ag(cc, 0, 1);  ag(cc, 1, 1);    ag(cc, 2, 1);
    ag(cc, 0, 2);  ag(cc, 1, 2);    ag(cc, 2, 2);  ag(cc, 3, 2);  ag(cc, 4, 2);
                                    ag(cc, 2, 3);  ag(cc, 3, 3);  ag(cc, 4, 3);
                                    ag(cc, 2, 4);  ag(cc, 3, 4);  ag(cc, 4, 4);
                                                                  ag(cc, 4, 5); ag(cc, 5, 5);  ag(cc, 6, 5);  ag(cc, 7, 5);
                                                                                ag(cc, 5, 6);  ag(cc, 6, 6);  ag(cc, 7, 6);
                                                                                ag(cc, 5, 7);  ag(cc, 6, 7);  ag(cc, 7, 7);


    ag(cc, 9, 9);
    return cc;
}

Conj<Coordenada> mapa_12_1(){
	Conj<Coordenada> cc;
	ag(cc, 5, 5);
	ag(cc, 12, 2);
	ag(cc, 12, 1);

	return cc;
}

void test_constructor_con_mapa() {
    Conj<Coordenada> cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(0,1));
    cc.Agregar(Coordenada(0,2));
    cc.Agregar(Coordenada(1,2));
    cc.Agregar(Coordenada(10,0));
    cc.Agregar(Coordenada(1,4));
    Driver d(cc);
    
    ASSERT(d.mapa() == cc);

    ASSERT(d.posConPokemons().EsVacio());
    ASSERT(d.jugadores().EsVacio());
    ASSERT(d.expulsados().EsVacio());
    ASSERT(d.posConPokemons().EsVacio());
    ASSERT(d.cantPokemonsTotales() == 0);

    Conj<Coordenada> cc2 = mapaTipo0();
    Driver d2(cc2);
    ASSERT(d2.mapa() == cc2);
    ASSERT(d2.posConPokemons().EsVacio());
    ASSERT(d2.jugadores().EsVacio());
    ASSERT(d2.expulsados().EsVacio());
    ASSERT(d2.posConPokemons().EsVacio());
    ASSERT(d2.cantPokemonsTotales() == 0);

    Conj<Coordenada> cc3 = mapaTipo1();
    Driver d3(cc3);
    ASSERT(d3.mapa() == cc3);
    ASSERT(d3.posConPokemons().EsVacio());
    ASSERT(d3.jugadores().EsVacio());
    ASSERT(d3.expulsados().EsVacio());
    ASSERT(d3.posConPokemons().EsVacio());
    ASSERT(d3.cantPokemonsTotales() == 0);
}

void test_agregar_jugadores(){
    Driver d(mapaTipo1());

    Jugador e = d.agregarJugador();
    ASSERT(e == 0);
    ASSERT(!d.estaConectado(e));
    ASSERT(d.sanciones(e) == 0);
    ASSERT(d.jugadores().Pertenece(e));
    ASSERT(!d.expulsados().Pertenece(e));

    Jugador e1 = d.agregarJugador();
    ASSERT(e1 == 1);
    ASSERT(!d.estaConectado(e1));
    ASSERT(d.sanciones(e1) == 0);
    ASSERT(d.jugadores().Pertenece(e1));
    ASSERT(!d.expulsados().Pertenece(e1));

    Jugador e2 = d.agregarJugador();
    ASSERT(e2 == 2);
    ASSERT(!d.estaConectado(e2));
    ASSERT(d.sanciones(e2) == 0);
    ASSERT(d.jugadores().Pertenece(e2));
    ASSERT(!d.expulsados().Pertenece(e2));

    ASSERT(d.jugadores().Pertenece(e));
    ASSERT(d.jugadores().Pertenece(e1));

    // tipo0 no tiene la coordenada (0,0), y los jugadores se inicializan en (0,0)
    // No deberia romperse nada, por eso el test
    Driver d2(mapaTipo0());
    Jugador e20 = d2.agregarJugador();
    ASSERT(e20 == 0);
    ASSERT(!d2.estaConectado(e20));
    ASSERT(d2.sanciones(e20) == 0);
    ASSERT(d2.jugadores().Pertenece(e20));
    ASSERT(!d2.expulsados().Pertenece(e20));

    Jugador e21 = d2.agregarJugador();
    ASSERT(e21 == 1);
    ASSERT(!d2.estaConectado(e21));
    ASSERT(d2.sanciones(e21) == 0);
    ASSERT(d2.jugadores().Pertenece(e21));
    ASSERT(!d2.expulsados().Pertenece(e21));

    Jugador e22 = d2.agregarJugador();
    ASSERT(e22 == 2);
    ASSERT(!d2.estaConectado(e22));
    ASSERT(d2.sanciones(e22) == 0);
    ASSERT(d2.jugadores().Pertenece(e22));
    ASSERT(!d2.expulsados().Pertenece(e22));

    ASSERT(d2.jugadores().Pertenece(e20));
    ASSERT(d2.jugadores().Pertenece(e21));

}


void test_agregar_pokemones(){
    Driver d(mapaTipo0());

    Pokemon pikachu = "Pikachu";
    Pokemon agumon = "Agumon";
    Pokemon caracteresRaros = "2$&&/&(/&020.202}{+{[^`~~'987987987987";
    Pokemon vacio = "";
    Pokemon agumo = "Agumo";


    Coordenada coorPikachu = Coordenada(1, 1);
    Coordenada laotracoord = Coordenada(2, 2);

    d.agregarPokemon(pikachu, coorPikachu);

    ASSERT(d.hayPokemonCercano(coorPikachu));
    ASSERT(d.hayPokemonCercano(laotracoord));
    ASSERT(d.cantPokemonsTotales() == 1);
    ASSERT(d.cantMismaEspecie(pikachu) == 1);
    ASSERT(d.indiceRareza(pikachu) == 0);

    Driver e(mapaTipo1());

    e.agregarPokemon(agumon, Coordenada(9, 9));
    e.agregarPokemon(caracteresRaros, Coordenada(0, 0));
    e.agregarPokemon(caracteresRaros, Coordenada(5, 5));

    ASSERT(e.posPokemonCercano(Coordenada(1, 1)) == Coordenada(0, 0));
    ASSERT(e.posPokemonCercano(Coordenada(5, 6)) == Coordenada(5, 5));
    ASSERT(e.posPokemonCercano(Coordenada(9, 9)) == Coordenada(9, 9));

    ASSERT(!e.puedoAgregarPokemon(Coordenada(1, 1)));
    ASSERT(!e.puedoAgregarPokemon(Coordenada(5, 6)));

    ASSERT(e.cantPokemonsTotales() == 3);
    ASSERT(e.cantMismaEspecie(agumon) == 1);
    ASSERT(e.cantMismaEspecie(caracteresRaros) == 2);

    ASSERT(e.indiceRareza(agumon) == 100 - 33);
    ASSERT(e.indiceRareza(caracteresRaros) == 100 - 66);

    Driver f(mapaTipo1());

    f.agregarPokemon(agumon, Coordenada(0, 0));
    f.agregarPokemon(agumo, Coordenada(4, 5));
    f.agregarPokemon(vacio, Coordenada(9, 9));

    ASSERT(!f.puedoAgregarPokemon(Coordenada(1, 1)));
    ASSERT(!f.puedoAgregarPokemon(Coordenada(5, 6)));
    ASSERT(!f.puedoAgregarPokemon(Coordenada(7, 6)));

    ASSERT(f.posPokemonCercano(Coordenada(1, 1)) == Coordenada(0, 0));
    ASSERT(f.posPokemonCercano(Coordenada(5, 6)) == Coordenada(4, 5));
    ASSERT(f.hayPokemonCercano(Coordenada(9, 9)));

    ASSERT(f.cantPokemonsTotales() == 3);

    ASSERT(f.cantMismaEspecie(agumon) == 1);
    ASSERT(f.cantMismaEspecie(agumo) == 1);
    ASSERT(f.cantMismaEspecie(vacio) == 1);

    ASSERT(f.indiceRareza(agumon) == 100 - 33);
    ASSERT(f.indiceRareza(vacio) == 100 - 33);
    ASSERT(f.indiceRareza(agumo) == 100 - 33);

}

void test_puedoAgregarPokemon_vol2() {
    Coordenada c3(12,0);
    Coordenada c4(12,1);

    Conj<Coordenada> cc;
    cc.Agregar(c3);
    cc.Agregar(c4);
   
    Driver d(cc);

    // Las coordenadas estan bien... 
    ASSERT( d.mapa() == cc );

    ASSERT( d.puedoAgregarPokemon(Coordenada(12,0)) == true );
    ASSERT( d.puedoAgregarPokemon(Coordenada(12,1)) == true );
}

void test_puedoAgregarPokemon_espia() {
    Conj<Coordenada> cc;
    ag(cc, 120,2);
    ag(cc, 0,0);
    ag(cc, 1,0);
    ag(cc, 2,0);
    ag(cc, 12,0);
    ag(cc, 12,1);
    ag(cc, 12,2);

    Driver d(cc);

    ASSERT(d.puedoAgregarPokemon(Coordenada(120,2)) == true );
    ASSERT(d.puedoAgregarPokemon(Coordenada(0,0)) == true );
    ASSERT(d.puedoAgregarPokemon(Coordenada(1,0)) == true );
    ASSERT(d.puedoAgregarPokemon(Coordenada(2,0)) == true );
    ASSERT(d.puedoAgregarPokemon(Coordenada(12,0)) == true );

    ASSERT( d.hayPokemonCercano(Coordenada(12,1)) == false);

    ASSERT( d.mapa().Pertenece(Coordenada(12,1)) );
    ASSERT( d.puedoAgregarPokemon(Coordenada(12,1)) == true );
    
    ASSERT( d.puedoAgregarPokemon(Coordenada(12,2)) == true );

}

void test_puedoAgregarPokemon() {
    // Driver conductor(mapaTipo0());

    // ASSERT(conductor.puedoAgregarPokemon(Coordenada(1, 1)) && conductor.puedoAgregarPokemon(Coordenada(2, 2)));

    // conductor.agregarPokemon("Ernesto", Coordenada(2, 2));

    // ASSERT(!conductor.puedoAgregarPokemon(Coordenada(1, 1)) && !conductor.puedoAgregarPokemon(Coordenada(2, 2)));

    // Driver d(mapaTipo1());

    // ASSERT(d.puedoAgregarPokemon(Coordenada(0, 0)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(0, 1)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(0, 2)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(1, 0)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(1, 1)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(1, 2)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(2, 0)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(2, 1)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(2, 2)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(2, 3)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(2, 4)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(3, 2)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(3, 3)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(3, 4)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(4, 2)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(4, 3)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(4, 4)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(4, 5)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(5, 5)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(5, 6)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(5, 7)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(6, 5)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(6, 6)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(6, 7)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(7, 5)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(7, 6)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(7, 7)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(9, 9)));

    // d.agregarPokemon("{}{}{}{}", Coordenada(3, 4));

    // ASSERT(d.puedoAgregarPokemon(Coordenada(0, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 6)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(7, 7)));
    // ASSERT(d.puedoAgregarPokemon(Coordenada(9, 9)));

    // d.agregarPokemon("{}{}{}{}", Coordenada(7, 7));

    // ASSERT(d.puedoAgregarPokemon(Coordenada(0, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(9, 9)));

    // d.agregarPokemon("Rigoberto", Coordenada(0, 0));

    // ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 0)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 1)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 2)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 3)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 4)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 5)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 6)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 7)));
    // ASSERT(!d.puedoAgregarPokemon(Coordenada(9, 9)));
}

// Esto se va a poner feo
void test_agregar_pokemones_sinJugs(){
    Driver d(mapaTipo1());
    Coordenada c(0,0);
    d.agregarPokemon("Oddish", c);

    ASSERT(d.pokemonEnPos(c) == "Oddish");

}

void test_agregar_pokemones_conJugs(){
    Driver d(mapaTipo1());

    Jugador AshKetchup = d.agregarJugador();
    Jugador AshMostaza = d.agregarJugador();
    Jugador AshMayonesa = d.agregarJugador();

    d.conectarse(AshMayonesa, Coordenada(1, 0));
    d.conectarse(AshKetchup, Coordenada(1, 0));

    d.agregarPokemon("Mew", Coordenada(1, 1));
    ASSERT(d.pokemonEnPos(Coordenada(1, 1)) == "Mew");

    // Si se mueve a una invalida, la posicion no cambia
    d.moverse(AshMayonesa, Coordenada(9, 9));
    ASSERT(Coordenada(1,0) == d.posicion(AshMayonesa));

    ASSERT(!d.hayPokemonCercano(Coordenada(6, 5)));
    ASSERT(d.hayPokemonCercano(Coordenada(2,2)));
    d.desconectarse(AshMayonesa);

    // Si agrego poke cerca deberia tener poke cerca
    d.conectarse(AshMostaza, Coordenada(7,7));
    d.agregarPokemon("Godzila", Coordenada(5,7));
    ASSERT(d.hayPokemonCercano(Coordenada(7,7)));  // Hay pokemon cerca de mostaza
    ASSERT(d.posPokemonCercano(Coordenada(7,7)) == Coordenada(5,7));
    ASSERT(d.hayCamino(Coordenada(7,7), Coordenada(5,7)));

    d.moverse(AshMostaza, Coordenada(1,1));

    // Si me muevo hacia poke tambien deberia tener poke cerca
    d.moverse(AshMostaza, Coordenada(7,7));
    ASSERT(d.hayPokemonCercano(Coordenada(7,7)));  // Hay pokemon cerca de mostaza
    ASSERT(d.posPokemonCercano(Coordenada(7,7)) == Coordenada(5,7));
    ASSERT(d.hayCamino(Coordenada(7,7), Coordenada(5,7)));

    d.desconectarse(AshMostaza);

    d.agregarPokemon("Mew", Coordenada(6, 5));

    ASSERT(d.pokemonEnPos(Coordenada(1, 1)) == "Mew");
    ASSERT(d.pokemonEnPos(Coordenada(6, 5)) == "Mew");

}

void test_hayPokemonCercano() {
    Driver d(mapaTipo1());
    d.agregarPokemon("pikachu", Coordenada(0,0));
    ASSERT(d.hayPokemonCercano(Coordenada(0,0)));
    ASSERT(d.hayPokemonCercano(Coordenada(1,1)));
    ASSERT(d.hayPokemonCercano(Coordenada(2,0)));
    ASSERT(!d.hayPokemonCercano(Coordenada(2,2)));
    ASSERT(!d.hayPokemonCercano(Coordenada(100,100)));
}

void test_posPokeCercano() {
    Driver d(mapaTipo1());
    Coordenada c(0,0);
    d.agregarPokemon("Vileplume", c);
    Coordenada c1 = d.posPokemonCercano(Coordenada(1,0));
    ASSERT(c == c1);
}

void test_movimientosParaCaptura() {
    Driver d(mapaTipo1());
    d.agregarPokemon("Gandalf", Coordenada(0,0));
    Jugador frodo = d.agregarJugador();
    // Inicialmente cantMovs esta en 0
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 0);
    d.conectarse(frodo, Coordenada(1,1));
    // Cuando alguien se conecta se reinicia a 0
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 0);
    // Si me muevo dentro del pokeradio no pasa nada
    d.moverse(frodo, Coordenada(0,1));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 0);


    Jugador gollum = d.agregarJugador();
    // Alguien se conecta fuera del pokerango, NO aumenta el contador
    // VER, quiza deberia
    d.conectarse(gollum, Coordenada(5,5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 0);

    // Alguien se mueve fuera del pokerango
    d.moverse(gollum, Coordenada(4,4));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 1);

    // Alguien se mueve fuera del pokerango
    d.moverse(gollum, Coordenada(4,5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 2);

    // Alguien se mueve dentro del pokerango, se reinicia contador
    d.moverse(gollum, Coordenada(1,1));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 0);
}

void test_capturarSeEliminaElPokemon() {
    Driver d(mapaTipo1());

    d.agregarPokemon("Cartucho de tinta negro 117 Epson", Coordenada(2, 2));

    //AshSalsaGolf es la fusión entre AshKetchup y AshMayonesa
    Jugador AshSalsaGolf = d.agregarJugador();
    Jugador AshAdhereso = d.agregarJugador();

    d.conectarse(AshSalsaGolf, Coordenada(2, 2));
    d.conectarse(AshAdhereso, Coordenada(2, 1));
    
    ASSERT(d.pokemons(AshAdhereso).CantClaves() == 0);

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 0);
    d.moverse(AshSalsaGolf, Coordenada(9, 9));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 0);
    d.moverse(AshSalsaGolf, Coordenada(9, 9));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 0);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 1);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 2);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 3);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 4);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 5);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 6);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 7);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 8);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 2)) == 9);
    d.moverse(AshSalsaGolf, Coordenada(4, 5));

    ASSERT(d.pokemons(AshAdhereso).CantClaves() == 1);    


    ASSERT(!d.hayPokemonCercano(Coordenada(2, 2)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(2, 2)));
}

void test_jugadorCorrectoEsQuienCaptura() {
    Driver d(mapaTipo1());

    Jugador ID_0 = d.agregarJugador();
    Jugador ID_1 = d.agregarJugador();
    Jugador ID_2 = d.agregarJugador();

    d.conectarse(ID_1, Coordenada(6, 5));

    d.agregarPokemon("Carlitos Bala", Coordenada(5, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(5, 5)) == 0);

    d.conectarse(ID_2, Coordenada(1, 1));

    d.moverse(ID_2, Coordenada(0, 0));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(5, 5)) == 1);

    d.conectarse(ID_0, Coordenada(5, 7));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(5, 5)) == 0);

    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));
    d.moverse(ID_2, Coordenada(0, 0));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(5, 5)) == 9);

    d.moverse(ID_2, Coordenada(0, 1));

    ASSERT(!d.hayPokemonCercano(Coordenada(5, 5)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(5, 5)));
    ASSERT(d.pokemons(ID_0).Definido("Carlitos Bala"));
    ASSERT(d.pokemons(ID_0).Significado("Carlitos Bala") == 1);

    d.agregarPokemon("Carlitos Bala 2", Coordenada(0, 0));

    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));
    d.moverse(ID_1, Coordenada(7, 6));

    ASSERT(d.pokemons(ID_0).Definido("Carlitos Bala"));
    ASSERT(d.pokemons(ID_0).Significado("Carlitos Bala") == 1);
    ASSERT(d.pokemons(ID_2).Definido("Carlitos Bala 2"));
    ASSERT(d.pokemons(ID_2).Significado("Carlitos Bala 2") == 1);

    d.desconectarse(ID_0);
    d.desconectarse(ID_2);

    d.moverse(ID_1, Coordenada(0, 0));

    d.agregarPokemon("Vicente Viloni", Coordenada(9, 9));

    d.conectarse(ID_2, Coordenada(9, 9));

    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 9);

    d.conectarse(ID_0, Coordenada(9, 9));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 0);

    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));
    d.moverse(ID_1, Coordenada(0, 0));

    d.desconectarse(ID_1);
    d.desconectarse(ID_0);
    d.desconectarse(ID_2);

    ASSERT(d.pokemons(ID_0).Definido("Carlitos Bala"));
    ASSERT(d.pokemons(ID_0).Significado("Carlitos Bala") == 1);
    ASSERT(d.pokemons(ID_0).Definido("Vicente Viloni"));
    ASSERT(d.pokemons(ID_0).Significado("Vicente Viloni") == 1);
    ASSERT(d.pokemons(ID_2).Definido("Carlitos Bala 2"));
    ASSERT(d.pokemons(ID_2).Significado("Carlitos Bala 2") == 1);
    ASSERT(d.puedoAgregarPokemon(Coordenada(0, 0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(0, 1)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(0, 2)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(1, 0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(1, 1)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(1, 2)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(2, 0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(2, 1)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(2, 2)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(2, 3)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(2, 4)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(3, 2)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(3, 3)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(3, 4)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(4, 2)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(4, 3)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(4, 4)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(4, 5)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(5, 5)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(5, 6)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(5, 7)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(6, 5)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(6, 6)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(6, 7)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(7, 5)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(7, 6)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(7, 7)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(9, 9)));
}

void test_capturarJugadorTieneNuevoPoke() {
    Driver d(mapaTipo1());

    Jugador Maquinola = d.agregarJugador();
    Jugador Lince = d.agregarJugador();
    Jugador BrunoBassi = d.agregarJugador();

    d.conectarse(Lince, Coordenada(1, 1));
    d.conectarse(Maquinola, Coordenada(9, 9));
    d.conectarse(BrunoBassi, Coordenada(6, 6));

    d.agregarPokemon("Julian Omar Maruca", Coordenada(6, 5));

    d.moverse(Maquinola, Coordenada(9, 9));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Maquinola, Coordenada(9, 9));
    d.moverse(Lince, Coordenada(1, 1));
    d.moverse(Maquinola, Coordenada(9, 9));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Maquinola, Coordenada(9, 9));
    d.moverse(Lince, Coordenada(1, 1));
    d.moverse(Maquinola, Coordenada(9, 9));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Maquinola, Coordenada(9, 9));
    d.moverse(Lince, Coordenada(1, 1));

    ASSERT(d.pokemons(BrunoBassi).Definido("Julian Omar Maruca"));
    ASSERT(d.pokemons(BrunoBassi).Significado("Julian Omar Maruca") == 1);

    d.desconectarse(Maquinola);
    d.conectarse(Maquinola, Coordenada(0, 0));

    d.moverse(Maquinola, Coordenada(6, 7));

    d.agregarPokemon("Elquechuga", Coordenada(6, 6));

    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));

    ASSERT(d.pokemons(BrunoBassi).Definido("Julian Omar Maruca"));
    ASSERT(d.pokemons(BrunoBassi).Significado("Julian Omar Maruca") == 1);
    ASSERT(d.pokemons(Maquinola).Definido("Elquechuga"));
    ASSERT(d.pokemons(Maquinola).Significado("Elquechuga") == 1);

    d.agregarPokemon("Elquechuga", Coordenada(6, 6));

    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));

    ASSERT(d.pokemons(BrunoBassi).Definido("Julian Omar Maruca"));
    ASSERT(d.pokemons(BrunoBassi).Significado("Julian Omar Maruca") == 1);
    ASSERT(d.pokemons(Maquinola).Definido("Elquechuga"));
    ASSERT(d.pokemons(Maquinola).Significado("Elquechuga") == 2);

    d.agregarPokemon("Pato The Hedgehog", Coordenada(6, 6));

    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));
    d.moverse(Lince, Coordenada(0, 0));

    ASSERT(d.pokemons(BrunoBassi).Definido("Julian Omar Maruca"));
    ASSERT(d.pokemons(BrunoBassi).Significado("Julian Omar Maruca") == 1);
    ASSERT(d.pokemons(BrunoBassi).Definido("Pato The Hedgehog"));
    ASSERT(d.pokemons(BrunoBassi).Significado("Pato The Hedgehog") == 1);
    ASSERT(d.pokemons(Maquinola).Definido("Elquechuga"));
    ASSERT(d.pokemons(Maquinola).Significado("Elquechuga") == 2);

}

void test_capturarContadoresDeTriesEstanBien() {
    Driver d(mapaTipo1());

    d.agregarPokemon("Valgrind no me tires errores pls", Coordenada(1, 0));

    Jugador NokiaLumia = d.agregarJugador();
    Jugador CapturaAValgrind = d.agregarJugador();
    Jugador Captura2Teletubbies = d.agregarJugador();

    d.conectarse(CapturaAValgrind, Coordenada(2, 1));
    d.conectarse(NokiaLumia, Coordenada(4, 3));
    d.moverse(NokiaLumia, Coordenada(4, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 1);

    d.moverse(NokiaLumia, Coordenada(9, 9));
    //Mov invalido

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 1);

    d.moverse(NokiaLumia, Coordenada(6, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 2);

    d.agregarPokemon("Teletubbie violeta", Coordenada(9, 9));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 2);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 0);

    d.conectarse(Captura2Teletubbies, Coordenada(9, 9));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 2);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 0);

    d.moverse(NokiaLumia, Coordenada(5, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 3);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 1);

    d.moverse(NokiaLumia, Coordenada(6, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 4);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 2);

    d.moverse(NokiaLumia, Coordenada(5, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 5);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 3);

    d.moverse(NokiaLumia, Coordenada(6, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 6);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 4);

    d.moverse(NokiaLumia, Coordenada(5, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 7);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 5);

    d.moverse(NokiaLumia, Coordenada(6, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 8);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 6);

    d.moverse(NokiaLumia, Coordenada(5, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(1, 0)) == 9);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 7);

    d.moverse(NokiaLumia, Coordenada(6, 5));

    ASSERT(d.puedoAgregarPokemon(Coordenada(1, 0)));
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 8);
    ASSERT(d.pokemons(CapturaAValgrind).Definido("Valgrind no me tires errores pls"));
    ASSERT(d.pokemons(CapturaAValgrind).Significado("Valgrind no me tires errores pls") == 1);

    d.moverse(CapturaAValgrind, Coordenada(2, 2));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 9);

    d.agregarPokemon("Teletubbie violeta", Coordenada(0, 0));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 0);
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(9, 9)) == 9);

    d.moverse(CapturaAValgrind, Coordenada(0, 2));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 0);    
    ASSERT(d.pokemons(Captura2Teletubbies).Definido("Teletubbie violeta"));
    ASSERT(d.pokemons(Captura2Teletubbies).Significado("Teletubbie violeta") == 1);
    ASSERT(d.pokemons(CapturaAValgrind).Definido("Valgrind no me tires errores pls"));
    ASSERT(d.pokemons(CapturaAValgrind).Significado("Valgrind no me tires errores pls") == 1);

    d.desconectarse(CapturaAValgrind);

    d.moverse(Captura2Teletubbies, Coordenada(0, 0));

    d.desconectarse(Captura2Teletubbies);

    d.conectarse(Captura2Teletubbies, Coordenada(0, 0));

    d.conectarse(CapturaAValgrind, Coordenada(1, 2));

    d.moverse(NokiaLumia, Coordenada(0, 1));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 0);    
    ASSERT(d.pokemons(Captura2Teletubbies).Definido("Teletubbie violeta"));
    ASSERT(d.pokemons(Captura2Teletubbies).Significado("Teletubbie violeta") == 1);
    ASSERT(d.pokemons(CapturaAValgrind).Definido("Valgrind no me tires errores pls"));
    ASSERT(d.pokemons(CapturaAValgrind).Significado("Valgrind no me tires errores pls") == 1);

    d.moverse(CapturaAValgrind, Coordenada(3, 2));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 1);

    d.moverse(CapturaAValgrind, Coordenada(7, 7));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 2);

    d.moverse(CapturaAValgrind, Coordenada(5, 6));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 3);

    d.moverse(CapturaAValgrind, Coordenada(2, 2));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 4);

    d.moverse(CapturaAValgrind, Coordenada(1, 2));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 5);

    d.moverse(CapturaAValgrind, Coordenada(2, 1));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 6);

    d.moverse(CapturaAValgrind, Coordenada(3, 2));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 7);

    d.moverse(CapturaAValgrind, Coordenada(6, 6));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 8);

    d.moverse(CapturaAValgrind, Coordenada(7, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 9);

    d.moverse(NokiaLumia, Coordenada(1, 1));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0, 0)) == 9);

    d.moverse(NokiaLumia, Coordenada(1, 2));

    ASSERT(d.pokemons(Captura2Teletubbies).Definido("Teletubbie violeta"));
    ASSERT(d.pokemons(Captura2Teletubbies).Significado("Teletubbie violeta") == 2);
    ASSERT(d.pokemons(CapturaAValgrind).Definido("Valgrind no me tires errores pls"));
    ASSERT(d.pokemons(CapturaAValgrind).Significado("Valgrind no me tires errores pls") == 1);
    ASSERT(d.puedoAgregarPokemon(Coordenada(1, 0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(0, 0)));
}

void test_entrenadoresPosibles() {
    Driver d(mapaTipo0());

    Jugador HashKetchup = d.agregarJugador();
    Jugador EquipoCohete = d.agregarJugador();
    Jugador RickyFort = d.agregarJugador();

    d.conectarse(HashKetchup, Coordenada(2, 2));

    d.agregarPokemon("Goku", Coordenada(2, 2));

    ASSERT(d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(HashKetchup));

    d.conectarse(RickyFort, Coordenada(2, 2));

    ASSERT(d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(HashKetchup));
    ASSERT(d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(RickyFort));

    // En vez de mover, conecto y desconecto pues los mover nunca van a ser validos
    d.desconectarse(RickyFort);
    d.conectarse(RickyFort, Coordenada(1, 1));

    ASSERT(d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(HashKetchup));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(RickyFort));

    d.conectarse(EquipoCohete, Coordenada(1, 1));

    ASSERT(d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(HashKetchup));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(RickyFort));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(EquipoCohete));

    d.desconectarse(RickyFort);

    ASSERT(d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(HashKetchup));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(RickyFort));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(EquipoCohete));

    d.desconectarse(HashKetchup);

    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(HashKetchup));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(RickyFort));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(EquipoCohete));

    d.desconectarse(EquipoCohete);
    d.conectarse(EquipoCohete, Coordenada(2, 2));

    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(HashKetchup));
    ASSERT(!d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(RickyFort));
    ASSERT(d.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(EquipoCohete));


    Driver e(mapaTipo1());

    Jugador MaquinaOrga1 = e.agregarJugador();

    e.conectarse(MaquinaOrga1, Coordenada(1, 0));

    e.moverse(MaquinaOrga1, Coordenada(0, 0));
    e.moverse(MaquinaOrga1, Coordenada(1, 0));

    Jugador Cache = e.agregarJugador();

    e.conectarse(Cache, Coordenada(2, 2));

    e.agregarPokemon("PokemonRecursivo", Coordenada(2, 1));

    ASSERT(e.entrenadoresPosibles(Coordenada(2, 1)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 1)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 0)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 0)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 3)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 3)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(3, 2)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(3, 2)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 2)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 2)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 1)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 1)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 0)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 0)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(0, 1)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(0, 1)).Pertenece(Cache));

    e.agregarPokemon("LosDronesDeAlgo1", Coordenada(6, 5));

    ASSERT(e.entrenadoresPosibles(Coordenada(6, 5)).EsVacio());

    e.desconectarse(Cache);

    ASSERT(e.entrenadoresPosibles(Coordenada(2, 1)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(2, 1)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(2, 0)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 0)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(2, 2)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 3)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(2, 3)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(3, 2)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(3, 2)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 2)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(1, 2)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 1)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(1, 1)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(1, 0)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(1, 0)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(0, 1)).Pertenece(MaquinaOrga1));
    ASSERT(!e.entrenadoresPosibles(Coordenada(0, 1)).Pertenece(Cache));
    ASSERT(e.entrenadoresPosibles(Coordenada(6, 5)).EsVacio());

    e.moverse(MaquinaOrga1, Coordenada(7, 7));

    ASSERT(e.entrenadoresPosibles(Coordenada(6, 5)).EsVacio());
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 1)).EsVacio());

/*    ASSERT(e.puedoAgregarPokemon(Coordenada(9, 9)));

    e.agregarPokemon("Taller De Haskell", Coordenada(9, 9));

    Jugador HojasA4 = e.agregarJugador();
    e.conectarse(HojasA4, Coordenada(7, 7));
    e.moverse(HojasA4, Coordenada(9, 9));
    e.moverse(HojasA4, Coordenada(1, 1));
    e.moverse(HojasA4, Coordenada(3, 2));
    e.moverse(MaquinaOrga1, Coordenada(9, 9));
    e.desconectarse(HojasA4);
    e.desconectarse(MaquinaOrga1);
    e.conectarse(HojasA4, Coordenada(9, 9));
    e.conectarse(MaquinaOrga1, Coordenada(9, 9));
    e.conectarse(Cache, Coordenada(9, 9));

    ASSERT(e.entrenadoresPosibles(Coordenada(9, 9)).Pertenece(Cache) && e.entrenadoresPosibles(Coordenada(9, 9)).Pertenece(HojasA4) && e.entrenadoresPosibles(Coordenada(9, 9)).Pertenece(MaquinaOrga1));
    ASSERT(e.entrenadoresPosibles(Coordenada(6, 5)).EsVacio());
    ASSERT(e.entrenadoresPosibles(Coordenada(2, 1)).EsVacio());
*/
}

void test_sancionar_simple() {
    Driver d(mapaTipo1());
    Jugador batracio = d.agregarJugador();
    d.conectarse(batracio, Coordenada(0,0));
    ASSERT(d.sanciones(batracio) == 0);

    d.moverse(batracio, Coordenada(100,100));
    ASSERT(d.sanciones(batracio) == 1);
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(d.sanciones(batracio) == 2);
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(d.sanciones(batracio) == 3);
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(d.sanciones(batracio) == 4);
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(!d.estaConectado(batracio));
    ASSERT(d.expulsados().Pertenece(batracio));
    ASSERT(!d.jugadores().Pertenece(batracio));
}

void test_sancionar_conpokerango() {
    Driver d(mapaTipo1());
    d.agregarPokemon("charizard", Coordenada(0,0));

    Jugador batracio = d.agregarJugador();
    d.conectarse(batracio, Coordenada(0,0));
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(d.sanciones(batracio) == 1);
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(d.sanciones(batracio) == 2);
    d.moverse(batracio, Coordenada(100,100));

    // Como fueron invalidos no afectan a los movs para captura
    ASSERT(d.cantMovimientosParaCaptura(Coordenada(0,0)) == 0);

    ASSERT(d.sanciones(batracio) == 3);
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(d.sanciones(batracio) == 4);
    d.moverse(batracio, Coordenada(100,100));
    ASSERT(!d.estaConectado(batracio));
    ASSERT(d.expulsados().Pertenece(batracio));
    ASSERT(!d.jugadores().Pertenece(batracio));

    // Habria que testear tambien que no haya entrenadores posibles etc
}

void test_eliminarDeJuego() {
    Driver d(mapaTipo0());

    Jugador TeVoyAEliminar = d.agregarJugador();

    d.conectarse(TeVoyAEliminar, Coordenada(1, 1));


    //Recordar que en un mov inválido la posición no cambia
    d.moverse(TeVoyAEliminar, Coordenada(2, 2));
    ASSERT(d.sanciones(TeVoyAEliminar) == 1);
    d.moverse(TeVoyAEliminar, Coordenada(2, 2));
    ASSERT(d.sanciones(TeVoyAEliminar) == 2);
    d.moverse(TeVoyAEliminar, Coordenada(2, 2));
    ASSERT(d.sanciones(TeVoyAEliminar) == 3);
    d.moverse(TeVoyAEliminar, Coordenada(2, 2));
    ASSERT(d.sanciones(TeVoyAEliminar) == 4);
    d.moverse(TeVoyAEliminar, Coordenada(2, 2));

    ASSERT(d.expulsados().Pertenece(TeVoyAEliminar));

    Jugador AgarraPokemon = d.agregarJugador();

    Driver e(mapaTipo1());

    Jugador Capturador = e.agregarJugador();

    e.agregarPokemon("Patamon", Coordenada(4, 5));

    e.conectarse(Capturador, Coordenada(4, 4));

    Jugador SeMueve = e. agregarJugador();

    e.moverse(Capturador, Coordenada(9, 9));
    ASSERT(e.sanciones(Capturador) == 1);
    e.moverse(Capturador, Coordenada(9, 9));
    ASSERT(e.sanciones(Capturador) == 2);
    e.moverse(Capturador, Coordenada(9, 9));
    ASSERT(e.sanciones(Capturador) == 3);
    e.moverse(Capturador, Coordenada(9, 9));
    ASSERT(e.sanciones(Capturador) == 4);

    e.desconectarse(Capturador);

    e.conectarse(Capturador, Coordenada(4, 3));

    e.conectarse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.desconectarse(SeMueve);
    e.conectarse(SeMueve, Coordenada(0, 1));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));
    e.moverse(SeMueve, Coordenada(0, 0));

    ASSERT(e.pokemons(Capturador).Definido("Patamon"));
    ASSERT(e.pokemons(Capturador).Significado("Patamon") == 1);
    ASSERT(e.cantPokemonsTotales() == 1);

    e.moverse(Capturador, Coordenada(9, 9));

    ASSERT(e.cantPokemonsTotales() == 0);
    ASSERT(e.expulsados().Pertenece(Capturador));

    e.agregarPokemon("Patamon", Coordenada(0, 0));

    ASSERT(e.cantPokemonsTotales() == 1);
    ASSERT(e.cantMismaEspecie("Patamon") == 1);
    ASSERT(e.expulsados().Pertenece(Capturador));
    ASSERT(e.indiceRareza("Patamon") == 0);
}

void test_conectar() {
    Driver d(mapaTipo1());
    Jugador j = d.agregarJugador();

    Coordenada c(0,0);

    d.conectarse(j, c);
    ASSERT(d.estaConectado(j));

    ASSERT(d.posicion(j) == c);
}

void test_desconectar() {
    Driver d(mapaTipo1());
    Jugador j = d.agregarJugador();

    Coordenada c(0,0);

    d.conectarse(j, c);
    ASSERT(d.estaConectado(j));

    d.desconectarse(j);
    ASSERT(!d.estaConectado(j));
}

void test_mover_sinPokes() {
  Driver d(mapaTipo1());
    Jugador j = d.agregarJugador();

    Coordenada c(0,0);

    d.conectarse(j, c);
    ASSERT(d.estaConectado(j));

    ASSERT(d.posicion(j) == c);
    d.moverse(j, Coordenada(2, 2));
    ASSERT(d.posicion(j) == Coordenada(2, 2));

    ASSERT(d.sanciones(j) == 0);


}

void test_mover_sinPokesYSancionar() {
    Driver d(mapaTipo1());
    Jugador j = d.agregarJugador();

    Coordenada c(0,0);

    d.conectarse(j, c);
    ASSERT(d.estaConectado(j));

    ASSERT(d.posicion(j) == c);

    d.moverse(j, Coordenada(12, 2));
    ASSERT(d.sanciones(j) == 1);
    ASSERT(d.posicion(j) == c);

}

void test_mover_conPokes() {
    Driver d(mapaTipo1());

    Jugador RedSocialRobertoCarlos = d.agregarJugador();

    d.agregarPokemon("e-ameos", Coordenada(2, 1));

    d.conectarse(RedSocialRobertoCarlos, Coordenada(2, 2));

    Jugador EseParcialEraImposible = d.agregarJugador();
    Jugador PorSuerteMeFueBienEnElRecuperatorio = d.agregarJugador();

    d.conectarse(EseParcialEraImposible, Coordenada(5, 5));

    d.conectarse(PorSuerteMeFueBienEnElRecuperatorio, Coordenada(7, 5));

    ASSERT(d.cantMovimientosParaCaptura(Coordenada(2, 1)) == 0);

    d.moverse(EseParcialEraImposible, Coordenada(5, 7));
    d.moverse(PorSuerteMeFueBienEnElRecuperatorio, Coordenada(5, 7));
    d.moverse(EseParcialEraImposible, Coordenada(5, 7));
    d.moverse(PorSuerteMeFueBienEnElRecuperatorio, Coordenada(5, 7));
    d.moverse(EseParcialEraImposible, Coordenada(5, 7));
    d.moverse(PorSuerteMeFueBienEnElRecuperatorio, Coordenada(5, 7));
    d.moverse(EseParcialEraImposible, Coordenada(5, 7));
    d.moverse(PorSuerteMeFueBienEnElRecuperatorio, Coordenada(5, 7));
    d.moverse(EseParcialEraImposible, Coordenada(5, 7));
    d.moverse(PorSuerteMeFueBienEnElRecuperatorio, Coordenada(5, 7));

    ASSERT(d.pokemons(RedSocialRobertoCarlos).Definido("e-ameos"));
    ASSERT(d.pokemons(RedSocialRobertoCarlos).Significado("e-ameos") == 1);

    d.moverse(RedSocialRobertoCarlos, Coordenada(1, 1));

    ASSERT(d.pokemons(RedSocialRobertoCarlos).Definido("e-ameos"));
    ASSERT(d.pokemons(RedSocialRobertoCarlos).Significado("e-ameos") == 1);

    d.moverse(RedSocialRobertoCarlos, Coordenada(9, 9));

    ASSERT(d.pokemons(RedSocialRobertoCarlos).Definido("e-ameos"));
    ASSERT(d.pokemons(RedSocialRobertoCarlos).Significado("e-ameos") == 1);

    d.moverse(RedSocialRobertoCarlos, Coordenada(5, 6));

    ASSERT(d.pokemons(RedSocialRobertoCarlos).Definido("e-ameos"));
    ASSERT(d.pokemons(RedSocialRobertoCarlos).Significado("e-ameos") == 1);

    d.moverse(RedSocialRobertoCarlos, Coordenada(3, 3));

    ASSERT(d.pokemons(RedSocialRobertoCarlos).Definido("e-ameos"));
    ASSERT(d.pokemons(RedSocialRobertoCarlos).Significado("e-ameos") == 1);

}

void test_mover_conPokesYCapturar() {
    Driver d(mapaTipo1());

    Jugador MC_Pluto = d.agregarJugador();

    d.conectarse(MC_Pluto, Coordenada(4, 2));

    d.moverse(MC_Pluto, Coordenada(9, 9));
    d.moverse(MC_Pluto, Coordenada(7, 5));

    Jugador WalterBlanco = d.agregarJugador();

    d.conectarse(WalterBlanco, Coordenada(0, 1));

    d.agregarPokemon("Pyramid Head", Coordenada(0, 0));

    d.agregarPokemon("El protagonista del Silent Hill 2 es el que mato a su jermu", Coordenada(9, 9));

    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));

    ASSERT(d.pokemons(WalterBlanco).Definido("Pyramid Head"));
    ASSERT(d.pokemons(WalterBlanco).Significado("Pyramid Head") == 1);

    d.moverse(WalterBlanco, Coordenada(6, 6));

    d.agregarPokemon("Al final de 9 reinas lo cagan a Darin", Coordenada(1, 0));

    d.moverse(WalterBlanco, Coordenada(0, 0));

    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));
    d.moverse(MC_Pluto, Coordenada(7, 5));

    ASSERT(d.pokemons(WalterBlanco).Definido("Pyramid Head"));
    ASSERT(d.pokemons(WalterBlanco).Significado("Pyramid Head") == 1);
    ASSERT(d.pokemons(WalterBlanco).Definido("Al final de 9 reinas lo cagan a Darin"));
    ASSERT(d.pokemons(WalterBlanco).Significado("Al final de 9 reinas lo cagan a Darin") == 1);

}

void test_indice_rareza() {
    Driver d(mapaTipo1());
    d.agregarPokemon("pikachu", Coordenada(0,0));
    d.agregarPokemon("rattata", Coordenada(7,7));

    ASSERT(d.indiceRareza("rattata") == 50);

    ASSERT(d.indiceRareza("rattata") == d.indiceRareza("pikachu"));


}

void test_pokemon_cercano_coor_invalida(){
    Driver d(mapaTipo1());
    d.agregarPokemon("pikachu", Coordenada(0, 0));
    ASSERT(!d.hayPokemonCercano(Coordenada(0, 3)));
}

void test_mov_invalido_con_camino(){

    Conj<Coordenada> cs;
    for (Nat i = 0; i < 12; i++) {
        ag(cs, 0, i);
    }
    Driver d(cs);

    Jugador maestroPokemon = d.agregarJugador();

    d.conectarse(maestroPokemon, Coordenada(0, 0));

    d.moverse(maestroPokemon, Coordenada(0, 11));

    ASSERT(d.posicion(maestroPokemon) == Coordenada(0, 0));

    ASSERT(d.sanciones(maestroPokemon) == 1);
}

void test_comprobarCoordenadasDelMapa(){

	Driver d(mapaTipo1());

	Jugador j0 = d.agregarJugador();
	d.agregarPokemon("Pikachu", Coordenada(1, 1));
	d.conectarse(j0, Coordenada(1, 1));

	ASSERT(d.mapa().Pertenece(Coordenada(0, 0)));
	ASSERT(d.mapa().Pertenece(Coordenada(0, 1)));
	ASSERT(d.mapa().Pertenece(Coordenada(0, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 4)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(0, 10)));

	ASSERT(d.mapa().Pertenece(Coordenada(1, 0)));
	ASSERT(d.mapa().Pertenece(Coordenada(1, 1)));
	ASSERT(d.mapa().Pertenece(Coordenada(1, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 4)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(1, 10)));

	ASSERT(d.mapa().Pertenece(Coordenada(2, 0)));
	ASSERT(d.mapa().Pertenece(Coordenada(2, 1)));
	ASSERT(d.mapa().Pertenece(Coordenada(2, 2)));
	ASSERT(d.mapa().Pertenece(Coordenada(2, 3)));
	ASSERT(d.mapa().Pertenece(Coordenada(2, 4)));
	ASSERT(!d.mapa().Pertenece(Coordenada(2, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(2, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(2, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(2, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(2, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(2, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(3, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(3, 1)));
	ASSERT(d.mapa().Pertenece(Coordenada(3, 2)));
	ASSERT(d.mapa().Pertenece(Coordenada(3, 3)));
	ASSERT(d.mapa().Pertenece(Coordenada(3, 4)));
	ASSERT(!d.mapa().Pertenece(Coordenada(3, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(3, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(3, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(3, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(3, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(3, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(4, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(4, 1)));
	ASSERT(d.mapa().Pertenece(Coordenada(4, 2)));
	ASSERT(d.mapa().Pertenece(Coordenada(4, 3)));
	ASSERT(d.mapa().Pertenece(Coordenada(4, 4)));
	ASSERT(d.mapa().Pertenece(Coordenada(4, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(4, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(4, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(4, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(4, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(4, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(5, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(5, 1)));
	ASSERT(!d.mapa().Pertenece(Coordenada(5, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(5, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(5, 4)));
	ASSERT(d.mapa().Pertenece(Coordenada(5, 5)));
	ASSERT(d.mapa().Pertenece(Coordenada(5, 6)));
	ASSERT(d.mapa().Pertenece(Coordenada(5, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(5, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(5, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(5, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(6, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(6, 1)));
	ASSERT(!d.mapa().Pertenece(Coordenada(6, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(6, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(6, 4)));
	ASSERT(d.mapa().Pertenece(Coordenada(6, 5)));
	ASSERT(d.mapa().Pertenece(Coordenada(6, 6)));
	ASSERT(d.mapa().Pertenece(Coordenada(6, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(6, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(6, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(6, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(7, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(7, 1)));
	ASSERT(!d.mapa().Pertenece(Coordenada(7, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(7, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(7, 4)));
	ASSERT(d.mapa().Pertenece(Coordenada(7, 5)));
	ASSERT(d.mapa().Pertenece(Coordenada(7, 6)));
	ASSERT(d.mapa().Pertenece(Coordenada(7, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(7, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(7, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(7, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(8, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 1)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 4)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(8, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(9, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 1)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 4)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 8)));
	ASSERT(d.mapa().Pertenece(Coordenada(9, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(9, 10)));

	ASSERT(!d.mapa().Pertenece(Coordenada(10, 0)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 1)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 2)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 3)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 4)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 5)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 6)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 7)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 8)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 9)));
	ASSERT(!d.mapa().Pertenece(Coordenada(10, 10)));
}

void test_hayCamino(){
	Driver d(mapaTipo0());

	ASSERT(!d.hayCamino(Coordenada(1, 1), Coordenada(2, 2)));
	ASSERT(!d.hayCamino(Coordenada(2, 2), Coordenada(1, 1)));
	ASSERT(d.hayCamino(Coordenada(1, 1), Coordenada(1, 1)));
	ASSERT(d.hayCamino(Coordenada(2, 2), Coordenada(2, 2)));

	Driver e(mapaTipo1());

	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 0), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(0, 0), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 1), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(0, 1), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(0, 2), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(0, 2), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 0), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(1, 0), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 1), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(1, 1), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(1, 2), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(1, 2), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 0), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(2, 0), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 1), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(2, 1), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 2), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(2, 2), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 3), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(2, 3), Coordenada(9, 9)));

	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(0, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(0, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(0, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(1, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(1, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(1, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(2, 0)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(2, 1)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(2, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(2, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(2, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(3, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(3, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(3, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(4, 2)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(4, 3)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(4, 4)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(4, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(5, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(5, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(5, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(6, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(6, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(6, 7)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(7, 5)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(7, 6)));
	ASSERT(e.hayCamino(Coordenada(2, 4), Coordenada(7, 7)));
	ASSERT(!e.hayCamino(Coordenada(2, 4), Coordenada(9, 9)));

	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(0, 0)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(0, 1)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(0, 2)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(1, 0)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(1, 1)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(1, 2)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(2, 0)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(2, 1)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(2, 2)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(2, 3)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(2, 4)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(3, 2)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(3, 3)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(3, 4)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(4, 2)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(4, 3)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(4, 4)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(4, 5)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(5, 5)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(5, 6)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(5, 7)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(6, 5)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(6, 6)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(6, 7)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(7, 5)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(7, 6)));
	ASSERT(!e.hayCamino(Coordenada(9, 9), Coordenada(7, 7)));
	ASSERT(e.hayCamino(Coordenada(9, 9), Coordenada(9, 9)));
}

void test_posExistente(){
	Driver d(mapaTipo0());

	ASSERT(d.posExistente(Coordenada(1, 1)));
	ASSERT(d.posExistente(Coordenada(2, 2)));
	ASSERT(!d.posExistente(Coordenada(0, 1)));
	ASSERT(!d.posExistente(Coordenada(0, 2)));
	ASSERT(!d.posExistente(Coordenada(1, 0)));
	ASSERT(!d.posExistente(Coordenada(1, 2)));
	ASSERT(!d.posExistente(Coordenada(0, 0)));
	ASSERT(!d.posExistente(Coordenada(9990, 546)));
	ASSERT(!d.posExistente(Coordenada(4, 0)));
}

void test_jugadoresNoEliminados(){
    Driver d(mapaTipo0());

    Jugador Eliminado = d.agregarJugador();
    Jugador Eliminado2 = d.agregarJugador();
    Jugador NoEliminado = d.agregarJugador();
    Jugador NoEliminado2 = d.agregarJugador();

    d.conectarse(Eliminado, Coordenada(1, 1));
    d.conectarse(Eliminado2, Coordenada(2, 2));
    d.conectarse(NoEliminado, Coordenada(2, 2));
    d.conectarse(NoEliminado2, Coordenada(1, 1));

    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));

    d.desconectarse(NoEliminado);
    d.desconectarse(NoEliminado2);

    Conj<Jugador> cj(d.jugadores());

    ASSERT(cj.Pertenece(NoEliminado));
    ASSERT(cj.Pertenece(NoEliminado2));
    ASSERT(!cj.Pertenece(Eliminado));
    ASSERT(!cj.Pertenece(Eliminado2));
}

void test_posicionJugador(){
    Driver d(mapaTipo0());

    Jugador Eliminado = d.agregarJugador();
    Jugador Eliminado2 = d.agregarJugador();
    Jugador NoEliminado = d.agregarJugador();
    Jugador NoEliminado2 = d.agregarJugador();

    d.conectarse(Eliminado, Coordenada(1, 1));
    d.conectarse(Eliminado2, Coordenada(2, 2));
    d.conectarse(NoEliminado, Coordenada(2, 2));
    d.conectarse(NoEliminado2, Coordenada(1, 1));

    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));
    d.moverse(Eliminado, Coordenada(0, 0));
    d.moverse(Eliminado2, Coordenada(1, 1));

    ASSERT(d.posicion(NoEliminado) == Coordenada(2, 2));
    ASSERT(d.posicion(NoEliminado2) == Coordenada(1, 1));
}

void test_posConPokemon(){
    Driver d(mapaTipo1());

    d.agregarPokemon("La puta madre cuando vamos a pasar los tests de la catedra", Coordenada(0, 0));

    ASSERT(d.posConPokemons().Pertenece(Coordenada(0, 0)));

    d.agregarPokemon("La puta madre cuando vamos a pasar los tests de la catedra", Coordenada(4, 4));

    d.agregarPokemon("La puta madre cuando vamos a pasar los tests de la catedra", Coordenada(9, 9));

    ASSERT(d.posConPokemons().Pertenece(Coordenada(0, 0)));
    ASSERT(d.posConPokemons().Pertenece(Coordenada(4, 4)));
    ASSERT(d.posConPokemons().Pertenece(Coordenada(9, 9)));
}

void test_expulsados(){
    ASSERT(false);
}

void test_cantMismaEspecie(){
    ASSERT(false);
}

void test_cantPokemonesTotales(){
    ASSERT(false);
}

void test_estaConectado(){
    ASSERT(false);
}

void test_sanciones(){
    ASSERT(false);
}

void test_pokemonsDelJugador(){
    ASSERT(false);
}

void test_pokemonEnPos(){
    ASSERT(false);
}

void test_coordenada_12_1(){
	Driver d(mapa_12_1());

	ASSERT(d.posExistente(Coordenada(12, 1)));
	ASSERT(d.puedoAgregarPokemon(Coordenada(12, 1)));
}

int main(int argc, char **argv){
/*  RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_agregar_pokemones);
    RUN_TEST(test_agregar_pokemones_sinJugs);
    RUN_TEST(test_agregar_pokemones_conJugs);
    RUN_TEST(test_puedoAgregarPokemon);
    RUN_TEST(test_posPokeCercano);
    RUN_TEST(test_hayPokemonCercano);
    RUN_TEST(test_entrenadoresPosibles);
    RUN_TEST(test_conectar);
    RUN_TEST(test_desconectar);
    RUN_TEST(test_indice_rareza);
    RUN_TEST(test_pokemon_cercano_coor_invalida);
    RUN_TEST(test_movimientosParaCaptura);
    RUN_TEST(test_mover_sinPokes);
    RUN_TEST(test_mover_sinPokesYSancionar);
    RUN_TEST(test_capturarSeEliminaElPokemon);
    RUN_TEST(test_sancionar_simple);
    RUN_TEST(test_sancionar_conpokerango);
    RUN_TEST(test_jugadorCorrectoEsQuienCaptura);
    RUN_TEST(test_capturarJugadorTieneNuevoPoke);
    RUN_TEST(test_capturarContadoresDeTriesEstanBien);
    RUN_TEST(test_mov_invalido_con_camino);
    RUN_TEST(test_eliminarDeJuego);
    RUN_TEST(test_mover_conPokes);
    RUN_TEST(test_mover_conPokesYCapturar);
    RUN_TEST(test_comprobarCoordenadasDelMapa);
    RUN_TEST(test_hayCamino);
	RUN_TEST(test_posExistente);
	RUN_TEST(test_puedoAgregarPokemon_vol2);
    RUN_TEST(test_puedoAgregarPokemon_espia);
	RUN_TEST(test_jugadoresNoEliminados);
	RUN_TEST(test_posicionJugador);
*/	RUN_TEST(test_posConPokemon);
/*	RUN_TEST(test_expulsados);
	RUN_TEST(test_cantMismaEspecie);
	RUN_TEST(test_cantPokemonesTotales);
	RUN_TEST(test_estaConectado);
	RUN_TEST(test_sanciones);
	RUN_TEST(test_pokemonsDelJugador);
	RUN_TEST(test_pokemonEnPos);
*/  RUN_TEST(test_coordenada_12_1);

	std::cout << "\nPara mí con estos tests ya estaría\n";


    return 0;
}
