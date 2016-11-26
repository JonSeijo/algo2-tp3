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

Conj<Coordenada> mapaTipo2() {
    // ES UN MAPA 12x12 TODO LLENO
    Conj<Coordenada> cc;
    for (int i = 12; i >= 0; i--) {
        for (int j = 12; j >= 0; j--) {
            ag(cc, i, j);
        }
    }
    return cc;
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

void test_puedoAgregar_vol2() {
    Driver d(mapaTipo2());

    // Puedo agregar en las esquinas    
    ASSERT(d.puedoAgregarPokemon(Coordenada(0,0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(12,12)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(12,0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(0,12)));

    // Puedo agregar en bordes
    ASSERT(d.puedoAgregarPokemon(Coordenada(12,6)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(0,6)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(6,0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(6,12)));

    // Puedo agregar en centro
    ASSERT(d.puedoAgregarPokemon(Coordenada(6,6)));

    // No puedo agregar fuera del mapa
    ASSERT(!d.puedoAgregarPokemon(Coordenada(20,20)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(13,12)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(12,13)));

    // Agrego poke al (0,0)
    d.agregarPokemon("Magicarp", Coordenada(0,0));


    /* En las 'o' se puede

      0 1 2 3 4 5
    0 X - - - - o
    1 - - - - - o
    2 - - - - - o
    3 - - - - - o
    4 - - - - o o
    5 o o o o o o 

    */

    // No puedo agregar pokemon en un rango <= 5 del 0
    ASSERT(!d.puedoAgregarPokemon(Coordenada(0,0)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(0,4)));   
    ASSERT(!d.puedoAgregarPokemon(Coordenada(4,0)));   
    ASSERT(!d.puedoAgregarPokemon(Coordenada(3,1)));   
    ASSERT(!d.puedoAgregarPokemon(Coordenada(1,3)));   
    ASSERT(!d.puedoAgregarPokemon(Coordenada(2,2)));
    
    ASSERT(!d.puedoAgregarPokemon(Coordenada(1,1)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(1,0)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(0,1)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(4,3)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(3,4)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(3,2)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(2,3)));

    ASSERT(d.puedoAgregarPokemon(Coordenada(4,4)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(5,0)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(0,5)));





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


void test_puedoAgregarPokemon() {
    Driver conductor(mapaTipo0());

    ASSERT(conductor.puedoAgregarPokemon(Coordenada(1, 1)) && conductor.puedoAgregarPokemon(Coordenada(2, 2)));

    conductor.agregarPokemon("Ernesto", Coordenada(2, 2));

    ASSERT(!conductor.puedoAgregarPokemon(Coordenada(1, 1)) && !conductor.puedoAgregarPokemon(Coordenada(2, 2)));

    Driver d(mapaTipo1());

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

    d.agregarPokemon("{}{}{}{}", Coordenada(3, 4));

    // Distancia <= 5 segun el bot
    ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 0)));
 
    ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 1)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(0, 2)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 0)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 1)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(1, 2)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 0)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 1)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 2)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 3)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(2, 4)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 2)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 3)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(3, 4)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 2)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 3)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 4)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(4, 5)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 5)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 6)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(5, 7)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 5)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 6)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(6, 7)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 5)));
    ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 6)));

    // Distancia <= 5 segun el bot
    ASSERT(!d.puedoAgregarPokemon(Coordenada(7, 7)));

    ASSERT(d.puedoAgregarPokemon(Coordenada(9, 9)));

    // No podia agregar pokemon en el 7,7 segun el bot !!!

    // d.agregarPokemon("{}{}{}{}", Coordenada(7, 7));
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
    //TERMINAR

    Driver d(mapaTipo1());

    d.agregarPokemon("Cartucho de tinta negro 117 Epson", Coordenada(2, 2));

    //AshSalsaGolf es la fusión entre AshKetchup y AshMayonesa
    Jugador AshSalsaGolf = d.agregarJugador();
    Jugador AshAdhereso = d.agregarJugador();

    d.conectarse(AshSalsaGolf, Coordenada(2, 2));
    d.conectarse(AshAdhereso, Coordenada(2, 1));

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

    std::cout << "Entro al ultimo moverse\n";
    
    d.moverse(AshSalsaGolf, Coordenada(4, 5));
    
    std::cout << "Salgo del ultimo moverse\n";

    ASSERT(!d.hayPokemonCercano(Coordenada(2, 2)));
    ASSERT(d.puedoAgregarPokemon(Coordenada(2, 2)));


    ASSERT(true);
}

void test_jugadorCorrectoEsQuienCaptura() {
    ASSERT(false);
}

void test_capturarJugadorTieneNuevoPoke() {
    ASSERT(false);
}

void test_capturarContadoresDeTriesEstanBien() {
    ASSERT(false);
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

    // Por que chequea EsVacio? no deberia ser maquinaOrga1 un entrenador posible?
    // ASSERT(e.entrenadoresPosibles(Coordenada(6, 5)).EsVacio());

    ASSERT(e.entrenadoresPosibles(Coordenada(2, 1)).EsVacio());

    // Ya no puedo agregar este pokemon
    // ASSERT(e.puedoAgregarPokemon(Coordenada(9, 9)));

    // e.agregarPokemon("Taller De Haskell", Coordenada(9, 9));

    // Jugador HojasA4 = e.agregarJugador();
    // e.conectarse(HojasA4, Coordenada(7, 7));
    // e.moverse(HojasA4, Coordenada(9, 9));
    // e.moverse(HojasA4, Coordenada(1, 1));
    // e.moverse(HojasA4, Coordenada(3, 2));
    // e.moverse(MaquinaOrga1, Coordenada(9, 9));
    // e.desconectarse(HojasA4);
    // e.desconectarse(MaquinaOrga1);
    // e.conectarse(HojasA4, Coordenada(9, 9));
    // e.conectarse(MaquinaOrga1, Coordenada(9, 9));
    // e.conectarse(Cache, Coordenada(9, 9));

    // ASSERT(e.entrenadoresPosibles(Coordenada(9, 9)).Pertenece(Cache) && e.entrenadoresPosibles(Coordenada(9, 9)).Pertenece(HojasA4) && e.entrenadoresPosibles(Coordenada(9, 9)).Pertenece(MaquinaOrga1));
    // ASSERT(e.entrenadoresPosibles(Coordenada(6, 5)).EsVacio());
    // ASSERT(e.entrenadoresPosibles(Coordenada(2, 1)).EsVacio());
}

void test_sancionar() {
    ASSERT(false);
}

void test_eliminarDeJuego() {
    ASSERT(false);
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
    ASSERT(false);
}

void test_mover_sinPokesYSancionar() {
    ASSERT(false);
}

void test_mover_conPokes() {
    ASSERT(false);
}

void test_mover_conPokesYCapturar() {
    ASSERT(false);
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

// TODO: Agregar más tests


int main(int argc, char **argv){
    RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_agregar_pokemones);
    RUN_TEST(test_agregar_pokemones_sinJugs);
    RUN_TEST(test_agregar_pokemones_conJugs);
    RUN_TEST(test_puedoAgregarPokemon);
    RUN_TEST(test_puedoAgregar_vol2);
    RUN_TEST(test_posPokeCercano);
    RUN_TEST(test_hayPokemonCercano);
    RUN_TEST(test_entrenadoresPosibles);
    RUN_TEST(test_conectar);
    RUN_TEST(test_desconectar);
    RUN_TEST(test_indice_rareza);
    RUN_TEST(test_pokemon_cercano_coor_invalida);
    RUN_TEST(test_movimientosParaCaptura);

    RUN_TEST(test_capturarSeEliminaElPokemon);
/*    RUN_TEST(test_jugadorCorrectoEsQuienCaptura);
    RUN_TEST(test_capturarJugadorTieneNuevoPoke);
    RUN_TEST(test_capturarContadoresDeTriesEstanBien);
    RUN_TEST(test_sancionar);
    RUN_TEST(test_eliminarDeJuego);
    RUN_TEST(test_mover_sinPokes);
    RUN_TEST(test_mover_sinPokesYSancionar);
    RUN_TEST(test_mover_conPokes);
    RUN_TEST(test_mover_conPokesYCapturar);
*/

    // std:cout << "HAY QUE HACER UN TEST PARA CADA METODO PUBLICO. FALTAN MAS DE LOS QUE HAY\n";

    return 0;
}
