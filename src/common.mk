BINDIR = bin

CXXFLAGS := -L../../bin/ -I../
RELEASEFLAGS := -O3 -DNDEBUG $(CXXFLAGS)
DEBUGFLAGS := -O0 -g -DDEBUG -Wall -Wextra -pedantic -ansi $(CXXFLAGS)