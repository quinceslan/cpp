CXXFLAGS= -Wall -Wextra -ggdb

all: main.o

run: pagos
	./pagos

pagos: main.o
	g++ -o pagos main.o

clean:
	rm -f main.o pagos
