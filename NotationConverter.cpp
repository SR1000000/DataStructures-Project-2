#include "NotationConverter.hpp"
#include "Deque.cpp"


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
       
        return "";
    }

    std::string prefixToInfix(std::string inStr) override {
   
        return "";
    }

    std::string prefixToPostfix(std::string inStr) override {
        
        return "";
    }

private:
    Deque<char> input;

    void TextToDeque(std::string text) {


    }

};
