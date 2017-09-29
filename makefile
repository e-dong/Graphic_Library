CC=gcc
CFLAGS=-I.
DEPS = graphics.h
OBJ = driver_test.o graphic_library.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

driver_test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
