#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_

#include "stdlib.h"
#include "stdio.h"
#include "SPBPriorityQueue.h"
#include "SPPoint.h"
#include "string.h"

/**
 * Fills an new array of Points with points that are created
 * from user input numbers.
 *
 *
 * @param n is the number of points to compare
 * @param dimension is the dimension of each point
 * @return
 * NULL in case allocation failure occurred
 * Otherwise, the new point Array is returned
 */
SPPoint** fillPointArray(int n, int dimension);

/**
 * Fills a new queue with elements where the index is the point index and the value
 * is the L2 Squared distance from the comparison point
 *
 *
 * @param pointArray is the Array containing all of the points to insert
 * @param n is the number of points to insert
 * @param k is the maxsize of the queue
 * @return
 * NULL in case allocation failure occurred
 * Otherwise, the new queue is returned
 */
SPBPQueue* fillQueue(SPPoint** pointArray, int n, int k);

/**
 * Prints the index of each of the elements in the queue to stdout.
 * They are printed in the order of the smallest value to the largest. The index breaks ties in value.
 *
 *
 * @param queue is the queue containing all of the points to print
 * @param k is the maxsize of the queue
 *
 */
void printIndices(SPBPQueue* queue, int k);

#endif /* MAIN_AUX_H_ */
