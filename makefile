# Builds the APC executable from all required object files
apc.exe: main.o apc.o addition.o subtraction.o multiplication.o division.o
	gcc -Wall -Wextra -std=c11 main.o apc.o addition.o subtraction.o multiplication.o division.o -o apc.exe

# Compiles the main program
main.o: main.c apc.h
	gcc -Wall -Wextra -std=c11 -c main.c -o main.o

# Compiles linked-list and validation helper functions
apc.o: apc.c apc.h
	gcc -Wall -Wextra -std=c11 -c apc.c -o apc.o

# Compiles addition
addition.o: addition.c apc.h
	gcc -Wall -Wextra -std=c11 -c addition.c -o addition.o

# Compiles subtraction
subtraction.o: subtraction.c apc.h
	gcc -Wall -Wextra -std=c11 -c subtraction.c -o subtraction.o

# Compiles multiplication
multiplication.o: multiplication.c apc.h
	gcc -Wall -Wextra -std=c11 -c multiplication.c -o multiplication.o

# Compiles division
division.o: division.c apc.h
	gcc -Wall -Wextra -std=c11 -c division.c -o division.o

# Removes generated object files and the executable
clean:
	rm -f *.o apc.exe

# Marks clean as a command rather than a file target
.PHONY: all clean
