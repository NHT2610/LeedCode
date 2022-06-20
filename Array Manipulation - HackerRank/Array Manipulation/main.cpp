//https://www.hackerrank.com/challenges/crush/problem?isFullScreen=true
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> parseString(const string& s, char sep) {
	vector<int> result;
	string tmp = "";
	for (int i = 0; i < (int)s.length(); ++i) {
		while (i < (int)s.length() && s[i] != sep) {
			tmp += s[i];
			++i;
		}
		if (i != (int)s.length()) {
			result.push_back(stoi(tmp));
			tmp = "";
		}
	}
	result.push_back(stoi(tmp));
	return result;
}

long long int arrayManipulation(int n, vector<vector<int>> queries) {
	vector<long long int> arr(n + 1, 0);
	for (int i = 0; i < (int)queries.size(); ++i) {
		arr[queries[i][0]] += queries[i][2];
		if (queries[i][1] + 1 <= n) {
			arr[queries[i][1] + 1] -= queries[i][2];
		}
	}	
	long long int _max = 0, maxCur = 0;
	for (int i = 1; i <= n; ++i) {
		maxCur += arr[i];
		_max = max(_max, maxCur);
	}
	return _max;
}

int main() {
	fstream input;
	int test = 7;
	string path = "testcase" + to_string(test) + ".txt";
	input.open(path, ios::in);
	int n, m;
	string tmp;
	getline(input, tmp);
	n = (int)parseString(tmp, ' ')[0];
	m = (int)parseString(tmp, ' ')[1];
	tmp = "";
	vector<vector<int>> queries;
	for (int i = 1; i <= m; ++i) {
		getline(input, tmp);
		vector<int> row = parseString(tmp, ' ');
		queries.push_back(row);
		tmp = "";
	}
	cout << arrayManipulation(n, queries);
	input.close();
	return 0;
}