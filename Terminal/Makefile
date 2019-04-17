CC=g++
CFLAGS=-c -std=c++17 -I./lib/
LDFLAGS=-L./lib/
LIB_SOURCES=conn.cpp data.cpp ./lib/CmdArgs.cpp
SOURCES=$(LIB_SOURCES) terminal.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=term

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:	
	rm -f *.o 
	rm $(LIBRARY)
	rm $(EXECUTABLE)
	touch *.cpp

