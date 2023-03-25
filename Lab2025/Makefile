GCC = g++
CFLAGS = -Wall
RM = rm -rf
TARGET = lab2025
TEST_INPUT = test.txt

all: clean $(TARGET) test

$(TARGET): $(TARGET).o
	$(GCC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).cpp
	$(GCC) $(CFLAGS) -c $(TARGET).cpp

test:
	cat ./$(TEST_INPUT) | ./$(TARGET)

clean:
	$(RM) *.o $(TARGET)