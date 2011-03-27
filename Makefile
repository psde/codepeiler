OBJS = $(addsuffix .o,$(basename $(wildcard src/*.cpp)))
CXXFLAGS := $(CXXFLAGS)
#LIBS := 

BIN = codepeiler

$(BIN): $(OBJS)
	$(CXX) -o $@ $(OBJS) #$(LIBS)

clean:
	$(RM) $(BIN) $(OBJS)

