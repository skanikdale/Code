#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>


/*

The following code implements a producer/consumer queue. The queue is represented as a bounded circular buffer, and is protected by a
critical section. The code uses two condition variables: one used by producers (BufferNotFull) and one used by consumers (BufferNotEmpty).

The code calls the InitializeConditionVariable function to create the condition variables. The consumer threads call the 
SleepConditionVariableCS function to wait for items to be added to the queue and the WakeConditionVariable function to signal the producer 
that it is ready for more items. The producer threads call SleepConditionVariableCS to wait for the consumer to remove items from the queue and
WakeConditionVariable to signal the consumer that there are more items in the queue.

*/

#define BUFFER_SIZE 4
#define PRODUCER_SLEEP_TIME_MS 500
#define CONSUMER_SLEEP_TIME_MS 2000

LONG Buffer[BUFFER_SIZE];
LONG LastItemProduced;
ULONG QueueSize;
ULONG QueueStartOffset;

ULONG TotalItemsProduced;
ULONG TotalItemsConsumed;

CONDITION_VARIABLE BufferNotEmpty;
CONDITION_VARIABLE BufferNotFull;
CRITICAL_SECTION   BufferLock;

BOOL StopRequested;

DWORD WINAPI ProducerThreadProc (PVOID p)
{
    ULONG ProducerId = (ULONG)(ULONG_PTR)p;

    while (true)
    {
        // Produce a new item.

        Sleep (rand() % PRODUCER_SLEEP_TIME_MS);

        ULONG Item = InterlockedIncrement (&LastItemProduced);

        EnterCriticalSection (&BufferLock);

        while (QueueSize == BUFFER_SIZE && StopRequested == FALSE)
        {
            // Buffer is full - sleep so consumers can get items.
            SleepConditionVariableCS (&BufferNotFull, &BufferLock, INFINITE);
        }

        if (StopRequested == TRUE)
        {
            LeaveCriticalSection (&BufferLock);
            break;
        }

        // Insert the item at the end of the queue and increment size.

        Buffer[(QueueStartOffset + QueueSize) % BUFFER_SIZE] = Item;
        QueueSize++;
        TotalItemsProduced++;

        printf ("Producer %u: item %2d, queue size %2u\r\n", ProducerId, Item, QueueSize);

        LeaveCriticalSection (&BufferLock);

        // If a consumer is waiting, wake it.

        WakeConditionVariable (&BufferNotEmpty);
    }

    printf ("Producer %u exiting\r\n", ProducerId);
    return 0;
}

DWORD WINAPI ConsumerThreadProc (PVOID p)
{
    ULONG ConsumerId = (ULONG)(ULONG_PTR)p;

    while (true)
    {
        EnterCriticalSection (&BufferLock);

        while (QueueSize == 0 && StopRequested == FALSE)
        {
            // Buffer is empty - sleep so producers can create items.
           // wait for producer to create items
            SleepConditionVariableCS (&BufferNotEmpty, &BufferLock, INFINITE);
        }

        if (StopRequested == TRUE && QueueSize == 0)
        {
            LeaveCriticalSection (&BufferLock);
            break;
        }

        // Consume the first available item.

        LONG Item = Buffer[QueueStartOffset];

        QueueSize--;
        QueueStartOffset++;
        TotalItemsConsumed++;

        if (QueueStartOffset == BUFFER_SIZE)
        {
            QueueStartOffset = 0;
        }

        printf ("Consumer %u: item %2d, queue size %2u\r\n", 
            ConsumerId, Item, QueueSize);

        LeaveCriticalSection (&BufferLock);

        // If a producer is waiting, wake it.

        WakeConditionVariable (&BufferNotFull);

        // Simulate processing of the item.

        Sleep (rand() % CONSUMER_SLEEP_TIME_MS);
    }

    printf ("Consumer %u exiting\r\n", ConsumerId);
    return 0;
}

void producerConsumerTest()
{
    InitializeConditionVariable (&BufferNotEmpty);
    InitializeConditionVariable (&BufferNotFull);

    InitializeCriticalSection (&BufferLock);

    DWORD id;
    HANDLE hProducer1 = CreateThread (NULL, 0, ProducerThreadProc, (PVOID)1, 0, &id);
    HANDLE hConsumer1 = CreateThread (NULL, 0, ConsumerThreadProc, (PVOID)1, 0, &id);
    HANDLE hConsumer2 = CreateThread (NULL, 0, ConsumerThreadProc, (PVOID)2, 0, &id);

    puts ("Press enter to stop...");
    getchar();

    EnterCriticalSection (&BufferLock);
    StopRequested = TRUE;
    LeaveCriticalSection (&BufferLock);

    WakeAllConditionVariable (&BufferNotFull);
    WakeAllConditionVariable (&BufferNotEmpty);

    WaitForSingleObject (hProducer1, INFINITE);
    WaitForSingleObject (hConsumer1, INFINITE);
    WaitForSingleObject (hConsumer2, INFINITE);

    printf ("TotalItemsProduced: %u, TotalItemsConsumed: %u\r\n", 
        TotalItemsProduced, TotalItemsConsumed);
    
    return;
}














































/*
 Producer adds one int to shared array

 Consuemr will removes one int from shared array

 If array is empty consumer waits

 If array is full then producer waits

 */

//int shareArr[10];
//
//DWORD WINAPI producer(LPVOID Param)
//{ 
//  for(int i = 0; i <= 10; i++)
//  {
//    shareArr[i] = 10;
//  }
//
//  return 0;
//}
//
//DWORD WINAPI consumer(LPVOID Param)
//{ 
//
//  return 0;
//}
//
//
//void producerConsumerTest()
//{
//  DWORD  threadID; 
//  HANDLE pThread, cThread;
//
//  HANDLE mutex = CreateMutex(NULL, FALSE, NULL);
//
//  pThread = CreateThread(NULL, 0, producer, &mutex, 0, &threadID); 
//
//  cThread = CreateThread(NULL, 0, consumer, &mutex, 0, &threadID);
//
//  WaitForSingleObject(pThread, INFINITE);
//  WaitForSingleObject(cThread, INFINITE);
//}