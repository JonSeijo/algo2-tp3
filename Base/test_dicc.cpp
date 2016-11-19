#include <iostream>
#include "./include/DiccString.hpp"
// #include "./include/DiccStringOriginal.hpp"
#include "mini_test.h"

using namespace aed2;

void test_vacio() {
    DiccString<int> d;
    ASSERT(!d.Definido(""));
    ASSERT(!d.Definido("uno"));
    ASSERT(!d.Definido("sarasa"));
    ASSERT(d.CantClaves() == 0);
}

void test_definir(){
    DiccString<int> d;
    d.Definir("uno", 1);
    ASSERT(d.Definido("uno"));
    ASSERT(d.CantClaves() == 1);
    d.Definir("uno", 2);
    ASSERT(d.Definido("uno"));
    ASSERT(d.CantClaves() == 1);

    d.Definir("tres", 3);
    ASSERT(d.Definido("tres"));
    ASSERT(d.CantClaves() == 2);


    d.Definir("trese", 33);
    ASSERT(d.Definido("trese"));
    ASSERT(d.CantClaves() == 3);

    d.Definir("tre", 333);
    ASSERT(d.Definido("tre"));
    ASSERT(d.CantClaves() == 4);

    d.Definir("c", 5);
    ASSERT(d.Definido("c"));
    ASSERT(d.CantClaves() == 5);
}

void test_significado() {
    DiccString<int> d;
    d.Definir("uno", 1);
    ASSERT(d.Significado("uno") == 1);
    d.Definir("uno", 2);
    ASSERT(d.Significado("uno") == 2);
    d.Definir("cinco", 5);
    ASSERT(d.Significado("cinco") == 5);
}

void test_borrar() {
    DiccString<int> d;
    d.Definir("uno", 1);
    d.Borrar("uno");
    ASSERT(!d.Definido("uno"));
    ASSERT(d.CantClaves() == 0);


    d.Definir("dos", 2);
    ASSERT(d.Definido("dos"));
    ASSERT(d.CantClaves() == 1);
    d.Borrar("dos");
    ASSERT(!d.Definido("dos"));
    ASSERT(d.CantClaves() == 0);
}

int main(int argc, char **argv){
    RUN_TEST(test_vacio);
    RUN_TEST(test_definir);
    RUN_TEST(test_significado);
    RUN_TEST(test_borrar);

    // Habria que hacer tambien tests de iterador
    return 0;
}
