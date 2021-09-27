#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*>* automata;
    vector<Token*>* tokens;
    int lineNumber;
    int maxRead;
    void CreateAutomata();

public:
    Lexer();
    ~Lexer();

    string toString() const;

    void Run(std::string& input);
    vector<Token *>* ReturnTokens();

};

#endif // LEXER_H

