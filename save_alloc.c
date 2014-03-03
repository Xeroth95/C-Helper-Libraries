#include "save_alloc.h"

/* implemented as binary tree */

struct gc
{
	struct gc_node *head;
};

struct gc_node
{
	void *ptr;
	struct gc_node *root;
	struct gc_node *left;
	struct gc_node *right;
};

struct gc *GARBAGE_COLLECTOR = NULL;

int init_save_alloc()
{
	if(GARBAGE_COLLECTOR == NULL)
		GARBAGE_COLLECTOR = malloc(sizeof(struct gc));
	if (GARBAGE_COLLECTOR == NULL)
		return 1;
	atexit(free_all);
	return 0;
}

void *save_alloc(size_t size)
{
	if(GARBAGE_COLLECTOR == NULL)
		return NULL;
	void *ptr = malloc(size);
	if (ptr == NULL)
		return NULL;
	struct gc_node **node = &GARBAGE_COLLECTOR->head;
	struct gc_node **next = node;
	while (*next != NULL) {
		node = next;
		if ((intptr_t) (*node)->ptr > (intptr_t) ptr)
			next = &(*node)->left;
		else
			next = &(*node)->right;
	}
	*next = malloc(sizeof(struct gc_node));
	if (*next == NULL) {
		free(ptr);
		return NULL;
	}
	(*next)->ptr = ptr;
	(*next)->left = NULL;
	(*next)->right = NULL;
	if (next == node)
		(*next)->root = NULL;
	else
		(*next)->root = *node;
	return ptr;
}

void remove(struct gc_node **node)
{
	if (*node == NULL) return;
	if ((*node)->left == NULL) {
		if ((*node)->right == NULL)
			*node = NULL;
		else
			*node = (*node)->right;
		return;
	}
	struct gc_node **current = &(*node)->left;
	while((*current)->right != NULL)
		current = &(*current)->right;
	(*current)->root->right = NULL;
	(*current)->root = (*node)->root;
        (*current)->left = (*node)->left;
	(*current)->right = (*node)->right;
	*node = *current;
}

int save_free(void *ptr)
{
	if (ptr == NULL)
		return 0;
	if(GARBAGE_COLLECTOR == NULL)
		return 1;
	struct gc_node **node = &GARBAGE_COLLECTOR->head;
	if (*node == NULL) goto found;
	while (*node != NULL) {
		if ((intptr_t) (*node)->ptr > (intptr_t) ptr)
			node = &(*node)->left;
		else if ((intptr_t) (*node)->ptr < (intptr_t) ptr)
			node = &(*node)->right;
		else
			break;
	}
	if (*node == NULL)
		return 2;
found:
	__asm__("nop");
	struct gc_node *cp = *node;
	remove(node);
	free(cp->ptr);
#ifdef SAVE_ALLOC_DEBUG
	free(ptr); // this should throw an exception (double free)
#endif

	free(cp);
	//*node = NULL;
	return 0;
}

void free_node(struct gc_node *node) {
	if (node == NULL) return;
	if (node->left != NULL) free_node(node->left);
	if (node->right != NULL) free_node(node->right);
	free(node->ptr);
	free(node);
}

void free_all() {
	if (GARBAGE_COLLECTOR == NULL)
		return;
	if (GARBAGE_COLLECTOR->head == NULL) {
		free(GARBAGE_COLLECTOR);
		return;
	}
	free_node(GARBAGE_COLLECTOR->head);
	free(GARBAGE_COLLECTOR);
}
