#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

int main() {
	SPBPQueue* myQueue;
	BPQueueElement* elmentPoin1;
	myQueue = spBPQueueCreate(2);
	spBPQueueEnqueue(myQueue, 1, 0.5);
	spBPQueueEnqueue(myQueue, 2, 1.5);
	spBPQueueEnqueue(myQueue, 3, 2.5);
	elmentPoin1 = (BPQueueElement*) malloc(sizeof(BPQueueElement));
	spBPQueuePeek(myQueue, elmentPoin1);
	printf("%d", elmentPoin1->index);
	spBPQueueDequeue(myQueue);
	spBPQueuePeek(myQueue, elmentPoin1);
	printf("%d", elmentPoin1->index);
	spBPQueueDequeue(myQueue);
	return 0;
  }
