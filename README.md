Here's a comprehensive bilingual README for your linear buffer implementation:

# Linear Buffer Implementation / 线性缓冲区实现

## English Version

### Overview
A lightweight, efficient linear buffer implementation in C that provides FIFO (First-In-First-Out) data management. Ideal for embedded systems, communication protocols, and any application requiring simple data buffering.

### Features
- **Simple API**: Easy-to-use push/pop/peek operations
- **Efficient**: O(1) operations for all functions
- **Memory Safe**: Bounds checking on all operations
- **Thread-Unsafe**: Designed for single-threaded use
- **No Dynamic Allocation**: Works with pre-allocated memory

### API Documentation

#### Initialization
```c
int linearbuffer_init(linearbuffer_t *lb, uint8_t *buffer, uint32_t size);
```
Initializes a linear buffer with the provided memory region.

#### Push Data
```c
int linearbuffer_push(linearbuffer_t *lb, uint8_t *data, uint32_t size);
```
Adds data to the end of the buffer.

#### Pop Data
```c
int linearbuffer_pop(linearbuffer_t *lb, uint8_t *data, uint32_t size);
```
Removes data from the front of the buffer.

#### Peek Data
```c
int linearbuffer_peek(linearbuffer_t *lb, uint8_t **data, uint32_t *size);
```
Views data at the front of the buffer without removal.

#### Utility Functions
```c
uint32_t linearbuffer_size(linearbuffer_t *lb);       // Total buffer size
uint32_t linearbuffer_data_len(linearbuffer_t *lb);   // Current data length
uint32_t linearbuffer_space_len(linearbuffer_t *lb);  // Remaining space
```

### Usage Example
```c
uint8_t buffer[256];
linearbuffer_t lb;

// Initialize
linearbuffer_init(&lb, buffer, sizeof(buffer));

// Push data
const char *msg = "Hello";
linearbuffer_push(&lb, (uint8_t*)msg, strlen(msg)+1);

// Peek data
uint8_t *peek_data;
uint32_t peek_size;
linearbuffer_peek(&lb, &peek_data, &peek_size);

// Pop data
uint8_t pop_data[256];
linearbuffer_pop(&lb, pop_data, peek_size);
```

### Building and Installing
```bash
mkdir build & cd build
cmake ..
cmake --build .
sudo cmake --install .
```

### Testing
Google Test cases are provided in the `tests/` directory.

## 中文版本

### 概述
一个用C语言实现的轻量级高效线性缓冲区，提供FIFO（先进先出）数据管理。适用于嵌入式系统、通信协议和任何需要简单数据缓冲的场景。

### 特性
- **简单API**：易用的push/pop/peek操作
- **高效**：所有操作都是O(1)时间复杂度
- **内存安全**：所有操作都有边界检查
- **非线程安全**：设计用于单线程环境
- **无动态内存分配**：使用预分配内存工作

### API文档

#### 初始化
```c
int linearbuffer_init(linearbuffer_t *lb, uint8_t *buffer, uint32_t size);
```
用指定的内存区域初始化线性缓冲区。

#### 压入数据
```c
int linearbuffer_push(linearbuffer_t *lb, uint8_t *data, uint32_t size);
```
向缓冲区末尾添加数据。

#### 弹出数据
```c
int linearbuffer_pop(linearbuffer_t *lb, uint8_t *data, uint32_t size);
```
从缓冲区头部移除数据。

#### 查看数据
```c
int linearbuffer_peek(linearbuffer_t *lb, uint8_t **data, uint32_t *size);
```
查看缓冲区头部的数据（不移除）。

#### 工具函数
```c
uint32_t linearbuffer_size(linearbuffer_t *lb);       // 缓冲区总大小
uint32_t linearbuffer_data_len(linearbuffer_t *lb);   // 当前数据长度
uint32_t linearbuffer_space_len(linearbuffer_t *lb);  // 剩余空间
```

### 使用示例
```c
uint8_t buffer[256];
linearbuffer_t lb;

// 初始化
linearbuffer_init(&lb, buffer, sizeof(buffer));

// 压入数据
const char *msg = "你好";
linearbuffer_push(&lb, (uint8_t*)msg, strlen(msg)+1);

// 查看数据
uint8_t *peek_data;
uint32_t peek_size;
linearbuffer_peek(&lb, &peek_data, &peek_size);

// 弹出数据
uint8_t pop_data[256];
linearbuffer_pop(&lb, pop_data, peek_size);
```

### 编译和安装
```bash
mkdir build & cd build
cmake ..
cmake --build .
sudo cmake --install .
```

### 测试
在`tests/`目录中提供了Google Test测试用例。

### 许可证
MIT License - 详见LICENSE文件
