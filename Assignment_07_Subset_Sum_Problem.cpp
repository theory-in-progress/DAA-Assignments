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

// USE ONLY THIS CODE, THIS CODE WORKS PERFECTLY, THIS PRINTS ALL THE INDICES OF THE ELEMENTS THAT SUM UPTO THE TARGET
// CAN BE MODIFIED TO PRINT THE ELEMENTS IN THE QUEUE
int main(){
	int n = 0;
	cin >> n;
	vector<int> nums(n, 0);
	for(int &x:nums){
		cin >> x;
	}
	int target = 0;
	cin >> target;

	vector<vector<int>> dp(n+1, vector<int>(target+1, 0));

	for(int i = 0; i < n+1; i++){
		dp[i][0] = 1; // a null set is possible for 0 sum target
	}

	for(int i = 1; i < n+1; i++){
		for(int j = 1; j < target+1; j++){
			if(j >= nums[i-1]){
				dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
			}
			else if(j < nums[i-1]){
				dp[i][j] = dp[i-1][j];
			}
		}
	}

	// we now have the dp table with true and false values
	// queue of <n, target, path>
	queue<pair<pair<int, int>, string>> possible;
	possible.push(make_pair(make_pair(n, target), ""));

	while(!possible.empty()){
		pair<pair<int, int>, string> front = possible.front();
		possible.pop();

		if(front.first.first == 0 || front.first.second == 0){
			cout << front.second << endl;
		}

		else{
			string temp = front.second;

			// If path is possible by Excluding the element
			if(dp[front.first.first-1][front.first.second]){
				possible.push(make_pair(make_pair(front.first.first-1, front.first.second), temp));
			}

			// If path is possible by Including the element
			if(front.first.second >= nums[front.first.first-1]){
				if(dp[front.first.first-1][front.first.second-nums[front.first.first-1]]){
					temp += to_string(front.first.first-1);
					possible.push(make_pair(make_pair(front.first.first-1, front.first.second-nums[front.first.first-1]), temp));
				}
			}
		}
	}
}
