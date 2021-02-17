//
// Created by Ben Cullen on 2/8/21.
//

#pragma once
#include <string>
#include <vector>
#include "Predicate.h"

class Rule {
public:
    Predicate* headPredicate;
    std::vector<Predicate*> predicates;
    Rule(){
        this->headPredicate = new Predicate;
        this->predicates = std::vector<Predicate*>();
    }
    void setPredicates(std::vector<Predicate*> predicates);
    void setHeadPredicate(Predicate* head);
    std::string toString();
};

