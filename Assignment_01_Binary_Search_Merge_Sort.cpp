// ASSIGNMENT 01
// Write a program to perform binary search on an unsorted random list of at least 5000 elements. The key element should be user input. Use the Divide & Conquer method to implement this program.

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

// Binary Search Iterative
pair<bool, int> binarySearch(int si, int ei, int *nums, int target){
	int mid = si + (ei-si)/2;

	while(si <= ei){
		mid = si + (ei-si)/2;

		if(nums[mid] == target){
			// return mid;
			pair<bool, int> tp = make_pair(true, mid);
			return tp;
		}
		if(nums[mid] > target){
			ei = mid-1;
		}
		else{
			si = mid+1;
		}
	}

	pair<bool, int> tp = make_pair(false, mid);
	return tp;
}

// ========================================================BREAK====================================================

// Binary Search Using Divide and Conquer
int binarySearch_DivideConquer(int si, int ei, int nums[], int target){
	int mid = si + (ei-si)/2;

	if(nums[mid] == target){
		return mid;
	}
	if(target > nums[mid]){
		binarySearch_DivideConquer(mid+1, ei, nums, target);
	}
	else{
		binarySearch_DivideConquer(si, mid-1, nums, target);
	}
}

// ========================================================BREAK====================================================

int main(){

	int i, num, first, last, middle;
	int x, y,size, temp;
	int sz;
	cout<<"Enter the size of array::";
	cin>>sz;
	int randArray[sz];
	int arr[5000];
	for(int i=0;i<sz;i++){
		randArray[i]= 1 + rand()%10000;
	}
	cout<<"The generated array : ";
	for(int i=0;i<sz;i++)
		cout<<randArray[i]<<" ";
	
	for(int x=0;x<sz;x++){
		arr[x]=randArray[x];
	}



	// int arr[10] = {5,10,6,9,7,8,20,25,79,69};
	// Sorting elements in ascending order
	mergeSort(arr, 0, sz-1);
	// Displaying output
	cout <<"\nElements sorted in the ascending order are : ";
	for(int i = 0; i < sz; i++){
		cout << arr[i] << " ";
	}

	cout<<"\nEnter Element to be Search: ";
	cin>>num;
	//bianry search 
	pair<bool, int> possible2 = binarySearch(0, sz-1, arr, num);
	if(possible2.first){
		cout<<"\nThe number, "<<num<<" found at Position "<<possible2.second;
	}
	else{
		cout<<"\nThe number, "<<num<<" is not found in given Array";
	}
	cout << endl;
	return 0;
}