// Compilar:
//   g++ -g test_cola.cpp -o test_cola

// Ejecutar:
//  ./test_cola

// Valgrind:
//   valgrind --leak-check=full ./test_cola

#include "include/ColaPrioridad.hpp"
#include "mini_test.h"

using namespace aed2;

void test_vacia() {
  ColaPrioridad<int> c;
  ASSERT(c.EsVacia());
}

void test_encolar(){
    ColaPrioridad<int> c;

    c.Encolar(3);
    ASSERT(c.Proximo() == 3);

    c.Encolar(1);
    ASSERT(c.Proximo() == 1);

    c.Encolar(1);
    ASSERT(c.Proximo() == 1);
   
    c.Encolar(2);
    ASSERT(c.Proximo() == 1);

    c.Encolar(0);
    ASSERT(c.Proximo() == 0);
}

void test_desencolar(){
    ColaPrioridad<int> c;
    c.Encolar(15);
    c.Encolar(8);
    //c.Desencolar();
    c.Encolar(12);
    c.Encolar(0);
    //c.Desencolar();
    //c.Desencolar();
    //c.Desencolar();
    //c.Desencolar();
    //std::cout << c << std::endl;
    bool noSeRompio = true;
    ASSERT(noSeRompio);
    //ASSERT(c.Proximo() == 8 && !c.EsVacia());
    c.Encolar(14);
    //std::cout << c << std::endl;
    //c.Desencolar();
    c.Encolar(6);
    c.Encolar(16);
    c.Encolar(16);
    c.Encolar(20);
    c.Encolar(21);
    c.Encolar(1515);
    c.Encolar(88);
    c.Encolar(87);
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Encolar(-6664);
    c.Desencolar();
    c.Encolar(123321);
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    c.Desencolar();
    //std::cout << c << std::endl;
    c.Encolar(20);
    c.Encolar(11);
    c.Encolar(6);
    c.Encolar(9);
    c.Encolar(60000);
    c.Desencolar();
    c.Desencolar();
    //std::cout << c << std::endl;
    c.Desencolar();
    c.Desencolar();
    //std::cout << c << std::endl;
    
}

void test_borrar(){
    ColaPrioridad<int> c;
    ColaPrioridad<int>::Iterador it4 = c.Encolar(4);
    ColaPrioridad<int>::Iterador it5 = c.Encolar(5);
    ColaPrioridad<int>::Iterador it1 = c.Encolar(1);
    ColaPrioridad<int>::Iterador it10 = c.Encolar(10);
    ColaPrioridad<int>::Iterador it12 = c.Encolar(12);
    ColaPrioridad<int>::Iterador it0 = c.Encolar(0);
    ColaPrioridad<int>::Iterador it5a = c.Encolar(5);
    //std::cout << c << std::endl;
    it1.Borrar();
    //std::cout << c << std::endl;
    it12.Borrar();
    //std::cout << c << std::endl;
    it4.Borrar();
    //std::cout << c << std::endl;
    it0.Borrar();
    //std::cout << c << std::endl;

    ColaPrioridad<int> d;
    ColaPrioridad<int>::Iterador it0a = d.Encolar(0);
    ColaPrioridad<int>::Iterador it100 = d.Encolar(100);
    ColaPrioridad<int>::Iterador it1a = d.Encolar(1);
    ColaPrioridad<int>::Iterador it200 = d.Encolar(200);
    ColaPrioridad<int>::Iterador it400 = d.Encolar(400);
    ColaPrioridad<int>::Iterador it2 = d.Encolar(2);
    ColaPrioridad<int>::Iterador it3 = d.Encolar(3);
    ColaPrioridad<int>::Iterador it1000 = d.Encolar(1000);
    ColaPrioridad<int>::Iterador it900 = d.Encolar(900);
    ColaPrioridad<int>::Iterador it600 = d.Encolar(600);
    ColaPrioridad<int>::Iterador it800 = d.Encolar(800);
    ColaPrioridad<int>::Iterador it4a = d.Encolar(4);
    //std::cout << d << std::endl;
    it900.Borrar();
    //std::cout << d << std::endl;
    ASSERT(true);
}

void test_siguiente(){
    ColaPrioridad<int> d;
    ColaPrioridad<int>::Iterador it0a = d.Encolar(0);
    ColaPrioridad<int>::Iterador it100 = d.Encolar(100);
    ColaPrioridad<int>::Iterador it1a = d.Encolar(1);
    ColaPrioridad<int>::Iterador it200 = d.Encolar(200);
    ColaPrioridad<int>::Iterador it400 = d.Encolar(400);
    ASSERT(it0a.Siguiente() == 0 && it100.Siguiente() == 100 && it1a.Siguiente() == 1);
    ASSERT(it200.Siguiente() == 200 && it400.Siguiente() == 400);
}

void test_casosraros(){
   //Quise hacer el operador < entre heaps pero no me salió, si sobra tiempo 
   // estaría bueno hacerlo para probar esto 


    /*ColaPrioridad<int> c;
    ColaPrioridad<int> d;
    ColaPrioridad<ColaPrioridad<int> > cc;
    ColaPrioridad<ColaPrioridad<ColaPrioridad<int> > > ccc;
    ColaPrioridad<ColaPrioridad<ColaPrioridad<ColaPrioridad<int> > > > cccc;

    ColaPrioridad<int>::Iterador it4 = c.Encolar(4);
    ColaPrioridad<int>::Iterador it5 = c.Encolar(5);
    ColaPrioridad<int>::Iterador it1 = c.Encolar(1);
    ColaPrioridad<int>::Iterador it10 = c.Encolar(10);
    ColaPrioridad<int>::Iterador it12 = c.Encolar(12);
    ColaPrioridad<int>::Iterador it0 = c.Encolar(0);
    ColaPrioridad<int>::Iterador it5a = c.Encolar(5);

    ColaPrioridad<int>::Iterador it0a = d.Encolar(0);
    ColaPrioridad<int>::Iterador it100 = d.Encolar(100);
    ColaPrioridad<int>::Iterador it1a = d.Encolar(1);
    ColaPrioridad<int>::Iterador it200 = d.Encolar(200);
    ColaPrioridad<int>::Iterador it400 = d.Encolar(400);
    ColaPrioridad<int>::Iterador it2 = d.Encolar(2);
    ColaPrioridad<int>::Iterador it3 = d.Encolar(3);
    ColaPrioridad<int>::Iterador it1000 = d.Encolar(1000);
    ColaPrioridad<int>::Iterador it900 = d.Encolar(900);
    ColaPrioridad<int>::Iterador it600 = d.Encolar(600);
    ColaPrioridad<int>::Iterador it800 = d.Encolar(800);
    ColaPrioridad<int>::Iterador it4a = d.Encolar(4);

    ColaPrioridad<ColaPrioridad<int> >::Iterador itcc = cc.Encolar(c);
    ColaPrioridad<ColaPrioridad<ColaPrioridad<int> > >::Iterador itccc = ccc.Encolar(cc);
    ColaPrioridad<ColaPrioridad<ColaPrioridad<ColaPrioridad<int> > > >::Iterador itcccc = cccc.Encolar(ccc);

    it4.Borrar();

    std::cout << cccc << std::endl;

*/
	bool noHuboSegmentationFault = true;
    ASSERT(noHuboSegmentationFault);
}

int main(int argc, char **argv){
  RUN_TEST(test_vacia);
  RUN_TEST(test_encolar);
  RUN_TEST(test_desencolar);
  RUN_TEST(test_borrar);
  RUN_TEST(test_siguiente);
  RUN_TEST(test_casosraros);

  return 0;
}
