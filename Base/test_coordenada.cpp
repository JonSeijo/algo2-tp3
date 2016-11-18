#include "Coordenada.cpp"
#include "mini_test.h"

using namespace aed2;

void test_vacia() {
    Coordenada c;
    ASSERT(c.Latitud() == 0);
    ASSERT(c.Longitud() == 0);
}

void test_constructor() {
    Coordenada c(5, 10);
    ASSERT(c.Latitud() == 5);
    ASSERT(c.Longitud() == 10);    
}

int main(int argc, char **argv){
    RUN_TEST(test_vacia);
    RUN_TEST(test_constructor);

    return 0;
}
