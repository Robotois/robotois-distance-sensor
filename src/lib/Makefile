CC=g++

COMPILE_FLAGS = -g -std=c++11 -Wall -c
LINKER_FLAGS = -g
LIBS = -l bcm2835 -l rt

OBJECTS = \
	test.o \
	DigitalHeader.o \
	DistanceSensor.o \

#OBJECTS = $(subst .cpp,.o,$(SOURCES))

all: digital.o distance.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS) $(LIBS)

main.o: test.cpp
	$(CC) $(COMPILE_FLAGS) test.cpp
digital.o: robotois-digital-header/DigitalHeader.cpp robotois-digital-header/DigitalHeader.h
	$(CC) $(COMPILE_FLAGS) robotois-digital-header/DigitalHeader.cpp
distance.o: DistanceSensor.cpp DistanceSensor.h
	$(CC) $(COMPILE_FLAGS) DistanceSensor.cpp

clean:
	$(RM) $(OBJECTS) runner
