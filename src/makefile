# Compiler
CXX = g++

# Source and executable
SRC = main.cpp
EXE = main

# Compiler flags (e.g., include paths for SDL2 and debugging)
CXXFLAGS = -Wall -g

# Linker flags for SDL2 and related libraries
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image

# Build target
build: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE) $(LIBS)

# Clean target
clean:
	rm -f $(EXE)

# Phony targets to avoid conflict with file names
.PHONY: build clean
