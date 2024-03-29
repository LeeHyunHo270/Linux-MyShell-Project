CC			= gcc
CFLAGS		= -g -O2
TARGET		= minish
OBJECTS		= execute.o parser.o symbol.o util.o command.o
MAIN_SOURCE	= minish.c

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(MAIN_SOURCE)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)
