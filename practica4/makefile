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

all : curvas keymotion menu menuNiveles

curvas : curvas.cpp
	$(CXX) -o curvas.o curvas.cpp $(CXXFLAGS)

keymotion : key_motion.cpp
	$(CXX) -o key_motion.o key_motion.cpp $(CXXFLAGS)

menu : menu.cpp
	$(CXX) -o menu.o menu.cpp $(CXXFLAGS)

menuNiveles : menu_niveles.cpp
	$(CXX) -o menu_niveles.o menu_niveles.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
