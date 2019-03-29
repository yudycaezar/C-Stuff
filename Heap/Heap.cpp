#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUMOFDATA 20

int minHeap[100];
int count = 0;

int getParentIndex(int index){
	return (index-1)/2;
}

int getLeftChildIndex(int index){
	return index*2+1;
}

int getRightChildIndex(int index){
	return index*2+2;
}

void swap(int* minHeap, int n1, int n2){
	int temp = minHeap[n1];
	minHeap[n1] = minHeap[n2];
	minHeap[n2] = temp;
}

void upheap(int idx){
	if(idx <= 0) return;
	int parent = getParentIndex(idx);
	
	if(minHeap[parent] <= minHeap[idx]) return;
	
	swap(minHeap, idx, parent);
	upheap(parent);
}

void downheap(int idx){
	if(idx >= count) return;
	
	int smallest = idx;
	int left = getLeftChildIndex(idx);
	int right = getRightChildIndex(idx);
	
	if(left < count && minHeap[left] < minHeap[smallest]){
		smallest = left;
	}
	
	if(right < count && minHeap[right] < minHeap[smallest]){
		smallest = right;
	}
	
	if(smallest == idx) return;
	
	swap(minHeap, smallest, idx);
	downheap(smallest);
}

void push(int input){
	minHeap[count] = input;
	count++;
	upheap(count-1);
}

int pop(){
	int removed = minHeap[0];
	swap(minHeap, 0, count-1);
	count--;
	downheap(0);
	return removed;
}

void view(){
	for(int i=0 ; i<count ; i++)
		printf("Data %2d: %d\n", i, minHeap[i]);
	printf("\n==================================\n");
	getchar();
}

void bulkInsertRandomly(int numOfData){
	int num;
	for(int i=0 ; i<numOfData ; i++){
		num = rand()%100;
		push(num);
	}
}

int main(){
	
	srand(time(NULL));
	
	bulkInsertRandomly(NUMOFDATA);
	view();
	
	printf("\nMin: %d\n", pop());	
	view();
	
	printf("\nMin: %d\n", pop());
	view();
	
	push(11);
	view();	
	
	return 0;
}
