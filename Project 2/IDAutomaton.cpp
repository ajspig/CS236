//
// Created by Abigail Spigarelli on 9/13/21.
//

#include "IDAutomaton.h"
#include <ctype.h>

//call the base constructor
void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void IDAutomaton::S1(const std::string& input) {
    if (isalpha(input[index]) | isdigit(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
}