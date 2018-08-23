
all:
	@echo "Compiling common folder"
	cd common; make all

clean:
	@echo "Cleanning common folder"
	cd common; make clean 

install: all
	@echo "Compiling netserver folder"
	cd netserver; make install
	@echo "Compiling netclient folder"
	cd netclient; make install