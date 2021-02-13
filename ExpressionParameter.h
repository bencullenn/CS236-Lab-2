//
// Created by Ben Cullen on 2/8/21.
//
#pragma once
#include <string>
#include <iostream>
#include "Parameter.h"
#include "TextParameter.h"

class ExpressionParameter: public Parameter {
public:
    std::string leftArg;
    std::string operand;
    std::string rightArg;
    ExpressionParameter(std::string leftArg, std::string operand, std::string rightArg){
        this->leftArg = leftArg;
        this->operand = operand;
        this->rightArg = rightArg;
    };

    std::string toString();
};

