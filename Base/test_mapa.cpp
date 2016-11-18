// Compilar usando:
//   g++ -g test_mapa.cpp Mapa.cpp Coordenada.cpp -o test_mapa

// Ejecutar:     
//   ./test_mapa

// Valgrind
//    valgrind --leak-check=full ./test_mapa


#include "include/Coordenada.h"
#include "include/Mapa.h"
#include "mini_test.h"

using namespace aed2;

void test_vacio() {
    Mapa map;
    ASSERT(map.Tam() == 0);
    ASSERT(map.Coordenadas().EsVacio());
}

void test_agregar_coordenada(){
    ASSERT( false );
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
    RUN_TEST(test_agregar_coordenada);
    RUN_TEST(test_posExistente);
    RUN_TEST(test_hayCamino);
    RUN_TEST(test_tam);

    return 0;
}
