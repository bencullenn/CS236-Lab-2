//
// Created by Ben Cullen on 2/8/21.
//

#include "Rule.h"
std::string Rule::toString(){
    std::string result = "";
    result += (headPredicate->toString() + " :- ");
    for (int i = 0; i < predicates.size(); i++){
        result += predicates[i]->toString();
        if(i < predicates.size() - 1){
            result += ",";
        } else {
            result += ".";
        }
    }

    return result;
};

void Rule::setPredicates(std::vector<Predicate*> predicates){
    this->predicates = predicates;
};
void Rule::setHeadPredicate(Predicate* head){
    this->headPredicate = head;
};