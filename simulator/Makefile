CXX=g++
CXXFLAGS= -std=c++11 -g -pthread
SRCDIR:= simulator

OBJS = Bus.o UMA.o main.o

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

cachemall: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CXXFLAGS)

clean:
	/bin/rm -rf cachemall
	/bin/rm -f *.o
