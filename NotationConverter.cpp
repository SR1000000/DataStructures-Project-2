#include "NotationConverter.hpp"
#include "Deque.cpp"
#include <iostream>     //for std exceptions

class NotationConverter : public NotationConverterInterface {
public:
    NotationConverter() : input(), stak() {}
    ~NotationConverter() {
        input.empty();
        stak.empty();
    }

    std::string postfixToInfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return post2iAlt();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";

        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string postfixToPrefix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            TextToDeque(post2iAlt());
            return i2preRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string infixToPostfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return i2postRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string infixToPrefix(std::string inStr) override {
        TextToDeque(inStr); 
        try {
            return i2preRecurse();  //apply recursion directly, no starter
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string prefixToInfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return pre2iRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";  //should not reach this point, error/assertfailure if it does
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
        return "";  //should not reach this point, error/assertfailure if it does
    }

private:
    Deque<char> input;  //The input Deque that all functions work off of, and that TextToDeque pushes into
    Deque<std::string> stak;

    //Takes an expression string and puts it into the object's "input" deque
    void TextToDeque(std::string text) {
        for(auto p = text.begin(); p != text.end(); p++) {  //traverse entirety of "text"
            if(*p != ' ') input.pushBack(*p);   //skip spaces
        }
    }

    //Recursive function that converts infix to prefix
    std::string i2preRecurse() {
        std::string left, op, right;
        if(input.empty())   //In case function is called on empty string, not a termination case
            return "";  
        if(isChar(input.peekFront())) { //Termination case, called on a character
            left = input.peekFront();   //reuse an already declared str variable
            input.popFront();
            return left;
        }
        if(input.peekFront() == '(') {
            input.popFront();   //discard the '('

            //left operand is either character or another '('
            left = i2preRecurse();

            if(isOp(input.peekFront())) {
                op = input.peekFront();
                input.popFront();
            } else
                throw std::invalid_argument("Expecting Operator");
            
            //right operand is either character or another '('
            right = i2preRecurse();

            if(input.peekFront() == ')')
                input.popFront();   //discard the ')'
            else
                throw std::invalid_argument("Expecting )");

            return op + " " + left + " " + right;   //Prefix implementation
        } else
            throw std::invalid_argument("Expecting char or ("); //recurse should not be called on anything else
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string pre2iRecurse() {
        std::string left, op, right;
        if(input.empty())
            return "";  //In case function is called on empty string, not a termination case
        if(isChar(input.peekFront())) { //Termination case, called on a character
            left = input.peekFront();
            input.popFront();
            return left;
        }
        if(isOp(input.peekFront())) {   //Called on an operator, recurse twice more to fill left and right operand values
            op = input.peekFront();
            input.popFront();

            left = pre2iRecurse();

            right = pre2iRecurse();

            return "(" + left + " " + op + " " + right + ")";   //Infix implementation    
        } else
            throw std::invalid_argument("Expecting operator or operand");
        return "";  //should not reach this point, error/assertfailure if it does    }

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

    //Alternative implementation using stack form of Deque instead of queue
    std::string post2iAlt() {
        std::string left, op, right;
        while(!input.empty()) {
            if(isChar(input.front())) {
                left = input.front();
                stak.pushBack(left);
                input.popFront();
            } else if(isOp(input.front())) {
                op = input.front();
                input.popFront();

                right = stak.back();
                stak.popBack();

                left = stak.back();
                stak.popBack();

                stak.pushBack("(" + left + " " + op + " " + right + ")");    
            } else
                throw std::invalid_argument("Expecting operator or operand");
        }
        if(stak.getSize() == 1) {
            right = stak.back();
            stak.popBack();
        } else 
            throw std::out_of_range("stak size should be 1, is " +std::to_string(stak.getSize()) + " instead");
        return  right;
    }

    //helper function to check for lowercase or uppercase letter
    bool isChar(const char &c) const {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }
    //helper function to check for operator
    bool isOp(const char &c) const {
        return (c=='/' || c=='*' || c=='+' || c=='-' );
    }
};
