#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
class DoublyLinkedList {
private:
	struct Node {
		int data;
		Node* prev;
		Node* next;
		Node(int val, Node* p = nullptr, Node* n = nullptr) {
			data = val;
			prev = p;
			next = n;
		}
	};
	Node* head;
	Node* tail;
public:
	// constructor
	DoublyLinkedList() { head = nullptr; tail = nullptr; }
	void push_back(int value) {
		Node* newNode = new Node(value);
		if (!tail) // if there's no tail, the list is empty
			head = tail = newNode;
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}
	void push_front(int value) {
		Node* newNode = new Node(value);
		if (!head) // if there's no head, the list is empty
			head = tail = newNode;
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
	}
	void insert_after(int value, int position) {
		if (position < 0) {
			cout << "Position must be >= 0." << endl;
			return;
		}
		Node* newNode = new Node(value);
		if (!head) {
			head = tail = newNode;
			return;
		}
		Node* temp = head;
		for (int i = 0; i < position && temp; ++i)
			temp = temp->next;
		if (!temp) {
			cout << "Position exceeds list size. Node not inserted.\n";
			delete newNode;
			return;
		}
		newNode->next = temp->next;
		newNode->prev = temp;
		if (temp->next)
			temp->next->prev = newNode;
		else
			tail = newNode; // Inserting at the end
		temp->next = newNode;
	}
	void delete_val(int value) {
		if (!head) return; // Empty list
		Node* temp = head;
		while (temp && temp->data != value)
			temp = temp->next;
		if (!temp) return; // Value not found
		if (temp->prev) {
			temp->prev->next = temp->next;
		}
		else {
			head = temp->next; // Deleting the head
		}
		if (temp->next) {
			temp->next->prev = temp->prev;
		}
		else {
			tail = temp->prev; //Deleting the tail
		}
		delete temp;
	}

	void delete_pos(int pos) {
		if (!head || pos < 0) {
			return; // Empty list or invalid pos
		}
		Node* temp = head;
		for (int i = 0; i < pos && temp; i++) { //loop through list until node is found at pos
			temp = temp->next;
		}
		if (!temp) {  // pos not found
			cout << "Position not found" << endl;
			return;
		}
		
		if (temp->prev) {
			temp->prev->next = temp->next;
		}
		else {
			head = temp->next; // Deleting the head
		}
		if (temp->next) {
			temp->next->prev = temp->prev;
		}
		else {
			tail = temp->prev; //Deleting the tail
		}
		delete temp;
	}

	void pop_front() {
		if (!head) { //check empty list
			cout << "List is empty" << endl;
			return;
		}

		Node* temp = head;

		if (head == tail) { //case of one node
			head = tail = nullptr;
		}
		else {
			head = head->next; //move head up one
			head->prev = nullptr;
		}

		delete temp;
	}

	void pop_back() {
		if (!head) { //check empty list
			cout << "List is empty" << endl;
			return;
		}

		Node* temp = tail;

		if (head == tail) { //case of one node
			head = tail = nullptr;
		}
		else {
			tail = tail->prev; //move tail one down
			tail->next = nullptr;
		}

		delete temp;
	}
	void print() {
		Node* current = head;
		if (!head) { //check empty list
			cout << "List is empty" << endl;
			return;
		}
		while (current) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	void print_reverse() {
		Node* current = tail;
		if (!tail) { //check empty list
			cout << "List is empty" << endl;
			return;
		}
		while (current) {
			cout << current->data << " ";
			current = current->prev;
		}
		cout << endl;
	}
	~DoublyLinkedList() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
};
// Driver program
int main() {
	srand(time(0));
	DoublyLinkedList list;
	int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
	for (int i = 0; i < size; ++i)
		list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);
	cout << "List forward: " << endl;
	list.print();
	cout << "List backward: " << endl;
	list.print_reverse();
	cout << "Push front 100" << endl;
	list.push_front(100);
	list.print();
	cout << "Push front 200" << endl;
	list.push_front(200);
	list.print();
	cout << "Push back 300" << endl;
	list.push_back(300);
	list.print();
	cout << "Delete position 2:" << endl;
	list.delete_pos(2);
	list.print();
	cout << "Delete value 200:" << endl;
	list.delete_val(200);
	list.print();
	cout << "Pop front:" << endl;
	list.pop_front();
	list.print();
	cout << "Pop back:" << endl;
	list.pop_back();
	list.print();
	return 0;
}