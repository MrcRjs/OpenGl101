nx : normalizando.o normalizer.o
	g++ -o nx.o normalizando.o normalizer.o
normalizando.o : normalizando.cpp
	g++ -c normalizando.cpp
normalizer.o : normalizer.cpp normalizer.h
	g++ -c normalizer.cpp
clean :
	rm *.o