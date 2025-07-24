#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <linearbuffer/inc/linearbuffer.h>

void print_buffer_status(linearbuffer_t *lb) {
    printf("Buffer status: Size=%u, DataLen=%u, SpaceLeft=%u\n",
           linearbuffer_size(lb),
           linearbuffer_data_len(lb),
           linearbuffer_space_len(lb));
}

int main() {
    printf("Linear Buffer Demonstration\n");
    printf("===========================\n\n");

    // Create a buffer with 128 bytes
    uint8_t buffer[128];
    linearbuffer_t lb;

    // Initialize the buffer
    printf("1. Initializing buffer...\n");
    if (linearbuffer_init(&lb, buffer, sizeof(buffer)) != 0) {
        printf("Failed to initialize buffer!\n");
        return 1;
    }
    print_buffer_status(&lb);
    printf("\n");

    // Push some data
    printf("2. Pushing data into buffer...\n");
    const char *message1 = "Hello, Linear Buffer!";
    if (linearbuffer_push(&lb, (uint8_t *)message1, strlen(message1) + 1) != (strlen(message1) + 1)) {
        printf("Failed to push data!\n");
        return 1;
    }
    print_buffer_status(&lb);
    printf("\n");

    // Peek at the data
    printf("3. Peeking at buffer contents...\n");
    uint8_t *peek_data;
    uint32_t peek_size;
    if (linearbuffer_peek(&lb, &peek_data, &peek_size) == 0) {
        printf("Peeked data (%u bytes): \"%s\"\n", peek_size, (char *)peek_data);
    } else {
        printf("Failed to peek data!\n");
    }
    print_buffer_status(&lb);
    printf("\n");

    // Push more data
    printf("4. Pushing more data...\n");
    const char *message2 = "This is a second message.";
    if (linearbuffer_push(&lb, (uint8_t *)message2, strlen(message2) + 1) != (strlen(message2) + 1)) {
        printf("Failed to push second message!\n");
        return 1;
    }
    print_buffer_status(&lb);
    printf("\n");

    // Pop the first message
    printf("5. Popping first message...\n");
    uint8_t pop_buffer[128];
    uint32_t message1_len = strlen(message1) + 1;
    if (linearbuffer_pop(&lb, pop_buffer, message1_len) == 0) {
        printf("Popped data: \"%s\"\n", (char *)pop_buffer);
    } else {
        printf("Failed to pop data!\n");
    }
    print_buffer_status(&lb);
    printf("\n");

    // Show remaining data by peeking
    printf("6. Showing remaining data...\n");
    if (linearbuffer_peek(&lb, &peek_data, &peek_size) == 0) {
        printf("Remaining data (%u bytes): \"%s\"\n", peek_size, (char *)peek_data);
    } else {
        printf("Failed to peek remaining data!\n");
    }
    print_buffer_status(&lb);
    printf("\n");

    // Pop the remaining data
    printf("7. Popping remaining data...\n");
    uint32_t message2_len = strlen(message2) + 1;
    if (linearbuffer_pop(&lb, pop_buffer, message2_len) == 0) {
        printf("Popped data: \"%s\"\n", (char *)pop_buffer);
    } else {
        printf("Failed to pop remaining data!\n");
    }
    print_buffer_status(&lb);
    printf("\n");

    // Try to pop from empty buffer
    printf("8. Trying to pop from empty buffer...\n");
    if (linearbuffer_pop(&lb, pop_buffer, 1) == 0) {
        printf("Unexpected success popping from empty buffer!\n");
    } else {
        printf("Correctly failed to pop from empty buffer\n");
    }
    print_buffer_status(&lb);
    printf("\n");

    printf("Demo completed successfully!\n");
    return 0;
}
