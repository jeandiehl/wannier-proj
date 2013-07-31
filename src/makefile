CC = g++
CFLAGS = -Wall -g -O3 -I../include/

LDFLAGS = 

SRCDIR := src
LIBDIR := lib
INCDIR := include
BINDIR := bin

all: ../bin/run_proj ../bin/init_smat

../bin/run_proj: ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../src/run_proj.o
	$(CC) $(CFLAGS) ../src/run_proj.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o -o ../bin/run_proj

../bin/init_smat: ../src/init_smat.o
	$(CC) $(CFLAGS) ../src/init_smat.o -o ../bin/init_smat


../lib/FileInproj.o: ../lib/FileInproj.cc ../include/FileInproj.h 
	$(CC) $(CFLAGS) -c ../lib/FileInproj.cc -o ../lib/FileInproj.o

../lib/FileSmat.o: ../lib/FileSmat.cc ../include/FileSmat.h 
	$(CC) $(CFLAGS) -c ../lib/FileSmat.cc -o ../lib/FileSmat.o

../lib/FileRot.o: ../lib/FileRot.cc ../include/FileRot.h 
	$(CC) $(CFLAGS) -c ../lib/FileRot.cc -o ../lib/FileRot.o

../lib/FileAlmblm.o: ../lib/FileAlmblm.cc ../include/FileAlmblm.h ../include/GeneralCoefficient.h
	$(CC) $(CFLAGS) -c ../lib/FileAlmblm.cc -o ../lib/FileAlmblm.o

../lib/FileGeneral.o: ../lib/FileGeneral.cc ../include/FileGeneral.h
	$(CC) $(CFLAGS) -c ../lib/FileGeneral.cc -o ../lib/FileGeneral.o


../src/run_proj.o: ../src/run_proj.cc ../include/FileAlmblm.h ../include/FileRot.h ../include/FileSmat.h  ../include/GeneralCoefficient.h
	$(CC) $(CFLAGS) -c ../src/run_proj.cc -o ../src/run_proj.o

../src/init_smat.o: ../src/init_smat.cc
	$(CC) $(CFLAGS) -c ../src/init_smat.cc -o ../src/init_smat.o

clean:
	@rm -f ../lib/*.o ../src/*.o
