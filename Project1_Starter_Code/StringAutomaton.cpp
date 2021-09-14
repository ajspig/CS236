//
// Created by Abigail Spigarelli on 9/13/21.
//

#include "StringAutomaton.h"
//call the base constructor:
//something along the lines of:
void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string& input) {
    if(index >= input.size()) {
        //we have gone past the size of our input string and should therefore return an undef token
        //we are just going to run the
        Serr();
        //but we might need to call the undefined token here somehow

    }else if (input[index] != '\'') {
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S1(input);
    } else if(input[index] == '\''){
        inputRead++;
    }
    else {
        Serr();
    }
}

