HEADERS=huftree.h splist.h
SOURCE=huftree_test.c huftree.c 
EXE=build/huftree_test

TITLE_COLOR = \033[33m
NO_COLOR = \033[0m

FLAGS = -std=c11 -Werror -lm $(shell pkg-config --cflags --libs check)

compile : $(SOURCE) $(HEADERS)
	@echo "$(TITLE_COLOR)Compiling huftree_test$(NO_COLOR)"
	@mkdir -p build
	gcc -c huftree_test.c huftree.c -g $(FLAGS)
	gcc huftree_test.o huftree.o splist.o -o build/huftree_test $(FLAGS)

run : compile
	@echo "$(TITLE_COLOR)Running huftree_test$(NO_COLOR)"
	./build/huftree_test

.PHONY : clean cppcheck valgrind coverage

cppcheck : $(SOURCE) $(HEADERS)
	@echo "$(TITLE_COLOR)Running cppcheck :$(NO_COLOR)"
	cppcheck --enable=all --suppress=missingIncludeSystem --error-exitcode=1 $(SOURCE) $(HEADERS)

valgrind : compile
	@echo "$(TITLE_COLOR)Running Valgrind :$(NO_COLOR)"
	CK_FORK=no valgrind --leak-check=full --track-origins=yes ./build/huftree_test

debug: build/huftree_test
	@echo "$(TITLE_COLOR)running UNIT TEST in debuf mode$(NO_COLOR)"
	CK_FORK=no gdb -q build/huftree_test

coverage :
	@mkdir -p build
	gcc $(SOURCE)  -O0  --coverage -o build/huftree_test $(FLAGS) -dumpbase ''
	./build/huftree_test
	gcov -o ./build -p  $(SOURCE)
	mv *.gcov build
	lcov --capture --directory ./build --output-file ./build/coverage.info
	genhtml -o ./build/test_coverage -t "splist test coverage" --num-spaces 4 ./build/coverage.info
