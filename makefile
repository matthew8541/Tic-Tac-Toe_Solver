# Boilerplate makefile for Assignment 2
# Feel free to edit or use your own versions if desired.

# Replace 'header1.h', 'header2.h', 'object1.o', 'object2.o', and 'executable'
# with your filenames. It's fine if you only have one header, just delete
# 'header2.h' in that case.


# What compiler do you use? Default is gcc.
CC=gcc

# Your headers go here. It's fine to only have one.
# generate.h
DEPS_1 = generate.h
DEPS_2 = solve.h

# List of the object files that will be built. Replace the dummy-files with
# names corresponding to your source files. I.E. if you have source_1.c and
# source_2.c, these would be source_1.o and source_2.o
# main_generate.o generate.o 
OBJ_1 = generate.o main_generate.o
OBJ_2 = main_solve.o solve.o

# This is your actual executable to build. In general, just name this the same
# as whichever .c file has the main() function, with no suffix.
# main_solve
EXE_1 = main_generate
EXE_2 = main_solve

################################################################################
## You should not need to change anything below this divider
################################################################################


# Default (first in the file) target. Will build your executable from your
# object files.
$(EXE_1): $(OBJ_1)
	$(CC) -o $@ $^

$(EXE_2): $(OBJ_2)
	$(CC) -o $@ $^

# This just makes sure your prerequisites exist before trying to build your
# object files.
$(OBJ_1): $(DEPS_1)
$(OBJ_2): $(DEPS_2)


# Pattern rule that will build the listed object files from corresponding C
# files, and has your dependency list as a prerequisite
%.o: %.c
	$(CC) -c -o $@ $<

# .PHONY tells the makefile that the "clean" target isn't a file.
.PHONY: clean all
all: $(EXE_1) $(EXE_2)

# remove object files and executable created by make
clean:
	-rm $(OBJ_1) $(EXE_1) $(OBJ_2) $(EXE_2)



