#include "NotationConverter.hpp"
#include "Deque.cpp"
#include <iostream>     //for std exceptions

class NotationConverter : public NotationConverterInterface {
public:
    NotationConverter() : input() {}
    ~NotationConverter() {
        input.empty();
    }
    std::string postfixToInfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return post2iRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";
    }

    std::string postfixToPrefix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            TextToDeque(post2iRecurse());
            return i2preRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";
    }

    std::string infixToPostfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return i2postRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";
    }

    std::string infixToPrefix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return i2preRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";
    }

    std::string prefixToInfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return pre2iRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";
    }

    std::string prefixToPostfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            TextToDeque(pre2iRecurse());
            return i2postRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";
    }

private:
    Deque<char> input;

    //Takes an expression string and puts it into the object's "input" deque
    void TextToDeque(std::string text) {
        for(auto p = text.begin(); p != text.end(); p++) {  //traverse entirety of "text"
            if(*p != ' ') input.pushBack(*p);
        }
    }

    std::string i2preRecurse() {
        std::string left, op, right;
        if(input.empty())
            return "";
        if(isChar(input.front())) {
            left = input.front();
            input.popFront();
            return left;
        }
        if(input.front() == '(') {
            input.popFront();

            left = i2preRecurse();

            if(isOp(input.front())) {
                op = input.front();
                input.popFront();
            } else
                throw std::invalid_argument("Expecting Operator");
            
            right = i2preRecurse();

            if(input.front() == ')')
                input.popFront();
            else
                throw std::invalid_argument("Expecting )");

            return op + " " + left + " " + right;    
        } else
            throw std::invalid_argument("Expecting char or (");
        return "";

    }

    std::string pre2iRecurse() {
        std::string left, op, right;
        if(input.empty())
            return "";
        if(isChar(input.front())) {
            left = input.front();
            input.popFront();
            return left;
        }
        if(isOp(input.front())) {
            op = input.front();
            input.popFront();

            left = pre2iRecurse();

            right = pre2iRecurse();

            return "(" + left + " " + op + " " + right + ")";    
        } else
            throw std::invalid_argument("Expecting operator or operand");
        return "";
    }

    std::string i2postRecurse() {
        std::string left, op, right;
        if(input.empty())
            return "";
        if(isChar(input.front())) {
            left = input.front();
            input.popFront();
            return left;
        }
        if(input.front() == '(') {
            input.popFront();

            left = i2postRecurse();

            if(isOp(input.front())) {
                op = input.front();
                input.popFront();
            } else
                throw std::invalid_argument("Expecting Operator");
            
            right = i2postRecurse();

            if(input.front() == ')')
                input.popFront();
            else
                throw std::invalid_argument("Expecting )");

            return left + " " + right + " " + op;    
        } else
            throw std::invalid_argument("Expecting char or (");
        return "";

    }

    std::string post2iRecurse() {
        std::string left, op, right;
        if(input.empty())
            return "";
        if(isChar(input.back())) {
            left = input.back();
            input.popBack();
            return left;
        }
        if(isOp(input.back())) {
            op = input.back();
            input.popBack();

            right = post2iRecurse();

            left = post2iRecurse();

            return "(" + left + " " + op + " " + right + ")";    
        } else
            throw std::invalid_argument("Expecting operator or operand");
        return "";
    }
    
    bool isChar(const char &c) const {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }
    bool isOp(const char &c) const {
        return (c=='/' || c=='*' || c=='+' || c=='-' );
    }
};
