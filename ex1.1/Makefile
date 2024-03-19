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

ofile: splist.c
	@echo "$(TITLE_COLOR)making o file$(NO_COLOR)"
	gcc -c splist.c -Wall -Werror -fPIC -o splist.o -g

.PHONY : clean cppcheck valgrind coverage

cppcheck : $(SOURCE) $(HEADERS)
	@echo "$(TITLE_COLOR)Running cppcheck :$(NO_COLOR)"
	cppcheck --enable=all --suppress=missingIncludeSystem --error-exitcode=1 $(SOURCE) $(HEADERS)

valgrind : compile
	@echo "$(TITLE_COLOR)Running Valgrind :$(NO_COLOR)"
	CK_FORK=no valgrind --leak-check=full --track-origins=yes ./build/splist_test

debug: build/splist_test
	@echo "$(TITLE_COLOR)running UNIT TEST in debuf mode$(NO_COLOR)"
	CK_FORK=no gdb -q build/splist_test

coverage :
	@mkdir -p build
	gcc $(SOURCE)  -O0  --coverage -o build/splist_test $(FLAGS) -dumpbase ''
	./build/splist_test
	gcov -o ./build -p  $(SOURCE)
	mv *.gcov build
	lcov --capture --directory ./build --output-file ./build/coverage.info
	genhtml -o ./build/test_coverage -t "splist test coverage" --num-spaces 4 ./build/coverage.info

clean:
	rm -f *.o a.out $(EXE) $(EXE)_test *~
	rm -r build