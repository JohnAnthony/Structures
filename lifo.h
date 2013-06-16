/*
 * Simple lifo (stack) implementation. Blocking in/out available.
 * This is *not* thread safe. Possible future additions may include
 * blocking, but this may only be availble in the threadsafe version
 *
 * @TODO: Doxygen, thorough testing
 *
 * Created by John Anthony. See LICENSE file for licensing information.
 */

#ifndef __LIFO_H
#define __LIFO_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct lifo {
    size_t size;
    void *base;
    void *tip;
    void *end;
};

/**
 * lifo_init - create a new lifo with provided buffer
 * @lifo: lifo struct to work on
 * @buffer: Piece of memory to use as the lifo's stack space
 * @sz: size of buffer to be allocated
 */
static inline bool
lifo_init(struct lifo *lifo, void *buffer, size_t sz) {
    lifo->size = sz;
    lifo->base = buffer;
    lifo->tip = lifo->base;
    lifo->end = lifo->base + sz;
    return true;
}

/**
 * lifo_alloc - create a new lifo with dynamic buffer
 * @lifo: lifo struct to work on
 * @sz: size of buffer to be allocated
 */
static inline bool
lifo_alloc(struct lifo *lifo, size_t sz) {
    void *buffer = malloc(sz);
    return buffer ? lifo_init(lifo, buffer, sz) : false;
}

static inline size_t
lifo_in(struct lifo *lifo, const void *from, size_t len) {
    len = MIN(len, lifo->size - (size_t)lifo->tip);
    memcpy(lifo->tip, from, len);
    lifo->tip += len;
    return len;
}

static inline size_t
lifo_out(struct lifo *lifo, void *to, size_t len) {
    len = MIN(len, lifo->tip - lifo->base);
    lifo->tip -= len;
    memcpy(to, lifo->tip, len);
    return len;
}

static inline size_t
lifo_out_peek(struct lifo *lifo, void *to, size_t len) {
    void *tmp_tip;
    
    len = MIN(len, lifo->tip - lifo->base);
    tmp_tip = lifo->tip - len;
    memcpy(to, tmp_tip, len);
    return len;
}

static inline size_t
lifo_len(struct lifo *lifo) {
    return lifo->tip - lifo->base;
}

static inline size_t
lifo_avail(struct lifo *lifo) {
    return lifo->end - lifo->tip;
}

static inline bool
lifo_is_empty(struct lifo *lifo) {
    return lifo->tip == lifo->base;
}

static inline bool
lifo_is_full(struct lifo *lifo) {
    return lifo->tip == lifo->end;
}

static inline void
lifo_reset(struct lifo *lifo) {
    lifo->tip = lifo->base;
}

lifo_free(struct lifo *lifo) {
    free(lifo->base);
    free(lifo);
}
    
#endif
