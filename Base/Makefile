SOURCES = tests.cpp Juego.cpp Mapa.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS = modulos.h

TARGET = tests

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

driver : Driver.o
	$(CXX) -o Driver  Driver.o $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET) Driver Driver.o

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
