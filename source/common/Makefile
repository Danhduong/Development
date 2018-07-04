
CXX = g++
RM = -rm -f

CXXFLAGS += -g -Wall -std=c++11

OBJ += common.o 

all: $(OBJ)

common.o: common.cpp common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.o