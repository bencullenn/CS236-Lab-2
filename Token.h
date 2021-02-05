#pragma once
#include <string>
//Stores the token type, line number, and actual input string

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES,
    FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOFFILE
};


class Token {
    std::string value;
    int lineNum;
    TokenType tokenType;

public:
    Token(TokenType type, std::string strValue, int LNum){
        tokenType = type;
        lineNum = LNum;
        value = strValue;
    }

    std::string toString();
    std::string typeToString(TokenType type);
};
