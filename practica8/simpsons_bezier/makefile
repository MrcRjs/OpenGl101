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

all : homero lisa

homero : homero.cpp
	$(CXX) -o homero.o homero.cpp $(CXXFLAGS)

lisa : lisa.cpp
	$(CXX) -o lisa.o lisa.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
