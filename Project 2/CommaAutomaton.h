//
// Created by Abigail Spigarelli on 9/11/21.
//

#ifndef PROJECT1_STARTER_CODE_COMMAAUTOMATON_H
#define PROJECT1_STARTER_CODE_COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton {
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);};


#endif //PROJECT1_STARTER_CODE_COMMAAUTOMATON_H
