#include "NotationConverter.hpp"
#include "Deque.cpp"
#include <iostream>     //for std exceptions

class NotationConverter : public NotationConverterInterface {
public:
    NotationConverter() : input(), output() {}
    ~NotationConverter() {
        input.empty();
        output.empty();
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
        try {
            i2preRecurse();
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        
        return DequeToText(input);
    }

    std::string prefixToInfix(std::string inStr) override {
   
        return "";
    }

    std::string prefixToPostfix(std::string inStr) override {
        
        return "";
    }

private:
    Deque<char> input;
    Deque<char> output;

    //Takes an expression string and puts it into the object's "input" deque
    void TextToDeque(std::string text) {
        for(auto p = text.begin(); p != text.end(); p++) {  //traverse entirety of "text"
            if(*p != ' ') input.pushBack(*p);
        }
    }

    //Takes an expression deque and returns it in string form (adding appropriate spaces)
    std::string DequeToText(Deque<char> x) {
        std::string out;
        char p, q;
        while(!x.empty()) {    //loop until deque is empty
            p = x.front();
            out.push_back(p);
            x.popFront();

            if(x.empty()) break;   //x reached the end, end for loop and skip the following space skipping
            q = x.front();  //check following element of x

            if(p == '(') {     //skip space for interior of parentheses
                
            } else if(p == ')' && q == ')') {  //skip space if ')' followed by ')'

            } else if(isChar(p) && q == ')') {//skip space if "p" is operand and next is ')' 
            
            } else 
                out.push_back(' ');   //Other than extra rules pertaining to (), every operator/operand is followed by a space
            q = ' ';
        }
        
        return out;
    }

    void i2preRecurse() {
        if(input.empty())
            return;
        if(input.front() == '(') {
            input.popFront();
            i2preRecurse();

            if(isOp(input.front())) {
                output.pushFront(input.front());
                input.popFront();
            } else
                throw std::invalid_argument("Expecting Operator");
            
            i2preRecurse();

            if(input.front() == ')')
                input.popFront();
            else
                throw std::invalid_argument("Expecting )");
                
        } else if(isChar(input.front())) {
            output.pushBack(input.front());
            input.popFront();
        } else
            throw std::invalid_argument("Expecting char or (");


    }

    bool isChar(const char &c) const {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }
    bool isOp(const char &c) const {
        return (c=='/' || c=='*' || c=='+' || c=='-' );
    }
};
