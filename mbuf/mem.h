/**
 * @file re_mem.h  Interface to Memory management with reference counting
 *
 * Copyright (C) 2010 Creytiv.com
 */

#ifndef ___MEM_H___
#define ___MEM_H___

#include <stdint.h>

/**
 * Defines the memory destructor handler, which is called when the reference
 * of a memory object goes down to zero
 *
 * @param data Pointer to memory object
 */
typedef void (mem_destroy_h)(void *data);

void    *mem_alloc(size_t size, mem_destroy_h *dh);
void    *mem_zalloc(size_t size, mem_destroy_h *dh);
void    *mem_realloc(void *data, size_t size);
void    *mem_reallocarray(void *ptr, size_t nmemb,
			  size_t membsize, mem_destroy_h *dh);
void    *mem_ref(void *data);
void    *mem_deref(void *data);
uint32_t mem_nrefs(const void *data);


#endif // ___MEM_H___
