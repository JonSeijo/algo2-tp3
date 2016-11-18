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

// Arreglo.Definir(pos, valor)
void test_definir() {
    // Arreglo comun
    Arreglo<Nat> a(10);
    a.Definir(0, 99);
    a.Definir(1, 99);
    ASSERT(a.Definido(0));
    ASSERT(a.Definido(1));
    ASSERT(a.Tamanho() == 10);

    // Arreglo de punteros

    // // ASI SON LEAKS
    // // HAY QUE HACER DELETE A MANOPLA
    // Arreglo<Nat*> b(10);
    // b.Definir(0, new Nat(9999));
    // b.Definir(1, new Nat(9999));
    // ASSERT(b.Definido(0));
    // ASSERT(b.Definido(1));
    // ASSERT(b.Tamanho() == 10);

    // Haciendo deletes a mano no hay leaks
    Arreglo<Nat*> c(10);
    Nat* test1 = new Nat(999);
    Nat* test2 = new Nat(999);
    c.Definir(0, test1);
    c.Definir(1, test2);
    ASSERT(c.Definido(0));
    ASSERT(c.Definido(1));
    ASSERT(c.Tamanho() == 10);

    delete test1;
    delete test2;
}

int main(int argc, char **argv){
    RUN_TEST(test_vacia);
    RUN_TEST(test_constructor);
    RUN_TEST(test_definir);
    return 0;
}
