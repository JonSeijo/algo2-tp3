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

void test_distEuclid() {
    Coordenada c1(0, 0);    
    Coordenada c2(0, 2);
    ASSERT(c1.DistEuclidea(c2) == 4);    

    Coordenada c3(0, 0);    
    Coordenada c4(2, 0);
    ASSERT(c3.DistEuclidea(c4) == 4);    
}

void test_igualdad() {
    Coordenada c1(0, 0);    
    Coordenada c2(0, 2);
    ASSERT(c1 != c2);    

    Coordenada c3(2, 2);    
    Coordenada c4(2, 2);
    ASSERT(c3 == c4);    
}

int main(int argc, char **argv){
    RUN_TEST(test_vacia);
    RUN_TEST(test_constructor);
    RUN_TEST(test_distEuclid);
    RUN_TEST(test_igualdad);

    return 0;
}
