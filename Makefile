# vim: set tabstop=4 noexpandtab:
OBJS = $(addsuffix .o,$(basename $(wildcard src/*.cpp)))
CXXFLAGS := -MD $(CXXFLAGS)
DEBUGFLAGS := -DDEBUG -Wall -Wextra -pedantic -ansi $(CXXFLAGS)
LIBS := 
BIN = codepeiler

release:
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" $(BIN)

debug:
	$(MAKE) CXXFLAGS="$(DEBUGFLAGS)" $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

clean:
	$(RM) $(BIN) $(OBJS)

