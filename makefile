CC  = gcc
CXX = g++
INC = include
LIB = lib
SRC = src/weirdutils
STD = -std=c++20
OBJ_1 = *.o
OBJ_2 = $(LIB)/libweirdc.so
OBJ_3 = $(LIB)/libweird-utils.so

CFLAGS = -fpic -I$(INC) -c
LFLAGS = -shared -I$(INC) -o

build:
	@echo CC  Building weirdc ...
	$(CC) $(CFLAGS) $(SRC)/*.c
	$(CC) $(LFLAGS) $(OBJ_2) $(OBJ_1)
	@echo
	@echo CXX Building weirdutils ...
	$(CXX) $(STD) $(CFLAGS) $(SRC)/*.cxx
	$(CXX) $(STD) $(LFLAGS) $(OBJ_3) $(OBJ_1)
	@echo
	@echo Done ^,..,^

install:
	@echo Installing weirdutils ...
	@sudo cp $(LIB)/*.so /usr/lib/
	@sudo cp $(INC)/weirdutils/* /usr/include/weirdutils && sudo cp $(INC)/weirdutils.hxx /usr/include/
	@echo Configuring LD ...
	@sudo ldconfig
	@echo Done ^,..,^

remove:
	@echo Uninstalling dynamicload ...
	@sudo rm /usr/lib/libweirdc.so /usr/lib/libweird-utils.so
	@sudo rm -r /usr/include/weirdutils && sudo rm /usr/include/weirdutils.h
	@sudo ldconfig
	@echo Done ^,..,^

clean:
	@echo Cleaning up risidual files ...
	@rm *.o && rm lib/*.so
	@echo Done ^,..,^

