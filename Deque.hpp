#ifndef DEQUE_H
#define DEQUE_H

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    Deque();
    ~Deque();
    bool empty() const;
    int getSize() const;
    void pushFront(const T& value);
    void pushBack(const T& value);
    void popFront();
    void popBack();
    T& front() const;
    T& back() const;
    void clear();
};

#endif /* DEQUE_H */