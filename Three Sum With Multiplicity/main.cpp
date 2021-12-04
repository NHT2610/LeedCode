//https://leetcode.com/problems/3sum-with-multiplicity/
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
int mod = int(pow(10, 9) + 7);
using namespace std;

vector<string> split_string(const string& s);
void input_array(vector<int>& arr, vector<string> tokens, int N);
void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right, bool option);
void merge_sort(vector<int>& arr, vector<int>& temp, int left, int right, bool option);
int sum(int number);
int threeSumMulti(vector<int>& nums, int target);

int main() {
	int N;
	string numbers_of_list;
	getline(cin, numbers_of_list);
	N = stoi(numbers_of_list);
	string temp_array;
	getline(cin, temp_array);
	vector<int> nums;
	input_array(nums, split_string(temp_array), N);
	string s;
	getline(cin, s);
	int target = stoi(s);
	cout << threeSumMulti(nums, target);
	return 0;
}

vector<string> split_string(const string& s) {
	vector<string> tokens;
	int len = int(s.length());
	string number;
	for (int i = 0; i < len; ++i) {
		int j;
		for (j = i; s[j] != ' ' && j < len; ++j) {
			number += s[j];
		}
		tokens.push_back(number);
		number = "";
		i = j;
	}
	return tokens;
}

void input_array(vector<int>& arr, vector<string> tokens, int N) {
	int number;
	for (int i = 0; i < N; ++i) {
		number = stoi(tokens[i]);
		arr.push_back(number);
	}
}

void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right, bool option) {
	int index, index1, index2;
	index = left, index1 = left, index2 = mid + 1;
	while (index1 <= mid && index2 <= right) {
		if (arr[index1] < arr[index2] == option) {
			temp[index++] = arr[index1++];
		}
		else {
			temp[index++] = arr[index2++];
		}
	}
	while (index1 < int(arr.size()) && index1 <= mid) {
		temp[index++] = arr[index1++];
	}
	while (index2 < int(arr.size()) && index2 <= right) {
		temp[index++] = arr[index2++];
	}
	for (int i = left; i <= right; ++i) {
		arr[i] = temp[i];
	}
}

void merge_sort(vector<int>& arr, vector<int>& temp, int left, int right, bool option) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(arr, temp, left, mid, option);
		merge_sort(arr, temp, mid + 1, right, option);
		merge(arr, temp, left, mid, right, option);
	}
}

int sum(int number) {
	int sum = 0;
	for (int i = number - 1; i >= 1; --i) { sum += i; }
	return sum;
}

int threeSumMulti(vector<int>& nums, int target) {
	int result = 0;
	int size = int(nums.size());
	vector<int> temp(size);
	merge_sort(nums, temp, 0, size - 1, true);
	int left, count_l, right, count_r;
	for (int i = 0; i < size - 2; ++i) {
		if (nums[i] > target) { break; }
		left = i + 1; right = size - 1;
		while (left < right) {
			if (nums[i] + nums[left] + nums[right] == target) {
				count_l = 1; count_r = 1;
				while (left < right && nums[left] == nums[left + 1]) { ++count_l; ++left; }
				while (right > left && nums[right - 1] == nums[right]) { ++count_r; --right; }
				if (left < right) { result = (result + count_l * count_r) % mod; }
				else { result = (result + sum(count_l)) % mod; }
				++left; --right;
			}
			else if (nums[i] + nums[left] + nums[right] > target) { --right; }
			else { ++left; }
		}
	}
	return result % mod;
}