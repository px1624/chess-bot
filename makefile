CXX= g++
CXXFLAGS= -g -Wall -std=gnu++11
LDFLAGS=
SHELL= bash
PROGRAMS= chess_player
SOURCES= chess_player.cpp chess_board.cpp king.cpp knight.cpp pawn.cpp piece.cpp queen.cpp rook.cpp bishop.cpp
OBJECTS= $(SOURCES:.cpp=.o)

all: $(PROGRAMS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

chess_player: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -f $(PROGRAMS) $(OBJECTS)

