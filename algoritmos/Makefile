SOURCES= $(wildcard *.cpp)
OBJECTS= $(patsubst %.cpp,%.o,$(SOURCES))
CXXFLAGS= -Wall -Wextra -pedantic -ggdb
CXXLIBS= -lsfml-system -lsfml-window -lsfml-graphics
TARGET= algoritmos

all: $(OBJECTS)

run: $(TARGET)
	./$<

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXLIBS)

clean:
	$(RM) $(TARGET) $(OBJECTS)
