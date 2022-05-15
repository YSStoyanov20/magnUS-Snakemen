SRCDIR=../src
_SRC=mainMenu.cpp PvP.cpp PvC.cpp global.cpp
SRC=$(patsubst %, $(SRCDIR)/%, $(_SRC))

OUTPUT=Booleo.exe

HEADERDIR=../include

LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

LIBDIR=../lib

ERRFLAGS=-O2 -Wall -Wno-missing-braces

all:
	windres -i res/icon.rc -o res/icon.o
	g++ ../main.cpp $(SRC) res/icon.o -o $(OUTPUT) $(ERRFLAGS) -I $(HEADERDIR) -L $(LIBDIR) $(LIBS)