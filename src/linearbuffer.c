#include <linearbuffer.h>

int linearbuffer_init(linearbuffer_t *lb, uint8_t *buffer, uint32_t size)
{
    if (NULL == lb || NULL == buffer || 0 == size)
        return -1;

    lb->bp = lb->sp = lb->region = buffer;
    lb->top = lb->bp + size;

    return 0;
}

int linearbuffer_push(linearbuffer_t *lb, uint8_t *data, uint32_t size)
{
    uint32_t data_len, wr2end;

    if (NULL == lb || NULL == data)
        return -1;

    /* the space size between sp and top is enough */
    if ((lb->top - lb->sp) >= size)
    {
        memcpy(lb->sp, data, size);
        lb->sp += size;
        return size;
    }

    /* check the space between region start and bp */
    if (lb->region != lb->bp)
    {
        data_len = linearbuffer_data_len(lb);
        memmove(lb->region, lb->bp, data_len);
        lb->bp = lb->region;
        lb->sp = lb->bp + data_len;
    }

    /* copy the data */
    wr2end = lb->top - lb->sp;
    size = size > wr2end ? wr2end : size;
    memcpy(lb->sp, data, size);
    lb->sp += size;

    return size;
}

int linearbuffer_pop(linearbuffer_t *lb, uint8_t *data, uint32_t size)
{
    uint8_t *end;
    uint32_t pop_size;

    if (NULL == lb)
        return -1;

    /* find the end of data */
    end = lb->bp + size;
    if (end > lb->sp)
        end = lb->sp;

    /* copy data out if need */
    pop_size = (end - lb->bp);
    if (NULL != data)
        memcpy(data, lb->bp, pop_size);

    /* update the lb point */
    lb->bp = end;

    return pop_size;
}

int linearbuffer_peek(linearbuffer_t *lb, uint8_t **data, uint32_t *size)
{
    if (NULL == lb || NULL == data)
        return -1;

    *data = lb->bp;
    *size = linearbuffer_data_len(lb);

    return 0;
}
