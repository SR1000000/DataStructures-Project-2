/*
    Header file for Deque implementation
*/

#ifndef DEQUE_H
#define DEQUE_H

template <typename T>
class Deque {
private:
    struct Node {
        T elem;
        Node* prev;
        Node* next;
        Node(const T& value) : elem(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;   //for O(1) sizing

public:
    Deque();
    ~Deque();
    bool empty() const;
    int sizeOf() const;
    void pushFront(const T& v);
    void pushBack(const T& v);
    void popFront();
    void popBack();
    T& peekFront() const;
    T& peekBack() const;
    void clear();
};

#endif /* DEQUE_H */