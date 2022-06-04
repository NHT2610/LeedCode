//https://www.hackerrank.com/challenges/print-the-elements-of-a-linked-list/problem?isFullScreen=true
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct SinglyLinkedListNode {
	int data;
	SinglyLinkedListNode* next;
};

//vector<string> ParseString(const string& s, char ch) {
//	vector<string> result;
//	int len = int(s.length());
//	int j;
//	string temp;
//	for (int i = 0; i < len; ++i) {
//		for (j = i; j < len && s[j] != ch; ++j) {
//			temp += s[j];
//		}
//		result.push_back(temp);
//		temp = "";
//		i = j;
//	}
//	return result;
//}

void printLinkedList(SinglyLinkedListNode* head) {
	if (head == NULL) {
		return;
	}
	while (head != NULL) {
		cout << head->data << endl;
		head = head->next;
	}
}

SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) {
	if (head == NULL) {
		SinglyLinkedListNode* newNode = new SinglyLinkedListNode;
		newNode->data = data;
		newNode->next = NULL;
		head = newNode;
		return head;
	}
	SinglyLinkedListNode* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	SinglyLinkedListNode* newNode = new SinglyLinkedListNode;
	newNode->data = data;
	newNode->next = NULL;
	temp->next = newNode;
	return head;
}

int main() {
	string temp;
	getline(cin, temp);
	int N = stoi(temp);
	temp = "";
	SinglyLinkedListNode* head = new SinglyLinkedListNode;
	head = NULL;
	int number;
	for (int i = 0; i < N; ++i) {
		getline(cin, temp);
		number = stoi(temp);
		head = insertNodeAtTail(head, number);
		temp = "";
	}
	printLinkedList(head);
	return 0;
}