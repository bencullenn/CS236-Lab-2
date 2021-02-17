//
// Created by Ben Cullen on 2/8/21.
//
#pragma once
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
public:
    std::vector<Predicate *> schemes;
    std::vector<Predicate *> queries;
    std::vector<Predicate *> facts;
    std::vector<Rule *> rules;
    std::set<std::string> domain;

    DatalogProgram(){
      this->schemes = std::vector<Predicate *>();
      this->queries = std::vector<Predicate *>();
      this->facts = std::vector<Predicate *>();
      this->rules = std::vector<Rule *>();
      this->domain = std::set<std::string>();
    };

    std::string toString();
    void calculateDomain();
};

