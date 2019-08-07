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

all : actividades actividades-alt

actividades : actividades.cpp
	$(CXX) -o actividades.o actividades.cpp $(CXXFLAGS)

actividades-alt : actividades-alt.cpp
	$(CXX) -o actividades-alt.o actividades-alt.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
