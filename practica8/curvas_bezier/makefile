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

all : bezier bezier_curve bezier_mouse

bezier : bezier.cpp
	$(CXX) -o bezier.o bezier.cpp $(CXXFLAGS)

bezier_curve : bezier_curve.cpp
	$(CXX) -o bezier_curve.o bezier_curve.cpp $(CXXFLAGS)

bezier_mouse : bezier_mouse.cpp
	$(CXX) -o bezier_mouse.o bezier_mouse.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
