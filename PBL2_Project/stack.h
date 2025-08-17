#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept> // runtime_error
using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = NULL) : data(d), next(n) {}
    };

    Node* top;

    void copyFrom(const Stack& other) {
        if (other.top == NULL) {
            top = NULL;
            return;
        }

        Node* nodes[1000];
        int count = 0;
        Node* cur = other.top;
        while (cur) {
            nodes[count++] = cur;
            cur = cur->next;
        }
        top = NULL;
        for (int i = count - 1; i >= 0; --i) {
            push(nodes[i]->data);
        }
    }

public:
    // Constructor
    Stack() : top(NULL) {}

    // Copy constructor
    Stack(const Stack& other) : top(NULL) {
        copyFrom(other);
    }

    // Operator=
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // Destructor
    ~Stack() {
        clear();
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == NULL;
    }

    void push(const T& value) {
        Node* newNode = new Node(value, top);
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Empty stack, cannot delete!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    T topValue() const {
        if (isEmpty()) {
            throw runtime_error("Empty stack, cannot get top value!");
        }
        return top->data;
    }

    void edit(const T& oldValue, const T& newValue) {
        Node* current = top;
        while (current != NULL) {
            if (current->data == oldValue) {
                current->data = newValue;
                return;
            }
            current = current->next;
        }
        cout << "Cannot find value!" << endl;
    }

    void print() const {
        Node* current = top;
        cout << "Stack (top -> bottom): ";
        while (current != NULL) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

#endif // STACK_H
