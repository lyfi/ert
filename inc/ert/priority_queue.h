#pragma once

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    int8_t      Priority;
    uint8_t     Content[];
} PriorityQueueItem;

typedef struct
{
    uint8_t*            Buffer;
    size_t              ItemSize;
    volatile size_t     Count;
    size_t              Capacity;
} PriorityQueue;

enum {
    PQ_PRIORITY_LOWEST = -127,
    PQ_PRIORITY_LOWER =  -64,
    PQ_PRIORITY_NORMAL = 0,
    PQ_PRIORITY_HIGHER = 64,
    PQ_PRIORITY_HIGHEST = 127,
};

#define PQ_EMPTY_SLOT                (-1)
#define PQ_ITEM_SIZE(ele_type)       (sizeof(PriorityQueueItem) + sizeof(ele_type))

#define PQ_STATIC_BUFFER(buf_name, ele_type, capacity)      static uint8_t buf_name[PQ_ITEM_SIZE(ele_type) * capacity]
#define PQ_BUFFER(buf_name, ele_type, capacity)             uint8_t buf_name[PQ_ITEM_SIZE(ele_type) * capacity]

void PriorityQueue_Init(PriorityQueue* pq, void* buffer, size_t capacity, size_t itemContentSize);
RESULT PriorityQueue_Enqueue(PriorityQueue* pq, int8_t priority, const void* item);
RESULT PriorityQueue_Dequeue(PriorityQueue* pq, void* dest);
RESULT PriorityQueue_PeekNext(PriorityQueue* pq, void* dest);
size_t PriorityQueue_Available(PriorityQueue* pq);


#ifdef __cplusplus
}
#endif