/*
 * Simple lifo (stack) implementation.
 * This is a variation of lifo.h with thread safety for use with
 * POSIX semaphores
 *
 * If you need thread safety, define SAFE_DATA_STRUCTURES before
 * including this header
 *
 * @TODO: Thorough testing, DECLARE_LIFO & INIT_LIFO - static lifos
 *
 * Created by John Anthony. See LICENSE file for licensing information.
 */

#ifndef __LIFO_H
#define __LIFO_H
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct lifo {
    void *base;
    void *tip;
    void *end;
#ifdef SAFE_DATA_STRUCTURES
    sem_t sem;
#endif
};

/**
 * lifo_init - create a new lifo with provided buffer
 * @lifo: lifo struct to work on
 * @buffer: Piece of memory to use as the lifo's stack space
 * @sz: size of buffer provided
 */
static bool
lifo_init(struct lifo *lifo, void *buffer, size_t sz) {
    lifo->base = buffer;
    lifo->tip = lifo->base;
    lifo->end = lifo->base + sz;
#ifdef SAFE_DATA_STRUCTURES
    sem_init(&lifo->sem, 0, 1);
#endif /* SAFE_DATA_STRUCTURES */
    return true;
}

/**
 * lifo_alloc - create a new lifo and dynamic buffer
 * @lifo: lifo struct to work on
 * @sz: size of buffer to be allocated
 */
static bool
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
static size_t
lifo_in(struct lifo *lifo, const void *from, size_t len) {
#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    len = MIN(len, lifo->end - lifo->tip);
    memcpy(lifo->tip, from, len);
    lifo->tip += len;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return len;
}

/**
 * lifo_out - remove data from the stack
 * @lifo: lifo struct to work on
 * @to: memory to copy to
 * @len: number of bytes to copy
 */
static size_t
lifo_out(struct lifo *lifo, void *to, size_t len) {
#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    len = MIN(len, lifo->tip - lifo->base);
    lifo->tip -= len;
    memcpy(to, lifo->tip, len);
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return len;
}

/**
 * lifo_out_peek - recover data from stack without moving tip
 * @lifo: lifo struct to work on
 * @to: memory to copy to
 * @len: number of bytes to copy
 */
static size_t
lifo_out_peek(struct lifo *lifo, void *to, size_t len) {
    void *tmp_tip;
    
#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    len = MIN(len, lifo->tip - lifo->base);
    tmp_tip = lifo->tip - len;
    memcpy(to, tmp_tip, len);
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return len;
}

/**
 * lifo_sz - get the buffer size of a lifo
 * @lifo: lifo struct to test
 */
static size_t
lifo_sz(struct lifo *lifo) {
    size_t ret;

#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    ret = lifo->end - lifo->base;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return ret;
}

/**
 * lifo_len - report amount of space used in lifo's buffer
 * @lifo: lifo struct to test
 */
static size_t
lifo_len(struct lifo *lifo) {
    size_t ret;

#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    ret = lifo->tip - lifo->base;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return ret;
}

/**
 * lifo_avail - report amount of available space in a lifo's buffer
 * @lifo: lifo struct to test
 */
static size_t
lifo_avail(struct lifo *lifo) {
    size_t ret;

#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    ret = lifo->end - lifo->tip;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return ret;
}

/**
 * lifo_is_empty - test for zero bytes of buffer used in lifo
 * @lifo: lifo struct to test
 */
static bool
lifo_is_empty(struct lifo *lifo) {
    bool ret;

#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    ret = lifo->tip == lifo->base;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return ret;
}

/**
 * lifo_is_full - test for zero bytes of buffer available in lifo
 * @lifo: lifo struct to test
 */
static bool
lifo_is_full(struct lifo *lifo) {
    bool ret;

#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    ret = lifo->tip == lifo->end;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return ret;
}

/**
 * lifo_resize - resize lifo buffer and correctly move pointers
 * @lifo: lifo struct to work on
 * @sz: Desired buffer size
 */
static bool
lifo_resize(struct lifo *lifo, size_t sz) {
    void *buffer;

#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    buffer = realloc(lifo->base, sz);
    if (!buffer) {
#ifdef SAFE_DATA_STRUCTURES
        sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
        return false;
    }
    lifo->tip = lifo->tip - lifo->base + buffer;
    lifo->end = lifo->end - lifo->base + buffer;
    lifo->base = buffer;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    return true;
}

/**
 * lifo_reset - empty a lifo ready for new use
 * @lifo: lifo struct to test
 */
static void
lifo_reset(struct lifo *lifo) {
#ifdef SAFE_DATA_STRUCTURES
    sem_wait(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    lifo->tip = lifo->base;
#ifdef SAFE_DATA_STRUCTURES
    sem_post(&lifo->sem);
    sem_destroy(&lifo->sem);
    sem_init(&lifo->sem, 0, 1);
#endif /* SAFE_DATA_STRUCTURES */
}

/**
 * lifo_free - release memory used by a dynamically allocated lifo
 * @lifo: lifo struct to test
 */
static inline void
lifo_free(struct lifo *lifo) {
#ifdef SAFE_DATA_STRUCTURES
    sem_destroy(&lifo->sem);
#endif /* SAFE_DATA_STRUCTURES */
    free(lifo->base);
    free(lifo);
}
    
#endif
