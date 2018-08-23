
CXX = g++
RM = -rm -f

CXXFLAGS += -g -Wall -std=c++11

OBJ += common.o log.o socket.o

all: $(OBJ)

common.o: common.cpp common.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

log.o: log.cpp log.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

socket.o: socket.cpp socket.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ -c $< 

clean:
	$(RM) *.o