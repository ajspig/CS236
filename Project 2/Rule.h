//
// Created by Abigail Spigarelli on 9/22/21.
//

#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H

//Grammar:
//headPredicate predicate predicateList
//ID LP ID idlist RP Colon_Dash then predicate and predicateList

#include <string>
#include "Predicate.h"
using namespace std;

class Rule {
private:
    Predicate* headPredicate;//store the head predicate (left side of colon-dash) and
    vector <Predicate*> listOfPredicateBody;//list for the body predicates(right side of colon-dash)

public:
    Rule(Predicate* headPreddy, vector<Predicate *> bodyPreddy);
    Predicate* getHeadPredicate();
    void setHeadPredicate(string idVal, vector <Parameter*> headPred);
    vector <Predicate*> getRightPredicate();
    //Rule(Predicate headPredicate, );
    string ruleToString();

};


#endif //PROJECT1_STARTER_CODE_RULE_H
