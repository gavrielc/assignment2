#include "main_aux.h"


SPPoint** fillPointArray(int n, int dimension) {
	int i, j;
	double* cord_array;
	char *str, *temp, *end;
	SPPoint** pointArray;
	pointArray = (SPPoint**) malloc((n+1) * sizeof(SPPoint*)); // n points and one comparison point
	if(pointArray == NULL) {
		return NULL;
	}
	cord_array = (double*) malloc(dimension * sizeof(double));  // will store the user input and be sent to the create point function
	if(cord_array == NULL) {
			free(pointArray);  // free resources
			return NULL;
	}
	str = (char*) malloc(100*sizeof(char));  // stores input in string format
	for(i=0; i<=n; i++){
		fgets(str, 100, stdin);
		temp = str;
		for (j=0; j<dimension; j++) {
			cord_array[j] = strtod(temp, &end);  // gets doubles from string and stores in cord_array
			temp = end;
		}
		pointArray[i] = spPointCreate(cord_array, dimension, i+1);
		if(pointArray[i]==NULL) {
			for(j=0; j<i; j++) {
				spPointDestroy(pointArray[j]);  // free each point that was created
			}	
			free(cord_array);
			free(pointArray);
			free(str);
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
	queue = spBPQueueCreate(k);  // creating the queue that will hold teh index-L2distance elements
	if(queue == NULL) {
		return NULL;
	}
	for(i=0; i<n; i++) {
		spBPQueueEnqueue(queue, i+1, spPointL2SquaredDistance(pointArray[i], pointArray[n]));
		spPointDestroy(pointArray[i]);  // free resources
	}
	spPointDestroy(pointArray[n]);  // free the comparison point
	free(pointArray);
	return queue;
}


void printIndices(SPBPQueue* queue, int k) {
	BPQueueElement* element;
	int i;
	element = (BPQueueElement*) malloc(sizeof(BPQueueElement));  // will store the index and value when peeking
	for(i=1; i<k; i++) {
		spBPQueuePeek(queue, element); // gets the index and value of the smallest valued element
		printf("%d, ", element->index); // prints the index
		spBPQueueDequeue(queue);  // removes the smallest element from the queue
	}
	spBPQueuePeek(queue, element);
	printf("%d\n", element->index); // last print is done outside of loop for formatting reasons
	spBPQueueDequeue(queue); // remove last element
	spBPQueueDestroy(queue); // free queue
	free(element);
}
