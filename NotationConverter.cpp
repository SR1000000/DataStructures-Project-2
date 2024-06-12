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

        return "";
    }

    std::string postfixToPrefix(std::string inStr) override {
        
        return "";
    }

    std::string infixToPostfix(std::string inStr) override {
        
        return "";
    }

    std::string infixToPrefix(std::string inStr) override {
        TextToDeque(inStr);
        std::string out;
        try {
            out = i2preRecurse();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return out;
    }

    std::string prefixToInfix(std::string inStr) override {
   
        return "";
    }

    std::string prefixToPostfix(std::string inStr) override {
        
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

    bool isChar(const char &c) const {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }
    bool isOp(const char &c) const {
        return (c=='/' || c=='*' || c=='+' || c=='-' );
    }
};
