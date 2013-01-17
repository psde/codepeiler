# Project config
NAME = codepeiler
LIBS = -lBuffer

# Generic makefile
include ../common.mk
ROOT = ../..
OUTDIR = $(ROOT)/$(BINDIR)
OUTNAME= $(OUTDIR)/$(NAME)
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

release:
	$(MAKE) CXXFLAGS="$(RELEASEFLAGS)" $(OUTNAME)

debug:
	$(MAKE) CXXFLAGS="$(DEBUGFLAGS)" $(OUTNAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTNAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OUTNAME) $(OBJS) $(DEPS)