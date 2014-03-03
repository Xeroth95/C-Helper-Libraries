DIR=~/C-Projekte/

all:	
	cd ${DIR}; gcc -g -o main main.c string.s save_alloc.c
