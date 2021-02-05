#pragma once
#include "Token.h"

class Automaton {
protected:
    int inputRead = 0;
    int newLines = 0;
    TokenType type;
public:
    Automaton(TokenType type) { this->type = type; }

    // Start the automaton and return the number of characters inputRead
    // inputRead == 0 indicates the input was rejected
    // inputRead > 0 indicates the input was accepted
    virtual int Read(const std::string &input) = 0;

    virtual Token *CreateToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber);
    }

    virtual int NewLinesRead() const { return newLines; }
};