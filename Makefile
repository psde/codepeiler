# Configuration
BIN = codepeiler
BINDIR = bin
SOURCEDIR = src

# Generic makefile
SRCS = $(wildcard $(SOURCEDIR)/*.cpp)
OBJS = $(patsubst $(SOURCEDIR)/%.cpp, $(BINDIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)
CXXFLAGS := #-MM
RELEASEFLAGS := -O3 -DNDEBUG $(CXXFLAGS)
DEBUGFLAGS := -O0 -g -DDEBUG -Wall -Wextra -pedantic -ansi $(CXXFLAGS)
LIBS := 

all: release

release:
	$(MAKE) CXXFLAGS="$(RELEASEFLAGS)" $(BIN)

debug:
	$(MAKE) CXXFLAGS="$(DEBUGFLAGS)" $(BIN)

#depend: .depend
#.depend: $(SRCS)
#	$(CXX) $(CXXFLAGS) -MM $^ -MF  ./.depend;
#include .depend

$(BINDIR)/%.o: $(SOURCEDIR)/%.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(BIN) $(OBJS) $(DEPS)
