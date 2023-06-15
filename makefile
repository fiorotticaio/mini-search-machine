DIR_ENTRADA_1=exemplo
DIR_ENTRADA_2=exemplo2

# all: clean compile runAll valAll
all: run1

compile: 
	@ gcc -o trab3 main.c

run1: clean compile
	@ ./trab3 ${DIR_ENTRADA_1}

run2: clean compile
	@ ./trab3 ${DIR_ENTRADA_2}

runAll: run1 run2

val1: clean compile
	@ valgrind --leak-check=full ./trab3 ${DIR_ENTRADA_1}

val2: clean compile
	@ valgrind --leak-check=full ./trab3 ${DIR_ENTRADA_2}

valAll: val1 val2

clean:
	@ rm -f trab3