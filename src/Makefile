CC=g++
CFLAGS=--std=c++17 -Wall -Werror -Wextra -lm
CFLAGS2=-fprofile-arcs -ftest-coverage
WASH=rm -rf *.o *.a *.out *html *css *gcno *gcda .clang-format
OS=$(shell uname)
ifeq ($(OS), Linux)
	LFLAGS = -lgtest -pthread -lgmock --coverage
	LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s ./test.out
else
	LFLAGS = -fsanitize=address -lcheck -pthread -lgcov --coverage
	LEAKS=CK_FORK=no leaks --atExit -- ./test.out
endif

all: clean test matrix_oop.a gcov_report

matrix_oop.a: matrix.o
	ar rcs matrix_oop.a matrix.o

main: main.o matrix.o
	$(CC) $^ -lm -o main.out && ./main.out

main.o: main.cc
	$(CC) $(CFLAGS) -c $^

matrix.o: matrix.cc
	$(CC) $(CFLAGS) -c $^
 
gcov_report: test
	gcovr -r . --html --html-details -o gcov_report.html
	open gcov_report.html

test: test.o matrix_test.o
	$(CC) $^ -o test.out $(LFLAGS) && ./test.out

matrix_test.o: matrix.cc
	$(CC) $(CFLAGS) $(CFLAGS2) -c $^ -o $@

test.o: test.cc
	$(CC) $(CFLAGS2) -c $^ -o $@

check_clang: *.cc *.h
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $^

check_leaks:
	$(LEAKS)

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cc

clean:
	$(WASH)
	