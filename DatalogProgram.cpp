//
// Created by Ben Cullen on 2/8/21.
//

#include "DatalogProgram.h"

std::string DatalogProgram::toString() {
    std::string result = "";
    result += "Schemes(" + std::to_string(schemes.size()) + "):\n";
    for(Predicate* scheme:schemes){
        result += ("  " + scheme->toString() + "\n");
    }

    result += "Facts(" + std::to_string(facts.size()) + "):\n";
    for(Predicate* fact:facts){
        result += ("  " + fact->toString() + ".\n");
    }


    result += "Rules(" + std::to_string(rules.size()) + "):\n";
    for(Rule* rule:rules){
        result += (rule->toString() + "\n");
    }

    result += "Queries(" + std::to_string(queries.size()) + "):\n";
    for(Predicate* query:queries){
        result += ("  " + query->toString() + "?\n");
    }

    calculateDomain();

    result += "Domain(" + std::to_string(domain.size()) + "):\n";
    for(std::string string:domain){
        result += ( string + "\n");
    }

    return result;
}

void DatalogProgram::calculateDomain(){
    std::set<std::string> domain = std::set<std::string>();

    for(Predicate* fact:facts){
        for(Parameter * string:fact->parameters){
            domain.insert(string->toString());
        }
    }

    this->domain = domain;
};
