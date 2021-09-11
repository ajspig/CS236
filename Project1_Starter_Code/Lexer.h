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
    //should lineNumber and maxRead be here?
    //do I want them to be accessed by other classes?
    //lets just test it out
    int lineNumber;
    int maxRead;
    //should maxAutomaton also be a private member variable

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    string toString() const;

    void Run(std::string& input);
    
    // TODO: add other public methods here

};

#endif // LEXER_H

