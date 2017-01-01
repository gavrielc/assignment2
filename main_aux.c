#include "main_aux.h"

SPPoint** fillPointArray(int n, int dimension) {
	int i, j;
	double* cord_array;
	char *str, *temp;
	SPPoint** pointArray;
	pointArray = (SPPoint**) malloc((n+1) * sizeof(SPPoint*));
	if(pointArray == NULL) {
		printf("Memory allocation failure.");
		return NULL;
	}
	cord_array = (double*) malloc(dimension * sizeof(double));
	if(cord_array == NULL) {
			printf("Memory allocation failure.");
			free(pointArray);
			return NULL;
		}
	str = (char*) malloc(100*sizeof(char));
	for(i=0; i<=n; i++){
		fgets(str, 100, stdin);
		fflush(NULL);
		for (j=0; j<dimension; j++) {
			cord_array[j] = strtod(str, &temp);
			str = temp;
		}
		pointArray[i] = spPointCreate(cord_array, dimension, i+1);
		if(pointArray[i]==NULL) {
			// need to free resources
			return NULL;
		}
	}
	free(cord_array);
	free(str);
	return pointArray;
}

SPBPQueue* fillQueue(SPPoint** pointArray, int n, int k) {
	int i;
	SPBPQueue* queue;
	queue = spBPQueueCreate(k);
	for(i=0; i<n; i++) {
		spBPQueueEnqueue(queue, i+1, spPointL2SquaredDistance(pointArray[i], pointArray[n]));
		spPointDestroy(pointArray[i]);
	}
	spPointDestroy(pointArray[n]);
	free(pointArray);
	return queue;
}

void printIndices(SPBPQueue* queue, int k) {
	BPQueueElement* element;
	int i;
	element = (BPQueueElement*) malloc(sizeof(BPQueueElement*));
	for(i=1; i<k; i++) {
		spBPQueuePeek(queue, element);
		printf("%d, ", element->index);
		fflush(NULL);
		spBPQueueDequeue(queue);
	}
	spBPQueuePeek(queue, element);
	printf("%d", element->index);
	fflush(NULL);
	spBPQueueDequeue(queue);
}
