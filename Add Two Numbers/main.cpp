//https://leetcode.com/problems/add-two-numbers/
#include "Linked_List.h"
#include <vector>
#include <string>

vector<string> split_string(const string& s);
void input_list(linked_list*& list, vector<string> tokens);
void reverse_list(Node*& head);
Node* add(Node*& head, Node*& tail, int value);
Node* remove(Node*& head);
Node* addTwoNumbers(Node* list1, Node* list2);

int main() {
	string temp_list1, temp_list2;
	getline(cin, temp_list1);
	getline(cin, temp_list2);
	linked_list* list1 = new linked_list;
	linked_list* list2 = new linked_list;
	list1->head = list1->head = NULL;
	list2->head = list2->head = NULL;
	input_list(list1, split_string(temp_list1));
	input_list(list2, split_string(temp_list2));
	linked_list* list_result = new linked_list;
	Node* node = addTwoNumbers(list1->head, list2->head);
	initialize_linked_list(list_result, node);
	print_element(list_result);
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

void input_list(linked_list*& list, vector<string> temp_list) {
	int N = int(temp_list.size());
	int number;
	for (int i = 0; i < N; ++i) {
		number = stoi(temp_list[i]);
		add_tail(list, number);
	}
}

void reverse_list(Node*& head) {
	if (head->next == NULL) { return; }
	Node* cur_head = head;
	Node* p1 = head->next, * p2 = head->next->next;
	while (head->next != NULL) {
		head->next = p2;
		p1->next = cur_head;
		cur_head = p1;
		p1 = p2;
		if (p2 != NULL) { p2 = p2->next; }
	}
	head = cur_head;
}

Node* add(Node*& head, Node*& tail, int value) {
	if (tail == NULL) {
		head = tail = initialize_node(value);
		return head;
	}
	Node* new_node = initialize_node(value);
	tail->next = new_node;
	tail = new_node;
	return head;
}

Node* remove(Node*& head) {
	if (head == NULL) { return NULL; }
	Node* node_del = head;
	head = head->next;
	delete node_del;
	return head;
}
//Algorithm with time complexity: O(n) and memory: O(1)
Node* addTwoNumbers(Node* list1, Node* list2) {
	Node* result = NULL, * tail_result = NULL;
	Node* tail1 = list1, * tail2 = list2;
	while (tail1->next != NULL) { tail1 = tail1->next; }
	while (tail2->next != NULL) { tail2 = tail2->next; }
	Node* node1 = list1, * node2 = list2;
	int value, k = 0;
	while (node1 != NULL && node2 != NULL) {
		value = node1->data + node2->data + k;
		if (value < 10) { result = add(result, tail_result, value); k = 0; }
		else { 
			k = int(value / 10); value = value - k * 10; 
			result = add(result,tail_result, value); 
		}
		node1 = remove(list1); node2 = remove(list2);
	}
	while (node1 != NULL) { 
		value = node1->data + k; 
		if (value < 10) { result = add(result, tail_result, value); k = 0; }
		else {
			k = int(value / 10); value = value - k * 10;
			result = add(result, tail_result, value);
		}
		node1 = remove(list1);
	}
	while (node2 != NULL) { 
		value = node2->data + k; 
		if (value < 10) { result = add(result, tail_result, value); k = 0; }
		else {
			k = int(value / 10); value = value - k * 10;
			result = add(result, tail_result, value);
		}
		node2 = remove(list2);
	}
	if (k) { result = add(result, tail_result, k); }
	return result;
}