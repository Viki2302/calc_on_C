CC=gcc
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c11
FLAGS_TEST_LIBS = -lcheck -lm -lpthread
#
SRC=s21_smartcalc.c


HEADER=s21_smartcalc.h
NAME=s21_smartcalc.a
CREDITHEAD=s21_credit.h
CREDIT=s21_credit.c
OBJ=$(patsubst %.c, %.o, $(SRC))
OS = $(shell uname)

.PHONY: all build static install uninstall rebuild dist test gcov_report clean m

all: build static tests

build:
	$(CC) $(CFLAGS) -c $(SRC)

static:
	ar rc s21_smartcalc.a $(OBJ)
	ranlib s21_smartcalc.a

tests: build static s21_test_smartcalc.c
	$(CC) $(CFLAGS) -c s21_test_smartcalc.c -o s21_test_smartcalc.o 
	$(CC) s21_test_smartcalc.o $(NAME) $(CREDIT) $(FLAGS_TEST_LIBS) -o s21_test_smartcalc
	./s21_test_smartcalc

gcov_report: all
	$(CC) $(CFLAGS) --coverage s21_test_smartcalc.c $(SRC) $(NAME) $(CREDIT) $(FLAGS_TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html


install:
	make clean
	mkdir build
	cd smartcalc && qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc/smartcalc.app build

uninstall:
	rm -rf build*

dvi:
	open readme.html

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	mv ./build/SmartCalc.app Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/

clean:
	rm -rf *.{a,o,dSYM,out}
	rm -rf $(EXECUTABLE)
	rm -rf gcov_report
	rm -rf report
	rm -rf CPPLINT.cfg
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf Archive_SmartCalc_v1.0 
	rm -rf *tgz
	rm -rf build
	rm -rf gcov_test

rebuild: clean all

check: tests
	@cp ../materials/linters/.clang-format .
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	@CK_FORK=no leaks --atExit -- ./s21_test_smartcalc
