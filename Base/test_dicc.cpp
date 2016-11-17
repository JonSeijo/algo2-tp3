#include "include/DiccString.hpp"
#include "mini_test.h"

using namespace aed2;

void test_vacio() {
	DiccString<int> d;

}

void test_definir(){
	DiccString<int> d;
	d.Definir("uno", 1);
	//ASSERT(d.Definido("uno"));
}


int main(int argc, char **argv){
  RUN_TEST(test_vacio);
  RUN_TEST(test_definir);

  return 0;
}
