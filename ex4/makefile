BUILDDIR = build
TITLE_COLOR = \033[33m
NO_COLOR = \033[0m

# requirements : flex bison libfl-dev libbison-dev
# compile flags to omit minor warnings : -Wno-unused-function
CFLAGS = -Wall -c -Wno-unused-function
LFLAGS = -Wall -ly -lfl -lm

###
# Info on automatic variables :
# $@ : The name of the target of the rule (first part, before the colon)
# $< : The name of the first prerequisite (first dependency, after the colon)
# $^ : The names of all the prerequisites (everything after the colon)
# $* : The matched pattern by % in the target of the rule (aka the stem)
###

all: symb hexlex hexyacc

symb: $(BUILDDIR)/symb.o $(BUILDDIR)/hash.o
	@echo "$(TITLE_COLOR)Linking symbol file$(NO_COLOR)"
	gcc $(BUILDDIR)/symb.o $(BUILDDIR)/hash.o -Wall -lm -o $(BUILDDIR)/symb

hexlex: $(BUILDDIR)/hexlex.yy.o $(BUILDDIR)/hash.o
	@echo "$(TITLE_COLOR)Linking lex output file$(NO_COLOR)"
	gcc $(BUILDDIR)/hexlex.yy.o $(BUILDDIR)/hash.o $(LFLAGS) -o $(BUILDDIR)/symbl

hexyacc: $(BUILDDIR)/hexyacc.tab.o $(BUILDDIR)/hexyacc.yy.o $(BUILDDIR)/hash.o
	@echo "$(TITLE_COLOR)Linking lex/yacc output files$(NO_COLOR)"
	gcc $(BUILDDIR)/hexyacc.tab.o $(BUILDDIR)/hexyacc.yy.o $(BUILDDIR)/hash.o $(LFLAGS) -o $(BUILDDIR)/symbly

# When a certain .o file is not found in the build folder, compile it from the .c file, and do a cppcheck
# % is a wildcard : e.g. when compiling tmp/main.o he will look for main.c
$(BUILDDIR)/%.o: %.c
	@echo "$(TITLE_COLOR)Compiling $< $(NO_COLOR)"
	@mkdir -p $(BUILDDIR)
	gcc $< $(CFLAGS) -o $@

# When looking for a .yy.c file generate first generate it from the .l file using flex
%.yy.c: %.l
	@echo "$(TITLE_COLOR)Running flex on $< $(NO_COLOR)"
	flex -o $@ $<

# When looking for a .tab.c file generate first generate it from the .y file using bison
%.tab.c: %.y
	@echo "$(TITLE_COLOR)Running bison on $< $(NO_COLOR)"
	bison -Wcounterexamples -d -o $@ $<

# do not look for files called clean or cppcheck this will be always a target
.PHONY : clean cppcheck

cppcheck : $(SOURCE) $(HEADERS)
	@echo "$(TITLE_COLOR)Running cppcheck $(NO_COLOR)"
	cppcheck --enable=all --suppress=missingIncludeSystem --error-exitcode=1 symbl.c hash.c

clean:
	rm -rf build hexlex.yy.c hexyacc.tab.h
