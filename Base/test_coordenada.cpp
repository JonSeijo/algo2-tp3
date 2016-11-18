// Compilar:
//  g++ -g test_coordenada.cpp -o test_coor

// Ejecutar:
//  ./test_coor

// Valgrind:
//   valgrind --leak-check=full ./test_coor

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

void test_direcciones() {
    Coordenada c1(1, 1);
    Coordenada c1_izq(0, 1);
    ASSERT(c1.CoordenadaALaIzquierda() == c1_izq);    

    Coordenada c2(1, 1);
    Coordenada c2_der(2, 1);
    ASSERT(c2.CoordenadaALaDerecha() == c2_der);    

    Coordenada c3(1, 1);
    Coordenada c3_arr(1, 2);
    ASSERT(c3.CoordenadaArriba() == c3_arr);    

    Coordenada c4(1, 1);
    Coordenada c4_aba(1, 0);
    ASSERT(c4.CoordenadaAbajo() == c4_aba);    
}

int main(int argc, char **argv){
    RUN_TEST(test_vacia);
    RUN_TEST(test_constructor);
    RUN_TEST(test_distEuclid);
    RUN_TEST(test_igualdad);
    RUN_TEST(test_direcciones);

    return 0;
}
