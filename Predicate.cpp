//
// Created by Ben Cullen on 2/8/21.
//

#include "Predicate.h"

void Predicate::setName(std::string name){
    this->name = name;
};

void Predicate::setParameters(std::vector<Parameter*> parameters){
    this->parameters = parameters;
};

void Predicate::addParameter(Parameter* parameter){
    this->parameters.push_back(parameter);
};

std::string Predicate::toString(){
    std::string result = "";
    result += this->name;
    result += "(";

    if(this->parameters.size() == 0){
        result += "No parameters found";
    }

    for(int i = 0; i < this->parameters.size(); i++){
        result += this->parameters[i]->toString();

        if(i == this->parameters.size()-2){
            //If it's the last element
            result+=")";
        } else {
            result += ", ";
        }
    }

    return result;
};