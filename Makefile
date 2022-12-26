CC = gcc
SRCPATH = ./src
BUILDPATH = ./build
sources = $(wildcard $(SRCPATH)/*.c)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -W -Wall -DDEBUG=1
target = main

$(target) : $(objects)
	$(CC) -o $(target) $(objects)

%.o : %.c
	$(CC) -c $(flags) $< -o $@

clean :
	rm -rf $(target) $(objects)
