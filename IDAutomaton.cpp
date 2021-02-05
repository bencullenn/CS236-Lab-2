//
// Created by Ben Cullen on 1/30/21.
//

#include "IDAutomaton.h"

int IDAutomaton::Read(const std::string &input){
    inputRead = 0;
    state0(input);
    return inputRead;
}

void IDAutomaton::state0(const std::string &input){
    if(isalpha(input.at(inputRead))) {
      inputRead++;
      state1(input);
    }
};

void IDAutomaton::state1(const std::string &input){
    if(isalpha(input.at(inputRead)) || isdigit(input.at(inputRead))){
        inputRead++;
        state1(input);
    } else {
        //Input accepted
        return;
    }
};
