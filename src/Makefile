CC=g++

COMPILE_FLAGS = -g -std=c++11 -Wall -c
LINKER_FLAGS = -g
LIBS = -l bcm2835 -l rt

OBJECTS = \
	test.o \
	DigitalHeader.o \
	DistanceSensor.o \
	AccurateTiming.o

#OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: ads.o rotary.o timer.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS) $(LIBS)

main.o: test.cpp
	$(CC) $(COMPILE_FLAGS) test.cpp
ads.o: Libraries/DigitalIO/DigitalHeader.cpp Libraries/DigitalIO/DigitalHeader.h
	$(CC) $(COMPILE_FLAGS) Libraries/DigitalIO/DigitalHeader.cpp
timer.o: Libraries/Timer/AccurateTiming.cpp Libraries/Timer/AccurateTiming.h
	$(CC) $(COMPILE_FLAGS) Libraries/Timer/AccurateTiming.cpp
rotary.o: Modules/Distance/DistanceSensor.cpp Modules/Distance/DistanceSensor.h
	$(CC) $(COMPILE_FLAGS) Modules/Distance/DistanceSensor.cpp

clean:
	$(RM) $(OBJECTS) runner
