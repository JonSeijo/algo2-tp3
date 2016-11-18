// Compilar:
//   g++ -g test_cola.cpp -o test_cola

// Ejecutar:
//  ./test_cola

// Valgrind:
//   valgrind --leak-check=full ./test_cola

#include "include/ColaPrioridad.hpp"
#include "mini_test.h"

using namespace aed2;

void test_vacia() {
  ColaPrioridad<int> c;
  ASSERT(c.EsVacia());
}

void test_encolar(){
    ColaPrioridad<int> c;

    c.Encolar(3);
    ASSERT(c.Proximo() == 3);

    c.Encolar(1);
    ASSERT(c.Proximo() == 1);

    c.Encolar(1);
    ASSERT(c.Proximo() == 1);
   
    c.Encolar(2);
    ASSERT(c.Proximo() == 1);

    c.Encolar(0);
    ASSERT(c.Proximo() == 0);
}

void test_desencolar(){
    ColaPrioridad<int> c;
    c.Encolar(15);
    c.Encolar(8);
    //c.Desencolar();
    c.Encolar(12);
    c.Encolar(0);
    //c.Desencolar();
    //c.Desencolar();
    //c.Desencolar();
    //c.Desencolar();
    //std::cout << c << std::endl;
    bool noSeRompio = true;
    ASSERT(noSeRompio);
    //ASSERT(c.Proximo() == 8 && !c.EsVacia());
    c.Encolar(14);
    //std::cout << c << std::endl;
    //c.Desencolar();
    c.Encolar(6);
    c.Encolar(16);
    c.Encolar(16);
    c.Encolar(20);
    c.Encolar(21);
    c.Encolar(1515);
    c.Encolar(88);
    c.Encolar(87);
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Encolar(-6664);
    c.Desencolar();
    c.Encolar(123321);
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    //std::cout << c << std::endl;
    c.Encolar(20);
    c.Encolar(11);
    c.Encolar(6);
    c.Encolar(9);
    c.Encolar(60000);
    c.Desencolar();
    c.Desencolar();
    //std::cout << c << std::endl;
    c.Desencolar();
    c.Desencolar();
    //std::cout << c << std::endl;
    
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
  // RUN_TEST(test_borrar);
  // RUN_TEST(test_siguiente);
  // RUN_TEST(test_casosraros);

  return 0;
}
