SOURCES= $(wildcard *.cpp)
OBJECTS= $(patsubst %.cpp,%.o,$(SOURCES))
CXXFLAGS= -Wall -ggdb
CXX= g++
BIN= dental

all: $(BIN)

run: $(BIN)
	./$<

$(BIN): $(OBJECTS)
	$(CXX) $^ -o $@
