//
// Created by Ben Cullen on 1/30/21.
//
#pragma once
#include "Automaton.h"

class IDAutomaton: public Automaton {
private:
    int inputRead = 0;
public:
    IDAutomaton(TokenType type) : Automaton(type) {
        this->type = type;
    }
    // Start the automaton and return the number of characters inputRead
    // inputRead == 0 indicates the input was rejected
    // inputRead > 0 indicates the input was accepted
    int Read(const std::string &input);

    Token *CreateToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber);
    }

    int NewLinesRead() const { return newLines; }

    void state0(const std::string &input);
    void state1(const std::string &input);
};
