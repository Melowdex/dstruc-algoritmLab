
FLAGS = -std=c11 -Werror -lm $(shell pkg-config --cflags --libs check)

compile: backtrack.c
	@echo "$(TITLE_COLOR)Compiling backtrack.c$(NO_COLOR)"
	@mkdir -p build
	gcc -c backtrack.c -g $(FLAGS)
	gcc -o build/backtrack backtrack.o $(FLAGS)

run: compile
	@echo "$(TITLE_COLOR)Running backtrack$(NO_COLOR)"
	./build/backtrack

debug: build/backtrack
	@echo "$(TITLE_COLOR)running backtrack.c in debug mode$(NO_COLOR)"
	CK_FORK=no gdb -q build/backtrack

.PHONY: clean
clean:
	rm -f build/backtrack
