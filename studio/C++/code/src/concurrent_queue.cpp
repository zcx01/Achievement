#include "concurrent_queue.hpp"
#include "ObjectFactory.h"
#include "commondefine.hpp"
#include <iostream>
#include "concurrent_queue/concurrentqueue.h"

ConcurrentQueueTest::ConcurrentQueueTest(/* args */) 
{
    moodycamel::ConcurrentQueue<int> queue_;
    queue_.enqueue(25);
    int out;
    queue_.try_dequeue(out);
    COUT(out)
}

CUSTOMEGISTER(ConcurrentQueue,ConcurrentQueueTest)