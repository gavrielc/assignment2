#include "main_aux.h"

int main() {
	int n, d, k;
	SPPoint** pointArray;
	SPBPQueue* queue;
	scanf("%d %d %d%*c", &n, &d, &k);
	fflush(NULL);
	pointArray = fillPointArray(n, d);
	printf("filled point array\n");
	fflush(NULL);
	if(pointArray == NULL) {
		printf("Memory allocation failure.");
		return 0;
	}
	queue = fillQueue(pointArray, n, k);
	printf("filled queue\n");
	fflush(NULL);
	printIndices(queue, k);
	printf("printed indices\n");
	fflush(NULL);
	return 0;
}
