#include "Linked_List.h"
#include <vector>
#include <string>

vector<string> split_string(const string& s);
void input_list(linked_list*& list, vector<string> tokens, int N);

int main() {
	linked_list* list = new linked_list;
	list->head = list->tail = NULL;
	int N;
	string numbers_of_list;
	getline(cin, numbers_of_list);
	N = stoi(numbers_of_list);
	string temp_list;
	getline(cin, temp_list);
	input_list(list, split_string(temp_list), N);

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

void input_list(linked_list*& list, vector<string> temp_list, int N) {
	int number;
	for (int i = 0; i < N; ++i) {
		number = stoi(temp_list[i]);
		add_tail(list, number);
	}
}