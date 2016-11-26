// Compilar usando:
//   g++ -g test_mapa.cpp Mapa.cpp -o test_mapa

// Ejecutar:
//   ./test_mapa

// Valgrind
//    valgrind --leak-check=full ./test_mapa


// #include "include/Coordenada.h"
//#include "include/Mapa.h"
#include "Mapa.cpp"
#include "mini_test.h"

using namespace aed2;

void test_vacio() {
    Mapa map;
    ASSERT(map.Tam() == 0);
    ASSERT(map.Coordenadas().EsVacio());
}

void test_agregar_coordenada_tam(){
    Mapa map;
    map.AgregarCoord(Coordenada(1,1));
    map.AgregarCoord(Coordenada(0,1));  
    map.AgregarCoord(Coordenada(1,0));  

    map.AgregarCoord(Coordenada(5,5));
    ASSERT(map.Tam() == 6);
    map.AgregarCoord(Coordenada(9,9));
    ASSERT(map.Tam() == 10);
    map.AgregarCoord(Coordenada(10,9));
    ASSERT(map.Tam() == 11);   
    map.AgregarCoord(Coordenada(10,11));
    ASSERT(map.Tam() == 12);   
    map.AgregarCoord(Coordenada(11,11));
    ASSERT(map.Tam() == 12);   
    map.AgregarCoord(Coordenada(11,10));
    ASSERT(map.Tam() == 12);   
}

void test_tam() {
    // Testeado indirectamente con el agregarCoordenada
    Mapa map;
    ASSERT(map.Tam() == 0);
}

void test_posExistente() {
    Mapa map;
    map.AgregarCoord(Coordenada(1,1));
    ASSERT(map.PosExistente(Coordenada(1,1)));
    ASSERT(!map.PosExistente(Coordenada(0,0)));
    ASSERT(!map.PosExistente(Coordenada(0,1)));
    ASSERT(!map.PosExistente(Coordenada(1,0)));
    ASSERT(!map.PosExistente(Coordenada(2,2)));

    map.AgregarCoord(Coordenada(5,5));
    ASSERT(map.PosExistente(Coordenada(1,1)));
    ASSERT(map.PosExistente(Coordenada(5,5)));
    ASSERT(!map.PosExistente(Coordenada(0,0)));
    ASSERT(!map.PosExistente(Coordenada(0,1)));
    ASSERT(!map.PosExistente(Coordenada(1,0)));
    ASSERT(!map.PosExistente(Coordenada(2,2)));
    
    map.AgregarCoord(Coordenada(5,5));
    ASSERT(map.PosExistente(Coordenada(1,1)));
    ASSERT(map.PosExistente(Coordenada(5,5)));
    ASSERT(!map.PosExistente(Coordenada(0,0)));
    ASSERT(!map.PosExistente(Coordenada(0,1)));
    ASSERT(!map.PosExistente(Coordenada(1,0)));
    ASSERT(!map.PosExistente(Coordenada(2,2)));
    
    map.AgregarCoord(Coordenada(3,3));
    ASSERT(map.PosExistente(Coordenada(1,1)));
    ASSERT(map.PosExistente(Coordenada(3,3)));
    ASSERT(map.PosExistente(Coordenada(5,5)));
    ASSERT(!map.PosExistente(Coordenada(0,0)));
    ASSERT(!map.PosExistente(Coordenada(0,1)));
    ASSERT(!map.PosExistente(Coordenada(1,0)));
    ASSERT(!map.PosExistente(Coordenada(2,2)));
}

void test_hayCamino_casoFeliz() {
    Mapa map;
    // Casos comunes funcionan bien
    map.AgregarCoord(Coordenada(0,1));
    map.AgregarCoord(Coordenada(1,1));
    map.AgregarCoord(Coordenada(0,0));
    ASSERT(map.HayCamino(Coordenada(0,1), Coordenada(1,1)));
    ASSERT(map.HayCamino(Coordenada(0,0), Coordenada(0,1)));
    ASSERT(map.HayCamino(Coordenada(0,0), Coordenada(1,1)));

    // Vale si pregunto con las coordenadas invertidas
    ASSERT(map.HayCamino(Coordenada(1,1), Coordenada(0,1)));
    ASSERT(map.HayCamino(Coordenada(0,1), Coordenada(0,0)));
    ASSERT(map.HayCamino(Coordenada(1,1), Coordenada(0,0)));
}

void test_hayCamino_casoTriste() {
    Mapa map;

    // Caso que no actualiza viejos del medio vertical
    map.AgregarCoord(Coordenada(0,0));
    map.AgregarCoord(Coordenada(0,2));
    ASSERT(!map.HayCamino(Coordenada(0,0), Coordenada(0,2)));
    map.AgregarCoord(Coordenada(0,1));
    // map.imprimir();
    // Deberia haber camino entre el (0,0) y el (0,2) pues ahora hay una coordenada entre ellos
    ASSERT(map.HayCamino(Coordenada(0,0), Coordenada(0,2)));
    ASSERT(map.HayCamino(Coordenada(0,0), Coordenada(0,1)));
    ASSERT(map.HayCamino(Coordenada(0,2), Coordenada(0,1)));

    // El HyaCamino funciona en ambas direcciones
    ASSERT(map.HayCamino(Coordenada(0,2), Coordenada(0,0)));
    ASSERT(map.HayCamino(Coordenada(0,1), Coordenada(0,0)));
    ASSERT(map.HayCamino(Coordenada(0,1), Coordenada(0,2)));


    // Caso que no actualiza viejos del medio horizontal
    map.AgregarCoord(Coordenada(5,5));
    map.AgregarCoord(Coordenada(7,5));
    ASSERT(!map.HayCamino(Coordenada(5,5), Coordenada(7,5)));
    map.AgregarCoord(Coordenada(6,5));
    ASSERT(map.HayCamino(Coordenada(5,5), Coordenada(7,5)));
}

int main(int argc, char **argv){
    RUN_TEST(test_vacio);
    RUN_TEST(test_agregar_coordenada_tam);
    RUN_TEST(test_tam);
    RUN_TEST(test_posExistente);
    RUN_TEST(test_hayCamino_casoFeliz);
    RUN_TEST(test_hayCamino_casoTriste);

    return 0;
}
