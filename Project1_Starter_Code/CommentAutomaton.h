//
// Created by Abigail Spigarelli on 9/13/21.
//

#ifndef PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H
#include "Automaton.h"
    
class CommentAutomaton : public Automaton {
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
    void S5(const std::string& input);





};


#endif //PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H
