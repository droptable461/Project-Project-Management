CC=g++
CFLAGS=-c -std=c++17 -I./lib/ -lcurl
LDFLAGS=-L./lib/
LIB_SOURCES=conn.cpp data.cpp ./lib/CmdArgs.cpp
SOURCES=$(LIB_SOURCES) terminal.cpp
SOURCES2=$(LIB_SOURCES) main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=term
EXECUTABLE2=test

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

test:
	g++ main.cpp conn.cpp data.cpp -lcurl -Wfatal-errors -g -o test 

$(EXECUTABLE2): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:	
	rm -f *.o 
	rm $(LIBRARY)
	rm $(EXECUTABLE)
	touch *.cpp

