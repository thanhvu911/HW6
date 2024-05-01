
#include "linked_list.h"
#include <stdexcept>
#include <iostream>

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T> *current = head;
    while (current != nullptr) {
        Node<T> *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    numItems = 0;
}

template <typename T>
void LinkedList<T>::insert(size_t pos, T item) {
    if (pos > numItems) {
        throw std::invalid_argument("Can't insert at that position.");
    }
    Node<T> *newNode = new Node<T>;
    newNode->data = item;
    if (pos == 0) {
        push_front(item);
    } else if (pos == numItems) {
        push_back(item);
    } else {
        Node<T> *currentNode = get_node(pos);
        Node<T> *prevNode = currentNode->prev;

        newNode->next = currentNode;
        newNode->prev = prevNode;
        currentNode->prev = newNode;
        prevNode->next = newNode;

        numItems++;
    }
}


template <typename T> 
void LinkedList<T>::push_back(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;
	
	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	tail->next = n;
	n->prev = tail;
	tail = n;	
}


template <typename T>
void LinkedList<T>::push_front(T item){
	Node<T> *n = new Node<T>;
	n->data = item;
	numItems++;

	if(head == nullptr){
		head = n;
		tail = n;
		return;
	}

	head->prev = n;
	n->next = head;
	head = n;
}


template <typename T>
T LinkedList<T>::at(size_t idx){
	if(idx >= numItems){
		throw std::invalid_argument("List index out of range: " + std::to_string(idx));
	}

	Node<T> *n = get_node(idx);
	return n->data;
}


template <typename T>
Node<T> *LinkedList<T>::get_node(size_t idx){

	size_t i = 0;
	Node<T> *cur = head;
	while(i < idx){
		cur = cur->next;
		i++;
	}

	return cur;
}



