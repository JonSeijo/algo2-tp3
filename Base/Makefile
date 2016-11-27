SOURCES = tests.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS = modulos.h aed2.h Juego.cpp Mapa.cpp

TARGET = tests

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	./$(TARGET)

all: $(TARGET)

test_mapa: Mapa.o
	$(CXX) -o test_mapa test_mapa.cpp Mapa.o
	./test_mapa

test_cola: 
	$(CXX) -o test_cola test_cola.cpp 
	./test_cola

test_dicc: 
	$(CXX) -o test_dicc test_dicc.cpp 
	./test_dicc

clean:
	rm -f $(OBJS) $(TARGET) test_mapa test_cola test_dicc *.o

valgrind: all
	valgrind --leak-check=full ./$(TARGET)

val_mapa: test_mapa
	valgrind --leak-check=full ./test_mapa

val_cola: test_cola
	valgrind --leak-check=full ./test_cola

val_dicc: test_dicc
	valgrind --leak-check=full ./test_dicc