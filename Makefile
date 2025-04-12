PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

CC = cc
CFLAGS = -g -pedantic -Wall -Wextra

PROGRAM = generate-names
SOURCES = main.c

all: $(PROGRAM)

$(PROGRAM): $(SOURCES)
	$(CC) -std=c99 $(CFLAGS) $(LDFLAGS) -o $@ $(SOURCES) $(LDLIBS)

clean:
	rm -f $(PROGRAM)

install: $(PROGRAM)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp -f $(PROGRAM) $(DESTDIR)$(BINDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(PROGRAM)
