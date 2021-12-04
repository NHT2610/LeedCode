#pragma once
#pragma once
#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
};

struct linked_list {
	Node* head, * tail;
};

Node* initialize_node(int init_data);
void initialize_linked_list(linked_list*& list, Node*& head);
void add_head(linked_list*& list, int value);
void add_tail(linked_list*& list, int value);
void delete_head(linked_list*& list);
void delete_tail(linked_list*& list);
void clear(linked_list*& list);
void add_element(linked_list*& list, int index, int value);
void remove_element(linked_list*& list, int index);
void remove_duplicate_elements(linked_list*& list);
void print_element(linked_list* list);
void swap_elements(Node*& before_A, Node*& A, Node*& before_B, Node*& B);
void sort(linked_list*& list);