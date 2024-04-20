CXX = g++

CXXFLAGS = -I./include -g

TARGET = lab-11_vector

OBJECTS = obj
SOURCE = src

all: $(OBJECTS)/ $(TARGET)

$(TARGET): $(OBJECTS)/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJECTS)/main.o: $(SOURCE)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJECTS)/:
	mkdir -p $(OBJECTS)

clean:
	rm -f $(OBJECTS)/*.o $(TARGET)