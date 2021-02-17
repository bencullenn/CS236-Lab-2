//
// Created by Ben Cullen on 2/5/21.
//
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "DatalogProgram.h"
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "TextParameter.h"
#include "ExpressionParameter.h"
#include "Rule.h"

class Parser {
private:
    Token* currentToken;
    int currentIndex;
    std::vector<Token *> tokens;
    DatalogProgram parseDatalogProgram();
    std::vector<Predicate *> parseSchemeList();
    std::vector<Predicate *> parseFactList();
    std::vector<Rule *> parseRuleList();
    std::vector<Predicate *> parseQueryList();
    Predicate* parseScheme();
    Predicate* parseFact();
    Rule* parseRule();
    Predicate* parseQuery();
    Predicate* parseHeadPredicate();
    Predicate* parsePredicate();
    std::vector<Predicate *> parsePredicateList();
    std::vector<Parameter*> parseParameterList();
    std::vector<Parameter*> parseStringList();
    std::vector<Parameter*> parseIdList();
    Parameter* parseParameter();
    Parameter* parseExpression();
    std::string parseOperator();
    void match(TokenType toMatch);
    void advanceInput();
    bool peek(TokenType toCheck);
    void checkCurrent(TokenType toMatch);

public:
    Parser(std::vector<Token *> tokens){
        this->tokens = tokens;
        //Print all tokens
        /*
        for(Token * tok:tokens){
            std::cout << tok->toString() << std::endl;
        }*/
        currentIndex = 0;
        currentToken = tokens[currentIndex];
    }
    DatalogProgram parse();
    Token * getCurrentToken();
};
