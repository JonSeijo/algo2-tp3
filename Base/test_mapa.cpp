// Compilar usando:
//	g++ -o tests_mapa tests_mapa.cpp Mapa.cpp 
//	valgrind --leak-check=full ./tests

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
