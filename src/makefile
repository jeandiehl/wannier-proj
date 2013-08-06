CC = g++
CFLAGS = -Wall -g -O3 -I../include/

LDFLAGS = 

SRCDIR := src
LIBDIR := lib
INCDIR := include
BINDIR := bin

SRCFILES := $(wildcard ../$(SRCDIR)/*.cc)
SRCOFILES := $(patsubst %.cc, %.o, $(SRCFILES))

BINFILES := $(patsubst ../$(SRCDIR)/%.cc, ../$(BINDIR)/%, $(SRCFILES))

all: $(BINFILES)

../bin/run_proj: ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../src/run_proj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o
	$(CC) $(CFLAGS) ../src/run_proj.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o  ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o -o ../bin/run_proj

../bin/init_smat: ../src/init_smat.o 
	$(CC) $(CFLAGS) ../src/init_smat.o -o ../bin/init_smat

../bin/run_dos: ../src/run_dos.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o
	$(CC) $(CFLAGS) ../src/run_dos.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o -o ../bin/run_dos


../lib/Overlap.o: ../lib/Overlap.cc ../include/Overlap.h 
	$(CC) $(CFLAGS) -c ../lib/Overlap.cc -o ../lib/Overlap.o

../lib/OverlapCalculator.o: ../lib/OverlapCalculator.cc ../include/OverlapCalculator.h 
	$(CC) $(CFLAGS) -c ../lib/OverlapCalculator.cc -o ../lib/OverlapCalculator.o

../lib/FileOutputproj.o: ../lib/FileOutputproj.cc ../include/FileOutputproj.h 
	$(CC) $(CFLAGS) -c ../lib/FileOutputproj.cc -o ../lib/FileOutputproj.o

../lib/FileStruct.o: ../lib/FileStruct.cc ../include/FileStruct.h 
	$(CC) $(CFLAGS) -c ../lib/FileStruct.cc -o ../lib/FileStruct.o

../lib/FermiEnergy.o: ../lib/FermiEnergy.cc ../include/FermiEnergy.h 
	$(CC) $(CFLAGS) -c ../lib/FermiEnergy.cc -o ../lib/FermiEnergy.o
	
../lib/ProjectorCalculator.o: ../lib/ProjectorCalculator.cc ../include/ProjectorCalculator.h 
	$(CC) $(CFLAGS) -c ../lib/ProjectorCalculator.cc -o ../lib/ProjectorCalculator.o

../lib/Projector.o: ../lib/Projector.cc ../include/Projector.h 
	$(CC) $(CFLAGS) -c ../lib/Projector.cc -o ../lib/Projector.o

../lib/FileEnergy.o: ../lib/FileEnergy.cc ../include/FileEnergy.h 
	$(CC) $(CFLAGS) -c ../lib/FileEnergy.cc -o ../lib/FileEnergy.o

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


../src/run_proj.o: ../src/run_proj.cc ../include/FileAlmblm.h ../include/FileRot.h ../include/FileSmat.h  ../include/GeneralCoefficient.h ../include/Projector.h ../include/ProjectorCalculator.h ../include/FileEnergy.h ../include/FermiEnergy.h ../include/FileStruct.h ../include/Overlap.h ../include/OverlapCalculator.h ../include/FileOutputproj.h
	$(CC) $(CFLAGS) -c ../src/run_proj.cc -o ../src/run_proj.o

../src/run_dos.o: ../src/run_dos.cc ../include/FileAlmblm.h ../include/FileRot.h ../include/FileSmat.h  ../include/GeneralCoefficient.h ../include/Projector.h ../include/ProjectorCalculator.h ../include/FileEnergy.h ../include/FermiEnergy.h ../include/FileStruct.h ../include/Overlap.h ../include/OverlapCalculator.h ../include/FileOutputproj.h
	$(CC) $(CFLAGS) -c ../src/run_dos.cc -o ../src/run_dos.o

../src/init_smat.o: ../src/init_smat.cc
	$(CC) $(CFLAGS) -c ../src/init_smat.cc -o ../src/init_smat.o

clean:
	@rm -f ../lib/*.o ../src/*.o
