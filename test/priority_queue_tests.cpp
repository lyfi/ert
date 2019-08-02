#include <gtest/gtest.h>
#include <cmath>
#include <stdio.h>

#include "ert/ert.h"
#include "ert/priority_queue.h"

TEST(PriorityQueueTests, Init) { 
    PriorityQueue pq;
    PQ_BUFFER(pq_buf, uint32_t, 100);
    PriorityQueue_Init(&pq, pq_buf, 100, sizeof(uint32_t));

    ASSERT_EQ((sizeof(uint32_t) + sizeof(PriorityQueueItem)) * 100, sizeof(pq_buf));
    ASSERT_EQ(sizeof(uint32_t), pq.ItemSize);
    ASSERT_EQ(100, pq.Capacity);
    ASSERT_EQ(0, pq.Count);
}

TEST(PriorityQueueTests, EnqueueAndDequeue) { 
    PriorityQueue pq;
    PQ_BUFFER(pq_buf, uint32_t, 100);
    PriorityQueue_Init(&pq, pq_buf, 100, sizeof(uint32_t));

    uint32_t x = 1;
    PriorityQueue_Enqueue(&pq, PQ_PRIORITY_NORMAL, &x);

    x = 2;
    PriorityQueue_Enqueue(&pq, PQ_PRIORITY_HIGHER, &x);

    x = 3;
    PriorityQueue_Enqueue(&pq, PQ_PRIORITY_HIGHEST, &x);

    x = 4;
    PriorityQueue_Enqueue(&pq, PQ_PRIORITY_HIGHEST, &x);

    ASSERT_EQ(100, pq.Capacity);
    ASSERT_EQ(4, pq.Count);

    PriorityQueue_Dequeue(&pq, &x);
    ASSERT_EQ(3, pq.Count);
    ASSERT_EQ(3, x);

    PriorityQueue_Dequeue(&pq, &x);
    ASSERT_EQ(2, pq.Count);
    ASSERT_EQ(4, x);

    PriorityQueue_Dequeue(&pq, &x);
    ASSERT_EQ(1, pq.Count);
    ASSERT_EQ(2, x);

    PriorityQueue_Dequeue(&pq, &x);
    ASSERT_EQ(0, pq.Count);
    ASSERT_EQ(1, x);
}
 