CC = g++
CFLAGS = -g
TARGET = Server
OBJS = ServerMain.o ServerFunction.o
SRCS = $(SRCS:.o=.c)
HEADERS = ServerFunction.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) daemon_server.log