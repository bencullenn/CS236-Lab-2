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
        parseScheme();
        parseSchemeList();

        //FOLLOW(schemeList) = {FACTS}
    } else if(checkCurrent(FACTS)){
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw(-1);
    }
};

void Parser::parseFactList(){
    //FIRST(factList) = {ID}
    if(checkCurrent(ID)){
        parseFact();
        parseFactList();
        //FOLLOW(factList) = {RULES}
    } else if(checkCurrent(RULES)) {
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw(-1);
    }
};

void Parser::parseRuleList(){
    //FIRST(ruleList) = {ID}
    if(checkCurrent(ID)){
        parseRule();
        parseRuleList();
        //FOLLOW(ruleList) = {Queries}
    } else if(checkCurrent(QUERIES)){
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw(-1);
    }
};

void Parser::parseQueryList(){
    //FIRST(queryList) = {ID}
    if(checkCurrent(ID)) {
        parseQuery();
        parseQueryList();

        //FOLLOW(queryList) = {EOF}
    } else if (checkCurrent(ENDOFFILE)) {
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw (-1);
    }
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
    match(ID);
    match(LEFT_PAREN);
    match(STRING);
    parseStringList();
    match(RIGHT_PAREN);
    match(PERIOD);
};

void Parser::parseRule(){
    parseHeadPredicate();
    match(COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(PERIOD);
};

void Parser::parseQuery(){
    parsePredicate();
    match(Q_MARK);
};

void Parser::parseHeadPredicate(){
    match(ID);
    match(LEFT_PAREN);
    match(ID);
    parseIdList();
    match(RIGHT_PAREN);
};

void Parser::parsePredicate(){
    match(ID);
    match(LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(RIGHT_PAREN);
};

void Parser::parsePredicateList(){
    //FIRST(predicateList) = {COMMA}
    if(checkCurrent(COMMA)){
        match(COMMA);
        parsePredicate();
        parsePredicateList();
        //FOLLOW(predicateList) = {PERIOD}
    } else if (checkCurrent(PERIOD)) {
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw(-1);
    }
};

void Parser::parseParameterList(){
    //FIRST(paramaterList)  = {COMMA}
    if(checkCurrent(COMMA)){
        match(COMMA);
        parseParameter();
        parseParameterList();
        //FOLLOW(paramaterList) = {RIGHT_PAREN}
    } else if(checkCurrent(RIGHT_PAREN)){
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw(-1);
    }
};

void Parser::parseStringList(){
    //FIRST(stringList) = {COMMA}
    if(checkCurrent(COMMA)){
        match(COMMA);
        match(STRING);
        parseStringList();
        //FOLLOW(stringList) = {RIGHT_PAREN}
    } else if(checkCurrent(RIGHT_PAREN)){
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw(-1);
    }
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
    if(checkCurrent(STRING)){
        match(STRING);
    } else if (checkCurrent(ID)) {
        match(ID);

        //FIRST(expression) = {LEFT_PAREN}
    } else if (checkCurrent(LEFT_PAREN)) {
        parseExpression();
    } else {
        //Throw exception
        throw (-1);
    }
};

void Parser::parseExpression(){
    match(LEFT_PAREN);
    parseParameter();
    parseOperator();
    parseParameter();
    match(RIGHT_PAREN);
};

void Parser::parseOperator(){
    if(checkCurrent(ADD)){
        match(ADD);
    } else if (checkCurrent(MULTIPLY)) {
        match(MULTIPLY);
    } else {
        //throw exception
        throw(-1);
    }
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
       //std::cout  << currentToken->typeToString(currentToken->getType());
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