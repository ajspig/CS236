#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TYPE
};

class Token
{
private:
    TokenType type;
    string description;
    int line; //line number the token starts on
public:
    Token(TokenType type, std::string description, int line);

    ~Token();

    string toString() const; //want to be able to call this on each item of the vector
    string enumToString(TokenType token) const;

    TokenType getType() const;
    string getDescript() const;
    int getLine () const;
    void setType(TokenType type);
    void setDescript(string description);
    void setLine(int line);
};

#endif // TOKEN_H

