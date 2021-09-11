//
// Created by Abigail Spigarelli on 9/11/21.
//

#ifndef PROJECT1_STARTER_CODE_RIGHTPARENAUTOMATON_H
#define PROJECT1_STARTER_CODE_RIGHTPARENAUTOMATON_H

#include <Automaton.h>

class RightParenAutomaton: public Automaton{
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_RIGHTPARENAUTOMATON_H

