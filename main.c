#include <stdio.h>
#include "string.h"
#include "save_alloc.h"

int c_byLine(FILE *f, char *buf, int n);

int main(int argc, char **argv)
{
	init_save_alloc();
	char *ptr = save_alloc(2000); ptr[0] = '1';
	char *ptr2 = save_alloc(2001); ptr2[0] = '2';
	char *ptr3 = save_alloc(233); ptr3[0] = '3';
	char *ptr4 = save_alloc(12); ptr4[0] = '4';
	if (save_free(ptr) != 0) { printf("1\n"); return 1; }
	if (save_free(ptr3) != 0) { printf("3\n"); return 3; }
	if (save_free(ptr4) != 0) { printf("4\n"); return 4; }
	if (save_free(ptr2) != 0) { printf("2\n"); return 2; }
	return 0;
}

int c_byLine(FILE *f, char *buf, int n)
{
	int read = 0, i = 0;
	for (; i < n; i++) {
		if ( !fread(buf+i, 1, 1, f) ) break;
		read++;
		if( *(buf+i) == '\0' ) break;
		if ( *(buf+i) == '\n' ) {
			*(buf+i) = '\0';
			break;
		}
	}
	return read;
}
