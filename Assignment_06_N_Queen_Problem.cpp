#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>

typedef long long ll;
#define endl '\n'
#define pi 3.141592653589793238
#define MOD 1000000007

using namespace std;

// ========================================================BREAK====================================================


vector<vector<int>> res;

bool queenPossible(vector<vector<int>> &board, int row, int column){
	// Check the above row for queens
	int ci = row-1, cj = column;
	while(ci >= 0){
		if(board[ci][column] == 1){
			return false;
		}
		ci--;
	}

	// Check the right upper diagonal for Queens
	ci = row-1, cj = column+1;
	while(ci >= 0 && cj < board.size()){
		if(board[ci][cj] == 1){
			return false;
		}
		ci--; cj++;
	}

	// Check the left upper diagonal for Queens
	ci = row-1, cj = column-1;
	while(ci >= 0 && cj >= 0){
		if(board[ci][cj] == 1){
			return false;
		}
		ci--; cj--;
	}

	return true;
}

// ========================================================BREAK====================================================


void NQueensRecursive(vector<vector<int>> &board, int n, int row){
	if(row == n){
		// Found Solution
		vector<int> positions;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(board[i][j] == 1){
					positions.push_back(j+1);
				}
			}
		}
		res.push_back(positions);
		return;
	}

	for(int i = 0; i < n; i++){
		if(queenPossible(board, row, i)){
			board[row][i] = 1;
			NQueensRecursive(board, n, row+1);
			board[row][i] = 0;
		}
	}

	return;
}

// ========================================================BREAK====================================================


vector<vector<int>> NQueens(int n){
	if(n == 1){
		return {{1}};
	}
	if(n == 2 || n == 3){
		return {};
	}
	res.clear();
	vector<vector<int>> board(n, vector<int>(n, 0));
	NQueensRecursive(board, n, 0);
	// sort(res.begin(), res.end());
	return res;
}
// ========================================================BREAK====================================================

int main(){
	int t;
	cin >> t; 
	while(t--){
		int n = 0;
		cin >> n;
		NQueens(n);
	}

	return 0;
}