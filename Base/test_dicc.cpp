#include "include/DiccString.hpp"
#include "mini_test.h"

using namespace aed2;

void test_vacio() {
  	ASSERT( false );
}

void test_definir(){
	ASSERT( false );
}


int main(int argc, char **argv){
  RUN_TEST(test_vacio);
  RUN_TEST(test_definir);

  return 0;
}
