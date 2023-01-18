GCC = g++
CFLAGS = -Wall
RM = rm -rf
TARGET = lab1401

all: clean $(TARGET) test

$(TARGET): $(TARGET).o
	$(GCC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).cpp
	$(GCC) $(CFLAGS) -c $(TARGET).cpp

test:
	./$(TARGET)

clean:
	$(RM) *.o $(TARGET)