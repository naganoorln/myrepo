CC = gcc
CFLAGS = -g -O0

all: test_math

test_math: math_utils.o test_math.o
	$(CC) $(CFLAGS) -o test_math math_utils.o test_math.o

math_utils.o: math_utils.c
	$(CC) $(CFLAGS) -c math_utils.c

test_math.o: test_math.c
	$(CC) $(CFLAGS) -c test_math.c

clean:
	rm -f *.o test_math

