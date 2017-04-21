#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#define MAX 10000000

void runDijstra(int** cost, int start, int end, int length);
int extractMin(int *q, int* found, int qLength);
void printPath(int* path, int start, int end, int dis);
void printPathRecursive(int* p, int s, int e);

int main(void) {

	int cost[5][5] = {{0, MAX, 8,6,5}, 
					  {MAX, 0, 1, MAX, 2},
					  {8, 1, 0, 7, MAX}, 
					  {6, MAX, 7, 0, MAX}, 
					  {5, 2, MAX, MAX, 0}};

	int costLength = sizeof(cost[0]) / sizeof(int);

	for (int i = 0; i < costLength; i++) {
		for (int j = 0; j < costLength; j++) {
			runDijstra(cost, i, j, costLength);
		}
	}
}

void runDijstra(int cost[5][5], int start, int end, int length) {
	int vertexNum = length;
	int *q;

	int *distance = (int*)malloc(sizeof(int)*length);
	int *path = (int*)malloc(sizeof(int)*length);
	int *foundVertex = (int*)malloc(sizeof(int)*length);

	for (int i = 0; i < vertexNum; i++) {
		distance[i] = cost[start][i];
		foundVertex[i] = 0;
		path[i] = start;
	}

	distance[start] = 0;
	foundVertex[start] = 1;
	q = distance;

	for (int i = 0; i < vertexNum - 1; i++) {
		int u = extractMin(q, foundVertex, length);
		foundVertex[u] = 1;

		for (int w = 0; w < vertexNum; w++) {
			if (foundVertex[w] < 1) {
				if (distance[w] > distance[u] + cost[u][w] && cost[u][w] != MAX) {
					distance[w] = distance[u] + cost[u][w];
					path[w] = u;
				}
			}
		}
	}

	printPath(path, start, end, distance[end]);
}

int extractMin(int *q, int* found, int qLength) {
	int result = -1;
	int min = MAX;

	for (int i = 0; i < qLength; i++) {
		if (q[i] < min && found[i] < 1) {
			min = q[i];
			result = i;
		}
	}

	return result;
}

void printPath(int* path, int start, int end, int dis) {

	printf("Start [%d] -> End[%d] (distance = %d)\n", start, end, dis);
	printPathRecursive(path, start, end);
	printf("-%d\n", end);
}

void printPathRecursive(int* p, int s, int e) {

	if (p[e] == s) {
		printf("%d", p[e]);
	}
	else {
		printPathRecursive(p, s, p[e]);
		printf("-%d", p[e]);
	}
}
