# top level makefile for GuberClient and GuberServer 
# compiler flags for GTK usage
GTKINC	= `pkg-config --cflags gtk+-2.0`
GTKLIBS	= `pkg-config --libs gtk+-2.0`

# general compiler flags
#DEBUG	= -g -DDEBUG
DEBUG	= -O2
CFLAGS	= -Wall -ansi $(DEBUG) $(GTKINC) -c
LFLAGS	= -Wall -ansi $(DEBUG) $(GTKLIBS)
CC	= gcc

DESIGN = GuberClient GuberServer GuberClient_bin GuberServer_bin TestTaxi TestReader TestRoute
TEST = TestTaxi TestRoute
OBJS = src/GuberClient.o src/Reader.o src/Taxi.o src/DrawMap.o src/DrawTaxi.o src/Belle.o src/Route.o
OBJS2 = src/GuberServer.o src/Reader.o src/Taxi.o src/DrawMap.o src/DrawTaxi.o src/Belle.o src/Route.o
DEPS = src/Reader.h src/Taxi.h src/GuberClient.h src/GuberServer.h src/Belle.h

#targets
all: GuberClient GuberServer GuberClient_bin GuberServer_bin

GuberClient: $(OBJS) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS) -o src/GuberClient
	
GuberClient_bin: $(OBJS) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS) -o bin/GuberClient
	
GuberServer: $(OBJS2) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS2) -o src/GuberServer
	
GuberServer_bin: $(OBJS2) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS2) -o bin/GuberServer
	
TestTaxi: src/TestTaxi.o src/Taxi.o src/Reader.o
	$(CC) -ansi -Wall src/TestTaxi.o src/Taxi.o src/Reader.o -o src/TestTaxi
	
TestReader: TestReader.o Reader.o 
	$(CC) -ansi -Wall src/TestReader.o src/Reader.o -o src/TestReader
	
TestRoute: TestRoute.o Route.o Reader.o
	$(CC) -ansi -Wall src/TestRoute.o src/Route.o src/Reader.o -o src/TestRoute

#################### generate object files ###################
	
GuberClient.o: src/GuberClient.c src/Reader.h src/Taxi.h 
	$(CC) src/GuberClient.c $(CFLAGS) -o src/GuberClient.o
	
GuberServer.o: src/GuberServer.c src/Reader.h src/Taxi.h src/GuberClient.h src/GuberServer.h
	$(CC) src/GuberServer.c $(CFLAGS) -o src/GuberServer.o

Reader.o: src/Reader.c src/Reader.h
	$(CC) $(CFLAGS) src/Reader.c -o src/Reader.o

Taxi.o: src/Taxi.c src/Taxi.h src/GuberClient.h
	$(CC) $(CFLAGS) src/Taxi.c -o src/Taxi.o
	
DrawMap.o: src/DrawMap.c src/GuberClient.h
	$(CC) $(CFLAGS) src/DrawMap.c -o src/DrawMap.o

DrawTaxi.o: src/DrawTaxi.c src/GuberClient.h
	$(CC) $(CFLAGS) src/DrawTaxi.c -o src/DrawTaxi.o
	
Route.o: src/Route.c src/Route.h
	$(CC) $(CFLAGS) src/Route.c -o src/Route.o

TestTaxi.o: src/TestTaxi.c src/Taxi.h src/Reader.h
	$(CC) $(CFLAGS) src/TestTaxi.c -o src/TestTaxi.o

TestReader.o: src/TestReader.c src/Reader.h
	$(CC) $(CFLAGS) src/TestReader.c -o src/TestReader.o

TestRoute.o: src/TestRoute.c src/Route.h
	$(CC) $(CFLAGS) src/TestRoute.c -o src/TestRoute.o
	
Belle.o: src/Belle.c src/Belle.h
	$(CC) $(CFLAGS) src/Belle.c -o src/Belle.o
	
clean: 
	rm -f src/*.o src/$(DESIGN) src/map.txt bin/GuberServer bin/GuberClient src/GuberClient src/GuberServer
	
