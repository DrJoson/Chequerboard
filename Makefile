CC = g++

CFLAGS = -std=c++11 -lGL -lGLEW -lglfw -Wall

TARGET = main

all: $(TARGET)

$(TARGET):$(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)




