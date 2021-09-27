#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "SchemesAutomaton.h"
#include "MatcherAutomaton.h"
#include "AddAutomaton.h"
#include "CommaAutomaton.h"
#include "FactsAutomaton.h"
#include "LeftParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "QMarkAutomaton.h"
#include "RightParenAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "IDAutomaton.h"

Lexer::Lexer() {
    tokens = new std::vector<Token*>();
    automata = new std::vector<Automaton*>();
    CreateAutomata();
}

Lexer::~Lexer() {
//    // clean up the memory in `automata` and `tokens`
//    for(unsigned int i =0; i < automata->size(); i++){
//        delete automata->at(i);
//    }
//    automata->clear();
//    for(unsigned int i =0; i < tokens->size(); i++){
//        delete tokens->at(i);
//    }
//    tokens->clear();
//}
}
vector<Token*>* Lexer::ReturnTokens() {
    return tokens;
}

void Lexer::CreateAutomata() {
    automata->push_back(new ColonAutomaton());
    automata->push_back(new ColonDashAutomaton());
    automata->push_back(new SchemesAutomaton());
    automata->push_back(new PeriodAutomaton());
    automata->push_back(new AddAutomaton());
    automata->push_back(new CommaAutomaton());
    automata->push_back(new FactsAutomaton());
    automata->push_back(new LeftParenAutomaton());
    automata->push_back(new MultiplyAutomaton());
    automata->push_back(new QMarkAutomaton());
    automata->push_back(new RightParenAutomaton());
    automata->push_back(new RulesAutomaton());
    automata->push_back(new SchemesAutomaton());
    automata->push_back(new QueriesAutomaton());
    automata->push_back(new CommentAutomaton());
    automata->push_back(new IDAutomaton());
    automata->push_back(new StringAutomaton());

}

string Lexer::toString() const {
    std::ostringstream output;

    for(unsigned int i =0; i < tokens->size(); i++){
        output << tokens->at(i)->toString();
    }
    output << "Total Tokens = " << tokens->size();
    return output.str();
}

void Lexer::Run(string& input) {
    lineNumber = 1;
    //set the bool isEOF to false to start off
    //while there are more characters to tokenize
    while(input.size() >0){
        maxRead = 0;

        Automaton *maxAutomaton = automata->front(); //set maxAutomaton to the first automaton in automata
//        bool newEOF = false;
//        maxAutomaton->setEOF(newEOF);

        while(isspace(input[0])) {
            if (input[0] == '\n') {
                maxRead =1;
                lineNumber++;
                input.erase(0, maxRead);
                if(input.size() <= 0){
                    break;
                }
                maxRead = 0;
            } else {
                maxRead = 1;
                input.erase(0, maxRead);
                maxRead = 0;
            }
        }
        if(input.size() <= 0){
            break;
        }

        //Here is the "Parallel" part of the algorithm
        //Each automaton runs with the same input
        for (Automaton *currentAutomaton : *automata) {
            int inputRead = currentAutomaton->Start((const string)input);//inputRead = automaton.Start(input)

            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = currentAutomaton; //set maxAutomaton to automaton
            }
        }

        // Here is the "Max" part of the algorithm
//        if((maxAutomaton->getUndef())) {
//            tokens->push_back(new Token(TokenType::UNDEFINED, input.substr(0,maxRead-1), lineNumber)); //add newToken to collection of all tokens
//            lineNumber += maxAutomaton->NewLinesRead(); //increment lineNumber by maxAutomaton.NewLinesRead()
//        }
        if((maxAutomaton->getEOF())){

            //as soon as isEOF is true, we know we have an undefined token on our hands

            tokens->push_back(new Token(TokenType::UNDEFINED, input.substr(0,maxRead-1), lineNumber)); //add newToken to collection of all tokens
            lineNumber += maxAutomaton->NewLinesRead(); //increment lineNumber by maxAutomaton.NewLinesRead()
            break;
        } else if (maxRead > 0) {

            Token *newToken = maxAutomaton->CreateToken(input.substr(0,maxRead),lineNumber); //set newToken to maxAutomaton.CreateToken(...)
            lineNumber += maxAutomaton->NewLinesRead(); //increment lineNumber by maxAutomaton.NewLinesRead()
            tokens->push_back(newToken); //add newToken to collection of all tokens
            if(tokens->at(tokens->size()-1)->getType() == TokenType::COMMENT){
                tokens->pop_back();
            }
        }
            // No automaton accepted input
            // Create single character undefined token
        else {
            maxRead =1;
            tokens->push_back(new Token(TokenType::UNDEFINED, input.substr(0,maxRead), lineNumber)); //add newToken to collection of all tokens

        }

        input.erase(0, maxRead);//remove maxRead characters from input
    }
    tokens->push_back(new Token(TokenType::EOF_TYPE, "", lineNumber)); //add end of file token to all tokens

}

