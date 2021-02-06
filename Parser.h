//
// Created by Ben Cullen on 2/5/21.
//
#pragma once
#include <vector>
#include <iostream>
#include "Token.h"


class Parser {
private:
    std::vector<Token *> tokens;
public:
    Parser(std::vector<Token *> tokens){
        this->tokens = tokens;
        //Print all tokens
        for(Token * tok:tokens){
            std::cout << tok->toString() << std::endl;
        }
    }
    void parse();
};
