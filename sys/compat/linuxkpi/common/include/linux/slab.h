/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013, 2014 Mellanox Technologies, Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */
#ifndef	_LINUX_SLAB_H_
#define	_LINUX_SLAB_H_

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/proc.h>
#include <vm/uma.h>

#include <linux/lkpi_uma.h>
#include <linux/lkpi_malloc.h>
#include <linux/types.h>
#include <linux/gfp.h>

MALLOC_DECLARE(M_KMALLOC);

#define	kvmalloc(size)			kmalloc((size), 0)
#define	kzalloc(size, flags)		kmalloc((size), M_ZERO | ((flags) ? (flags) : M_NOWAIT))
#define	kzalloc_node(size, flags, node)	kzalloc(size, flags)
#define	kfree_const(ptr)		kfree(ptr)
#define	krealloc(ptr, size, flags)	lkpi_realloc((ptr), (size), M_KMALLOC, (flags))
#define	kcalloc(n, size, flags)	        kmalloc((n) * (size), flags | M_ZERO)
#define	vzalloc(size)			kzalloc(size, GFP_KERNEL | __GFP_NOWARN)
#define	vfree(arg)			kfree(arg)
#define	kvfree(arg)			kfree(arg)
#define	vmalloc(size)                   kmalloc(size, GFP_KERNEL)
#define	__vmalloc(size, flags, other)                   kmalloc(size, (flags))
#define	vmalloc_node(size, node)        kmalloc(size, GFP_KERNEL)
#define	vmalloc_user(size)              kmalloc(size, GFP_KERNEL | __GFP_ZERO)
#define __kmalloc			kmalloc

/**
 * kmalloc_array - allocate memory for an array.
 * @n: number of elements.
 * @size: element size.
 * @flags: the type of memory to allocate (see kmalloc).
 */


/*
 * Prefix some functions with linux_ to avoid namespace conflict
 * with the OpenSolaris code in the kernel.
 */
#define	kmem_cache		linux_kmem_cache
#define	kmem_cache_create(...)	linux_kmem_cache_create(__VA_ARGS__)
#define	kmem_cache_alloc(...)	linux_kmem_cache_alloc(__VA_ARGS__)
#define	kmem_cache_free(...) 	linux_kmem_cache_free(__VA_ARGS__)
#define	kmem_cache_destroy(...) linux_kmem_cache_destroy(__VA_ARGS__)

struct linux_kmem_cache {
	uma_zone_t	cache_zone;
	void		(*cache_ctor)(void *);
};

#define	SLAB_HWCACHE_ALIGN	0x0001

static inline void *
kmalloc(int size, gfp_t flags)
{

	return (lkpi_malloc(size, M_KMALLOC, flags ? flags : M_NOWAIT));
}


static inline void *
kmalloc_array(size_t n, size_t size, gfp_t flags)
{
	if (size != 0 && n > SIZE_MAX / size)
		return NULL;
	return kmalloc(n * size, flags);
}


static inline void
kfree(const void *ptr)
{
	lkpi_free(__DECONST(void *, ptr), M_KMALLOC);
}

static inline int
linux_kmem_ctor(void *mem, int size, void *arg, int flags)
{
	void (*ctor)(void *);

	ctor = arg;
	ctor(mem);

	return (0);
}

static inline struct kmem_cache *
linux_kmem_cache_create(char *name, size_t size, size_t align, u_long flags,
    void (*ctor)(void *))
{
	struct kmem_cache *c;

	c = lkpi_malloc(sizeof(*c), M_KMALLOC, M_WAITOK);
	if (align)
		align--;
	if (flags & SLAB_HWCACHE_ALIGN)
		align = UMA_ALIGN_CACHE;
	c->cache_zone = lkpi_uma_zcreate(name, size, ctor ? linux_kmem_ctor : NULL,
	    NULL, NULL, NULL, align, 0);
	c->cache_ctor = ctor;

	return (c);
}

static inline void *
linux_kmem_cache_alloc(struct kmem_cache *c, int flags)
{
	return lkpi_uma_zalloc_arg(c->cache_zone, c->cache_ctor, (flags ? flags : M_NOWAIT));
}

static inline void *
kmem_cache_zalloc(struct kmem_cache *c, int flags)
{
	return lkpi_uma_zalloc_arg(c->cache_zone, c->cache_ctor, (flags ? flags : M_NOWAIT) |M_ZERO);
}

static inline void
linux_kmem_cache_free(struct kmem_cache *c, void *m)
{
	lkpi_uma_zfree(c->cache_zone, m);
}

static inline void
linux_kmem_cache_destroy(struct kmem_cache *c)
{
	lkpi_uma_zdestroy(c->cache_zone);
	lkpi_free(c, M_KMALLOC);
}

#endif	/* _LINUX_SLAB_H_ */
