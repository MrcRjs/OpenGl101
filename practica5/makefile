CXX = g++
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
CXXFLAGS = -lGL -lGLU -lglut
endif
ifeq ($(UNAME), Darwin)
CXXFLAGS = -framework GLUT -framework OpenGL
endif

all : cuboPrimitivo iluminacion iluminacion2 piramidePrimitiva proyeccion3D sillaPrimitiva

cuboPrimitivo : cuboPrimitivo.cpp
	$(CXX) -o cuboPrimitivo.o cuboPrimitivo.cpp $(CXXFLAGS)

iluminacion : iluminacion3D.cpp
	$(CXX) -o iluminacion3D.o iluminacion3D.cpp $(CXXFLAGS)

iluminacion2 : iluminacion3Dpt2.cpp
	$(CXX) -o iluminacion3Dpt2.o iluminacion3Dpt2.cpp $(CXXFLAGS)

piramidePrimitiva : piramidePrimitiva.cpp
	$(CXX) -o piramidePrimitiva.o piramidePrimitiva.cpp $(CXXFLAGS)

proyeccion3D : proyeccion3D.cpp
	$(CXX) -o proyeccion3D.o proyeccion3D.cpp $(CXXFLAGS)

sillaPrimitiva : sillaPrimitiva.cpp normalizer.o
	$(CXX) -o sillaPrimitiva.o normalizer.o sillaPrimitiva.cpp $(CXXFLAGS)

normalizer.o : ../utils/normalizer.cpp ../utils/normalizer.h
	$(CXX) -c ../utils/normalizer.cpp

.PHONY : clean

clean:
	rm -f $(obj) normalizer.o
