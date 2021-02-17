//
// Created by Ben Cullen on 2/5/21.
//

#include "Parser.h"

DatalogProgram Parser::parse(){
    return parseDatalogProgram();
};

DatalogProgram Parser::parseDatalogProgram(){
    /*
     * datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON
     * factList RULES COLON ruleList QUERIES COLON query queryList EOF
     */
    DatalogProgram program = DatalogProgram();
    //Schemes
    match(SCHEMES);
    match(COLON);
    Predicate * scheme  = parseScheme();
    std::vector<Predicate *> scheme_vec = parseSchemeList();

    scheme_vec.push_back(scheme);
    std::reverse(scheme_vec.begin(), scheme_vec.end());
    program.schemes = scheme_vec;

    // Facts
    match(FACTS);
    match(COLON);
    std::vector<Predicate *> fact_vec = parseFactList();
    std::reverse(fact_vec.begin(), fact_vec.end());
    program.facts = fact_vec;

    //Rule
    match(RULES);
    match(COLON);
    parseRuleList();

    //Queries
    match(QUERIES);
    match(COLON);
    Predicate * query  = parseQuery();
    std::vector<Predicate *> query_vec = parseQueryList();

    query_vec.push_back(query);
    std::reverse(query_vec.begin(), query_vec.end());
    program.queries = query_vec;

    //EOF
    match(ENDOFFILE);

    return program;
};

std::vector<Predicate *> Parser::parseSchemeList(){
    //FIRST(schemeList) = {ID}
    if (peek(ID)){
        Predicate * pred  = parseScheme();
        std::vector<Predicate *> pred_vec = parseSchemeList();

        pred_vec.push_back(pred);

        return pred_vec;
        //FOLLOW(schemeList) = {FACTS}
    } else if(peek(FACTS)){
        //Return for lambda
        return std::vector<Predicate *>();
    } else {
        //Throw exception
        throw(-1);
    }
};

std::vector<Predicate *> Parser::parseFactList(){
    //FIRST(factList) = {ID}
    if(peek(ID)){
        Predicate * fact = parseFact();
        std::vector<Predicate *> fact_vec = parseFactList();

        fact_vec.push_back(fact);

        return fact_vec;
        //FOLLOW(factList) = {RULES}
    } else if(peek(RULES)) {
        //Return for lambda
        return std::vector<Predicate *>();
    } else {
        //Throw exception
        throw(-1);
    }
};

void Parser::parseRuleList(){
    //FIRST(ruleList) = {ID}
    if(peek(ID)){
        parseRule();
        parseRuleList();
        //FOLLOW(ruleList) = {Queries}
    } else if(peek(QUERIES)){
        //Return for lambda
        return;
    } else {
        //Throw exception
        throw(-1);
    }
};

std::vector<Predicate *> Parser::parseQueryList(){
    //FIRST(queryList) = {ID}
    if(peek(ID)) {
        Predicate * query = parseQuery();
        std::vector<Predicate *> query_vec = parseQueryList();

        query_vec.push_back(query);
        return query_vec;

        //FOLLOW(queryList) = {EOF}
    } else if (peek(ENDOFFILE)) {
        //Return for lambda
        return std::vector<Predicate *>();
    } else {
        //Throw exception
        throw (-1);
    }
};
Predicate* Parser::parseScheme(){
    //FIRST(scheme) = {ID}
    if(peek(ID)) {
        Predicate * pred = new Predicate();
        pred->setName(currentToken->value);

        match(ID);
        match(LEFT_PAREN);
        //Make sure that first ID is included in parameters
        checkCurrent(ID); //Will fail if ID is not present
        Parameter* firstID = new TextParameter(currentToken->value);
        match(ID);

        std::vector<Parameter*> p_vec = parseIdList();
        p_vec.push_back(firstID);
        std::reverse(p_vec.begin(),p_vec.end());

        pred->setParameters(p_vec);
        match(RIGHT_PAREN);

        //std::cout << "Predicate Name:" << pred->name << std::endl;
        //std::cout << "Parameter Count:" << std::to_string(pred->paramaters.size()) << std::endl;
        return pred;
    } else {
        //Throw exception
        throw (-1);
    }
};

Predicate* Parser::parseFact(){
    if(peek(ID)){
        Predicate * pred = new Predicate();
        pred->setName(currentToken->value);

        match(ID);
        match(LEFT_PAREN);
        peek(STRING);
        Parameter* firstString = new TextParameter(currentToken->value);
        match(STRING);

        std::vector<Parameter*> p_vec = parseStringList();

        p_vec.push_back(firstString);
        std::reverse(p_vec.begin(),p_vec.end());
        pred->setParameters(p_vec);

        match(RIGHT_PAREN);
        match(PERIOD);
        return pred;
    } else {
        //Throw exception
        throw (-1);
    }
};

void Parser::parseRule(){
    parseHeadPredicate();
    match(COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(PERIOD);
};

Predicate* Parser::parseQuery(){
    Predicate* pred = parsePredicate();
    match(Q_MARK);
    return pred;
};

void Parser::parseHeadPredicate(){
    match(ID);
    match(LEFT_PAREN);
    match(ID);
    parseIdList();
    match(RIGHT_PAREN);
};

Predicate* Parser::parsePredicate(){
    Predicate * pred = new Predicate();
    checkCurrent(ID); // Will throw exception if current token is not ID
    pred->setName(currentToken->value);

    match(ID);
    match(LEFT_PAREN);

    Parameter * parameter = parseParameter();
    std::vector<Parameter*> p_vec = parseParameterList();
    p_vec.push_back(parameter);
    std::reverse(p_vec.begin(),p_vec.end());
    pred->setParameters(p_vec);

    match(RIGHT_PAREN);
    return pred;
};

std::vector<Predicate *> Parser::parsePredicateList(){
    //FIRST(predicateList) = {COMMA}
    if(peek(COMMA)){
        match(COMMA);
        Predicate* pred = parsePredicate();
        std::vector<Predicate*> p_vec = parsePredicateList();

        p_vec.push_back(pred);
        return p_vec;
        //FOLLOW(predicateList) = {PERIOD}
    } else if (peek(PERIOD)) {
        //Return for lambda
        return std::vector<Predicate*>();
    } else {
        //Throw exception
        throw(-1);
    }
};

std::vector<Parameter*> Parser::parseParameterList(){
    //FIRST(paramaterList)  = {COMMA}
    if(peek(COMMA)){
        match(COMMA);
        Parameter * parameter = parseParameter();
        std::vector<Parameter*> p_vec = parseParameterList();
        p_vec.push_back(parameter);
        return p_vec;

        //FOLLOW(paramaterList) = {RIGHT_PAREN}
    } else if(peek(RIGHT_PAREN)){
        //Return for lambda
        return std::vector<Parameter*>();
    } else {
        //Throw exception
        throw(-1);
    }
};

std::vector<Parameter*> Parser::parseStringList(){
    //FIRST(stringList) = {COMMA}
    if(peek(COMMA)){
        match(COMMA);
        checkCurrent(STRING); //Will throw exception if there is no String to extract
        Parameter * p = new TextParameter(currentToken->value);

        match(STRING);
        std::vector<Parameter*> p_vec = parseStringList();
        p_vec.push_back(p);
        return p_vec;
        //FOLLOW(stringList) = {RIGHT_PAREN}
    } else if(peek(RIGHT_PAREN)){
        //Return for lambda
        return std::vector<Parameter *>();
    } else {
        //Throw exception
        throw(-1);
    }
};

std::vector<Parameter*> Parser::parseIdList(){
    //FIRST(idList) = {COMMA}
    if(peek(COMMA)){
        match(COMMA);
        checkCurrent(ID); //Will throw exception if there is no ID to extract
        Parameter * p = new TextParameter(currentToken->value);
        //std::cout << "Paramater added:" << p->toString() << std::endl;
        match(ID);
        std::vector<Parameter*> p_vec = parseIdList();
        p_vec.push_back(p);
        //std::cout << "Parameter count:" << std::to_string(p_vec.size()) << std::endl;
        return p_vec;
        //FOLLOW(idList) = {RIGHT_PAREN}
    } else if (peek(RIGHT_PAREN)){
        //Return for empty vector lambda
        return std::vector<Parameter *>();
    } else {
        //Throw execution
        throw(-1);
    }
};

Parameter* Parser::parseParameter(){
    if(peek(STRING)){
        Parameter * p = new TextParameter(currentToken->value);
        match(STRING);
        return p;
    } else if (peek(ID)) {
        Parameter * p = new TextParameter(currentToken->value);
        match(ID);
        return p;

        //FIRST(expression) = {LEFT_PAREN}
    } else if (peek(LEFT_PAREN)) {
        return parseExpression();
    } else {
        //Throw exception
        throw (-1);
    }
};

Parameter* Parser::parseExpression(){
    match(LEFT_PAREN);
    Parameter* left = parseParameter();
    std::string opr = parseOperator();
    Parameter* right = parseParameter();
    ExpressionParameter* exp = new ExpressionParameter(left->toString(), opr, right->toString());
    match(RIGHT_PAREN);
    return exp;
};

std::string Parser::parseOperator(){
    if(peek(ADD)){
        std::string value = currentToken->value;
        match(ADD);
        return value;
    } else if (peek(MULTIPLY)) {
        std::string value = currentToken->value;
        match(MULTIPLY);
        return value;
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

bool Parser::peek(TokenType toCheck){
    if(currentToken->getType() == toCheck){
        return true;
    } else {
        return false;
    }
}

void Parser::checkCurrent(TokenType toMatch){
    //std::cout << "Current Type:" << currentType  << std::endl;
    //std::cout << "Type to match:" << toMatchString << std::endl;
    if(currentToken->getType() == toMatch){
        //std::cout << "Successfully matched " << currentToken->typeToString(currentToken->getType());
        //std::cout << " and " << currentToken->typeToString(toMatch) << std::endl;
    } else {
        //Throw execption
        //std::cout  << currentToken->typeToString(currentToken->getType());
        //std::cout << " did not match " << currentToken->typeToString(toMatch) << std::endl;
        throw (-1);
    }
}


Token * Parser::getCurrentToken(){
    return currentToken;
};