#include <string.h>

#include <ert/ert.h>
#include <ert/priority_queue.h>

static PriorityQueueItem*
_GetItemByIndex(PriorityQueue* pq, size_t index);

static RESULT
PriorityQueue_InternalDequeue(PriorityQueue* pq, void* dest, int isPeek);

/**
 * 从索引获取元素
 */
inline static PriorityQueueItem*
_GetItemByIndex(PriorityQueue* pq, size_t index) {
    size_t itemSize = (pq->ItemSize + 1);
    PriorityQueueItem* pitems = (PriorityQueueItem*)(pq->Buffer + (itemSize * index));
    return pitems;
}


/**
 * 初始化队列
 */
void 
PriorityQueue_Init(PriorityQueue* pq, void* buffer, size_t capacity, size_t itemContentSize) {
    pq->Buffer = buffer;
    pq->Count = 0;
    pq->ItemSize = itemContentSize;
    pq->Capacity = capacity;
    //All priority value set to -1
    for(size_t i = 0; i < capacity; i++) {
        PriorityQueueItem* pitem = _GetItemByIndex(pq, i);
        pitem->Priority = PQ_EMPTY_SLOT;
    }
}


/**
 * 入队
 */
RESULT
PriorityQueue_Enqueue(PriorityQueue* pq, int8_t priority, const void* item) {
    if(pq->Count == pq->Capacity)
    {
        return RESULT_ERROR;
    }
 
    PriorityQueueItem* pitem = NULL;
    for (size_t i = 0; i < pq->Capacity; i++)
    {
        pitem = _GetItemByIndex(pq, i);
        if(pitem->Priority == PQ_EMPTY_SLOT) {
            break;
        }
    }
    pitem->Priority = priority;
    memcpy(pitem->Content, item, pq->ItemSize);
    pq->Count++;
    return RESULT_OK;
}


/**
 * 按照优先级出队
 */
RESULT
PriorityQueue_Dequeue(PriorityQueue* pq, void* dest) {
    return PriorityQueue_InternalDequeue(pq, dest, 0);
}


/** 查看下一个要出队的元素但不出队 */
RESULT 
PriorityQueue_PeekNext(PriorityQueue* pq, void* dest) {
    return PriorityQueue_InternalDequeue(pq, dest, 1);
}


static RESULT 
PriorityQueue_InternalDequeue(PriorityQueue* pq, void* dest, int isPeek) {
    if (pq->Count == 0) {
        return RESULT_ERROR;
    }
    size_t pos = 0;
    PriorityQueueItem* item = _GetItemByIndex(pq, 0);
    int maxp = item->Priority;
    for (size_t i = 1; i < pq->Capacity; i++)
    {
        PriorityQueueItem* item = _GetItemByIndex(pq, i);
        if (maxp < item->Priority) {
            pos = i;
            maxp = item->Priority;
        }
    }
    item = _GetItemByIndex(pq, pos);
    memcpy(dest, item->Content, pq->ItemSize);
    if(!isPeek) {
        item->Priority = -1;
        pq->Count--;
    }
    return RESULT_OK;
}

inline size_t 
PriorityQueue_Available(PriorityQueue* pq) {
    return pq->Capacity - pq->Count;
}