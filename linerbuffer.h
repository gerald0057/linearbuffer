#ifndef __AUDIO_STACK_H
#define __AUDIO_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define audio_malloc malloc
#define audio_free free

typedef struct audio_stack
{
    uint8_t *bp;
    uint8_t *sp;
    uint8_t *top;
    uint8_t *region;
}
audio_stack_t;

int audio_stack_init(audio_stack_t *stack, uint8_t *buffer, uint32_t size);

int audio_stack_push(audio_stack_t *stack, uint8_t *data, uint32_t size);

int audio_stack_pop(audio_stack_t *stack, uint8_t *data, uint32_t size);

int audio_stack_peek(audio_stack_t *stack, uint8_t **data, uint32_t *size);

static inline uint32_t audio_stack_size(audio_stack_t *stack)
{
    return stack ? (stack->top - stack->region) : 0;
}

static inline uint32_t audio_stack_data_len(audio_stack_t *stack)
{
    return stack ? (stack->sp - stack->bp) : 0;
}

static inline uint32_t audio_stack_space_len(audio_stack_t *stack)
{
    return stack ? (audio_stack_size(stack) - audio_stack_data_len(stack)) : 0;
}

#ifdef __cplusplus
}
#endif

#endif /* __AUDIO_STACK_H */
