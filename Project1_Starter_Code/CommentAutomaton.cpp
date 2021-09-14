//
// Created by Abigail Spigarelli on 9/13/21.
//

#include "CommentAutomaton.h"
#include <istream>

//my single line comments still have /n at the end of their statements. WHy?

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') { //true for both comments
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {//this is where we split the comments out
        //this would be a multi line comment
        inputRead++;
        index++;
        S3(input);
    }else{
        //as long as the first character isnt a | then it is a line comment
        inputRead++;
        index++;
        S2(input);
    }
}
void CommentAutomaton::S2(const std::string& input) {
    // line comments!!!
    if ((input[index] != '\n') || (index >= input.size())) { //until we reach a new line or EOF just keep reading it in
        inputRead++;
        index++;
        S2(input);
    }else if(input[index] == '\n'){// || index >= input.size()) {
        newLines++;
        //we reach the end of the a SINGLE line comment
    }else{
        //I dont think we need this section
        //how do we handle if we the end of file is never reached?
        //not a comment
        Serr();
    }
}
void CommentAutomaton::S3(const std::string& input) {
    if(index >= input.size()){
        isEOF = true;
        newLines++;
        //inputRead++;
        //this is if we have reached EOF
        //how do we send the undefined token to the lexer class?


    }else if (input[index] != '|') {
        //keep reading the comment in
        inputRead++;
        index++;
        S3(input);

    }else if(input[index == '|']) {
        index++;
        S4(input);
        //need to complete the comment
    }
}
void CommentAutomaton::S4(const std::string& input) {
    if (input[index] == '#') {
        //this is where the multi line comment ends
        newLines++;
        //multi line comment complete!!
    }else{
        //not a comment
        Serr();
    }
}

