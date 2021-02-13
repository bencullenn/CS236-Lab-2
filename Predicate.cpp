//
// Created by Ben Cullen on 2/8/21.
//

#include "Predicate.h"

void Predicate::setName(std::string name){

};

void Predicate::setParameters(std::vector<Parameter*> parameters){

};

void Predicate::addParameter(Parameter* parameter){

};

void Predicate::toString(){
    std::string result = "";
    result += this->name;
    result += "(";

    for(int i = 0; i < this->paramaters.size(); i++){
        result += this->paramaters[i]->toString();

        if(i == this->paramaters.size()-2){
            //If it's the last element
            result+=")";
        } else {
            result += ", ";
        }
    }
};