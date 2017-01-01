#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

//Checks if copy Works
bool queueBasicCopyTest() {
	int maxSize = 4;
	int dataIndex[] = { 5, 2, 3, 7 };
	double dataValue[] = { 80, 40, 10, 3 };
	SPBPQueue* myQueue;
	BPQueueElement* elmentPoin1;
	BPQueueElement* elmentPoin2;
	SPBPQueue* copy;
	elmentPoin1 = (BPQueueElement*) malloc(sizeof(BPQueueElement));
	assert(NULL != elmentPoin1);
	elmentPoin2 = (BPQueueElement*) malloc(sizeof(BPQueueElement));
	assert(NULL != elmentPoin2);

	myQueue = spBPQueueCreate(maxSize);

	for (int i = 0; i < (sizeof(dataIndex) / sizeof(*dataIndex)); i++) {
		spBPQueueEnqueue(myQueue, dataIndex[i], dataValue[i]);
	}

	copy = spBPQueueCopy(myQueue);
	ASSERT_TRUE(spBPQueueGetMaxSize(myQueue) == spBPQueueGetMaxSize(copy));
	ASSERT_TRUE(spBPQueueSize(myQueue) == spBPQueueSize(copy));
	for (int i = 0; i < maxSize; i++) {
		spBPQueuePeek(myQueue, elmentPoin1);
		spBPQueuePeek(copy, elmentPoin2);
		ASSERT_TRUE(elmentPoin1->index == elmentPoin2->index);
		ASSERT_TRUE(elmentPoin1->value == elmentPoin2->value);
		spBPQueueDequeue(myQueue);
		spBPQueueDequeue(copy);

	}
	spBPQueueDestroy(myQueue);
	spBPQueueDestroy(copy);
	free(elmentPoin1);
	free(elmentPoin2);
	return true;
}
//bounding check
bool queueBasicBound() {
	int maxSize = 4;
	int dataIndex[] = { 5, 2, 3, 7, 8, 9, 10 };
	double dataValue[] = { 80, 40, 10, 3, 1.4, 1.6, 90 };
	int sortIndex[] = { 8, 9, 7, 3 };
	double sortValue[] = { 1.4, 1.6, 3, 10 };
	SPBPQueue* myQueue;
	BPQueueElement* elmentPoin1;
	elmentPoin1 = (BPQueueElement*) malloc(sizeof(BPQueueElement));
	assert(NULL != elmentPoin1);

	myQueue = spBPQueueCreate(maxSize);

	for (int i = 0; i < (sizeof(dataIndex) / sizeof(*dataIndex)); i++) {
		spBPQueueEnqueue(myQueue, dataIndex[i], dataValue[i]);
	}

	ASSERT_TRUE(spBPQueueGetMaxSize(myQueue) == 4);
	ASSERT_TRUE(spBPQueueSize(myQueue) == 4);
	ASSERT_TRUE(spBPQueueMaxValue(myQueue) == 10);
	ASSERT_TRUE(spBPQueueMinValue(myQueue) == 1.4);
	ASSERT_TRUE(spBPQueueIsFull(myQueue));
	ASSERT_FALSE(spBPQueueIsEmpty(myQueue));

	for (int i = 0; i < maxSize; i++) {
		spBPQueuePeek(myQueue, elmentPoin1);
		ASSERT_TRUE(elmentPoin1->index == sortIndex[i]);
		ASSERT_TRUE(elmentPoin1->value == sortValue[i]);
		spBPQueueDequeue(myQueue);
	}
	ASSERT_FALSE(spBPQueueIsFull(myQueue));
	ASSERT_TRUE(spBPQueueIsEmpty(myQueue));

	free(elmentPoin1);
	spBPQueueDestroy(myQueue);
	return true;
}

//clearing check
bool queueBasicClear() {
	int maxSize = 4;
	int dataIndex[] = { 5, 2, 3, 7, 8, 9, 10 };
	double dataValue[] = { 80, 40, 10, 3, 1.4, 1.6, 90 };
	SPBPQueue* myQueue;
	BPQueueElement* elmentPoin1;
	elmentPoin1 = (BPQueueElement*) malloc(sizeof(BPQueueElement));
	assert(NULL != elmentPoin1);

	myQueue = spBPQueueCreate(maxSize);

	for (int i = 0; i < (sizeof(dataIndex) / sizeof(*dataIndex)); i++) {
		spBPQueueEnqueue(myQueue, dataIndex[i], dataValue[i]);
	}

	spBPQueueClear(myQueue);
	ASSERT_TRUE(spBPQueueGetMaxSize(myQueue) == 4);
	ASSERT_TRUE(spBPQueueSize(myQueue) == 0);
	ASSERT_TRUE(spBPQueueMaxValue(myQueue) < 0);
	ASSERT_TRUE(spBPQueueMinValue(myQueue) < 0);
	ASSERT_FALSE(spBPQueueIsFull(myQueue));
	ASSERT_TRUE(spBPQueueIsEmpty(myQueue));

	free(elmentPoin1);
	spBPQueueDestroy(myQueue);
	return true;
}
int main() {
	RUN_TEST(queueBasicCopyTest);
	RUN_TEST(queueBasicBound);
	RUN_TEST(queueBasicClear);
	return 0;
}
