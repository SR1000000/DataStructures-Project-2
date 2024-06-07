#include "NotationConverter.hpp"
#include "Deque.cpp"
#include <cassert>     //for debug purposes only

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
        std::string yy = DequeToText(input);
        return yy;
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
        out.reserve(x.getSize() * 2);   //twice the size of "x" to account for addition of spaces
        for(auto p = out.begin(); !x.empty(); p++) {    //loop until deque is empty
            *p = x.front();
            x.popFront();
            if(x.empty()) break;   //x reached the end, end for loop and skip the following space skipping
            if(*p == '(') {     //skip space for interior of parentheses
                
            } else if(*p == ')' && x.front() == ')') {  //skip space if ')' followed by ')'

            } else if(isChar(*p) && x.front() == ')') {//skip space if "p" is operand and next is ')' 
            
            } else 
                *(++p) = ' ';   //Other than extra rules pertaining to (), every operator/operand is followed by a space
            assert("breakpoint");
        }
        assert("breakpoint");
        return out;
    }

    bool isChar(const char &c) const {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }
    bool isOp(const char &c) const {
        return (c=='/' || c=='*' || c=='+' || c=='-' );
    }
};
