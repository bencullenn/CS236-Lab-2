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
    //FIRST(schemeList) = {ID}
    if (checkCurrent(ID)){
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        parseIdList();
        match(RIGHT_PAREN);

        //FOLLOW(schemeList) = {Rules}
    } else if(checkCurrent(RULES)){
        //Return for lambda
        return;
    } else {
        //Throw exeption
        throw(-1);
    }
};

void Parser::parseFactList(){
    //FOLLOW(factList) = {Factlist}
};

void Parser::parseRuleList(){
    //FOLLOW(ruleList) = {Queries}
};

void Parser::parseQueryList(){
    //FOLLOW(queryList) = {EOF}
};
void Parser::parseScheme(){
    //FIRST(scheme) = {ID}
    if(checkCurrent(ID)) {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        parseIdList();
        match(RIGHT_PAREN);
    } else {
        //Throw exception
        throw (-1);
    }
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
    //FOLLOW(predicateList) = {PERIOD}
};

void Parser::parseParameterList(){
    //FOLLOW(paramaterList) = {RIGHT_PAREN}
};

void Parser::parseStringList(){
    //FOLLOW(stringList) = {RIGHT_PAREN}
};

void Parser::parseIdList(){
    //FIRST(idList) = {COMMA}
    if(checkCurrent(COMMA)){
        match(COMMA);
        match(ID);
        parseIdList();

        //FOLLOW(idList) = {RIGHT_PAREN}
    } else if (checkCurrent(RIGHT_PAREN)){
        //Return for lambda
        return;
    } else {
        //Throw execution
        throw(-1);
    }
};

void Parser::parseParameter(){

};

void Parser::parseExpression(){

};

void Parser::parseOperator(){

};

void Parser::match(TokenType toMatch){
    //std::cout << "Current Type:" << currentType  << std::endl;
    //std::cout << "Type to match:" << toMatchString << std::endl;
   if(currentToken->getType() == toMatch){
       //std::cout << "Successfully matched " << currentToken->typeToString(currentToken->getType());
       //std::cout << " and " << currentToken->typeToString(toMatch) << std::endl;
       advanceInput();
   } else {
       //Throw execption
       std::cout  << currentToken->typeToString(currentToken->getType());
       //std::cout << " did not match " << currentToken->typeToString(toMatch) << std::endl;
       throw (-1);
   }
}

void Parser::advanceInput(){
    currentIndex += 1;
    currentToken = tokens[currentIndex];
};

bool Parser::checkCurrent(TokenType toCheck){
    if(currentToken->getType() == toCheck){
        return true;
    } else {
        return false;
    }
}

Token * Parser::getCurrentToken(){
    return currentToken;
};