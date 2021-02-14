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
    std::vector<Parameter*> parameters;
    Predicate(){
      this->name = "";
      this->parameters = std::vector<Parameter*>();
    };

    void setName(std::string name);
    void setParameters(std::vector<Parameter*> parameters);
    void addParameter(Parameter* parameter);
    std::string toString();
};
