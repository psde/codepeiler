# Project config
NAME = Buffer
LIBS = 

# Generic library makefile
include ../common.mk
ROOT = ../..
OUTDIR = $(ROOT)/$(BINDIR)
OUTNAME = $(OUTDIR)/lib$(NAME).a
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
	ar rs $@ $(OBJS)

.PHONY: clean
clean:
	$(RM) $(OUTNAME) $(OBJS) $(DEPS)