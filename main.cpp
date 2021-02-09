#include <iostream>
#include <fstream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char* argv[]) {
    /*
     * PART 1: LEXER
     */
    //Create lexer
    Lexer lex = Lexer();

    //Open input file
    std::string fileName = argv[1];
    std::ifstream inputFile;
    std::string fileContents;

    inputFile.open(fileName, std::fstream ::in);
    //Make sure file could be opened
    if(inputFile.is_open()){
        //TODO make this more robust in case the ifstream doesn't recognize EOF
        while(inputFile.peek() != EOF) {
            fileContents.push_back(static_cast<char>(inputFile.get()));
        }
        //Assume end of file
        if (inputFile.peek() == EOF){
            fileContents.push_back(inputFile.get());
            //std::cout << "End of file reached" << std::endl;
        }
    } else {
        //std::cout << "File could could not be opened" << std::endl;
    }

    //For each line in the input file call run on it
    lex.run(fileContents);
    // Call print from lexer
    //lex.print();

    /*
     * PART 2: PARSER
    */

    //Create Parser
    Parser parser = Parser(lex.getTokens());

    try{
        parser.parse();
        std::cout << "Success!" << std::endl;
    } catch (int e) {
        std::cout << "Failure!" << std::endl;
        std::cout << "Failed on token " << parser.getCurrentToken()->toString() << std::endl;
        std::cout << "Exception:" << e << std::endl;
    }
    return 0;
}
