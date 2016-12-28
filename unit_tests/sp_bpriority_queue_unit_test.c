#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

//Checks if copy Works
bool queueBasicCopyTest() {
	int maxSize = 4;
	int dataIndex[] = {5,2,3,7};
	double dataValue[] = {80,40,1.444,3};
	SPBPQueue* myQueue;
	BPQueueElement* elmentPoin1;
	BPQueueElement* elmentPoin2;
	SPBPQueue* copy;
	elmentPoin1=(BPQueueElement*)malloc(sizeof(BPQueueElement));
	assert(NULL != elmentPoin1);
	elmentPoin2=(BPQueueElement*)malloc(sizeof(BPQueueElement));
	assert(NULL != elmentPoin2);

	myQueue= spBPQueueCreate(maxSize);

	for (int i = 0; i < sizeof(*dataIndex); i++) {
		spBPQueueEnqueue(myQueue,dataIndex[i],dataValue[i]);
	}

	copy = spBPQueueCopy(myQueue);
	ASSERT_TRUE(spBPQueueGetMaxSize(myQueue) == spBPQueueGetMaxSize(copy));
	ASSERT_TRUE(spBPQueueSize(myQueue) == spBPQueueSize(copy));
	for (int i = 0; i < maxSize; i++) {
		spBPQueuePeek(myQueue,elmentPoin1);
		spBPQueuePeek(copy,elmentPoin2);
		ASSERT_TRUE(elmentPoin1->index==elmentPoin2->index);
		ASSERT_TRUE(elmentPoin1->value==elmentPoin2->value);
		spBPQueueDequeue(myQueue);
		spBPQueueDequeue(copy);
	}
	spBPQueueDestroy(myQueue);
	spBPQueueDestroy(copy);
	return true;
}
bool pointBasicL2Distance() {
//	double data1[2] = { 1.0, 1.0 };
//	double data2[2] = { 1.0, 0.0 };
//	int dim1 = 2;
//	int dim2 = 2;
//	int index1 = 1;
//	int index2 = 1;
//	SPPoint* p = spPointCreate(data1, dim1, index1);
//	SPPoint* q = spPointCreate(data2, dim2, index2);
//	ASSERT_TRUE(spPointL2SquaredDistance(p,p) == 0.0);
//	ASSERT_TRUE(spPointL2SquaredDistance(q,q) == 0.0);
//	ASSERT_FALSE(spPointL2SquaredDistance(p,q) == 0.0);
//	spPointDestroy(p);
//	spPointDestroy(q);
	return true;
}
int main() {
	RUN_TEST(queueBasicCopyTest);
	RUN_TEST(pointBasicL2Distance);
	return 0;
}
