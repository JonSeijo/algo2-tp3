// Compilar usando:
//   g++ -g test_mapa.cpp Mapa.cpp -o test_mapa

// Ejecutar:
//   ./test_mapa

// Valgrind
//    valgrind --leak-check=full ./test_mapa


// #include "include/Coordenada.h"
#include "include/Mapa.h"
#include "mini_test.h"

using namespace aed2;

void test_vacio() {
    Mapa map;
    ASSERT(map.Tam() == 0);
    ASSERT(map.Coordenadas().EsVacio());
}

void test_agregar_coordenada_tam(){
    Mapa map;
    map.AgregarCoord(Coordenada(5,5));
    map.AgregarCoord(Coordenada(1,1));
    ASSERT(map.Tam() == 6);
    map.AgregarCoord(Coordenada(9,9));
    ASSERT(map.Tam() == 10);
    map.AgregarCoord(Coordenada(10,9));
    ASSERT(map.Tam() == 11);
    
}

void test_posExistente() {
    ASSERT( false );
}

void test_hayCamino() {
    ASSERT( false );
}

void test_tam() {
    ASSERT( false );
}

int main(int argc, char **argv){
    RUN_TEST(test_vacio);
    RUN_TEST(test_agregar_coordenada_tam);
    RUN_TEST(test_posExistente);
    RUN_TEST(test_hayCamino);
    RUN_TEST(test_tam);

    return 0;
}
