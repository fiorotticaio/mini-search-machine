DIR_ENTRADA_0=exemplo0
DIR_ENTRADA_1=exemplo1
DIR_ENTRADA_2=exemplo2

# all: clean compile runAll valAll
all: run0

compile: documento rbtDocs rbtPal rbtMain
	@ gcc -o trab3 documento.o RBTdocs.o RBTpal.o main.c

documento:
	@ gcc -c documento.c

rbtDocs:
	@ gcc -c RBTdocs.c

rbtPal:
	@ gcc -c RBTpal.c

rbtMain:
	@ gcc -c RBTmain.c

run0: clean compile
	@ ./trab3 ${DIR_ENTRADA_0}

run1: clean compile
	@ ./trab3 ${DIR_ENTRADA_1}

run2: clean compile
	@ ./trab3 ${DIR_ENTRADA_2}

runAll: run0 run1 run2

val0: clean compile
	@ valgrind --leak-check=full ./trab3 ${DIR_ENTRADA_0}

val1: clean compile
	@ valgrind --leak-check=full ./trab3 ${DIR_ENTRADA_1}

val2: clean compile
	@ valgrind --leak-check=full ./trab3 ${DIR_ENTRADA_2}

valAll: val0 val1 val2

clean:
	@ rm -f trab3 *.o