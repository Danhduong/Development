
EXE = netclient
RM = -rm -f
INCLUDE_DIR = -I../common/ ../common/common.cpp ../common/socket.cpp

all:
	g++ -Wall -o $(EXE) client.cpp $(INCLUDE_DIR) -std=c++11 -lpthread

clean:
	$(RM) *.o $(EXE)

install: all
	@echo Installing the $(EXE)
	mkdir -p ../bin && cp -uvf $(EXE) ../bin