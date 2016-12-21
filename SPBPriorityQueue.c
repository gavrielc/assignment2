#include <stdbool.h>
#include "SPBPriorityQueue.h"
#include <malloc.h>
#include <assert.h>
#include <stdbool.h>

/**
 * SP Bounded Priority Queue summary
 *
 * TODO Complete documentation
 */
#define EMPTY_BPQUEUE_ELEMENT_INDEX -1
#define EMPTY_BPQUEUE_ELEMENT_VALUE -1

/** type used to define Bounded priority queue **/
typedef struct sp_bp_queue_t {
	int size;//the numbers of elements in the queue
	int maxSize;
	BPQueueElement* queue;//pointer to the first element of the queue
}SPBPQueue;

/**
 * Allocates a new SPBPQueue in the memory.
 * Given maxSize the bound of the queue
 *
 * Initialize every queue element to EMPTY_BPQUEUE_ELEMENT_VALUE & EMPTY_BPQUEUE_ELEMENT_VALUE
 *
 * O(maxSize) - complexity
 *
 * @param maxSize is the maximum Capacity of the queue
 * @assert (maxSize<1)
 * @return
 * NULL in case allocation failure occurred
 * Otherwise, the new point is returned
 */


SPBPQueue* spBPQueueCreate(int maxSize){
	assert(maxSize<1);
	int i=0;
	SPBPQueue* res;
	res->queue =(SPBPQueue*)malloc(sizeof(*res)*maxSize);
	if (res==NULL){
		return NULL;
	}
	res->size=0;
	res->maxSize=maxSize;
	for (i=0;i<maxSize*sizeof(*res->queue);i+=sizeof(*res->queue)){
		res->queue[i].index=EMPTY_BPQUEUE_ELEMENT_INDEX;
		res->queue[i].value=EMPTY_BPQUEUE_ELEMENT_VALUE;
	}
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
 * @assert (source != NUlL)
 *
 * @return
 * NULL in case memory allocation occurs
 * Others a copy of source is returned.
 */
SPBPQueue* spBPQueueCopy(SPBPQueue* source){
	assert(source != NULL);
	int i=0;
	SPBPQueue* copy;
	copy = spBPQueueCreate(source->maxSize);
	copy->maxSize=source->maxSize;
	copy->size=source->size;
	for (i=0;i<source->maxSize*sizeof(*source->queue);i+=sizeof(*source->queue)){
		copy->queue[i].index=source->queue[i].index;
		copy->queue[i].value=source->queue[i].value;
	}
	return copy;
}

/**
 * Free all memory allocation associated with point,
 * if source is NULL nothing happens.
 */
void spBPQueueDestroy(SPBPQueue* source){
	if (source==NULL)
		return;
	free(source->queue);
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
void spBPQueueClear(SPBPQueue* source){
	assert(source != NULL);
	int i=0;
	for (i=0;i<source->size*sizeof(*source->queue);i+=sizeof(*source->queue)){
		source->queue[i].index=EMPTY_BPQUEUE_ELEMENT_INDEX;
		source->queue[i].value=EMPTY_BPQUEUE_ELEMENT_VALUE;
	}
	source->size=0;
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
int spBPQueueSize(SPBPQueue* source){
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
int spBPQueueGetMaxSize(SPBPQueue* source){
	assert(source != NULL);
	return source->maxSize;
}

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue* source, int index, double value){
	int i=0;
	BPQueueElement temp;//will be used for moving elements
	BPQueueElement move;
	bool flag=0;//true if we alredy found a place for the new value that given
	if(source==NULL || value<0){
		//Values should be non negative
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	for (i=0 ; i< source->size*sizeof(*source->queue) ; i+=sizeof(*source->queue)){
		if (source->queue[i].value<=value && !flag){
			temp=source->queue[i];
			source->queue[i].index=index;
			source->queue[i].value=value;
			flag=true;
			break;
		}
	}
	if(!flag){
		//the value that given is smaller than the min value in the queue
		temp.index=index;
		temp.value=value;
	}
	if (!spBPQueueIsFull(source)){
		for ( i+=sizeof(*source->queue); i< (source->size+1)*sizeof(*source->queue) ; i+=sizeof(*source->queue)){
			move=source->queue[i];
			source->queue[i]=temp;
			temp=move;
		}
		source->size++;
		return SP_BPQUEUE_SUCCESS;
	}
	else{//full capacity
		for (; i==0 ; i-=sizeof(*source->queue)){
					move=source->queue[i];
					source->queue[i]=temp;
					temp=move;
		}
		return SP_BPQUEUE_FULL;
	}

}

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue* source);

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueuePeek(SPBPQueue* source, BPQueueElement* res);

/**
 * TODO Complete documentation
 */
SP_BPQUEUE_MSG spBPQueuePeekLast(SPBPQueue* source, BPQueueElement* res);

/**
 * TODO Complete documentation
 */
double spBPQueueMinValue(SPBPQueue* source);

/**
 * TODO Complete documentation
 */
double spBPQueueMaxValue(SPBPQueue* source);

/**
 * TODO Complete documentation
 */
bool spBPQueueIsEmpty(SPBPQueue* source);

/**
 * TODO Complete documentation
 */
bool spBPQueueIsFull(SPBPQueue* source){
	assert (source==NULL);
	if (source->size < source.maxSize){
		return false;
	}
	else {
		return true;
	}
}
