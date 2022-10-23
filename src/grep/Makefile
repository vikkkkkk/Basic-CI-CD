CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep.o: s21_grep.c
	${CC} ${CFLAGS} -c s21_grep.c -o s21_grep.o
	
s21_grep: s21_grep.o
	${CC} s21_grep.o -o s21_grep

test: s21_grep
	bash grep_test.sh

clean:
	rm -rf s21_grep.o
	rm -rf s21_grep
	rm -rf log.txt

rebuild: clean all
