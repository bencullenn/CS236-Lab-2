//
// Created by Ben Cullen on 1/30/21.
//
#pragma once
#include <iostream>
#include "Automaton.h"

class StringAutomaton : public Automaton {
private:
    bool undefinedString = false;
    int inputRead = 0;
public:
    StringAutomaton(TokenType type) : Automaton(type) {
        this->type = type;
    }

    // Start the automaton and return the number of characters inputRead
    // inputRead == 0 indicates the input was rejected
    // inputRead > 0 indicates the input was accepted
    int Read(const std::string &input);

    Token *CreateToken(std::string input, int lineNumber) {
        if (undefinedString == true){
            return new Token(UNDEFINED, input, lineNumber);
        } else {
            return new Token(type, input, lineNumber);
        }
    }

    void state0(const std::string &input);
    void state1(const std::string &input);
    void state2(const std::string &input);
    void state3(const std::string &input);
};
