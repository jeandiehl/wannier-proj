CC = g++
CFLAGS = -Wall -s -O3 -I../include/

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

../bin/run_dos: ../src/run_dos.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o ../lib/FileSymm.o ../lib/FileIngf.o ../lib/GreensFunction.o ../lib/GreensFunctionCalculator.o ../lib/GreensFunctionProjector.o ../lib/KSymmSum.o ../lib/DOSCalculator.o ../lib/DOS.o ../lib/BandsCalculator.o ../lib/Bands.o
	$(CC) $(CFLAGS) ../src/run_dos.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o ../lib/FileSymm.o ../lib/FileIngf.o ../lib/GreensFunction.o ../lib/GreensFunctionCalculator.o ../lib/GreensFunctionProjector.o ../lib/KSymmSum.o ../lib/DOSCalculator.o ../lib/DOS.o ../lib/BandsCalculator.o ../lib/Bands.o -o ../bin/run_dos

../bin/plot_dos: ../src/plot_dos.o 
	$(CC) $(CFLAGS) ../src/plot_dos.o -o ../bin/plot_dos
	
../bin/run_spec: ../src/run_spec.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o ../lib/FileSymm.o ../lib/FileIngf.o ../lib/GreensFunction.o ../lib/GreensFunctionCalculator.o ../lib/GreensFunctionProjector.o ../lib/KSymmSum.o ../lib/DOSCalculator.o ../lib/DOS.o ../lib/BandsCalculator.o ../lib/Bands.o ../lib/SpectralFunctionCalculator.o ../lib/SpectralFunction.o
	$(CC) $(CFLAGS) ../src/run_spec.o ../lib/FileAlmblm.o ../lib/FileGeneral.o ../lib/FileRot.o ../lib/FileSmat.o ../lib/FileInproj.o ../lib/ProjectorCalculator.o ../lib/Projector.o ../lib/FileEnergy.o ../lib/FermiEnergy.o ../lib/FileStruct.o ../lib/Overlap.o ../lib/OverlapCalculator.o ../lib/FileOutputproj.o ../lib/FileSymm.o ../lib/FileIngf.o ../lib/GreensFunction.o ../lib/GreensFunctionCalculator.o ../lib/GreensFunctionProjector.o ../lib/KSymmSum.o ../lib/DOSCalculator.o ../lib/DOS.o ../lib/BandsCalculator.o ../lib/Bands.o ../lib/SpectralFunctionCalculator.o ../lib/SpectralFunction.o -o ../bin/run_spec

../bin/plot_bands: ../src/plot_bands.o 
	$(CC) $(CFLAGS) ../src/plot_bands.o -o ../bin/plot_bands

../bin/plot_spec: ../src/plot_spec.o 
	$(CC) $(CFLAGS) ../src/plot_spec.o -o ../bin/plot_spec
	
	
../lib/SpectralFunctionCalculator.o: ../lib/SpectralFunctionCalculator.cc ../include/SpectralFunctionCalculator.h 
	$(CC) $(CFLAGS) -c ../lib/SpectralFunctionCalculator.cc -o ../lib/SpectralFunctionCalculator.o

../lib/SpectralFunction.o: ../lib/SpectralFunction.cc ../include/SpectralFunction.h 
	$(CC) $(CFLAGS) -c ../lib/SpectralFunction.cc -o ../lib/SpectralFunction.o
	
../lib/Bands.o: ../lib/Bands.cc ../include/Bands.h 
	$(CC) $(CFLAGS) -c ../lib/Bands.cc -o ../lib/Bands.o

../lib/BandsCalculator.o: ../lib/BandsCalculator.cc ../include/BandsCalculator.h 
	$(CC) $(CFLAGS) -c ../lib/BandsCalculator.cc -o ../lib/BandsCalculator.o
	
../lib/DOS.o: ../lib/DOS.cc ../include/DOS.h 
	$(CC) $(CFLAGS) -c ../lib/DOS.cc -o ../lib/DOS.o

../lib/DOSCalculator.o: ../lib/DOSCalculator.cc ../include/DOSCalculator.h 
	$(CC) $(CFLAGS) -c ../lib/DOSCalculator.cc -o ../lib/DOSCalculator.o

../lib/KSymmSum.o: ../lib/KSymmSum.cc ../include/KSymmSum.h 
	$(CC) $(CFLAGS) -c ../lib/KSymmSum.cc -o ../lib/KSymmSum.o

../lib/GreensFunctionProjector.o: ../lib/GreensFunctionProjector.cc ../include/GreensFunctionProjector.h 
	$(CC) $(CFLAGS) -c ../lib/GreensFunctionProjector.cc -o ../lib/GreensFunctionProjector.o

../lib/GreensFunction.o: ../lib/GreensFunction.cc ../include/GreensFunction.h 
	$(CC) $(CFLAGS) -c ../lib/GreensFunction.cc -o ../lib/GreensFunction.o

../lib/GreensFunctionCalculator.o: ../lib/GreensFunctionCalculator.cc ../include/GreensFunctionCalculator.h 
	$(CC) $(CFLAGS) -c ../lib/GreensFunctionCalculator.cc -o ../lib/GreensFunctionCalculator.o

../lib/FileIngf.o: ../lib/FileIngf.cc ../include/FileIngf.h 
	$(CC) $(CFLAGS) -c ../lib/FileIngf.cc -o ../lib/FileIngf.o

../lib/FileSymm.o: ../lib/FileSymm.cc ../include/FileSymm.h 
	$(CC) $(CFLAGS) -c ../lib/FileSymm.cc -o ../lib/FileSymm.o

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
	$(CC) $(CFLAGS) -c ../lib/ProjectorCalculator.cc -o ../lib/ProjectorCalculator.o -s

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


../src/plot_spec.o: ../src/plot_spec.cc
	$(CC) $(CFLAGS) -c ../src/plot_spec.cc -o ../src/plot_spec.o

../src/plot_bands.o: ../src/plot_bands.cc
	$(CC) $(CFLAGS) -c ../src/plot_bands.cc -o ../src/plot_bands.o

../src/run_spec.o: ../src/run_spec.cc ../include/FileAlmblm.h ../include/FileRot.h ../include/FileSmat.h  ../include/GeneralCoefficient.h ../include/Projector.h ../include/ProjectorCalculator.h ../include/FileEnergy.h ../include/FermiEnergy.h ../include/FileStruct.h ../include/Overlap.h ../include/OverlapCalculator.h ../include/FileOutputproj.h ../include/FileSymm.h ../include/FileIngf.h ../include/GreensFunctionCalculator.h  ../include/GreensFunction.h ../include/GreensFunctionProjector.h ../include/KSymmSum.h  ../include/DOS.h  ../include/DOSCalculator.h ../include/BandsCalculator.h ../include/Bands.h  ../include/SpectralFunction.h  ../include/SpectralFunctionCalculator.h 
	$(CC) $(CFLAGS) -c ../src/run_spec.cc -o ../src/run_spec.o

../src/plot_dos.o: ../src/plot_dos.cc
	$(CC) $(CFLAGS) -c ../src/plot_dos.cc -o ../src/plot_dos.o

../src/run_proj.o: ../src/run_proj.cc ../include/FileAlmblm.h ../include/FileRot.h ../include/FileSmat.h  ../include/GeneralCoefficient.h ../include/Projector.h ../include/ProjectorCalculator.h ../include/FileEnergy.h ../include/FermiEnergy.h ../include/FileStruct.h ../include/Overlap.h ../include/OverlapCalculator.h ../include/FileOutputproj.h 
	$(CC) $(CFLAGS) -c ../src/run_proj.cc -o ../src/run_proj.o

../src/run_dos.o: ../src/run_dos.cc ../include/FileAlmblm.h ../include/FileRot.h ../include/FileSmat.h  ../include/GeneralCoefficient.h ../include/Projector.h ../include/ProjectorCalculator.h ../include/FileEnergy.h ../include/FermiEnergy.h ../include/FileStruct.h ../include/Overlap.h ../include/OverlapCalculator.h ../include/FileOutputproj.h ../include/FileSymm.h ../include/FileIngf.h ../include/GreensFunctionCalculator.h  ../include/GreensFunction.h ../include/GreensFunctionProjector.h ../include/KSymmSum.h  ../include/DOS.h  ../include/DOSCalculator.h ../include/BandsCalculator.h ../include/Bands.h 
	$(CC) $(CFLAGS) -c ../src/run_dos.cc -o ../src/run_dos.o

../src/init_smat.o: ../src/init_smat.cc
	$(CC) $(CFLAGS) -c ../src/init_smat.cc -o ../src/init_smat.o

clean:
	@rm -f ../lib/*.o ../src/*.o
