objects = sillaPrimitiva.o normalizer.o

sillaGl : $(objects)
	g++ -o sillaGl.o $(objects) -framework GLUT -framework OpenGL
sillaPrimitiva.o : sillaprimitiva.cpp
	g++ -w -c sillaPrimitiva.cpp
normalizer.o : ../utils/normalizer.cpp ../utils/normalizer.h
	g++ -c ../utils/normalizer.cpp
clean :
	rm $(objects)