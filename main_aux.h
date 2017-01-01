#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_

#include "stdlib.h"
#include "stdio.h"
#include "SPBPriorityQueue.h"
#include "SPPoint.h"
#include "string.h"

SPPoint** fillPointArray(int n, int dimension);

SPBPQueue* fillQueue(SPPoint** pointArray, int n, int k);

void printIndices(SPBPQueue* queue, int k);

#endif /* MAIN_AUX_H_ */
