SOURCES = tests.cpp Juego.cpp Mapa.cpp Driver.cpp
OBJS = $(SOURCES:.cpp=.o)

LIBS = modulos.h aed2.h

TARGET = tests

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)
