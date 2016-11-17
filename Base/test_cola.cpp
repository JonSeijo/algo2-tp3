
#include "include/ColaPrioridad.hpp"
#include "mini_test.h"

using namespace aed2;

void test_vacia() {
  ColaPrioridad<int> c;
  ASSERT(c.EsVacia());
}

void test_encolar(){
  ColaPrioridad<int> c;
  c.Encolar(20);
  c.Encolar(10);
  c.Encolar(30);
  //c.Encolar(3);
  //c.Encolar(0);
  c.Encolar(40);
  c.Encolar(15);
  //c.Encolar(1);
  //c.Encolar(-6);


  std::cout << c << std::endl;
	//ASSERT(true);
}

void test_desencolar(){
	ASSERT( false );
}

void test_borrar(){
	ASSERT( false );
}

void test_siguiente(){
	ASSERT( false );
}

void test_casosraros(){
	ASSERT( false );
}

int main(int argc, char **argv){
  RUN_TEST(test_vacia);
  RUN_TEST(test_encolar);
  RUN_TEST(test_desencolar);
  RUN_TEST(test_borrar);
  RUN_TEST(test_siguiente);
  RUN_TEST(test_casosraros);

  return 0;
}
