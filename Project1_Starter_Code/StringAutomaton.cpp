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
        isEOF = true;
        newLines++;
        Serr();
    }else if(input[index] == '\''){
        inputRead++;
        index++;
        S3(input);
    }else{
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S2(input);
    }
}void StringAutomaton::S2(const std::string& input) {
    if(index >= input.size()) {
        //we have gone past the size of our input string and should therefore return an undef token
        isEOF = true;
        newLines++;
        Serr();
    }else if (input[index] != '\'') {
        if(input[index] == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
        S2(input);
    } else if(input[index] == '\''){
        inputRead++;
        index++;
        S3(input);
    }
    else {
        Serr();
    }
}
void StringAutomaton::S3(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    } else {
        index++;
    }
}