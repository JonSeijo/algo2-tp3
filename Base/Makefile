SOURCES = tests.cpp Juego.cpp Mapa.cpp Driver.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS = modulos.h aed2.h

TARGET = tests

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

test_mapa: Mapa.o
	$(CXX) -o test_mapa test_mapa.cpp Mapa.o $(LIBS)

test_cola: 
	$(CXX) -o test_cola test_cola.cpp $(LIBS)

test_dicc: 
	$(CXX) -o test_dicc test_dicc.cpp $(LIBS)

%.o: %.cpp
	$(CXX) -c $<


clean:
	rm -f $(OBJS) $(TARGET) test_mapa test_cola test_dicc

valgrind: all
	valgrind --leak-check=full ./$(TARGET)

val_mapa: test_mapa
	valgrind --leak-check=full ./test_mapa

val_cola: test_cola
	valgrind --leak-check=full ./test_cola

val_dicc: test_dicc
	valgrind --leak-check=full ./test_dicc