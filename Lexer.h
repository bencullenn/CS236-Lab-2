#pragma once
#include <vector>
#include <iostream>
#include "Token.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "BlockCommentAutomaton.h"

class Lexer {
private:
    std::vector<Token *> tokens;
    std::vector<Automaton *> automatas;
public:
    Lexer() {
        // May need to add back new keyword to get it working correctly
        tokens = std::vector<Token *>();
        automatas =  std::vector<Automaton *>();
        // Add all of the Automaton instances
        automatas.push_back(new MatcherAutomaton(",", COMMA));
        automatas.push_back(new MatcherAutomaton(".", PERIOD));
        automatas.push_back(new MatcherAutomaton("?", Q_MARK));
        automatas.push_back(new MatcherAutomaton("(", LEFT_PAREN));
        automatas.push_back(new MatcherAutomaton(")", RIGHT_PAREN));
        automatas.push_back(new MatcherAutomaton(":", COLON));
        automatas.push_back(new MatcherAutomaton(":-", COLON_DASH));
        automatas.push_back(new MatcherAutomaton("*", MULTIPLY));
        automatas.push_back(new MatcherAutomaton("+", ADD));
        automatas.push_back(new MatcherAutomaton("Schemes", SCHEMES));
        automatas.push_back(new MatcherAutomaton("Facts", FACTS));
        automatas.push_back(new MatcherAutomaton("Rules", RULES));
        automatas.push_back(new MatcherAutomaton("Queries", QUERIES));
        automatas.push_back(new StringAutomaton(STRING));
        automatas.push_back(new CommentAutomaton(COMMENT));
        automatas.push_back(new BlockCommentAutomaton(COMMENT));
        automatas.push_back(new IDAutomaton(ID));

    }

    void run(std::string input);

    //Print all tokens in format and token count
    void print();
};