// Find a subset of a given set S = {s1 ,s2 ,.....,s n } of n positive integers whose sum is equal to a given positive integer d. 

#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <set>

typedef long long ll;
#define endl '\n'
#define pi 3.141592653589793238
#define MOD 1000000007

using namespace std;

bool subsetSum_Recursive(int nums[], int n, int targetSum){
	if(targetSum == 0){
		return true;
	}
	if(n == 0){
		return false;
	}
	if(nums[n-1] <= targetSum){
		return(subsetSum_Recursive(nums, n-1, targetSum-nums[n-1]) || subsetSum_Recursive(nums, n-1, targetSum));
	}
	else if(nums[n-1] > targetSum){
		return subsetSum_Recursive(nums, n-1, targetSum);
	}
}

bool subsetSum_Memoization(int nums[], int n, int targetSum, int **matrix){
	if(targetSum == 0){
		return 1;
	}
	if(n == 0){
		return 0;
	}
	if(matrix[n-1][targetSum] != -1){
		return matrix[n-1][targetSum];
	}
	if(nums[n-1] <= targetSum){
		return matrix[n-1][targetSum] = (subsetSum_Memoization(nums, n-1, targetSum-nums[n-1], matrix) || subsetSum_Memoization(nums, n-1, targetSum, matrix));
	}
	else if(nums[n-1] > targetSum){
		return matrix[n-1][targetSum] = subsetSum_Memoization(nums, n-1, targetSum, matrix);
	}
}

int mainRecursive(){
	int nums[5] = {1,3,7,5,10};
	int sum = 11;
	if(subsetSum_Recursive(nums, 5, sum)){
		cout << "Present" << endl;
	}
	else{
		cout << "Not Present" << endl;
	}
	return 0;
}

int mainMemoization(){
	int nums[5] = {2,3,7,8,10};
	int n = 5;
	int sum = 11;
	int ** matrix = new int*[n+1];
	for(int i = 0; i < n+1; i++){
		matrix[i] = new int[sum+1];
		for(int j = 0; j < sum+1; j++){
			matrix[i][j] = -1;
		}
	}

	if(subsetSum_Memoization(nums, n, sum, matrix)){
		cout << "Present" << endl;
	}
	else{
		cout << "NOt Present" << endl;
	}

	return 0;
}

int mainDynamic(){

	int nums[5] = {1,3,7,5,10};
	int n = 5;
	int sum = 11;

	vector<vector<int>> matrix(n+1, vector<int>(sum+1, -1));

	for(int i = 0; i < sum+1; i++){
		matrix[0][i] = 0;
	}
	for(int i = 1; i < n+1; i++){
		matrix[i][0] = 1;
	}
	matrix[0][0] = 1;

	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < sum+1; j++){
			if(nums[i-1] <= j){
				matrix[i][j] = (matrix[i-1][j-nums[i-1]] || matrix[i-1][j]);
			}
			else if(nums[i-1] > j){
				matrix[i][j] = matrix[i-1][j];
			}
		}
	}
	if(matrix[n][sum]){
		cout << "Present" << endl;
	}
	else{
		cout << "Not Present" << endl;
	}
}


// GFG

// ========================================================BREAK====================================================
// ========================================================BREAK====================================================
// ========================================================BREAK====================================================
// ========================================================BREAK====================================================
// ========================================================BREAK====================================================
// ========================================================BREAK====================================================
// ========================================================BREAK====================================================
// ========================================================BREAK====================================================
// ========================================================BREAK====================================================


// C++ program to count all subsets with
// given sum.
#include <bits/stdc++.h>
using namespace std;

// dp[i][j] is going to store true if sum j is
// possible with array elements from 0 to i.
bool** dp;

void display(const vector<int>& v)
{
	for (int i = 0; i < v.size(); ++i)
		printf("%d ", v[i]);
	printf("\n");
}

// A recursive function to print all subsets with the
// help of dp[][]. Vector p[] stores current subset.
void printSubsetsRec(int arr[], int i, int sum, vector<int>& p)
{
	// If we reached end and sum is non-zero. We print
	// p[] only if arr[0] is equal to sum OR dp[0][sum]
	// is true.
	if (i == 0 && sum != 0 && dp[0][sum])
	{
		p.push_back(arr[i]);
		// Display Only when Sum of elements of p is equal to sum
		if (arr[i] == sum)
			display(p);
		return;
	}

	// If sum becomes 0
	if (i == 0 && sum == 0)
	{
		display(p);
		return;
	}

	// If given sum can be achieved after ignoring
	// current element.
	if (dp[i-1][sum])
	{
		// Create a new vector to store path
		vector<int> b = p;
		printSubsetsRec(arr, i-1, sum, b);
	}

	// If given sum can be achieved after considering
	// current element.
	if (sum >= arr[i] && dp[i-1][sum-arr[i]])
	{
		p.push_back(arr[i]);
		printSubsetsRec(arr, i-1, sum-arr[i], p);
	}
}

// Prints all subsets of arr[0..n-1] with sum 0.
void printAllSubsets(int arr[], int n, int sum)
{
	if (n == 0 || sum < 0)
	return;

	// Sum 0 can always be achieved with 0 elements
	dp = new bool*[n];
	for (int i=0; i<n; ++i)
	{
		dp[i] = new bool[sum + 1];
		dp[i][0] = true;
	}

	// Sum arr[0] can be achieved with single element
	if (arr[0] <= sum)
	dp[0][arr[0]] = true;

	// Fill rest of the entries in dp[][]
	for (int i = 1; i < n; ++i)
		for (int j = 0; j < sum + 1; ++j)
			dp[i][j] = (arr[i] <= j) ? dp[i-1][j] ||
									dp[i-1][j-arr[i]]
									: dp[i - 1][j];
	if (dp[n-1][sum] == false)
	{
		printf("There are no subsets with sum %d\n", sum);
		return;
	}

	// Now recursively traverse dp[][] to find all
	// paths from dp[n-1][sum]
	vector<int> p;
	printSubsetsRec(arr, n-1, sum, p);
}

// Driver code
int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	int n = sizeof(arr)/sizeof(arr[0]);
	int sum = 10;
	printAllSubsets(arr, n, sum);
	return 0;
}
