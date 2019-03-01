/**
 * @file mem.c  Memory management with reference counting
 *
 * Copyright (C) 2010 Creytiv.com
 */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "list.h"
#include "mbuf.h"
#include "mem.h"


/** Defines a reference-counting memory object */
struct mem {
	uint32_t nrefs;     /**< Number of references  */
	mem_destroy_h *dh;  /**< Destroy handler       */
};


/**
 * Allocate a new reference-counted memory object
 *
 * @param size Size of memory object
 * @param dh   Optional destructor, called when destroyed
 *
 * @return Pointer to allocated object
 */
void *mem_alloc(size_t size, mem_destroy_h *dh)
{
	struct mem *m;

	m = malloc(sizeof(*m) + size);
	if (!m)
		return NULL;

	m->nrefs = 1;
	m->dh    = dh;

	return (void *)(m + 1);
}


/**
 * Allocate a new reference-counted memory object. Memory is zeroed.
 *
 * @param size Size of memory object
 * @param dh   Optional destructor, called when destroyed
 *
 * @return Pointer to allocated object
 */
void *mem_zalloc(size_t size, mem_destroy_h *dh)
{
	void *p;

	p = mem_alloc(size, dh);
	if (!p)
		return NULL;

	memset(p, 0, size);

	return p;
}


/**
 * Re-allocate a reference-counted memory object
 *
 * @param data Memory object
 * @param size New size of memory object
 *
 * @return New pointer to allocated object
 *
 * @note Realloc NULL pointer is not supported
 */
void *mem_realloc(void *data, size_t size)
{
	struct mem *m, *m2;

	if (!data)
		return NULL;

	m = ((struct mem *)data) - 1;

	m2 = realloc(m, sizeof(*m2) + size);

	if (!m2) {
		return NULL;
	}

	return (void *)(m2 + 1);
}


#ifndef SIZE_MAX
#define SIZE_MAX    (~((size_t)0))
#endif


/**
 * Re-allocate a reference-counted array
 *
 * @param ptr      Pointer to existing array, NULL to allocate a new array
 * @param nmemb    Number of members in array
 * @param membsize Number of bytes in each member
 * @param dh       Optional destructor, only used when ptr is NULL
 *
 * @return New pointer to allocated array
 */
void *mem_reallocarray(void *ptr, size_t nmemb, size_t membsize,
		       mem_destroy_h *dh)
{
	size_t tsize;

	if (membsize && nmemb > SIZE_MAX / membsize) {
		return NULL;
	}

	tsize = nmemb * membsize;

	if (ptr) {
		return mem_realloc(ptr, tsize);
	}
	else {
		return mem_alloc(tsize, dh);
	}
}


/**
 * Reference a reference-counted memory object
 *
 * @param data Memory object
 *
 * @return Memory object (same as data)
 */
void *mem_ref(void *data)
{
	struct mem *m;

	if (!data)
		return NULL;

	m = ((struct mem *)data) - 1;

	++m->nrefs;

	return data;
}


/**
 * Dereference a reference-counted memory object. When the reference count
 * is zero, the destroy handler will be called (if present) and the memory
 * will be freed
 *
 * @param data Memory object
 *
 * @return Always NULL
 */
void *mem_deref(void *data)
{
	struct mem *m;

	if (!data)
		return NULL;

	m = ((struct mem *)data) - 1;

	if (--m->nrefs > 0)
		return NULL;

	if (m->dh)
		m->dh(data);

	/* NOTE: check if the destructor called mem_ref() */
	if (m->nrefs > 0)
		return NULL;

	free(m);

	return NULL;
}


/**
 * Get number of references to a reference-counted memory object
 *
 * @param data Memory object
 *
 * @return Number of references
 */
uint32_t mem_nrefs(const void *data)
{
	struct mem *m;

	if (!data)
		return 0;

	m = ((struct mem *)data) - 1;

	return m->nrefs;
}


/**
 * Print memory status
 *
 * @param pf     Print handler for debug output
 * @param unused Unused parameter
 *
 * @return 0 if success, otherwise errorcode
 */
int mem_status(struct re_printf *pf, void *unused)
{
	(void)pf;
	(void)unused;
	return 0;
}


/**
 * Get memory statistics
 *
 * @param mstat Returned memory statistics
 *
 * @return 0 if success, otherwise errorcode
 */
int mem_get_stat(struct memstat *mstat)
{
	if (!mstat)
		return EINVAL;
	return ENOSYS;
}
