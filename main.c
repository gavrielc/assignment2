#include "main_aux.h"

/**
 * Initially recieves three integers from stdin, n,k,d. The receives n points of dimension d and
 * a comparison point of the same dimension. 
 * Prints to stdout the indices of the k points that are closest to the comparison point 
 * based on L2SquaredDistance
 *
 */
int main() {
	int n, d, k;
	SPPoint** pointArray;
	SPBPQueue* queue;
	scanf("%d %d %d%*c", &n, &d, &k);  // gets three integers and discards the newline  
	pointArray = fillPointArray(n, d);  // fills an array with the n points and comparison point from stdin input
	if(pointArray == NULL) {
		printf("Memory allocation failure.");
		return 0;
	}
	queue = fillQueue(pointArray, n, k); // fills an SPB Priority queue with the indices and distances
	printIndices(queue, k); // prints to stdout the indices in the correct order
	return 0;
}
