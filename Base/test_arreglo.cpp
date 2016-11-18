// Compilar:
//  g++ -g test_arreglo.cpp -o test_arr

// Ejecutar:
//  ./test_arr

// Valgrind:
//   valgrind --leak-check=full ./test_arr

#include "./aed2/Arreglo.h"
#include "mini_test.h"

using namespace aed2;

void test_vacia() {
    ASSERT(true);
}

void test_constructor() {
    ASSERT(true);
}

int main(int argc, char **argv){
    RUN_TEST(test_vacia);
    RUN_TEST(test_constructor);
    return 0;
}
