/* -*- linux -*- */

#include "save_alloc.h"
#include <stdlib.h>
#include <time.h>

#define LEVEL 4
/* implemented as a skip-list */

struct gc_node//save_alloc_node
{
	void **ptr;
	struct gc_node *next;
	struct gc_node *below;
};

struct gc//save_alloc_head
{
	struct gc_node *level[LEVEL];
};

struct gc *GARBAGE_COLLECTOR = NULL;

int init_save_alloc()
{
	if (GARBAGE_COLLECTOR != NULL) {
		fprintf(stderr, "Cannot initialize save alloc twice!\n");
		return 1;
	} else {
		GARBAGE_COLLECTOR = malloc(sizeof(struct gc));
		register int i = 0;
		while (i < LEVEL)
			GARBAGE_COLLECTOR->level[i++] = NULL;
	}
	if (GARBAGE_COLLECTOR == NULL) {
		fprintf(stderr, "Could not initialize save alloc!\n");
		return 1;
	}
	atexit(free_all);
	srand(time(NULL));
	return 0;
}

void *save_alloc(size_t size)
{
	if (GARBAGE_COLLECTOR == NULL) {
		fprintf(stderr, "Garbage Collector is not initialized!\n");
		return NULL;
	}
	void *ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "Could not allocate memory!\n");
		return NULL;
	}

	return ptr;
}

int save_free(void *ptr)
{
	return 0;
}

void free_all()
{

}
