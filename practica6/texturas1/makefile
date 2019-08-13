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

all : texturas

texturas : texturas.cpp
	$(CXX) -o texturas.o texturas.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
