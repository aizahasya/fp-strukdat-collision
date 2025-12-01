CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/main.cpp src/Particle.cpp src/ParticleSystem.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = particle-sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
