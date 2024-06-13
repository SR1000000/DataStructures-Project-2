/*
    Deque implementation copied from COP 4530 class files
*/

#include "Deque.hpp"
#include <iostream>

template <typename T>
Deque<T>::Deque() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
Deque<T>::~Deque() {
    clear();
}

template <typename T>
bool Deque<T>::empty() const {
    return size == 0;
}

template <typename T>
int Deque<T>::getSize() const {
    return size;
}

template <typename T>
void Deque<T>::pushFront(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

template <typename T>
void Deque<T>::pushBack(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

template <typename T>
void Deque<T>::popFront() {
    if (empty()) {
        throw std::length_error("Deque is empty. Cannot pop from front.");
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete temp;
    size--;
}

template <typename T>
void Deque<T>::popBack() {
    if (empty()) {
        throw std::length_error("Deque is empty. Cannot pop from back.");
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail)
        tail->next = nullptr;
    else
        head = nullptr;
    delete temp;
    size--;
}

template <typename T>
T& Deque<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty. Cannot access front element.");
    }
    return head->data;
}

template <typename T>
T& Deque<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty. Cannot access back element.");
    }
    return tail->data;
}

template <typename T>
void Deque<T>::clear() {
    while (!empty()) {
        popFront();
    }
}
