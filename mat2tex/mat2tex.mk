# Generated by makegen....

TARGET = mat2tex
OBJECTS = mat2tex.o

CC = gcc
CFLAGS = -O2 $(INCDIR)

LIBS =  
LIBDIR =  
INCDIR =  

INSTALLDIR = /usr/local/bin

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBDIR) $(LIBS)

clean:
	rm -f a.out core *~ \#* *.bak $(TARGET) $(OBJECTS)

install:
	install -s -m 777 $(TARGET) $(INSTALLDIR)
