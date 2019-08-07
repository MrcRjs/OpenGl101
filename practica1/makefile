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

all : basic ejemplo1 config

basic : basic.cpp
	$(CXX) -o basic.o basic.cpp $(CXXFLAGS)

ejemplo1 : ejemplo1.cpp
	$(CXX) -o ejemplo1.o ejemplo1.cpp $(CXXFLAGS)

config : config.cpp
	$(CXX) -o config.o config.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
