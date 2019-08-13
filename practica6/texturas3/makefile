CXX = g++
src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
CXXFLAGS = -lSOIL -lGL -lGLU -lglut
endif
ifeq ($(UNAME), Darwin)
CXXFLAGS = -framework GLUT -framework OpenGL
endif

all : multtexturas

multtexturas : multtexturas.cpp
	$(CXX) -o multtexturas.o multtexturas.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
