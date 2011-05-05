# vim: set tabstop=4 noexpandtab:
OBJS = $(addsuffix .o,$(basename $(wildcard src/*.cpp)))
CXXFLAGS := -MD $(CXXFLAGS)
DEBUGFLAGS := -Wall -Wextra -pedantic -ansi $(CXXFLAGS)
LIBS := 
BIN = codepeiler

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(BIN)

$(BIN): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

clean:
	$(RM) $(BIN) $(OBJS)

