#ifndef __LINEARBUFFER_H
#define __LINEARBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef struct linearbuffer
{
    uint8_t *bp;
    uint8_t *sp;
    uint8_t *top;
    uint8_t *region;
}
linearbuffer_t;

int linearbuffer_init(linearbuffer_t *lb, uint8_t *buffer, uint32_t size);

int linearbuffer_push(linearbuffer_t *lb, uint8_t *data, uint32_t size);

int linearbuffer_pop(linearbuffer_t *lb, uint8_t *data, uint32_t size);

int linearbuffer_peek(linearbuffer_t *lb, uint8_t **data, uint32_t *size);

static inline uint32_t linearbuffer_size(linearbuffer_t *lb)
{
    return lb ? (lb->top - lb->region) : 0;
}

static inline uint32_t linearbuffer_data_len(linearbuffer_t *lb)
{
    return lb ? (lb->sp - lb->bp) : 0;
}

static inline uint32_t linearbuffer_space_len(linearbuffer_t *lb)
{
    return lb ? (linearbuffer_size(lb) - linearbuffer_data_len(lb)) : 0;
}

#ifdef __cplusplus
}
#endif

#endif /* __LINEARBUFFER_H */
