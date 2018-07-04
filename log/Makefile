
CXX = g++
RM = -rm -f

CXXFLAGS += -g -Wall
LDFLAGS  = 

objects += baseLogger.o 
objects += stdoutLogger.o
objects += fileLogger.o
objects += sysLogger.o

all: $(objects)

baseLogger.o: baseLogger.cpp baseLogger.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

stdoutLogger.o: stdoutLogger.cpp stdoutLogger.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

fileLogger.o: fileLogger.cpp fileLogger.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

sysLogger.o: sysLogger.cpp sysLogger.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.o