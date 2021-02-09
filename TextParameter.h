//
// Created by Ben Cullen on 2/8/21.
//
#pragma once
#include <string>
#include "Parameter.h"

class TextParameter: public Parameter {
public:
    std::string data;
    TextParameter(std::string data){
        this->data = data;
    };

};


