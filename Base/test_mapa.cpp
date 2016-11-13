// Compilar usando:
//	g++ -o tests_mapa tests_mapa.cpp Mapa.cpp 
//	valgrind --leak-check=full ./tests

#include "include/Mapa.h"
#include "mini_test.h"

using namespace aed2;

void test_vacio() {
  ASSERT( false );
}

void test_agregar_coordenada(){
	ASSERT( false );
}


int main(int argc, char **argv){
  RUN_TEST(test_vacio);
  RUN_TEST(test_agregar_coordenada);

  return 0;
}
