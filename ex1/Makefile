HEADERS=splist.h
SOURCE=splist.c splist_test.c
EXE=build/splist

TITLE_COLOR = \033[33m
NO_COLOR = \033[0m

FLAGS = -std=c11 -Werror -lm $(shell pkg-config --cflags --libs check)

compile : $(SOURCE) $(HEADERS)
	@echo "$(TITLE_COLOR)Compiling UNIT TEST$(NO_COLOR)"
	@mkdir -p build
	gcc splist.c splist_test.c -g -o build/splist_test $(FLAGS)

test : compile
	@echo "$(TITLE_COLOR)Running UNIT TEST$(NO_COLOR)"
	./build/splist_test

.PHONY : clean cppcheck valgrind

cppcheck : $(SOURCE) $(HEADERS)
	@echo "$(TITLE_COLOR)Running cppcheck :$(NO_COLOR)"
	cppcheck --enable=all --suppress=missingIncludeSystem --error-exitcode=1 $(SOURCE) $(HEADERS)

valgrind : compile
	@echo "$(TITLE_COLOR)Running Valgrind :$(NO_COLOR)"
	CK_FORK=no valgrind --leak-check=full --track-origins=yes ./build/splist_test

clean:
	rm -f *.o a.out $(EXE) $(EXE)_test *~
	rm -r build