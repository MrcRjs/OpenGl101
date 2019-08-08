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

all : cuboNormalizado materials sillaTexturizada

cuboNormalizado : cuboNormalizado.cpp
	$(CXX) -o cuboNormalizado.o cuboNormalizado.cpp $(CXXFLAGS)

materials : materials.cpp
	$(CXX) -o materials.o materials.cpp $(CXXFLAGS)

sillaTexturizada : sillaTexturizada.cpp normalizer.o
	$(CXX) -o sillaTexturizada.o normalizer.o sillaTexturizada.cpp $(CXXFLAGS)

normalizer.o : ../utils/normalizer.cpp ../utils/normalizer.h
	$(CXX) -c ../utils/normalizer.cpp

.PHONY : clean

clean:
	rm -f $(obj) normalizer.o