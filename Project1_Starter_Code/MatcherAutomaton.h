//
// Created by Abigail Spigarelli on 9/8/21.
//

//will be used to generate simpler tokens (COMMA ect)

#ifndef PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
#define PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
#include "Automaton.h"


class MatcherAutomaton: public Automaton
    {
    private:
        string toMatch;
    public:
        MatcherAutomaton(string toMatch, TokenType tokenType);
        //originally had TokenType tokenType passed in as a command argument to the constructor because of sudo, took it out because I dont know why its there

        //int S0(const string& input);
        //int Read(const string& input);

};


#endif //PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
