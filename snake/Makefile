CC = gcc
FLAGS = -ggdb3 -Wall -Wextra -Wshadow -std=gnu11 -fsanitize=address -Wno-unused-parameter

# Linking ncurses works differently on Linux and Mac. Detect
# OS to account for this
HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
ifeq ($(SYSTEM),Darwin)
LIBS = -lncurses
FLAGS += -D_XOPEN_SOURCE_EXTENDED
else
LIBS = $(shell ncursesw5-config --libs)
FLAGS += $(shell ncursesw5-config --cflags)
endif

FILES = $(wildcard src/*.c) $(wildcard src/*.h)
OBJS = src/game.o src/game_setup.o src/render.o src/common.o src/linked_list.o src/mbstrings.o
TEST_OBJS = src/game_test.c src/linked_list_test.c src/test_runner.c
BINS = snake autograder

TEST_COUNT = 50
TESTS = $(shell seq 1 1 $(TEST_COUNT))

# How verbose should test output be? 0 gives default output, 1 gives
# each step of the board as the snake moves.
# Options are 0 or 1
#
# To choose one, you can edit the variable below, or specify its value on the
# command line.
#    $ make check -B V=1
#
V ?= 0
ifeq ($(V),1)
FLAGS += -DVERBOSE
endif

all: $(BINS)

# wildcard rule for compiling object file from source and header
src/%.o: src/%.c src/%.h
	$(CC) $(FLAGS) -c $< -o $@

autograder: $(OBJS) test/autograder.c
	$(CC) $(FLAGS) $^ $(LIBS) -o $@ -lm

snake: $(OBJS) src/snake.c
	$(CC) $(FLAGS) $^ $(LIBS) -o $@ -lm

check: autograder
	python3 test/autograder.py $(TESTS)

# this target supports running individual tests (for example, `check-3`)
# and ranges of tests (for example, `check-5-10`).
check-%: autograder
	python3 test/autograder.py $(shell echo -n "$(patsubst check-%, %, $@)" | awk -F '-' '{if (NF==2) print $$1 " 1 " $$2; else print $$1 " 1 " $$1}' | xargs seq)

# run a test under gdb
check-gdb-%: autograder
	sudo echo ""
	DEBUG=1 python3 test/autograder.py "$(patsubst check-gdb-%, %, $@)" & sleep 0.5 && sudo gdb -p `pgrep autograder`

format:
	clang-format -style=file -i $(FILES)

clean:
	rm -f $(BINS)
	rm -f ${OBJS}

.PHONY: all clean format echo check

