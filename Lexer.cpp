#include "Lexer.h"

 void Lexer::run(std::string input) {
    int lineNumber = 1;

    // While there are more characters to tokenize
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomation = automatas[0];

        //Check for spaces and new lines between characters
        while(isspace(input[0])){
            if(input[0] == '\n'){
                lineNumber += 1;
	    }

            input.erase(0,1);
        }

        // Here is the "Parallel" part of the algorithm
        // Each automaton runs with the same input
        for (Automaton* automaton : automatas) {
                int inputRead = automaton->Read(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomation = automaton;
                }
        }
        // Here is the "Max" part of the algorithm
        if (maxRead > 0) {
            //set newToken to maxAutomaton.CreateToken(...)
            //Update line count
            Token* newToken = maxAutomation->CreateToken(input.substr(0,maxRead), lineNumber);
            //increment lineNumber by maxAutomaton.NewLinesRead()
            lineNumber += maxAutomation->NewLinesRead();
            //add newToken to collection of all tokens
            tokens.push_back(newToken);
        } else {
            // No automaton accepted input; create invalid token
            //set maxRead to 1
            maxRead = 1;

            std::string firstChar = "";
            firstChar.push_back(input[0]);
            Token* newToken;

            if(input[0] == -1){
                //End of file token
                newToken = new Token(ENDOFFILE, "", lineNumber);
            } else {
                //Undefined token
                newToken = new Token(UNDEFINED, firstChar, lineNumber);
            }

            tokens.push_back(newToken);
        }

        // Update ‘input‘ by removing characters inputRead to create Token
        input.erase(0, maxRead);
    }
}

void Lexer::print() {
    for(Token* token: tokens){
        std::cout << token->toString() << std::endl;
    }

    std::cout << "Total Tokens = " << tokens.size() << std::endl;
}
