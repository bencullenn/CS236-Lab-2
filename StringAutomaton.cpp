//
// Created by Ben Cullen on 1/30/21.
//

#include "StringAutomaton.h"
int StringAutomaton::Read(const std::string &input){
    this->inputRead = 0;
    this->newLines = 0;
    state0(input);
    return this->inputRead;
}

void StringAutomaton::state0(const std::string &input){
    //Case: Starting Quote
    if(input.at(this->inputRead) == '\''){
        this->inputRead++;
        state1(input);
    }
};

void StringAutomaton::state1(const std::string &input){
    //Case: Not Quote
    if(input.at(this->inputRead) != '\''){
        //Case: End of file reached
        if(input.at(this->inputRead) == -1){
            undefinedString = true;
            return;
        } else {
            //Case: Not the end of file
            if(input.at(this->inputRead) == '\n'){
                //Count new lines
                this->newLines++;
            }
            this->inputRead++;
            state1(input);
        }
        //Case: Is quote
    } else if(input.at(this->inputRead) == '\''){
        this->inputRead++;
        state2(input);
    }
};

void StringAutomaton::state2(const std::string &input){
    //Case: Double quotes so go back
    if(input.at(this->inputRead) == '\''){
        this->inputRead++;
        state1(input);
    } else if(input.at(this->inputRead != '\'')){
        //Case: Not a quote return
        state3(input);
    }
};

void StringAutomaton::state3(const std::string &input){
    //Accept state
    return;
};
