
# List of all object files
OBJECTS = build/main.o\
	  build/file.o\
	  build/args.o

HEADERS = src/socklib.h\
	  src/file.h\
	  src/args.h


.PHONY: all
all: build/app

# Build .o from .c files,
# found in their respective /build and /src folders
# Explanation:
#   gcc = C Compiler
#   -c  = gcc flag to compile source files without linking
#   -o  = gcc flag to
#   $@  = the target
#   $<  = the first prerequisite
build/%.o: src/%.c $(HEADERS)
	gcc -c $< -o $@

# Build our 'app' executable from our files
build/app: $(OBJECTS) 
	gcc -o build/app $^

