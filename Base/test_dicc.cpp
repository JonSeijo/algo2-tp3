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

}


int main(int argc, char **argv){
    RUN_TEST(test_vacio);
    // RUN_TEST(test_definir);

    // Habria que hacer tambien tests de iterador
    return 0;
}
