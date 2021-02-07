//
// Created by Ben Cullen on 2/5/21.
//

#include "Parser.h"

void Parser::parse(){
    parseDatalogProgram();
};

void Parser::parseDatalogProgram(){
    /*
     * datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON
     * factList RULES COLON ruleList QUERIES COLON query queryList EOF
     */

    //Schemes
    match(SCHEMES);
    match(COLON);
    parseScheme();
    parseSchemeList();

    // Facts
    match(FACTS);
    match(COLON);
    parseFactList();

    //Rules
    match(RULES);
    match(COLON);
    parseRuleList();

    //Queries
    match(QUERIES);
    match(COLON);
    parseQuery();
    parseQueryList();

    //EOF
    match(ENDOFFILE);
};

void Parser::parseSchemeList(){

};

void Parser::parseFactList(){

};

void Parser::parseRuleList(){

};

void Parser::parseQueryList(){

};
void Parser::parseScheme(){

};

void Parser::parseFact(){

};

void Parser::parseRule(){

};

void Parser::parseQuery(){

};

void Parser::parseHeadPredicate(){

};

void Parser::parsePredicate(){

};

void Parser::parsePredicateList(){

};

void Parser::parseParameterList(){

};

void Parser::parseStringList(){

};

void Parser::parseIdList(){

};

void Parser::parseParameter(){

};

void Parser::parseExpression(){

};

void Parser::parseOperator(){

};

bool Parser::match(TokenType toMatch){
    //std::cout << "Current Type:" << currentType  << std::endl;
    //std::cout << "Type to match:" << toMatchString << std::endl;
   if(currentToken->getType() == toMatch){
       //std::cout << "Successfully matched " << currentToken->typeToString(currentToken->getType());
       //std::cout << " and " << currentToken->typeToString(toMatch) << std::endl;
       advanceInput();
   } else {
       //Throw execption
       //std::cout  << currentToken->typeToString(currentToken->getType());
       //std::cout << " did not match " << currentToken->typeToString(toMatch) << std::endl;
       throw (-1);
   }
}

void Parser::advanceInput(){
    currentIndex += 1;
    currentToken = tokens[currentIndex];
};