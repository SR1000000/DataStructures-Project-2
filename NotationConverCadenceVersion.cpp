#include "NotationConverter.hpp"
#include <iostream>
#include <string>

class Node
{ // declares the node class to build the deque with.

public:
    std::string data; // the nodes will have 3 values, a string data, next pointer, and previous pointer
    Node *next;
    Node *prev;

    Node(std::string val) : data(val), next(nullptr), prev(nullptr){}; // default values will be data == val, next == null, and prev == null.
};

class deque
{ // declares the interface for the deque.

private:
    Node *head; // the internal data will the be the head and tail nodes
    Node *tail;

public:
    deque() : head(nullptr), tail(nullptr){}; // default values will be head == null and tail == null

    ~deque()
    { // deconstructor method for deque
        while (head != nullptr)
        {
            removeFront();
        }
    };

    void addElementFront(std::string val)
    { // pushFront method for the deque
        Node *newNode = new Node(val);
        if (head == nullptr)
        { // if deque is empty, both tail and head will point to the new node
            head = tail = newNode;
        }
        else
        {
            newNode->next = head; // newNode will become the new head
            head->prev = newNode;
            head = newNode;
        }
    };

    void addElementBack(std::string val)
    { // pushBack method for the deque
        Node *newNode = new Node(val);
        if (tail == nullptr)
        { // if the deque is empty, the head and tail will point to the newNode
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode; // newNode will become the new tail
            newNode->prev = tail;
            tail = newNode;
        }
    };

    void removeBack()
    { // popBack method for the deque
        if (tail == nullptr)
        {
            std::cout << "empty deque" << std::endl; // if the deque is empty, will print the error message
        }
        else
        {
            Node *temp = tail;
            if (tail == head)
            {
                head = tail = nullptr; // if there is only 1 node, will make head and tail null
            }
            else
            {
                tail = tail->prev; // moves the tail pointer to the previous node
                tail->next = nullptr;
            }
            delete temp; // deletes the tail
        }
    };

    void removeFront()
    { // popFront method for the deque
        if (head == nullptr)
        {
            std::cout << "empty deque" << std::endl; // if deque is empty, prints the error message
        }
        else
        {
            Node *temp = head;
            if (head == tail)
            { // if the deque only has 1 node, makes the head and tail pointer null
                head = tail = nullptr;
            }
            else
            {
                head = head->next; // moves the head pointer to the next node
                head->prev = nullptr;
            }
            delete temp; // deletes the current head.
        }
    };

    std::string peekFront()
    { // peekFront method for the deque
        if (head == nullptr)
        {
            return "error"; // if deque is empty, returns the error message
        }
        else
        {
            return head->data; // returns the head data
        }
    };

    std::string peekBack()
    { // peekBack method for the deque
        if (tail == nullptr)
        { // if deque is empty, returns the error message
            return "error";
        }
        else
        {
            return tail->data; // returns the tail data
        }
    };

    bool isOperand(char x)
    { // declares the method to check if the given character is a letter
        return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
    };

    bool isEmpty()
    { // declares the method to check if the deque is empty
        return head == nullptr;
    }

    int precedence(char x)
    { // declares the method to check if the given character is an operator, and what precedence it takes
        if (x == '+' || x == '-')
        {
            return 1;
        }
        if (x == '*' || x == '/')
        {
            return 2;
        }
        return 0;
    };

    std::string reverse(std::string x)
    { // declares the method to reverse the given string
        int n = x.length();
        for (int i = 0; i < n / 2; i++)
        {
            char temp = x[i];
            x[i] = x[n - i - 1];
            x[n - i - 1] = temp;
        }
        return x;
    };
};

class NotationConverter : public NotationConverterInterface
{
public:
    deque input; // declares the deque to be used for all operations.

    std::string postfixToInfix(std::string inStr) override
    {
        for (int i = 0; i < inStr.length(); i++)
        {
            if (input.isOperand(inStr[i]))
            {                                // if the current character in the string is an operand
                std::string op(1, inStr[i]); // creates a string and typecasts the character to it
                input.addElementFront(op);   // adds the character to front of the deque
            }
            else if (inStr[i] == ' ')
            {
                continue; // if the current character is a whitespace, continues and ignores it
            }
            else
            {

                std::string op1 = input.peekFront();                                 // creates a string op1 and puts sets it to the top of the deque
                input.removeFront();                                                 // pops the top of the deque
                std::string op2 = input.peekFront();                                 // creates a string op2 and puts sets it to the top of the deque
                input.removeFront();                                                 // pops the top of the deque
                input.addElementFront("(" + op2 + ' ' + inStr[i] + ' ' + op1 + ")"); // adds the new expression to the top of the deque
            };
        };
        return input.peekFront(); // returns the final expression
    };

    std::string postfixToPrefix(std::string inStr) override
    {
        for (int i = 0; i < inStr.length(); i++)
        {
            if (input.isOperand(inStr[i]))
            {                                // if the current character in the string is an operand
                std::string op(1, inStr[i]); // creates a string and typecasts the character to it
                input.addElementFront(op);   // adds the character to front of the deque
            }

            else if (inStr[i] == ' ')
            { // if the current character is a whitespace, continues and ignores it
                continue;
            }

            else
            {

                std::string op1 = input.peekFront(); // creates a string op1 and puts sets it to the top of the deque
                input.removeFront();                 // pops the top of the deque
                std::string op2 = input.peekFront(); // creates a string op2 and puts sets it to the top of the deque
                input.removeFront();                 // pops the top of the deque
                std::string combined = std::string(1, inStr[i]) + ' ' + op2 + ' ' + op1;
                input.addElementFront(combined); // adds the new expression to the top of the deque
            };
        };
        return input.peekFront(); // returns the final expression
    }

    std::string infixToPostfix(std::string inStr) override
    {
        std::string post; // declares the string to input the final expression to

        for (int i = 0; i < inStr.length(); i++)
        {
            if (input.isOperand(inStr[i]))
            {
                post += inStr[i]; // if the current character is an operand, it is added to the post string along with a whitespace
                post += ' ';
            }
            else if (inStr[i] == '(')
            {
                input.addElementFront("("); // if the current character is an open parantheses, it is added to the top of the deque
            }
            else if (inStr[i] == ')')
            {
                while (!input.isEmpty() && input.peekFront() != "(")
                {
                    post += input.peekFront(); // if the current character is a closed parentheses, it empties the deque to the post string
                    post += ' ';
                    input.removeFront();
                }
                input.removeFront(); // Removes the open parentheses from the deque
            }
            else if (inStr[i] != ' ')
            { // if the current character is a whitespace, it evaluates the order of operations for the expression and if it can be correctly applied to the post string
                while (!input.isEmpty() && input.precedence(input.peekFront()[0]) >= input.precedence(inStr[i]))
                {
                    post += input.peekFront();
                    post += ' ';
                    input.removeFront();
                }
                input.addElementFront(std::string(1, inStr[i]));
            }
        }

        while (!input.isEmpty())
        { // empties the deque to the post string
            post += input.peekFront();
            post += ' ';
            input.removeFront();
        }
        if (!post.empty() && post.back() == ' ')
        {
            post.pop_back(); // removes the final whitespace from the post string
        }
        return post; // returns the post string
    }

    std::string infixToPrefix(std::string inStr) override
    {
        inStr = input.reverse(inStr); // reverse the current input string
        for (auto &ch : inStr)
        { // for every character in the reversed string, it switches the closing and opening parentheses
            if (ch == '(')
                ch = ')';
            else if (ch == ')')
                ch = '(';
        }
        std::string postfix = infixToPostfix(inStr); // runs the reversed string through the infix to postfix method
        postfix = input.reverse(postfix);            // reverses the postfix method and returns it
        return postfix;
    }

    std::string prefixToInfix(std::string inStr) override
    {
        for (int i = inStr.length() - 1; i >= 0; i--)
        {
            if (input.isOperand(inStr[i]))
            { // if the current character is an operand, it is typecasted to the op string and applied to the front of the deque
                std::string op(1, inStr[i]);
                input.addElementFront(op);
            }

            else if (inStr[i] == ' ')
            { // if the current character is a whitespace, it is ignored
                continue;
            }

            else
            {
                std::string op1 = input.peekFront(); // creates a new string op1 and pops the current top of the deque to it
                input.removeFront();
                std::string op2 = input.peekFront(); // creates a new string op2 and pops the current top of the deque to it
                input.removeFront();
                input.addElementFront("(" + op1 + ' ' + inStr[i] + ' ' + op2 + ")"); // pushes the current expression to the top of the deque
            };
        };
        return input.peekFront(); // returns the final expression
    };

    std::string prefixToPostfix(std::string inStr) override
    {
        inStr = input.reverse(inStr); // reverses the input string
        for (int i = 0; i < inStr.length(); i++)
        {
            if (input.isOperand(inStr[i]))
            { // if the current character is an operand, it is typecasted and pushed to the front of the deque
                input.addElementFront(std::string(1, inStr[i]));
            }
            else if (inStr[i] == ' ')
            { // if the current character is a whitespace, it is ignored
                continue;
            }
            else
            {
                std::string op1 = input.peekFront(); // creates a string op1 and pops the top of the deque to it
                input.removeFront();
                std::string op2 = input.peekFront(); // creates a string op2 and pops to top of the deque to it
                input.removeFront();
                std::string temp = op1 + ' ' + op2 + ' ' + inStr[i];
                input.addElementFront(temp); // pushes the new expression to the top of the deque
            }
        }
        return input.peekFront(); // retuns the top of the deque
    }
};
