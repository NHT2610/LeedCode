//https://leetcode.com/problems/3sum/
#include <iostream>
#include <vector>
#include <string>
using namespace std;	

vector<string> split_string(const string& s);
void input_array(vector<int>& arr, vector<string> tokens, int N);
void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right, bool option);
void merge_sort(vector<int>& arr, vector<int>& temp, int left, int right, bool option);
vector<vector<int>> threeSum(vector<int>& nums);
void output(vector<vector<int>>& result);

int main() {
	int N;
	string numbers_of_list;
	getline(cin, numbers_of_list);
	N = stoi(numbers_of_list);
	string temp_array;
	getline(cin, temp_array);
	vector<int> nums;
	input_array(nums, split_string(temp_array), N);
	vector<vector<int>> result = threeSum(nums);
	output(result);
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

void output(vector<vector<int>>& result) {
	int size = int(result.size());
	if (size == 0) { cout << "[]" << endl; return; }
	cout << "[";
	for (int i = 0; i < size; ++i) {
		if (i != size - 1) { cout << "[" << result[i][0] << "," << result[i][1] << "," << result[i][2] << "]" << ","; }
		else { cout << "[" << result[i][0] << "," << result[i][1] << "," << result[i][2] << "]"; }
	}
	cout << "]";
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

vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> result;
	int size = int(nums.size());
	//Sort array nums with merge sort algorithm, time complexity: O(nlogn), memory: O(n)
	vector<int> temp(size);
	merge_sort(nums, temp, 0, size - 1, true);
	//Find all three integer set, time complexity: O(n^2)
	for (int i = 0; i < size - 2; ++i) {
		if (nums[i] > 0) { break; }
		if (i > 0 && nums[i] == nums[i - 1]) { continue; }
		int left = i + 1, right = size - 1;
		while (left < right) {
			if (nums[i] + nums[left] + nums[right] == 0) {
				result.push_back({ nums[i],nums[left++],nums[right--] });
				while (left < right && nums[left] == nums[left - 1]) { ++left; }
				while (left < right && nums[right] == nums[right + 1]) { --right; }
			}
			else if (nums[i] + nums[left] + nums[right] < 0) { ++left; }
			else { --right; }
		}
	}
	return result;
}