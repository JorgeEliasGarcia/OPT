CXX = g++
CXXFLAGS = -std=c++14 -Wall
LDFLAGS =

all= grafo
aproximacion_numero_e: grafo.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean

clean: 
	rm -f grafo *.o
	rm -rf a.out 