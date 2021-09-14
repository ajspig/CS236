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
//for some reason I had to change all the parameters
//not sure why
void Token::setType(TokenType Type) {
    this->type = Type;
}
void Token::setDescript(string des) {
    this->description = des;
}
void Token::setLine(int Line) {
    this->line = Line;
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
    output<< "(" << enumToString(getType()) << ",\"" << description << "\"," << line << ")" << endl;
    return output.str();
}