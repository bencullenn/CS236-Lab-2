#pragma once
#include "Automaton.h"

class MatcherAutomaton :
        public Automaton
{
private:
    std::string toMatch;
public:
    MatcherAutomaton(std::string toMatch, TokenType type): Automaton(type){
        this->toMatch = toMatch;
    };

    int Read(const std::string& input);

    Token *CreateToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber);
    }
};