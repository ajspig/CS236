//
// Created by Abigail Spigarelli on 9/8/21.
//

#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(string toMatch, TokenType tokenType) {
//receives a string in its constructor which indicates what exact string it's trying to match.

}

//int MatcherAutomaton::S0(const string &input) {
//    bool isMatch = true;
//    inputRead =0;
//    for(int i =0; i < (int)toMatch.size() && isMatch; i++){
//        if(input[i] != toMatch[i]){
//            isMatch = false;
//        }
//    }
//    if(isMatch){
//        inputRead = toMatch.size();
//    }
//    return inputRead;
//}


//int MatcherAutomaton::Read(const string &input) {
//    bool isMatch = true;
//    int inputRead = 0;
//    for (int i=0; i < (int)toMatch.size() && isMatch; i++){
//        if(input[i] != toMatch[i]){
//            isMatch = false;
//        }
//    }
//    if (isMatch){
//        inputRead = toMatch.size();
//    }
//    return inputRead;
//}

// Then you'll just build a separate instance for each Automaton you are combinding
