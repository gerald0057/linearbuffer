#include <gtest/gtest.h>
#include <linearbuffer/inc/linearbuffer.h>

class LinearBufferTest : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            buffer = new uint8_t[BUFFER_SIZE];
            ASSERT_EQ(linearbuffer_init(&lb, buffer, BUFFER_SIZE), 0);
        }
        void TearDown() override
        {
            delete[] buffer;
        }

        const uint32_t BUFFER_SIZE = 256;
        uint8_t* buffer;
        linearbuffer_t lb;
};

// Test initialization
TEST_F(LinearBufferTest, Initialization) {
    EXPECT_EQ(lb.region, buffer);
    EXPECT_EQ(lb.top, buffer + BUFFER_SIZE);
    EXPECT_EQ(lb.bp, lb.region);
    EXPECT_EQ(lb.sp, lb.region);
    EXPECT_EQ(linearbuffer_size(&lb), BUFFER_SIZE);
    EXPECT_EQ(linearbuffer_data_len(&lb), 0);
    EXPECT_EQ(linearbuffer_space_len(&lb), BUFFER_SIZE);
}

// Test pushing data
TEST_F(LinearBufferTest, PushData) {
    const char* test_str = "Test push data";
    uint32_t str_len = strlen(test_str) + 1; // Include null terminator

    EXPECT_EQ(linearbuffer_push(&lb, (uint8_t*)test_str, str_len), str_len);
    EXPECT_EQ(linearbuffer_data_len(&lb), str_len);
    EXPECT_EQ(linearbuffer_space_len(&lb), BUFFER_SIZE - str_len);
    EXPECT_EQ(lb.bp, lb.region);
    EXPECT_EQ(lb.sp, lb.region + str_len);
}

// Test peeking data
TEST_F(LinearBufferTest, PeekData) {
    const char* test_str = "Test peek data";
    uint32_t str_len = strlen(test_str) + 1;
    ASSERT_EQ(linearbuffer_push(&lb, (uint8_t*)test_str, str_len), str_len);

    uint8_t* peek_data;
    uint32_t peek_size;
    EXPECT_EQ(linearbuffer_peek(&lb, &peek_data, &peek_size), 0);
    EXPECT_EQ(peek_size, str_len);
    EXPECT_EQ(memcmp(peek_data, test_str, str_len), 0);
}

// Test popping data
TEST_F(LinearBufferTest, PopData) {
    const char* test_str = "Test pop data";
    uint32_t str_len = strlen(test_str) + 1;
    ASSERT_EQ(linearbuffer_push(&lb, (uint8_t*)test_str, str_len), str_len);

    uint8_t pop_buffer[256];
    EXPECT_EQ(linearbuffer_pop(&lb, pop_buffer, str_len), str_len);
    EXPECT_EQ(memcmp(pop_buffer, test_str, str_len), 0);
    EXPECT_EQ(linearbuffer_data_len(&lb), 0);
    EXPECT_EQ(lb.bp, lb.sp);
}

// Test multiple push/pop operations
TEST_F(LinearBufferTest, MultipleOperations) {
    const char* str1 = "First string";
    const char* str2 = "Second string";
    uint32_t len1 = strlen(str1) + 1;
    uint32_t len2 = strlen(str2) + 1;

    // Push first string
    ASSERT_EQ(linearbuffer_push(&lb, (uint8_t*)str1, len1), len1);
    EXPECT_EQ(linearbuffer_data_len(&lb), len1);

    // Push second string
    ASSERT_EQ(linearbuffer_push(&lb, (uint8_t*)str2, len2), len2);
    EXPECT_EQ(linearbuffer_data_len(&lb), len1 + len2);

    // Pop first string
    uint8_t pop_buffer1[256];
    EXPECT_EQ(linearbuffer_pop(&lb, pop_buffer1, len1), len1);
    EXPECT_EQ(memcmp(pop_buffer1, str1, len1), 0);
    EXPECT_EQ(linearbuffer_data_len(&lb), len2);

    // Pop second string
    uint8_t pop_buffer2[256];
    EXPECT_EQ(linearbuffer_pop(&lb, pop_buffer2, len2), len2);
    EXPECT_EQ(memcmp(pop_buffer2, str2, len2), 0);
    EXPECT_EQ(linearbuffer_data_len(&lb), 0);
}

// Test buffer overflow
TEST_F(LinearBufferTest, BufferOverflow) {
    uint8_t large_data[BUFFER_SIZE + 1];
    memset(large_data, 'A', sizeof(large_data));

    // Should fail to push data larger than buffer
    EXPECT_NE(linearbuffer_push(&lb, large_data, sizeof(large_data)), sizeof(large_data));
    EXPECT_EQ(linearbuffer_data_len(&lb), BUFFER_SIZE);
}

// Test pop more than available
TEST_F(LinearBufferTest, PopMoreThanAvailable) {
    const char* test_str = "Test data";
    uint32_t str_len = strlen(test_str) + 1;
    ASSERT_EQ(linearbuffer_push(&lb, (uint8_t*)test_str, str_len), str_len);

    uint8_t pop_buffer[256];
    // Try to pop more than we pushed
    EXPECT_NE(linearbuffer_pop(&lb, pop_buffer, str_len + 1), str_len + 1);
    // Data all popped
    EXPECT_EQ(linearbuffer_data_len(&lb), 0);
}

// Test peek with empty buffer
TEST_F(LinearBufferTest, PeekEmptyBuffer) {
    uint8_t *peek_data;
    uint32_t peek_size;
    linearbuffer_peek(&lb, &peek_data, &peek_size);
    EXPECT_EQ(peek_data, lb.bp);
    EXPECT_EQ(peek_size, 0);
}

// Test pop from empty buffer
TEST_F(LinearBufferTest, PopEmptyBuffer) {
    uint8_t pop_buffer[256];
    EXPECT_NE(linearbuffer_pop(&lb, pop_buffer, 1), 1);
}

// Test boundary conditions
TEST_F(LinearBufferTest, BoundaryConditions) {
    // Fill buffer to exact capacity
    uint8_t full_data[BUFFER_SIZE];
    memset(full_data, 'B', sizeof(full_data));
    
    EXPECT_EQ(linearbuffer_push(&lb, full_data, sizeof(full_data)), sizeof(full_data));
    EXPECT_EQ(linearbuffer_data_len(&lb), BUFFER_SIZE);
    EXPECT_EQ(linearbuffer_space_len(&lb), 0);

    // Try to push one more byte (should fail)
    uint8_t extra_byte = 0xAA;
    EXPECT_NE(linearbuffer_push(&lb, &extra_byte, 1), 1);

    // Pop all data
    uint8_t pop_buffer[BUFFER_SIZE];
    EXPECT_EQ(linearbuffer_pop(&lb, pop_buffer, sizeof(pop_buffer)), sizeof(pop_buffer));
    EXPECT_EQ(memcmp(pop_buffer, full_data, sizeof(full_data)), 0);
    EXPECT_EQ(linearbuffer_data_len(&lb), 0);
}
