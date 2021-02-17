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

    if(int(this->parameters.size()) == 0){
        result += "No parameters found";
    }

    for(int i = 0; i < int(this->parameters.size()); i++){
        result += this->parameters[i]->toString();

        if(i == int(this->parameters.size()-1)){
            //If it's the last element
            result+=")";
        } else {
            result += ",";
        }
    }

    return result;
};
