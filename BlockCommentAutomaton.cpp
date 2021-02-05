//
// Created by Ben Cullen on 1/30/21.
//

#include "BlockCommentAutomaton.h"

int BlockCommentAutomaton::Read(const std::string &input){
    inputRead = 0;
    newLines = 0;
    state0(input);
    return inputRead;
};

void BlockCommentAutomaton::state0(const std::string &input){
    if(input.at(inputRead) == '#'){
        inputRead++;
        state1(input);
    }
};

void BlockCommentAutomaton::state1(const std::string &input){
    if(input.at(inputRead) == '|'){
        inputRead++;
        state2(input);
    }
};

void BlockCommentAutomaton::state2(const std::string &input){
    if(input.at(inputRead) != '|') {
        if (input.at(inputRead) == -1) {
            // Case: EOF reached before end of comment
            undefinedComment = true;
            return;
        } else {
            if (input.at(inputRead) == '\n') {
                this->newLines++;
                //If we encounter new line increment newline value
            }
            //Case: Not EOF or |
            inputRead++;
            state2(input);
        }
    } else {
        //Case: If |
        inputRead++;
        state3(input);
    }
};

void BlockCommentAutomaton::state3(const std::string &input){
    if(input.at(inputRead) != '#'){
        //Case: Not #
        if (input.at(inputRead) == '\n') {
            this->newLines++;
            //If we encounter new line increment newline value
        }
        inputRead++;
        state2(input); 
    } else {
        //Case: Accept
        inputRead++;
        return;
    }
};
