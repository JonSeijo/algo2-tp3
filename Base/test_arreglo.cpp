// Compilar:
//  g++ -g test_arreglo.cpp -o test_arr

// Ejecutar:
//  ./test_arr

// Valgrind:
//   valgrind --leak-check=full ./test_arr

#include "./aed2/TiposBasicos.h"
#include "./aed2/Arreglo.h"
#include "mini_test.h"

using namespace aed2;

// LA IDEA SERIA TESTEAR PRINCIPALMENTE ARRAYS DE PUNTEROS

void test_vacia() {
    Arreglo<Nat> a;
    ASSERT(a.Tamanho() == 0);

    Arreglo<Nat*> b;
    ASSERT(b.Tamanho() == 0);
}

void test_constructor() {
    Arreglo<Nat> a(10);
    ASSERT(a.Tamanho() == 10);

    Arreglo<Nat*> b(10);
    ASSERT(b.Tamanho() == 10);

    for (int i = 0; i < b.Tamanho(); i++) {
        ASSERT(!b.Definido(i));
    }
}

int main(int argc, char **argv){
    RUN_TEST(test_vacia);
    RUN_TEST(test_constructor);
    return 0;
}
