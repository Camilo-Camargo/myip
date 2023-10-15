# MYIP configuracion
PROG_NAME=myip
ENTRY_POINT=myip.c
BINARY_DIR = bin

# Windows configuration
WIN_CC = x86_64-w64-mingw32-cc
WIN_LIBS = 
WIN_EXEC = wine
WIN_BINARY_PATH = $(BINARY_DIR)/$(PROG_NAME).exe
# Unix configuration
UNIX_CC = cc
UNIX_LIBS = 
UNIX_EXEC = 
UNIX_BINARY_PATH = $(BINARY_DIR)/$(PROG_NAME)


ifeq ($(PLATFORM),)
	ifeq ($(OS),Windows_NT)
		PLATFORM = win32
	else
		PLATFORM = unix
	endif
endif

ifeq ($(PLATFORM),win32)
	CC = x86_64-w64-mingw32-cc
	LIBS = $(WIN_LIBS)
	EXEC = $(WIN_EXEC)
	BINARY_PATH = $(WIN_BINARY_PATH)
else
	CC = cc
	LIBS = $(UNIX_LIBS)
	EXEC = $(UNIX_EXEC)
	BINARY_PATH = $(UNIX_BINARY_PATH)
endif

.PHONY: all

all: clean build run

build:
	mkdir -p $(BINARY_DIR)
	$(CC) -o bin/$(PROG_NAME) $(ENTRY_POINT) $(LIBS)

clean:
	rm -rf $(BINARY_DIR)

run:
	$(EXEC) ./$(BINARY_PATH)


