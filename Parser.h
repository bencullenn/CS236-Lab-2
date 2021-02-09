//
// Created by Ben Cullen on 2/5/21.
//
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Token.h"


class Parser {
private:
    Token* currentToken;
    int currentIndex;
    std::vector<Token *> tokens;
    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();
    void parseExpression();
    void parseOperator();
    void match(TokenType toMatch);
    void advanceInput();
    bool checkCurrent(TokenType toCheck);

public:
    Parser(std::vector<Token *> tokens){
        this->tokens = tokens;
        //Print all tokens
        for(Token * tok:tokens){
            std::cout << tok->toString() << std::endl;
        }
        currentIndex = 0;
        currentToken = tokens[currentIndex];
    }
    void parse();
    Token * getCurrentToken();
};
