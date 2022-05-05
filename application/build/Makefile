SRCDIR=../src
_SRC=mainMenu.cpp PvP.cpp
SRC=$(patsubst %, $(SRCDIR)/%, $(_SRC))

OUTPUT=Booleo.exe

HEADERDIR=../include

LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

LIBDIR=../lib

ERRFLAGS=-O2 -Wall -Wno-missing-braces

all:
	g++ ../main.cpp $(SRC) -o $(OUTPUT) $(ERRFLAGS) -I $(HEADERDIR) -L $(LIBDIR) $(LIBS)