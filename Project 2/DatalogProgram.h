//
// Created by Abigail Spigarelli on 9/22/21.
//

#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include <vector>
#include "Token.h"
#include <set>


using namespace std;
//included all of these libraries so I could have access to their vectors.

class DatalogProgram {
private:
    vector<Parameter *> vectorOfParam;
    vector<Predicate *> vectorOfQueries;
    Predicate* headPredForRules;
    vector<Predicate *> vectorOfSchemes;
    vector<Predicate *> vectorOfFacts;
    vector<Rule *> vectorOfRules;

    //BELOW FROM PARSER
    vector<Token*>* parserTokens;
    int index;
    bool syntaxCheck = true;
    string tokenFailedOn;
    set<string> domain;

public:
    string datalogProgramToString();
    //for my interpreter I think I want getter functions for schemes facts rules nad queries
    vector<Predicate *> getSchemes(){ return vectorOfSchemes; }
    vector<Predicate *> getFacts(){ return vectorOfFacts; }
    vector<Rule *> getRules(){ return vectorOfRules; }
    vector<Predicate *> getQueries(){ return vectorOfQueries; }

    //BELOW FROM PARSER
    DatalogProgram();
    void parseSyntax(vector<Token*>* tokens);
    void easyMatching(TokenType tokenToCompare);
    string getFailedToken();
    void parseDatalogProgram();
    void parseSchemeList();
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
    //should I make a toString for each of my vectors?
    //be sure to have a way to get the lists of schemes facts, rules, and queries out of DatalogProgram

};


#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
