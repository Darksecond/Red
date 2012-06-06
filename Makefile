CC = clang++
LD = clang++
RM = rm -rf

CFLAGS = -Wall -g3
LDFLAGS = 
SOURCES = $(wildcard src/*.cc)
OBJECTS = $(SOURCES:.cc=.o)
HEADERS = $(wildcard src/*.h)
TARGET = red

.PHONY: clean all

all: $(OBJECTS) $(TARGET)

clean:
	$(RM) $(OBJECTS) $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cc $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@
