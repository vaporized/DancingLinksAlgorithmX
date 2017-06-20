CXX = 	g++

CXXFLAGS =	-O2 -g -Wall -std=c++11

OBJS =	main.o ConstraintMatrix.o AlgorithmX.o

LIBS =

TARGET =	main

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)


ConstraintMatrix.o: ConstraintMatrix.hpp ConstraintMatrix.cpp
		$(CXX) $(CXXFLAGS) -c ConstraintMatrix.cpp

AlgorithmX.o: AlgorithmX.hpp AlgorithmX.cpp
		$(CXX) $(CXXFLAGS) -c AlgorithmX.cpp

main.o: main.cpp ConstraintMatrix.hpp AlgorithmX.hpp
		$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f $(OBJS) $(TARGET)
