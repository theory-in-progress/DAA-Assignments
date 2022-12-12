#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <set>
#include <cstring>

typedef long long ll;
#define endl '\n'
#define pi 3.141592653589793238
#define MOD 1000000007

using namespace std;

// ========================================================BREAK====================================================


int knapsack_0_1_Recursive(int weights[], int values[], int W, int n){
	/*
	@parameters:
	int weights[] - array of the weights of the items 
	int values[] - array of the values of the items 
	int W - the total weight capacity of the knapsack 
	int n - the numebr of items in the given array 
	*/

	// FIRST SHOULD BE THE BASE CASE:
	if(n == 0 || W == 0){
		return 0;
	}
	if(weights[n-1] <= W){
		return (max((values[n-1] + knapsack_0_1_Recursive(weights, values, W-weights[n-1], n-1)),(knapsack_0_1_Recursive(weights, values, W, n-1))));
	}
	else if(weights[n-1] > W){
		return (knapsack_0_1_Recursive(weights, values, W, n-1));
	}
}

// ========================================================BREAK====================================================


// int n = 100, W = 1000; // UNCOMMENT
// int t[102][1002]; // UNCOMMENT 
int knapsack_0_1_Memoization(int weights[], int values[], int W, int n){
	if(n == 0 || W == 0){
		return 0;
	}
	if(t[n][W] != -1){
		return t[n][W];
	}
	if(weights[n-1] <= W){
		return t[n][W] = max((values[n-1] + knapsack_0_1_Memoization(weights, values, W-weights[n-1], n-1)), (knapsack_0_1_Memoization(weights, values, W, n-1)));
	}
	else if(weights[n-1] > W){
		return t[n][W] = knapsack_0_1_Memoization(weights, values, W, n-1);
	}
}

// ========================================================BREAK====================================================


int mainMemoization(){

	int weights[4] = {1,3,4,5};
	int values[4] = {1,4,5,7};
	memset(t, -1, sizeof(t));
	knapsack_0_1_Memoization(weights, values, W, n);
	return 0;
}

// ========================================================BREAK====================================================


// CODE-BREAK: Printing the items which were taken in the knapsack
// https://www.geeksforgeeks.org/printing-items-01-knapsack/

int knapsackdp01(vector<int> weights,  vector<int> profits, int n, int capacity){
	vector<vector<int>> dp(n+1, vector<int>(capacity+1, -1));
	for(int i = 0; i < n+1; i++){
		dp[i][0] = 0;
	}
	for(int i = 0; i < capacity+1; i++){
		dp[0][i] = 0;
	}

	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < capacity+1; j++){
			if(j >= weights[i-1]){
				dp[i][j] = max(profits[i-1]+dp[i-1][j-weights[i-1]], dp[i-1][j]);
			}
			else{
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	vector<int> taken; taken.clear();
	int i = n, res = dp[n][capacity], w = capacity;
	// either the result comes from the top 
	// (dp[i-1][capacity]) or from (val[i-1]+dp[i-1][capacity-weights[i-1]]) 
	// as in knapsack table 
	// if it comes form the later one it means the item is included 
	// if the values of the same column in two consecutive rows are equal then the value did not come from there
	// this is because it was just updated form the previous column, 
	// in the code we essentially do max(values[i-1]+dp[i-1][j-weights[i-1]], dp[i-1][j]) 
	// so if the rows values are same then it means that the max value of the next row was just updated with dp[i-1][j] in the max process, so this value was not actually taken, the value will be taken which is greater than the current value when we update it with the max. That is possible when we choose values[i-1]+dp[i-1][w-weights[i-1]] so we are updating the vvalues with this value
	while(i > 0 && res > 0){
		if(res == dp[i-1][w]){
			i--;
			continue;
		}
		else{
			// this item is included
			taken.push_back(weights[i-1]);
			res = res - profits[i-1];
			w = w - weights[i-1];
		}
		i--;
	}
}

// ========================================================BREAK====================================================


int main(){
	vector<int> weights = {5,9,10,1,6};
	vector<int> profits = {10,20,30,40,50};
	int capacity = 16;
	vector<int> taken(6, 0);
	cout << knapsackdp01(weights, profits, capacity, 5) << endl;
	for(int i = 0; i < 5; i++){
		cout << taken[i] << " ";
	}
	cout << endl;
}