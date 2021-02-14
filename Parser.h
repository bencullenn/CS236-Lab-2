//
// Created by Ben Cullen on 2/5/21.
//
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "DatalogProgram.h"
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "TextParameter.h"
#include "ExpressionParameter.h"

class Parser {
private:
    Token* currentToken;
    int currentIndex;
    std::vector<Token *> tokens;
    DatalogProgram parseDatalogProgram();
    std::vector<Predicate *> parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    Predicate* parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    std::vector<Parameter*> parseIdList();
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
    DatalogProgram parse();
    Token * getCurrentToken();
};
