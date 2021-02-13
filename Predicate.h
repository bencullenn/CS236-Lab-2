//
// Created by Ben Cullen on 2/8/21.
//
#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
public:
    std::string name;
    std::vector<Parameter*> paramaters;
    Predicate(){
      this->name = "";
      this->paramaters = std::vector<Parameter*>();
    };

    void setName(std::string name);
    void setParameters(std::vector<Parameter*> parameters);
    void addParameter(Parameter* parameter);
    void toString();
};
