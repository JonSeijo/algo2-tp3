#include <iostream>
#include "include/DiccString.hpp"
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


int main(int argc, char **argv){
    RUN_TEST(test_vacio);
    RUN_TEST(test_definir);

    // Habria que hacer tambien tests de iterador
    return 0;
}
