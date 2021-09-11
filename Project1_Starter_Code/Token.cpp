#include "Token.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Token::Token(TokenType type, std::string description, int line) {
    this->setType(type);
    this->setDescript(description);
    this->setLine(line);
}

void Token::setType(TokenType type) {
    this->type = type;
}
void Token::setDescript(string description) {
    this->description = description;
}
void Token::setLine(int line) {
    this->line = line;
}
TokenType Token::getType() const {
    return type;
}

string Token::getDescript() const {
    return description;
}

int Token::getLine() const {
    return line;
}
string Token::enumToString(TokenType token) const {
    switch(token){
        case TokenType::COMMA: return "COMMA"; break;
        case TokenType::PERIOD: return "PERIOD"; break;
        case TokenType::Q_MARK: return "Q_MARK"; break;
        case TokenType::LEFT_PAREN: return "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::MULTIPLY: return "MULTIPLY"; break;
        case TokenType::SCHEMES: return "SCHEMES"; break;
        case TokenType::FACTS: return "FACTS"; break;
        case TokenType::RULES: return "RULES"; break;
        case TokenType::QUERIES: return "QUERIES"; break;
        case TokenType::STRING: return "STRING"; break;
        case TokenType::COMMENT: return "COMMENT"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
        case TokenType::ID: return "ID"; break;
        case TokenType::ADD: return "ADD"; break;
        case TokenType::EOF_TYPE: return "EOF"; break;

    }
    return "ERROR";
}
string Token::toString() const {
    std::ostringstream output;
    output<< "(" << enumToString(getType()) << ", \"" << description << "\", " << line << ")" << endl;
    return output.str();
}