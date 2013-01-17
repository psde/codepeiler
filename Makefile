NAME = codepeiler
LIBRARIES = Buffer Lexer Parser

BINARIES = $(LIBARIES:%=lib%.a) $(NAME)
BINPATHS = $(BINARIES:%=bin/%)
SRCPATHS = $(LIBRARIES:%=src/lib%/) src/$(NAME)/

all: release

.PHONY: release debug clean
release:
	$(foreach project, $(SRCPATHS), $(MAKE) -C $(project) release;)
	cp bin/$(NAME) .

debug:
	$(foreach project, $(SRCPATHS), $(MAKE) -C $(project) release;)
	cp bin/$(NAME) .

clean:
	$(foreach project, $(SRCPATHS), $(MAKE) -C $(project) clean;)
	rm -f $(NAME)