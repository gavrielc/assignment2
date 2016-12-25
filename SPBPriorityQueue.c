#include <stdbool.h>
#include "SPBPriorityQueue.h"
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

/**
 * SP Bounded Priority Queue summary
 *
 * TODO Complete documentation
 */
#define EMPTY_BPQUEUE_ELEMENT_INDEX -1
#define EMPTY_BPQUEUE_ELEMENT_VALUE -1

/** type used to define Bounded priority queue **/
typedef struct sp_bp_queue_t {
	int size; //the numbers of elements in the queue
	int maxSize;
	BPQueueElement* queue; //pointer to the first element of the queue
} SPBPQueue;

/**
 * Allocates a new SPBPQueue in the memory.
 * Given maxSize the bound of the queue
 *
 * Initialize every queue element to EMPTY_BPQUEUE_ELEMENT_INDEX & EMPTY_BPQUEUE_ELEMENT_VALUE
 *
 * O(maxSize) - complexity
 *
 * @param maxSize is the maximum Capacity of the queue
 * @assert(maxSize>0)
 * @return
 * NULL in case allocation failure occurred
 * Otherwise, the new point is returned
 */

SPBPQueue* spBPQueueCreate(int maxSize) {
	assert(0 < maxSize);
	SPBPQueue* res = NULL;
	res = (SPBPQueue*) malloc(sizeof(*res));
	if (NULL == res) {
		return NULL;
	}
	res->queue = (BPQueueElement*) malloc(sizeof(*(res->queue)) * maxSize);
	if (NULL == res->queue) {
		return NULL;
	}
	res->size = maxSize; //only for init the queue
	res->maxSize = maxSize;
	spBPQueueClear(res);
	return res;
}

/**
 * Allocates a copy of the given Queue.
 *
 * Given the SPBQueue source, the functions returns a
 * new SPBQueue such that:
 *
 * - copy_maxSize = source_maxSize (The maximum capacity is the same)
 * - size(copy) = size(source) (copy and source have the same current size)
 * - for every BPQueueElement:
 *		- index(copy) = index(source) (copy and source have the same index)
 *		- value(copy) = value(source) (copy and source have the same value)
 *
 * @param source - The source queue
 * @assert (source != NULL && source->queue !=NULL)
 *
 * @return
 * NULL in case memory allocation occurs
 * Others a copy of source is returned.
 */
double spBPQueueMaxValue(SPBPQueue* source) {
	assert(NULL != source);
	assert(!(spBPQueueIsEmpty(source)));
	return source->queue[0].value;
}

SPBPQueue* spBPQueueCopy(SPBPQueue* source) {
	assert(NULL != source && NULL !=source->queue);
	int i = 0;
	SPBPQueue* copy;
	copy = spBPQueueCreate(source->maxSize);
	copy->maxSize = source->maxSize;
	copy->size = source->size;
	for (i = 0; i < source->maxSize; i++) {
		copy->queue[i] = source->queue[i];
	}
	return copy;
}

/**
 * Free all memory allocation associated with point,
 * if source is NULL nothing happens.
 */
void spBPQueueDestroy(SPBPQueue* source) {
	if (NULL == source)
		return;
	free(&(source->queue));
	free(source);
}

/**
 * Given the SPBQueue source,the function initialize the queue
 * the functions returns source such that:
 *
 * - source_maxSize (no change)
 * - size(source)=0 (initialized the size to empty queue)
 * Initialize every queue element to EMPTY_BPQUEUE_ELEMENT_VALUE & EMPTY_BPQUEUE_ELEMENT_VALUE
 *
 * @param source - The source queue
 * @assert (source != NUlL)
 *
 */
void spBPQueueClear(SPBPQueue* source) {
	assert(NULL != source);
	int i = 0;
	BPQueueElement emptyElement;
	emptyElement.index = EMPTY_BPQUEUE_ELEMENT_INDEX;
	emptyElement.value = EMPTY_BPQUEUE_ELEMENT_VALUE;

	for (i = 0; i < source->size; i++) {
		source->queue[i] = emptyElement;
	}
	source->size = 0;
	return;
}

/**
 * returns the number of elements in the queue source.
 *
 * Given the SPBQueue source

 * @param source - The source queue
 * @assert (source != NUlL)
 *
 * @return
 * The numbers of elements in the queue
 */
int spBPQueueSize(SPBPQueue* source) {
	assert(source != NULL);
	return source->size;
}

/**
 * returns the maximum capacity of elements in the queue source.
 *
 * Given the SPBQueue source

 * @param source - The source queue
 * @assert (source != NUlL)
 *
 * @return
 * The maximum capacity of elements in the queue
 */
int spBPQueueGetMaxSize(SPBPQueue* source) {
	assert(source != NULL);
	return source->maxSize;
}

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue* source, int index, double value) {
	int i = 0;
	int j = 0;
	if (NULL == source || 0 > value || NULL == source->queue) {	//Values should be non negative
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	for (i = 0; i < (source->size); i++) {
		if (value >= source->queue[i].value) {
			break;
		}
	}
	if (spBPQueueIsFull(source)) {
		for (j = 0; j < i; j++) {
			source->queue[j] = source->queue[j + 1];
		}
		source->queue[i - 1].index = index;
		source->queue[i - 1].value = value;

		return SP_BPQUEUE_FULL;
	} else {
		for (j = source->size - 1; j >= i; j--) {
			source->queue[j + 1] = source->queue[j];
		}
		source->queue[i].index = index;
		source->queue[i].value = value;
		source->size++;
		return SP_BPQUEUE_SUCCESS;
	}

}

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue* source) {
	BPQueueElement emptyElement;
	emptyElement.index = EMPTY_BPQUEUE_ELEMENT_INDEX;
	emptyElement.value = EMPTY_BPQUEUE_ELEMENT_VALUE;
	if (source == NULL) {
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	if (spBPQueueIsEmpty(source)) {
		return SP_BPQUEUE_EMPTY;
	}
	source->queue[(source->size)] = emptyElement;
	source->size--;
	return SP_BPQUEUE_SUCCESS;

}

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueuePeek(SPBPQueue* source, BPQueueElement* res) {
	if (NULL == source || NULL == res) {
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	if (spBPQueueIsEmpty(source)) {
		return SP_BPQUEUE_EMPTY;
	}
	res->index = source->queue[source->size - 1].index;
	res->value = source->queue[source->size - 1].value;
	return SP_BPQUEUE_SUCCESS;
}

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueuePeekLast(SPBPQueue* source, BPQueueElement* res) {
	if (source == NULL) {
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	if (spBPQueueIsEmpty(source)) {
		return SP_BPQUEUE_EMPTY;
	}
	res->index = source->queue[0].index;
	res->value = source->queue[0].value;
	return SP_BPQUEUE_SUCCESS;
}

/**
 * TODO Complete documentation
 */
double spBPQueueMinValue(SPBPQueue* source) {
	assert(source != NULL);
	assert(!spBPQueueIsEmpty(source));
	return source->queue[source->size - 1].value;
}

/**
 * TODO Complete documentation
 */
/**
 * TODO Complete documentation
 */
bool spBPQueueIsEmpty(SPBPQueue* source) {
	assert(source!=NULL);
	if (source->size == 0) {
		return true;
	} else {
		return false;
	}
}

/**
 * TODO Complete documentation
 */
bool spBPQueueIsFull(SPBPQueue* source) {
	assert(source!=NULL);
	if (source->size < source->maxSize) {
		return false;
	} else {
		return true;
	}
}
