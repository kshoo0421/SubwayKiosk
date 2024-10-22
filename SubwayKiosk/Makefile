CC = g++
CFLAGS = -g -std=c++11
TARGET = Server
OBJS = ServerMain.o ServerFunction.o
SRCS = $(SRCS:.o=.cpp)
HEADERS = ServerFunction.h json.hpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) daemon_server.log
