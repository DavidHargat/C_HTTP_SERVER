
HEADERS =\

OBJECTS=\
build/main.o \

.PHONY: all
all: build/app

build/%.o: src/%.c $(HEADERS)
	gcc -c -o $@ $<

build/app: $(OBJECTS)
	gcc -o $@ $^
