CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat.o: s21_cat.c
	${CC} ${CFLAGS} -c s21_cat.c -o s21_cat.o

s21_cat: s21_cat.o
	${CC} s21_cat.o -o s21_cat

test: s21_cat
	bash s21_test.sh

clean:
	rm -rf s21_cat.o
	rm -rf s21_cat
	rm -rf log.txt

rebuild: clean all
