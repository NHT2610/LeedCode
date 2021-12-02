#include "Linked_List.h"
#include <vector>
#include <string>

vector<string> split_string(const string& s);
void input_list(linked_list*& list, vector<string> tokens, int N);
unsigned int get_size(Node* head);
Node* oddEvenList(Node* head);

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
	list->head = oddEvenList(list->head);
	print_element(list);
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

unsigned int get_size(Node* head) {
	int count = 0;
	while (head != NULL) {
		head = head->next;
		++count;
	}
	return count;
}

Node* oddEvenList(Node* head) {
	if (head == NULL || head->next == NULL || head->next->next == NULL) { return head; }
	//Get size of list
	unsigned int size = get_size(head);
	//Change
	int i = 3;
	Node* p1 = head;
	Node* p2 = head->next;
	Node* p3 = head->next->next;
	Node* before_p3 = p2, * b4 = p2;
	while (i <= size && p3 != NULL) {
		before_p3 = p3->next;
		if (p1 == head) {
			p1->next = p3;
			p2->next = p3->next;
			p3->next = p2;
		}
		else {
			p1->next = p3;
			b4->next = p3->next;
			p3->next = p2;
		}
		b4 = before_p3;
		if (b4 != NULL && before_p3->next != NULL) { p3 = before_p3->next; }
		else { break; }
		p1 = p1->next;
		i += 2;
	}
	return head;
}