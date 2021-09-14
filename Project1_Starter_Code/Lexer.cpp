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
    //while there are more characters to tokenize
    while(input.size() >0){
        maxRead = 0;

        Automaton *maxAutomaton = automata->front(); //set maxAutomaton to the first automaton in automata
        //I suspect that my problem is the fact that im not updating maxAutomaton with new automatons
        //TODO: you need to handle whitespace inbetween tokens
        //do I say input.peek()
        //char current = input.at(0);
        while(isspace(input[0])) {
            if (input[0] == '\n') {
                maxRead = 1;
                lineNumber++;
                input.erase(0, maxRead);
            } else {
                maxRead = 1;
                input.erase(0, maxRead);
            }
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

        if (maxRead > 0) {
            Token *newToken = maxAutomaton->CreateToken(input.substr(0,maxRead),lineNumber); //set newToken to maxAutomaton.CreateToken(...)
            lineNumber += maxAutomaton->NewLinesRead(); //increment lineNumber by maxAutomaton.NewLinesRead()
            tokens->push_back(newToken); //add newToken to collection of all tokens
        }
            // No automaton accepted input
            // Create single character undefined token
        else {
            maxRead =1;
            //Token *newToken = nullptr; //set newToken to a  new undefined Token //99% sure this is incorrect
            //Token *newToken = new Token(TokenType::UNDEFINED, input.at(0),lineNumber); // (with first character of input)
            //tokens->push_back(new Token(TokenType::UNDEFINED, input.at(0), lineNumber); //add newToken to collection of all tokens
            //TODO: fix above
        }
        //tokens->push_back(new Token( tokens->at(0)->getType(), input.substr(0,maxRead), lineNumber));

        input.erase(0, maxRead);//remove maxRead characters from input
    }
    tokens->push_back(new Token(TokenType::EOF_TYPE, "", lineNumber)); //add end of file token to all tokens

}

