#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

// ========================================================BREAK====================================================

// Function to merge two  sorted arrays
void mergeTwoArrays(int *arr, int si, int ei){
	int mid = si + (ei-si)/2;

	int i = si, j = mid+1, k = 0;
	
	int *temp = new int[ei-si+1];
	
	while((i <= mid) && (j <= ei)){
		if(arr[i] <= arr[j]){
			temp[k++] = arr[i++];
		}
		else{
			temp[k++] = arr[j++];
		}
	}

	while(i <= mid){
		temp[k++] = arr[i++];
	}

	while(j <= ei){
		temp[k++] = arr[j++];
	}

	int r = 0;
	for(int t = si; t < ei+1; t++){
		arr[t] = temp[r++];
	}
}

// ========================================================BREAK====================================================

// Merge Sort using Divide and Conquer
void mergeSort(int *arr, int si, int ei){
	if(si >= ei){
		return;
	}

	int mid = si + (ei - si)/2;
	
	mergeSort(arr, 0, mid);
	mergeSort(arr, mid+1, ei);
	mergeTwoArrays(arr, si, ei);
}

// ========================================================BREAK====================================================


int partition(int arr[], int start, int end){

	int pivot = arr[start];
 

	int count = 0;

	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {
		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}
	return pivotIndex;
}

// ========================================================BREAK====================================================


void quickSort(int arr[], int start, int end){
	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(arr, start, end);

	// Sorting the left part
	quickSort(arr, start, p - 1);

	// Sorting the right part
	quickSort(arr, p + 1, end);
}

// ========================================================BREAK====================================================


int main(){
	int arr[] = { 9, 3, 4, 2, 1, 8 };
	int n = 6;
	quickSort(arr, 0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	return 0;
}