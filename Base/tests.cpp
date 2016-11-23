// Compilar usando:
//  g++ -g tests.cpp Driver.cpp -o tests
//  valgrind --leak-check=full ./tests

#include <iostream>
#include "Driver.h"
#include "modulos.h"
#include "mini_test.h"

using namespace aed2;

void test_constructor_con_mapa() {
    Conj<Coordenada> cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(0,1));
    cc.Agregar(Coordenada(0,2));
    cc.Agregar(Coordenada(1,2));
    cc.Agregar(Coordenada(10,0));
    cc.Agregar(Coordenada(1,4));
    Driver d(cc);

    // d.mapa() ya tira las coordenadas... weird
    ASSERT( d.mapa() == cc );
}

void test_agregar_jugadores(){
    Conj<Coordenada> cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(0,1));
    cc.Agregar(Coordenada(0,2));
    cc.Agregar(Coordenada(1,2));
    cc.Agregar(Coordenada(10,0));
    cc.Agregar(Coordenada(1,4));
    Driver d(cc);

    Jugador e = d.agregarJugador();

    ASSERT(e == 0);

    ASSERT(!d.estaConectado(e));
    ASSERT(d.sanciones(e) == 0);

    ASSERT(d.jugadores().Pertenece(e));
    ASSERT(!d.expulsados().Pertenece(e));


}

void test_agregar_pokemones(){
    ASSERT( false );
}

// TODO: Agregar más tests


int main(int argc, char **argv){
    RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_agregar_pokemones);

    return 0;
}
