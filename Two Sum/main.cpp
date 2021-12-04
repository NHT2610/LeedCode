//https://leetcode.com/problems/two-sum/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct elements {
	int index;
	int value;
	elements operator=(elements& s) {
		this->index = s.index;
		this->value = s.value;
		return *this;
	}
};

vector<string> split_string(const string& s);
void input_array(vector<int>& arr, vector<string> tokens, int N);
vector<int> twoSum_verOn2(vector<int>& nums, int target);
vector<int> twoSum_verOnlogn(vector<int>& nums, int target);
void merge(vector<elements>& arr, vector<elements>& temp, int left, int mid, int right, bool option);
void merge_sort(vector<elements>& arr, vector<elements>& temp, int left, int right, bool option);

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
	vector<int> result = twoSum_verOnlogn(nums, target);
	cout << "[" << result[0] << "," << result[1] << "]" << endl;
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

vector<int> twoSum_verOn2(vector<int>& nums, int target) {
	vector<int> result(2);
	int size = int(nums.size());
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (nums[i] + nums[j] == target) {
				result[0] = i; result[1] = j;
				return result;
			}
		}
	}
	result[0] = -1; result[1] = -1;
	return result;
}

void merge(vector<elements>& arr, vector<elements>& temp, int left, int mid, int right, bool option) {
	int index, index1, index2;
	index = left, index1 = left, index2 = mid + 1;
	while (index1 <= mid && index2 <= right) {
		if (arr[index1].value < arr[index2].value == option) {
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

void merge_sort(vector<elements>& arr, vector<elements>& temp, int left, int right, bool option) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(arr, temp, left, mid, option);
		merge_sort(arr, temp, mid + 1, right, option);
		merge(arr, temp, left, mid, right, option);
	}
}

vector<int> twoSum_verOnlogn(vector<int>& nums, int target) {
	vector<int> result(2);
	int size = int(nums.size());
	vector<elements> arr(size);
	for (int i = 0; i < size; ++i) {
		arr[i].index = i;
		arr[i].value = nums[i];
	}
	vector<elements> temp(size);
	merge_sort(arr, temp, 0, size - 1, true);
	int left, right, mid;
	for (int i = 0; i < size; ++i) {
		left = 0; right = size - 1; mid = (left + right) / 2;
		while (left <= right) {
			if (target - nums[i] == arr[mid].value) {
				if (i == arr[mid].index) {
					if (arr[mid + 1].value == arr[mid].value) {
						if (arr[mid + 1].index > i) {
							result[0] = i; result[1] = arr[mid + 1].index;
							return result;
						}
						else {
							result[0] = arr[mid + 1].index; result[1] = i;
							return result;
						}
					}
					else if (arr[mid - 1].value == arr[mid].value) {
						if (arr[mid - 1].index > i) {
							result[0] = i; result[1] = arr[mid - 1].index;
							return result;
						}
						else {
							result[0] = arr[mid - 1].index; result[1] = i;
							return result;
						}
					}
					else { break; }
				}
				else {
					if (arr[mid].index > i) {
						result[0] = i; result[1] = arr[mid].index;
						return result;
					}
					else {
						result[0] = arr[mid].index; result[1] = i;
						return result;
					}
				}
			}
			else if (target - nums[i] > arr[mid].value) {
				left = mid + 1;
				mid = (left + right) / 2;
			}
			else {
				right = mid - 1;
				mid = (left + right) / 2;
			}
		}
	}
	result[0] = -1; result[1] = -1;
	return result;
}