//
// Created by Abigail Spigarelli on 9/18/21.
//

#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H

#include <vector>
#include "Token.h"
#include "DatalogProgram.h"//I am 95% sure this is supposed to be included in here
//check slides if you get error "redefinition"


class Parser {
public:
    Parser();
    void parseSyntax(vector<Token*>* tokens);
    void easyMatching(TokenType tokenToCompare);
    string getFailedToken();
    void parseDatalogProgram();
    void parseSchemelist();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();
    bool getSyntaxCheck();
    //current token

private:
    //should have an index for an iterator in order to keep track of which token is next
    //should I also have a private set of tokens?
    vector<Token*>* parserTokens;
    int index;
    bool syntaxCheck = true;
    string tokenFailedOn;
};


#endif //PROJECT1_STARTER_CODE_PARSER_H

//takes in Token objects from lexer
//check syntax
//run this to see if you get success or failure for test on website

//create a function to start parsing. Might look like
// void parse();
// Datalog parse();
//start with all your functions in your parser class as void

//have a function for every single production in the datalog grammar
//inside the functions check for a token type or call another function
//the function that starts it all is datalog function
//use a try catch block to throw a token
//do if statements for terminals with multiple options
//for lamda situations, just have an empty pair of curly braces
//