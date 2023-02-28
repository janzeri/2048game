CC = g++

TARGET = 2048

SRCS = /src/game.cpp
SRCS += /src/solver.cpp

OBJS = $(SRCS:.cpp=.o)

INCDIR = /src

$(TARGET): $(OBJS) $(CC) -o $@ $^ $(LIBDIR) $(LIBS)

$(OBJS): $(SRCS) $(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

all: clean $(OBJS) $(TARGET)

clean: -rm -f $(OBJS) $(TARGET) *.d
