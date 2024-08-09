# Define the compiler
CXX = g++

# Define compiler flags
CXXFLAGS = -g -Wall

# Define the target executable
TARGET = main

# Define source files
SRCS = main.cpp figure.cpp king.cpp queen.cpp rook.cpp bishop.cpp knight.cpp pawn.cpp board.cpp

# Define object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule for linking the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule for compiling source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<