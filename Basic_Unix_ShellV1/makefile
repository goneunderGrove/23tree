CPP      = g++
CPPFLAGS = -Wall -g
LDFLAGS  = -lreadline
OBJFILES = main.o shell.o
TARGET   = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CPP) $(CPPFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~