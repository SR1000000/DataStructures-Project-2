#include "NotationConverter.hpp"
#include "Deque.hpp"
#include "Deque.cpp"
#include <iostream>     //for std exceptions

class NotationConverter : public NotationConverterInterface {
public:
    NotationConverter() : input() {}
    ~NotationConverter() {
        input.expunge();    
    }

    std::string postfixToInfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return post2iAlt(); //either post2iRecurse() or post2iAlt()
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string postfixToPrefix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            TextToDeque(post2iAlt());   //convert input(Post) to Infix text, then funnel Infix text to input 
            return i2preRecurse();  //input is Infix, now convert to Pre
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";  //should not reach this point, error/assertfailure if it does
    }
        

    std::string infixToPostfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return i2postRecurse();     //Call and return string from recursive function, no starter needed
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string infixToPrefix(std::string inStr) override {
        TextToDeque(inStr); 
        try {
            return i2preRecurse();  //Call and return string from recursive function, no starter needed
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string prefixToInfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            return pre2iRecurse();  //Call and return string from recursive function, no starter needed
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        
        return "";  //should not reach this point, error/assertfailure if it does
    }

    std::string prefixToPostfix(std::string inStr) override {
        TextToDeque(inStr);
        try {
            TextToDeque(pre2iRecurse());    //convert input(Pre) to Infix text, then funnel Infix text to input 
            return i2postRecurse();     //input is Infix, convert to Post string
        }
        catch(const std::exception& e) {
            std::cout << e.what() << '\n';
        }
        return "";  //should not reach this point, error/assertfailure if it does
    }

private:
    Deque<char> input;  //The input Deque that all functions work off of, and that TextToDeque pushes into

    //Takes an expression string and puts it into the object's "input" deque
    void TextToDeque(std::string text) {
        for(auto p = text.begin(); p != text.end(); p++) {  //traverse entirety of "text"
            if(*p != ' ') input.pushBack(*p);   //skip spaces
        }
    }

    //Recursive function that converts infix (stored in input) to prefix string
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

    //Recursive function that converts prefix (stored in input) to infix string
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
        return "";  //should not reach this point, error/assertfailure if it does    
    }

    //Recursive function that converts infix (stored in input) to postfix string
    std::string i2postRecurse() {
        std::string left, op, right;
        if(input.empty())
            return "";
        if(isChar(input.peekFront())) { //termination case, called on character
            left = input.peekFront();
            input.popFront();
            return left;
        }
        if(input.peekFront() == '(') {
            input.popFront();   //discard the '('

            left = i2postRecurse(); //call to fill left operand, either char or (

            if(isOp(input.peekFront())) {
                op = input.peekFront();
                input.popFront();
            } else
                throw std::invalid_argument("Expecting Operator");
            
            right = i2postRecurse();    //call to fill right operand, either char or (

            if(input.peekFront() == ')')
                input.popFront();   //discard the ')'
            else
                throw std::invalid_argument("Expecting )");

            return left + " " + right + " " + op;   //postfix string implementation 
        } else
            throw std::invalid_argument("Expecting char or ("); //recurse should not be called on anything else
        return "";  //should not reach this point, error/assertfailure if it does
    }

    //Recursive function that converts postfix (stored in input) to infix string
    //just a copy of pre2iRecurse but working off the back of input deque instead of front
    std::string post2iRecurse() {
        std::string left, op, right;
        if(input.empty())   //not termination case, if input is empty then number of operands/operators probably off
            return "";  
        if(isChar(input.peekBack())) {  //termination case: is character operand
            left = input.peekBack();
            input.popBack();
            return left;
        }
        if(isOp(input.peekBack())) {    //called on operator, fill with next two operands
            op = input.peekBack();
            input.popBack();

            right = post2iRecurse();

            left = post2iRecurse();

            return "(" + left + " " + op + " " + right + ")";   //Infix implementation    
        } else
            throw std::invalid_argument("Expecting operator or operand");
        
        return "";  //should not reach this point, error/assertfailure if it does
    }

    //Alternative implementation using stack form of Deque instead of queue
    //Processes input left to right instead of right to left from post2iRecurse
    std::string post2iAlt() {
        Deque<std::string> stak;    //for stack-based implementation, text output
        std::string left, op, right;
        while(!input.empty()) { //process entire input deque one element at a time
            if(isChar(input.peekFront())) { //Add encountered individual operands to stack
                left = input.peekFront();   //reuse string variable to cast char to string
                stak.pushBack(left);
                input.popFront();
            } else if(isOp(input.peekFront())) {    //when encounter operator
                //take two operands from stack, combine with operator into Infix string, then return
                //formatted string back to stack as a potential operand (or final output).
                op = input.peekFront();
                input.popFront();

                right = stak.peekBack();
                stak.popBack();

                left = stak.peekBack();
                stak.popBack();

                stak.pushBack("(" + left + " " + op + " " + right + ")");    //Infix implementation
            } else
                throw std::invalid_argument("Expecting operator or operand");
        }
        if(stak.sizeOf() == 1) {    //stak should have only one elem: the final formatted string
            right = stak.peekBack();
            stak.popBack();
        } else 
            throw std::out_of_range("stak size should be 1, is " +std::to_string(stak.sizeOf()) + " instead");
        return right;
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
