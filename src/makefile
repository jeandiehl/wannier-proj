CC = g++
CFLAGS = -Wall -O3 -I../include/

LDFLAGS = 

SRCDIR := src
LIBDIR := lib
INCDIR := include
BINDIR := bin

all: ../bin/run_proj

../bin/run_proj: ../lib/FileAlmblm.o ../src/run_proj.o
	$(CC) $(CFLAGS) ../src/run_proj.o ../lib/FileAlmblm.o ../bin/run_proj


../lib/FileGeneral.o: ../lib/FileGeneral.cc ../include/FileGeneral.h
	$(CC) $(CFLAGS) -c ../lib/FileGeneral.cc -o ../lib/FileGeneral.o

../lib/FileAlmblm.o: ../lib/FileAlmblm.cc ../include/FileAlmblm.h
	$(CC) $(CFLAGS) -c ../lib/FileAlmblm.cc -o ../lib/FileAlmblm.o



../src/run_proj.o: ../src/run_proj.cc ../include/FileAlmblm.h
	$(CC) $(CFLAGS) -c ../src/run_proj.cc -o ../src/run_proj.o

clean:
	@rm -f ../lib/*.o ../src/*.o
