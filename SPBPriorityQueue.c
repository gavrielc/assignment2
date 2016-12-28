#include <stdbool.h>
#include "SPBPriorityQueue.h"
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

#define EMPTY_BPQUEUE_ELEMENT_INDEX -1
#define EMPTY_BPQUEUE_ELEMENT_VALUE -1

/**
 * SP Bounded Priority Queue summary
 *
 *
 * TODO Complete documentation
 */


/** type used to define Bounded priority queue
 *
 * * size - the numbers of elements in the queue
 * maxSize - the bound on the number of the elements in the queue
 * queue - pointer to BPQueueElement with the highest value in the queue
 *
 */
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
 * @assert(NULL != source)
 *
 * @return
 * The numbers of elements in the queue
 */
int spBPQueueSize(SPBPQueue* source) {
	assert(NULL != source);
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
 * Inserts an element to the queue
 *
 * @param source pointer to the queue that we will insert the element to
 * @param index is the index of the element that we insert
 * @param value is the value of the element that we insert
 *
 * case1 : the queue isn't full
 * 		- inserts the value and the index after all the values
 * 		  that with higher value than the new value
 *
 * case2 : the queue is full & the value is higher than every value in the queue
 * 		- nothing happened
 * case3 : the queue is full & the value is not higher than every value in the queue
 * 		- follow case1 and remove the element with the highest value
 *
 *  * O(size) - complexity
 *
 * @return
 * SP_BPQUEUE_INVALID_ARGUMENT -for NULL pointer or value is negative
 * SP_BPQUEUE_FULL - the insertion was successful and the queue is full capacity
 * SP_BPQUEUE_SUCCESS - the insertion was successful
 *
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
	}
	else {
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
 * removes the element with the lowest value
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
 * Returns a copy of the element with the lowest value
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
 * Returns a copy of the element with the highest value
 *
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
 * returns the minimum value in the queue
 *
 * Given the SPBQueue source
 *
 * @param source - The source queue
 * @assert(NULL != source)
 *
 * @return
 * double - the minimum value in the queue
 *
 */
double spBPQueueMinValue(SPBPQueue* source) {
	assert(source != NULL);
	assert(!spBPQueueIsEmpty(source));
	return source->queue[source->size - 1].value;
}

/**
 * checks if the queue is empty
 *
 * Given the SPBQueue source
 *
 * @param source - The source queue
 * @assert(NULL != source)
 *
 * @return
 * TRUE - the queue is empty
 * FALSE - the queue is not empty
 *
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
 * checks if the queue is in full capacity
 *
 * Given the SPBQueue source
 *
 * @param source - The source queue
 * @assert(NULL != source)
 *
 * @return
 * TRUE - the queue is in full capacity
 * FALSE - the queue is not full capacity
 *
 */
bool spBPQueueIsFull(SPBPQueue* source) {
	assert(source!=NULL);
	if (source->size < source->maxSize) {
		return false;
	} else {
		return true;
	}
}
