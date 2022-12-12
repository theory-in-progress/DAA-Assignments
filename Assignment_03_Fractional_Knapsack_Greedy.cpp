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

/*
Solve the following instance of the knapsack problem given the  knapsack capacity in w=20 using greedy methods. Total no of item is 5.
Item   Weight   Profit
X1        3             10
X1        5             20
X1        5             21
X1        8             30
X1       4             16
*/

// ========================================================BREAK====================================================

float knapsackFractional(vector<int> weights, vector<int> profits, int capacity, int n){

	vector<pair<float, float>> pbw(n);
	for(int i = 0; i < n; i++){
		float diff = float(profits[i])/float(weights[i]);

		pbw[i] = make_pair(diff, weights[i]);
	}

	sort(pbw.rbegin(), pbw.rend());
	float totalProfit = 0;
	for(auto it:pbw){
		if(it.second <= capacity){
			capacity -= it.second;
			totalProfit += it.first*it.second;
		}
		else if(it.second > capacity){
			totalProfit += capacity*it.first;
			break; // break pakka hoga naaa????
		}
	}
	return totalProfit;
}

// ========================================================BREAK====================================================

int main(){
	vector<int> weights = {3,5,5,8,4};
	vector<int> profits = {10,20,21,30,16};
	int capacity = 20;
	
	cout << knapsackFractional(weights, profits, capacity, weights.size()) << endl;
}