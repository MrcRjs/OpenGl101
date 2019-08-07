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

all : primitiveRobot primitiveRobotFunctions

primitiveRobot : primitiveRobot.cpp
	$(CXX) -o primitiveRobot.o primitiveRobot.cpp $(CXXFLAGS)

primitiveRobotFunctions : primitiveRobotFunctions.cpp
	$(CXX) -o primitiveRobotFunctions.o primitiveRobotFunctions.cpp $(CXXFLAGS)

.PHONY : clean

clean:
	rm -f $(obj)
