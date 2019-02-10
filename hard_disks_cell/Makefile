TARGET = test.exe
OBJS = main.o pair_correlation.o xy.o randuni.o init.o configFile.o
CC = g++
CFLAGS = -c -Wall -g
LFLAGS = -Wall -g
#CFLAGS = -c -Wall -O3 -DNDEBUG
#LFLAGS = -Wall -O3 -DNDEBUG

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS)  $(OBJS) -o $(TARGET)

main.o: main.cpp xy.h init.h system.h pair_correlation.h configFile.h
	$(CC) $(CFLAGS) main.cpp

pair_correlation.o: pair_correlation.cpp pair_correlation.h xy.h
	$(CC) $(CFLAGS)	pair_correlation.cpp

xy.o: xy.cpp xy.h
	$(CC) $(CFLAGS) xy.cpp

configFile.o: configFile.cpp configFile.h
	$(CC) $(CFLAGS) configFile.cpp

randuni.o: randuni.cpp randuni.h
	$(CC) $(CFLAGS) randuni.cpp

init.o: init.cpp init.h xy.h
	$(CC) $(CFLAGS) init.cpp

.PHONY: clean
clean:
	rm -f  $(OBJS) $(TARGET)

.PHONY: cleanObject
cleanObject:
	rm -f  $(OBJS)

