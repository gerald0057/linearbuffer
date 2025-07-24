#include "audio_stack.h"

int audio_stack_init(audio_stack_t *stack, uint8_t *buffer, uint32_t size)
{
    if (NULL == stack || NULL == buffer || 0 == size)
        return -1;

    stack->bp = stack->sp = stack->region = buffer;
    stack->top = stack->bp + size;

    return 0;
}

int audio_stack_push(audio_stack_t *stack, uint8_t *data, uint32_t size)
{
    uint32_t data_len, wr2end;

    if (NULL == stack || NULL == data)
        return -1;

    /* the space size between sp and top is enough */
    if ((stack->top - stack->sp) >= size)
    {
        memcpy(stack->sp, data, size);
        stack->sp += size;
        return size;
    }

    /* check the space between region start and bp */
    if (stack->region != stack->bp)
    {
        data_len = audio_stack_data_len(stack);
        memmove(stack->region, stack->bp, data_len);
        stack->bp = stack->region;
        stack->sp = stack->bp + data_len;
    }

    /* copy the data */
    wr2end = stack->top - stack->sp;
    size = size > wr2end ? wr2end : size;
    memcpy(stack->sp, data, size);
    stack->sp += size;

    return size;
}

int audio_stack_pop(audio_stack_t *stack, uint8_t *data, uint32_t size)
{
    uint8_t *end;
    uint32_t pop_size;

    if (NULL == stack)
        return -1;

    /* find the end of data */
    end = stack->bp + size;
    if (end > stack->sp)
        end = stack->sp;

    /* copy data out if need */
    pop_size = (end - stack->bp);
    if (NULL != data)
        memcpy(data, stack->bp, pop_size);

    /* update the stack point */
    stack->bp = end;

    return pop_size;
}

int audio_stack_peek(audio_stack_t *stack, uint8_t **data, uint32_t *size)
{
    if (NULL == stack || NULL == data)
        return -1;

    *data = stack->bp;
    *size = audio_stack_data_len(stack);

    return 0;
}
