CC     = g++
CFLAGS = -g -Wall -Wextra -Wpedantic
LFLAGS = -lSDL2

.PHONY: all clean re run

TGT  = main
SRCS = main.cpp screen.cpp vec3.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TGT)


$(TGT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(TGT)

%.o: %.cpp
	$(CC) $(CFLAGS) $(LFLAGS) -c $^ -o $@ 

clean:
	@rm -f $(TGT) $(OBJS)
	@echo "clean"

re: clean all

run: all
	./$(TGT)
