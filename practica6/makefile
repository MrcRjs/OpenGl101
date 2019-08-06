objects = sillaTexturizada.o normalizer.o

sillaGl : $(objects)
    # OSX
	# g++ -o sillaGl.o $(objects) -framework GLUT -framework OpenGL

	# Linux
	g++ -o sillaGl.o $(objects) -lGL -lGLU -lglut
sillaTexturizada.o : sillaTexturizada.cpp
	g++ -w -c sillaTexturizada.cpp
normalizer.o : ../utils/normalizer.cpp ../utils/normalizer.h
	g++ -c ../utils/normalizer.cpp
clean :
	rm $(objects)