/*
 * Simple lifo (stack) implementation.
 * This is *not* thread safe. Possible future additions may include
 * blocking, but this may only be availble in the threadsafe version
 *
 * @TODO: Thorough testing, DECLARE_LIFO, INIT_LIFO
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
    void *base;
    void *tip;
    void *end;
};

/**
 * lifo_init - create a new lifo with provided buffer
 * @lifo: lifo struct to work on
 * @buffer: Piece of memory to use as the lifo's stack space
 * @sz: size of buffer provided
 */
static inline bool
lifo_init(struct lifo *lifo, void *buffer, size_t sz) {
    lifo->base = buffer;
    lifo->tip = lifo->base;
    lifo->end = lifo->base + sz;
    return true;
}

/**
 * lifo_alloc - create a new lifo and dynamic buffer
 * @lifo: lifo struct to work on
 * @sz: size of buffer to be allocated
 */
static inline bool
lifo_alloc(struct lifo *lifo, size_t sz) {
    void *buffer = malloc(sz);
    return buffer ? lifo_init(lifo, buffer, sz) : false;
}

/**
 * lifo_in - add data to the stack
 * @lifo: lifo struct to work on
 * @from: memory to copy from
 * @len: number of bytes to copy
 */
static inline size_t
lifo_in(struct lifo *lifo, const void *from, size_t len) {
    len = MIN(len, lifo->end - lifo->tip);
    memcpy(lifo->tip, from, len);
    lifo->tip += len;
    return len;
}

/**
 * lifo_out - remove data from the stack
 * @lifo: lifo struct to work on
 * @to: memory to copy to
 * @len: number of bytes to copy
 */
static inline size_t
lifo_out(struct lifo *lifo, void *to, size_t len) {
    len = MIN(len, lifo->tip - lifo->base);
    lifo->tip -= len;
    memcpy(to, lifo->tip, len);
    return len;
}

/**
 * lifo_out_peek - recover data from stack without moving tip
 * @lifo: lifo struct to work on
 * @to: memory to copy to
 * @len: number of bytes to copy
 */
static inline size_t
lifo_out_peek(struct lifo *lifo, void *to, size_t len) {
    void *tmp_tip;
    
    len = MIN(len, lifo->tip - lifo->base);
    tmp_tip = lifo->tip - len;
    memcpy(to, tmp_tip, len);
    return len;
}

/**
 * lifo_sz - get the buffer size of a lifo
 * @lifo: lifo struct to test
 */
static inline size_t
lifo_sz(struct lifo *lifo) {
    return lifo->end - lifo->base;
}

/**
 * lifo_len - report amount of space used in lifo's buffer
 * @lifo: lifo struct to test
 */
static inline size_t
lifo_len(struct lifo *lifo) {
    return lifo->tip - lifo->base;
}

/**
 * lifo_avail - report amount of available space in a lifo's buffer
 * @lifo: lifo struct to test
 */
static inline size_t
lifo_avail(struct lifo *lifo) {
    return lifo->end - lifo->tip;
}

/**
 * lifo_is_empty - test for zero bytes of buffer used in lifo
 * @lifo: lifo struct to test
 */
static inline bool
lifo_is_empty(struct lifo *lifo) {
    return lifo->tip == lifo->base;
}

/**
 * lifo_is_full - test for zero bytes of buffer available in lifo
 * @lifo: lifo struct to test
 */
static inline bool
lifo_is_full(struct lifo *lifo) {
    return lifo->tip == lifo->end;
}

/**
 * lifo_reset - empty a lifo ready for new use
 * @lifo: lifo struct to test
 */
static inline void
lifo_reset(struct lifo *lifo) {
    lifo->tip = lifo->base;
}

/**
 * lifo_free - release memory used by a dynamically allocated lifo
 * @lifo: lifo struct to test
 */
lifo_free(struct lifo *lifo) {
    free(lifo->base);
    free(lifo);
}
    
#endif
