/*
    Deque implementation, inspired by COP 4530 class file implementation. 
*/

#include <iostream>
#include <stdexcept> //for specific logic exceptions

template <typename T>
Deque<T>::Deque() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
Deque<T>::~Deque() {
    expunge();  
}

//check if empty
template <typename T>
bool Deque<T>::empty() const {
    return size == 0;
}

//return size, tracked on push/pop
template <typename T>
int Deque<T>::sizeOf() const {
    return size;
}

//push to front (or onto left) of deque
template <typename T>
void Deque<T>::pushFront(const T& v) {
    Node* newNode = new Node(v);
    if (empty())
        head = tail = newNode;
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

//push to back (or onto right) of deque
template <typename T>
void Deque<T>::pushBack(const T& v) {
    Node* newNode = new Node(v);
    if (empty())
        head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

//pop front/left into nether
template <typename T>
void Deque<T>::popFront() {
    if (empty()) {
        throw std::length_error("Deque is empty. No pop.");
        return;
    }
    Node* tmp = head;
    head = head->next;
    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete tmp;
    size--;
}

//pop back/right into nether
template <typename T>
void Deque<T>::popBack() {
    if (empty()) {
        throw std::length_error("Deque is empty. No pop.");
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

//peek at front/left, does not pop
template <typename T>
T& Deque<T>::peekFront() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty. No front element.");
    }
    return head->elem;
}

//peek at back/right, does not pop
template <typename T>
T& Deque<T>::peekBack() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty. No back element.");
    }
    return tail->elem;
}

//for deconstruction, not to be confused with empty() which is a check
template <typename T>
void Deque<T>::expunge() {
    while (!empty()) {
        popFront();
    }
}
