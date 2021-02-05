//
// Created by Ben Cullen on 1/30/21.
//

#include "CommentAutomaton.h"

int CommentAutomaton::Read(const std::string &input){
    inputRead = 0;
    state0(input);
    return inputRead;
}

void CommentAutomaton::state0(const std::string &input){
    if(input.at(inputRead) == '#'){
        inputRead++;
        state1(input);
    }
};


void CommentAutomaton::state1(const std::string &input){
   if(input.at(inputRead) != '|'){
       inputRead++;
       state2(input);
   }
};

void CommentAutomaton::state2(const std::string &input){
    if(input.at(inputRead) != -1 && input.at(inputRead) != '\n'){
        inputRead++;
        state2(input);
    } else {
        //Case accept
        return;
    }
};

