CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra $(INCLUDES) -g
INCLUDES = -Imain

# Source files
SRCS = main/main.cpp \
       main/Game/game.cpp \
       main/Pieces/piece.cpp \
       main/Pieces/pawn.cpp \
       main/Pieces/knight.cpp \
       main/Pieces/bishop.cpp \
       main/Pieces/rook.cpp \
       main/Pieces/queen.cpp \
       main/Pieces/king.cpp \
       main/Board/move.cpp \
       main/Board/board.cpp \
       main/GameTree/gametree.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

TARGET = chess

.PHONY: all clean lldb

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

lldb: $(TARGET)
	lldb ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
