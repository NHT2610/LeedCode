#include "Linked_List.h"

Node* initialize_node(int init_data) {
	Node* new_node = new Node;
	if (new_node == NULL) {
		cout << "Khong du vung nho!" << endl;
		return NULL;
	}
	new_node->data = init_data;
	new_node->next = NULL;
	return new_node;
}

void initialize_linked_list(linked_list*& list, Node*& head) {
	list->head = list->tail = head;
}

void add_head(linked_list*& list, int value) {
	Node* new_node = initialize_node(value);
	if (list->head == NULL) {
		list->head = list->tail = new_node;
		return;
	}
	new_node->next = list->head;
	list->head = new_node;
}

void add_tail(linked_list*& list, int value) {
	Node* new_node = initialize_node(value);
	if (list->head == NULL) {
		list->head = list->tail = new_node;
		return;
	}
	list->tail->next = new_node;
	list->tail = new_node;
}

void delete_head(linked_list*& list) {
	if (list->head == NULL) {
		return;
	}
	Node* p = list->head;
	list->head = p->next;
	delete p;
	if (list->head == NULL) {
		list->head = list->tail = NULL;
	}
}

void delete_tail(linked_list*& list) {
	if (list->head == NULL) {
		return;
	}
	Node* node = list->head;
	if (node == list->tail) {
		Node* p = list->head;
		list->head = list->tail = NULL;
		delete p;
		return;
	}
	while (node->next != list->tail) {
		node = node->next;
	}
	Node* p = list->tail;
	list->tail = node;
	node->next = NULL;
	delete p;
}

void clear(linked_list*& list) {
	if (list->head == NULL) {
		return;
	}
	Node* node = list->head;
	while (node != NULL) {
		delete_head(list);
		node = list->head;
	}
}

void add_element(linked_list*& list, int index, int value) {
	if (list->head == NULL && index != 0 || index < 0) {
		cout << "Khong ton tai vi tri " << index << " trong danh sach" << endl;
		return;
	}
	if (index == 0) {
		add_head(list, value);
		return;
	}
	Node* new_node = initialize_node(value);
	Node* node = list->head;
	int count = 0;
	while (node->next != NULL && count + 1 != index) {
		node = node->next;
		++count;
	}
	if (node->next != NULL) {
		new_node->next = node->next;
		node->next = new_node;
		return;
	}
	if (count + 1 == index) {
		add_tail(list, value);
		return;
	}
	cout << "Khong ton tai vi tri " << index << " trong danh sach" << endl;
}

void remove_element(linked_list*& list, int index) {
	if (list->head == NULL || index < 0) {
		cout << "Danh sach da rong!" << endl;
		return;
	}
	if (index == 0) {
		delete_head(list);
		return;
	}
	Node* node = list->head;
	if (node == list->tail && index != 0) {//Danh sách chỉ có một phần tử
		cout << "Khong ton tai vi tri " << index << " trong danh sach" << endl;
		return;
	}
	int count = 0;
	while (node->next != NULL && count + 1 != index) {
		node = node->next;
		++count;
	}
	if (node->next != NULL) {//index có tồn tại trong danh sách
		if (node->next == list->tail) {
			delete_tail(list);
			return;
		}
		Node* p_del = node->next;
		node->next = p_del->next;
		delete p_del;
		return;
	}
	cout << "Khong ton tai vi tri " << index << " trong danh sach" << endl;
}

void remove_duplicate_elements(linked_list*& list) {
	if (list->head == NULL || list->head == list->tail) {
		return;
	}
	Node* node = list->head;
	while (node != NULL) {
		Node* node1 = node;
		Node* node2 = node->next;
		while (node2 != NULL) {
			if (node2->data == node->data) {
				if (node2 == list->tail) {
					Node* del = node2;
					list->tail = node1;
					node1->next = NULL;
					delete del;
					break;
				}
				Node* del = node2;
				node1->next = node2->next;
				node2 = node1;
				delete del;
			}
			node1 = node2;
			node2 = node2->next;
		}
		node = node->next;
	}
}

void print_element(linked_list* list) {
	if (list->head == NULL) {
		cout << "Danh sach rong!" << endl;
		return;
	}
	Node* node = list->head;
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}

void swap_elements(Node*& before_A, Node*& A, Node*& before_B, Node*& B) {
	if (before_A == A) {//A là phần tử đầu
		if (A->next == B) {//Hai node cần đổi nằm cạnh nhau
			A->next = B->next;
			B->next = A;
			before_B = B;//Trả lại vị trí cho node p3, là node phía trước của node B
			return;
		}
		before_B->next = B->next;
		B->next = A->next;
		A->next = before_B->next;
		before_B->next = A;
		return;
	}
	if (A->next == B) {//Hai node cần đổi nằm cạnh nhau
		A->next = B->next;
		before_A->next = B;
		B->next = A;
		before_B = B;//Trả lại vị trí cho node p3, là node phía trước của node B
		return;
	}
	before_B->next = B->next;
	B->next = A->next;
	before_A->next = B;
	A->next = before_B->next;
	before_B->next = A;
}

void sort(linked_list*& list) {
	Node* p1 = list->head;
	Node* p2 = list->head;
	while (p2->next != NULL) {
		Node* p3 = p2;
		Node* p4 = p3->next;
		while (p4 != NULL) {
			if (p4->data < p2->data) {
				swap_elements(p1, p2, p3, p4);
				if (p2 == list->head) {
					list->head = p4;
					p1 = list->head;
					p2 = list->head;
				}
				else {
					p2 = p1->next;//Trả lại vị trí node đang xét
				}
			}
			p3 = p3->next;
			p4 = p3->next;
		}
		if (p1 == p2) {//Trường hợp đầu tiên của vòng lặp khi p1 == p2 == list->head
			p2 = p2->next;
		}
		else {
			p1 = p2;
			p2 = p1->next;
		}
	}
	/*Trả lại vị trí cho list->tail*/
	Node* node = list->head;
	while (node->next != NULL) {
		node = node->next;
	}
	list->tail = node;
}