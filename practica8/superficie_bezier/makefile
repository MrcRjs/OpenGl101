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

all : bez3d bezier_sup

bez3d : bez3d.cpp
	$(CXX) -o bez3d.o bez3d.cpp $(CXXFLAGS)

bezier_sup : bezier_sup.cpp
	$(CXX) -o bezier_sup.o bezier_sup.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
