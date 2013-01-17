NAME = codepeiler
LIBRARIES = Buffer

BINARIES = $(LIBARIES:%=lib%.a) $(NAME)
BINPATHS = $(BINARIES:%=bin/%)
SRCPATHS = $(LIBRARIES:%=src/lib%/) src/$(NAME)/

all: release

.PHONY: release
release:
	$(foreach project, $(SRCPATHS), $(MAKE) -C $(project) release;)

.PHONY: debug
debug:
	$(foreach project, $(SRCPATHS), $(MAKE) -C $(project) release;)

.PHONY: clean
clean:
	$(foreach project, $(SRCPATHS), $(MAKE) -C $(project) clean;)