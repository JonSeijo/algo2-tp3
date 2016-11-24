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
    // COPIPASTIE A MANO
    
    Driver d(mapaTipo0());
    Conj<Coordenada> coordDeMapa = d.mapa();
    Conj<Coordenada>::Iterador it = coordDeMapa.CrearIt();
    Pokemon pikachu = "Pikachu";
    Pokemon charmander = "Charmander";
    Pokemon agumon = "Agumon";
    Pokemon caracteresRaros = "2$&&/&(/&020.202}{{[^`~~'¿?'¿¿'";
    std::cout << "Agrego pikachu en la coordenada: " << it.Siguiente() << std::endl;
    Coordenada coorPikachu = it.Siguiente();
    d.agregarPokemon(pikachu, it.Siguiente());
    it.Avanzar();
    //En el mapa hay dos coordenadas, pongo al pikachu en una y me fijo si es la pos cercana de la otra
    //Faltan 40 mil cosas todavía, pero es un avance (?)
    std::cout << "Coordenada libre: " << it.Siguiente() << std::endl;
    ASSERT(d.posPokemonCercano(it.Siguiente()) == coorPikachu);

    Jugador AshKetchup = d.agregarJugador();
    d.conectarse(AshKetchup, it.Siguiente());
    d.moverse(AshKetchup, coorPikachu);
    d.moverse(AshKetchup, it.Siguiente());
    ASSERT(d.jugadores().Pertenece(AshKetchup));
    std::cout << "Hasta acá no se rompió nada" << std::endl;
    ASSERT(d.cantMovimientosParaCaptura(d.posPokemonCercano(d.posicion(AshKetchup))) == 8);
}


void test_puedoAgregarPokemon() {
    ASSERT(false);
}

// Esto se va a poner feo
void test_agregar_pokemones_sinJugs(){
    Driver d(mapaTipo1());
    ASSERT(false);
}

void test_agregar_pokemones_conJugs(){
    Driver d(mapaTipo1());
    ASSERT(false);
}

void test_hayPokemonCercano() {
    Driver d(mapaTipo1());

}

void test_posPokeCercano() {
    ASSERT(false);
}

void test_entrenadoresPosibles() {
    ASSERT(false);
}

void test_conectar() {    
    ASSERT(false);
}

void test_desconectar() {    
    ASSERT(false);
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
    ASSERT(false);
}



int main(int argc, char **argv){
    RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_agregar_pokemones);
    RUN_TEST(test_agregar_pokemones_sinJugs);
    RUN_TEST(test_agregar_pokemones_conJugs);
    RUN_TEST(test_puedoAgregarPokemon); 
    RUN_TEST(test_agregar_pokemones_sinJugs);
    RUN_TEST(test_agregar_pokemones_conJugs);
    RUN_TEST(test_posPokeCercano); 
    RUN_TEST(test_hayPokemonCercano); 
    RUN_TEST(test_entrenadoresPosibles); 
    RUN_TEST(test_conectar);     
    RUN_TEST(test_desconectar);     
    RUN_TEST(test_mover_sinPokes);     
    RUN_TEST(test_mover_sinPokesYSancionar);     
    RUN_TEST(test_mover_conPokes);     
    RUN_TEST(test_mover_conPokesYCapturar);     
    RUN_TEST(test_indice_rareza); 

    std:cout << "HAY QUE HACER UN TEST PARA CADA METODO PUBLICO. FALTAN MAS DE LOS QUE HAY\n";

    return 0;
}
