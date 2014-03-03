#ifndef SAVE_ALLOC_H_GUARD
#define SAVE_ALLOC_H_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#ifdef SAVE_ALLOC_DEBUG
#include <assert.h>
#endif

struct gc;

int init_save_alloc();
void *save_alloc(size_t size);
int save_free(void *ptr);
void free_all();

#endif
